// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

/// @brief Checks if the test fails with the expected value.
/// @author Amlal El Mahrouss

#include <ocl/option.hpp>

#define BOOST_TEST_MODULE option
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(option_should_fail)
{
	ocl::option opt(ocl::eval_false());
	BOOST_CHECK_THROW(opt.expect(""), std::exception);
}

BOOST_AUTO_TEST_CASE(option_should_succeed)
{
	ocl::option opt(ocl::eval_true());
	BOOST_CHECK_NO_THROW(opt.expect(""));
}
