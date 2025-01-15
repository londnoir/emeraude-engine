/*
 * src/Graphics/Geometry/GenerationParameters.cpp
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

#include "GenerationParameters.hpp"

/* STL inclusions. */
#include <sstream>

/* Local inclusions. */
#include "Graphics/Geometry/Types.hpp"
#include "Libraries/Utility.hpp"

namespace Emeraude::Graphics::Geometry
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Libraries::VertexFactory;

	GenerationParameters::GenerationParameters (uint32_t geometryFlagBits) noexcept
		: FlagTrait(geometryFlagBits)
	{

	}

	std::string
	GenerationParameters::uniqueIdentifier () const noexcept
	{
		return (std::stringstream{} <<
			m_globalVertexColor << ',' <<
			m_transformMatrix << ',' <<
			m_textureCoordinatesMultiplier << ',' <<
			this->flagBits() << ',' <<
			m_flags[CenterAtBottom] << ',' <<
			m_flags[FlipGeometry] << ',' <<
			m_flags[GlobalVertexColorSet]
		).str();
	}

	ShapeBuilderOptions< float >
	GenerationParameters::getShapeBuilderOptions () const noexcept
	{
		ShapeBuilderOptions< float > options{
			this->isFlagEnabled(EnableNormal),
			this->isFlagEnabled(EnablePrimaryTextureCoordinates) || this->isFlagEnabled(EnableSecondaryTextureCoordinates),
			this->isFlagEnabled(EnableVertexColor),
			this->isFlagEnabled(EnableInfluence),
			this->isFlagEnabled(EnableWeight)
		};
		options.setTextureCoordinatesMultiplier(m_textureCoordinatesMultiplier);
		options.setCenterAtBottom(this->isCenteredAtBottom());
		options.enableGeometryFlipping(this->flipGeometry());

		/* NOTE: Set the global vertex color only if the parameter received a color. */
		if ( m_flags[GlobalVertexColorSet] )
		{
			options.enableGlobalVertexColor(m_globalVertexColor);
		}

		return options;
	}
}
