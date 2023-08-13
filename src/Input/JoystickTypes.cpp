/*
 * Emeraude/Input/JoystickTypes.cpp
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

#include "JoystickTypes.hpp"

namespace Emeraude::Input
{
	const char *
	to_cstring (JoystickAxis type) noexcept
	{
		switch ( type )
		{
			case AxisX :
				return AxisXString;

			case AxisY :
				return AxisYString;

			case AxisZ :
				return AxisZString;

			case ThrottleA :
				return ThrottleAString;

			case ThrottleB :
				return ThrottleBString;

			case ThrottleC :
				return ThrottleCString;
		}

		return nullptr;
	}

	const char *
	to_cstring (JoystickHatDirection type) noexcept
	{
		switch ( type )
		{
			case Center :
				return CenterString;

			case Up :
				return UpString;

			case Right :
				return RightString;

			case UpRight :
				return UpRightString;

			case Down :
				return DownString;

			case DownRight :
				return DownRightString;

			case Left :
				return LeftString;

			case UpLeft :
				return UpLeftString;

			case DownLeft :
				return DownLeftString;
		}

		return nullptr;
	}
}
