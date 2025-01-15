/*
 * src/PlatformSpecific/UserInfo.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "UserInfo.hpp"

/* STL inclusions. */
#include <sstream>

namespace Emeraude::PlatformSpecific
{
	std::ostream &
	operator<< (std::ostream & out, const UserInfo & obj)
	{
		if ( !obj.informationFound() )
		{
			return out << "User information : Not found !" "\n";
		}

		out <<
			"User information :" "\n"
			"Account : " << obj.accountName() << "\n"
			"Name : " << obj.name() << "\n"
			"Home : " << obj.homePath() << "\n";

		return out;
	}

	std::string
	to_string (const UserInfo & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
