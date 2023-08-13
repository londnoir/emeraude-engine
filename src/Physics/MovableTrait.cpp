/*
 * Emeraude/Physics/MovableTrait.cpp
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

#include "MovableTrait.hpp"

namespace Emeraude::Physics
{
	using namespace Libraries;
	using namespace Libraries::Math;

	void
	MovableTrait::setVelocity (const Vector< 3, float > & velocity, bool resetAcceleration) noexcept
	{
		m_velocity = velocity;

		if ( resetAcceleration )
		{
			m_acceleration.reset();
		}

		/* NOTE: Restart the simulation if it was paused. */
		this->pauseSimulation(false);
	}

	const Vector< 3, float > &
	MovableTrait::velocity () const noexcept
	{
		return m_velocity;
	}

	float
	MovableTrait::getSpeed () const noexcept
	{
		return m_velocity.length();
	}

	void
	MovableTrait::setAcceleration (const Vector< 3, float > & acceleration) noexcept
	{
		m_acceleration = acceleration;

		/* NOTE: Restart the simulation if it was paused. */
		this->pauseSimulation(false);
	}

	void
	MovableTrait::addRawAcceleration (const Vector< 3, float > & acceleration) noexcept
	{
		m_acceleration += acceleration;

		/* NOTE: Restart the simulation if it was paused. */
		this->pauseSimulation(false);
	}

	const Vector< 3, float > &
	MovableTrait::acceleration () const noexcept
	{
		return m_acceleration;
	}

	void
	MovableTrait::setCenterOfMass (const Vector< 3, float > & centerOfMass) noexcept
	{
		m_centerOfMass = centerOfMass;
	}

	const Vector< 3, float > &
	MovableTrait::centerOfMass () const noexcept
	{
		return m_centerOfMass;
	}

	void
	MovableTrait::addForce (const Vector< 3, float > & force) noexcept
	{
		const auto & physicalObjectProperties = this->physicalObjectProperties();

		/* NOTE: If the object mass is null, we discard the force. */
		if ( physicalObjectProperties.isMassNull() )
		{
			return;
		}

		/* "F = m * a"
		 * (Vector)Force = (Number)mass * (Vector)acceleration
		 * => A = F * 1/m */
		m_acceleration += force * physicalObjectProperties.inverseMass();

		/* NOTE: Restart the simulation if it was paused. */
		this->pauseSimulation(false);
	}

	void
	MovableTrait::applyGravityForce (float gravity) noexcept
	{
		const auto & physicalObjectProperties = this->physicalObjectProperties();

		/* NOTE: If the object mass is null (or the free fly mode is enabled), we discard the gravity force. */
		if ( this->isFreeFlyModeEnabled() || physicalObjectProperties.isMassNull() )
		{
			return;
		}

		/* NOTE: Just apply the gravity on the Y axis. */
		m_acceleration[Y] += gravity;
	}

	void
	MovableTrait::applyDragForce (float density) noexcept
	{
		const auto & physicalObjectProperties = this->physicalObjectProperties();

		/* NOTE: If there is no velocity, there can't be drag. */
		if ( m_velocity.isNull() )
		{
			return;
		}

		const auto drag = Physics::getDragMagnitude(physicalObjectProperties.dragCoefficient(), density, m_velocity.length(), physicalObjectProperties.surface());

		if ( drag > physicalObjectProperties.mass() * Gravity::Earth< float > )
		{
			return;
		}

		this->addForce(Physics::getDragForce(m_velocity, drag));
	}

	void
	MovableTrait::deflect (const Vector< 3, float > & surfaceNormal, float surfaceBounciness) noexcept
	{
		const auto & physicalObjectProperties = this->physicalObjectProperties();

		/* NOTE: Velocity vector length gives the speed in m/s. */
		const auto speed = this->getSpeed() * (physicalObjectProperties.bounciness() * Math::clampToUnit(surfaceBounciness));

		/* NOTE: Velocity vector normalized gives the direction. */
		m_velocity = Vector< 3, float >::reflect(m_velocity.normalized(), surfaceNormal).scale(speed);
	}

	const Vector< 3, float > &
	MovableTrait::updateVelocity (const PhysicalEnvironmentProperties & properties) noexcept
	{
		/* Adds the gravity force. */
		this->applyGravityForce(properties.gravity());

		/* Then compute the drag force from current velocity to reduce the acceleration. */
		this->applyDragForce(properties.atmosphericDensity());

		/* Transfer acceleration to the current velocity. */
		m_velocity += m_acceleration;
		m_acceleration.reset();

		return m_velocity;
	}

	void
	MovableTrait::stopMovement ()
	{
		m_acceleration.reset();
		m_velocity.reset();
	}

	bool
	MovableTrait::isMoving () const
	{
		if ( !m_velocity.isNull() )
		{
			return true;
		}

		return m_acceleration.isNull();
	}

	void
	MovableTrait::clearVelocity() noexcept
	{
		m_velocity.reset();
	}
}
