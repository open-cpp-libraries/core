// SPDX-License-Identifier: BSL-1.0
// Copyright 2026, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/open-cpp-libraries/core

#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <ocl/detail/math/config.hpp>
#include <ocl/equiv_fwd.hpp>
#include <ocl/option_fwd.hpp>
#include <ocl/scientific_fwd.hpp>

/// @todo To be defined in a final design

#define Im(x) std::complex(x)
#define Re(x) ((::ocl::scientific::real_type)x)
#define Q(x)  ((std::int32_t)x)
#define P(x)  ((::ocl::scientific::real_type)x)

/// @note The following are as you may have noticed, is terribly inaccurate.
/// For any serious computation of PI, please refer to either: The Boost Math Library, 
/// or rolling your own summation of pi based on Ramanujan's work (if you have such time to spare)
#define pi				  (3.14159265358979323846)
#define euler_num		  (2.71828182845904523536)
#define euler_masch		  (0.57721566490153286060651209008240243104215933593992)
#define apery			  (zeta_apery)
#define golden_ratio	  (((1 + std::sqrt(5)) / 2))
#define sqrt_two		  (std::sqrt(2))
#define gelfond_schneider (std::pow(2, sqrt_two))
#define catalan			  (0.9159655941772190150)

namespace ocl::scientific
{

	using variable_count_type = int;

	template <variable_count_type functions_cnt,
			  variable_count_type variable_cnt>
	class pde_solver
	{
	public:
		pde_solver()  = default;
		~pde_solver() = default;

		using number_type = real_type;

		number_type operator()(const number_type& left, const std::vector<number_type>& right)
		{
			return 0;
		}
	};

	template <variable_count_type variable_cnt>
	using ode_solver = pde_solver<1, variable_cnt>;

	template <variable_count_type variable_cnt>
	class nth_deriv_solver
	{
	public:
		nth_deriv_solver()	= default;
		~nth_deriv_solver() = default;

		using number_type = real_type;

		number_type operator()(const number_type& left, const std::vector<number_type>& right)
		{
			return 0;
		}
	};

	template <variable_count_type variable_cnt>
	class nth_int_solver
	{
	public:
		nth_int_solver()  = default;
		~nth_int_solver() = default;

		using number_type = real_type;

		number_type operator()(const number_type& left, const std::vector<number_type>& right)
		{
			return 0;
		}
	};

	class eq_solver_two
	{
	public:
		eq_solver_two()	 = default;
		~eq_solver_two() = default;

		using number_type = real_type;

		/// @brief basic equality solver for two parameters.
		number_type operator()(const number_type& left, const std::vector<number_type>& right)
		{
			number_type res = left;

			for (const auto& p : right)
			{
				if (res < 0)
					res = add(res, p);
				else
					res = sub(res, p);
			}

			return res;
		}
	};

	class ineq_solver_two
	{
	public:
		ineq_solver_two()  = default;
		~ineq_solver_two() = default;

		using number_type = real_type;

		/// @brief basic inequality solver for two parameters.
		number_type operator()(const number_type& left, const std::vector<number_type>& right)
		{
			number_type res = left;

			for (const auto& p : right)
			{
				if (res < 0)
					res = add(res, p);
				else
					res = sub(res, p);
			}

			return res;
		}
	};

	namespace kernels
	{

	/// @brief Provides a sset of olvers for induction, construction, and contradiction methods in mathematical proofs.

		class induction_solver;
		class construction_solver;
		class contradiction_solver;

		class solver_kernel;

	} // namespace kernels

} // namespace ocl::scientific
