/*
 * Libraries/Hash/Hash.cpp
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

#include "Hash.hpp"

/* C/C++ standard libraries. */
#include <array>

/* Local inclusions. */
#include "MD5.hpp"
#include "SHA256.hpp"
#include "SHA512.hpp"

namespace Libraries::Hash
{
	// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast, *-magic-numbers)
	std::string
	_toString (const uint8_t * data, size_t size, size_t stringSize) noexcept
	{
		std::string hash(stringSize, '\0');

		for ( size_t i = 0; i < size; i++ )
		{
			sprintf(&hash[i * 2], "%02x", data[i]); // NOLINT(cppcoreguidelines-pro-type-vararg, cppcoreguidelines-pro-bounds-pointer-arithmetic)
		}

		return hash;
	}

	std::string
	md5 (const std::string & input) noexcept
	{
		std::array< uint8_t, 16 > digest{0};

		MD5 hash{};
		hash.update(reinterpret_cast< const uint8_t * >(input.data()), input.size());
		hash.final(digest);

		return _toString(digest.data(), digest.size(), MD5::HashLength);
	}

	std::string
	sha256 (const std::string & input) noexcept
	{
		std::array< uint8_t, 32 > digest{0};

		SHA256 hash{};
		hash.update(reinterpret_cast< const uint8_t * >(input.data()), input.size());
		hash.final(digest);

		return _toString(digest.data(), digest.size(), SHA256::HashLength);
	}

	std::string
	sha512 (const std::string & input) noexcept
	{
		std::array< uint8_t, 64 > digest{0};

		SHA512 hash{};
		hash.update(reinterpret_cast< const uint8_t * >(input.data()), input.size());
		hash.final(digest);

		return _toString(digest.data(), digest.size(), SHA512::HashLength);
	}
	// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast, *-magic-numbers)
}
