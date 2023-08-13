/*
 * Emeraude/Types.hpp
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

/* C/C++ standards libraries */
#include <cstdint>
#include <string>

namespace Emeraude
{
	/**
	 * @brief The message severity enumeration.
	 */
	enum class Severity
	{
		Debug,
		Success,
		Info,
		Warning,
		Error,
		Fatal
	};

	static constexpr auto DebugString = "Debug";
	static constexpr auto SuccessString = "Success";
	static constexpr auto InfoString = "Info";
	static constexpr auto WarningString = "Warning";
	static constexpr auto ErrorString = "Error";
	static constexpr auto FatalString = "Fatal";

	/**
	 * @brief Returns a C-String version of the enum value.
	 * @param value The enum value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (Severity value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (Severity value) noexcept
	{
		return {to_cstring(value)};
	}
}
