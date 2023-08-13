/*
 * Libraries/String.hpp
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
#include <array>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
#include <type_traits>

/* Local inclusions for usages. */
#include "Utility.hpp"

/**
 * @brief Advanced strings manipulations.
 * @note Most of these functions has been inspired by PHP and Qt.
 */
namespace Libraries::String
{
	// NOLINTBEGIN(*-magic-numbers)
	static constexpr auto Empty = "";
	static constexpr auto WhiteCharsList = " \f\n\r\t\v";

	/** @brief Enumerates how to operate on a string. */
	enum class Side
	{
		Right,
		Left,
		Both
	};

	/**
	 * @brief Returns an incremental label.
	 * @param label The base label.
	 * @param count A reference to a counter. This will be used next to the label then incremented.
	 * @return std::string
	 */
	template< typename type_t, std::enable_if_t< std::is_integral_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	std::string
	numericLabel (const std::string & label, type_t count) noexcept
	{
		return label + std::to_string(count);
	}

	/**
	 * @brief Returns an incremental label.
	 * @param label The base label.
	 * @param count A reference to a counter. This will be used next to the label then incremented.
	 * @return std::string
	 */
	template< typename type_t, std::enable_if_t< std::is_integral_v< type_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	std::string
	incrementalLabel (const std::string & label, type_t & count) noexcept
	{
		return label + std::to_string(count++);
	}

	/**
	 * @brief Returns a string cleaned from white char at the beginning and/or the end.
	 * @param source A reference to the input string.
	 * @param list A list of characters to remove. Default the regular white characters.
	 * @param trimType From where removing chars off the string. Default Side::Both.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string trim (const std::string & source, const char * list = WhiteCharsList, Side trimType = Side::Both) noexcept;

	/**
	 * @brief Adds a padding to a string to meet the desired size.
	 * @todo Allow the pad parameter to be a string instead of only a char.
	 * @param source A reference to the input string.
	 * @param size The final size of the string, if the input string is greater or equals in size, the function will returns the string.
	 * @param padChar The char to pad with.
	 * @param padType Where to add chars to the string. Default Side::Right.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string pad (const std::string & source, size_t size, char pad = ' ', Side padType = Side::Right) noexcept;

	/**
	 * @brief Splits a string into multiple others using a separator.
	 * @param source A reference to the input string.
	 * @param separator A character to use as a separator.
	 * @param keepEmpty Keep empty part after splitting. Default true.
	 * @param limit Limits the number of split. Default MAXIMUM.
	 * @return std::vector< std::string >
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::vector< std::string > explode (const std::string & source, char separator, bool keepEmpty = true, unsigned int limit = std::numeric_limits< unsigned int >::max()) noexcept;

	/**
	 * @brief Splits a string into multiple others using a separator.
	 * @param source A reference to the input string.
	 * @param separator A reference to a string to use as a separator.
	 * @param keepEmpty Keep empty part after splitting. Default true.
	 * @param limit Limits the number of split. Default MAXIMUM.
	 * @return std::vector< std::string >
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::vector< std::string > explode (const std::string & source, const std::string & separator, bool keepEmpty = true, unsigned int limit = std::numeric_limits< unsigned int >::max()) noexcept;

	/**
	 * @brief Joins a list of string to a single string.
	 * @param list A reference to a vector of string.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string implode (const std::vector< std::string > & list) noexcept;

	/**
	 * @brief Joins a list of string to a single string using a delimiter between parts.
	 * @tparam The type of value to insert as delimiter.
	 * @param list A reference to a vector of string.
	 * @param delimiter A reference to a value to insert between each parts.
	 * @return std::string
	 */
	template< typename delimiter_t >
	[[maybe_unused]]
	[[nodiscard]]
	std::string implode (const std::vector< std::string > & list, const delimiter_t & delimiter) noexcept
	{
		std::stringstream output{};

		for ( const auto & item : list )
		{
			if ( item.empty() )
			{
				continue;
			}

			if ( output.tellp() == 0 )
			{
				output << item;
			}
			else
			{
				output << delimiter << item;
			}
		}

		return output.str();
	}

	/**
	 * @brief Returns the string in upper case.
	 * @param source A reference to the input string.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string toUpper (const std::string & source) noexcept;

	/**
	 * @brief Returns the string in lower case.
	 * @param source A reference to the input string.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string toLower (const std::string & source) noexcept;

	/**
	 * @brief Returns the string with the first char in upper case.
	 * @param source A reference to the input string.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string ucfirst (const std::string & source) noexcept;

	/**
	 * @brief Replaces a piece of string by an other inside a string.
	 * @param search A reference to a string to seek the part to replace.
	 * @param replace A reference to a string to set the replacing part.
	 * @param input A reference to the target string.
	 * @param limit The limit of search occurrence. Default 0 (all).
	 * @return
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string replace (const std::string & search, const std::string & replace, const std::string & input, size_t limit = 0) noexcept;

	/**
	 * @brief Removes every occurrence of a character in a string and returns it.
	 * @param source A reference to the input string.
	 * @param character The character to remove.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string removeChars (const std::string & source, char character) noexcept;

	/**
	 * @brief Removes every occurrence from the character list in a string and returns it.
	 * @param source A reference to the input string.
	 * @param character The character to remove.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string removeChars (const std::string & source, const std::string & characters) noexcept;

	/**
	 * @brief Removes the file extension in string representing a filepath.
	 * @param input A reference to a string.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string removeFileExtension (const std::string & input) noexcept;

	/**
	 * @brief Extracts the filename from a filepath.
	 * @param input A reference to a string.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string extractFilename (const std::string & input) noexcept;

	/**
	 * @brief Returns a string with only numbers present in the input string.
	 * @param input The input C-String.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string extractNumbers (const char * input) noexcept;

	/**
	 * @brief Extracts a list of tag in a string.
	 * @param input A reference to a string.
	 * @param delimiters A reference to an array of two chars to set the tag delimiter. By default '{', '}'.
	 * @return std::vector< std::string >
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::vector< std::string > extractTags (const std::string & input, const std::array< char, 2 > & delimiters = {'{', '}'}) noexcept;

	/**
	 * @brief Returns the left part of match in source string.
	 * @param source A reference to the string.
	 * @param match A reference to a string for the matching part.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string left (const std::string & source, const std::string & match) noexcept;

	/**
	 * @brief Returns the right part of match in source string.
	 * @param source A reference to the string.
	 * @param match A reference to a string for the matching part.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string right (const std::string & source, const std::string & match) noexcept;

	/**
	 * @brief Returns whether a piece of string is part of the source string.
	 * @param source A reference to the string.
	 * @param match A reference to a string for the matching part.
	 * @return bool
	 */
	[[maybe_unused]]
	[[nodiscard]]
	bool contains (const std::string & source, const std::string & piece) noexcept;

	/**
	 * @brief Returns whether str execute with the piece.
	 * @param source A reference to the string.
	 * @param piece A reference to a string for the matching part.
	 * @return bool
	 */
	[[maybe_unused]]
	[[nodiscard]]
	inline
	bool
	startsWith (const std::string & source, const std::string & piece) noexcept
	{
		return source.rfind(piece, 0) == 0;
	}

	/**
	 * @brief Returns a multibyte character stored in a string from unicode code.
	 * @param unicode The code of the character in the unicode.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string unicodeToUTF8 (unsigned int unicode) noexcept;

	/**
	 * @brief Converts a string into a number.
	 * @tparam number_t The type of number.
	 * @warning This function is intended to be used within a number based template.
	 * If you know exactly the type of number you need, consider using the STL functions directly.
	 * @param stringValue A reference to a string.
	 * @return number_t
	 */
	template< typename number_t, std::enable_if_t< std::is_arithmetic_v< number_t >, bool > = false >
	[[nodiscard]]
	number_t
	toNumber (const std::string & stringValue) noexcept
	{
		if constexpr ( std::is_same_v< number_t, float > )
		{
			return std::stof(stringValue, nullptr);
		}

		if constexpr ( std::is_same_v< number_t, double > )
		{
			return std::stod(stringValue, nullptr);
		}

		if constexpr ( std::is_same_v< number_t, long double > )
		{
			return std::stold(stringValue, nullptr);
		}

		/* NOTE: Same as 'int8_t', 'int16_t' */
		/* WARNING: 'signed char' !== 'char' */
		if constexpr ( std::is_same_v< number_t, signed char > || std::is_same_v< number_t, char > || std::is_same_v< number_t, short int > )
		{
			const int integer = std::stoi(stringValue, nullptr, 10);

			if ( integer < std::numeric_limits< number_t >::min() )
			{
				return std::numeric_limits< number_t >::min();
			}

			if ( integer > std::numeric_limits< number_t >::max() )
			{
				return std::numeric_limits< number_t >::max();
			}

			return static_cast< number_t >(integer);
		}

		/* NOTE: Same as 'int32_t' */
		if constexpr ( std::is_same_v< number_t, int > )
		{
			return std::stoi(stringValue, nullptr, 10);
		}

		/* NOTE: Same as 'int64_t' */
		if constexpr ( std::is_same_v< number_t, long int > )
		{
			return std::stol(stringValue, nullptr, 10);
		}

		/* NOTE: Same as 'int128_t' */
		if constexpr ( std::is_same_v< number_t, long long int > )
		{
			return std::stoll(stringValue, nullptr, 10);
		}

		/* NOTE: Same as 'uint8_t', 'uint16_t', 'uint32_t' */
		if constexpr ( std::is_same_v< number_t, unsigned char > || std::is_same_v< number_t, unsigned short int > || std::is_same_v< number_t, unsigned int > )
		{
			const unsigned long int integer = std::stoul(stringValue, nullptr, 10);

			if ( integer > std::numeric_limits< number_t >::max() )
			{
				return std::numeric_limits< number_t >::max();
			}

			return static_cast< number_t >(integer);
		}

		/* NOTE: Same as 'uint64_t' */
		if constexpr ( std::is_same_v< number_t, unsigned long int > )
		{
			return std::stoul(stringValue, nullptr, 10);
		}

		/* NOTE: Same as 'uint128_t' */
		if constexpr ( std::is_same_v< number_t, unsigned long long int > )
		{
			return std::stoull(stringValue, nullptr, 10);
		}

		return 0;
	}

	/**
 	 * @brief Converts a floating point number into a boolean.
	 * @tparam float_t The variable type. Default float.
	 * @param value The value to converts.
	 * @return bool
	 */
	template< typename float_t = float, std::enable_if_t< std::is_floating_point_v< float_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	bool
	toBool (float_t value) noexcept
	{
		return !Utility::isZero(value);
	}

	/**
	 * @brief Converts an integer into a boolean.
	 * @tparam integer_t The variable type. Default int.
	 * @param value The value to converts.
	 * @return bool
	 */
	template< typename integer_t = int, std::enable_if_t< std::is_integral_v< integer_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	bool
	toBool (integer_t value) noexcept
	{
		return value != 0;
	}

	/**
	 * @brief Converts a string into a boolean.
	 * @param value A reference to a string.
	 * @return bool
	 */
	[[maybe_unused]]
	[[nodiscard]]
	bool toBool (std::string value) noexcept;

	/**
	 * @brief Concatenates two C-strings.
	 * @param strA A C-String
	 * @param strB A C-String
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	inline
	std::string
	concat (const char * strA, const char * strB) noexcept
	{
		return std::string{strA} + std::string{strB};
	}

	/**
	 * @brief Concatenates something to a string.
	 * @param str A C-String
	 * @param append A value to appends
	 * @return std::string
	 */
	template< typename type >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	std::string
	concat (const char * str, type append) noexcept
	{
		return std::string{str} + std::to_string(append);
	}

	/**
	 * @brief Concatenates something to a string.
	 * @param str A reference to a string.
	 * @param append A value to appends
	 * @return std::string
	 */
	template< typename type >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	std::string
	concat (const std::string & str, type append) noexcept
	{
		return str.append(std::to_string(append));
	}

	/**
	 * @brief Converts a type to a string.
	 * @param value The value to convert.
	 * @return std::string
	 */
	template< typename type_t >
	[[maybe_unused]]
	[[nodiscard]]
	inline
	std::string
	to_string (type_t value) noexcept
	{
		return std::to_string(value);
	}

	/**
	 * @brief Converts a pointer to a string.
	 * @param value A pointer.
	 * @return std::string
	 */
	template<>
	[[maybe_unused]]
	[[nodiscard]]
	inline
	std::string
	to_string< void * > (void * value) noexcept
	{
		return '@' + std::to_string(reinterpret_cast< std::intptr_t >(value)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
	}

	/**
	 * @brief Converts a const pointer to a string.
	 * @param value A pointer.
	 * @return std::string
	 */
	template<>
	[[maybe_unused]]
	[[nodiscard]]
	inline
	std::string
	to_string< const void * > (const void * value) noexcept
	{
		return '@' + std::to_string(reinterpret_cast< std::intptr_t >(value)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
	}

	/**
	 * @brief Converts a boolean to a string.
	 * @param value A boolean.
	 * @return std::string
	 */
	template<>
	[[maybe_unused]]
	[[nodiscard]]
	inline
	std::string
	to_string< bool > (bool value) noexcept
	{
		return value ? "true" : "false";
	}

	/**
	 * @brief Converts a thread id to a string.
	 * @param value A thread id.
	 * @return std::string
	 */
	template<>
	[[maybe_unused]]
	[[nodiscard]]
	inline
	std::string
	to_string< std::thread::id > (std::thread::id value) noexcept
	{
		return (std::stringstream{} << value).str();
	}
	// NOLINTEND(*-magic-numbers)
}
