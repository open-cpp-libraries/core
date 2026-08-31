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

namespace ocl::scientific::solver
{

	using variable_count_type = int;

	template <variable_count_type functions_cnt,
			  variable_count_type variable_cnt>
	class pde_solver
	{
	public:
		pde_solver()  = default;

		using number_type = real_type;

		number_type operator()(const number_type& left, const std::vector<number_type>& right)
		{
			return {};
		}
	};

	template <variable_count_type variable_cnt>
	using ode_solver = pde_solver<1, variable_cnt>;

	template <variable_count_type variable_cnt>
	class nth_deriv_solver
	{
	public:
		nth_deriv_solver()	= default;

		using number_type = real_type;

		number_type operator()(const number_type& left, const std::vector<number_type>& right)
		{
			return {};
		}
	};

	template <variable_count_type variable_cnt>
	class nth_int_solver
	{
	public:
		nth_int_solver()  = default;

		using number_type = real_type;

		number_type operator()(const number_type& left, const std::vector<number_type>& right)
		{
			return {};
		}
	};

	class eq_solver_two
	{
	public:
		eq_solver_two()	 = default;

		using number_type = real_type;

		/// @brief basic equality solver for two parameters.
		number_type operator()(const number_type& left, const std::vector<number_type>& right)
		{
			return {};
		}
	};

	class ineq_solver_two
	{
	public:
		ineq_solver_two()  = default;

		using number_type = real_type;

		/// @brief basic inequality solver for two parameters.
		number_type operator()(const number_type& left, const std::vector<number_type>& right)
		{
			return {};
		}
	};

#ifndef sorry
#define sorry true
#endif

	template <class Friend>
	class kernel_solver_tag
	{
	public:
		friend Friend;

		using pointer = Friend;

		uint64_t id_{};
		pointer	 self_{};

        /// This guarantees that the solver is indeed solved.
        static const bool is_formalized = false;

	};

	/// @brief Provides a set of solvers for induction, construction,
	// and contradiction methods in mathematical proofs.

	template <class Friend>
	class induction_solver_tag : public kernel_solver_tag<Friend>
	{
	};

	template <class Friend>
	class construction_solver_tag : public kernel_solver_tag<Friend>
	{
	};

	template <class Friend>
	class contradiction_solver_tag : public kernel_solver_tag<Friend>
	{
	};

    /// @brief Solve a mathematical conjecture using a pre-solved solver first.
	template <class Solver, class Friend>
	class basic_chain_solver_tag : public kernel_solver_tag<Friend>
	{
    public:
        static_assert(Solver::is_formalized, "The Solver you want to base this chain on is not solved. Use ::sorry to make this error go away.");

        Solver pre_cond_;

	};

	/// @brief base kernel solver.
	template <class Friend>
	using solver_kernel_tag = kernel_solver_tag<Friend>;
    
    template <class Solver, class Friend>
	using chain_solver_tag = basic_chain_solver_tag<Solver, Friend>;


} // namespace ocl::scientific::solver
