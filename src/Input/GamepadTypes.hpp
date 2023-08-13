/*
 * Emeraude/Input/GamepadTypes.hpp
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

namespace Emeraude::Input
{
	enum GamepadAxis
	{
		AxisLeftX = 0,
		AxisLeftY = 1,
		AxisRightX = 2,
		AxisRightY = 3,
		AxisLeftTrigger = 4,
		AxisRightTrigger = 5
	};

	static constexpr auto AxisLeftXString = "AxisLeftX";
	static constexpr auto AxisLeftYString = "AxisLeftY";
	static constexpr auto AxisRightXString = "AxisRightX";
	static constexpr auto AxisRightYString = "AxisRightY";
	static constexpr auto AxisLeftTriggerString = "AxisLeftTrigger";
	static constexpr auto AxisRightTriggerString = "AxisRightTrigger";

	/**
	 * @brief Returns a C-String version of the enum value.
	 * @param value The enum value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (GamepadAxis type) noexcept;

	[[nodiscard]]
	inline
	std::string
	to_string (GamepadAxis type) noexcept
	{
		return {to_cstring(type)};
	}

	enum GamepadButton
	{
		ButtonA = 0, //GLFW_GAMEPAD_BUTTON_A,
		ButtonB = 1, //GLFW_GAMEPAD_BUTTON_B,
		ButtonX = 2, //GLFW_GAMEPAD_BUTTON_X,
		ButtonY = 3, //GLFW_GAMEPAD_BUTTON_Y,
		ButtonLeftBumper = 4, //GLFW_GAMEPAD_BUTTON_LEFT_BUMPER,
		ButtonRightBumper = 5, //GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER,
		ButtonBack = 6, //GLFW_GAMEPAD_BUTTON_BACK,
		ButtonStart = 7, //GLFW_GAMEPAD_BUTTON_START,
		ButtonGuide = 8, //GLFW_GAMEPAD_BUTTON_GUIDE,
		ButtonLeftThumb = 9, //GLFW_GAMEPAD_BUTTON_LEFT_THUMB,
		ButtonRightThumb = 10, //GLFW_GAMEPAD_BUTTON_RIGHT_THUMB,
		ButtonDPadUp = 11, //GLFW_GAMEPAD_BUTTON_DPAD_UP,
		ButtonDPadRight = 12, //GLFW_GAMEPAD_BUTTON_DPAD_RIGHT,
		ButtonDPadDown = 13, //GLFW_GAMEPAD_BUTTON_DPAD_DOWN,
		ButtonDPadLeft = 14 //GLFW_GAMEPAD_BUTTON_DPAD_LEFT,
	};

	static constexpr auto ButtonAString = "ButtonA";
	static constexpr auto ButtonBString = "ButtonB";
	static constexpr auto ButtonXString = "ButtonX";
	static constexpr auto ButtonYString = "ButtonY";
	static constexpr auto ButtonLeftBumperString = "ButtonLeftBumper";
	static constexpr auto ButtonRightBumperString = "ButtonRightBumper";
	static constexpr auto ButtonBackString = "ButtonBack";
	static constexpr auto ButtonStartString = "ButtonStart";
	static constexpr auto ButtonGuideString = "ButtonGuide";
	static constexpr auto ButtonLeftThumbString = "ButtonLeftThumb";
	static constexpr auto ButtonRightThumbString = "ButtonRightThumb";
	static constexpr auto ButtonDPadUpString = "ButtonDPadUp";
	static constexpr auto ButtonDPadRightString = "ButtonDPadRight";
	static constexpr auto ButtonDPadDownString = "ButtonDPadDown";
	static constexpr auto ButtonDPadLeftString = "ButtonDPadLeft";

	/**
	 * @brief Returns a C-String version of the enum value.
	 * @param value The enum value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (GamepadButton type) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (GamepadButton type) noexcept
	{
		return {to_cstring(type)};
	}
}
