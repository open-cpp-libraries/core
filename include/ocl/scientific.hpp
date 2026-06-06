// SPDX-License-Identifier: BSL-1.0
// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-foss-org/core

#pragma once

#include <ocl/detail/math/config.hpp>

#ifndef zeta_apery
#define zeta_apery zeta_three
#endif

namespace ocl::scientific 
{
    
    using quaternionf = boost::math::quaternion<float>;
	using quaterniond = boost::math::quaternion<double>;

    inline auto zeta_apery_f = boost::math::zeta<float>(3.0f);
	inline auto zeta_apery_d = boost::math::zeta<double>(3.0);

} // namespace ocl::scientific
