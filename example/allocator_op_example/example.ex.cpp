// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#include <ocl/print_fwd.hpp>
#include <ocl/allocator_fwd.hpp>
#include <coroutine>
#include <future>

/// \brief Allocation of ints example.
struct task final
{
	int operator()()
	{
		ocl::allocator<int> int_alloc;
		auto				foo = int_alloc.construct_array<1>();

		*foo = 109000;
		ocl::io::println(*foo);

		return EXIT_SUCCESS;
	}
};

auto main(int argc, char** argv) -> int
{
	auto ret  = std::async(std::launch::deferred, task{});
	auto ret2 = std::async(std::launch::deferred, task{});
	auto ret3 = std::async(std::launch::deferred, task{});

	ret.get();
	ret2.get();
	ret3.get();
}
