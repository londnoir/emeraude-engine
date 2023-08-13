/*
 * Libraries/FastJSON.hpp
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

/* Local inclusions */
#include "PixelFactory/Color.hpp"

/* Third-party inclusions */
#include "Third-Party-Inclusion/json.hpp"

namespace Libraries::FastJSON
{
	[[maybe_unused]]
	constexpr auto TypeKey{"Type"};
	[[maybe_unused]]
	constexpr auto NameKey{"Name"};
	[[maybe_unused]]
	constexpr auto PositionKey{"Position"};
	[[maybe_unused]]
	constexpr auto OrientationKey{"Orientation"};
	[[maybe_unused]]
	constexpr auto ColorKey{"Color"};
	[[maybe_unused]]
	constexpr auto IntensityKey{"Intensity"};
	[[maybe_unused]]
	constexpr auto DataKey{"Data"};
	[[maybe_unused]]
	constexpr auto PropertiesKey{"Properties"};
	[[maybe_unused]]
	constexpr auto ScaleKey{"Scale"};
	[[maybe_unused]]
	constexpr auto SizeKey{"Size"};
	[[maybe_unused]]
	constexpr auto DivisionKey{"Division"};
	[[maybe_unused]]
	constexpr auto UVMultiplierKey{"UVMultiplier"};
	[[maybe_unused]]
	constexpr auto ModeKey{"Mode"};
	
	/**
	 * @brief Gets the root json node from a filepath.
	 * @param filepath A reference to a filepath.
	 * @return Json::Value
	 */
	[[maybe_unused]]
	[[nodiscard]]
	Json::Value getRootFromFile (const Path::File & filepath) noexcept;

	/**
	 * @brief Gets a number from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value if not exits. Default 0.
	 * @return int
	 */
	[[maybe_unused]]
	[[nodiscard]]
	int getInteger (const Json::Value & data, const char * JSONKey, int defaultValue = 0) noexcept;

	/**
	 * @brief Gets a number from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value if not exits. Default 0.
	 * @return unsigned int
	 */
	[[maybe_unused]]
	[[nodiscard]]
	unsigned int getUnsignedInteger (const Json::Value & data, const char * JSONKey, unsigned int defaultValue = 0) noexcept;

	/**
	 * @brief Gets a number from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value if not exits. Default 0.
	 * @return float
	 */
	[[maybe_unused]]
	[[nodiscard]]
	float getFloat (const Json::Value & data, const char * JSONKey, float defaultValue = 0.0F) noexcept;

	/**
	 * @brief Gets a number from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value if not exits. Default 0.
	 * @return double
	 */
	[[maybe_unused]]
	[[nodiscard]]
	double getDouble (const Json::Value & data, const char * JSONKey, double defaultValue = 0.0) noexcept;

	/**
	 * @brief Gets a boolean from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value if not exits. Default false.
	 * @return bool
	 */
	[[maybe_unused]]
	[[nodiscard]]
	bool getBoolean (const Json::Value & data, const char * JSONKey, bool defaultValue = false) noexcept;

	/**
	 * @brief Gets a string from a json node.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value if not exits. Default empty.
	 * @return std::string
	 */
	[[maybe_unused]]
	[[nodiscard]]
	std::string getString (const Json::Value & data, const char * JSONKey, const std::string & defaultValue = {}) noexcept;

	/**
	 * @brief Gets a vector from a json node.
	 * @tparam dim_t The dimension of the vector.
	 * @tparam output_t The data type of the vector. Default float.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.
	 * @param defaultValue The default value if not exits. Default [0, 0, (0, (0))].
	 * @return Math::Vector< dim_t, output_t >
	 */
	template<
		std::size_t dim_t,
		typename output_t = float,
		std::enable_if_t< dim_t == 2 || dim_t == 3 || dim_t == 4, bool > = false,
		std::enable_if_t< std::is_arithmetic_v< output_t >, bool > = false
	>
	[[maybe_unused]]
	[[nodiscard]]
	static
	Math::Vector< dim_t, output_t >
	getVector (const Json::Value & data, const char * JSONKey, const Math::Vector< dim_t, output_t > & defaultValue = {}) noexcept
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return defaultValue;
		}

		const auto & vector = data[JSONKey];

		if ( !vector.isArray() || vector.size() < dim_t )
		{
			std::cerr << "The key '" << JSONKey << "' is not an array of " << dim_t << " numbers !" "\n";

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
	 * @param defaultValue The default value if not exits. Default black.
	 * @return PixelFactory::Color< output_t >
	 */
	template< typename output_t = float, std::enable_if_t< std::is_floating_point_v< output_t >, bool > = false >
	[[maybe_unused]]
	[[nodiscard]]
	static
	PixelFactory::Color< output_t >
	getColor (const Json::Value & data, const char * JSONKey, const PixelFactory::Color< output_t > & defaultValue = {}) noexcept
	{
		if ( !data.isMember(JSONKey) )
		{
			std::cerr << "The key '" << JSONKey << "' is not present !" "\n";

			return defaultValue;
		}

		if ( !data[JSONKey].isArray() )
		{
			std::cerr << "The key '" << JSONKey << "' is not an array !" "\n";

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

	/**
	 * @brief Returns whether the data is numeric.
	 * @param data A reference to a json value.
	 * @param JSONKey The json key name.The json key name.
	 * @return bool
	 */
	[[maybe_unused]]
	[[nodiscard]]
	bool checkNumericalValue (const Json::Value & data, const char * JSONKey) noexcept;
}
