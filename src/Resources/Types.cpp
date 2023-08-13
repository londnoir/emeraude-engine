/*
 * Emeraude/Resources/Types.cpp
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

#include "Types.hpp"

/* C/C++ standard libraries */
#include <iostream>

namespace Emeraude::Resources
{
	const char *
	to_cstring (SourceType enumeration) noexcept
	{
		switch ( enumeration )
		{
			case SourceType::Undefined :
				return UndefinedString;

			case SourceType::LocalData :
				return LocalDataString;

			case SourceType::ExternalData :
				return ExternalDataString;

			case SourceType::DirectData :
				return DirectDataString;
		}

		return UndefinedString;
	}

	SourceType
	to_SourceType (const std::string & string) noexcept
	{
		if ( string == LocalDataString )
			return SourceType::LocalData;

		if ( string == ExternalDataString )
			return SourceType::ExternalData;

		if ( string == DirectDataString )
			return SourceType::DirectData;

		std::cerr << __PRETTY_FUNCTION__ << ", unknown " << string << " source type. Return Undefined by default !" << std::endl;

		return SourceType::Undefined;
	}
}
