/*
 * src/PlatformSpecific/Desktop/Commands.hpp
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

/* Project configuration files. */
#include "platform.hpp"

/* STL inclusions. */
#include <string>
#include <filesystem>

namespace Emeraude::PlatformSpecific::Desktop
{
	/**
	 * @brief Tries to open a URL in an external web browser.
	 * @param url A reference to a string.
	 * @return bool
	 */
	bool openURL (const std::string & url) noexcept;

	/**
	 * @brief Tries to open a file in an external program.
	 * @param filepath A reference to a path.
	 * @return bool
	 */
	bool openFile (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Tries to open a folder in an external program.
	 * @param filepath A reference to a path.
	 * @return bool
	 */
	bool openFolder (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Tries to open the directory of a file in an external file browser.
	 * @param filepath A reference to a path.
	 * @return bool
	 */
	bool showInFolder (const std::filesystem::path & filepath) noexcept;

	/**
	 * @brief Tries to open the directory of a file in an external file browser.
	 * @param argument A reference to a string.
	 * @return void
	 */
	void runDesktopApplication (const std::string & argument) noexcept;
}
