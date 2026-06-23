// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#ifndef OCL_CORE_BASIC_HASH
#define OCL_CORE_BASIC_HASH

#include <ocl/detail/config.hpp>

/// @brief OCL basic hash support.

namespace ocl
{

	/// \brief Hash helper.
	template <class Type>
	struct basic_hash
	{
		using result_type = typename Type::result_type;
		using type		  = Type;

		// AMLALE: If it throws, we can't compute the hash correctly.
		constexpr result_type hash() noexcept
		{
			return type{}.hash();
		}
	};

	/// \brief For all boolean types, return false as they are not hashable
	template <>
	struct basic_hash<bool>
	{
		using result_type = bool;
		using type		  = bool;

		// AMLALE: If it throws, we can't compute the hash correctly.
		constexpr result_type hash()
		{
			return false;
		}
	};

} // namespace ocl

#endif
