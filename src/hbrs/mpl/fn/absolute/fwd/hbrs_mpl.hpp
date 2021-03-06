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

#ifndef HBRS_MPL_FN_ABSOLUTE_FWD_HBRS_MPL_HPP
#define HBRS_MPL_FN_ABSOLUTE_FWD_HBRS_MPL_HPP

#include <hbrs/mpl/core/preprocessor.hpp>
#include <hbrs/mpl/dt/smc/fwd.hpp>
#include <hbrs/mpl/dt/smr/fwd.hpp>
#include <boost/hana/tuple.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

struct absolute_impl_smc {
	template<typename Matrix, typename Index>
	constexpr decltype(auto)
	operator()(smc<Matrix, Index> const& s) const;
};

struct absolute_impl_smr {
	template<typename Matrix, typename Index>
	constexpr decltype(auto)
	operator()(smr<Matrix, Index> const& s) const;
};

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#define HBRS_MPL_FN_ABSOLUTE_IMPLS_HBRS_MPL boost::hana::make_tuple(                                                   \
		hbrs::mpl::detail::absolute_impl_smc{},                                                                        \
		hbrs::mpl::detail::absolute_impl_smr{}                                                                         \
	)

#endif // !HBRS_MPL_FN_ABSOLUTE_FWD_HBRS_MPL_HPP
