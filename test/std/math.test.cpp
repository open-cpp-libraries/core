// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

/// @author Amlal El Mahrouss

#include <ocl/math_fwd.hpp>

#define BOOST_TEST_MODULE allocator_op
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(math_should_solve_eq)
{
	ocl::scientific::eq_solver_two solver;

	BOOST_TEST(solver(1, {ocl::scientific::add(2, 2)}) == 0);
	BOOST_TEST(solver(4, {ocl::scientific::add(2, 2)}) != 0);
	BOOST_TEST(solver(ocl::scientific::add(1, 1), {2}) == 0);
}
