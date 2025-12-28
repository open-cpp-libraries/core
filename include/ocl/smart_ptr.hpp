// Copyright 2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-org/core

#ifndef __OCL_SMART_PTR
#define __OCL_SMART_PTR

#include <boost/core/null_deleter.hpp>
#include <ocl/detail/config.hpp>
#include <ocl/tracked_ptr.hpp>
#include <memory>

namespace ocl
{

	template <class Type, class Del = std::default_delete<Type>>
	using unique_ptr = std::unique_ptr<Type, Del>;

	template <class Type>
	using shared_ptr = std::shared_ptr<Type>;

	/// @brief Constructs a `delete_ptr`, that is, a pointer that isn't deleted from the heap.
	template <class Type>
	inline auto delete_ptr(Type* object) -> shared_ptr<Type>
	{
		return shared_ptr<Type>{object, boost::null_deleter{}};
	}

} // namespace ocl

#endif // ifndef __OCL_SMART_PTR
