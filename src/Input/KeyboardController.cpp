/*
 * Emeraude/Input/KeyboardController.cpp
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

#include "KeyboardController.hpp"

/* C/C++ standard libraries. */
#include <algorithm>
#include <sstream>

namespace Emeraude::Input
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
	constexpr auto TracerTag{"KeyboardController"};

	std::array< bool, 349 > KeyboardController::s_deviceState{}; // NOLINT NOTE: Special state copy.

	bool
	KeyboardController::isConnected () const noexcept
	{
		return true;
	}

	bool
	KeyboardController::isKeyPressed (int key) const noexcept
	{
		if ( key == KeyUnknown )
		{
			return false;
		}

		return s_deviceState[static_cast< size_t >(key)];
	}

	bool
	KeyboardController::isAnyKeyPressed () const noexcept
	{
		return std::any_of(s_deviceState.cbegin(), s_deviceState.cend(), [] (auto state) {
			return state;
		});
	}

	bool
	KeyboardController::isKeyReleased (int key) const noexcept
	{
		if ( key == KeyUnknown )
		{
			return true;
		}

		return !s_deviceState[static_cast< size_t >(key)];
	}

	std::string
	KeyboardController::getRawState () const noexcept
	{
		std::stringstream output{};

		output << "Keyboard mapping." "\n";

		for ( int key = GLFW_KEY_SPACE; key < GLFW_KEY_LAST + 1; key++ )
		{
			output << "Key #" << key << " : " << s_deviceState[static_cast< size_t >(key)] << '\n';
		}

		return output.str();
	}

	void
	KeyboardController::readDeviceState (GLFWwindow * window) noexcept
	{
		for ( auto key = GLFW_KEY_SPACE; key < GLFW_KEY_LAST + 1; key++ )
		{
			s_deviceState[static_cast< size_t >(key)] = ( glfwGetKey(window, key) == GLFW_PRESS );
		}
	}
	// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
}
