// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#include <ocl/crc_hash.hpp>
#include <ocl/print.hpp>
#include <ocl/smart_ptr.hpp>
#include <ocl/basic_math.hpp>

/// \brief Smart pointer example.
auto main(int argc, char** argv) -> int
{
	ocl::scientific::eq_solver_two solver;
	std::cout << solver(1, 2 + 2) << std::endl; // false
	std::cout << solver(4, 2 + 2) << std::endl;					// true
	std::cout << solver(1+1, 2) << std::endl;					// true
	std::cout << solver(sqrt_two, (2 / sqrt_two)) << std::endl; // false, normally it is true, but the solver solves (2 / 2^(1/12)) first and then compares the result to 2^(1/12).

	return EXIT_SUCCESS;
}
