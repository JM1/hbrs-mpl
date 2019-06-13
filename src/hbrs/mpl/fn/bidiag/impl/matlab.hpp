/* Copyright (c) 2018 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_FN_BIDIAG_IMPL_MATLAB_HPP
#define HBRS_MPL_FN_BIDIAG_IMPL_MATLAB_HPP

#include <hbrs/mpl/core/preprocessor.hpp>
#include <hbrs/mpl/dt/decompose_mode.hpp>
#include <hbrs/mpl/dt/bidiag_result.hpp>
#include <hbrs/mpl/dt/ml_matrix.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <type_traits>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace mpl = hbrs::mpl;
namespace detail {

#define _DEC_BIDIAG(lvl)                                                                                               \
	struct bidiag_impl_level ## lvl {                                                                                  \
		mpl::bidiag_result<                                                                                            \
			hbrs::mpl::ml_matrix<real_T> /* U */,                                                                            \
			hbrs::mpl::ml_matrix<real_T> /* B */,                                                                            \
			hbrs::mpl::ml_matrix<real_T> /* V */                                                                             \
		>                                                                                                              \
		operator()(hbrs::mpl::ml_matrix<real_T> const& a, mpl::decompose_mode mode) const;                                   \
	};

_DEC_BIDIAG(0)
#undef _DEC_BIDIAG

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#define HBRS_MPL_FN_BIDIAG_IMPLS_MATLAB boost::hana::make_tuple(                                                           \
		matlab::detail::bidiag_impl_level0{}                                                                           \
	)

#endif // !HBRS_MPL_FN_BIDIAG_IMPL_MATLAB_HPP