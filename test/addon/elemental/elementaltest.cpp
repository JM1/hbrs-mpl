/* Copyright (c) 2016-2018 Jakob Meng, <jakobmeng@web.de>
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

// #define BOOST_TEST_TOOLS_UNDER_DEBUGGER
#define BOOST_TEST_MODULE elemental_test
#define BOOST_TEST_MAIN

// #define HBRS_MPL_TEST_DO_NOT_CATCH_EXCEPTIONS
#ifdef HBRS_MPL_TEST_DO_NOT_CATCH_EXCEPTIONS
	// catch exceptions with debugger and allow to examine stack trace
	
	/* NOTE: If linked against boost test library, this program will crash on exit, 
	 *       see e.g.: https://bugzilla.redhat.com/show_bug.cgi?id=1446852
	 */
	#include <boost/throw_exception.hpp>
	#define BOOST_NO_EXCEPTIONS
	#include <boost/test/included/unit_test.hpp>
#else
	#define BOOST_TEST_DYN_LINK
	#include <boost/test/unit_test.hpp>
#endif // !HBRS_MPL_TEST_DO_NOT_CATCH_EXCEPTIONS

#include <hbrs/mpl/detail/test.hpp>
#include <hbrs/mpl/detail/gather.hpp>
#include <elemental/dt/matrix.hpp>
#include <elemental/dt/vector.hpp>
#include <elemental/dt/dist_matrix.hpp>
#include <elemental/dt/dist_vector.hpp>
#include <hbrs/mpl/dt/ctsav.hpp>
#include <hbrs/mpl/dt/matrix_size.hpp>
#include <hbrs/mpl/dt/sm.hpp>
#include <hbrs/mpl/dt/scv.hpp>
#include <vector>
#include <hbrs/mpl/fn/m.hpp>
#include <hbrs/mpl/fn/n.hpp>
#include <hbrs/mpl/fn/size.hpp>
#include <hbrs/mpl/fn/svd.hpp>
#include <hbrs/mpl/fn/pca.hpp>
#include <hbrs/mpl/fn/pca_filter.hpp>
#include <hbrs/mpl/fn/at.hpp>
#include <hbrs/mpl/fn/transpose.hpp>
#include <hbrs/mpl/fn/vertcat.hpp>
#include <hbrs/mpl/fn/expand.hpp>
#include <hbrs/mpl/fn/mean.hpp>
#include <hbrs/mpl/fn/multiply.hpp>
#include <hbrs/mpl/fn/divide.hpp>
#include <hbrs/mpl/fn/transform.hpp>
#include <hbrs/mpl/fn/absolute.hpp>
#include <hbrs/mpl/fn/columns.hpp>
#include <hbrs/mpl/fn/rows.hpp>
#include <hbrs/mpl/fn/indices.hpp>
#include <hbrs/mpl/fn/zip.hpp>
#include <hbrs/mpl/fn/less.hpp>
#include <hbrs/mpl/fn/first.hpp>
#include <hbrs/mpl/fn/second.hpp>
#include <hbrs/mpl/fn/fold1.hpp>
#include <hbrs/mpl/fn/equal.hpp>
#include <hbrs/mpl/fn/power.hpp>
#include <hbrs/mpl/fn/plus.hpp>
#include <hbrs/mpl/fn/select.hpp>
#include <hbrs/mpl/fn/diag.hpp>
#include <hbrs/mpl/fn/times.hpp>
#include <hbrs/mpl/fn/sum.hpp>
#include <boost/hana/pair.hpp>
#include <El.hpp>
#include <boost/format.hpp>

#include "../../data.hpp"

namespace utf = boost::unit_test;
namespace tt = boost::test_tools;

#define _TOL 0.000000001

BOOST_AUTO_TEST_SUITE(elemental_test)

using hbrs::mpl::detail::environment_fixture;
BOOST_TEST_GLOBAL_FIXTURE(environment_fixture);

BOOST_AUTO_TEST_CASE(matrix_m_n_size) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	matrix<double> a0{2,4};
	
	auto const a0_size = (*size)(a0);
	auto const a0_m = (*m)(a0_size);
	auto const a0_m2 = (*m)(a0);
	BOOST_TEST(a0_m == a0_m2);
	BOOST_TEST((*m)(a0) == a0_m);
	BOOST_TEST(a0_m == 2);
	
	auto const a0_n = (*n)(a0_size);
	auto const a0_n2 = (*n)(a0);
	BOOST_TEST(a0_n == a0_n2);
	BOOST_TEST((*n)(a0) == a0_n);
	BOOST_TEST(a0_n == 4);
}

BOOST_AUTO_TEST_CASE(vector_size_at) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	El::Matrix<double> rnd_rv;
	El::Uniform(rnd_rv, 1, 5);
	
	El::Matrix<double> rnd_cv;
	El::Uniform(rnd_cv, 5, 1);
	
	std::vector<double> rnd{{1., 2., 3., 4., 5. }};
	
	auto rv1 = make_row_vector(rnd_rv);
	auto rv2 = make_row_vector(rnd.data(), rnd.size());
	auto cv1 = make_column_vector(rnd_cv);
	auto cv2 = make_column_vector(rnd.data(), rnd.size());
	
	BOOST_TEST((*size)(rv1) == rnd_rv.Width());
	BOOST_TEST((*size)(rv2) == rnd.size());
	
	BOOST_TEST((*size)(cv1) == rnd_cv.Height());
	BOOST_TEST((*size)(cv2) == rnd.size());
	
	for(El::Int i = 0; i < rnd_rv.Width(); ++i) {
		BOOST_TEST((*at)(rv1, i) == rnd_rv(0, i));
		BOOST_TEST((*at)(rv2, i) == (*at)(rnd, i));
	}
	
	for(El::Int i = 0; i < rnd_cv.Height(); ++i) {
		BOOST_TEST((*at)(cv1, i) == rnd_cv(i, 0));
		BOOST_TEST((*at)(cv2, i) == (*at)(rnd, i));
	}
}

BOOST_AUTO_TEST_CASE(matrix_make) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto a1 = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto a1_m = (*m)(size(a1));
	auto a1_n = (*n)(size(a1));
	
	El::Int nr = 0;
	for(El::Int i = 0; i < a1_m; ++i) {
		for(El::Int j = 0; j < a1_n; ++j) {
			nr += 1;
			BOOST_TEST((*at)(a1, make_matrix_index(i,j)) == nr);
		}
	}
	
	auto a2 = elemental::make_matrix(
		std::initializer_list<double>{
			1.,4.,
			2.,5.,
			3.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		column_major_c
	);
	
	auto a2_m = (*m)(size(a2));
	auto a2_n = (*n)(size(a2));
	
	El::Int nr2 = 0;
	for(El::Int i = 0; i < a2_m; ++i) {
		for(El::Int j = 0; j < a2_n; ++j) {
			nr2 += 1;
			BOOST_TEST((*at)(a2, make_matrix_index(i,j)) == nr2);
		}
	}
}


BOOST_AUTO_TEST_CASE(matrix_svd, * utf::tolerance(_TOL)) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a3 = make_sm(
		make_ctsav(test::mat_g), 
		make_matrix_size(test::mat_g_m, test::mat_g_n), 
		row_major_c
	);
	
	auto const a3_size = (*size)(a3);
	auto const a3_m = (*m)(a3_size);
	auto const a3_n = (*n)(a3_size);
	BOOST_TEST(a3_m == test::mat_g_m);
	BOOST_TEST(a3_n == test::mat_g_n);
	
	matrix<double> a4 = elemental::make_matrix(a3);
	
	for(std::size_t i = 0; i < a3_m; ++i) {
		for(std::size_t j = 0; j < a3_n; ++j) {
			(*at)(a4, make_matrix_index((El::Int)i, (El::Int)j)) = a3[i][j];
		}
	}
	for(std::size_t i = 0; i < a3_m; ++i) {
		for(std::size_t j = 0; j < a3_n; ++j) {
			BOOST_TEST((*at)(a4, make_matrix_index((El::Int)i, (El::Int)j)) == a3[i][j]);
		}
	}
	
	elemental::detail::svd_impl_matrix{}(a4, mpl::decompose_mode::complete);
	auto const svd1 = (*svd)(a4, mpl::decompose_mode::complete);
	
	static_assert(std::is_same<
		decltype(svd1),
		mpl::svd_result<matrix<double>, matrix<double>, matrix<double>> const
	>::value, "");
	
	auto && svd1_u = (*at)(svd1, svd_u{});
	auto && svd1_s = (*at)(svd1, svd_s{});
	auto && svd1_v = (*at)(svd1, svd_v{});
	
	BOOST_TEST((*size)(svd1_u) == make_matrix_size((El::Int) a3_m, (El::Int) a3_m));
	BOOST_TEST((*size)(svd1_s) == make_matrix_size((El::Int) a3_m, (El::Int) a3_n));
	BOOST_TEST((*size)(svd1_v) == make_matrix_size((El::Int) a3_n, (El::Int) a3_n));
	
	for(std::size_t i = 0; i < a3_m; ++i) {
		for(std::size_t j = 0; j < a3_n; ++j) {
			BOOST_TEST((*at)(a4, make_matrix_index((El::Int)i, (El::Int)j)) == a3[i][j]);
		}
	}
	
	auto const a5 = (*multiply)(svd1_u, multiply(svd1_s, transpose(svd1_v)));
	for(std::size_t i = 0; i < a3_m; ++i) {
		for(std::size_t j = 0; j < a3_n; ++j) {
			BOOST_TEST((*at)(a5, make_matrix_index((El::Int)i, (El::Int)j)) == a3[i][j]);
		}
	}
}

BOOST_AUTO_TEST_CASE(matrix_multiply_1, * utf::tolerance(_TOL)) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,
			3.,4.,
			5.,6.
		},
		make_matrix_size(3,2),
		row_major_c
	);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		make_matrix_size(2,3),
		row_major_c
	);
	
	auto const c = elemental::make_matrix(
		std::initializer_list<double>{
			 9., 12., 15.,
			19., 26., 33.,
			29., 40., 51.
		},
		make_matrix_size(3,3),
		row_major_c
	);
	
	elemental::detail::multiply_impl_matrix_matrix{}(a, b);
	matrix<double> rc0 = (*multiply)(a, b);
	
	HBRS_MPL_TEST_MMEQ(c, rc0, false);
}

BOOST_AUTO_TEST_CASE(dist_matrix_svd_1, * utf::tolerance(_TOL)) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	// Ref.: https://github.com/elemental/Elemental/blob/master/tests/lapack_like/SVD.cpp
	
	El::Grid grid{El::mpi::COMM_WORLD};
	
	El::Int m = 10;
	El::Int n = 10;
	typedef double Real;
	El::DistMatrix<Real, El::VC, El::STAR, El::ELEMENT> A{grid};
	El::Uniform(A, m, n);
	
	El::SVDCtrl<Real> ctrl;
	ctrl.useLAPACK = true;
	ctrl.useScaLAPACK = true;
	ctrl.bidiagSVDCtrl.wantU = true;
	ctrl.bidiagSVDCtrl.wantV = true;
	ctrl.bidiagSVDCtrl.approach = El::SVDApproach::FULL_SVD;
	
	El::DistMatrix<Real, El::VC, El::STAR, El::ELEMENT> U{grid}, V{grid};
    El::DistMatrix<Real,El::STAR,El::STAR> s{grid};
	
	BOOST_CHECK_EXCEPTION(
		El::SVD(A, U, s, V, ctrl),
		std::logic_error,
		[](std::logic_error const& e){
			return std::string{"Only Thin and Compact singular value options currently supported\n"} == e.what();
		}
	);
	
	ctrl.bidiagSVDCtrl.approach = El::SVDApproach::THIN_SVD;
	/* auto info = */El::SVD(A, U, s, V, ctrl);
	
	auto E = A;
	
	El::DiagonalScale( El::RIGHT, El::NORMAL, s, U );
	El::Gemm( El::NORMAL, El::ADJOINT, Real(-1.), U, V, Real(1.), E );
	
	const Real twoNormA = MaxNorm( s );
	const Real maxNormE = El::MaxNorm( E );
	const Real frobNormE = El::FrobeniusNorm( E );
	const Real eps = El::limits::Epsilon<Real>();
	const Real scaledResidual = frobNormE / (El::Max(m,n)*eps*twoNormA);
	
	BOOST_TEST_MESSAGE("||A - U Sigma V^H||_max = " << maxNormE);
	BOOST_TEST_MESSAGE("||A - U Sigma V^H||_F   = " << frobNormE);
	BOOST_TEST_MESSAGE("||A - U Sigma V_H||_F / (max(m,n) eps ||A||_2) = " << scaledResidual);
	
	BOOST_TEST(maxNormE == 0.);
}

BOOST_AUTO_TEST_CASE(dist_matrix_sum_1, * utf::tolerance(_TOL)) {
	using namespace elemental;
	using namespace hbrs::mpl;
	typedef double Real;
	
	auto copy = [](auto x) { return x; };
	
	El::Grid grid{El::mpi::COMM_WORLD};
	
	// generate and distribute test matrix
	El::DistMatrix<Real, El::VC, El::STAR, El::ELEMENT> b{
		elemental::make_dist_matrix(
			grid,
			elemental::make_matrix(
				std::initializer_list<double>{
					1.,2.,3.,
					4.,5.,6.,
					7.,8.,9.
				},
				make_matrix_size(3,3),
				row_major_c
			)
		)
	};
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	//TODO: Split this big monolithic test into multiple test functions
	
	/////////////////////////// columns ///////////////////////////
	mpl::expression<
		mpl::columns_t,
		std::tuple<
			El::DistMatrix<Real, El::VC, El::STAR, El::ELEMENT> &
		>
	> columns_expr0 = (*columns)(b);
	
	//TODO: implement real unit test for columns(DistMatrix)
	
	/////////////////////////// column sum ///////////////////////////
	
	// Sum up columns
	auto sums_dmat = (*sum)(columns(b));
	{
		auto const expected = elemental::make_row_vector(
			std::initializer_list<double>{
				12.,15.,18.,
			}
		);
		
		HBRS_MPL_TEST_VVEQ(expected, sums_dmat, false);
	}
	
	El::Print(b, "original");
	El::Print(sums_dmat.data(), "column sums");
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	
	auto d_local = elemental::make_matrix(
		make_sm(
			make_ctsav(test::mat_g), make_matrix_size(hana::size_c<test::mat_g_m>, hana::size_c<test::mat_g_n>), row_major_c
		)
	);
	auto d_dist = elemental::make_dist_matrix(grid, d_local);
	auto sums_dmat2 = (*sum)(columns(d_dist));
	{
		auto const expected = (*sum)(columns(d_local));
		HBRS_MPL_TEST_VVEQ(expected, sums_dmat2, false);
	}
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	/////////////////////////// column mean ///////////////////////////
	auto column_mean_dmat = (*mean)(columns(b));
	{
		auto const expected = elemental::make_row_vector(
			std::initializer_list<double>{
				4.,5.,6.,
			}
		);
		
		HBRS_MPL_TEST_VVEQ(expected, column_mean_dmat, false);
	}
	
	El::Print(b, "original");
	El::Print(column_mean_dmat.data(), "column mean");
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	/////////////////////////// expand ///////////////////////////
	
	mpl::expression<
		mpl::expand_t,
		std::tuple<
			dist_row_vector<El::DistMatrix<Real, El::STAR, El::STAR, El::ELEMENT>> const&,
			mpl::matrix_size<El::Int, El::Int> const&
		>
	> expand_expr0 = (*expand)(column_mean_dmat, make_matrix_size(3,3));
	
	//TODO: implement real unit test for expand(dist_row_vector)
	
	/////////////////////////// size ///////////////////////////
	
	//TODO: implement unit test for size(El::DistMatrix<...>)
	
	/////////////////////////// minus ///////////////////////////
	
	auto minus_dmat = (*minus)(b, expand(column_mean_dmat, (*size)(b)));
	{
		auto const expected = elemental::make_matrix(
			std::initializer_list<double>{
				-3.,-3.,-3.,
				0.,0.,0.,
				3.,3.,3.
			},
			make_matrix_size(3,3),
			row_major_c
		);
		
		HBRS_MPL_TEST_MMEQ(expected, minus_dmat, false);
	}
	
	El::Print(b, "original");
	El::Print(minus_dmat, "minus");
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	
	/////////////////////////// plus ///////////////////////////
	
	auto plus_dmat = (*plus)(minus_dmat, expand(column_mean_dmat, (*size)(minus_dmat)));
	{
		HBRS_MPL_TEST_MMEQ(b, plus_dmat, false);
	}
	
	El::Print(b, "original");
	El::Print(plus_dmat, "plus");
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	
	/////////////////////////// svd ///////////////////////////
	
	struct svd_result {
		El::DistMatrix<Real, El::MC, El::MR> u;
		El::DistMatrix<Real, El::STAR, El::STAR> s;
		El::DistMatrix<Real, El::MC, El::MR> v;
	};
	
	auto usv = (*svd)(minus_dmat, mpl::decompose_mode::economy);
	svd_result usv_{
		(*at)(usv, svd_u{}),
		(*at)(usv, svd_s{}),
		(*at)(usv, svd_v{})
	};
	
	{
		El::DistMatrix<Real, El::MC, El::MR> rec_dmat /* reconstructed */ = (*multiply)((*multiply)(usv_.u, usv_.s), (*transpose)(usv_.v));
		HBRS_MPL_TEST_MMEQ(minus_dmat, rec_dmat, false);
	}
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	
	auto c = elemental::make_dist_matrix(
		grid,
		elemental::make_matrix(
			std::initializer_list<double>{
				1.,2.,3.,
				4.,5.,6.,
				7.,8.,9.
			},
			make_matrix_size(3,3),
			row_major_c
		)
	);
	
	auto usv2 = (*svd)(c, mpl::decompose_mode::economy);
	{
		auto rec_dmat /* reconstructed */ = (*multiply)((*multiply)(usv2.u(), usv2.s()), (*transpose)(usv2.v()));
		HBRS_MPL_TEST_MMEQ(c, rec_dmat, false);
	}
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	/////////////////////////// diag ///////////////////////////
	
	auto diag_dmat = (*diag)(b).data();
	{
		auto const expected = elemental::make_matrix(
			std::initializer_list<double>{
				1.,
				5.,
				9.
			},
			make_matrix_size(3,1),
			row_major_c
		);
		
		HBRS_MPL_TEST_MMEQ(expected, diag_dmat, false);
	}
	
	El::Print(b, "original");
	El::Print(diag_dmat, "diag");
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	/////////////////////////// transform ///////////////////////////
	auto transform_dmat = (*transform)(copy(b), [](auto a) { return a * 2; });
	{
		auto const expected = elemental::make_matrix(
			std::initializer_list<double>{
				2.,4.,6.,
				8.,10.,12.,
				14.,16.,18.
			},
			make_matrix_size(3,3),
			row_major_c
		);
		
		HBRS_MPL_TEST_MMEQ(expected, transform_dmat, false);
	}
	
	El::Print(b, "original");
	El::Print(transform_dmat, "transform: x*2");
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	
	auto transform_dist_cv = (*transform)(diag(b), [](auto a) { return a * 3; });
	{
		auto const expected = elemental::make_matrix(
			std::initializer_list<double>{
				3.,
				15.,
				27.
			},
			make_matrix_size(3,1),
			row_major_c
		);
		
		auto got = transform_dist_cv.data();
		HBRS_MPL_TEST_MMEQ(expected, got, false);
	}
	
	El::Print(diag_dmat, "original");
	El::Print(transform_dist_cv.data(), "transform: x*3");
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	/////////////////////////// divide ///////////////////////////
	auto divide_dmat = (*divide)( copy(transform_dist_cv), 3).data();
	{
		auto const expected = elemental::make_matrix(
			std::initializer_list<double>{
				1.,
				5.,
				9.
			},
			make_matrix_size(3,1),
			row_major_c
		);
		
		HBRS_MPL_TEST_MMEQ(expected, divide_dmat, false);
	}
	
	El::Print(transform_dist_cv.data(), "original");
	El::Print(divide_dmat, "divide: x/3");
	
	El::mpi::Barrier();
	BOOST_TEST_PASSPOINT();
	/////////////////////////// select ///////////////////////////
	
	// see unit test dist_matrix_select below
	
	/////////////////////////// - ///////////////////////////
	
	/////////////////////////// - ///////////////////////////
	//TODO
	
	El::Output( boost::format("ColStride: %d, RowStride %d, DistSize %d, CrossSize %d, RedundantSize %d") % b.ColStride() % b.RowStride() % b.DistSize() % b.CrossSize() % b.RedundantSize() );
}

BOOST_AUTO_TEST_CASE(matrix_multiply_2, * utf::tolerance(_TOL)) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,0.,0.,
			0.,1.,0.,
			0.,0.,1.
		},
		make_matrix_size(3,3),
		row_major_c
	);
	
	elemental::detail::multiply_impl_matrix_matrix{}(a, elemental::detail::multiply_impl_matrix_matrix{}(a, a));
	matrix<double> const rb0 = (*multiply)(a, multiply(a, a));
	
	HBRS_MPL_TEST_MMEQ(a, rb0, false);
}

BOOST_AUTO_TEST_CASE(matrix_multiply_3) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			 7.,  8.,
			 9., 10.,
			11., 12.
		},
		matrix_size<El::Int, El::Int>{3,2},
		row_major_c
	);
	
	auto const b_sz = (*size)(b);
	auto const b_m = (*m)(b_sz);
	auto const b_n = (*n)(b_sz);
	
	auto const c = elemental::make_matrix(
		std::initializer_list<double>{
			 58.,  64.,
			139., 154.
		},
		matrix_size<El::Int, El::Int>{2,2},
		row_major_c
	);
	
	auto const c_sz = (*size)(c);
	auto const c_m = (*m)(c_sz);
	auto const c_n = (*n)(c_sz);
	
	auto d = (*multiply)(a, b);
	HBRS_MPL_TEST_MMEQ(c, d, false);
}

BOOST_AUTO_TEST_CASE(matrix_multiply_4) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			 2.,  4.,  6.,
			 8., 10., 12.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const b_sz = (*size)(b);
	auto const b_m = (*m)(b_sz);
	auto const b_n = (*n)(b_sz);
	
	auto d = (*multiply)(a, 2.);
	HBRS_MPL_TEST_MMEQ(b, d, false);
}

BOOST_AUTO_TEST_CASE(matrix_vector_multiply) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,-1.,2.,
			0.,-3.,1.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto const b = make_scv(
		std::vector<double>{
			 2.,
			 1.,
			 0.
		}
	);
	
	auto const b_sz = (*size)(b);
	
	auto const c = make_scv(
		std::vector<double>{
			1.,
			-3.
		}
	);
	
	auto const c_sz = (*size)(c);
	
	auto d = (*multiply)(a, b);
	auto d_sz = (*size)(d);
	
	BOOST_TEST(d_sz == c_sz);
	
	for(El::Int i = 0; i < c_sz; ++i) {
		BOOST_TEST((*at)(d, i) == (*at)(c, i));
	}
}

BOOST_AUTO_TEST_CASE(matrix_divide) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			2.,  4.,  6.,
			8., 10., 12.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const b_sz = (*size)(b);
	auto const b_m = (*m)(b_sz);
	auto const b_n = (*n)(b_sz);
	
	auto d = (*divide)(a, 2.);
	auto d_sz = (*size)(d);
	BOOST_TEST(b_sz == d_sz);
	for(El::Int j = 0; j < b_n; ++j) {
		for(El::Int i = 0; i < b_m; ++i) {
			auto ix = make_matrix_index(i,j);
			BOOST_TEST((*at)(d, ix) == (*at)(b, ix));
		}
	}
}

BOOST_AUTO_TEST_CASE(matrix_plus_1) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	matrix<double> a11{2,3};
	matrix<double> a12{2,3};
	auto const a11_m = (*m)(size(a11));
	auto const a11_n = (*n)(size(a11));
	
	auto const a12_m = (*m)(size(a12));
	auto const a12_n = (*n)(size(a12));
	
	BOOST_TEST(a11_m == a12_m);
	BOOST_TEST(a11_n == a12_n);
	
	for(El::Int i = 0; i < a11_m; ++i) {
		for(El::Int j = 0; j < a11_n; ++j) {
			(*at)(a11, make_matrix_index(i, j)) = i;
			(*at)(a12, make_matrix_index(i, j)) = j;
		}
	}
	auto a13 = (*plus)(a11, a12);
	auto const a13_m = (*m)(size(a13));
	auto const a13_n = (*n)(size(a13));
	BOOST_TEST(a11_m == a13_m);
	BOOST_TEST(a11_n == a13_n);
	
	for(El::Int i = 0; i < a12_m; ++i) {
		for(El::Int j = 0; j < a12_n; ++j) {
			(*at)(a12, make_matrix_index(i, j)) = i+j;
		}
	}
}

BOOST_AUTO_TEST_CASE(matrix_plus_2) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			11.,12.,13.,
			14.,15.,16.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const c = elemental::make_matrix(
		std::initializer_list<double>{
			10.,10.,10.,
			10.,10.,10.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto d = (*plus)(a, c);
	auto d_sz = (*size)(d);
	BOOST_TEST(a_sz == d_sz);
	for(El::Int j = 0; j < a_n; ++j) {
		for(El::Int i = 0; i < a_m; ++i) {
			auto ix = make_matrix_index(i,j);
			BOOST_TEST((*at)(d, ix) == (*at)(b, ix));
			
		}
	}
	
	auto e = (*plus)(a, 10.);
	auto e_sz = (*size)(e);
	BOOST_TEST(a_sz == e_sz);
	for(El::Int j = 0; j < a_n; ++j) {
		for(El::Int i = 0; i < a_m; ++i) {
			auto ix = make_matrix_index(i,j);
			BOOST_TEST((*at)(e, ix) == (*at)(b, ix));
		}
	}
}

BOOST_AUTO_TEST_CASE(matrix_minus) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			11.,12.,13.,
			14.,15.,16.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const c = elemental::make_matrix(
		std::initializer_list<double>{
			10.,10.,10.,
			10.,10.,10.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto d = (*minus)(a, b);
	auto d_sz = (*size)(d);
	BOOST_TEST(a_sz == d_sz);
	for(El::Int j = 0; j < a_n; ++j) {
		for(El::Int i = 0; i < a_m; ++i) {
			auto ix = make_matrix_index(i,j);
			BOOST_TEST((*at)(d, ix) == (*at)(c, ix));
			
		}
	}
	
	auto e = (*minus)(a, 10.);
	auto e_sz = (*size)(e);
	BOOST_TEST(a_sz == e_sz);
	for(El::Int j = 0; j < a_n; ++j) {
		for(El::Int i = 0; i < a_m; ++i) {
			auto ix = make_matrix_index(i,j);
			BOOST_TEST((*at)(e, ix) == (*at)(b, ix));
		}
	}
}

BOOST_AUTO_TEST_CASE(matrix_vertcat) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const z = make_sm(
		make_ctsav(test::mat_h), 
		make_matrix_size(test::mat_h_m, test::mat_h_n), 
		row_major_c
	);
	
	auto const a = elemental::make_matrix(z);
	
	auto a_r0 = (*at)(a, 0);
	auto a_r1 = (*at)(a, 1);
	auto a_r2 = (*at)(a, 2);
	
	elemental::detail::vertcat_impl_smr_smr{}(a_r0, a_r1);
	elemental::detail::vertcat_impl_matrix_smr{}(elemental::detail::vertcat_impl_smr_smr{}(a_r0, a_r1), a_r2);
	
	auto b = (*mpl::vertcat)(mpl::vertcat(a_r0, a_r1), a_r2);
	auto const a_m = (*m)(size(a));
	auto const a_n = (*n)(size(a));
	
	auto const b_m = (*m)(size(b));
	auto const b_n = (*n)(size(b));
	
	BOOST_TEST(a_m == b_m);
	BOOST_TEST(a_n == b_n);
	
	for(El::Int i = 0; i < a_m; ++i) {
		for(El::Int j = 0; j < a_n; ++j) {
			BOOST_TEST((*at)(b, make_matrix_index(i,j)) == (*at)(a, make_matrix_index(i,j)));
		}
	}
}

BOOST_AUTO_TEST_CASE(matrix_expand) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const z = make_sm(
		make_ctsav(test::mat_h), 
		make_matrix_size(test::mat_h_m, test::mat_h_n), 
		row_major_c
	);
	
	auto const a = elemental::make_matrix(z);
	auto const a_m = (*m)(size(a));
	auto const a_n = (*n)(size(a));
	
	auto a_r0 = (*at)(a, 0);
	auto sz = matrix_size<El::Int, El::Int>{a_m*2, a_n*3};
	
	elemental::detail::expand_impl_smr{}(a_r0, sz);
	auto b = (*mpl::expand)(a_r0, sz);
	auto const b_m = (*m)(size(b));
	auto const b_n = (*n)(size(b));
	
	BOOST_TEST(a_m*2 == b_m);
	BOOST_TEST(a_n*3 == b_n);
	
	for(El::Int i = 0; i < b_m; ++i) {
		for(El::Int j = 0; j < b_n; ++j) {
			BOOST_TEST((*at)(b, make_matrix_index(i,j)) == (*at)(a, mpl::matrix_index<El::Int, El::Int>(0,j%a_n)));
		}
	}
}

BOOST_AUTO_TEST_CASE(vector_expand) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	El::Matrix<double> rnd_rv;
	El::Uniform(rnd_rv, 1, 5);
	auto rv = make_row_vector(rnd_rv);
	auto rv_sz = (*size)(rv);
	
	auto const m1_sz = matrix_size<El::Int, El::Int>{1,   rv_sz};
	auto const m2_sz = matrix_size<El::Int, El::Int>{1*2, rv_sz};
	auto const m3_sz = matrix_size<El::Int, El::Int>{1,   rv_sz*2};
	auto const m4_sz = matrix_size<El::Int, El::Int>{1*2, rv_sz*2};
	
	auto m1_m = (*m)(m1_sz);
	auto m1_n = (*n)(m1_sz);
	auto m2_m = (*m)(m2_sz);
	auto m2_n = (*n)(m2_sz);
	auto m3_m = (*m)(m3_sz);
	auto m3_n = (*n)(m3_sz);
	auto m4_m = (*m)(m4_sz);
	auto m4_n = (*n)(m4_sz);
	
	auto m1 = (*expand)(rv, m1_sz);
	auto m2 = (*expand)(rv, m2_sz);
	auto m3 = (*expand)(rv, m3_sz);
	auto m4 = (*expand)(rv, m4_sz);
	
	BOOST_TEST((*m)(size(m1)) == m1_m);
	BOOST_TEST((*n)(size(m1)) == m1_n);
	BOOST_TEST((*m)(size(m2)) == m2_m);
	BOOST_TEST((*n)(size(m2)) == m2_n);
	BOOST_TEST((*m)(size(m3)) == m3_m);
	BOOST_TEST((*n)(size(m3)) == m3_n);
	BOOST_TEST((*m)(size(m4)) == m4_m);
	BOOST_TEST((*n)(size(m4)) == m4_n);
	
	for(El::Int i = 0; i < m1_m; ++i) {
		for(El::Int j = 0; j < m1_n; ++j) {
			BOOST_TEST((*at)(rv, j % m1_n) == (*at)(m1, mpl::matrix_index<El::Int, El::Int>{i, j}));
		}
	}
	
	for(El::Int i = 0; i < m2_m; ++i) {
		for(El::Int j = 0; j < m2_n; ++j) {
			BOOST_TEST((*at)(rv, j % m1_n) == (*at)(m2, mpl::matrix_index<El::Int, El::Int>{i, j}));
		}
	}
	
	for(El::Int i = 0; i < m3_m; ++i) {
		for(El::Int j = 0; j < m3_n; ++j) {
			BOOST_TEST((*at)(rv, j % m1_n) == (*at)(m3, mpl::matrix_index<El::Int, El::Int>{i, j}));
		}
	}
	
	for(El::Int i = 0; i < m4_m; ++i) {
		for(El::Int j = 0; j < m4_n; ++j) {
			BOOST_TEST((*at)(rv, j % m1_n) == (*at)(m4, mpl::matrix_index<El::Int, El::Int>{i, j}));
		}
	}
}

BOOST_AUTO_TEST_CASE(matrix_column_sum) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.,
			7.,8.,9.
		},
		matrix_size<El::Int, El::Int>{3,3},
		row_major_c
	);
	
	auto const b = elemental::make_row_vector(
		std::initializer_list<double>{
			12.,15.,18.
		}
	);
	
	auto c = (*sum)(columns(a));
	HBRS_MPL_TEST_VVEQ(b, c, false);
}

BOOST_AUTO_TEST_CASE(matrix_row_sum) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.,
			7.,8.,9.
		},
		matrix_size<El::Int, El::Int>{3,3},
		row_major_c
	);
	
	auto const b = elemental::make_column_vector(
		std::initializer_list<double>{
			6.,
			15.,
			24.
		}
	);
	
	auto c = (*sum)(rows(a));
	HBRS_MPL_TEST_VVEQ(b, c, false);
}

BOOST_AUTO_TEST_CASE(matrix_mean) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto a_m = (*m)(size(a));
	auto a_n = (*n)(size(a));
	
	elemental::detail::mean_impl_smcs_matrix{}((*columns)(a));
	auto cm = (*mean)(columns(a));
	auto cm_sz = (*size)(cm);
	
	elemental::detail::mean_impl_smrs_matrix{}((*rows)(a));
	auto rm = (*mean)(rows(a));
	auto rm_sz = (*size)(rm);
	
	BOOST_TEST(cm_sz == a_n);
	BOOST_TEST(rm_sz == a_m);
	
	for(El::Int i = 0; i < a_m; ++i) {
		double rm_ = 0.;
		for(El::Int j = 0; j < a_n; ++j) {
			rm_ += (*at)(a, make_matrix_index(i,j));
		}
		
		rm_ /= a_n;
		BOOST_TEST((*at)(rm, i) == rm_);
	}
	
	for(El::Int j = 0; j < a_n; ++j) {
		double cm_ = 0.;
		for(El::Int i = 0; i < a_m; ++i) {
			cm_ += (*at)(a, make_matrix_index(i,j));
		}
		
		cm_ /= a_m;
		BOOST_TEST((*at)(cm, j) == cm_);
	}
	
	auto orm = elemental::make_matrix(
		std::initializer_list<double>{
			2.0,
			5.0
		},
		matrix_size<El::Int, El::Int>{2,1},
		row_major_c
	);
	
	BOOST_TEST((*m)(size(orm)) == a_m);
	BOOST_TEST((*n)(size(orm)) == 1);
	for(El::Int i = 0; i < a_m; ++i) {
		BOOST_TEST((*at)(rm, i) == (*at)(orm, make_matrix_index((El::Int)i, (El::Int)0)));
	}
	
	auto ocm = elemental::make_matrix(
		std::initializer_list<double>{
			2.5, 3.5, 4.5
		},
		matrix_size<El::Int, El::Int>{1,3},
		row_major_c
	);
	
	BOOST_TEST((*m)(size(ocm)) == 1);
	BOOST_TEST((*n)(size(ocm)) == a_n);
	
	for(El::Int j = 0; j < a_n; ++j) {
		BOOST_TEST((*at)(cm, j) == (*at)(ocm, make_matrix_index((El::Int)0, (El::Int)j)));
	}
}


BOOST_AUTO_TEST_CASE(matrix_transform) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			 2.,  4.,  6.,
			 8., 10., 12.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const b_sz = (*size)(b);
	auto const b_m = (*m)(b_sz);
	auto const b_n = (*n)(b_sz);
	
	std::function<double(double)> f = [](double d) -> double { return 2.*d; };
	
	elemental::detail::transform_impl_matrix{}(a, f);
	auto d = (*transform)(a, f);
	auto d_sz = (*size)(d);
	BOOST_TEST(b_sz == d_sz);
	for(El::Int j = 0; j < b_n; ++j) {
		for(El::Int i = 0; i < b_m; ++i) {
			auto ix = make_matrix_index(i,j);
			BOOST_TEST((*at)(d, ix) == (*at)(b, ix));
		}
	}
}

BOOST_AUTO_TEST_CASE(power) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	El::Complex<double> c1 = {2., 0.};
	El::Int i1 = 2;
	El::Complex<double> c2 = {4., 0.};
	
	BOOST_TEST((*mpl::power)(c1, i1) == c2);
}

BOOST_AUTO_TEST_CASE(smr_absolute) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			-1.,2.,-3.
		},
		matrix_size<El::Int, El::Int>{1,3},
		row_major_c
	);
	
	auto const c = (*at)(a, 0);
	auto const c_sz = (*size)(c);
	
	std::vector<double> const b {{ 1.,  2., 3. }};
	auto const b_sz = (*size)(b);
	
	mpl::detail::absolute_impl_smr{}(c);
	auto d = (*absolute)(c);
	auto d_sz = (*size)(d);
	BOOST_TEST(b_sz == d_sz);
	for(El::Int i = 0; i < d_sz; ++i) {
		BOOST_TEST((*at)(d, i) == (*at)(b, i));
	}
}

BOOST_AUTO_TEST_CASE(matrix_absolute) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			-1.,2.,-3.,
			4.,-5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			 1., 2., 3.,
			 4., 5., 6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const b_sz = (*size)(b);
	auto const b_m = (*m)(b_sz);
	auto const b_n = (*n)(b_sz);
	
	elemental::detail::absolute_impl_matrix{}(a);
	auto d = (*absolute)(a);
	auto d_sz = (*size)(d);
	BOOST_TEST(b_sz == d_sz);
	for(El::Int j = 0; j < b_n; ++j) {
		for(El::Int i = 0; i < b_m; ++i) {
			auto ix = make_matrix_index(i,j);
			BOOST_TEST((*at)(d, ix) == (*at)(b, ix));
		}
	}
}

BOOST_AUTO_TEST_CASE(matrix_select) {
	using namespace elemental;
	using namespace hbrs::mpl;
	using hbrs::mpl::select;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.,
			7.,8.,9.
		},
		make_matrix_size(3,3),
		row_major_c
	);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.,
		},
		make_matrix_size(2,3),
		row_major_c
	);
	
	auto const c = elemental::make_matrix(
		std::initializer_list<double>{
			4.,5.,6.,
			7.,8.,9.
		},
		make_matrix_size(2,3),
		row_major_c
	);
	
	auto const d = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,
			4.,5.,
			7.,8.
		},
		make_matrix_size(3,2),
		row_major_c
	);
	
	auto const e = elemental::make_matrix(
		std::initializer_list<double>{
			2.,3.,
			5.,6.,
			8.,9.
		},
		make_matrix_size(3,2),
		row_major_c
	);
	
	elemental::detail::select_impl_matrix{}(a, make_range(make_matrix_index(0,0), make_matrix_index(1,2)));
	matrix<double const> rb0 = (*select)(a, make_range(make_matrix_index(0,0), make_matrix_index(1,2)));
	matrix<double const> rc0 = (*select)(a, make_range(make_matrix_index(1,0), make_matrix_index(2,2)));
	matrix<double const> rd0 = (*select)(a, make_range(make_matrix_index(0,0), make_matrix_index(2,1)));
	matrix<double const> re0 = (*select)(a, make_range(make_matrix_index(0,1), make_matrix_index(2,2)));
	
	matrix<double const> rb1 = (*select)(a, std::make_pair(El::IR(0,2), El::IR(0,3)));
	matrix<double const> rc1 = (*select)(a, std::make_pair(El::IR(1,3), El::IR(0,3)));
	matrix<double const> rd1 = (*select)(a, std::make_pair(El::IR(0,3), El::IR(0,2)));
	matrix<double const> re1 = (*select)(a, std::make_pair(El::IR(0,3), El::IR(1,3)));
	
	matrix<double const> rb2 = (*select)(a, std::make_pair(make_matrix_index(0,0), make_matrix_size(2,3)));
	matrix<double const> rc2 = (*select)(a, std::make_pair(make_matrix_index(1,0), make_matrix_size(2,3)));
	matrix<double const> rd2 = (*select)(a, std::make_pair(make_matrix_index(0,0), make_matrix_size(3,2)));
	matrix<double const> re2 = (*select)(a, std::make_pair(make_matrix_index(0,1), make_matrix_size(3,2)));
	
	matrix<double const> rb3 = (*select)(std::move(a), std::make_pair(El::IR(0,2), El::IR(0,3)));
	matrix<double const> rc3 = (*select)(std::move(a), std::make_pair(El::IR(1,3), El::IR(0,3)));
	matrix<double const> rd3 = (*select)(std::move(a), std::make_pair(El::IR(0,3), El::IR(0,2)));
	matrix<double const> re3 = (*select)(std::move(a), std::make_pair(El::IR(0,3), El::IR(1,3)));
	
	matrix<double> rb4 = (*select)(matrix<double>{a}, std::make_pair(El::IR(0,2), El::IR(0,3)));
	matrix<double> rc4 = (*select)(matrix<double>{a}, std::make_pair(El::IR(1,3), El::IR(0,3)));
	matrix<double> rd4 = (*select)(matrix<double>{a}, std::make_pair(El::IR(0,3), El::IR(0,2)));
	matrix<double> re4 = (*select)(matrix<double>{a}, std::make_pair(El::IR(0,3), El::IR(1,3)));
	
	HBRS_MPL_TEST_MMEQ(b, rb0, false);
	HBRS_MPL_TEST_MMEQ(c, rc0, false);
	HBRS_MPL_TEST_MMEQ(d, rd0, false);
	HBRS_MPL_TEST_MMEQ(e, re0, false);
	
	HBRS_MPL_TEST_MMEQ(b, rb1, false);
	HBRS_MPL_TEST_MMEQ(c, rc1, false);
	HBRS_MPL_TEST_MMEQ(d, rd1, false);
	HBRS_MPL_TEST_MMEQ(e, re1, false);
	
	HBRS_MPL_TEST_MMEQ(b, rb2, false);
	HBRS_MPL_TEST_MMEQ(c, rc2, false);
	HBRS_MPL_TEST_MMEQ(d, rd2, false);
	HBRS_MPL_TEST_MMEQ(e, re2, false);
	
	HBRS_MPL_TEST_MMEQ(b, rb3, false);
	HBRS_MPL_TEST_MMEQ(c, rc3, false);
	HBRS_MPL_TEST_MMEQ(d, rd3, false);
	HBRS_MPL_TEST_MMEQ(e, re3, false);
	
	HBRS_MPL_TEST_MMEQ(b, rb4, false);
	HBRS_MPL_TEST_MMEQ(c, rc4, false);
	HBRS_MPL_TEST_MMEQ(d, rd4, false);
	HBRS_MPL_TEST_MMEQ(e, re4, false);
}

BOOST_AUTO_TEST_CASE(dist_matrix_select) {
	using namespace elemental;
	using namespace hbrs::mpl;
	using hbrs::mpl::select;
	
	El::Grid grid{El::mpi::COMM_WORLD};
	
	auto const a = elemental::make_dist_matrix(
		grid,
		elemental::make_matrix(
			std::initializer_list<double>{
				1.,2.,3.,
				4.,5.,6.,
				7.,8.,9.
			},
			make_matrix_size(3,3),
			row_major_c
			)
	);
	
	auto const b = elemental::make_dist_matrix(
		grid,
		elemental::make_matrix(
			std::initializer_list<double>{
				1.,2.,3.,
				4.,5.,6.,
			},
			make_matrix_size(2,3),
			row_major_c
		)
	);
	
	auto const c = elemental::make_dist_matrix(
		grid,
		elemental::make_matrix(
			std::initializer_list<double>{
				4.,5.,6.,
				7.,8.,9.
			},
			make_matrix_size(2,3),
			row_major_c
		)
	);
	
	auto const d = elemental::make_dist_matrix(
		grid,
		elemental::make_matrix(
			std::initializer_list<double>{
				1.,2.,
				4.,5.,
				7.,8.
			},
			make_matrix_size(3,2),
			row_major_c
		)
	);
	
	auto const e = elemental::make_dist_matrix(
		grid,
		elemental::make_matrix(
			std::initializer_list<double>{
				2.,3.,
				5.,6.,
				8.,9.
			},
			make_matrix_size(3,2),
			row_major_c
		)
	);
	
	elemental::detail::select_impl_matrix{}(a, make_range(make_matrix_index(0,0), make_matrix_index(1,2)));
	auto const rb0 = (*select)(a, make_range(make_matrix_index(0,0), make_matrix_index(1,2)));
	auto const rc0 = (*select)(a, make_range(make_matrix_index(1,0), make_matrix_index(2,2)));
	auto const rd0 = (*select)(a, make_range(make_matrix_index(0,0), make_matrix_index(2,1)));
	auto const re0 = (*select)(a, make_range(make_matrix_index(0,1), make_matrix_index(2,2)));
	auto const rb1 = (*select)(a, std::make_pair(El::IR(0,2), El::IR(0,3)));
	auto const rc1 = (*select)(a, std::make_pair(El::IR(1,3), El::IR(0,3)));
	auto const rd1 = (*select)(a, std::make_pair(El::IR(0,3), El::IR(0,2)));
	auto const re1 = (*select)(a, std::make_pair(El::IR(0,3), El::IR(1,3)));
	auto const rb2 = (*select)(a, std::make_pair(make_matrix_index(0,0), make_matrix_size(2,3)));
	auto const rc2 = (*select)(a, std::make_pair(make_matrix_index(1,0), make_matrix_size(2,3)));
	auto const rd2 = (*select)(a, std::make_pair(make_matrix_index(0,0), make_matrix_size(3,2)));
	auto const re2 = (*select)(a, std::make_pair(make_matrix_index(0,1), make_matrix_size(3,2)));
	auto       rb3 = (*select)(El::DistMatrix<double>{a}, std::make_pair(El::IR(0,2), El::IR(0,3)));
	auto       rc3 = (*select)(El::DistMatrix<double>{a}, std::make_pair(El::IR(1,3), El::IR(0,3)));
	auto       rd3 = (*select)(El::DistMatrix<double>{a}, std::make_pair(El::IR(0,3), El::IR(0,2)));
	auto       re3 = (*select)(El::DistMatrix<double>{a}, std::make_pair(El::IR(0,3), El::IR(1,3)));
	
	
	HBRS_MPL_TEST_MMEQ(b, rb0, false);
	HBRS_MPL_TEST_MMEQ(c, rc0, false);
	HBRS_MPL_TEST_MMEQ(d, rd0, false);
	HBRS_MPL_TEST_MMEQ(e, re0, false);
	HBRS_MPL_TEST_MMEQ(b, rb1, false);
	HBRS_MPL_TEST_MMEQ(c, rc1, false);
	HBRS_MPL_TEST_MMEQ(d, rd1, false);
	HBRS_MPL_TEST_MMEQ(e, re1, false);
	HBRS_MPL_TEST_MMEQ(b, rb2, false);
	HBRS_MPL_TEST_MMEQ(c, rc2, false);
	HBRS_MPL_TEST_MMEQ(d, rd2, false);
	HBRS_MPL_TEST_MMEQ(e, re2, false);
	HBRS_MPL_TEST_MMEQ(b, rb3, false);
	HBRS_MPL_TEST_MMEQ(c, rc3, false);
	HBRS_MPL_TEST_MMEQ(d, rd3, false);
	HBRS_MPL_TEST_MMEQ(e, re3, false);
	
}

BOOST_AUTO_TEST_CASE(column_vector_select) {
	using namespace elemental;
	using namespace hbrs::mpl;
	using hbrs::mpl::select;
	
	auto const a = elemental::make_column_vector(
		std::initializer_list<double>{
			1.,2.,3.,4.,5.,6.,7.,8.,9.
		}
	);
	
	auto const b = elemental::make_column_vector(
		std::initializer_list<double>{
			1.,2.,3.,4.,5.,6.,
		}
	);
	
	auto const c = elemental::make_column_vector(
		std::initializer_list<double>{
			4.,5.,6.,7.,8.,9.
		}
	);
	
	elemental::detail::select_impl_column_vector{}(a, make_range(0,5));
	column_vector<double> rb0 = (*select)(a, make_range(0,5));
	column_vector<double> rc0 = (*select)(a, make_range(3,8));
	
	column_vector<double> rb1 = (*select)(a, El::IR(0,6));
	column_vector<double> rc1 = (*select)(a, El::IR(3,9));
	
	HBRS_MPL_TEST_VVEQ(b, rb0, false);
	HBRS_MPL_TEST_VVEQ(c, rc0, false);
	HBRS_MPL_TEST_VVEQ(b, rb1, false);
	HBRS_MPL_TEST_VVEQ(c, rc1, false);
}

BOOST_AUTO_TEST_CASE(dist_column_vector_select) {
	using namespace elemental;
	using namespace hbrs::mpl;
	using hbrs::mpl::select;
	
	El::Grid grid{El::mpi::COMM_WORLD};
	
	auto const a = elemental::make_dist_column_vector(
		grid,
		std::initializer_list<double>{
			1.,2.,3.,4.,5.,6.,7.,8.,9.
		}
	);
	
	auto const b = elemental::make_dist_column_vector(
		grid,
		std::initializer_list<double>{
			1.,2.,3.,4.,5.,6.,
		}
	);
	
	auto const c = elemental::make_dist_column_vector(
		grid,
		std::initializer_list<double>{
			4.,5.,6.,7.,8.,9.
		}
	);
	
	elemental::detail::select_impl_dist_column_vector{}(a, make_range(0,5));
	auto const rb0 = (*select)(a, make_range(0,5));
	auto const rc0 = (*select)(a, make_range(3,8));
	auto const rb1 = (*select)(a, El::IR(0,6));
	auto const rc1 = (*select)(a, El::IR(3,9));
	auto const rb2 = (*select)(std::move(a), El::IR(0,6));
	auto const rc2 = (*select)(std::move(a), El::IR(3,9));
	
	HBRS_MPL_TEST_VVEQ(b, rb0, false);
	HBRS_MPL_TEST_VVEQ(c, rc0, false);
	HBRS_MPL_TEST_VVEQ(b, rb1, false);
	HBRS_MPL_TEST_VVEQ(c, rc1, false);
	HBRS_MPL_TEST_VVEQ(b, rb2, false);
	HBRS_MPL_TEST_VVEQ(c, rc2, false);
}

BOOST_AUTO_TEST_CASE(matrix_columns) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto b = (*mpl::columns)(a);
	auto const b_sz = (*size)(b);
	BOOST_TEST(b_sz == a_n);
	
	for(El::Int j = 0; j < a_n; ++j) {
		auto column = (*at)(b, j);
		BOOST_TEST((*size)(column) == a_m);
		for(El::Int i = 0; i < a_m; ++i) {
			BOOST_TEST((*at)(column, i) == (*at)(a, make_matrix_index(i,j)));
		}
	}
}

BOOST_AUTO_TEST_CASE(matrix_rows) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{2,3},
		row_major_c
	);
	
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto b = (*mpl::rows)(a);
	auto const b_sz = (*size)(b);
	BOOST_TEST(b_sz == a_m);
	
	for(El::Int i = 0; i < a_m; ++i) {
		auto row = (*at)(b, i);
		BOOST_TEST((*size)(row) == a_n);
		for(El::Int j = 0; j < a_n; ++j) {
			BOOST_TEST((*at)(row, j) == (*at)(a, make_matrix_index(i,j)));
		}
	}
}

BOOST_AUTO_TEST_CASE(matrix_indices) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,4.,5.,6.
		},
		matrix_size<El::Int, El::Int>{1,6},
		row_major_c
	);
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			1.,
			2.,
			3.,
			4.,
			5.,
			6.
		},
		matrix_size<El::Int, El::Int>{6,1},
		row_major_c
	);
	auto const b_sz = (*size)(b);
	auto const b_m = (*m)(b_sz);
	auto const b_n = (*n)(b_sz);
	
	std::vector<double> const c {{ 0.,1.,2.,3.,4.,5. }};
	auto const c_sz = (*size)(c);
	
	auto d = (*indices)(at(mpl::rows(a), 0));
	auto const d_sz = (*size)(d);
	BOOST_TEST(d_sz == c_sz);
	
	auto e = (*indices)(at(mpl::columns(b), 0));
	auto const e_sz = (*size)(e);
	BOOST_TEST(e_sz == c_sz);
	
	for(El::Int i = 0; i < c_sz; ++i) {
		BOOST_TEST((*at)(d, i) == (*at)(c, i));
		BOOST_TEST((*at)(e, i) == (*at)(c, i));
	}
}

BOOST_AUTO_TEST_CASE(matrix_fold1) {
	using namespace elemental;
	using namespace hbrs::mpl;
	namespace hana = boost::hana;
	
	matrix<double> zero{2,2};
	
	mpl::zas<
		mpl::smc<
			matrix<double>,
			El::Int
		>,
		boost::integer_range<El::Int>
	> z1 = make_zas(make_smc(zero, El::Int{0}), boost::irange(0,2));
	
	static constexpr auto f1 = [](hana::pair<El::Int,El::Int> i, hana::pair<El::Int,El::Int> j) -> hana::pair<El::Int,El::Int> { 
		return { (*first)(i) + (*first)(j), (*second)(i) + (*second)(j) };
	};
	
	hana::pair<El::Int,El::Int> p1 = elemental::detail::fold1_impl_zas_smc_matrix_irange{}(z1, f1);
	
	hana::pair<El::Int,El::Int> p2 = (*fold1)(z1, f1);
	BOOST_TEST((*equal)(p2,hana::make_pair(0,1)));
}

BOOST_AUTO_TEST_CASE(matrix_transform_zip_fold1) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,4.,5.,6.,
			6.,5.,4.,3.,2.,1.
		},
		matrix_size<El::Int, El::Int>{2,6},
		row_major_c
	);
	auto const a_sz = (*size)(a);
	auto const a_m = (*m)(a_sz);
	auto const a_n = (*n)(a_sz);
	
	static constexpr auto zip_with_idx = [](auto && dim) {
		return (*zip)(HBRS_MPL_FWD(dim), (*indices)(HBRS_MPL_FWD(dim)));
	};
	
	std::vector<zas<
		smc<matrix<double> const&, El::Int>,
		boost::integer_range<El::Int>
	>> zipped_cols_seq = (*transform)(mpl::columns(a), zip_with_idx);
	
	std::vector<zas<
		smr<matrix<double> const&, El::Int>,
		boost::integer_range<El::Int>
	>> zipped_rows_seq = (*transform)(mpl::rows(a), zip_with_idx);
	
	BOOST_TEST(zipped_cols_seq.size() == a_n);
	BOOST_TEST(zipped_rows_seq.size() == a_m);
	
	static constexpr auto max = [](auto && dim) {
		return (*fold1)(
			HBRS_MPL_FWD(dim),
			[](auto && a, auto && b) {
				if ((*less)(first(a), first(b))) {
					return HBRS_MPL_FWD(b);
				} else {
					return HBRS_MPL_FWD(a);
				}
			}
		);
	};
	
	std::vector<hana::pair<double const&, int>> max_of_cols = (*transform)(zipped_cols_seq, max);
	std::vector<hana::pair<double const&, int>> max_of_rows = (*transform)(zipped_rows_seq, max);
	
	BOOST_TEST(max_of_cols.size() == a_n);
	BOOST_TEST(max_of_rows.size() == a_m);
	
	std::vector<double> max_cols_vals = (*transform)(max_of_cols, *first);
	std::vector<int>    max_cols_idxs = (*transform)(max_of_cols, *second);
	
	std::vector<double> max_rows_vals = (*transform)(max_of_rows, *first);
	std::vector<int>    max_rows_idxs = (*transform)(max_of_rows, *second);
	
	BOOST_TEST(max_cols_vals == (std::vector<double> {{ 6.,5.,4.,4.,5.,6. }}));
	BOOST_TEST(max_cols_idxs == (std::vector<int>    {{ 1,1,1,0,0,0       }}));
	BOOST_TEST(max_rows_vals == (std::vector<double> {{ 6., 6.            }}));
	BOOST_TEST(max_rows_idxs == (std::vector<int>    {{ 5, 0              }}));
}

BOOST_AUTO_TEST_CASE(matrix_pca, * utf::tolerance(_TOL)) {
	using namespace elemental;
	using namespace hbrs::mpl;
	namespace hana = boost::hana;
	
	static constexpr auto a = make_sm(
		make_ctsav(test::mat_g),
		make_matrix_size(hana::size_c<test::mat_g_m>, hana::size_c<test::mat_g_n>),
		row_major_c
	);
	
	static constexpr auto a_sz = (*size)(a);
	static constexpr auto a_m = (*m)(a_sz);
	static constexpr auto a_n = (*n)(a_sz);
	
	matrix<double> b = elemental::make_matrix(a);
	
	elemental::detail::pca_impl_matrix{}(b, true);
	
	pca_result<
		matrix<double>,
		matrix<double>,
		elemental::column_vector<double>,
		elemental::row_vector<double>
	> r = (*pca)(b, true);
	
	auto && r_coeff = (*at)(r, pca_coeff{});
	auto && r_score = (*at)(r, pca_score{});
	auto && r_latent = (*at)(r, pca_latent{});
	auto && r_mean = (*at)(r, pca_mean{});
	
	BOOST_TEST((*size)(r_coeff) == make_matrix_size((El::Int) a_n, (El::Int) a_n));
	BOOST_TEST((*size)(r_score) == make_matrix_size((El::Int) a_m, (El::Int) a_n));
	BOOST_TEST((*size)(r_latent) == (El::Int) a_n);
	BOOST_TEST((*size)(r_mean) == (El::Int) a_n);
	
	auto r_centered = (*multiply)(r_score, transpose(r_coeff));
	auto rcst /* reconstructed */ = (*plus)(r_centered, expand(r_mean, size(r_centered)));
	
	HBRS_MPL_TEST_MMEQ(b, rcst, false);
	HBRS_MPL_TEST_MMEQ(a, b, false);

	auto const e_coeff = elemental::make_matrix(
		std::initializer_list<double>{
			-0.067799985695474,  -0.646018286568728,   0.567314540990512,   0.506179559977706,
			-0.678516235418647,  -0.019993340484099,  -0.543969276583817,   0.493268092159296,
			+0.029020832106229,   0.755309622491133,   0.403553469172668,   0.515567418476836,
			+0.730873909451461,  -0.108480477171676,  -0.468397518388290,   0.484416225289198
		},
		matrix_size<El::Int, El::Int>{4,4},
		row_major_c
	);
	
	auto const e_score = elemental::make_matrix(
		std::initializer_list<double>{
			+36.821825999449707,  -6.870878154227366,  -4.590944457629756,   0.396652582713917,
			+29.607273420710953,   4.610881963526309,  -2.247578163663929,  -0.395843536696505,
			-12.981775719737623,  -4.204913183175936,   0.902243082694701,  -1.126100587210616,
			+23.714725720918025,  -6.634052554708716,   1.854742000806314,  -0.378564808384689,
			-0.553191676624599,  -4.461732123178686,  -6.087412652325182,   0.142384896047280,
			-10.812490833309822,  -3.646571174544056,   0.912970791674606,  -0.134968810314681,
			-32.588166608817929,   8.979846284936059,  -1.606265913996590,   0.081763927599947,
			+22.606395499005593,  10.725906457369444,   3.236537714483414,   0.324334774646370,
			-9.262587237675840,   8.985373347478783,  -0.016909578102172,  -0.543746175981798,
			-3.283969329640687, -14.157277337500910,   7.046512994833767,   0.340509860960603,
			+9.220031117829384,  12.386080787220449,   3.428342878284622,   0.435152769664897,
			-25.584908517429557,  -2.781693148152385,  -0.386716066864489,   0.446817950545604,
			-26.903161834677608,  -2.930971165042989,  -2.445522630195304,   0.411607156409657
		},
		matrix_size<El::Int, El::Int>{13,4},
		row_major_c
	);
	
	auto const e_latent = elemental::make_column_vector(
		std::initializer_list<double>{
			5.177968780739056*100,
			0.674964360487231*100,
			0.124054300480810*100,
			0.002371532651878*100
		}
	);
	
	auto const e_mean = elemental::make_row_vector(
		std::initializer_list<double>{
			7.461538461538462,  48.153846153846153,  11.769230769230770,  30.000000000000000
		}
	);
	
	BOOST_TEST((unsigned)(*m)(size(r_coeff)) == (unsigned)(*m)(size(e_coeff)));
	BOOST_TEST((unsigned)(*n)(size(r_coeff)) == (unsigned)(*n)(size(e_coeff)));
	BOOST_TEST((unsigned)(*m)(size(r_score)) == (unsigned)(*m)(size(e_score)));
	BOOST_TEST((unsigned)(*n)(size(r_score)) == (unsigned)(*n)(size(e_score)));
	BOOST_TEST((unsigned)(*size)(r_latent) == (unsigned)(*size)(e_latent));
	BOOST_TEST((unsigned)(*size)(r_mean) == (unsigned)(*size)(e_mean));
	
	HBRS_MPL_TEST_MMEQ(e_coeff, r_coeff, true);
	HBRS_MPL_TEST_MMEQ(e_score, r_score, true);
	HBRS_MPL_TEST_VVEQ(e_latent, r_latent, false);
	HBRS_MPL_TEST_VVEQ(e_mean, r_mean, false);
}


BOOST_AUTO_TEST_CASE(matrix_diag) {
	using namespace elemental;
	using namespace hbrs::mpl;
	using hbrs::mpl::select;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.,
			7.,8.,9.
		},
		make_matrix_size(3,3),
		row_major_c
	);
	
	auto const b = elemental::make_column_vector(
		std::initializer_list<double>{
			1.,
			5.,
			9.
		}
	);
	
	elemental::detail::diag_impl_matrix{}(a);
	elemental::column_vector<double> rb0 = (*diag)(a);
	
	HBRS_MPL_TEST_VVEQ(b, rb0, false);
}


BOOST_AUTO_TEST_CASE(column_vector_transform) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_column_vector(
		std::initializer_list<double>{
			1.,
			2.,
			3.,
			4.,
			5.,
			6.
		}
	);
	
	auto const b = elemental::make_column_vector(
		std::initializer_list<double>{
			 2.,
			 4.,
			 6.,
			 8.,
			 10.,
			 12.
		}
	);
	
	std::function<double(double)> f = [](double d) -> double { return 2.*d; };
	
	elemental::detail::transform_impl_vector{}(a, f);
	column_vector<double> rb0 = (*transform)(a, f);
	
	HBRS_MPL_TEST_VVEQ(b, rb0, false);
}

BOOST_AUTO_TEST_CASE(row_vector_transform) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_row_vector(
		std::initializer_list<double>{
			1., 2., 3., 4., 5., 6.
		}
	);
	
	auto const b = elemental::make_row_vector(
		std::initializer_list<double>{
			 2., 4., 6., 8., 10., 12.
		}
	);
	
	std::function<double(double)> f = [](double d) -> double { return 2.*d; };
	
	elemental::detail::transform_impl_vector{}(a, f);
	row_vector<double> rb0 = (*transform)(a, f);
	
	HBRS_MPL_TEST_VVEQ(b, rb0, false);
}

BOOST_AUTO_TEST_CASE(column_vector_divide) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_column_vector(
		std::initializer_list<double>{
			 2.,
			 4.,
			 6.,
			 8.,
			 10.,
			 12.
		}
	);
	
	auto const b = elemental::make_column_vector(
		std::initializer_list<double>{
			1.,
			2.,
			3.,
			4.,
			5.,
			6.
		}
	);
	
	elemental::detail::divide_impl_vector_scalar{}(a, 2.);
	column_vector<double> rb0 = (*divide)(a, 2.);
	
	HBRS_MPL_TEST_VVEQ(b, rb0, false);
}

BOOST_AUTO_TEST_CASE(matrix_times) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	auto const a = elemental::make_matrix(
		std::initializer_list<double>{
			1.,2.,3.,
			4.,5.,6.,
			7.,8.,9.
		},
		make_matrix_size(3,3),
		row_major_c
	);
	
	auto const b = elemental::make_matrix(
		std::initializer_list<double>{
			2.,2.,2.,
			2.,2.,2.,
			2.,2.,2.
		},
		make_matrix_size(3,3),
		row_major_c
	);
	
	auto const c = elemental::make_matrix(
		std::initializer_list<double>{
			2.,4.,6.,
			8.,10.,12.,
			14.,16.,18.
		},
		make_matrix_size(3,3),
		row_major_c
	);
	
	elemental::detail::times_impl_matrix_matrix{}(a, b);
	matrix<double> rc0 = (*times)(a, b);
	
	HBRS_MPL_TEST_MMEQ(c, rc0, false);
}

BOOST_AUTO_TEST_CASE(dist_matrix_times) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	El::Grid grid{El::mpi::COMM_WORLD};
	
	auto const a = elemental::make_dist_matrix(
		grid,
		elemental::make_matrix(
			std::initializer_list<double>{
				1.,2.,3.,
				4.,5.,6.,
				7.,8.,9.
			},
			make_matrix_size(3,3),
			row_major_c
		)
	);
	
	auto const b = elemental::make_dist_row_vector(
		grid,
		std::initializer_list<double>{
			2.,2.,2.,
		}
	);
	
	auto const c = elemental::make_dist_matrix(
		grid,
		elemental::make_matrix(
			std::initializer_list<double>{
				2.,4.,6.,
				8.,10.,12.,
				14.,16.,18.
			},
			make_matrix_size(3,3),
			row_major_c
		)
	);
	
	auto rc0 = (*times)(a, expand(b, size(a)));
	HBRS_MPL_TEST_MMEQ(c, rc0, false);
}

BOOST_AUTO_TEST_CASE(matrix_pca_filter, * utf::tolerance(_TOL)) {
	using namespace elemental;
	using namespace hbrs::mpl;
	
	static constexpr auto a = make_sm(
		make_ctsav(test::mat_g),
		make_matrix_size(hana::size_c<test::mat_g_m>, hana::size_c<test::mat_g_n>),
		row_major_c
	);
	
	static constexpr auto a_sz = (*size)(a);
	static constexpr auto a_m = (*m)(a_sz);
	static constexpr auto a_n = (*n)(a_sz);
	
	auto const b = elemental::make_matrix(a);
	std::vector<bool> const keep(std::min((std::size_t)a_m, (std::size_t)a_n), true);
	
	elemental::detail::pca_filter_impl_matrix{}(b, keep);
	
	pca_filter_result<
		matrix<double>,
		elemental::column_vector<double>
	> rslt = (*pca_filter)(b, keep);
	
	auto && data   = (*at)(rslt, pca_filter_data{});
	auto && latent = (*at)(rslt, pca_filter_latent{});
	
	HBRS_MPL_TEST_MMEQ(b, data, false);
	BOOST_TEST((*size)(latent) == (El::Int) a_n);
}

BOOST_AUTO_TEST_SUITE_END()
