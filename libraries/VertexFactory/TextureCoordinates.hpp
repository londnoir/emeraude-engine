/*
 * Libraries/VertexFactory/TextureCoordinates.hpp
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

/* C/C++ standard libraries. */
#include <cmath>
#include <type_traits>

/* Local inclusions for usages. */
#include "Math/Base.hpp"
#include "Math/Vector.hpp"

namespace Libraries::VertexFactory::TextureCoordinates
{
	/**
	 * @brief Generates cubic texture coordinates.
	 * @tparam type_t The precision of data.
	 * @param position The vertex position.
	 * @param normal The vertex normal vector.
	 * @return Vector< 2, type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Math::Vector< 2, type_t >
	generateCubicCoordinates (const Math::Vector< 3, type_t > & position, const Math::Vector< 3, type_t > & normal) noexcept // NOLINT(readability-function-cognitive-complexity)
	{
		const auto absNX = std::abs(normal[Math::X]);
		const auto absNY = std::abs(normal[Math::Y]);
		const auto absNZ = std::abs(normal[Math::Z]);

		type_t texCoordU = 0;
		type_t texCoordV = 0;

		/* From ZY Plane */
		if ( absNX > absNZ && absNX > absNY )
		{
			texCoordU = normal[Math::X] > 0 ? ( position[Math::Z] > 0 ? 0 : 1 ) : ( position[Math::Z] > 0 ? 1 : 0 );
			texCoordV = position[Math::Y] > 0 ? 1 : 0;
		}
		/* From XZ Plane */
		else if ( absNY > absNX && absNY > absNZ )
		{
			texCoordU = position[Math::X] > 0 ? 1 : 0;
			texCoordV = normal[Math::Y] > 0 ? ( position[Math::Z] > 0 ? 0 : 1 ) : ( position[Math::Z] > 0 ? 1 : 0 );
		}
		/* From XY Plane */
		else if ( absNZ > absNX && absNZ > absNY )
		{
			texCoordU = normal[Math::Z] > 0 ? ( position[Math::X] > 0 ? 1 : 0 ) : ( position[Math::X] > 0 ? 0 : 1 );
			texCoordV = position[Math::Y] > 0 ? 1 : 0;
		}

		return {texCoordU, texCoordV};
	}

	/**
	 * @brief Generates spherical texture coordinates.
	 * @tparam type_t The precision of data.
	 * @param position A reference to a vector.
	 * @param radius The radius of the sphere.
	 * @return Math::Vector< 2, type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Math::Vector< 2, type_t >
	generateSphericalCoordinates (const Math::Vector< 3, type_t > & position, type_t radius = 1) noexcept
	{
		return {
			/* S angle (longitude). */
			std::atan2(position[Math::X], position[Math::Z]) + Math::Pi< float >,
			/* T angle (latitude). */
			static_cast< type_t >(1.0) - std::acos(position[Math::Y] / radius) / Math::Pi< float >
		};
	}
}
