// SPDX-License-Identifier: BSL-1.0
// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#pragma once

#include <ocl/detail/math/config.hpp>

/// @brief Scientific file for Number Theory, and Geometry.

namespace ocl::scientific 
{
    
    using quaternionf = ::boost::math::quaternion<float>;
	using quaterniond = ::boost::math::quaternion<double>;

    /// @brief The value of the Riemann zeta function at 3, also known as Apery's constant.
    inline auto zeta_apery_f = ::boost::math::zeta<float>(3.0f);
	inline auto zeta_apery_d = ::boost::math::zeta<double>(3.0);

    /// @brief Enumeration to specify the type of space for quaternion norm computation.
    enum class space_type : int32_t
	{
		invalid = 1,
		euclidean,
		minkowski,
		count = 2,
	};

    /// @brief Computes the norm of a quaternion in the specified space.
	/// @tparam T The type of the quaternion components (e.g., float, double).
	/// @tparam S The type of space (euclidean or minkowski) to compute the norm in.
	/// @param q The quaternion for which to compute the norm.
	/// @return The norm of the quaternion in the specified space.
	template <typename T, space_type S>
	inline T norm(::boost::math::quaternion<T> const& q)
	{
		switch (S)
		{
		case space_type::euclidean:
			return ::boost::math::abs(q);
		case space_type::minkowski:
			return ::boost::math::norm(q);
		}

        ::boost::throw_exception(std::runtime_error("Invalid type"), BOOST_CURRENT_LOCATION);
    }

} // namespace ocl::scientific

#ifndef zeta_apery
#define zeta_apery zeta_three
#endif
