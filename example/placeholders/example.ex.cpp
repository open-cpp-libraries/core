// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://git.ocl.nekernel.org/core

#include <ocl/print.hpp>
#include <ocl/asio.hpp>
#include <ocl/allocator_op.hpp>
#include <boost/process.hpp>

namespace asio	  = ::boost::asio;
namespace process = ::boost::process;

/// @brief Wrap OCL in ASIO calls.
auto main(int argc, char** argv) -> int
{
	auto path = ::ocl::placeholders::find_and_replace("${compiler.name}.exe", "g++", "compiler.name");

	asio::io_context ioc;
	process::process proc(ioc, path, {"--version"}, process::v2::process_stdio{{/* in to default */}, {}, nullptr});

	proc.wait();

	ocl::asio::run<[]() { (void)0; }>(ioc);

	return EXIT_SUCCESS;
}
