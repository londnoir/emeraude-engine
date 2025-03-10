/*
 * src/Libraries/Utility.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* Project configuration. */
#include "platform.hpp"

/* STL inclusions. */
#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

namespace Libraries::Utility
{
	/**
	 * @brief Execute the function a numerous times.
	 * @param count The number of times.
	 * @param loopScope A reference to a function.
	 * @return void
	 */
	inline
	void
	forCount (size_t count, const std::function< void () > & loopScope) noexcept
	{
		while ( count-- )
		{
			loopScope();
		}
	}

	/**
	 * @brief Execute the function a numerous times.
	 * @param count The number of times.
	 * @param loopScope A reference to a function.
	 * @return void
	 */
	inline
	void
	forCount (size_t count, const std::function< void (size_t) > & loopScope) noexcept
	{
		for ( size_t i = 0; i < count; ++i )
		{
			loopScope(i);
		}
	}

	/**
	 * @brief Contains method version for STL vector using a pair as key/value.
	 * @param haystack A reference to a vector of pairs.
	 * @param needle A reference to the key.
	 * @return bool
	 */
	template< typename t_x, typename t_y >
	[[nodiscard]]
	bool
	contains (const std::vector< std::pair< t_x, t_y > > & haystack, const t_x & needle) noexcept
	{
		for ( const auto & item : haystack )
		{
			if ( needle == item.first )
			{
				return true;
			}
		}

		return false;
	}

	/**
	 * @brief Returns the number between boundaries or on extreme number.
	 * @tparam number_t The type of the number. Default float.
	 * @param value The number to be tested.
	 * @param lowest The lowest number allowed.
	 * @param highest The highest number allowed.
	 * @return number_t
	 */
	template< typename number_t = float >
	[[nodiscard]]
	number_t
	between (number_t value, number_t lowest, number_t highest) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		if ( value < lowest )
		{
			return lowest;
		}

		if ( value > highest )
		{
			return highest;
		}

		return value;
	}

	/**
	 * @brief Gets the celled result of a division.
	 * @tparam number_t The type of the number. Default float.
	 * @param dividend The dividend.
	 * @param divisor The divisor.
	 * @return number_t
	 */
	template< typename number_t = float >
	[[nodiscard]]
	constexpr
	number_t
	ceilDivision (number_t dividend, number_t divisor) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		return (dividend / divisor) + (dividend % divisor != 0);
	}

	/**
	 * @brief Returns the ratio between two number.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param total The divisor.
	 * @param part The dividend.
	 * @param scale Scale the output number.
	 * @return float_t
	 */
	template< typename float_t >
	[[nodiscard]]
	constexpr
	float_t
	ratio (float_t total, float_t part, float_t scale) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return (part / total) * scale;
	}

	/**
	 * @brief Returns the ratio between two number.
	 * @tparam integral_t The type of integral number. Default int32_t.
	 * @param total The divisor.
	 * @param part The dividend.
	 * @param scale Scale the output number.
	 * @return integral_t
	 */
	template< typename integral_t = int32_t >
	[[nodiscard]]
	constexpr
	integral_t
	ratio (integral_t total, integral_t part, float scale = 1.0F) noexcept requires (std::is_integral_v< integral_t >)
	{
		return static_cast< integral_t >(static_cast< float >(part) / static_cast< float >(total) * scale);
	}

	/**
	 * @brief Rounds up a number.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param value The number to round.
	 * @param precision The number of decimal.
	 * @return float_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	float_t
	round (float_t value, size_t precision = 0) noexcept requires (std::is_floating_point_v< float_t >)
	{
		auto scale = static_cast< float_t >(std::pow(10, precision));

		return std::round(value * scale) / scale;
	}

	/**
	 * @brief Returns a random integer between a specified range.
	 * @note This version use the C rand() function.
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @return type_t
	 */
	template< typename type_t >
	[[nodiscard]]
	type_t
	quickRandom (type_t min, type_t max) noexcept requires (std::is_integral_v< type_t >)
	{
		if ( min > max )
		{
			std::swap(min, max);
		}

		const auto delta = (1 + max - min);

		if ( delta <= 0 )
		{
			return min;
		}

		return (static_cast< type_t >(std::rand()) % delta) + min; // NOLINT(cert-msc50-cpp)
	}

	/**
	 * @brief Returns a random float between a specified range.
	 * @note This version use the C rand() function.
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @return type_t
	 */
	template< typename type_t >
	[[nodiscard]]
	type_t
	quickRandom (type_t min, type_t max) noexcept requires (std::is_floating_point_v< type_t >)
	{
		if ( max < min )
		{
			std::swap(min, max);
		}

		const auto random = static_cast< type_t >(std::rand()) / static_cast< type_t >(RAND_MAX); // NOLINT(cert-msc50-cpp)
		const auto range = max - min;

		return (random * range) + min;
	}

	/**
	 * @brief Returns a random number between a specified range.
	 * @tparam number_t The type of integral number. Default int32_t.
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @return number_t
	 */
	template< typename number_t = int32_t >
	[[nodiscard]]
	number_t
	random (number_t min, number_t max) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		if ( max < min )
		{
			std::swap(min, max);
		}

		std::random_device device{};

		//std::default_random_engine generator{device()};
		//std::knuth_b generator{device()};
		std::mt19937 generator{device()};

		if constexpr ( std::is_integral_v< number_t > )
		{
			return std::uniform_int_distribution< number_t >{min, max}(generator);
		}
		else
		{
			return std::uniform_real_distribution< number_t >{min, max}(generator);
		}
	}

	/**
	 * @brief Returns a random number between a specified range using a seed.
	 * @tparam number_t The type of integral number. Default int32_t.
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @param seed A fixed value.
	 * @return number_t
	 */
	template< typename number_t = int32_t >
	[[nodiscard]]
	number_t
	random (number_t min, number_t max, int seed) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		if ( max < min )
		{
			std::swap(min, max);
		}

		//std::knuth_b generator(seed);
		std::mt19937 generator(seed);

		if constexpr ( std::is_integral_v< number_t > )
		{
			return std::uniform_int_distribution< number_t >{min, max}(generator);
		}
		else
		{
			return std::uniform_real_distribution< number_t >{min, max}(generator);
		}
	}

	/**
	 * @brief Returns an STL vector of random number between a specified range.
	 * @tparam number_t The type of integral number. Default int32_t.
	 * @param count The number of desired numbers.
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @return std::vector< number_t >
	 */
	template< typename number_t = int32_t >
	[[nodiscard]]
	std::vector< number_t >
	randomVector (size_t count, number_t min, number_t max) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		std::vector< number_t > range(count);

		if ( max < min )
		{
			std::swap(min, max);
		}

		std::random_device device{};

		//std::default_random_engine generator{device()};
		//std::knuth_b generator{device()};
		std::mt19937 generator{device()};

		if constexpr ( std::is_integral_v< number_t > )
		{
			std::uniform_int_distribution< number_t > distribution{min, max};

			for ( auto & value : range )
			{
				value = distribution(generator);
			}
		}
		else
		{
			std::uniform_real_distribution< number_t > distribution{min, max};

			for ( auto & value : range )
			{
				value = distribution(generator);
			}
		}

		return range;
	}

	/**
	 * @brief Returns an STL vector of random number between a specified range.
	 * @tparam number_t The type of integral number. Default int32_t.
	 * @param count The number of desired numbers.
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @param seed A fixed value.
	 * @return std::vector< number_t >
	 */
	template< typename number_t = int32_t >
	[[nodiscard]]
	std::vector< number_t >
	randomVector (size_t count, number_t min, number_t max, int seed) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		std::vector< number_t > range(count);

		if ( max < min )
		{
			std::swap(min, max);
		}

		//std::knuth_b generator(seed);
		std::mt19937 generator(seed);

		if constexpr ( std::is_integral_v< number_t > )
		{
			std::uniform_int_distribution< number_t > distribution{min, max};

			for ( auto & value : range )
			{
				value = distribution(generator);
			}
		}
		else
		{
			std::uniform_real_distribution< number_t > distribution{min, max};

			for ( auto & value : range )
			{
				value = distribution(generator);
			}
		}

		return range;
	}

	/**
	 * @brief Returns an STL array of random number between a specified range.
	 * @tparam count_t The number of desired numbers.
	 * @tparam number_t The type of integral number. Default int32_t.
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @return number_t
	 */
	template< size_t count_t, typename number_t = int32_t >
	[[nodiscard]]
	std::array< number_t, count_t >
	randomArray (number_t min, number_t max) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		std::array< number_t, count_t > range{};

		if ( max < min )
		{
			std::swap(min, max);
		}

		std::random_device device{};

		//std::default_random_engine generator{device()};
		//std::knuth_b generator{device()};
		std::mt19937 generator{device()};

		if constexpr ( std::is_integral_v< number_t > )
		{
			std::uniform_int_distribution< number_t > distribution{min, max};

			for ( auto & value : range )
			{
				value = distribution(generator);
			}
		}
		else
		{
			std::uniform_real_distribution< number_t > distribution{min, max};

			for ( auto & value : range )
			{
				value = distribution(generator);
			}
		}

		return range;
	}

	/**
	 * @brief Returns an STL array of random number between a specified range.
	 * @tparam count_t The number of desired numbers.
	 * @tparam number_t The type of integral number. Default int32_t.
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @param seed A fixed value.
	 * @return number_t
	 */
	template< size_t count_t, typename number_t = int32_t >
	[[nodiscard]]
	std::array< number_t, count_t >
	randomArray (number_t min, number_t max, int seed) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		std::array< number_t, count_t > range{};

		if ( max < min )
		{
			std::swap(min, max);
		}

		//std::knuth_b generator(seed);
		std::mt19937 generator(seed);

		if constexpr ( std::is_integral_v< number_t > )
		{
			std::uniform_int_distribution< number_t > distribution{min, max};

			for ( auto & value : range )
			{
				value = distribution(generator);
			}
		}
		else
		{
			std::uniform_real_distribution< number_t > distribution{min, max};

			for ( auto & value : range )
			{
				value = distribution(generator);
			}
		}

		return range;
	}

	/**
	 * @brief Checks if two floating numbers are equal.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param operandA The first number.
	 * @param operandB The second number.
	 * @param epsilon The authorized error.
	 * @return bool
	 */
	template< typename float_t = float >
	[[nodiscard]]
	bool
	equal (float_t operandA, float_t operandB, float_t epsilon = std::numeric_limits< float_t >::epsilon()) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return std::abs(operandA - operandB) <= epsilon;
	}

	/**
	 * @brief Checks if two floating numbers are different.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param operandA The first number.
	 * @param operandB The second number.
	 * @param epsilon The authorized error.
	 * @return bool
	 */
	template< typename float_t = float >
	[[nodiscard]]
	bool
	different (float_t operandA, float_t operandB, float_t epsilon = std::numeric_limits< float_t >::epsilon()) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return std::abs(operandA - operandB) > epsilon;
	}

	/**
	 * @brief Checks if a floating number is zero.
	 * @tparam float_t The type of floating point number.
	 * @param value The number to test.
	 * @param epsilon The authorized error.
	 * @return bool
	 */
	template< typename float_t = float >
	[[nodiscard]]
	bool
	isZero (float_t value, float_t epsilon = std::numeric_limits< float_t >::epsilon()) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return std::abs(value) <= epsilon;
	}

	/**
	 * @brief Replaces a number if it's a below the tolerated zero.
	 * @tparam float_t The type of floating point number. Default float.
	 * @param value The number to test.
	 * @param replacement The number to replace with if the test failed.
	 * @param epsilon The authorized error.
	 * @return type_t
	 */
	template< typename float_t = float >
	[[nodiscard]]
	float_t
	ifZero (float_t value, float_t replacement, float_t epsilon = std::numeric_limits< float_t >::epsilon()) noexcept requires (std::is_floating_point_v< float_t >)
	{
		return std::abs(value) <= epsilon ? replacement : value;
	}

	/**
	 * @brief Returns a random seed for the perlin noise generator based on UNIX timestamp.
	 * @return unsigned int
	 */
	[[nodiscard]]
	inline
	unsigned int
	timeBasedSeed () noexcept
	{
		return static_cast< unsigned int >(std::chrono::system_clock::now().time_since_epoch().count());
	}

	/**
	 * @brief Utility function to test 'noexcept' behavior of an object.
	 * @tparam data_t The type of tested object.
	 * @param objectA A type of object.
	 * @param objectB A type of object.
	 * @param objectC A type of object.
	 */
	template< typename data_t >
	void
	checkNoexcept (data_t objectA, data_t objectB, data_t objectC)
	{
		std::cout <<
			"Is constructor is noexcept : " << noexcept(data_t{}) << "\n"
			"Is copy constructor is noexcept : " << noexcept(data_t(objectA)) << "\n"
			"Is move constructor is noexcept : " << noexcept(data_t(std::move(objectA))) << "\n"
			"Is assignment is noexcept : " << noexcept(objectB = objectC) << "\n"
			"Is move-assignment is noexcept : " << noexcept(objectB = std::move(objectC)) << "\n";
	}
}
