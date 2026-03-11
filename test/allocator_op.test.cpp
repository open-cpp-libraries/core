// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-foss-org/core

/// @author Amlal El Mahrouss

#include <ocl/allocator_op.hpp>

#define BOOST_TEST_MODULE allocator_op
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(allocator_should_succeed)
{
	auto ptr = ocl::allocator<int>{}.construct_array<10>();
	int* arr = ptr.get();
	BOOST_TEST(arr != nullptr);

	for (auto i{0ul}; i < 10; ++i)
	{
		*(arr + i) = 10;
		BOOST_TEST(*(arr + i) == 10);
	}
}
