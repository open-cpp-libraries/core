// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#include <ocl/crc_hash_fwd.hpp>
#include <ocl/print_fwd.hpp>
#include <ocl/smart_ptr.hpp>

/// \brief Smart pointer example.
auto main(int argc, char** argv) -> int
{
	ocl::shared_ptr<std::ostream> smart = ocl::delete_ptr(&std::cout);
	*smart << "hello, world\n";

	ocl::smart_ptr::tracked_ptr<int> tracked = ocl::smart_ptr::make_tracked<int>(10);
	*smart << *tracked << "\n";

	return EXIT_SUCCESS;
}
