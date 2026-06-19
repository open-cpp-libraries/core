// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#ifndef OCL_CORE_ALLOCATOR_OP
#define OCL_CORE_ALLOCATOR_OP

#include <ocl/detail/config.hpp>
#include <ocl/detail/alloc/config.hpp>

/// @brief Memory allocator for OCL support.

namespace ocl
{

	namespace detail
	{

		/// @internal Bad allocation descriptor. Use it to grab references about an allocation error.
		struct bad_alloc_traits final
		{
			using pointer = void*;
			pointer				   ptr_{};
			boost::source_location loc_;
		};

		inline void throw_bad_alloc(bad_alloc_traits::pointer p, const boost::source_location& loc = BOOST_CURRENT_LOCATION)
		{
			bad_alloc_traits ba;
			ba.ptr_ = p;
			ba.loc_ = loc;

			throw ba;
		}

	} // namespace detail

	/// @note these are guidelines on allocating a resource
	template <typename Type>
	struct global_new_op final
	{
	public:
		using pointer_type		 = Type*;
		using const_pointer_type = const Type*;
		using pointer			 = Type*;
		using const_pointer		 = const Type*;
		using mutex_type		 = std::mutex;
		using lock_type			 = std::scoped_lock<mutex_type>;
		using type				 = Type;

	public:
		mutex_type m_;

		auto single_alloc() -> pointer_type
		{
			return new type{};
		}

		template <size_t N>
		auto array_alloc() -> pointer_type
		{
			static_assert(N > 0, "N == 0, whereas N shall be greater than zero.");
			return new type[N]{};
		}

		template <typename... VarType>
		auto var_alloc(VarType&&... args) -> pointer_type
		{
			return new type{std::forward<VarType>(args)...};
		}
	};

	template <typename Type>
	struct global_delete_op final
	{
		using pointer_type		 = Type*;
		using const_pointer_type = const Type*;

		global_delete_op()	= default;
		~global_delete_op() = default;

		auto operator()(pointer_type t, const bool array_delete = false) -> void
		{
			if (t == nullptr)
				return;

			if (array_delete)
				delete[] t;
			else
				delete t;
		}
	};

	/// \brief Backwards compat. alias of global_new_op.
	template <typename Type>
	using global_array_delete_op = global_new_op<Type>;

	/// \brief Allocator operations structure. Takes care of memory mgmt within a pool.
	template <typename RetType, typename AllocNew, typename AllocDelete>
	class allocator_op final
	{
	public:
		allocator_op()	= default;
		~allocator_op() = default;

		allocator_op& operator=(const allocator_op&) = delete;
		allocator_op(const allocator_op&)			 = delete;

		using size_type = std::size_t;
		using type		= RetType;

		template <typename... VarType>
		auto construct_var(VarType&&... args)
		{
			static AllocNew				 alloc;
			typename AllocNew::lock_type lt{alloc.m_};
			return std::shared_ptr<type>(alloc.template var_alloc<VarType...>(std::forward<VarType...>(args)...), AllocDelete{});
		}

		template <size_type N>
		auto construct_array()
		{
			static AllocNew				 alloc;
			typename AllocNew::lock_type lt{alloc.m_};
			return std::shared_ptr<type>(alloc.template array_alloc<N>(), AllocDelete{});
		}
	};

	template <typename Type>
	using allocator = allocator_op<Type, global_new_op<Type>, global_delete_op<Type>>;

} // namespace ocl

#endif // ifndef OCL_CORE_ALLOCATOR_OP
