// Copyright 2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-org/core

#include <ocl/print.hpp>
#include <ocl/allocator_op.hpp>

/// \brief Allocation of ints example.
int main()
{
	ocl::allocator<int> int_alloc;
	auto				foo = int_alloc.construct_array<1>();

	*foo = 67;
    ocl::io::print(*foo);

	return EXIT_SUCCESS;
}
