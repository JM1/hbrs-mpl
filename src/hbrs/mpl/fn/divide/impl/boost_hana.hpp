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

#ifndef HBRS_MPL_FN_DIVIDE_IMPL_BOOST_HANA_HPP
#define HBRS_MPL_FN_DIVIDE_IMPL_BOOST_HANA_HPP

#include "../fwd/boost_hana.hpp"

#include <hbrs/mpl/detail/operators/impl/boost_hana.hpp>
#include <boost/hana/div.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {
HBRS_MPL_DEFINE_BOOST_HANA_INTEGRAL_CONSTANT_OPERATOR_IMPL_ARITY2(divide, HBRS_MPL_OPERATOR_DIVIDE, div)
/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_FN_DIVIDE_IMPL_BOOST_HANA_HPP
