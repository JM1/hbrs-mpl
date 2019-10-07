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

#ifndef HBRS_MPL_FN_DMD_FWD_HPP
#define HBRS_MPL_FN_DMD_FWD_HPP

#include <hbrs/mpl/config.hpp>
#include <hbrs/mpl/dt/function/fwd.hpp>
#include <hbrs/mpl/core/implementations_of.hpp>

HBRS_MPL_NAMESPACE_BEGIN
HBRS_MPL_DEC_F3(dmd, dmd_t)
HBRS_MPL_NAMESPACE_END

#include "fwd/elemental.hpp"
#include "fwd/matlab.hpp"

//TODO: (a) Describe input matrices X1 and X2 and their properties (e.g. rows of X correspond to variables and columns correspond to observations ) or
//      (b) Wrap input matrix in wrapper data structure, which describes meanings of columns and rows
HBRS_MPL_MAP_IMPLS(dmd_t, HBRS_MPL_FN_DMD_IMPLS_ELEMENTAL, HBRS_MPL_FN_DMD_IMPLS_MATLAB)

#endif // !HBRS_MPL_FN_DMD_FWD_HPP
