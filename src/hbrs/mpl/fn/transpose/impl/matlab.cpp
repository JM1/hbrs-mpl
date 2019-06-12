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

#include <hbrs/mpl/fn/transpose.hpp>
#include <hbrs/mpl/dt/ml_matrix.hpp>

extern "C" {
	#include <matlab/cxn/transpose_m.h>
}
#undef I /* I is defined by MATLAB Coder, but also used within Boost Unit Test Framework as a template parameter. */

MATLAB_NAMESPACE_BEGIN
namespace detail {

matlab::matrix<real_T>
transpose_impl_matrix::operator()(matlab::matrix<real_T> const& a) const {
	matlab::matrix<real_T> b;
	transpose_m(&a.data(), &b.data());
	return b;
}

/* namespace detail */ }
MATLAB_NAMESPACE_END