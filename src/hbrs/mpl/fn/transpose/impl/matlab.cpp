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

#include "matlab.hpp"
#ifdef HBRS_MPL_ENABLE_MATLAB

#include <hbrs/mpl/dt/ml_matrix.hpp>
#include <hbrs/mpl/dt/ml_vector.hpp>

extern "C" {
	#include <hbrs/mpl/detail/matlab_cxn/impl/transpose_md.h>
}
#undef I /* I is defined by MATLAB Coder, but also used within Boost Unit Test Framework as a template parameter. */

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

HBRS_MPL_API
ml_matrix<real_T>
transpose_impl_ml_matrix::operator()(ml_matrix<real_T> const& a) const {
	ml_matrix<real_T> b;
	transpose_md(&a.data(), &b.data());
	return b;
}

HBRS_MPL_API
ml_row_vector<real_T>
transpose_impl_ml_vector::operator()(ml_column_vector<real_T> const& v) const {
	return {v};
}

HBRS_MPL_API
ml_column_vector<real_T>
transpose_impl_ml_vector::operator()(ml_row_vector<real_T> const& v) const {
	return {v};
}

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_ENABLE_MATLAB
