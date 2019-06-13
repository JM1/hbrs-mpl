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

#ifndef HBRS_MPL_FN_APPLY_AT_HPP
#define HBRS_MPL_FN_APPLY_AT_HPP

#include <hbrs/mpl/fn/apply_at/fwd.hpp>
#include <hbrs/mpl/dt/function.hpp>

HBRS_MPL_NAMESPACE_BEGIN
HBRS_MPL_DEF_F3(apply_at, apply_at_t)
HBRS_MPL_NAMESPACE_END

#include <hbrs/mpl/fuse/fn/apply_at.hpp>
#include <hbrs/mpl/core/implementations_of.hpp>
HBRS_MPL_MAP_IMPLS(apply_at_t, HBRS_MPL_FUSE_FN_APPLY_AT_IMPLS)

#endif // !HBRS_MPL_FN_APPLY_AT_HPP