/* Copyright (c) 2019 Abdullah Güntepe, <abdullah@guentepe.com>
 * Copyright (c) 2019 Jakob Meng, <jakobmeng@web.de>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HBRS_MPL_FN_SVD_IMPL_HBRS_MPL_HPP
#define HBRS_MPL_FN_SVD_IMPL_HBRS_MPL_HPP

#include "../fwd/hbrs_mpl.hpp"

#include <hbrs/mpl/config.hpp>
#include <hbrs/mpl/core/preprocessor.hpp>
#include <hbrs/mpl/dt/bidiag_result.hpp>
#include <hbrs/mpl/dt/svd_result.hpp>
#include <hbrs/mpl/dt/rtsam.hpp>
#include <hbrs/mpl/dt/submatrix.hpp>
#include <hbrs/mpl/dt/rtsacv.hpp>
#include <hbrs/mpl/dt/rtsarv.hpp>
#include <hbrs/mpl/dt/range.hpp>
#include <hbrs/mpl/fn/bidiag.hpp>
#include <hbrs/mpl/fn/givens.hpp>
#include <hbrs/mpl/fn/almost_equal.hpp>
#include <hbrs/mpl/fn/select.hpp>
#include <hbrs/mpl/fn/multiply.hpp>
#include <cmath>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

/*
 * Algorithm 8.6.2 (The SVD Algorithm) on page 492
 * Given matrix A (which is real and m-by-n) (m>=n) the following
 * algorithm computes the SVD, where U (which is real and m-by-m) is
 * orthogonal and V (which is real and n-by-n) is orthogonal.
 *
 * Contrary to the book this algorithm also computes U' and V. Taking
 * matrices U' and V from the bidiagonalization it overwrites them by
 * applying the Givens transformations calculated in this algorithm to
 * them.
 *
 * Instead of overwriting A this algorithm stores A, U' and V and
 * returns them in the Struct SVDResult.
 */
template<
	typename Ring,
	storage_order Order
>
decltype(auto)
svd_impl::operator()(rtsam<Ring,Order> const& A, int econ) {
	BOOST_ASSERT(m(size(A)) >= n(size(A)));

	//Use Algorithm 5.4.2 to compute the bidiagonalization.
	auto UAV {bidiag(A, econ)};
	svd_result UBV {make_svd_result(UAV.u(), UAV.b(), UAV.v())};

	auto& U {UBV.u()};
	auto& B {UBV.s()};
	auto& V {UBV.v()};

	auto const n {size(A).n()};

	std::size_t q {0};
	std::size_t p {0};

	while (q != n) {
		for (std::size_t i {0}; i < n - 1; ++i) {
			if (almost_equal(0., B[i][i+1])) {
				B[i][i+1] = 0;
			}
		}

		/*
		 * Find the largest q and the smallest p such that if
		 *     -----------------
		 *     | B11   0    0  |    p
		 *     |               |
		 * B = |  0   B22   0  |  n-p-q
		 *     |               |
		 *     |  0    0   B33 |    q
		 *     -----------------
		 *        p  n-p-q  q
		 * then B33 is diagonal and B22 has a nonzero superdiagonal.
		 */
		
		{ // First find q
			for (q = 0; q < n; ++q) {
				if (q == n-1) {
					q = n;
					break;
				} else if (B[n-1 - q - 1][n-1 - q] != 0) {
					break;
				}
			}
		}
		
		if (q < n) {
			/*
			 * Second find p
			 * In the book this part is before the if condition. We
			 * moved it inside the if condition for optimization.
			 */
			{
				for (p = n-1 - q; p >= 1; --p) {
					if (B[p-1][p] == 0) {
						break;
					} else if (p == 1) {
						p = 0;
						break;
					}
				}
			}
			
			/*
			 * if any diagonal entry in B22 is zero, then zero the
			 * superdiagonal entry in the same row.
			 */
			auto zeroFound {false}; // Turns true once a zero is found in the bidiagonal of B22
			for (auto i {p}; i < n - q; ++i) {
				if (B[i][i] == 0) {
					zeroFound = true;
					if (i < n-1 - q) {
						for (auto j {i + 1}; j < n - q; ++j) {
							auto theta(givens(-B[j][j], B[i][j]));
							B = G(i, j, theta) * B;
							U = U * G(i, j, theta);
						}
					} else {
						for (auto j {n-1 - q - 1}; j >= p; --j) {
							auto theta(givens(B[j][j], B[j][n-1 - q]));
							B = B * G(j, n-1 - q, theta);
							V = V * G(j, n-1 - q, theta);
						}
					}
				}
			}
			
			if (zeroFound);
			else {
				svd_step(B, p, q, U, V); // Apply Algorithm 8.6.1 to B22
				/* In the book there is another line here that looks
				 * like this:
				 * B = diag(Ip,U,Iq+m-n)' B diag(Ip,V,Iq)
				 * But that line is actually not part of the algorithm.
				 */
			}
		}
	}
	return UBV;
}

/*
 * Algorithm 8.6.1 (Golub-Kahan SVD Step) on page 491
 * Given a bidiagonal matrix B (which is of real numbers and of the
 * dimensions m-by-n) having no zeros on its diagonal or superdiagonal,
 * the following algorithm overwrites B with the bidiagonal matrix
 * B=U'BV where U and V are orthogonal and V is essentially the
 * orthogonal matrix that would be obtained by applying Algorithm
 * 8.3.2 to T=B'B.
 *
 * Contrary to the book this algorithm also computes U' and V. Given
 * matrices U' and V it overwrites them by applying the Givens
 * transformations calculated in this algorithm to them.
 *
 * In the Book B is actually B22 which is a submatrix of B. But here
 * we take B and the paramters p and q which are then used to create
 * the submatrix. Also p and q are necessary for the calculation of U
 * and V.
 */
template<
	typename Ring,
	storage_order Order
>
void
svd_impl::svd_step(rtsam<Ring,Order>& B, std::size_t const p, std::size_t const q, rtsam<Ring,Order>& U, rtsam<Ring,Order>& V) {
	range<std::size_t,std::size_t> const pq { p, n(size(B))-1 - q }; // The range for B22 rows and columns
	auto B22 {B(pq, pq)};

	/* Let mu be the eigenvalue of the trailing 2-by-2 submatrix of
	 * T=B'B that is closer to tnn.
	 *
	 * Calculate mu.
	 */
	/* auto const T {transpose(B22) * B22}; */ // FIXME
	auto                                 T   { transpose(B22) * B22 };
	range<std::size_t,std::size_t> const T22 { m(size(T)) - 2, m(size(T)) - 1 };
	auto                           const l   { eigenvalueOf2x2Matrix(T(T22, T22)) };
	double                         const tnn { T[m(size(T))-1][m(size(T))-1] };
	auto                           const mu  { std::abs(l.at(0) - tnn) < std::abs(l.at(1) - tnn) ? l.at(0) : l.at(1) };

	auto y { T[0][0] - mu };
	auto z { T[0][1] };

	std::array<double, 2> theta;
	for (std::size_t k {0}; k < n(size(B22))-1; ++k) {
		// Determine c = cos(theta) and s = sin(theta) such that
		theta = givens(y, z);
		B22 = B22 * G(  k,   k + 1, theta);
		V   = V   * G(p+k, p+k + 1, theta);

		y = B22[k  ][k];
		z = B22[k+1][k];

		// Determine c = cos(theta) and s = sin(theta) such that
		theta = givens(y, z);
		B22 = G(k, k + 1, theta) * B22;
		U   = U * G(p+k, p+k + 1, theta);
		if (k + 1 < n(size(B22))-1) {
			y = B22[k][k+1];
			z = B22[k][k+2];
		}
	}
}

/*
 * Returns an array of lenght 2 that holds eigenvalues of 2x2 Matrix A.
 */
template<
	typename Ring,
	storage_order Order,
	typename Offset,
	typename Size
>
auto const
svd_impl::eigenvalueOf2x2Matrix(submatrix<rtsam<Ring,Order>&, Offset,Size> const& A) {
	std::array<Ring, 2> result;
	if (A.at(make_matrix_index(0, 1)) == 0 && A.at(make_matrix_index(1, 0)) == 0) {
		result[0] = 1;
		result[1] = 0;
	} else {
		double const T {A.at(make_matrix_index(0, 0)) + A.at(make_matrix_index(1, 1))};
		double const D {A.at(make_matrix_index(0, 0)) * A.at(make_matrix_index(1, 1)) - A.at(make_matrix_index(0, 1)) * A.at(make_matrix_index(1, 0))};

		result[0] = T / 2 + std::sqrt((T * T / 4 - D));
		result[1] = T / 2 - std::sqrt((T * T / 4 - D));
	}
	return result;
}

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_FN_SVD_IMPL_HBRS_MPL_HPP