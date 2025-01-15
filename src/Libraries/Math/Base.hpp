/*
 * src/Libraries/Math/Base.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <type_traits>
#include <vector>

#define OPTIMIZED

namespace Libraries::Math
{
	/**
	 * @brief The interpolation types.
	 */
	enum class InterpolationType : uint8_t
	{
		Linear,
		Cosine,
		Cubic
	};

	/**
	 * @brief Archimedes's constant.
	 * @tparam float_t The type of floating point number. Default float.
	 */
	template< typename float_t = float >
	requires (std::is_floating_point_v< float_t >)
	constexpr float_t Pi = static_cast< float_t >(3.14159265358979323846264338327950288);

	/**
	 * @brief Constant for the golden ratio.
	 * @note (A + B) / A = A / B ('A' must be the biggest) or (1 + std::sqrt(5)) / 2
	 * @tparam float_t The type of floating point number. Default float.
	 */
	template< typename float_t = float >
	requires (std::is_floating_point_v< float_t >)
	constexpr float_t Phi = static_cast< float_t >(1.61803398874989484820458683436563811);

	/**
	 * @brief Euleur's constant.
	 * @tparam float_t The type of floating point number. Default float.
	 */
	template< typename float_t = float >
	requires (std::is_floating_point_v< float_t >)
	constexpr float_t e = static_cast< float_t >(2.71828182845904523536028747135266249);

	/**
	 * @brief Gets the gold number.
	 * @tparam float_t The type of floating point number. Default float.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	float_t
	getPhi () noexcept requires (std::is_floating_point_v< float_t >)
	{
		return (1 + std::sqrt(static_cast< float_t >(5))) * static_cast< float_t >(0.5);
	}

	/**
	 * @brief Gets the pi constant.
	 * @tparam float_t The floating point number type. Default float.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	float_t
	getPi () noexcept requires (std::is_floating_point_v< float_t >)
	{
		return std::atan(static_cast< float_t >(1)) * 4;
	}

	/**
	 * @brief Gets the Euleur's constant.
	 * @tparam float_t The type of floating point number. Default float.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	float_t
	getE (int trial = 4) noexcept requires (std::is_floating_point_v< float_t >)
	{
		auto euler = [] (const int number) {
			return static_cast< float_t >(std::pow(1 + 1.0 / number, number));
		};

		float_t tmpA = euler(1);
		float_t tmpB = euler(2);

		while ( std::abs(tmpA - tmpB) > static_cast< float_t >(1e-8) )
		{
			tmpA = tmpB;

			tmpB = euler(trial);

			trial *= 2;
		}

		return tmpB;
	}

	/**
	 * @brief 90 degrees constant.
	 * @tparam number_t The type of number. Default float.
	 */
	template< typename number_t = float >
	requires (std::is_arithmetic_v< number_t >)
	constexpr number_t QuartRevolution = static_cast< number_t >(90);

	/**
	 * @brief 180 degrees constant.
	 * @tparam number_t The type of number. Default float.
	 */
	template< typename number_t = float >
	requires (std::is_arithmetic_v< number_t >)
	constexpr number_t HalfRevolution = static_cast< number_t >(180);

	/**
	 * @brief 270 degrees constant.
	 * @tparam number_t The type of number. Default float.
	 */
	template< typename number_t = float >
	requires (std::is_arithmetic_v< number_t >)
	constexpr number_t ThreeQuartsRevolution = static_cast< number_t >(270);

	/**
	 * @brief 360 degrees constant.
	 * @tparam number_t The type of number. Default float.
	 */
	template< typename number_t = float >
	requires (std::is_arithmetic_v< number_t >)
	constexpr number_t FullRevolution = static_cast< number_t >(360);

	/**
	 * @brief Turns degree value into radian value.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param degree The angle to convert in radians.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	float_t
	Radian (float_t degree) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return degree * Pi< float_t > / HalfRevolution< float_t >;
	}

	/**
	 * @brief Turns radian value into degree value.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param radian The angle to convert in degrees.
	 * @return float_t
	 */
	template< typename float_t = float>
	[[nodiscard]]
	constexpr
	float_t
	Degree (float_t radian) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return radian / Pi< float_t > * HalfRevolution< float_t >;
	}

	/**
	 * @brief Clamps a value between two boundaries.
	 * @tparam number_t The type of number. Default float.
	 * @param value The value.
	 * @param min The minimum boundary.
	 * @param max The maximum boundary.
	 * @return number_t
	 */
	template< typename number_t = float >
	[[nodiscard]]
	constexpr
	number_t
	clamp (number_t value, number_t min, number_t max) noexcept requires (std::is_arithmetic_v< number_t >)
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
	 * @tparam float_t The type of floating point number. Default float.
	 * @param value The value.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	float_t
	clampToUnit (float_t value) noexcept requires (std::is_floating_point_v< float_t >)
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
	 * @tparam float_t The type of floating point number. Default float.
	 * @param radian A reference to the value.
	 * @return bool
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	bool
	clampRadian (float_t & radian) noexcept requires (std::is_floating_point_v< float_t >)
	{
		const auto limit = Radian(FullRevolution< float_t >);

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
	 * @tparam float_t The type of floating point number. Default float.
	 * @param radian The angle in radian.
	 * @return bool
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	float_t
	getClampedRadian (float_t radian) noexcept requires (std::is_floating_point_v< float_t >)
	{
		const auto limit = Radian(FullRevolution< float_t >);

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
	 * @tparam float_t The type of floating point number. Default float.
	 * @param degree The angle to compute.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	float_t
	cotan (float_t degree) noexcept requires (std::is_floating_point_v< float_t >)
	{
		degree = Radian(degree);

		return std::cos(degree) / std::sin(degree);
	}

	/**
	 * @brief Performs fast cotan of an angle in degree.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param degree The angle to compute.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	float_t
	fastCotan (float_t degree) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return std::tan(Radian< float_t >(QuartRevolution< float_t >) - Radian(degree));
	}

	/**
	 * @brief Performs a linear interpolation between values.
	 * @tparam number_t The type of number. Default float.
	 * @tparam scale_float_t The type of floating point number for the scale. Default float.
	 * @param operandA The operand A.
	 * @param operandB The operand B.
	 * @param factor The interpolation factor from 0.0 to 1.0.
	 * @return number_t
	 */
	template< typename number_t = float, typename scale_float_t = float >
	[[nodiscard]]
	number_t
	linearInterpolation (number_t operandA, number_t operandB, scale_float_t factor) noexcept requires (std::is_arithmetic_v< number_t >, std::is_floating_point_v< scale_float_t >)
	{
		return operandA + (operandB - operandA) * factor;
	}

	/**
	 * @brief Performs a cosine interpolation between values.
	 * @tparam number_t The type of number. Default float.
	 * @tparam scale_float_t The type of floating point number for the scale. Default float.
	 * @param operandA The first value.
	 * @param operandB The second value.
	 * @param factor The interpolation factor from 0.0 to 1.0.
	 * @return number_t
	 */
	template< typename number_t = float, typename scale_float_t = float >
	[[nodiscard]]
	number_t
	cosineInterpolation (number_t operandA, number_t operandB, scale_float_t factor) noexcept requires (std::is_arithmetic_v< number_t >, std::is_floating_point_v< scale_float_t >)
	{
		/* Cosine version only modifies 'factor' before performing a simple linear interpolation. */
		factor = (static_cast< scale_float_t >(1) - std::cos(factor * Pi< scale_float_t >)) * static_cast< scale_float_t >(0.5);

		return linearInterpolation(operandA, operandB, factor);
	}

	/**
	 * @brief Performs a cubic interpolation between values.
	 * @tparam number_t The type of number. Default float.
	 * @tparam scale_float_t The type of floating point number for the scale. Default float.
	 * @param valueA The first value.
	 * @param valueB The second value.
	 * @param valueC The third value.
	 * @param valueD The fourth value.
	 * @param factor The interpolation factor from 0.0 to 1.0.
	 * @return number_t
	 */
	template< typename number_t = float, typename scale_float_t = float >
	[[nodiscard]]
	number_t
	cubicInterpolation (number_t valueA, number_t valueB, number_t valueC, number_t valueD, scale_float_t factor) noexcept requires (std::is_arithmetic_v< number_t >, std::is_floating_point_v< scale_float_t >)
	{
		const auto tmpA = valueD - valueC - valueA + valueB;
		const auto tmpB = valueA - valueB - tmpA;
		const auto tmpC = valueC - valueA;
		const auto tmpD = valueB;

#ifdef OPTIMIZED
		return ((tmpA * factor + tmpB) * factor + tmpC) * factor + tmpD;
#else
		const auto factor2 = factor * factor;

		return tmpA * factor * factor2 + tmpB * factor2 + tmpC * factor + tmpD;
#endif
	}

	/**
	 * @brief Performs a cubic (Catmull-Rom) interpolation between values.
	 * @tparam number_t The type of number. Default float.
	 * @tparam scale_float_t The type of floating point number for the scale. Default float.
	 * @param valueA The first value.
	 * @param valueB The second value.
	 * @param valueC The third value.
	 * @param valueD The fourth value.
	 * @param factor The interpolation factor from 0.0 to 1.0.
	 * @return number_t
	 */
	template< typename number_t = float, typename scale_float_t = float >
	[[nodiscard]]
	number_t
	cubicCatmullRomInterpolation (number_t valueA, number_t valueB, number_t valueC, number_t valueD, scale_float_t factor) noexcept requires (std::is_arithmetic_v< number_t >, std::is_floating_point_v< scale_float_t >)
	{
		const auto tmpA = static_cast< scale_float_t >(-0.5) * valueA + static_cast< scale_float_t >(1.5) * valueB - static_cast< scale_float_t >(1.5) * valueC + static_cast< scale_float_t >(0.5) * valueD;
		const auto tmpB = valueA - static_cast< scale_float_t >(2.5) * valueB + static_cast< scale_float_t >(2.0) * valueC - static_cast< scale_float_t >(0.5) * valueD;
		const auto tmpC = static_cast< scale_float_t >(-0.5) * valueA + static_cast< scale_float_t >(0.5) * valueC;
		const auto tmpD = valueB;

#ifdef OPTIMIZED
		return ((tmpA * factor + tmpB) * factor + tmpC) * factor + tmpD;
#else
		const auto factor2 = factor * factor;

		return tmpA * factor * factor2 + tmpB * factor2 + tmpC * factor + tmpD;
#endif
	}

	/**
	 * @brief Performs a Hermite interpolation between values.
	 * @tparam number_t The type of number. Default float.
	 * @tparam scale_float_t The type of floating point number for the scale. Default float.
	 * @param valueA The first value.
	 * @param valueB The second value.
	 * @param valueC The third value.
	 * @param valueD The fourth value.
	 * @param factor The factor between 0 and 1.
	 * @param tension 1 is high, 0 normal, -1 is low.
	 * @param bias 0 is even, positive is towards first segment, negative towards the other.
	 * @return number_t
	 */
	template< typename number_t = float, typename scale_float_t = float >
	[[nodiscard]]
	number_t
	hermiteInterpolate (number_t valueA, number_t valueB, number_t valueC, number_t valueD, scale_float_t factor, scale_float_t tension, scale_float_t bias) noexcept requires (std::is_arithmetic_v< number_t >, std::is_floating_point_v< scale_float_t >)
	{
		const auto factor2 = factor * factor;
		const auto factor3 = factor2 * factor;

		const auto tmpA = static_cast< scale_float_t >(2.0) * factor3 - static_cast< scale_float_t >(3.0) * factor2 + static_cast< scale_float_t >(1.0);
		const auto tmpB = factor3 - static_cast< scale_float_t >(2.0) * factor2 + factor;
		const auto tmpC = factor3 - factor2;
		const auto tmpD = - static_cast< scale_float_t >(2.0) * factor3 + static_cast< scale_float_t >(3.0) * factor2;

		auto mult0 = (valueB - valueA) * (static_cast< scale_float_t >(1.0) + bias) * (static_cast< scale_float_t >(1.0) - tension) * static_cast< scale_float_t >(0.5);
		mult0 += (valueC - valueB) * (static_cast< scale_float_t >(1.0) - bias) * (static_cast< scale_float_t >(1.0) - tension) * static_cast< scale_float_t >(0.5);

		auto mult1 = (valueC - valueB) * (static_cast< scale_float_t >(1.0) + bias) * (static_cast< scale_float_t >(1.0) - tension) * static_cast< scale_float_t >(0.5);
		mult1 += (valueD - valueC) * (static_cast< scale_float_t >(1.0) - bias) * (static_cast< scale_float_t >(1.0) - tension) * static_cast< scale_float_t >(0.5);

		return tmpA * valueB + tmpB * mult0 + tmpC * mult1 + tmpD * valueC;
	}

	/**
	 * @brief Normalizes a value.
	 * @tparam input_number_t The type of input number. Default float.
	 * @tparam output_number_t The type of output number. Default float.
	 * @param value The value.
	 * @param scale The scale of the value.
	 * @return output_number_t
	 */
	template< typename input_number_t = float, typename output_number_t = float >
	[[nodiscard]]
	output_number_t
	normalize (input_number_t value, input_number_t scale) noexcept requires (std::is_arithmetic_v< input_number_t >, std::is_arithmetic_v< output_number_t >)
	{
		return scale > 0 ? static_cast< output_number_t >(value / scale) : 0;
	}

	/**
	 * @brief Computes a circle circumference.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param radius The radius.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	float_t
	circleCircumference (float_t radius) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return radius > 0 ? 2 * Pi< float_t > * radius : 0;
	}

	/**
	 * @brief Computes a circle area.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param radius The radius.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	float_t
	circleArea (float_t radius) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return radius > 0 ? Math::Pi< float_t > * (radius * radius) : 0;
	}

	/**
	 * @brief Computes a sphere volume.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param radius The radius.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	constexpr
	float_t
	sphereVolume (float_t radius) noexcept requires (std::is_floating_point_v< float_t >)
	{
		if ( radius <= 0 )
		{
			return 0;
		}

		return (static_cast< float_t >(4) / static_cast< float_t >(3)) * Pi< float_t > * std::pow(radius, 3);
	}

	/**
	 * @brief Returns the delta between two numbers.
	 * @tparam number_t The type of number. Default float.
	 * @param operandA The first value.
	 * @param operandB The second value.
	 * @return number_t
	 */
	template< typename number_t = float >
	[[deprecated("Invalid formula !")]]
	[[nodiscard]]
	number_t
	delta (number_t operandA, number_t operandB) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		return operandA > operandB ? operandA - operandB : operandB - operandA;
	}

	/**
	 * @brief Returns the scale difference between two numbers.
	 * @tparam number_t The type of number. Default float.
	 * @param operandA The first value.
	 * @param operandB The second value.
	 * @return number_t
	 */
	template< typename number_t = float >
	[[nodiscard]]
	number_t
	difference (number_t operandA, number_t operandB) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		return operandA > operandB ? (operandA - operandB) / operandB : (operandB - operandA) / operandA;
	}

	/**
	 * @brief Returns the reciprocal.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param value The value.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	float_t
	reciprocal (float_t value) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return static_cast< float_t >(1) / value;
	}

	/**
	 * @brief Returns the reciprocal square root.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param value The value.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	float_t
	reciprocalSquareRoot (float_t value) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return static_cast< float_t >(1) / std::sqrt(value);
	}

	/**
	 * @brief Returns the number of time a value is divisible by another without getting into decimal.
	 * @note This is a naive function. Use std::log2().
	 * @tparam integral_t The type of integral number. Default uint32_t.
	 * @param value The value.
	 * @param division The division.
	 * @return size_t
	 */
	template< typename integral_t = uint32_t >
	[[nodiscard]]
	size_t
	timesDivisible (integral_t value, integral_t division) noexcept requires (std::is_integral_v< integral_t >)
	{
		size_t count = 0;

		while ( value % division == 0 )
		{
			value /= division;

			count++;
		}

		return count;
	}

	/**
	 * @brief Returns the number of time requested to fit the alignment.
	 * @tparam integral_t The type of integral number. Default uint32_t.
	 * @param value The value to align.
	 * @param alignment A fixed value for the alignment.
	 * @return size_t
	 */
	template< typename integral_t = uint32_t >
	[[nodiscard]]
	size_t
	alignCount (integral_t value, integral_t alignment) requires (std::is_integral_v< integral_t >)
	{
		return static_cast< size_t >(std::ceil(static_cast< float >(value) / static_cast< float >(alignment)));
	}

	/**
	 * @brief Returns the average of numbers in a vector.
	 * @tparam number_t A type of number. Default float.
	 * @param numbers A reference to a vector of numbers.
	 * @return number_t
	 */
	template< typename number_t = float >
	[[nodiscard]]
	number_t
	average (const std::vector< number_t > & numbers) requires (std::is_arithmetic_v< number_t >)
	{
		return numbers.empty() ? 0 : std::accumulate(numbers.cbegin(), numbers.cend(), 0) / numbers.size();
	}
}
