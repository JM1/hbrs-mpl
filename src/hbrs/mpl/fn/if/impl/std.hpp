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

#ifndef HBRS_MPL_FN_IF_IMPL_STD_HPP
#define HBRS_MPL_FN_IF_IMPL_STD_HPP

#include "../fwd/std.hpp"

#include <hbrs/mpl/core/preprocessor.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

template <
	typename If,
	typename Else
>
constexpr decltype(auto)
if_impl_std_types::operator()(bool const& b, If && i, Else && e) const {
	return b ? HBRS_MPL_FWD(i) : HBRS_MPL_FWD(e);
}

template <
	typename If,
	typename Else
>
constexpr decltype(auto)
if_impl_std_types::operator()(std::true_type, If && i, Else && e) const {
	return HBRS_MPL_FWD(i);
}

template <
	typename If,
	typename Else
>
constexpr decltype(auto)
if_impl_std_types::operator()(std::false_type, If && i, Else && e) const {
	return HBRS_MPL_FWD(e);
}

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_FN_IF_IMPL_STD_HPP
