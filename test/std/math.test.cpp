// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

/// @author Amlal El Mahrouss

#define BOOST_TEST_MODULE math
#include <boost/test/included/unit_test.hpp>

#include <ocl/math_fwd.hpp>

BOOST_AUTO_TEST_CASE(math_should_solve_eq)
{
	// try with empty cls.
	ocl::scientific::solver::eq_solver_two solver;

	bool r1 = solver(1, {ocl::scientific::add(2, 2)}) == 0;
	BOOST_TEST(r1 == true);

	r1 = solver(4, {ocl::scientific::add(2, 2)}) == 0;
	BOOST_TEST(r1 == true);

	r1 = solver(ocl::scientific::add(1, 1), {2}) == 0;
	BOOST_TEST(r1 == true);

	// try with tags.
}

struct simple_solver : public ocl::scientific::solver::kernel_solver_tag<ocl::scientific::solver::eq_solver_two>
{
	using number_type = ocl::scientific::real_type;

	number_type operator()(const number_type& left, const number_type& right)
	{
		return left + right == ((left - right) + right);
	}

	static const bool is_formalized = true;
};

BOOST_AUTO_TEST_CASE(math_solver_example_simple)
{
	ocl::scientific::solver::chain_solver_tag<simple_solver, 
		ocl::scientific::solver::construction_solver_tag<ocl::scientific::solver::eq_solver_two>> proof;
	BOOST_TEST(proof.pre_cond_(1, 1) == 0);
}
