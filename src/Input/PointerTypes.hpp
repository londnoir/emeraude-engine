/*
 * Emeraude/Input/PointerTypes.hpp
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
	enum MouseButton
	{
		Button1Left = 0, //GLFW_MOUSE_BUTTON_1 or GLFW_MOUSE_BUTTON_LEFT,
		Button2Right = 1, //GLFW_MOUSE_BUTTON_2 or GLFW_MOUSE_BUTTON_RIGHT,
		Button3Middle = 2, //GLFW_MOUSE_BUTTON_3 or GLFW_MOUSE_BUTTON_MIDDLE,
		Button4Extra = 3, //GLFW_MOUSE_BUTTON_4,
		Button5Extra = 4, //GLFW_MOUSE_BUTTON_5,
		Button6Extra = 5, //GLFW_MOUSE_BUTTON_6,
		Button7Extra = 6, //GLFW_MOUSE_BUTTON_7,
		Button8Extra = 7, //GLFW_MOUSE_BUTTON_8
	};

	static constexpr auto Button1LeftString = "Button1Left";
	static constexpr auto Button2RightString = "Button2Right";
	static constexpr auto Button3MiddleString = "Button3Middle";
	static constexpr auto Button4ExtraString = "Button4Extra";
	static constexpr auto Button5ExtraString = "Button5Extra";
	static constexpr auto Button6ExtraString = "Button6Extra";
	static constexpr auto Button7ExtraString = "Button7Extra";
	static constexpr auto Button8ExtraString = "Button8Extra";

	/**
	 * @brief Returns a C-String version of the enum value.
	 * @param value The enum value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (MouseButton type) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (MouseButton type) noexcept
	{
		return {to_cstring(type)};
	}
}
