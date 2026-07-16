// SPDX-License-Identifier: BSL-1.0
// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#pragma once

#include <boost/math/quaternion.hpp>
#include <boost/math/special_functions.hpp>
#include <boost/math/constants/constants.hpp>
#include <cmath>

#define OCL_MATH_MODULE (202606)

namespace ocl::scientific
{

	namespace detail
	{

		inline void throw_math_error(::boost::source_location const& loc = BOOST_CURRENT_LOCATION)
		{
			::boost::throw_exception(std::runtime_error(""), loc);
		}

	} // namespace detail

	using real_type = double;

	inline const real_type add(const real_type& left, const real_type& right)
	{
		return left + right;
	}

	inline const real_type sub(const real_type& left, const real_type& right)
	{
		return left - right;
	}

	inline const real_type mul(const real_type& left, const real_type& right)
	{
		return left * right;
	}

	inline const real_type div(const real_type& left, const real_type& right)
	{
		return left / right;
	}

	inline const real_type pow(const real_type& left, const real_type& right)
	{
		return std::pow(left, right);
	}

	inline const real_type sqrt(const real_type& left, const real_type& right = 0)
	{
		return std::sqrt(left);
	}

} // namespace ocl