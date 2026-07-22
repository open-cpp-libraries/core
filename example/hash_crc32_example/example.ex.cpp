// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#include <ocl/crc_hash_fwd.hpp>
#include <ocl/print_fwd.hpp>
#include <ocl/option_fwd.hpp>

auto main(int argc, char** argv) -> int
{
	if (argc != 2)
	{
		ocl::io::print("Hello, World!\n"_crc32);
		return EXIT_SUCCESS;
	}

	std::hash<ocl::crc_hash_trait> hash{};

	ocl::io::enable_stdio_sync(false);
	ocl::io::print(hash.operator()<true, false>(argv[1]));

	return EXIT_SUCCESS;
}
