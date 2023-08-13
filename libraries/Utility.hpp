/*
 * Libraries/Utility.hpp
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
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <random>
#include <string>
#include <type_traits>

/* Local inclusions for usages. */
#include "Path/File.hpp"

namespace Libraries::Utility
{
	// NOLINTBEGIN(readability-identifier-length, *-magic-numbers)
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
	 * @param value The number to be tested.
	 * @param lowest The lowest number allowed.
	 * @param highest The highest number allowed.
	 * @return type_t
	 */
	template< typename type_t, std::enable_if_t< std::is_arithmetic_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	type_t
	between (type_t value, type_t lowest, type_t highest) noexcept
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
	 * @param dividend The dividend.
	 * @param divisor The divisor.
	 * @return type_t
	 */
	template< typename type_t, std::enable_if_t< std::is_arithmetic_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	constexpr
	type_t
	ceilDivision (type_t dividend, type_t divisor) noexcept
	{
		return (dividend / divisor) + (dividend % divisor != 0);
	}

	/**
	 * @brief Returns the ratio between two number.
	 * @param total The divisor.
	 * @param part The dividend.
	 * @param scale Scale the output number.
	 * @return type_t
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	constexpr
	type_t
	ratio (type_t total, type_t part, type_t scale) noexcept
	{
		return (part / total) * scale;
	}

	/**
	 * @brief Returns the ratio between two number.
	 * @param total The divisor.
	 * @param part The dividend.
	 * @param scale Scale the output number.
	 * @return type_t
	 */
	template< typename type_t, std::enable_if_t< std::is_integral_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	constexpr
	type_t
	ratio (type_t total, type_t part, float scale = 1.0F) noexcept
	{
		return static_cast< type_t >(static_cast< float >(part) / static_cast< float >(total) * scale);
	}

	/**
	 * @brief Rounds up a number.
	 * @param value The number to round.
	 * @param precision The number of decimal.
	 * @return type_t
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	type_t
	round (type_t value, size_t precision = 0) noexcept
	{
		auto scale = static_cast< type_t >(std::pow(10, precision));

		return std::round(value * scale) / scale;
	}

	/**
	 * @brief Returns a random integer between a specified range
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @return type_t
	 */
	template< typename type_t, std::enable_if_t< std::is_integral_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	type_t
	random (type_t min, type_t max) noexcept
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
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @return type_t
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	type_t
	random (type_t min, type_t max) noexcept
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
	 * @brief Returns a random integer between a specified range
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @return type_t
	 */
	template< typename type_t, std::enable_if_t< std::is_integral_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	type_t
	trueRandom (type_t min, type_t max) noexcept
	{
		if ( max < min )
		{
			std::swap(min, max);
		}

		//static std::default_random_engine generator{std::random_device{}()};
		//static std::knuth_b generator{std::random_device{}()};
		static std::mt19937 generator{std::random_device{}()};

		return std::uniform_int_distribution< type_t >{min, max}(generator);
	}

	/**
	 * @brief Returns a random float between a specified range.
	 * @param min The minimum number.
	 * @param max The maximum number.
	 * @return type_t
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	type_t
	trueRandom (type_t min, type_t max) noexcept
	{
		if ( max < min )
		{
			std::swap(min, max);
		}

		//static std::default_random_engine generator{std::random_device{}()};
		//static std::knuth_b generator{std::random_device{}()};
		static std::mt19937 generator{std::random_device{}()};

		return std::uniform_real_distribution< type_t >{min, max}(generator);
	}

	/**
	 * @brief Checks if two floating numbers are equal.
	 * @param a The first number.
	 * @param b The second number.
	 * @param epsilon The authorized error.
	 * @return bool
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	bool
	equal (type_t a, type_t b, type_t epsilon = std::numeric_limits< type_t >::epsilon()) noexcept
	{
		return std::fabs(a - b) <= epsilon;
	}

	/**
	 * @brief Checks if two floating numbers are different.
	 * @param a The first number.
	 * @param b The second number.
	 * @param epsilon The authorized error.
	 * @return bool
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	bool
	different (type_t a, type_t b, type_t epsilon = std::numeric_limits< type_t >::epsilon()) noexcept
	{
		return std::fabs(a - b) > epsilon;
	}

	/**
	 * @brief Checks if a floating number is zero.
	 * @tparam type_t The type of number.
	 * @param value The number to test.
	 * @param epsilon The authorized error.
	 * @return bool
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	bool
	isZero (type_t value, type_t epsilon = std::numeric_limits< type_t >::epsilon()) noexcept
	{
		return std::fabs(value) <= epsilon;
	}

	/**
	 * @brief Replaces a number if its a below the tolerated zero.
	 * @tparam type_t The type of number.
	 * @param value The number to test.
	 * @param replacement The number to replace with if the test failed.
	 * @param epsilon The authorized error.
	 * @return type_t
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	type_t
	ifZero (type_t value, type_t replacement, type_t epsilon = std::numeric_limits< type_t >::epsilon()) noexcept
	{
		return std::fabs(value) <= epsilon ? replacement : value;
	}

	/**
	 * @brief Returns a random seed for the perlin noise generator based on UNIX timestamp.
	 * @return unsigned int
	 */
	[[maybe_unused]]
	[[nodiscard]]
	unsigned int timeBasedSeed () noexcept;

	/**
	 * @brief Reads a file and returns the content into a std::vector.
	 * @param filepath The file path.
	 * @param content A reference to a string.
	 * @return bool
	 */
	[[maybe_unused]]
	bool fileGetContents (const Path::File & filepath, std::string & content) noexcept;

	/**
	 * @brief Writes a string to a file.
	 * @param filepath The file path.
	 * @param content A reference to a string.
	 * @return bool
	 */
	[[maybe_unused]]
	bool filePutContents (const Path::File & filepath, const std::string & content) noexcept;

	/**
	 * @brief Reads a file and returns the binary content into a std::vector.
	 * @param filepath The file path.
	 * @param content A reference to an unsigned int vector.
	 * @return bool
	 */
	template< typename type_t >
	[[maybe_unused]]
	bool
	fileGetContents (const Path::File & filepath, std::vector< type_t > & content) noexcept
	{
		std::ifstream file{to_string(filepath), std::ios::ate | std::ios::binary};

		if ( !file.is_open() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to read '" << filepath << "' file." << std::endl;

			return false;
		}

		/* NOTE: Read the file size. */
		const auto size = file.tellg();
		file.seekg(0);

		content.resize(size / sizeof(type_t) + (size % (sizeof(type_t) ? 1U : 0U)));

		file.read(reinterpret_cast< char * >(content.data()), size); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
		file.close();

		return true;
	}

	/**
	 * @brief Writes binary data to a file.
	 * @param filepath The file path.
	 * @param content A reference to an unsigned int vector.
	 * @return bool
	 */
	template< typename type_t >
	[[maybe_unused]]
	bool
	filePutContents (const Path::File & filepath, const std::vector< type_t > & content) noexcept
	{
		std::ofstream file{to_string(filepath), std::ios::binary | std::ios::trunc};

		if ( !file.is_open() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to write into '" << filepath << "' file." << std::endl;

			return false;
		}

		file.write(reinterpret_cast< const char * >(content.data()), content.size() * sizeof(type_t)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
		file.close();

		return true;
	}

	/**
	 * @brief Uncompress a stream using ZLIB.
	 * @param sourceStream The compressed source stream.
	 * @param targetStream The uncompressed target stream.
	 * @return bool
	 */
	[[maybe_unused]]
	bool uncompressStream (std::istream & sourceStream, std::ostream & targetStream) noexcept;

	/**
	 * @brief Compress a stream using ZLIB.
	 * @param sourceStream The uncompressed source stream.
	 * @param targetStream The compressed target stream.
	 * @param chunkSize The size of chunk to be compressed by step.
	 * @param level The compression level.
	 * @return size_t
	 */
	[[maybe_unused]]
	size_t compressStream (std::istream & sourceStream, std::ostream & targetStream, size_t chunkSize = 4096, int level = 9) noexcept;

	/**
	 * @brief Utility function to test 'noexcept' behavior of an object.
	 * @param objectA A type of object.
	 * @param objectB A type of object.
	 * @param objectC A type of object.
	 */
	template< class type_t >
	[[maybe_unused]]
	inline
	void
	checkNoexcept (type_t objectA, type_t objectB, type_t objectC)
	{
		std::cout <<
			"Is constructor is noexcept : " << noexcept(type_t{}) << "\n"
			"Is copy constructor is noexcept : " << noexcept(type_t(objectA)) << "\n"
			"Is move constructor is noexcept : " << noexcept(type_t(std::move(objectA))) << "\n"
			"Is assignment is noexcept : " << noexcept(objectB = objectC) << "\n"
			"Is move-assignment is noexcept : " << noexcept(objectB = std::move(objectC)) << "\n";
	}
	// NOLINTEND(readability-identifier-length, *-magic-numbers)
}
