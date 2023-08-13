/*
 * Libraries/FastJSON.cpp
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

#include "FastJSON.hpp"

/* C/C++ standard libraries. */
#include <iostream>

namespace Libraries::FastJSON
{
	bool
	checkNumericalValue (const Json::Value & data, const char * JSONKey) noexcept
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return false;
		}

		if ( !data[JSONKey].isNumeric() )
		{
			std::cerr << "The key '" << JSONKey << "' is not numeric !" "\n";

			return false;
		}

		return true;
	}

	Json::Value
	getRootFromFile (const Path::File & filepath) noexcept
	{
		const Json::CharReaderBuilder builder{};

		std::ifstream json{to_string(filepath), std::ifstream::binary};

		Json::Value root{};

		std::string errors{};

		if ( !Json::parseFromStream(builder, json, &root, &errors) )
		{
			std::cerr << "Unable to parse JSON file " << filepath << " ! Errors :" "\n" << errors << "\n";

			return Json::nullValue;
		}

		return root;
	}

	int
	getInteger (const Json::Value & data, const char * JSONKey, int defaultValue) noexcept
	{
		if ( !checkNumericalValue(data, JSONKey) )
		{
			return defaultValue;
		}

		return data[JSONKey].asInt();
	}

	unsigned int
	getUnsignedInteger (const Json::Value & data, const char * JSONKey, unsigned int defaultValue) noexcept
	{
		if ( !checkNumericalValue(data, JSONKey) )
		{
			return defaultValue;
		}

		return data[JSONKey].asUInt();
	}

	float
	getFloat (const Json::Value & data, const char * JSONKey, float defaultValue) noexcept
	{
		if ( !checkNumericalValue(data, JSONKey) )
		{
			return defaultValue;
		}

		return data[JSONKey].asFloat();
	}

	double
	getDouble (const Json::Value & data, const char * JSONKey, double defaultValue) noexcept
	{
		if ( !checkNumericalValue(data, JSONKey) )
		{
			return defaultValue;
		}

		return data[JSONKey].asDouble();
	}

	bool
	getBoolean(const Json::Value & data, const char * JSONKey, bool defaultValue) noexcept
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return defaultValue;
		}

		if ( !data[JSONKey].isBool() )
		{
			std::cerr << "The key '" << JSONKey << "' is not a boolean !" "\n";

			return defaultValue;
		}

		return data[JSONKey].asBool();
	}

	std::string
	getString(const Json::Value & data, const char * JSONKey, const std::string & defaultValue) noexcept
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return defaultValue;
		}

		if ( !data[JSONKey].isString() )
		{
			std::cerr << "The key '" << JSONKey << "' is not a string !" "\n";

			return defaultValue;
		}

		return data[JSONKey].asString();
	}
}
