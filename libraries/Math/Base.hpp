/*
 * Libraries/Math/Base.hpp
 * This file is part of Emeraude
 *
 * Copyright (C) 2012-2023 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude
 * 
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* C/C++ standard libraries. */
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <vector>

#define OPTIMIZED

namespace Libraries::Math
{
	// NOLINTBEGIN(readability-identifier-length, *-magic-numbers)
	/**
	 * @brief The interpolation types.
	 */
	enum class InterpolationType
	{
		Linear,
		Cosine,
		Cubic
	};

	/**
	 * @brief Archimedes's constant.
	 * @tparam data_t A floating point type. Default float.
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	constexpr
	data_t Pi = static_cast< data_t >(3.14159265358979323846264338327950288);

	/**
	 * @brief Constant for the golden ratio.
	 * @note (A + B) / A = A / B ('A' must be the biggest) or (1 + std::sqrt(5)) / 2
	 * @tparam data_t A floating point type. Default float.
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	constexpr
	data_t Phi = static_cast< data_t >(1.61803398874989484820458683436563811);

	/**
	 * @brief Euleur's constant.
	 * @tparam data_t A floating point type. Default float.
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	constexpr
	data_t e = static_cast< data_t >(2.71828182845904523536028747135266249);

	/**
	 * @brief Gets the gold number.
	 * @tparam data_t A floating point type. Default float.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	constexpr
	data_t
	getPhi () noexcept
	{
		return (1 + std::sqrt(static_cast< data_t >(5))) * static_cast< data_t >(0.5);
	}

	/**
	 * @brief Gets the pi constant.
	 * @tparam data_t A floating point type. Default float.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	constexpr
	data_t
	getPi () noexcept
	{
		return std::atan(static_cast< data_t >(1)) * 4;
	}

	/**
	 * @brief Gets the Euleur's constant.
	 * @tparam data_t A floating point type. Default float.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	data_t
	getE (int trial = 4) noexcept
	{
		auto euler = [] (int n) {
			return static_cast< data_t >(std::pow(1 + 1.0 / n, n));
		};

		data_t tmpA = euler(1);
		data_t tmpB = euler(2);

		while ( std::abs(tmpA - tmpB) > static_cast< data_t >(1e-8) )
		{
			tmpA = tmpB;

			tmpB = euler(trial);

			trial *= 2;
		}

		return tmpB;
	}

	/**
	 * @brief 90 degrees constant.
	 * @tparam data_t The precision type. Default float.
	 */
	template< typename data_t = float >
	constexpr
	data_t QuartRevolution = static_cast< data_t >(90);

	/**
	 * @brief 180 degrees constant.
	 * @tparam data_t The precision type. Default float.
	 */
	template< typename data_t = float >
	constexpr
	data_t HalfRevolution = static_cast< data_t >(180);

	/**
	 * @brief 270 degrees constant.
	 * @tparam data_t The precision type. Default float.
	 */
	template< typename data_t = float >
	constexpr
	data_t ThreeQuartsRevolution = static_cast< data_t >(270);

	/**
	 * @brief 360 degrees constant.
	 * @tparam data_t The precision type. Default float.
	 */
	template< typename data_t = float >
	constexpr
	data_t FullRevolution = static_cast< data_t >(360);

	/**
	 * @brief Turns degree value into radian value.
	 * @tparam data_t A floating point type. Default float.
	 * @param degree The angle to convert in radians.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	constexpr
	data_t
	Radian (data_t degree) noexcept
	{
		return (degree * Pi< data_t >) / HalfRevolution< data_t >;
	}

	/**
	 * @brief Turns radian value into degree value.
	 * @tparam data_t A floating point type. Default float.
	 * @param radian The angle to convert in degrees.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	constexpr
	data_t
	Degree (data_t radian) noexcept
	{
		return (radian / Pi< data_t >) * HalfRevolution< data_t >;
	}

	/**
	 * @brief Clamps a value between two boundaries.
	 * @tparam data_t An arithmetic type. Default float.
	 * @param value The value.
	 * @param min The minimum boundary.
	 * @param max The maximum boundary.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	constexpr
	data_t
	clamp (data_t value, data_t min, data_t max) noexcept
	{
		if ( value < min )
		{
			return min;
		}

		if ( value > max )
		{
			return max;
		}

		return value;
	}

	/**
	 * @brief Clamps a value between "0.0" and "1.0".
	 * @tparam data_t A floating type. Default float.
	 * @param value The value.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	constexpr
	data_t
	clampToUnit (data_t value) noexcept
	{
		if ( value < 0 )
		{
			return 0;
		}

		if ( value > 1 )
		{
			return 1;
		}

		return value;
	}

	/**
	 * @brief Clamps a radian value to one cycle.
	 * @tparam data_t A floating type. Default float.
	 * @param radian A reference to the value.
	 * @return bool
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	constexpr
	bool
	clampRadian (data_t & radian) noexcept
	{
		const auto limit = Radian(FullRevolution< data_t >);

		/* Too high */
		if ( radian > limit )
		{
			radian -= limit;

			return false;
		}

		/* Too low */
		if ( radian < -limit )
		{
			radian += limit;

			return false;
		}

		/* Inside -360 and +360 */
		return true;
	}

	/**
	 * @brief Clamps a radian value to one cycle.
	 * @tparam data_t A floating type. Default float.
	 * @param radian The angle in radian.
	 * @return bool
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	constexpr
	data_t
	getClampedRadian (data_t radian) noexcept
	{
		const auto limit = Radian(FullRevolution< data_t >);

		/* Too high */
		if ( radian > limit )
		{
			return radian - limit;
		}

		/* Too low */
		if ( radian < -limit )
		{
			return radian + limit;
		}

		/* Inside -360 and +360 */
		return radian;
	}

	/**
	 * @brief Performs cotan of an angle in degree.
	 * @tparam data_t A floating type. Default float.
	 * @param degree The angle to compute.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	constexpr
	data_t
	cotan (data_t degree) noexcept
	{
		degree = Radian(degree);

		return std::cos(degree) / std::sin(degree);
	}

	/**
	 * @brief Performs fast cotan of an angle in degree.
	 * @tparam data_t A floating type. Default float.
	 * @param degree The angle to compute.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	constexpr
	data_t
	fastCotan (data_t degree) noexcept
	{
		return std::tan(Radian< data_t >(90) - Radian(degree));
	}

	/**
	 * @brief Performs a linear interpolation between values.
	 * @tparam data_t An arithmetic type for input data. Default float.
	 * @tparam scale_t A floating type for scale data. Default float.
	 * @param a The operand A.
	 * @param b The operand B.
	 * @param factor The interpolation factor.
	 * @return data_t
	 */
	template<
		typename data_t = float,
		typename scale_t = float,
		//std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false,
		std::enable_if_t< std::is_floating_point_v< scale_t >, bool > = false
	>
	[[maybe_unused]]
	[[nodiscard]]
	inline
	data_t
	linearInterpolation (data_t a, data_t b, scale_t factor) noexcept
	{
		/*
		 * Formula A : {a * (1 - mu) + b * factor}
		 * Formula B : {a + (b - a) * factor} ! Only 1 multiplication
		 */
		return a + (b - a) * factor;
	}

	/**
	 * @brief Performs a cosine interpolation between values.
	 * @tparam data_t An arithmetic type for input data. Default float.
	 * @tparam scale_t A floating type for scale data. Default float.
	 * @param a The first value.
	 * @param b The second value.
	 * @param mu The factor between 0 and 1.
	 * @return data_t
	 */
	template<
		typename data_t = float,
		typename scale_t = float,
		//std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false,
		std::enable_if_t< std::is_floating_point_v< scale_t >, bool > = false
	>
	[[maybe_unused]]
	[[nodiscard]]
	data_t
	cosineInterpolation (data_t a, data_t b, scale_t mu) noexcept
	{
		/* Cosine version only modifies 'mu' before performing a simple linear interpolation. */
		mu = (static_cast< scale_t >(1) - std::cos(mu * Pi< scale_t >)) * static_cast< scale_t >(0.5);

		return linearInterpolation(a, b, mu);
	}

	/**
	 * @brief Performs a cubic interpolation between values.
	 * @tparam data_t An arithmetic type for input data. Default float.
	 * @tparam scale_t A floating type for scale data. Default float.
	 * @param y0 The first value.
	 * @param y1 The second value.
	 * @param y2 The third value.
	 * @param y3 The fourth value.
	 * @param mu The factor between 0 and 1.
	 * @return data_t
	 */
	template<
		typename data_t = float,
		typename scale_t = float,
		//std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false,
		std::enable_if_t< std::is_floating_point_v< scale_t >, bool > = false
	>
	[[maybe_unused]]
	[[nodiscard]]
	data_t
	cubicInterpolation (data_t y0, data_t y1, data_t y2, data_t y3, scale_t mu) noexcept
	{
		const auto a0 = y3 - y2 - y0 + y1;
		const auto a1 = y0 - y1 - a0;
		const auto a2 = y2 - y0;
		const auto a3 = y1;

#ifdef OPTIMIZED
		return ((a0 * mu + a1) * mu + a2) * mu + a3;
#else
		const auto mu2 = mu * mu;

		return a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3;
#endif
	}

	/**
	 * @brief Performs a cubic (Catmull-Rom) interpolation between values.
	 * @tparam data_t An arithmetic type for input data. Default float.
	 * @tparam scale_t A floating type for scale data. Default float.
	 * @param y0 The first value.
	 * @param y1 The second value.
	 * @param y2 The third value.
	 * @param y3 The fourth value.
	 * @param mu The factor between 0 and 1.
	 * @return data_t
	 */
	template<
		typename data_t = float,
		typename scale_t = float,
		//std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false,
		std::enable_if_t< std::is_floating_point_v< scale_t >, bool > = false
	>
	[[maybe_unused]]
	[[nodiscard]]
	data_t
	cubicCatmullRomInterpolation (data_t y0, data_t y1, data_t y2, data_t y3, scale_t mu) noexcept
	{
		const auto a0 = static_cast< scale_t >(-0.5) * y0 + static_cast< scale_t >(1.5) * y1 - static_cast< scale_t >(1.5) * y2 + static_cast< scale_t >(0.5) * y3;
		const auto a1 = y0 - static_cast< scale_t >(2.5) * y1 + static_cast< scale_t >(2.0) * y2 - static_cast< scale_t >(0.5) * y3;
		const auto a2 = static_cast< scale_t >(-0.5) * y0 + static_cast< scale_t >(0.5) * y2;
		const auto a3 = y1;

#ifdef OPTIMIZED
		return ((a0 * mu + a1) * mu + a2) * mu + a3;
#else
		const auto mu2 = mu * mu;

		return a0 * mu * mu2 + a1 * mu2 + a2 * mu + a3;
#endif
	}

	/**
	 * @brief Performs a Hermite interpolation between values.
	 * @tparam data_t An arithmetic type for input data. Default float.
	 * @tparam scale_t A floating type for scale data. Default float.
	 * @param y0 The first value.
	 * @param y1 The second value.
	 * @param y2 The third value.
	 * @param y3 The fourth value.
	 * @param mu The factor between 0 and 1.
	 * @param tension 1 is high, 0 normal, -1 is low.
	 * @param bias 0 is even, positive is towards first segment, negative towards the other.
	 * @return data_t
	 */
	template<
		typename data_t = float,
		typename scale_t = float,
		//std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false,
		std::enable_if_t< std::is_floating_point_v< scale_t >, bool > = false
	>
	[[maybe_unused]]
	[[nodiscard]]
	data_t
	hermiteInterpolate (data_t y0, data_t y1, data_t y2, data_t y3, scale_t mu, scale_t tension, scale_t bias) noexcept
	{
		const auto mu2 = mu * mu;
		const auto mu3 = mu2 * mu;

		const auto a0 = static_cast< scale_t >(2.0) * mu3 - static_cast< scale_t >(3.0) * mu2 + static_cast< scale_t >(1.0);
		const auto a1 = mu3 - static_cast< scale_t >(2.0) * mu2 + mu;
		const auto a2 = mu3 - mu2;
		const auto a3 = - static_cast< scale_t >(2.0) * mu3 + static_cast< scale_t >(3.0) * mu2;

		auto m0 = (y1 - y0) * (static_cast< scale_t >(1.0) + bias) * (static_cast< scale_t >(1.0) - tension) * static_cast< scale_t >(0.5);
		m0 += (y2 - y1) * (static_cast< scale_t >(1.0) - bias) * (static_cast< scale_t >(1.0) - tension) * static_cast< scale_t >(0.5);

		auto m1 = (y2 - y1) * (static_cast< scale_t >(1.0) + bias) * (static_cast< scale_t >(1.0) - tension) * static_cast< scale_t >(0.5);
		m1 += (y3 - y2) * (static_cast< scale_t >(1.0) - bias) * (static_cast< scale_t >(1.0) - tension) * static_cast< scale_t >(0.5);

		return a0 * y1 + a1 * m0 + a2 * m1 + a3 * y2;
	}

	/**
	 * @brief Normalizes a value.
	 * @tparam input_t An arithmetic type for input data. Default float.
	 * @tparam output_t A arithmetic type for output data. Default float.
	 * @param value The value.
	 * @param scale The scale of the value.
	 * @return output_t
	 */
	template<
		typename input_t = float,
		typename output_t = float,
		//std::enable_if_t< std::is_arithmetic_v< input_t >, bool > = false,
		std::enable_if_t< std::is_arithmetic_v< output_t >, bool > = false
	>
	[[maybe_unused]]
	[[nodiscard]]
	inline
	output_t
	normalize (input_t value, input_t scale) noexcept
	{
		return scale > 0 ? static_cast< output_t >(value / scale) : 0;
	}

	/**
	 * @brief Computes a circle circumference.
	 * @tparam data_t A floating type. Default float.
	 * @param radius The radius.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	data_t
	circleCircumference (data_t radius) noexcept
	{
		return radius > 0 ? 2 * Pi< data_t > * radius : 0;
	}

	/**
	 * @brief Computes a circle area.
	 * @tparam data_t A floating type. Default float.
	 * @param radius The radius.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	data_t
	circleArea (data_t radius) noexcept
	{
		return radius > 0 ? Math::Pi< data_t > * (radius * radius) : 0;
	}

	/**
	 * @brief Computes a sphere volume.
	 * @tparam data_t A floating type. Default float.
	 * @param radius The radius.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	data_t
	sphereVolume (data_t radius) noexcept
	{
		if ( radius <= 0 )
		{
			return 0;
		}

		constexpr data_t r = 4 / 3;

		return r * Pi< data_t > * std::pow(radius, 3);
	}

	/**
	 * @brief Returns the delta between two numbers.
	 * @tparam data_t A floating type. Default float.
	 * @param a The first value.
	 * @param b The second value.
	 * @return data_t
	 */
	template< typename data_t = float >
	[[deprecated("Invalid formula !")]]
	[[maybe_unused]]
	[[nodiscard]]
	inline
	data_t
	delta (data_t a, data_t b) noexcept
	{
		return ( a > b ) ? a - b : b - a;
	}

	/**
	 * @brief Returns the scale difference between two numbers.
	 * @tparam data_t A floating type. Default float.
	 * @param a The first value.
	 * @param b The second value.
	 * @return data_t
	 */
	template< typename data_t = float >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	data_t
	difference (data_t a, data_t b) noexcept
	{
		return a > b ? (a - b) / b : (b - a) / a;
	}

	/**
	 * @brief Returns the reciprocal.
	 * @tparam data_t A floating type. Default float.
	 * @param value The value.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	data_t
	reciprocal (data_t value) noexcept
	{
		return static_cast< data_t >(1) / value;
	}

	/**
	 * @brief Returns the reciprocal square root.
	 * @tparam data_t A floating type. Default float.
	 * @param value The value.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	data_t
	reciprocalSquareRoot (data_t value) noexcept
	{
		return static_cast< data_t >(1) / std::sqrt(value);
	}

	/**
	 * @brief Returns the number of time a value is divisible by an other without getting into decimal.
	 * @tparam data_t An integral type. Default unsigned int.
	 * @param value The value.
	 * @param division The division.
	 * @return data_t
	 */
	template< typename data_t = unsigned int, std::enable_if_t< std::is_integral_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	data_t
	timesDivisible (data_t value, data_t division) noexcept
	{
		auto count = 0;

		while ( value % division == 0 )
		{
			value /= division;

			count++;
		}

		return count;
	}

	/**
	 * @brief Returns the number of time requested to fit the alignment.
	 * @FIXME: Find a better function name !
	 * @tparam data_t An integral type. Default unsigned int.
	 * @param value The value to align.
	 * @param alignment A fixed value for the alignment.
	 * @return size_t
	 */
	template< typename data_t = unsigned int, std::enable_if_t< std::is_integral_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	size_t
	alignCount (data_t value, data_t alignment)
	{
		return static_cast< size_t >(std::ceil(static_cast< float >(value) / static_cast< float >(alignment)));
	}

	/**
	 * @brief Returns the average of numbers in a vector.
	 * @tparam data_t An arithmetic type. Default float.
	 * @param numbers A reference to a vector of numbers.
	 * @return data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	data_t
	average (const std::vector< data_t > & numbers)
	{
		return numbers.empty() ? 0 : std::accumulate(numbers.cbegin(), numbers.cend(), 0) / numbers.size();
	}
	// NOLINTEND(readability-identifier-length, *-magic-numbers)
}
