// Copyright 2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-org/core

#ifndef OCL_CORE_IO
#define OCL_CORE_IO

#include <ocl/detail/config.hpp>

#ifndef OCL_FREESTANDING
#define console_io_out std::cout
#define console_io_in  std::cin

#include <iostream>
#else
#define console_io_out ::ocl::io::void_cout
#define console_io_in  ::ocl::io::void_cin

#warning The OCL doesnt define IO streams in freestanding mode.

namespace ocl::io
{

	class void_stream final
	{
		void_stream()  = default;
		~void_stream() = default;

		void_stream& operator<<(...) = delete;
		void_stream& operator>>(...) = delete;
	}

	inline void_stream void_cout;
	inline void_stream void_cin;

} // namespace ocl::io

#endif
#endif
