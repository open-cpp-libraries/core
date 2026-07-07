// SPDX-License-Identifier: BSL-1.0
// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#pragma once

#include <boost/math/quaternion.hpp>
#include <boost/math/special_functions.hpp>
#include <boost/math/constants/constants.hpp>

#define OCL_MATH_MODULE (202606)

namespace ocl
{

	namespace detail
	{

		inline void throw_math_error(::boost::source_location const& loc = BOOST_CURRENT_LOCATION)
		{
			::boost::throw_exception(std::runtime_error(""), loc);
		}

	} // namespace detail

} // namespace ocl