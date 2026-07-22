// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#include <ocl/crc_hash_fwd.hpp>
#include <ocl/print_fwd.hpp>
#include <ocl/option_fwd.hpp>

struct invalid_callable final
{
	explicit invalid_callable() = default;
	void operator()(const char* reason)
	{
		ocl::detail::throw_runtime_error();
	}
};

/// \brief Option Monad example
auto main(int argc, char** argv) -> int
{
	ocl::option opt{ocl::eval_eq(nullptr, nullptr)};
	opt.expect("option::incorrect");

	ocl::option opt2{ocl::eval_eq(argv, nullptr)};
	opt2.expect<invalid_callable>("option::incorrect");

	return 0;
}
