/*
 * Emeraude/Graphics/Geometry/GenerationParameters.cpp
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

#include "GenerationParameters.hpp"

/* C/C++ standard libraries. */
#include <sstream>

namespace Emeraude::Graphics::Geometry
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Libraries::VertexFactory;

	GenerationParameters::GenerationParameters (uint32_t geometryResourceFlagBits) noexcept
		: FlagTrait(geometryResourceFlagBits)
	{

	}

	void
	GenerationParameters::setGlobalVertexColor (const Color< float > & globalVertexColor) noexcept
	{
		m_globalVertexColor = globalVertexColor;

		m_flags[GlobalVertexColorSet] = true;
	}

	void
	GenerationParameters::setTransformMatrix (const Matrix< 4, float > & transformMatrix) noexcept
	{
		m_transformMatrix = transformMatrix;
	}

	void
	GenerationParameters::setTextureCoordinatesMultiplier (float xMultiplier, float yMultiplier, float zMultiplier) noexcept
	{
		m_textureCoordinatesMultiplier[X] = xMultiplier;
		m_textureCoordinatesMultiplier[Y] = Utility::isZero(yMultiplier) ? xMultiplier : yMultiplier;
		m_textureCoordinatesMultiplier[Z] = Utility::isZero(zMultiplier) ? xMultiplier : zMultiplier;
	}

	void
	GenerationParameters::setGeometryFlags (uint32_t geometryResourceFlagBits) noexcept
	{
		this->setFlagBits(geometryResourceFlagBits);
	}

	void
	GenerationParameters::setCenterAtBottom (bool state) noexcept
	{
		m_flags[CenterAtBottom] = state;
	}

	void
	GenerationParameters::setFlipGeometry (bool state) noexcept
	{
		m_flags[FlipGeometry] = state;
	}

	const Color< float > &
	GenerationParameters::globalVertexColor () const noexcept
	{
		return m_globalVertexColor;
	}

	const Matrix< 4, float > &
	GenerationParameters::transformMatrix () const noexcept
	{
		return m_transformMatrix;
	}

	const Vector< 3, float > &
	GenerationParameters::textureCoordinatesMultiplier () const noexcept
	{
		return m_textureCoordinatesMultiplier;
	}

	uint32_t
	GenerationParameters::geometryFlags () const noexcept
	{
		return this->flagBits();
	}

	bool
	GenerationParameters::isCenteredAtBottom () const noexcept
	{
		return m_flags[CenterAtBottom];
	}

	bool
	GenerationParameters::flipGeometry () const noexcept
	{
		return m_flags[FlipGeometry];
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
		ShapeBuilderOptions< float > options{};
		options.setTextureCoordinatesMultiplier(m_textureCoordinatesMultiplier);
		options.setCenterAtBottom(this->isCenteredAtBottom());
		options.enableGeometryFlipping(this->flipGeometry());

		/* NOTE: Set the global vertex color only if the parameter received a color. */
		if ( m_flags[GlobalVertexColorSet] )
			options.enableGlobalVertexColor(m_globalVertexColor);

		return options;
	}
}
