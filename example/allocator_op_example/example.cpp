// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-foss-org/core

#include <ocl/print.hpp>
#include <ocl/allocator_op.hpp>
#include <coroutine>
#include <future>

/// \brief Allocation of ints example.
int task()
{
	ocl::allocator<int> int_alloc;
	auto				foo = int_alloc.construct_array<1>();

	*foo = 109000;
	ocl::io::println(*foo);

	return EXIT_SUCCESS;
}

int main()
{
	auto ret  = std::async(std::launch::deferred, task);
	auto ret2 = std::async(std::launch::deferred, task);
	auto ret3 = std::async(std::launch::deferred, task);

	ret.get();
	ret2.get();
	ret3.get();
}
