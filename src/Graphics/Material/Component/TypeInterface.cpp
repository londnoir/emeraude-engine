/*
 * Emeraude/Graphics/Material/Component/TypeInterface.cpp
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

#include "TypeInterface.hpp"

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Graphics::Material::Component
{
	bool
	TypeInterface::parseBase (const Json::Value & data, FillingType & fillingType, Json::Value & componentData) noexcept
	{
		if ( !data.isMember(JKType) || !data[JKType].isString() )
			return false;

		fillingType = to_FillingType(data[JKType].asString());

		if ( !data.isMember(JKData) || !data[JKData].isObject() )
			return false;

		componentData = data[JKData];

		return true;
	}

	bool
	TypeInterface::getComponentAsValue (const Json::Value & data, const char * componentType, float & value) noexcept
	{
		if ( !data.isMember(AutoIlluminationString) )
			return false;

		auto jsonNode = data[AutoIlluminationString];

		if  ( jsonNode.isObject() )
		{
			if ( !jsonNode.isMember(JKType) || !jsonNode[JKType].isString() )
				return false;

			if ( to_FillingType(jsonNode[JKType].asString()) != FillingType::Value )
				return false;

			if ( !jsonNode.isMember(JKData) || !jsonNode[JKData].isObject() )
				return false;

			value = jsonNode[JKData].asFloat();

			return true;
		}

		if ( !jsonNode.isNumeric() )
		{
			TraceError{"TypeInterface"} << "The '" << componentType << "' key in Json structure is not numeric ! ";

			return false;
		}

		value = jsonNode.asFloat();

		return true;
	}
}
