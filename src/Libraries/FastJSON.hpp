/*
 * src/Libraries/FastJSON.hpp
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

#pragma once

/* STL inclusions. */
#include <cstddef>
#include <iostream>
#include <string>
#include <type_traits>
#include <filesystem>

/* Third-party inclusions. */
#ifndef JSON_USE_EXCEPTION
#define JSON_USE_EXCEPTION 0
#endif
#include "json/json.h"

/* Local inclusions. */
#include "Libraries/Math/Vector.hpp"
#include "Libraries/PixelFactory/Color.hpp"

namespace Libraries::FastJSON
{
	constexpr auto TypeKey{"Type"};
	constexpr auto NameKey{"Name"};
	constexpr auto PositionKey{"Position"};
	constexpr auto OrientationKey{"Orientation"};
	constexpr auto ColorKey{"Color"};
	constexpr auto IntensityKey{"Intensity"};
	constexpr auto DataKey{"Data"};
	constexpr auto PropertiesKey{"Properties"};
	constexpr auto ScaleKey{"Scale"};
	constexpr auto SizeKey{"Size"};
	constexpr auto DivisionKey{"Division"};
	constexpr auto UVMultiplierKey{"UVMultiplier"};
	constexpr auto ModeKey{"Mode"};
	
	/**
	 * @brief Gets the root json node from a filepath.
	 * @param filepath A reference to a filesystem path.
	 * @param root A writable reference to a Json::Value.
	 * @param stackLimit The depth of JSON parsing. Default 16.
	 * @param quiet Do not print console message. Default false.
	 * @return bool
	 */
	[[nodiscard]]
	bool getRootFromFile (const std::filesystem::path & filepath, Json::Value & root, int stackLimit = 16, bool quiet = false) noexcept;

	/**
	 * @brief Gets the root json node from a string.
	 * @param json A reference to a string.
	 * @param root A writable reference to a Json::Value.
	 * @param stackLimit The depth of JSON parsing. Default 16.
	 * @param quiet Do not print console message. Default false.
	 * @return bool
	 */
	[[nodiscard]]
	bool getRootFromString (const std::string & json, Json::Value & root, int stackLimit = 16, bool quiet = false) noexcept;

	/**
	 * @brief Gets a JSON array node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param array A writable reference to a json value.
	 * @return bool
	 */
	[[nodiscard]]
	bool getArray (const Json::Value & data, const char * JSONKey, Json::Value & array) noexcept;

	/**
	 * @brief Gets a JSON object node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param object A writable reference to a json value.
	 * @return bool
	 */
	[[nodiscard]]
	bool getObject (const Json::Value & data, const char * JSONKey, Json::Value & object) noexcept;

	/**
	 * @brief Gets a number from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @return std::string
	 */
	template< typename number_t >
	[[nodiscard]]
	number_t
	getNumber (const Json::Value & data, const char * JSONKey) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return static_cast< number_t >(0);
		}

		if ( !data[JSONKey].isNumeric() )
		{
			std::cerr << "The key '" << JSONKey << "' is not numeric !" "\n";

			return static_cast< number_t >(0);
		}

		if constexpr ( std::is_same_v< number_t, int8_t > || std::is_same_v< number_t, int16_t> || std::is_same_v< number_t, int32_t > )
		{
			return static_cast< number_t >(data[JSONKey].asInt());
		}

		if constexpr ( std::is_same_v< number_t, int64_t > )
		{
			return data[JSONKey].asInt64();
		}

		if constexpr ( std::is_same_v< number_t, uint8_t > || std::is_same_v< number_t, uint16_t> || std::is_same_v< number_t, uint32_t > )
		{
			return data[JSONKey].asUInt();
		}

		if constexpr ( std::is_same_v< number_t, uint64_t > )
		{
			return data[JSONKey].asUInt64();
		}

		if constexpr ( std::is_same_v< number_t, float_t > )
		{
			return data[JSONKey].asFloat();
		}

		if constexpr ( std::is_same_v< number_t, double_t > )
		{
			return data[JSONKey].asDouble();
		}

		/* NOTE: Default behavior. */
		return static_cast< number_t >(data[JSONKey].asInt());
	}

	/**
	 * @brief Gets a number from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value.
	 * @return std::string
	 */
	template< typename number_t >
	[[nodiscard]]
	number_t
	getNumber (const Json::Value & data, const char * JSONKey, number_t defaultValue) noexcept requires (std::is_arithmetic_v< number_t >)
	{
		if ( !data.isMember(JSONKey) || !data[JSONKey].isNumeric() )
		{
			return defaultValue;
		}

		if constexpr ( std::is_same_v< number_t, int8_t > || std::is_same_v< number_t, int16_t> || std::is_same_v< number_t, int32_t > )
		{
			return static_cast< number_t >(data[JSONKey].asInt());
		}

		if constexpr ( std::is_same_v< number_t, int64_t > )
		{
			return data[JSONKey].asInt64();
		}

		if constexpr ( std::is_same_v< number_t, uint8_t > || std::is_same_v< number_t, uint16_t> || std::is_same_v< number_t, uint32_t > )
		{
			return data[JSONKey].asUInt();
		}

		if constexpr ( std::is_same_v< number_t, uint64_t > )
		{
			return data[JSONKey].asUInt64();
		}

		if constexpr ( std::is_same_v< number_t, float_t > )
		{
			return data[JSONKey].asFloat();
		}

		if constexpr ( std::is_same_v< number_t, double_t > )
		{
			return data[JSONKey].asDouble();
		}

		/* NOTE: Default behavior. */
		return static_cast< number_t >(data[JSONKey].asInt());
	}

	/**
	 * @brief Gets a boolean from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @return std::string
	 */
	[[nodiscard]]
	bool getBoolean (const Json::Value & data, const char * JSONKey) noexcept;

	/**
	 * @brief Gets a boolean from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value.
	 * @return std::string
	 */
	[[nodiscard]]
	bool getBoolean (const Json::Value & data, const char * JSONKey, bool defaultValue) noexcept;

	/**
	 * @brief Gets a string from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @return std::string
	 */
	[[nodiscard]]
	std::string getString (const Json::Value & data, const char * JSONKey) noexcept;

	/**
	 * @brief Gets a string from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value.
	 * @return std::string
	 */
	[[nodiscard]]
	std::string getString (const Json::Value & data, const char * JSONKey, const std::string & defaultValue) noexcept;

	/**
	 * @brief Gets a vector from a json node.
	 * @tparam dim_t The dimension of the vector.
	 * @tparam output_t The data type of the vector. Default float.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @return Math::Vector< dim_t, output_t >
	 */
	template< size_t dim_t, typename output_t = float >
	[[nodiscard]]
	static
	Math::Vector< dim_t, output_t >
	getVector (const Json::Value & data, const char * JSONKey) noexcept requires (dim_t == 2 || dim_t == 3 || dim_t == 4) && std::is_arithmetic_v< output_t >
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return {};
		}

		const auto & vector = data[JSONKey];

		if ( !vector.isArray() || vector.size() < dim_t )
		{
			std::cerr << "The key '" << JSONKey << "' is not an array of " << dim_t << " numbers !" "\n";

			return {};
		}

		if constexpr ( dim_t == 2 )
		{ 
			return {vector[0].asFloat(), vector[1].asFloat()};
		}

		if constexpr ( dim_t == 3 )
		{ 
			return {vector[0].asFloat(), vector[1].asFloat(), vector[2].asFloat()};
		}

		if constexpr ( dim_t == 4 )
		{ 
			return {vector[0].asFloat(), vector[1].asFloat(), vector[2].asFloat(), vector[3].asFloat()};
		}

		return {};
	}

	/**
	 * @brief Gets a vector from a json node.
	 * @tparam dim_t The dimension of the vector.
	 * @tparam output_t The data type of the vector. Default float.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value.
	 * @return Math::Vector< dim_t, output_t >
	 */
	template< size_t dim_t, typename output_t = float >
	[[nodiscard]]
	static
	Math::Vector< dim_t, output_t >
	getVector (const Json::Value & data, const char * JSONKey, const Math::Vector< dim_t, output_t > & defaultValue) noexcept requires (dim_t == 2 || dim_t == 3 || dim_t == 4) && std::is_arithmetic_v< output_t >
	{
		if ( !data.isMember(JSONKey) )
		{
			return defaultValue;
		}

		const auto & vector = data[JSONKey];

		if ( !vector.isArray() || vector.size() < dim_t )
		{
			return defaultValue;
		}

		if constexpr ( dim_t == 2 )
		{
			return {vector[0].asFloat(), vector[1].asFloat()};
		}

		if constexpr ( dim_t == 3 )
		{
			return {vector[0].asFloat(), vector[1].asFloat(), vector[2].asFloat()};
		}

		if constexpr ( dim_t == 4 )
		{
			return {vector[0].asFloat(), vector[1].asFloat(), vector[2].asFloat(), vector[3].asFloat()};
		}

		return defaultValue;
	}

	/**
	 * @brief Gets a color from a json node.
	 * @tparam output_t The data type of the color. Must be a floating point number. Default float.
	 * @param data  A reference to a json value.
	 * @param JSONKey The json key name.
	 * @return PixelFactory::Color< output_t >
	 */
	template< typename output_t = float >
	[[nodiscard]]
	static
	PixelFactory::Color< output_t >
	getColor (const Json::Value & data, const char * JSONKey) noexcept requires (std::is_floating_point_v< output_t >)
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return {};
		}

		if ( !data[JSONKey].isArray() )
		{
			std::cerr << "The key '" << JSONKey << "' is not an array !" "\n";

			return {};
		}

		const auto & vector = data[JSONKey];

		switch ( vector.size() )
		{
			case 3 :
				return {vector[0].asFloat(), vector[1].asFloat(), vector[2].asFloat()};

			case 4 :
				return {vector[0].asFloat(), vector[1].asFloat(), vector[2].asFloat(), vector[3].asFloat()};

			default:
				std::cerr << "The key '" << JSONKey << "' is an invalid color !" "\n";

				return {};
		}
	}

	/**
	 * @brief Gets a color from a json node.
	 * @tparam output_t The data type of the color. Must be a floating point number. Default float.
	 * @param data  A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value.
	 * @return PixelFactory::Color< output_t >
	 */
	template< typename output_t = float >
	[[nodiscard]]
	static
	PixelFactory::Color< output_t >
	getColor (const Json::Value & data, const char * JSONKey, const PixelFactory::Color< output_t > & defaultValue) noexcept requires (std::is_floating_point_v< output_t >)
	{
		if ( !data.isMember(JSONKey) || !data[JSONKey].isArray() )
		{
			return defaultValue;
		}

		const auto & vector = data[JSONKey];

		switch ( vector.size() )
		{
			case 3 :
				return {vector[0].asFloat(), vector[1].asFloat(), vector[2].asFloat()};

			case 4 :
				return {vector[0].asFloat(), vector[1].asFloat(), vector[2].asFloat(), vector[3].asFloat()};

			default:
				std::cerr << "The key '" << JSONKey << "' is an invalid color !" "\n";

				return defaultValue;
		}
	}
}
