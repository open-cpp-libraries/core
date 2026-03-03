// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-foss-org/core

#ifndef OCL_CORE_ASIO
#define OCL_CORE_ASIO

#ifdef OCL_CORE_INCLUDE_ALL_ASIO

#include <boost/asio.hpp>

#else

#include <boost/asio/co_spawn.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>

#endif

#endif
