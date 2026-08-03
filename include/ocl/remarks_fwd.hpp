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

	/// @brief The remarks manifest structure, which stores LLM information about a file.
	struct remarks_manifest_hdr
	{
		int64_t llm_magic_;
		int64_t llm_version_;

		int32_t llm_vendor_id_{};
		int32_t llm_class_id_{};
		int32_t llm_flags_{};
		int32_t llm_kind_{};

		bool llm_is_video_{}, llm_is_audio_{}, llm_is_image_{};
		bool llm_is_text_{}, llm_is_binary_{};
	};

	inline bool remarks_manifest_is_valid(const remarks_manifest_hdr& hdr)
	{
		return hdr.llm_magic_ == OCL_REMARKS_MAGIC && hdr.llm_version_ == OCL_REMARKS_VERSION;
	}

    template <int32_t T>
    inline bool remarks_manifest_is_llm_vendor(const remarks_manifest_hdr& hdr)
    {
        return hdr.llm_vendor_id_ == T;
    }

} // namespace ocl::remarks

#endif // ifndef OCL_REMARKS_FMT