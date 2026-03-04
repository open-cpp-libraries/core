// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://git.ocl.nekernel.org/core

#include <ocl/print.hpp>
#include <ocl/asio.hpp>
#include <ocl/allocator_op.hpp>
#include <future>

constexpr long int operator ""_USD(long double n)
{
  return n * 1000.0;
}

/// @brief Wrap OCL in ASIO calls.
int main()
{
	boost::asio::io_context ioc{1};
	auto					spawn_strand = boost::asio::make_strand(ioc);

  boost::asio::co_spawn(spawn_strand, [&]() -> boost::asio::awaitable<void> {
      ocl::allocator<int> int_alloc;
      auto				balance = int_alloc.construct_array<1>();

      *balance = operator ""_USD(150);
      ocl::io::println("USD: ", *balance);
      co_return;
  }, boost::asio::detached);

  ocl::asio::run<[]() { std::terminate(); }>(ioc);

  return EXIT_SUCCESS;
}
