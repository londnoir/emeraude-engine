/*
 * Emeraude/Input/JoystickTypes.hpp
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
	/** @brief Joystick axis enumeration */
	enum JoystickAxis
	{
		AxisX = 0,
		AxisY = 1,
		AxisZ = 2,
		ThrottleA = 3,
		ThrottleB = 4,
		ThrottleC = 5
	};

	static constexpr auto AxisXString = "AxisX";
	static constexpr auto AxisYString = "AxisY";
	static constexpr auto AxisZString = "AxisZ";
	static constexpr auto ThrottleAString = "ThrottleA";
	static constexpr auto ThrottleBString = "ThrottleB";
	static constexpr auto ThrottleCString = "ThrottleC";

	/**
	 * @brief Returns a C-String version of the enum value.
	 * @param value The enum value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (JoystickAxis type) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (JoystickAxis type) noexcept
	{
		return {to_cstring(type)};
	}

	enum JoystickHatDirection
	{
		Center = 0,
		Up = 1,
		Right = 2,
		UpRight = 3,
		Down = 4,
		DownRight = 6,
		Left = 8,
		UpLeft = 9,
		DownLeft = 12
	};

	static constexpr auto CenterString = "Center";
	static constexpr auto UpString = "Up";
	static constexpr auto RightString = "Right";
	static constexpr auto UpRightString = "UpRight";
	static constexpr auto DownString = "Down";
	static constexpr auto DownRightString = "DownRight";
	static constexpr auto LeftString = "Left";
	static constexpr auto UpLeftString = "UpLeft";
	static constexpr auto DownLeftString = "DownLeft";

	/**
	 * @brief Returns a C-String version of the enum value.
	 * @param value The enum value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (JoystickHatDirection type) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (JoystickHatDirection type) noexcept
	{
		return {to_cstring(type)};
	}
}
