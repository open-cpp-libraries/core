// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-foss-org/core

#ifndef OCL_CORE_CONFIG
#define OCL_CORE_CONFIG

#ifndef OCL_FREESTANDING
#include <boost/config.hpp>
#include <boost/core/addressof.hpp>
#include <boost/core/nvp.hpp>
#include <boost/core/demangle.hpp>
#include <boost/core/null_deleter.hpp>
#include <boost/container/allocator.hpp>
#include <boost/assert/source_location.hpp>
#include <boost/assert.hpp>
#include <boost/utility/string_view.hpp>
#include <boost/config.hpp>
#endif

#define OCL_DEPRECATED()		[[deprecated]]
#define OCL_DEPRECATED_MSG(MSG) [[deprecated(MSG)]]

#if 202002L > __cplusplus
#error !! OCL.Core works with C++20 and greater !!
#endif

#ifdef __cplusplus
#define OCL_DECL extern "C"
/// DLL/Dylib/So specific macro.
#ifdef __GNUC__
#define OCL_EXPORT_DECL OCL_DECL __attribute__((visibility("default")))
#else
#define OCL_EXPORT_DECL OCL_DECL declspec(dllexport)
#endif
#else
#define OCL_DECL
#ifdef __GNUC__
#define OCL_EXPORT_DECL
#else
#define OCL_EXPORT_DECL OCL_DECL declspec(dllimport)
#endif
#endif

#ifdef _WIN32
#define OCL_USE_CRLF_ENDINGS 1
#define OCL_WINDOWS			 1
#endif

#if OCL_WANTS_PRAGMA_ONCE
#define OCL_HAS_PRAGMA_ONCE 1
#endif

namespace ocl
{

	namespace detail
	{

		inline void throw_runtime_error(const boost::source_location& loc = BOOST_CURRENT_LOCATION)
		{
			throw std::runtime_error(loc.to_string());
		}

	} // namespace detail

	namespace placeholders
	{

#define OCL_PLACEHOLDER_PREFIX "${"
#define OCL_PLACEHOLDER_SUFFIX "}"

		inline std::string find_and_replace(const std::string& input,
								const std::string& new_val,
								const std::string& name)
		{
			if (input.find(OCL_PLACEHOLDER_PREFIX + name + OCL_PLACEHOLDER_SUFFIX) == std::string::npos)
				return {};

			std::string replacement = input;
			replacement.replace(input.find(OCL_PLACEHOLDER_PREFIX + name + OCL_PLACEHOLDER_SUFFIX),
								std::string(OCL_PLACEHOLDER_PREFIX + name + OCL_PLACEHOLDER_SUFFIX).size(),
								new_val);

			return replacement;
		}

	} // namespace placeholders

} // namespace ocl

#endif
