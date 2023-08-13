/*
 * Emeraude/Resources/Types.hpp
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
#include <string>

namespace Emeraude::Resources
{
	/**
	 * @brief The resource source type.
	 */
	enum class SourceType
	{
		Undefined,
		/* Data key will hold the path to a local file. */
		LocalData,
		/* Data key will hold the URL to an external file. */
		ExternalData,
		/* Data key will hold the JSON definition of the resource. */
		DirectData
	};

	static constexpr auto UndefinedString = "Undefined";
	static constexpr auto LocalDataString = "LocalData";
	static constexpr auto ExternalDataString = "ExternalData";
	static constexpr auto DirectDataString = "DirectData";

	/**
	 * @brief Converts a source type enumeration value to the corresponding string.
	 * @param value The enumeration value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (SourceType value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (SourceType value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief Converts a string to a source type enumeration value.
	 * @param value A reference to a string.
	 * @return ComponentType
	 */
	[[nodiscard]]
	SourceType to_SourceType (const std::string & value) noexcept;
}
