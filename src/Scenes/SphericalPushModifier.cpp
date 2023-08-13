/*
 * Emeraude/Scenes/SphericalPushModifier.cpp
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

#include "SphericalPushModifier.hpp"

/* Local inclusions */
#include "Node.hpp"

namespace Emeraude::Scenes
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
	SphericalPushModifier::move () noexcept
	{

	}

	void
	SphericalPushModifier::processLogics (const Scene &, size_t cycle) noexcept
	{
		this->updateAnimations(cycle);
	}

	bool
	SphericalPushModifier::playAnimation (Animations::id_t id, const Variant & value) noexcept
	{
		switch ( id )
		{
			case Magnitude :
				this->setMagnitude(value.asFloat());

				return true;

			default:
				return false;
		}
	}

	void
	SphericalPushModifier::apply (Physics::MovableTrait & movable) const noexcept
	{
		auto magnitude = m_magnitude;

		if ( this->hasInfluenceArea() )
		{
			const auto influence = this->influenceArea()->influenceStrength(movable);

			if ( influence <= 0.0F )
				return;

			magnitude *= influence;
		}

		/* FIXME: Performance losses. Multiple call to worldCoordinates() with influence area for the targeted node. */
		const auto forceVector = (movable.getWorldCoordinates().position() - this->parentEntity().getWorldCoordinates().position()).normalize().scale(magnitude);

		movable.addForce(forceVector);
	}

	const char *
	SphericalPushModifier::getComponentType () const noexcept
	{
		return "SphericalPushModifier";
	}

	void
	SphericalPushModifier::setMagnitude (float magnitude) noexcept
	{
		m_magnitude = magnitude;
	}

	float
	SphericalPushModifier::magnitude () const noexcept
	{
		return m_magnitude;
	}
}
