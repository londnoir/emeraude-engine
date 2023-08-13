/*
 * Emeraude/Input/GamepadTypes.cpp
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

#include "GamepadTypes.hpp"

namespace Emeraude::Input
{
	const char *
	to_cstring (GamepadAxis type) noexcept
	{
		switch ( type )
		{
			case AxisLeftX :
				return AxisLeftXString;

			case AxisLeftY :
				return AxisLeftYString;

			case AxisRightX :
				return AxisRightXString;

			case AxisRightY :
				return AxisRightYString;

			case AxisLeftTrigger :
				return AxisLeftTriggerString;

			case AxisRightTrigger :
				return AxisRightTriggerString;
		}

		return nullptr;
	}

	const char *
	to_cstring (GamepadButton type) noexcept
	{
		switch ( type )
		{
			case ButtonA :
				return ButtonAString;

			case ButtonB :
				return ButtonBString;

			case ButtonX :
				return ButtonXString;

			case ButtonY :
				return ButtonYString;

			case ButtonLeftBumper :
				return ButtonLeftBumperString;

			case ButtonRightBumper :
				return ButtonRightBumperString;

			case ButtonBack :
				return ButtonBackString;

			case ButtonStart :
				return ButtonStartString;

			case ButtonGuide :
				return ButtonGuideString;

			case ButtonLeftThumb :
				return ButtonLeftThumbString;

			case ButtonRightThumb :
				return ButtonRightThumbString;

			case ButtonDPadUp :
				return ButtonDPadUpString;

			case ButtonDPadRight :
				return ButtonDPadRightString;

			case ButtonDPadDown :
				return ButtonDPadDownString;

			case ButtonDPadLeft :
				return ButtonDPadLeftString;
		}

		return nullptr;
	}
}
