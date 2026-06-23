// SPDX-License-Identifier: BSL-1.0
// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#ifndef OCL_CORE_ASIO
#define OCL_CORE_ASIO

#ifdef OCL_CORE_INCLUDE_ALL_ASIO

#include <boost/asio.hpp>

#else

#include <boost/asio/strand.hpp>
#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <ocl/print.hpp>

#endif

/// @brief ASIO file for OCL support.

namespace ocl::asio
{

	using io_context_type = boost::asio::io_context;
	using run_pred_type	  = void (*)();

	template <class IOCPred>
	inline void run(io_context_type& ioc)
	{
		try
		{
			ioc.run();
		}
		catch (const std::exception& e)
		{
			IOCPred{}();
			ocl::io::println(e.what());
		}
	}

	template <run_pred_type IOCFn>
	inline void run(io_context_type& ioc)
	{
		try
		{
			ioc.run();
		}
		catch (const std::exception& e)
		{
			IOCFn();
			ocl::io::println(e.what());
		}
	}

} // namespace ocl::asio

#endif
