// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#ifndef OCL_REMARKS_FMT
#define OCL_REMARKS_FMT

#include <ocl/detail/config.hpp>

#define OCL_REMARKS_MAGIC	0x4C4D5245
#define OCL_REMARKS_VERSION 0x00010000

#ifndef __attribute_packed__
#define __attribute_packed__ __attribute__((packed))
#endif

#ifndef __ocl_packed__
#define __ocl_packed__ __attribute_packed__
#endif

namespace ocl::remarks
{

	struct remarks_manifest_hdr;

	enum
	{
		llm_vendor_unknown		= 0,
		llm_vendor_openai		= 100,
		llm_vendor_google		= 101,
		llm_vendor_microsoft_ai = 102,
		llm_vendor_anthropic	= 103,
		llm_vendor_custom_start = 1000,
	};

    enum
    {
        llm_kind_unknown = 0,
        llm_kind_video = 200,
        llm_kind_text,
        llm_kind_code,
        llm_kind_agent,
    };

	/// @brief The remarks manifest structure, which stores LLM information about a file.
	struct __ocl_packed__ remarks_manifest_hdr final
	{
		int64_t llm_magic_{OCL_REMARKS_MAGIC};
		int64_t llm_version_{OCL_REMARKS_VERSION};

		int32_t llm_vendor_id_{llm_vendor_unknown};
		int32_t llm_class_id_{0};
		int32_t llm_flags_{0};
        int32_t llm_kind_{llm_kind_unknown};
	};

    /// @brief Is the manifest valid?
	inline bool remarks_manifest_is_valid(const remarks_manifest_hdr& hdr)
	{
		return hdr.llm_magic_ == OCL_REMARKS_MAGIC && hdr.llm_version_ == OCL_REMARKS_VERSION;
	}

    /// @brief Does the vendor id matches the vendor we expect?
    template <int32_t V>
    inline bool remarks_manifest_is_llm_vendor(const remarks_manifest_hdr& hdr)
    {
        return hdr.llm_vendor_id_ == V;
    }

} // namespace ocl::remarks

#endif // ifndef OCL_REMARKS_FMT