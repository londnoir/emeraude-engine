/*
 * Emeraude/Input/GamepadController.cpp
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

#include "GamepadController.hpp"

/* C/C++ standard libraries. */
#include <cmath>
#include <sstream>

/* Local inclusion */
#include "Tracer.hpp"

namespace Emeraude::Input
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
	constexpr auto TracerTag{"GamepadController"};

	std::array< GLFWgamepadstate, 16 > GamepadController::s_devicesState{}; // NOLINT NOTE: Special state copy.

	GamepadController::GamepadController (int deviceID) noexcept
		: m_deviceID(deviceID)
	{

	}

	bool
	GamepadController::isConnected () const noexcept
	{
		return m_deviceID > -1;
	}

	int
	GamepadController::deviceID () const noexcept
	{
		return m_deviceID;
	}

	void
	GamepadController::attachDeviceID (int deviceID) noexcept
	{
		m_deviceID = deviceID;
	}

	void
	GamepadController::setAxisThreshold (float value) noexcept
	{
		m_threshold = std::abs(value);
	}

	void
	GamepadController::setAxisSensitivity (float multiplier) noexcept
	{
		m_multiplier = std::abs(multiplier);
	}

	float
	GamepadController::axisThreshold () const noexcept
	{
		return m_threshold;
	}

	float
	GamepadController::axisSensitivity () const noexcept
	{
		return m_multiplier;
	}

	bool
	GamepadController::isButtonPressed (GamepadButton button) const noexcept
	{
		if ( m_deviceID < 0 )
		{
			return false;
		}

		return s_devicesState[m_deviceID].buttons[button] == GLFW_PRESS;
	}

	bool
	GamepadController::isButtonReleased (GamepadButton button) const noexcept
	{
		if ( m_deviceID < 0 )
		{
			return true;
		}

		return s_devicesState[m_deviceID].buttons[button] == GLFW_PRESS;
	}

	float
	GamepadController::axeValue (GamepadAxis axe) const noexcept
	{
		if ( m_deviceID > -1 )
		{
			const auto value = s_devicesState[m_deviceID].axes[axe];

			if ( value > m_threshold || value < -m_threshold )
			{
				return value * m_multiplier;
			}
		}

		return 0.0F;
	}

	std::string
	GamepadController::getRawState () const noexcept
	{
		std::stringstream output{};

		output << "Gamepad #" << m_deviceID << " mapping." "\n";

		for ( auto i = 0U; i < GLFW_GAMEPAD_BUTTON_LAST; i++ )
		{
			output << "Button #" << i << " : " << ( s_devicesState[m_deviceID].buttons[i] > 0 ? "Pressed" : "Released" ) << "\n";
		}

		for ( auto i = 0U; i < GLFW_GAMEPAD_AXIS_LAST; i++ )
		{
			output << "Axe #" << i << " : " << s_devicesState[m_deviceID].axes[i] << "\n";
		}

		return output.str();
	}

	void
	GamepadController::readDeviceState (GLFWwindow * /*handle*/, int deviceID) noexcept
	{
		if ( glfwGetGamepadState(deviceID, &s_devicesState[deviceID]) == GLFW_FALSE )
		{
			TraceError{TracerTag} << "Gamepad device #" << deviceID << " is not connected !";
		}
	}

	void
	GamepadController::clearDeviceState (int deviceID) noexcept
	{
		for ( auto & button : s_devicesState[deviceID].buttons )
		{
			button = 0;
		}

		for ( auto & axe : s_devicesState[deviceID].axes )
		{
			axe = 0.0F;
		}
	}

	// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
}
