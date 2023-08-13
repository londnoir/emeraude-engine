/*
 * Emeraude/Scenes/SphericalInfluenceArea.cpp
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

#include "SphericalInfluenceArea.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "AbstractEntity.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Physics;

	SphericalInfluenceArea::SphericalInfluenceArea (const AbstractEntity & parentEntity) noexcept
		: m_parentEntity(&parentEntity)
	{

	}

	SphericalInfluenceArea::SphericalInfluenceArea (const AbstractEntity & parentEntity, float outerRadius, float innerRadius) noexcept
		: SphericalInfluenceArea(parentEntity)
	{
		if ( outerRadius > innerRadius )
		{
			this->setOuterRadius(outerRadius);
			this->setInnerRadius(innerRadius);
		}
		else
		{
			this->setOuterRadius(innerRadius);
			this->setInnerRadius(outerRadius);
		}
	}

	bool
	SphericalInfluenceArea::isUnderInfluence (const Physics::MovableTrait & movable) const noexcept
	{
		/* FIXME: This method don't use the AABB. */
		const auto range = m_outerRadius + movable.getWorldBoundingSphere().radius();

		return ( (movable.getWorldCoordinates().position() - m_parentEntity->getWorldCoordinates().position()).length() <= range );
	}

	float
	SphericalInfluenceArea::influenceStrength (const Physics::MovableTrait & movable) const noexcept
	{
		/* FIXME: This method don't use the AABB. */
		const auto distance = (movable.getWorldCoordinates().position() - m_parentEntity->getWorldCoordinates().position()).length();

		const auto targetBoundingRadius = movable.getWorldBoundingSphere().radius();

		/* Outside the outer radius, so no influence at all. */
		if ( distance > m_outerRadius + targetBoundingRadius )
		{
			return 0.0F;
		}

		/* Inside the inner radius, full influence. */
		if ( distance < m_innerRadius + targetBoundingRadius )
		{
			return 1.0F;
		}

		/* Compute fallout distance. */
		const auto falloutDistance = m_outerRadius - m_innerRadius;

		return (distance + targetBoundingRadius - m_innerRadius) / falloutDistance;
	}

	void
	SphericalInfluenceArea::setOuterRadius (float outerRadius) noexcept
	{
		if ( outerRadius <= 0.0F )
		{
			Tracer::warning(ClassId, "Radius must be positive !");

			return;
		}

		m_outerRadius = outerRadius;

		if ( m_innerRadius > m_outerRadius )
		{
			m_innerRadius = m_outerRadius;
		}
	}

	float
	SphericalInfluenceArea::outerRadius () const noexcept
	{
		return m_outerRadius;
	}

	void
	SphericalInfluenceArea::setInnerRadius (float innerRadius) noexcept
	{
		if ( innerRadius <= 0.0F )
		{
			Tracer::warning(ClassId, "Radius must be positive !");

			return;
		}

		m_innerRadius = innerRadius;

		if ( m_innerRadius > m_outerRadius )
		{
			m_outerRadius = m_innerRadius;
		}
	}

	float
	SphericalInfluenceArea::innerRadius () const noexcept
	{
		return m_innerRadius;
	}
}
