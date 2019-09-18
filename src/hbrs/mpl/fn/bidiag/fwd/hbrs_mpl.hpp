/* Copyright (c) 2019 Abdullah Güntepe, <abdullah@guentepe.com>
 * Copyright (c) 2019 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_FN_BIDIAG_FWD_HBRS_MPL_HPP
#define HBRS_MPL_FN_BIDIAG_FWD_HBRS_MPL_HPP

#include <hbrs/mpl/config.hpp>
#include <hbrs/mpl/core/preprocessor.hpp>
#include <hbrs/mpl/dt/storage_order/fwd.hpp>
#include <hbrs/mpl/dt/rtsam/fwd.hpp>
#include <cmath>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

struct bidiag_impl_householder {
	template<
		typename Ring,
		storage_order Order
	>
	decltype(auto)
	operator()(rtsam<Ring,Order> const& A, int econ);
private:
	template<
		typename Ring,
		storage_order Order
	>
	rtsam<Ring,Order>
	identity(std::size_t const size);
};
/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#define HBRS_MPL_FN_BIDIAG_IMPLS_HBRS_MPL boost::hana::make_tuple(                                                     \
        hbrs::mpl::detail::bidiag_impl_householder{}                                                                   \
	)

#endif // !HBRS_MPL_FN_BIDIAG_FWD_HBRS_MPL_HPP
