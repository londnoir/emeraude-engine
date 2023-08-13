/*
 * Emeraude/Graphics/Geometry/Utility.cpp
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

#include "Utility.hpp"

/* Local inclusions. */
#include "Interface.hpp"

namespace Emeraude::Graphics::Geometry
{
	using namespace Libraries;
	using namespace Libraries::VertexFactory;
	using namespace Libraries::Math;

	void
	addGridPointToVertexAttributes (const Libraries::VertexFactory::Grid< float > & grid, size_t index, int flag, std::vector< float > & vertexAttributes) noexcept
	{
		const auto position = grid.position(index);

		/* Position */
		vertexAttributes.emplace_back(position[X]);
		vertexAttributes.emplace_back(position[Y]);
		vertexAttributes.emplace_back(position[Z]);

		if ( flag & EnableTangentSpace )
		{
			const auto normal = grid.normal(index, position);
			const auto tangent = grid.tangent(index, position, grid.textureCoordinates2D(index));
			const auto binormal = Vector< 3, float >::crossProduct(normal, tangent);

			/* Tangent */
			vertexAttributes.emplace_back(tangent[X]);
			vertexAttributes.emplace_back(tangent[Y]);
			vertexAttributes.emplace_back(tangent[Z]);

			/* Binormal */
			vertexAttributes.emplace_back(binormal[X]);
			vertexAttributes.emplace_back(binormal[Y]);
			vertexAttributes.emplace_back(binormal[Z]);

			/* Normal */
			vertexAttributes.emplace_back(normal[X]);
			vertexAttributes.emplace_back(normal[Y]);
			vertexAttributes.emplace_back(normal[Z]);
		}
		else if ( flag & EnableNormal )
		{
			const auto normal = grid.normal(index, position);

			/* Normal */
			vertexAttributes.emplace_back(normal[X]);
			vertexAttributes.emplace_back(normal[Y]);
			vertexAttributes.emplace_back(normal[Z]);
		}

		if ( flag & EnablePrimaryTextureCoordinates )
		{
			if ( flag & Enable3DPrimaryTextureCoordinates )
			{
				const auto UVWCoords = grid.textureCoordinates3D(index);

				/* 3D Texture2Ds Coordinates */
				vertexAttributes.emplace_back(UVWCoords[X]);
				vertexAttributes.emplace_back(UVWCoords[Y]);
				vertexAttributes.emplace_back(UVWCoords[Z]);
			}
			else
			{
				const auto UVCoords = grid.textureCoordinates2D(index);

				/* 2D Texture2Ds Coordinates */
				vertexAttributes.emplace_back(UVCoords[X]);
				vertexAttributes.emplace_back(UVCoords[Y]);
			}
		}

		/* FIXME: For now the secondary texture are the same as primary. */
		if ( flag & EnableSecondaryTextureCoordinates )
		{
			if ( flag & Enable3DSecondaryTextureCoordinates )
			{
				const auto UVWCoords = grid.textureCoordinates3D(index);

				/* 3D Texture2Ds Coordinates */
				vertexAttributes.emplace_back(UVWCoords[X]);
				vertexAttributes.emplace_back(UVWCoords[Y]);
				vertexAttributes.emplace_back(UVWCoords[Z]);
			}
			else
			{
				const auto UVCoords = grid.textureCoordinates2D(index);

				/* 2D Texture2Ds Coordinates */
				vertexAttributes.emplace_back(UVCoords[X]);
				vertexAttributes.emplace_back(UVCoords[Y]);
			}
		}

		/* Vertex color. */
		if ( flag & EnableVertexColor )
		{
			const auto UVCoords = grid.textureCoordinates2D(index);
			const auto level = 1.0F - ((position[Y] - grid.boundingBox().minimum(Y)) / grid.boundingBox().height());

			vertexAttributes.emplace_back(UVCoords[X] / grid.UMultiplier());
			vertexAttributes.emplace_back(UVCoords[Y] / grid.VMultiplier());
			vertexAttributes.emplace_back(level);
			vertexAttributes.emplace_back(1.0);
		}

		/* Vertex weight. */
		if ( flag & EnableWeight )
		{
			vertexAttributes.emplace_back(1.0);
			vertexAttributes.emplace_back(1.0);
			vertexAttributes.emplace_back(1.0);
			vertexAttributes.emplace_back(1.0);
		}
	}
}
