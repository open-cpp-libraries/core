// SPDX-License-Identifier: BSL-1.0
// Copyright 2025-2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-foss-org/core

#ifndef OCL_CORE_OPTION
#define OCL_CORE_OPTION

#include <ocl/detail/config.hpp>
#include <ocl/print.hpp>
#include <cstdint>

namespace ocl
{

	enum struct return_type : int
	{
		invalid = 0,
		okay	= 100,
		err,
		count = err - okay + 1,
	};

	namespace detail
	{
		using option_error = std::runtime_error;

		inline void throw_option_invalid_type_error(const boost::source_location& loc = BOOST_CURRENT_LOCATION)
		{
			throw option_error(loc.to_string());
		}
	} // namespace detail

	class option final
	{
	public:
		option() = delete;
		explicit option(const return_type& return_type)
			: ret_(return_type)
		{
			if (ret_ == return_type::invalid)
				detail::throw_option_invalid_type_error();
		}

		~option() = default;

		option& operator=(const option&) = default;
		option(const option&)			 = default;

		option& expect(const char* input)
		{
			assert(ret_ != return_type::invalid);

			if (ret_ == return_type::err)
			{
				io::println(input ? input : "option::error");
				detail::throw_option_invalid_type_error();
			}

			return *this;
		}

		template <typename Handleable>
		option& expect(const char* input)
		{
			assert(ret_ != return_type::invalid);

			if (ret_ == return_type::err)
			{
				// AMLALE: Shall it be a functor or container here?
				Handleable{}(input ? input : "option::error");
			}

			return *this;
		}

	private:
		return_type ret_{return_type::invalid};
	};

	namespace detail
	{
		// AMLALE: The operator() are marked as `noexcept` as failing conditions within an evaluation (say a overloads operator==) proves that the
		// predictate is wrong. Thus program state is undefined.

		struct eq_teller final
		{
			template <class ObjFirst, class ObjLast>
			bool operator()(ObjFirst a, ObjLast b) noexcept
			{
				return (a == b);
			}
		};

		struct greater_than_teller final
		{
			template <class ObjFirst, class ObjLast>
			bool operator()(ObjFirst a, ObjLast b) noexcept
			{
				return (a > b);
			}
		};

		struct less_than_teller final
		{
			template <class ObjFirst, class ObjLast>
			bool operator()(ObjFirst a, ObjLast b) noexcept
			{
				return (a < b);
			}
		};
	} // namespace detail

	template <typename Teller, typename... Lst>
	inline return_type eval(const Teller& tell, Lst&&... arg)
	{
		return tell(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	template <typename... Lst>
	inline return_type eval_less_than(Lst&&... arg)
	{
		return detail::less_than_teller{}(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	template <typename... Lst>
	inline return_type eval_eq(Lst&&... arg)
	{
		return detail::eq_teller{}(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	template <typename... Lst>
	inline return_type eval_greater_than(Lst&&... arg)
	{
		return detail::greater_than_teller{}(std::forward<Lst>(arg)...) ? return_type::okay : return_type::err;
	}

	inline return_type eval_true() noexcept
	{
		return return_type::okay;
	}

	inline return_type eval_false() noexcept
	{
		return return_type::err;
	}

	inline return_type eval_invalid() noexcept
	{
		return return_type::invalid;
	}

} // namespace ocl

#endif /* ifndef OCL_CORE_OPTION */
