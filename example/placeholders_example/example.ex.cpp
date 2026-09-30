// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://git.ocl.nekernel.org/core

#define OCL_USE_TPROC 1
#include <ocl/print_fwd.hpp>
#include <ocl/asio_fwd.hpp>
#include <ocl/allocator_fwd.hpp>
#include <boost/process.hpp>

namespace asio	  = ::boost::asio;
namespace process = ::boost::process;

/// @brief Wrap OCL in ASIO calls.
auto main(int argc, char** argv) -> int

{
	::ocl::tproc::crope* out_path	   = new ::ocl::tproc::crope("/usr");

	::ocl::placeholders::find_and_replace("/bin/",
										  out_path, "x86_64-linux-gnu-g++");

	::asio::io_context ioc;
	::process::process proc(ioc, out_path->to_string(), {"--version"}, process::v2::process_stdio{{/* in to default */}, {}, nullptr});

	proc.wait();

	::ocl::asio::run<[]() { (void)0; }>(ioc);

	return EXIT_SUCCESS;
}
