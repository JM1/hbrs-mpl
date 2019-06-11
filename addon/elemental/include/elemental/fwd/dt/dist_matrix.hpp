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

#pragma once

#ifndef ELEMENTAL_FWD_DT_DIST_MATRIX_HPP
#define ELEMENTAL_FWD_DT_DIST_MATRIX_HPP

#include <elemental/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/to.hpp>
#include <El.hpp>

ELEMENTAL_NAMESPACE_BEGIN
namespace hana = boost::hana;

template<typename Ring, El::Dist Columnwise, El::Dist Rowwise, El::DistWrap Wrapping>
struct dist_matrix;
struct dist_matrix_tag;
constexpr auto make_dist_matrix = hana::make<dist_matrix_tag>;
constexpr auto to_dist_matrix = hana::to<dist_matrix_tag>;

ELEMENTAL_NAMESPACE_END

#endif // !ELEMENTAL_FWD_DT_DIST_MATRIX_HPP
