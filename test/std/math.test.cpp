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
											  ocl::scientific::solver::construction_solver_tag<ocl::scientific::solver::eq_solver_two>>
		proof;
	BOOST_TEST(proof.pre_cond_(1, 1) == 0);
}

BOOST_AUTO_TEST_CASE(math_add)
{
	BOOST_TEST(ocl::scientific::add(2.0, 3.0) == 5.0);
	BOOST_TEST(ocl::scientific::add(0.0, 0.0) == 0.0);
	BOOST_TEST(ocl::scientific::add(-1.0, 1.0) == 0.0);
}

BOOST_AUTO_TEST_CASE(math_sub)
{
	BOOST_TEST(ocl::scientific::sub(5.0, 3.0) == 2.0);
	BOOST_TEST(ocl::scientific::sub(0.0, 0.0) == 0.0);
	BOOST_TEST(ocl::scientific::sub(1.0, -1.0) == 2.0);
}

BOOST_AUTO_TEST_CASE(math_mul)
{
	BOOST_TEST(ocl::scientific::mul(3.0, 4.0) == 12.0);
	BOOST_TEST(ocl::scientific::mul(0.0, 99.0) == 0.0);
	BOOST_TEST(ocl::scientific::mul(-2.0, 3.0) == -6.0);
}

BOOST_AUTO_TEST_CASE(math_div)
{
	BOOST_TEST(ocl::scientific::div(10.0, 2.0) == 5.0);
	BOOST_TEST(ocl::scientific::div(0.0, 1.0) == 0.0);
	BOOST_TEST(ocl::scientific::div(-6.0, 3.0) == -2.0);
}

BOOST_AUTO_TEST_CASE(math_pow)
{
	BOOST_TEST(ocl::scientific::pow(2.0, 10.0) == 1024.0);
	BOOST_TEST(ocl::scientific::pow(5.0, 0.0) == 1.0);
	BOOST_TEST(ocl::scientific::pow(3.0, 3.0) == 27.0);
}

BOOST_AUTO_TEST_CASE(math_sqrt)
{
	BOOST_TEST(ocl::scientific::sqrt(4.0) == 2.0);
	BOOST_TEST(ocl::scientific::sqrt(0.0) == 0.0);
	BOOST_TEST(ocl::scientific::sqrt(9.0) == 3.0);
}

BOOST_AUTO_TEST_CASE(math_quaternion_norm_euclidean)
{
	ocl::scientific::quaternionf q(3.0f, 0.0f, 0.0f, 0.0f);
	float n = ocl::scientific::norm<float, ocl::scientific::space_type::euclidean>(q);
	BOOST_TEST(n == 3.0f);

	ocl::scientific::quaternionf q2(0.0f, 0.0f, 0.0f, 0.0f);
	float n2 = ocl::scientific::norm<float, ocl::scientific::space_type::euclidean>(q2);
	BOOST_TEST(n2 == 0.0f);
}

BOOST_AUTO_TEST_CASE(math_quaternion_norm_minkowski)
{
	ocl::scientific::quaternionf q(2.0f, 0.0f, 0.0f, 0.0f);
	float n = ocl::scientific::norm<float, ocl::scientific::space_type::minkowski>(q);
	BOOST_TEST(n == 4.0f);
}

BOOST_AUTO_TEST_CASE(math_constants_range)
{
	BOOST_TEST(pi > 3.14 && pi < 3.15);
	BOOST_TEST(euler_num > 2.71 && euler_num < 2.72);
	BOOST_TEST(golden_ratio > 1.61 && golden_ratio < 1.62);
	BOOST_TEST(sqrt_two > 1.41 && sqrt_two < 1.42);
	BOOST_TEST(catalan > 0.91 && catalan < 0.92);
}

BOOST_AUTO_TEST_CASE(math_ineq_solver)
{
	ocl::scientific::solver::ineq_solver_two solver;
	BOOST_TEST(solver(1, {2}) == 0);
	BOOST_TEST(solver(5, {3}) == 0);
}

BOOST_AUTO_TEST_CASE(math_apery_constant)
{
	BOOST_TEST(ocl::scientific::zeta_apery_d > 1.20 && ocl::scientific::zeta_apery_d < 1.21);
	BOOST_TEST((double)ocl::scientific::zeta_apery_f > 1.20 && (double)ocl::scientific::zeta_apery_f < 1.21);
}
