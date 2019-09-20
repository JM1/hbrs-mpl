/* Copyright (c) 2018-2019 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_DT_SUBMATRIX_IMPL_HPP
#define HBRS_MPL_DT_SUBMATRIX_IMPL_HPP

#include "fwd.hpp"

#include <hbrs/mpl/core/preprocessor.hpp>

#include <hbrs/mpl/dt/matrix_index.hpp>
#include <hbrs/mpl/dt/smr.hpp>
#include <hbrs/mpl/dt/givens_rotation.hpp>
#include <hbrs/mpl/fn/at.hpp>
#include <hbrs/mpl/fn/size.hpp>
#include <hbrs/mpl/fn/m.hpp>
#include <hbrs/mpl/fn/n.hpp>
#include <hbrs/mpl/fn/plus.hpp>
#include <hbrs/mpl/fn/less_equal.hpp>
#include <hbrs/mpl/fn/not_equal.hpp>
#include <hbrs/mpl/fn/select.hpp>
#include <hbrs/mpl/dt/exception.hpp>
#include <type_traits>

#include <boost/assert.hpp>

HBRS_MPL_NAMESPACE_BEGIN

template<typename Matrix, typename Offset, typename Size>
struct submatrix {
	template<typename Matrix_, typename Offset_, typename Size_>
	constexpr 
	submatrix(Matrix_ && mat, Offset_ && o, Size_ && sz)
	: mat_{HBRS_MPL_FWD(mat)}, o_{HBRS_MPL_FWD(o)}, sz_{HBRS_MPL_FWD(sz)}
	{
		BOOST_ASSERT(
			(*less_equal)(
				plus(m(o_), m(sz_)),
				m(hbrs::mpl::size(mat_))
			)
		);
		
		BOOST_ASSERT(
			(*less_equal)(
				plus(n(o_), n(sz_)),
				n(hbrs::mpl::size(mat_))
			)
		);
	}
	
	constexpr 
	submatrix(submatrix const&) = default;
	constexpr 
	submatrix(submatrix &&) = default;
	
	//TODO: Move to new implementation of assign() function and only enable for specific datatypes, e.g. if Matrix is rtsam
	submatrix&
	operator=(submatrix const& m_) {
		using hbrs::mpl::size;
		BOOST_ASSERT(&m_.mat_ != &this->mat_);
		//TODO: Handle &m_.mat_ == &this->mat_
		
		BOOST_ASSERT((*m)(sz_) == (*m)(size(m_)));
		BOOST_ASSERT((*n)(sz_) == (*n)(size(m_)));
		
		//TODO: Optimize for column_major/row_major
		for (std::size_t i = 0; i < (*m)(size(m_)); ++i) {
			for (std::size_t j = 0; j < (*n)(size(m_)); ++j) {
				at(make_matrix_index(i,j)) = m_.at(make_matrix_index(i,j));
			}
		}
		
		return *this;
	}

	//TODO: Implement move assignment operator!
	constexpr submatrix&
	operator=(submatrix &&) = delete;
	
	//TODO: Move to new implementation of assign() function and only enable for specific datatypes, e.g. if Matrix is rtsam
	submatrix&
	operator=(std::decay_t<Matrix> const& m_) {
		using hbrs::mpl::size;
		if ((*not_equal)(sz_, size(m_))) {
			BOOST_THROW_EXCEPTION(incompatible_matrices_exception{});
		}
		
		//TODO: Optimize for column_major/row_major
		for (std::size_t i = 0; i < m(size(m_)); ++i) {
			for (std::size_t j = 0; j < n(size(m_)); ++j) {
				at(make_matrix_index(i,j)) = m_.at(make_matrix_index(i,j));
			}
		}
		
		return *this;
	}

	//TODO: Move to new implementation of assign() function
	/*
	 * Chapter 5.1.9 (Applying Givens Rotations) on page 241
	 * A = G(i,k,theta)^T * A
	 *              --     --T
	 *              |       |
	 *              |  c s  |
	 * A([i,k],:) = |       | * A([i,k],:)
	 *              | -s c  |
	 *              |       |
	 *              --     --
	 *
	 * Apply the Givens roation on A and return A.
	 */
	template<
		typename Ring,
		typename std::enable_if_t<
			!std::is_const_v<std::remove_reference_t<Ring>>
		>* = nullptr
	>
	submatrix&
	operator=(
		detail::givens_rotation_expression<
			givens_rotation<Ring> const&,
			submatrix<Matrix,Offset,Size> const&
		> const& e
	) {
		if (&(e.rhs()) != this) {
			*this = e.rhs();
		}

		decltype(auto) i     = e.lhs().i();
		decltype(auto) k     = e.lhs().k();
		decltype(auto) theta = e.lhs().theta();

		BOOST_ASSERT(i < (*m)(sz_));
		BOOST_ASSERT(k < (*m)(sz_));

		for (std::size_t j = 0; j <= (*n)(sz_) - 1; ++j) {
			auto tau1 = at(make_matrix_index(i, j));
			auto tau2 = at(make_matrix_index(k, j));
			at(make_matrix_index(i, j)) = theta.c() * tau1 - theta.s() * tau2;
			at(make_matrix_index(k, j)) = theta.s() * tau1 + theta.c() * tau2;
		}
		
		return *this;
	}

	//TODO: Move to new implementation of assign() function
	/*
	 * Chapter 5.1.9 (Applying Givens Rotations) on page 241
	 * A = A * G(i,k,theta)
	 *                           --     --
	 *                           |       |
	 *                           |  c s  |
	 * A(:,[i,k]) = A(:,[i,k]) * |       |
	 *                           | -s c  |
	 *                           |       |
	 *                           --     --
	 *
	 * Apply the Givens roation on A and return A.
	 */
	template<
		typename Ring,
		typename std::enable_if_t<
			!std::is_const_v<std::remove_reference_t<Ring>>
		>* = nullptr
	>
	submatrix&
	operator=(
		detail::givens_rotation_expression<
			submatrix<Matrix,Offset,Size> const&,
			givens_rotation<Ring> const&
		> const& e
	) {
		if (&(e.lhs()) != this) {
			*this = e.lhs();
		}

		decltype(auto) i     = e.rhs().i();
		decltype(auto) k     = e.rhs().k();
		decltype(auto) theta = e.rhs().theta();

		BOOST_ASSERT(i < (*n)(sz_));
		BOOST_ASSERT(k < (*n)(sz_));

		for (std::size_t j = 0; j <= (*m)(sz_) - 1; ++j) {
			auto tau1 = at(make_matrix_index(j, i));
			auto tau2 = at(make_matrix_index(j, k));
			at(make_matrix_index(j, i)) = theta.c() * tau1 - theta.s() * tau2;
			at(make_matrix_index(j, k)) = theta.s() * tau1 + theta.c() * tau2;
		}
		
		return *this;
	}

	
	constexpr decltype(auto)
	size() const { return (sz_); };
	
	template<typename Index>
	constexpr decltype(auto)
	at(Index && i) {
		return (*hbrs::mpl::at)(
			mat_,
			make_matrix_index(
				(*plus)(m(o_), m(HBRS_MPL_FWD(i))),
				(*plus)(n(o_), n(HBRS_MPL_FWD(i)))
			)
		);
	}
	
	template<typename Index>
	constexpr decltype(auto)
	at(Index && i) const {
		return (*hbrs::mpl::at)(
			mat_,
			make_matrix_index(
				(*plus)(m(o_), m(HBRS_MPL_FWD(i))),
				(*plus)(n(o_), n(HBRS_MPL_FWD(i)))
			)
		);
	}
	
	template<typename Index>
	constexpr auto
	operator[](Index && i) & {
		return smr<submatrix &, std::decay_t<Index>>{*this, HBRS_MPL_FWD(i)};
	}
	
	template<typename Index>
	constexpr auto
	operator[](Index && i) const& {
		return smr<submatrix const&, std::decay_t<Index>>{*this, HBRS_MPL_FWD(i)};
	}
	
	template<typename Index>
	constexpr auto
	operator[](Index && i) && {
		return make_smr(std::move(*this), HBRS_MPL_FWD(i));
	}
	
private:
	Matrix mat_;
	Offset const o_;
	Size const sz_;
};

template<
	typename LHS,
	typename RHS,
	typename std::enable_if_t<
		(std::is_same_v< hana::tag_of_t<LHS>, submatrix_tag       > && std::is_same_v< hana::tag_of_t<RHS>, submatrix_tag       >) ||
		(std::is_same_v< hana::tag_of_t<LHS>, submatrix_tag       > && std::is_same_v< hana::tag_of_t<RHS>, givens_rotation_tag >) ||
		(std::is_same_v< hana::tag_of_t<LHS>, givens_rotation_tag > && std::is_same_v< hana::tag_of_t<RHS>, submatrix_tag       >)
	>* = nullptr
>
decltype(auto)
operator*(LHS && lhs, RHS && rhs) {
	return multiply(HBRS_MPL_FWD(lhs), HBRS_MPL_FWD(rhs));
}

HBRS_MPL_NAMESPACE_END

namespace boost { namespace hana {

template<typename Matrix, typename Offset, typename Size>
struct tag_of< hbrs::mpl::submatrix<Matrix, Offset, Size> > {
	using type = hbrs::mpl::submatrix_tag;
};

template <>
struct make_impl<hbrs::mpl::submatrix_tag> {
	
	template<typename Matrix, typename Offset, typename Size>
	static constexpr hbrs::mpl::submatrix< 
		std::decay_t<Matrix>,
		std::decay_t<Offset>,
		std::decay_t<Size>
	>
	apply(Matrix && mat, Offset && o, Size && sz) {
		return {HBRS_MPL_FWD(mat), HBRS_MPL_FWD(o), HBRS_MPL_FWD(sz)};
	}
};

/* namespace hana */ } /* namespace boost */ }


#endif // !HBRS_MPL_DT_CTSSRV_IMPL_HPP
