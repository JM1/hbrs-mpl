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

#include <hbrs/mpl/fn/zip.hpp>

ELEMENTAL_NAMESPACE_BEGIN
namespace detail {

template auto zip_impl_smc_matrix_integer_range::operator()(mpl::smc<matrix<float>               , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smc_matrix_integer_range::operator()(mpl::smc<matrix<El::Complex<float>>  , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smc_matrix_integer_range::operator()(mpl::smc<matrix<double>              , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smc_matrix_integer_range::operator()(mpl::smc<matrix<El::Complex<double>> , El::Int>, boost::integer_range<El::Int>) const;

template auto zip_impl_smc_matrix_integer_range::operator()(mpl::smc<matrix<float>              const& , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smc_matrix_integer_range::operator()(mpl::smc<matrix<El::Complex<float>> const& , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smc_matrix_integer_range::operator()(mpl::smc<matrix<double>             const& , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smc_matrix_integer_range::operator()(mpl::smc<matrix<El::Complex<double>>const& , El::Int>, boost::integer_range<El::Int>) const;

template auto zip_impl_smr_matrix_integer_range::operator()(mpl::smr<matrix<float>               , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smr_matrix_integer_range::operator()(mpl::smr<matrix<El::Complex<float>>  , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smr_matrix_integer_range::operator()(mpl::smr<matrix<double>              , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smr_matrix_integer_range::operator()(mpl::smr<matrix<El::Complex<double>> , El::Int>, boost::integer_range<El::Int>) const;

template auto zip_impl_smr_matrix_integer_range::operator()(mpl::smr<matrix<float>              const& , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smr_matrix_integer_range::operator()(mpl::smr<matrix<El::Complex<float>> const& , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smr_matrix_integer_range::operator()(mpl::smr<matrix<double>             const& , El::Int>, boost::integer_range<El::Int>) const;
template auto zip_impl_smr_matrix_integer_range::operator()(mpl::smr<matrix<El::Complex<double>>const& , El::Int>, boost::integer_range<El::Int>) const;

/* namespace detail */ }
ELEMENTAL_NAMESPACE_END