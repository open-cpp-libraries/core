// SPDX-License-Identifier: BSL-1.0
// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#pragma once

#include <ocl/detail/math/config.hpp>
#include <ocl/equiv.hpp>
#include <ocl/option.hpp>
#include <ocl/scientific.hpp>
#include <complex>

/// @todo To be defined in a final design

#define Im(x)
#define Re(x)
#define Q(x)
#define P(x)

#define pi
#define euler_num
#define euler_masch
#define apery zeta_apery
#define golden_ratio
#define sqrt_two
#define gelfond_schneider
#define catalan

namespace ocl::scientific 
{

    class ode_solver;
    class nth_deriv_solver;
    class nth_int_solver;
    class alg_solver;

    struct natural_type;
    struct natural_plus_type;
    struct real_type;
    struct properties;

}
