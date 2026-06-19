// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#ifndef OCL_CORE_EQUIV
#define OCL_CORE_EQUIV

#include <ocl/detail/config.hpp>

/// @brief OCL equivalence file for conditions.


namespace ocl
{

	template <typename Type>
	struct is_real final
	{
		using type					= Type;
		static constexpr auto value = false;
	};

	template <typename L, typename R>
	struct equiv_to final
	{
		using left_type	 = L;
		using right_type = R;

		static constexpr auto value = false;
	};

	template <typename L>
	struct equiv_to<L, L> final
	{
		static constexpr auto value = true;
	};

	template <>
	struct is_real<double> final
	{
		static constexpr auto value = true;
	};

	template <>
	struct is_real<float> final
	{
		static constexpr auto value = true;
	};

	/// \brief alias equiv_to to boolean type.
	template <typename Type>
	using equiv_to_bool = equiv_to<bool, Type>;

} // namespace ocl

#endif
