/*
 * Emeraude/Graphics/Renderable/AbstractSceneArea.cpp
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

#include "AbstractSceneArea.hpp"

/* Local inclusions. */
#include "Scenes/Node.hpp"

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Scenes;

	AbstractSceneArea::AbstractSceneArea (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	void
	AbstractSceneArea::setReadyForInstanciation (bool state) noexcept
	{
		if ( state )
			this->enableFlag(IsReadyForInstanciation);
		else
			this->disableFlag(IsReadyForInstanciation);
	}

	bool
	AbstractSceneArea::isReadyForInstantiation () const noexcept
	{
		return this->isFlagEnabled(IsReadyForInstanciation);
	}

	int
	AbstractSceneArea::flags (size_t) const noexcept
	{
		return m_renderableFlags;
	}

	void
	AbstractSceneArea::setBoundary (float boundary) noexcept
	{
		m_boundary = std::abs(boundary);
	}

	float
	AbstractSceneArea::boundary () const noexcept
	{
		return m_boundary;
	}

	float
	AbstractSceneArea::getLevelAt (const Vector< 3, float > &) const noexcept
	{
		return -m_boundary;
	}

	Vector< 3, float >
	AbstractSceneArea::getLevelAt (float x, float z, float delta) const noexcept
	{
		return {x, -m_boundary + delta, z};
	}

	Vector< 3, float >
	AbstractSceneArea::getNormalAt (const Vector< 3, float > &) const noexcept
	{
		return Vector< 3, float >::positiveY();
	}

	bool
	AbstractSceneArea::isOnGround (Node & node) const noexcept
	{
		/* Gets the absolute position to test against the scene boundaries. */
		auto worldPosition = node.getWorldCoordinates().position();

		return Utility::equal(worldPosition[Y], -m_boundary);
	}
}
