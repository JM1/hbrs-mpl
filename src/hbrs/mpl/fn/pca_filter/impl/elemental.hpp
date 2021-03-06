/* Copyright (c) 2016-2020 Jakob Meng, <jakobmeng@web.de>
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

#ifndef HBRS_MPL_FN_PCA_FILTER_IMPL_ELEMENTAL_HPP
#define HBRS_MPL_FN_PCA_FILTER_IMPL_ELEMENTAL_HPP

#include "../fwd/elemental.hpp"
#ifdef HBRS_MPL_ENABLE_ELEMENTAL

#include <hbrs/mpl/core/preprocessor.hpp>
#include <hbrs/mpl/dt/el_matrix.hpp>
#include <hbrs/mpl/dt/el_dist_matrix.hpp>
#include <hbrs/mpl/dt/matrix_index.hpp>
#include <hbrs/mpl/dt/pca_control.hpp>
#include <hbrs/mpl/dt/pca_filter_control.hpp>
#include <hbrs/mpl/dt/pca_filter_result.hpp>

#include <hbrs/mpl/fn/pca.hpp>
#include <hbrs/mpl/fn/at.hpp>
#include <hbrs/mpl/fn/size.hpp>
#include <hbrs/mpl/fn/m.hpp>
#include <hbrs/mpl/fn/n.hpp>
#include <hbrs/mpl/fn/multiply.hpp>
#include <hbrs/mpl/fn/transpose.hpp>
#include <hbrs/mpl/fn/plus.hpp>
#include <hbrs/mpl/fn/equal.hpp>
#include <hbrs/mpl/fn/expand.hpp>

#include <hbrs/mpl/detail/log.hpp>

#include <vector>
#include <boost/numeric/conversion/cast.hpp>
#include <boost/assert.hpp>
#include <algorithm>

HBRS_MPL_NAMESPACE_BEGIN
namespace hana = boost::hana;
namespace detail {

template <
	typename Matrix,
	typename std::enable_if_t< 
		std::is_same_v< hana::tag_of_t<Matrix>, el_matrix_tag > ||
		std::is_same_v< hana::tag_of_t<Matrix>, el_dist_matrix_tag >
	>*
>
auto
pca_filter_impl_el_matrix::operator()(
	Matrix && a,
	std::function<bool(El::Int)> const& keep,
	pca_filter_control<pca_control<bool,bool,bool>,bool> const& ctrl
) const {
	HBRS_MPL_LOG_TRIVIAL(debug) << "pca_filter:elemental:begin";
	HBRS_MPL_LOG_TRIVIAL(trace) << "A:" << loggable{a};
	
	auto a_sz = (*size)(a);
	auto a_m = (*m)(a_sz);
	auto a_n = (*n)(a_sz);
	auto DOF = a_m - (ctrl.pca_control().center() ? 1 : 0);
	auto keep_sz = (DOF<a_n && ctrl.pca_control().economy()) ? DOF : std::min(a_m, a_n);
	auto latent_sz = (DOF<a_n && ctrl.pca_control().economy()) ? DOF : a_n;
	
	auto rslt = (*pca)(HBRS_MPL_FWD(a), ctrl.pca_control());
	
	decltype(auto) coeff  =  (*at)(rslt, pca_coeff{});
	decltype(auto) score  =  (*at)(rslt, pca_score{});
	decltype(auto) latent = (*at)(rslt, pca_latent{});
	decltype(auto) mean   =   (*at)(rslt, pca_mean{});
	
	BOOST_ASSERT((*equal)(size(latent), latent_sz));
	
	// size(keep) <= n(size(score))
	for (El::Int i = 0; i < (*n)(size(score)); ++i) {
		if ((i >= keep_sz) || (keep(i) == false)) {
			auto column = score.data()(El::ALL, i);
			El::Zero(column);
		}
	}
	
	auto centered = (*multiply)(score, transpose(coeff));
	BOOST_ASSERT((*equal)(a_sz, size(centered)));
	
	auto data = ctrl.pca_control().center() && !ctrl.keep_centered()
		? (*plus)(centered, expand(mean, size(centered)))
		: std::move(centered);
	BOOST_ASSERT((*equal)(size(data), a_sz));
	
	HBRS_MPL_LOG_TRIVIAL(trace) << "data:" << loggable{data};
	HBRS_MPL_LOG_TRIVIAL(trace) << "latent:" << loggable{latent};
	HBRS_MPL_LOG_TRIVIAL(debug) << "pca_filter:elemental:end";
	return make_pca_filter_result(data, latent);
}

template <
	typename Matrix,
	typename std::enable_if_t< 
		std::is_same_v< hana::tag_of_t<Matrix>, el_matrix_tag > ||
		std::is_same_v< hana::tag_of_t<Matrix>, el_dist_matrix_tag >
	>*
>
auto
pca_filter_impl_el_matrix::operator()(
	Matrix && a,
	std::vector<bool> const& keep,
	pca_filter_control<pca_control<bool,bool,bool>,bool> const& ctrl
) const {
	auto a_sz = (*size)(a);
	auto a_m = (*m)(a_sz);
	auto a_n = (*n)(a_sz);
	
	auto DOF = a_m - (ctrl.pca_control().center() ? 1 : 0);
	BOOST_ASSERT(keep.size() == (unsigned)((DOF<a_n && ctrl.pca_control().economy()) ? DOF : std::min(a_m, a_n)));
	
	return (*this)(
		HBRS_MPL_FWD(a),
		[&keep](El::Int i) {
			BOOST_ASSERT(i < boost::numeric_cast<El::Int>(keep.size()));
			return keep.at(static_cast<std::size_t>(i));
		},
		ctrl
	);
}

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_ENABLE_ELEMENTAL
#endif // !HBRS_MPL_FN_PCA_FILTER_IMPL_ELEMENTAL_HPP
