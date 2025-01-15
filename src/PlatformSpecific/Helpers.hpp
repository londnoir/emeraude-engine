/*
 * src/PlatformSpecific/Helpers.hpp
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

/* Project configuration files. */
#include "platform.hpp"

#if IS_LINUX

namespace Emeraude::PlatformSpecific
{

}

#elif IS_MACOS

namespace Emeraude::PlatformSpecific
{

}

#elif IS_WINDOWS

/* STL inclusions. */
#include <string>

/* Third-party inclusions. */
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>

namespace Emeraude::PlatformSpecific
{
	/**
	 * @brief Returns a value in a wide string from the Windows register.
	 * @param regSubKey A reference to a wide string.
	 * @param regValue A reference to a wide string.
	 * @return std::wstring
	 */
	[[nodiscard]]
	std::wstring getStringValueFromHKLM (const std::wstring & regSubKey, const std::wstring & regValue);

	/**
	 * @brief Converts a wide string to an ASCII string.
	 * @param input A reference to a wide string.
	 * @return std::string
	 */
	std::string
	convertWideToANSI (const std::wstring & input);

	/**
	 * @brief Converts an ASCII string to a wide string.
	 * @param input A reference to a string.
	 * @return std::string
	 */
	std::wstring
	convertANSIToWide (const std::string & input);

	/**
	 * @brief Converts a wide string to a UTF-8 string.
	 * @param input A reference to a wide string.
	 * @return std::string
	 */
	std::string
	convertWideToUTF8 (const std::wstring & input);

	/**
	 * @brief Converts a UTF-8 string to a wide string.
	 * @param input A reference to a string.
	 * @return std::string
	 */
	std::wstring
	convertUTF8ToWide (const std::string & input);

	/**
	 * @brief Displays a console.
	 * @warning Used only for Windows OS since the logs are displayed in their own process.
	 * @param title A reference to a string.
	 * @return void
	 */
	bool createConsole (const std::string & title);

	/**
	 * @brief Returns the parent process ID on Windows.
	 * @return int
	 */
	[[nodiscard]]
	int getParentProcessId (DWORD pid) noexcept;
}

#endif
