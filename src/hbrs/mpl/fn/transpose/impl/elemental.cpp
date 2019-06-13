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
#include <hbrs/mpl/core/preprocessor.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

#define PROTO(type_spec_1, cv_qual_1, ref_decl_1)                                                                      \
	template auto transpose_impl_matrix::operator()(type_spec_1 cv_qual_1 ref_decl_1) const;
HBRS_MPL_INST_FWDREFS(PROTO, matrix<float>)
HBRS_MPL_INST_FWDREFS(PROTO, matrix<El::Complex<float>>)
HBRS_MPL_INST_FWDREFS(PROTO, matrix<double>)
HBRS_MPL_INST_FWDREFS(PROTO, matrix<El::Complex<double>>)
#undef PROTO

#define PROTO(type_spec_1, cv_qual_1, ref_decl_1)                                                                      \
	template auto transpose_impl_dist_matrix::operator()(type_spec_1 cv_qual_1 ref_decl_1) const;
HBRS_MPL_INST_FWDREFS(PROTO, dist_matrix<float>)
HBRS_MPL_INST_FWDREFS(PROTO, dist_matrix<El::Complex<float>>)
HBRS_MPL_INST_FWDREFS(PROTO, dist_matrix<double>)
HBRS_MPL_INST_FWDREFS(PROTO, dist_matrix<El::Complex<double>>)
#undef PROTO

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END