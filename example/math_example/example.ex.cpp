// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#include <ocl/crc_hash.hpp>
#include <ocl/print.hpp>
#include <ocl/smart_ptr.hpp>
#include <ocl/math_fwd.hpp>

/// \brief CAS solver example in modern C++. Operations to be implemented.
auto main(int argc, char** argv) -> int
{
	ocl::scientific::eq_solver_two solver;

	std::cout << solver(1, {ocl::scientific::add(2, 2)}) << std::endl; // false
	std::cout << solver(4, {ocl::scientific::add(2, 2)}) << std::endl; // true
	std::cout << solver(ocl::scientific::add(1, 1), {2}) << std::endl; // true

	// false, normally it is true, but the solver solves (2 / 2^(1/12)) first and then compares the result to 2^(1/12).
	std::cout << solver(sqrt_two, {ocl::scientific::div(2, sqrt_two)}) << std::endl;

	ocl::scientific::ineq_solver_two solver_ineq;
	
	std::cout << solver_ineq(ocl::scientific::div(2, sqrt_two), {ocl::scientific::div(2, sqrt_two)}) << std::endl;
	std::cout << solver_ineq(5, {ocl::scientific::div(2, sqrt_two)}) << std::endl;

	return EXIT_SUCCESS;
}
