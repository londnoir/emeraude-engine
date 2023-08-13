/*
 * Emeraude/Input/PointerController.cpp
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

#include "PointerController.hpp"

/* C/C++ standard libraries. */
#include <algorithm>
#include <sstream>

namespace Emeraude::Input
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index, cppcoreguidelines-pro-bounds-array-to-pointer-decay)

	std::array< bool, 8 > PointerController::s_deviceState{false, false, false, false, false, false, false, false}; // NOLINT NOTE: Special state copy.
	std::array< double, 2 > PointerController::s_pointerPosition{0.0, 0.0}; // NOLINT NOTE: Special state copy.

	bool
	PointerController::isConnected () const noexcept
	{
		return true;
	}

	bool
	PointerController::isButtonPressed (MouseButton button) const noexcept
	{
		return s_deviceState[static_cast< size_t >(button)];
	}

	bool
	PointerController::isAnyButtonPressed () const noexcept
	{
		return std::any_of(s_deviceState.cbegin(), s_deviceState.cend(), [] (auto state) {
			return state;
		});
	}

	bool
	PointerController::isButtonReleased (MouseButton button) const noexcept
	{
		return !s_deviceState[static_cast< size_t >(button)];
	}

	double
	PointerController::xPosition () const noexcept
	{
		return s_pointerPosition[0];
	}

	double
	PointerController::yPosition () const noexcept
	{
		return s_pointerPosition[1];
	}

	std::string
	PointerController::getRawState () const noexcept
	{
		std::stringstream output{};

		output << "Pointer mapping." "\n";

		for ( auto key = GLFW_MOUSE_BUTTON_1; key < GLFW_MOUSE_BUTTON_LAST + 1; key++ )
		{
			output << "Button #" << key << " : " << ( s_deviceState[static_cast< size_t >(key)] ? "Pressed" : "Released" ) << '\n';
		}

		output << "Pointer position X: " << s_pointerPosition[0] << ", Y: " << s_pointerPosition[1] << "." "\n";

		return output.str();
	}

	void
	PointerController::readDeviceState (GLFWwindow * window) noexcept
	{
		for ( auto key = GLFW_MOUSE_BUTTON_1; key < GLFW_MOUSE_BUTTON_LAST + 1; key++ )
		{
			s_deviceState[static_cast< size_t >(key)] = (glfwGetMouseButton(window, key) == GLFW_PRESS);
		}

		glfwGetCursorPos(window, &s_pointerPosition[0], &s_pointerPosition[1]);
	}

	// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
}
