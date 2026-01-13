// Copyright 2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-org/core

#ifndef __OCL_CORE_ALLOCATOR_OP
#define __OCL_CORE_ALLOCATOR_OP

#include <ocl/detail/config.hpp>
#include <memory>

namespace ocl
{

	/// @note these are guidelines on allocating a resource
	template <typename type>
	struct global_new_op final
	{
		using pointer_type		 = type*;
		using const_pointer_type = const type*;
		using pointer			 = type*;
		using const_pointer		 = const type*;

		auto alloc() -> pointer_type
		{
			return new type;
		}

		template <size_t N>
		auto array_alloc() -> pointer_type
		{
			return new type[N];
		}

		template <typename... var_type>
		auto var_alloc(var_type&&... args) -> pointer_type
		{
			return new type{std::forward<var_type>(args)...};
		}
	};

	template <typename type>
	struct global_delete_op final
	{
		using pointer_type		 = type*;
		using const_pointer_type = const type*;

		auto operator()(pointer_type t) -> void
		{
			delete[] t;
		}
	};

	/// \brief Backwards compat. alias of global_new_op.
	template <typename type>
	using global_array_delete_op = global_new_op<type>;

	/// \brief Allocator operations structure. Takes care of memory mgmt within a pool.
	template <typename ret_type, typename allocator_new, typename allocator_delete>
	class allocator_op
	{
	public:
		allocator_op()	= default;
		~allocator_op() = default;

		allocator_op& operator=(const allocator_op&) = delete;
		allocator_op(const allocator_op&)			 = delete;

		template <typename... var_type>
		auto construct_var(var_type&&... args)
		{
			return std::shared_ptr<ret_type>(allocator_new{}.template var_alloc<var_type...>(std::forward<var_type...>(args)...), allocator_delete{});
		}

		template <std::size_t N>
		auto construct_array()
		{
			return std::shared_ptr<ret_type>(allocator_new{}.template array_alloc<N>(), allocator_delete{});
		}
	};

	template <typename type>
	using allocator = allocator_op<type, global_new_op<type>, global_delete_op<type>>;

} // namespace ocl

#endif // ifndef __OCL_CORE_ALLOCATOR_OP
