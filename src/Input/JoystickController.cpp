/*
 * Emeraude/Input/JoystickController.cpp
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

#include "JoystickController.hpp"

/* C/C++ standard libraries. */
#include <cmath>
#include <iostream>
#include <sstream>

namespace Emeraude::Input
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
	constexpr auto TracerTag{"JoystickController"};

	std::array< JoystickState, 16 > JoystickController::s_devicesState{}; // NOLINT NOTE: Special state copy.

	JoystickController::JoystickController (int deviceID) noexcept
		: m_deviceID(deviceID)
	{

	}

	bool
	JoystickController::isConnected () const noexcept
	{
		return m_deviceID > -1;
	}

	int
	JoystickController::deviceID () const noexcept
	{
		return m_deviceID;
	}

	void
	JoystickController::attachDeviceID (int deviceID) noexcept
	{
		m_deviceID = deviceID;
	}

	void
	JoystickController::setAxisThreshold (float value) noexcept
	{
		m_threshold = std::abs(value);
	}

	void
	JoystickController::setAxisSensitivity (float multiplier) noexcept
	{
		m_multiplier = std::abs(multiplier);
	}

	float
	JoystickController::axisThreshold () const noexcept
	{
		return m_threshold;
	}

	float
	JoystickController::axisSensitivity () const noexcept
	{
		return m_multiplier;
	}

	float
	JoystickController::axeValue (JoystickAxis axeIndex) const noexcept
	{
		if ( m_deviceID > -1 )
		{
			auto value = s_devicesState[m_deviceID].axes[axeIndex];

			if ( value > m_threshold || value < -m_threshold )
			{
				return value * m_multiplier;
			}
		}

		return 0.0F;
	}

	bool
	JoystickController::isButtonPressed (int buttonNum) const noexcept
	{
#ifdef DEBUG
		if ( static_cast< size_t >(buttonNum) > JoystickMaxButtons )
		{
			std::cerr << "Buttons limit is " << JoystickMaxButtons << " !" "\n";

			return false;
		}
#endif
		if ( m_deviceID < 0 )
		{
			return false;
		}

		return s_devicesState[m_deviceID].buttons[buttonNum];
	}

	bool
	JoystickController::isButtonReleased (int buttonNum) const noexcept
	{
#ifdef DEBUG
		if ( static_cast< size_t >(buttonNum) > JoystickMaxButtons )
		{
			std::cerr << "Buttons limit is " << JoystickMaxButtons << " !" "\n";

			return true;
		}
#endif

		if ( m_deviceID < 0 )
		{
			return true;
		}

		return !s_devicesState[m_deviceID].buttons[buttonNum];
	}

	JoystickHatDirection
	JoystickController::hatValue (int hatNum) const noexcept
	{
#ifdef DEBUG
		if ( static_cast< size_t >(hatNum) > JoystickMaxHats )
		{
			std::cerr << "Hats limit is " << JoystickMaxHats << " !" "\n";

			return Center;
		}
#endif
		if ( m_deviceID < 0 )
		{
			return Center;
		}

		return s_devicesState[m_deviceID].hats[hatNum];
	}

	std::string
	JoystickController::getRawState () const noexcept
	{
		std::stringstream output{};

		output << "Joystick #" << m_deviceID << " mapping." "\n";

		for ( int index = 0; index < JoystickMaxAxis; index++ )
		{
			output << "Axe #" << index << " : " << s_devicesState[m_deviceID].axes[index] << '\n';
		}

		for ( int index = 0; index < JoystickMaxButtons; index++ )
		{
			output << "Button #" << index << " : " << (s_devicesState[m_deviceID].buttons[index] ? "Pressed" : "Released") << '\n';
		}

		for ( int index = 0; index < JoystickMaxHats; index++ )
		{
			output << "Hat #" << index << " : " << s_devicesState[m_deviceID].hats[index] << '\n';
		}

		return output.str();
	}

	void
	JoystickController::readDeviceState (GLFWwindow *, int deviceID) noexcept
	{
		int count = 0;

		const auto * axes = glfwGetJoystickAxes(deviceID, &count);

		for ( int index = 0; index < std::min(count, JoystickMaxAxis); index++ )
		{
			s_devicesState[deviceID].axes[index] = axes[index];
		}

		const auto * buttons = glfwGetJoystickButtons(deviceID, &count);

		for ( int index = 0; index < std::min(count, JoystickMaxButtons); index++ )
		{
			s_devicesState[deviceID].buttons[index] = (buttons[index] == GLFW_PRESS);
		}

		buttons = glfwGetJoystickHats(deviceID, &count);

		for ( int index = 0; index < std::min(count, JoystickMaxHats); index++ )
		{
			s_devicesState[deviceID].hats[index] = static_cast< JoystickHatDirection >(buttons[index]);
		}
	}

	void
	JoystickController::clearDeviceState (int deviceID) noexcept
	{
		for ( int index = 0; index < JoystickMaxAxis; index++ )
		{
			s_devicesState[deviceID].axes[index] = 0.0F;
		}

		for ( int index = 0; index <  JoystickMaxButtons; index++ )
		{
			s_devicesState[deviceID].buttons[index] = false;
		}

		for ( int index = 0; index < JoystickMaxHats; index++ )
		{
			s_devicesState[deviceID].hats[index] = Center;
		}
	}
	// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index, cppcoreguidelines-pro-bounds-array-to-pointer-decay)
}
