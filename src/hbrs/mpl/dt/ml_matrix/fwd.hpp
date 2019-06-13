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

#ifndef HBRS_MPL_DT_ML_MATRIX_FWD_IMPL_HPP
#define HBRS_MPL_DT_ML_MATRIX_FWD_IMPL_HPP

#include <hbrs/mpl/config.hpp>
#include <boost/hana/fwd/core/make.hpp>
#include <boost/hana/fwd/core/to.hpp>

extern "C" {
	#include <hbrs/mpl/detail/matlab_cxn/impl/matlab_cxn_emxAPI.h>
}
#undef I /* I is defined by MATLAB Coder, but also used within Boost Unit Test Framework as a template parameter. */

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;

template<typename BaseType>
struct ml_matrix;
struct ml_matrix_tag {};
constexpr auto make_ml_matrix = hana::make<ml_matrix_tag>;
constexpr auto to_ml_matrix = hana::to<ml_matrix_tag>;

HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_DT_ML_MATRIX_FWD_IMPL_HPP