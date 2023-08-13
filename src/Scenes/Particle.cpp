/*
 * Emeraude/Scenes/Particle.cpp
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

#include "Particle.hpp"

/* Local inclusions */
#include "Math/OrientedCuboid.hpp"
#include "ParticlesEmitter.hpp"
#include "Physics/Physics.hpp"
#include "Utility.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Physics;

	Particle::Particle (ParticlesEmitter & emitter, size_t initialLife, float initialSize, float spreading) noexcept
		: m_emitter(&emitter), m_life(initialLife), m_size(initialSize)
	{
		m_coordinates.setScaleVector(initialSize);

		if ( !Utility::isZero(spreading)  )
			this->applyChaos(spreading);
	}

	void
	Particle::enableSphereCollision (bool state) noexcept
	{
		m_flags[SphereCollisionEnabled] = state;
	}

	bool
	Particle::sphereCollisionIsEnabled () const noexcept
	{
		return m_flags[SphereCollisionEnabled];
	}

	const Physics::PhysicalObjectProperties &
	Particle::physicalObjectProperties () const noexcept
	{
		return m_emitter->physicalObjectProperties();
	}

	Physics::PhysicalObjectProperties &
	Particle::physicalObjectProperties () noexcept
	{
		return m_emitter->physicalObjectProperties();
	}

	void
	Particle::setLocalCoordinates (const Coordinates< float > & coordinates) noexcept
	{
		m_coordinates = coordinates;
	}

	const Coordinates< float > &
	Particle::localCoordinates () const noexcept
	{
		return m_coordinates;
	}

	Coordinates< float > &
	Particle::getWritableLocalCoordinates () noexcept
	{
		return m_coordinates;
	}

	const Cuboid< float > &
	Particle::localBoundingBox () const noexcept
	{
		return m_emitter->boundingBox();
	}

	const Sphere< float > &
	Particle::localBoundingSphere () const noexcept
	{
		return m_emitter->boundingSphere();
	}

	Coordinates< float >
	Particle::getWorldCoordinates () const noexcept
	{
		return m_emitter->emitterSpace() + m_coordinates;
	}

	Cuboid< float >
	Particle::getWorldBoundingBox () const noexcept
	{
		OrientedCuboid< float > orientedBox{m_emitter->boundingBox(), this->getWorldCoordinates()};

		return orientedBox.getAxisAlignedBox();
	}

	Sphere< float >
	Particle::getWorldBoundingSphere () const noexcept
	{
		return {
			m_emitter->boundingSphere().radius(),
			this->getWorldCoordinates().position() + m_emitter->boundingSphere().position()
		};
	}

	void
	Particle::setMovingAbility (bool state) noexcept
	{
		m_flags[IsMovable] = state;
	}

	bool
	Particle::isMovable () const noexcept
	{
		return m_flags[IsMovable];
	}

	void
	Particle::pauseSimulation (bool state) noexcept
	{
		m_flags[SimulationPaused] = state;
	}

	bool
	Particle::isSimulationPaused () const noexcept
	{
		return m_flags[SimulationPaused];
	}

	void
	Particle::enableFreeFlyMode (bool state) noexcept
	{
		m_flags[FreeFlyModeEnabled] = state;
	}

	bool
	Particle::isFreeFlyModeEnabled () const noexcept
	{
		return m_flags[FreeFlyModeEnabled];
	}

	void
	Particle::enableNoClippingMode (bool state) noexcept
	{
		m_flags[NoClippingModeEnabled] = state;
	}

	bool
	Particle::isNoClippingModeEnabled () const noexcept
	{
		return m_flags[NoClippingModeEnabled];
	}

	Vector< 3, float >
	Particle::getWorldVelocity () const noexcept
	{
		/* FIXME: Check for perf with conversion. */
		return (m_emitter->emitterSpace().modelMatrix() * this->velocity().toVector4()).toVector3();
	}

	Vector< 3, float >
	Particle::getWorldAcceleration () const noexcept
	{
		/* FIXME: Check for perf with conversion. */
		return (m_emitter->emitterSpace().modelMatrix() * this->acceleration().toVector4()).toVector3();
	}

	Vector< 3, float >
	Particle::getWorldCenterOfMass () const noexcept
	{
		return m_emitter->emitterSpace().position() + this->centerOfMass();
	}

	void
	Particle::setLife (size_t life) noexcept
	{
		m_life = life;
	}

	void
	Particle::setSize (float size) noexcept
	{
		m_size = size;
	}

	size_t
	Particle::life () const noexcept
	{
		return m_life;
	}

	float
	Particle::size () const noexcept
	{
		return m_size;
	}

	bool
	Particle::isDead () const noexcept
	{
		return m_life == 0;
	}

	void
	Particle::applyChaos (float magnitude) noexcept
	{
		const auto half = magnitude * 0.5F;

		/* Sets chaos on position. */
		m_coordinates.translateAlongLocalAxis(Utility::random(-half, +half), Utility::random(-half, +half), Utility::random(-half, +half));
	}

	void
	Particle::update (const Vector< 3, float > & velocity, float updateSize, float chaos) noexcept
	{
		/* Reducing his life per one. */
		m_life--;

		/* Checks the new size if requested. */
		if ( !Utility::isZero(updateSize) )
		{
			/* Updates the current size. */
			m_size += updateSize;

			/* NOTE: Kill the particle if below 0.0F. */
			if ( m_size < 0.0F )
			{
				m_life = 0;

				/* This particle is dead. */
				return;
			}

			m_coordinates.setScaleVector(m_size);
		}

		/* Applies velocity to particle position. */
		m_coordinates.translateAlongWorldAxis(velocity * EngineUpdateCycleDuration< float >);

		if ( !Utility::isZero(chaos) )
			this->applyChaos(chaos);
	}
}
