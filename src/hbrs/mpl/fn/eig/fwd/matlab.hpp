/* Copyright (c) 2019 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_FN_EIG_FWD_MATLAB_HPP
#define HBRS_MPL_FN_EIG_FWD_MATLAB_HPP

#include <hbrs/mpl/config.hpp>

#ifdef HBRS_MPL_ENABLE_MATLAB
	#include <hbrs/mpl/dt/ml_matrix/fwd.hpp>
	#include <hbrs/mpl/dt/ml_vector/fwd.hpp>
	#include <hbrs/mpl/dt/eig_control/fwd.hpp>
	#include <hbrs/mpl/dt/eig_result/fwd.hpp>
#endif

#include <boost/hana/tuple.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <type_traits>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

#ifdef HBRS_MPL_ENABLE_MATLAB

#define _DEC_EIG(lvl)                                                                                                  \
	struct eig_impl_level ## lvl ## _ml_matrix {                                                                       \
		HBRS_MPL_API                                                                                                   \
		eig_result<                                                                                                    \
			ml_column_vector<creal_T> /* eigenvalues */,                                                               \
			ml_matrix<creal_T>        /* eigenvectors */                                                               \
		>                                                                                                              \
		operator()(                                                                                                    \
			ml_matrix<real_T> const& a,                                                                                \
			eig_control<> const& ctrl                                                                                  \
		) const;                                                                                                       \
	};

_DEC_EIG(0)
#undef _DEC_EIG

#else
struct eig_impl_level0_ml_matrix{};
#endif

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#define HBRS_MPL_FN_EIG_IMPLS_MATLAB boost::hana::make_tuple(                                                          \
		hbrs::mpl::detail::eig_impl_level0_ml_matrix{}                                                                 \
	)

#endif // !HBRS_MPL_FN_EIG_FWD_MATLAB_HPP
