// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://git.ocl.nekernel.org/core

#include <ocl/print.hpp>
#include <ocl/asio.hpp>
#include <ocl/allocator_op.hpp>
#include <future>

constexpr long int operator""_USD(long double n)
{
	return n * 1000.0;
}

/// @brief Wrap OCL in ASIO calls.
int main()
{
	boost::asio::io_context ioc{1};
	auto					spawn_strand = boost::asio::make_strand(ioc);

	ocl::allocator<int> int_alloc;

	boost::asio::co_spawn(spawn_strand, [&int_alloc]() -> boost::asio::awaitable<void> {
      auto				balance = int_alloc.construct_array<1>();

      *balance = operator ""_USD(150);
      ocl::io::println("Balance USD: ", *balance);
      co_return; }, boost::asio::detached);

	auto balances = int_alloc.construct_array<5>();

	ocl::asio::run<[]() { (void)0; }>(ioc);

	return EXIT_SUCCESS;
}
