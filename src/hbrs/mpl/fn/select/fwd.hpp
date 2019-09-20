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

#ifndef HBRS_MPL_FN_SELECT_FWD_HPP
#define HBRS_MPL_FN_SELECT_FWD_HPP

#include <hbrs/mpl/config.hpp>
#include <hbrs/mpl/dt/function/fwd.hpp>
#include <hbrs/mpl/core/implementations_of.hpp>

/* select() is like view or submatrix or subsequence but does not imply a specific memory mgmt strategy.
 * select() can return a view that references an collection but does not manage its lifetime.
 * select() can also return e.g. an subsequence or submatrix that manages its resources on its own.
 */

HBRS_MPL_NAMESPACE_BEGIN
HBRS_MPL_DEC_F2(select, select_t)
HBRS_MPL_NAMESPACE_END

#include "fwd/elemental.hpp"
#include "fwd/hbrs_mpl.hpp"
#include "fwd/matlab.hpp"

HBRS_MPL_MAP_IMPLS(select_t, HBRS_MPL_FN_SELECT_IMPLS_ELEMENTAL, HBRS_MPL_FN_SELECT_IMPLS_HBRS_MPL, HBRS_MPL_FN_SELECT_IMPLS_MATLAB)

#endif // !HBRS_MPL_FN_SELECT_FWD_HPP
