// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-foss-org/core

#ifndef OCL_CORE_PRINT
#define OCL_CORE_PRINT

#include <ocl/detail/config.hpp>
#include <ocl/io.hpp>

#ifdef OCL_HAS_PRINT_LIBRARY
#include <print>
#warning !! OCL.Core: starting from C++23, please use <print> rather than print.hpp. !!
#endif

namespace ocl::io
{

	template <typename T>
	inline void print(T fmt) noexcept
	{
		console_io_out << fmt;
	}

	inline void print() noexcept
	{
		extern void lf() noexcept;
		lf();
	}

	template <typename... Args>
	inline void print(Args... fmt) noexcept
	{
		print(fmt...);
		print();
	}

	template <typename T, typename... Args>
	inline void print(T fmt, Args... other) noexcept
	{
		console_io_out << fmt;
		print(other...);
	}

	namespace detail
	{
		inline bool is_stdio_sync = true;

		using io_error = std::runtime_error;

		inline void throw_option_invalid_type_error(const boost::source_location& loc = BOOST_CURRENT_LOCATION)
		{
			throw io_error(loc.to_string());
		}
	} // namespace detail

	inline void enable_stdio_sync(const bool& enable) noexcept
	{
		detail::is_stdio_sync = enable;
		console_io_out.sync_with_stdio(detail::is_stdio_sync);
	}

	inline const bool& is_stdio_sync()
	{
		return detail::is_stdio_sync;
	}

	inline void lf() noexcept
	{
#ifdef OCL_USE_CRLF_ENDINGS
		if (!is_stdio_sync())
			print("\r\n");
#else
		if (!is_stdio_sync())
			print("\n");
#endif

		if (is_stdio_sync())
			console_io_out << std::endl;
	}

	template <typename... T>
	inline void println(T... fmt) noexcept
	{
		print(fmt...);
		lf();
	}

} // namespace ocl::io

#endif // ifndef OCL_CORE_PRINT
