/*
 * Emeraude/Input/PointerTypes.cpp
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

#include "PointerTypes.hpp"

namespace Emeraude::Input
{
	const char *
	to_cstring (MouseButton type) noexcept
	{
		switch ( type )
		{
			case Button1Left :
				return Button1LeftString;

			case Button2Right :
				return Button2RightString;

			case Button3Middle :
				return Button3MiddleString;

			case Button4Extra :
				return Button4ExtraString;

			case Button5Extra :
				return Button5ExtraString;

			case Button6Extra :
				return Button6ExtraString;

			case Button7Extra :
				return Button7ExtraString;

			case Button8Extra :
				return Button8ExtraString;
		}

		return nullptr;
	}
}
