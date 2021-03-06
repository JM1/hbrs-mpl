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

#ifndef HBRS_MPL_FN_DIVIDE_IMPL_ELEMENTAL_HPP
#define HBRS_MPL_FN_DIVIDE_IMPL_ELEMENTAL_HPP

#include "../fwd/elemental.hpp"
#ifdef HBRS_MPL_ENABLE_ELEMENTAL

#include <hbrs/mpl/dt/el_vector.hpp>
#include <hbrs/mpl/dt/el_dist_vector.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

template <
	typename Vector,
	typename Scalar,
	typename std::enable_if_t< 
		(
			std::is_same< hana::tag_of_t<Vector>, el_column_vector_tag >::value ||
			std::is_same< hana::tag_of_t<Vector>, el_row_vector_tag >::value
		) &&
		std::is_arithmetic<Scalar>::value
	>*
>
auto
divide_impl_el_vector_scalar::operator()(Vector v, Scalar const& b) const {
	//TODO: Move to member function? Or replace with transform call?
	typedef decltype(v.at(0)) Ring;
	typedef std::decay_t<Ring> _Ring_;
	El::Scale(_Ring_(1)/b, v.data());
	return v;
}

template <
	typename Ring, El::Dist Columnwise, El::Dist Rowwise, El::DistWrap Wrapping,
	typename Scalar,
	typename std::enable_if_t<
		std::is_arithmetic_v<Scalar>
	>*
>
auto
divide_impl_el_dist_vector_scalar::operator()(
	el_dist_column_vector<Ring, Columnwise, Rowwise, Wrapping> && v,
	Scalar const& b
) const {
	//TODO: Move to member function? Or replace with transform call?
	typedef std::decay_t<Ring> _Ring_;
	El::Scale(_Ring_(1)/b, v.data());
	return HBRS_MPL_FWD(v);
}

template <
	typename Ring,
	typename std::enable_if_t< 
		!std::is_const< Ring >::value
	>*
>
auto
divide_impl_el_matrix_scalar::operator()(el_matrix<Ring> a, Ring const& b) const {
	El::Scale(Ring(1)/b, a.data());
	return a;
}

template <
	typename Scalar,
	typename std::enable_if_t<
		std::is_arithmetic_v<Scalar>
	>*
>
auto
divide_impl_el_complex_scalar::operator()(El::Complex<Scalar> const& a, Scalar const& b) const {
	return a/b;
}

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_ENABLE_ELEMENTAL
#endif // !HBRS_MPL_FN_DIVIDE_IMPL_ELEMENTAL_HPP
