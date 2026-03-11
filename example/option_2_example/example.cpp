// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-foss-org/core

#include <ocl/crc_hash.hpp>
#include <ocl/print.hpp>
#include <ocl/option.hpp>

struct invalid_callable
{
	explicit invalid_callable() = default;
	void operator()(const char* reason)
	{
		ocl::detail::throw_runtime_error();
	}
};

/// \brief Option Monad example
int main(int argc, char** argv)
{
	ocl::option opt{ocl::eval_eq(nullptr, nullptr)};
	opt.expect("option::incorrect");

	opt = ocl::option{ocl::eval_eq(argv, nullptr)};
	opt.expect<invalid_callable>("option::incorrect");

	return EXIT_SUCCESS;
}
