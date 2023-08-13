/*
 * Libraries/String.cpp
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

#include "String.hpp"

/* C/C++ standard libraries */
#include <algorithm>
#include <cstring>

namespace Libraries::String
{
	std::string
	trim (const std::string & source, const char * list, Side trimType) noexcept
	{
		switch ( trimType )
		{
			case Side::Right:
			{
				const auto end = source.find_last_not_of(list);

				if ( end == std::string::npos )
				{
					return source;
				}

				return {source, 0, end + 1};
			}

			case Side::Left:
			{
				const auto start = source.find_first_not_of(list);

				if ( start == std::string::npos )
				{
					return source;
				}

				return {source, start, source.size() - start};
			}

			case Side::Both:
			{
				const auto start = source.find_first_not_of(list);
				const auto end = source.find_last_not_of(list);

				if ( start == std::string::npos || end == std::string::npos )
				{
					return source;
				}

				return {source, start, end - start + 1};
			}
		}

		return source;
	}

	std::string
	pad (const std::string & source, size_t size, char pad, Side padType) noexcept
	{
		if ( source.size() >= size )
		{
			return source;
		}

		switch ( padType )
		{
			case Side::Right:
				return source + std::string(size - source.size(), pad);

			case Side::Left:
				return std::string(size-source.size(), pad) + source;

			case Side::Both:
			{
				const auto count = size - source.size();

				std::string copy{source};

				for ( size_t i = 0; i < count; i++ )
				{
					copy.insert((i % 2) != 0 ? copy.begin() : copy.end(), pad);
				}

				return copy;
			}

			default:
				return source;
		}
	}

	std::vector< std::string >
	explode (const std::string & source, char separator, bool keepEmpty, unsigned int limit) noexcept
	{
		std::vector< std::string > list{};

		size_t startOffset = 0;
		size_t endOffset = 0;

		while ( (endOffset = source.find(separator, startOffset)) != std::string::npos )
		{
			const std::string chunk{source, startOffset, endOffset - startOffset};

			if ( keepEmpty || !chunk.empty() )
			{
				list.emplace_back(chunk);
			}

			startOffset = endOffset + 1;

			if ( list.size() >= limit )
			{
				break;
			}
		}

		/* Adds the end of the string if exists. */
		if ( startOffset != source.size() )
		{
			const std::string chunk{source, startOffset, source.size() - startOffset};

			if ( keepEmpty || !chunk.empty() )
			{
				list.emplace_back(chunk);
			}
		}

		return list;
	}

	std::vector< std::string >
	explode (const std::string & source, const std::string & separator, bool keepEmpty, unsigned int limit) noexcept
	{
		std::vector< std::string > list{};

		size_t startOffset = 0;
		size_t endOffset = 0;

		while ( (endOffset = source.find(separator, startOffset)) != std::string::npos )
		{
			const std::string chunk{source, startOffset, endOffset - startOffset};

			if ( keepEmpty || !chunk.empty() )
			{
				list.emplace_back(chunk);
			}

			startOffset = endOffset + separator.size();

			if ( list.size() >= limit )
			{
				break;
			}
		}

		/* Adds the end of the string if exists. */
		if ( startOffset != source.size() )
		{
			const std::string chunk{source, startOffset, source.size() - startOffset};

			if ( keepEmpty || !chunk.empty() )
			{
				list.emplace_back(chunk);
			}
		}

		return list;
	}

	std::string
	implode (const std::vector< std::string > & list) noexcept
	{
		std::string output{};

		for ( const auto & chunk : list )
		{
			output.append(chunk);
		}

		return output;
	}

	std::string
	toUpper (const std::string & source) noexcept
	{
		std::string output{};

		const auto length = source.size();

		output.resize(length);

		for ( size_t i = 0; i < length; ++i )
		{
			output[i] = static_cast< char >(std::toupper(source[i]));
		}

		return output;
	}

	std::string
	toLower (const std::string & source) noexcept
	{
		std::string output{};

		const auto length = source.size();

		output.resize(length);

		for ( size_t i = 0; i < length; ++i )
		{
			output[i] = static_cast< char >(std::tolower(source[i]));
		}

		return output;
	}

	std::string
	ucfirst (const std::string & source) noexcept
	{
		std::string output{source};

		output[0] = static_cast< char >(std::toupper(output[0]));

		return output;
	}

	std::string
	replace (const std::string & search, const std::string & replace, const std::string & input, size_t limit) noexcept
	{
		std::string output{input};

		size_t count = 0;
		size_t pos = 0;

		while ( ( pos = output.find(search, pos) ) != std::string::npos )
		{
			output.replace(pos, search.length(), replace);

			pos += replace.length();

			if ( limit == 0 )
			{
				continue;
			}

			count++;

			if ( limit >= count )
			{
				break;
			}
		}

		return output;
	}

	std::string
	removeChars (const std::string & source, char character) noexcept
	{
		std::string output{};
		output.reserve(source.size());

		for ( auto inputCharacter : source )
		{
			if ( inputCharacter == character )
			{
				continue;
			}

			output += inputCharacter;
		}

		return output;
	}

	std::string
	removeChars (const std::string & source, const std::string & characters) noexcept
	{
		std::string output{};
		output.reserve(source.size());

		for ( auto inputCharacter : source )
		{
			auto characterFound = std::any_of(characters.cbegin(), characters.cend(), [inputCharacter](auto character) {
				return inputCharacter == character;
			});

			if ( characterFound )
			{
				continue;
			}

			output += inputCharacter;
		}

		return output;
	}

	std::string
	removeFileExtension (const std::string & input) noexcept
	{
		const auto position = input.find_last_of('.');

		if ( position != std::string::npos )
		{
			return input.substr(0, position);
		}

		return input;
	}

	std::string
	extractFilename (const std::string & input) noexcept
	{
		const auto position = input.find_last_of('/');

		if ( position != std::string::npos )
		{
			return input.substr(position + 1);
		}

		return {};
	}

	std::string
	extractNumbers (const char * input) noexcept
	{
		std::string output{};

		const auto stringLength = std::strlen(input);

		output.reserve(stringLength);

		auto needSpace = false;

		for ( size_t i = 0; i < stringLength; i++ )
		{
			const auto chr = input[i]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

			switch ( chr )
			{
				case '0' :
				case '1' :
				case '2' :
				case '3' :
				case '4' :
				case '5' :
				case '6' :
				case '7' :
				case '8' :
				case '9' :
				case '.' :
					output += chr;

					needSpace = true;
					break;

				default :
					if ( needSpace )
					{
						output += ' ';

						needSpace = false;
					}
					break;
			}
		}

		return trim(output);
	}

	bool
	toBool (std::string value) noexcept
	{
		value = toLower(value);

		if ( value == "false" )
		{
			return false;
		}

		if ( value == "off" )
		{
			return false;
		}

		if ( value == "none" )
		{
			return false;
		}

		if ( value == "0" )
		{
			return false;
		}

		return true;
	}

	std::string
	left (const std::string & source, const std::string & match) noexcept
	{
		const auto pos = source.find(match);

		if ( pos == std::string::npos )
		{
			return {};
		}

		return source.substr(0, pos);
	}

	std::string
	right (const std::string & source, const std::string & match) noexcept
	{
		const auto pos = source.find(match);

		if ( pos == std::string::npos )
		{
			return {};
		}

		return source.substr(pos + match.size());
	}

	bool
	contains (const std::string & source, const std::string & piece) noexcept
	{
		return source.find(piece) != std::string::npos;
	}

	// NOLINTBEGIN(*-magic-numbers)
	std::string
	unicodeToUTF8 (unsigned int unicode) noexcept
	{
		std::string utf8{};

		if ( unicode <= 0x7f )
		{
			utf8.append(1, static_cast< char >(unicode));
		}
		else if (unicode <= 0x7ff)
		{
			utf8.append(1, static_cast< char >(0xc0 | ((unicode >> 6) & 0x1f)));
			utf8.append(1, static_cast< char >(0x80 | (unicode & 0x3f)));
		}
		else if (unicode <= 0xffff)
		{
			utf8.append(1, static_cast< char >(0xe0 | ((unicode >> 12) & 0x0f)));
			utf8.append(1, static_cast< char >(0x80 | ((unicode >> 6) & 0x3f)));
			utf8.append(1, static_cast< char >(0x80 | (unicode & 0x3f)));
		}
		else
		{
			utf8.append(1, static_cast< char >(0xf0 | ((unicode >> 18) & 0x07)));
			utf8.append(1, static_cast< char >(0x80 | ((unicode >> 12) & 0x3f)));
			utf8.append(1, static_cast< char >(0x80 | ((unicode >> 6) & 0x3f)));
			utf8.append(1, static_cast< char >(0x80 | (unicode & 0x3f)));
		}

		return utf8;
	}
	// NOLINTEND(*-magic-numbers)

	std::vector< std::string >
	extractTags (const std::string & input, const std::array< char, 2 > & delimiters) noexcept
	{
		std::vector< std::string > list{};

		size_t lastOffset = 0;

		while ( true )
		{
			const auto startPos = input.find_first_of(delimiters[0], lastOffset);

			if ( startPos == std::string::npos )
			{
				break;
			}

			lastOffset = input.find_first_of(delimiters[1], startPos);

			if ( lastOffset == std::string::npos )
			{
				break;
			}

			const auto offset = startPos + 1;

			list.emplace_back(input.substr(offset, lastOffset - offset));
		}

		return list;
	}
}
