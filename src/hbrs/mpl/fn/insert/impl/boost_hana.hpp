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

#ifndef HBRS_MPL_FN_INSERT_IMPL_BOOST_HANA_HPP
#define HBRS_MPL_FN_INSERT_IMPL_BOOST_HANA_HPP

#include "../fwd/boost_hana.hpp"

#include <hbrs/mpl/core/preprocessor.hpp>
#include <boost/hana/insert.hpp>
#include <boost/hana/first.hpp>
#include <boost/hana/second.hpp>
#include <boost/hana/pair.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

template <
	typename Map,
	typename Pair, 
	typename std::enable_if_t< 
		std::is_same< hana::tag_of_t<Map>, hana::map_tag >::value &&
		(
			std::is_same< hana::tag_of_t<Pair>, hana::pair_tag           >::value ||
			std::is_same< hana::tag_of_t<Pair>, hana::ext::std::pair_tag >::value
		) &&
		is_core_applicable_trait<
			hana::insert_impl<hana::tag_of_t<Map>>, Map&&, Pair&&
		>::value
	>*
>
constexpr decltype(auto)
insert_impl_hana_map::operator()(Map && m, Pair && p) const {
	return hana::insert(HBRS_MPL_FWD(m), HBRS_MPL_FWD(p));
}

template <
	typename Map,
	typename Key,
	typename Value,
	typename std::enable_if_t< 
		std::is_same< hana::tag_of_t<Map>, hana::map_tag >::value &&
		hana::Comparable<Key&&>::value
	>*
>
constexpr decltype(auto)
insert_impl_hana_map::operator()(Map && m, Key && k, Value && v) const {
	return hana::insert(HBRS_MPL_FWD(m), hana::make_pair(HBRS_MPL_FWD(k), HBRS_MPL_FWD(v)));
}

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_FN_INSERT_IMPL_BOOST_HANA_HPP
