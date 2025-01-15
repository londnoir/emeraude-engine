/*
 * src/Scenes/Component/SphericalPushModifier.cpp
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

#include "SphericalPushModifier.hpp"

/* Local inclusions. */
#include "Scenes/AbstractEntity.hpp"
#include "Scenes/Scene.hpp"

namespace Emeraude::Scenes::Component
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Physics;

	SphericalPushModifier::SphericalPushModifier (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: AbstractModifier(name, parentEntity)
	{

	}

	void
	SphericalPushModifier::move (const CartesianFrame< float > & /*worldCoordinates*/) noexcept
	{

	}

	void
	SphericalPushModifier::processLogics (const Scene & scene) noexcept
	{
		this->updateAnimations(scene.cycle());
	}

	bool
	SphericalPushModifier::shouldRemove () const noexcept
	{
		return false;
	}

	bool
	SphericalPushModifier::playAnimation (id_t identifier, const Variant & value) noexcept
	{
		switch ( identifier )
		{
			case Magnitude :
				this->setMagnitude(value.asFloat());

				return true;

			default:
				return false;
		}
	}

	Vector< 3, float >
	SphericalPushModifier::getForceAppliedToEntity (const CartesianFrame< float > & worldCoordinates, const Sphere< float > & worldBoundingSphere) const noexcept
	{
		auto magnitude = m_magnitude;

		if ( this->hasInfluenceArea() )
		{
			const auto influence = this->influenceArea()->influenceStrength(worldCoordinates, worldBoundingSphere);

			if ( influence <= 0.0F )
			{
				return {};
			}

			magnitude *= influence;
		}

		return (worldCoordinates.position() - this->parentEntity().getWorldCoordinates().position()).normalize().scale(magnitude);
	}

	Vector< 3, float >
	SphericalPushModifier::getForceAppliedToEntity (const CartesianFrame< float > & worldCoordinates, const Cuboid< float > & worldBoundingBox) const noexcept
	{
		auto magnitude = m_magnitude;

		if ( this->hasInfluenceArea() )
		{
			const auto influence = this->influenceArea()->influenceStrength(worldCoordinates, worldBoundingBox);

			if ( influence <= 0.0F )
			{
				return {};
			}

			magnitude *= influence;
		}

		return (worldCoordinates.position() - this->parentEntity().getWorldCoordinates().position()).normalize().scale(magnitude);
	}
}
