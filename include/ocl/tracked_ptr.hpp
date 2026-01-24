// Copyright 2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-org/core

#ifndef OCL_TRACKED_PTR
#define OCL_TRACKED_PTR

#include "boost/assert/source_location.hpp"
#include <ocl/detail/config.hpp>
#include <atomic>
#include <stdexcept>

namespace ocl
{

	template <typename Type>
	class tracked_allocator
	{
	public:
		std::atomic<std::size_t> allocated_count_{0};
		std::atomic<std::size_t> deallocated_count_{0};

	public:
		explicit tracked_allocator() = default;
		virtual ~tracked_allocator() = default;

		tracked_allocator& operator=(const tracked_allocator&) = default;
		tracked_allocator(const tracked_allocator&)			   = default;

	public:
		using pointer_type = Type*;
		using type		   = Type;

		template <typename... Args>
		void retain(pointer_type& ptr, Args&&... args)
		{
			ptr = new type(std::forward<Args>(args)...);

			if (ptr)
			{
				++allocated_count_;
				return;
			}

			throw std::bad_alloc();
		}

		void dispose(pointer_type& ptr)
		{
			if (ptr)
			{
				if (allocated_count_)
					--allocated_count_;

				++deallocated_count_;

				delete ptr;
				ptr = nullptr;
			}
		}
	};

	template <typename Type>
	class tracked_mgr
	{
	private:
		tracked_allocator<Type> allocator_;

	public:
		explicit tracked_mgr() = default;
		virtual ~tracked_mgr() = default;

		tracked_mgr& operator=(const tracked_mgr&) = default;
		tracked_mgr(const tracked_mgr&)			   = default;

	public:
		using pointer_type = Type*;
		using type		   = Type;

		const tracked_allocator<Type>& allocator() noexcept
		{
			return allocator_;
		}

		template <typename... Args>
		pointer_type retain(Args&&... args)
		{
			pointer_type ptr = nullptr;
			allocator_.retain(ptr, std::forward<Args>(args)...);

			return ptr;
		}

		template <typename... Args>
		[[maybe_unused]] pointer_type must_retain(Args&&... args)
		{
			try
			{
				return this->retain(std::forward<Args>(args)...);
			}
			catch (...)
			{
				std::terminate();
			}
		}

		void dispose(pointer_type& ptr) noexcept
		{
			allocator_.dispose(ptr);
		}
	};

	template <typename Type, typename Mgr = tracked_mgr<Type>>
	class tracked_ptr
	{
		using manager = Mgr;

		manager mgr_;

	public:
		template <typename... Args>
		tracked_ptr(Args&&... args)
			: ptr_(nullptr)
		{
			ptr_ = mgr_.retain(std::forward<Args>(args)...);
		}

		virtual ~tracked_ptr() noexcept
		{
			this->reset();
		}

		tracked_ptr(const tracked_ptr&)			   = delete;
		tracked_ptr& operator=(const tracked_ptr&) = delete;

	public:
		using pointer_type		   = Type*;
		using type				   = Type;
		using reference_type	   = Type&;
		using const_reference_type = const Type&;
		using manager_type		   = tracked_mgr<manager>;
		using pointer			   = pointer_type;
		using reference			   = reference_type;

		void reset()
		{
			if (ptr_)
			{
				mgr_.dispose(ptr_);
			}
		}

		pointer_type get() const
		{
			return ptr_;
		}

		type& operator*() const
		{
			return *ptr_;
		}

		pointer_type operator->() const
		{
			return ptr_;
		}

		explicit operator bool() const
		{
			return ptr_ != nullptr;
		}

		void swap(tracked_ptr& other)
		{
			std::swap(ptr_, other.ptr_);
		}

	public:
		tracked_ptr(tracked_ptr&& other) noexcept
			: ptr_(other.ptr_)
		{
			other.ptr_ = nullptr;
		}

		tracked_ptr& operator=(tracked_ptr&& other) noexcept
		{
			if (this != &other)
			{
				ptr_	   = other.ptr_;
				other.ptr_ = nullptr;
			}

			return *this;
		}

	private:
		pointer_type ptr_{nullptr};
	};

	template <typename Type>
	inline auto make_tracked() -> tracked_ptr<Type>
	{
		return tracked_ptr<Type>();
	}

	template <typename RetType, typename... Type>
	inline auto make_tracked(Type&&... arg) -> tracked_ptr<RetType>
	{
		return tracked_ptr<RetType>(std::forward<Type>(arg)...);
	}

	template <typename Type>
	inline void swap(tracked_ptr<Type>& a, tracked_ptr<Type>& b)
	{
		a.swap(b);
	}

	namespace detail
	{
		using tracked_error = std::runtime_error;

		inline void throw_tracked_error(const boost::source_location& loc = BOOST_CURRENT_LOCATION)
		{
			throw tracked_error(loc.to_string());
		}
	} // namespace detail

	/// @brief This function is a standard way to verify a container' validity, inspired from NeKernel/VMKernel.
	template <typename Type>
	inline void try_throw(tracked_ptr<Type>& ptr)
	{
		if (ptr.manager().allocator().allocated_count_ < ptr.manager().allocator().deallocated_count_)
		{
			detail::throw_tracked_error();
		}
	}

} // namespace ocl

#endif // ifndef OCL_TRACKED_PTR
