/*
 * src/Libraries/FastJSON.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "FastJSON.hpp"

/* STL inclusions. */
#include <fstream>
#include <iostream>
#include <string>

namespace Libraries::FastJSON
{
	bool
	getRootFromFile (const std::filesystem::path & filepath, Json::Value & root, int stackLimit, bool quiet) noexcept
	{
		Json::CharReaderBuilder builder{};
		builder["collectComments"] = false;
		builder["allowComments"] = false;
		builder["allowTrailingCommas"] = false;
		builder["strictRoot"] = true;
		builder["allowDroppedNullPlaceholders"] = false;
		builder["allowNumericKeys"] = false;
		builder["allowSingleQuotes"] = false;
		builder["stackLimit"] = stackLimit;
		builder["failIfExtra"] = true;
		builder["rejectDupKeys"] = true;
		builder["allowSpecialFloats"] = true;
		builder["skipBom"] = true;

		std::ifstream json{filepath, std::ifstream::binary};

		if ( !json.is_open() )
		{
			if ( !quiet )
			{
				std::cerr << "Unable to open the file " << filepath << " !" "\n";
			}

			return false;
		}

		std::string errors;

		if ( !parseFromStream(builder, json, &root, &errors) )
		{
			if ( !quiet )
			{
				std::cerr << "Unable to parse JSON file " << filepath << " ! Errors :" "\n" << errors << "\n";
			}

			root = Json::nullValue;

			return false;
		}

		return true;
	}

	bool
	getRootFromString (const std::string & json, Json::Value & root, int stackLimit, bool quiet) noexcept
	{
		Json::CharReaderBuilder builder{};
		builder["collectComments"] = false;
		builder["allowComments"] = false;
		builder["allowTrailingCommas"] = false;
		builder["strictRoot"] = true;
		builder["allowDroppedNullPlaceholders"] = false;
		builder["allowNumericKeys"] = false;
		builder["allowSingleQuotes"] = false;
		builder["stackLimit"] = stackLimit;
		builder["failIfExtra"] = true;
		builder["rejectDupKeys"] = true;
		builder["allowSpecialFloats"] = true;
		builder["skipBom"] = true;

		Json::CharReader * reader = builder.newCharReader();

		std::string errors;

		if ( !reader->parse(json.data(), json.data() + json.size(), &root, &errors) )
		{
			if ( !quiet )
			{
				std::cerr << "Unable to parse JSON from a string ! Errors :" "\n" << errors << "\n";
			}

			root = Json::nullValue;

			return false;
		}

		return true;
	}

	std::string
	stringify (const Json::Value & root) noexcept
	{
		Json::StreamWriterBuilder builder{};
		builder["commentStyle"] = "None";
		builder["indentation"] = "";
		builder["enableYAMLCompatibility"] = false;
		builder["dropNullPlaceholders"] = false;
		builder["useSpecialFloats"] = false;
		builder["precision"] = 5;
		builder["precisionType"] = "significant";
		builder["emitUTF8"] = true;

		return Json::writeString(builder, root);
	}

	bool
	getArray (const Json::Value & data, const char * JSONKey, Json::Value & array) noexcept
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return false;
		}

		array = data[JSONKey];

		if ( !array.isArray() )
		{
			std::cerr << "The key '" << JSONKey << "' is not an array !" "\n";

			return false;
		}

		return true;
	}

	bool
	getObject (const Json::Value & data, const char * JSONKey, Json::Value & object) noexcept
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return false;
		}

		object = data[JSONKey];

		if ( !object.isObject() )
		{
			std::cerr << "The key '" << JSONKey << "' is not an object !" "\n";

			return false;
		}

		return true;
	}

	bool
	getBoolean (const Json::Value & data, const char * JSONKey) noexcept
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return false;
		}

		if ( !data[JSONKey].isBool() )
		{
			std::cerr << "The key '" << JSONKey << "' is not a boolean !" "\n";

			return false;
		}

		return data[JSONKey].asBool();
	}

	bool
	getBoolean (const Json::Value & data, const char * JSONKey, bool defaultValue) noexcept
	{
		return data.isMember(JSONKey) && data[JSONKey].isBool() ? data[JSONKey].asBool() : defaultValue;
	}

	std::string
	getString (const Json::Value & data, const char * JSONKey) noexcept
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return {};
		}

		if ( !data[JSONKey].isString() )
		{
			std::cerr << "The key '" << JSONKey << "' is not a string !" "\n";

			return {};
		}

		return data[JSONKey].asString();
	}

	std::string
	getString (const Json::Value & data, const char * JSONKey, const std::string & defaultValue) noexcept
	{
		return data.isMember(JSONKey) && data[JSONKey].isString() ? data[JSONKey].asString() : defaultValue;
	}
}
