/*
 * Emeraude/Scenes/DirectionalPushModifier.cpp
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

#include "DirectionalPushModifier.hpp"

/* Local inclusions */
#include "Node.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Animations;
	using namespace Physics;

	DirectionalPushModifier::DirectionalPushModifier (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: AbstractModifier(name, parentEntity), m_direction(parentEntity.getWorldCoordinates().forwardVector())
	{

	}

	void
	DirectionalPushModifier::move () noexcept
	{
		/* Updates the force vector using the Node
		 * forward vector and the modifier magnitude. */
		if ( m_useCoordinatesDirection )
			m_direction = this->getWorldCoordinates().forwardVector();
	}

	void
	DirectionalPushModifier::processLogics (const Scene &, size_t cycle) noexcept
	{
		this->updateAnimations(cycle);
	}

	bool
	DirectionalPushModifier::playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept
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
	DirectionalPushModifier::apply (Physics::MovableTrait & movable) const noexcept
	{
		auto magnitudeValue = m_magnitude;

		if ( this->hasInfluenceArea() )
		{
			const auto influence = this->influenceArea()->influenceStrength(movable);

			if ( influence <= 0.0F )
				return;

			magnitudeValue *= influence;
		}

		const auto forceVector = m_direction.scaled(magnitudeValue);

		movable.addForce(forceVector);
	}

	const char *
	DirectionalPushModifier::getComponentType () const noexcept
	{
		return "DirectionalPushModifier";
	}

	void
	DirectionalPushModifier::setMagnitude (float magnitude) noexcept
	{
		m_magnitude = magnitude;
	}

	float
	DirectionalPushModifier::magnitude () const noexcept
	{
		return m_magnitude;
	}

	void
	DirectionalPushModifier::setCustomDirection (const Vector< 3, float > & direction) noexcept
	{
		m_direction = direction;
		m_useCoordinatesDirection = true;
	}

	void
	DirectionalPushModifier::disableCustomDirection () noexcept
	{
		m_direction = this->parentEntity().getWorldCoordinates().forwardVector();

		m_useCoordinatesDirection = false;
	}

	const Vector< 3, float > &
	DirectionalPushModifier::direction () const noexcept
	{
		return m_direction;
	}
}
