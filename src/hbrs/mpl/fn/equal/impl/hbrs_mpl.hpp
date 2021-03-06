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

#ifndef HBRS_MPL_FN_EQUAL_IMPL_HBRS_MPL_HPP
#define HBRS_MPL_FN_EQUAL_IMPL_HBRS_MPL_HPP

#include "../fwd/hbrs_mpl.hpp"

#include <hbrs/mpl/detail/function_object.hpp>
#include <hbrs/mpl/dt/matrix_size.hpp>
#include <hbrs/mpl/dt/matrix_index.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

HBRS_MPL_DEF_FO_TRY_OPERATOR(equal_impl_matrix_size, matrix_size_tag, HBRS_MPL_OPERATOR_EQUAL, equal)
HBRS_MPL_DEF_FO_TRY_OPERATOR(equal_impl_matrix_index, matrix_index_tag, HBRS_MPL_OPERATOR_EQUAL, equal)

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_FN_EQUAL_IMPL_HBRS_MPL_HPP
