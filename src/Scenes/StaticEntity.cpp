/*
 * Emeraude/Scenes/StaticEntity.cpp
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

#include "StaticEntity.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;

	const size_t StaticEntity::ClassUID{Observable::getClassUID()};

	StaticEntity::StaticEntity (const std::string & name, Scene * parentScene, const Coordinates< float > & coordinates) noexcept
		: AbstractEntity(name, parentScene), m_coordinates(coordinates)
	{
		TraceInfo{ClassId} << "The static entity '" << this->name() << "' is constructed !";
	}

	StaticEntity::~StaticEntity ()
	{
		TraceInfo{ClassId} << "The static entity '" << this->name() << "' is destructed !";
	}

	bool
	StaticEntity::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	StaticEntity::isRenderable () const noexcept
	{
		return m_flags[IsRenderable];
	}

	bool
	StaticEntity::hasPhysicalObjectProperties () const noexcept
	{
		return m_flags[HasPhysicalObjectProperties];
	}

	void
	StaticEntity::setLocalCoordinates (const Coordinates< float > & coordinates) noexcept
	{
		m_coordinates = coordinates;
	}

	const Coordinates< float > &
	StaticEntity::localCoordinates () const noexcept
	{
		return m_coordinates;
	}

	Coordinates< float > &
	StaticEntity::getWritableLocalCoordinates () noexcept
	{
		return m_coordinates;
	}

	Coordinates< float >
	StaticEntity::getWorldCoordinates () const noexcept
	{
		return m_coordinates;
	}

	Cuboid< float >
	StaticEntity::getWorldBoundingBox () const noexcept
	{
		return this->localBoundingBox();
	}

	Sphere< float >
	StaticEntity::getWorldBoundingSphere () const noexcept
	{
		return this->localBoundingSphere();
	}

	bool
	StaticEntity::processLogics (const Scene & scene, size_t cycle) noexcept
	{
		for ( auto & pair : this->components() )
			pair.second->processLogics(scene, cycle);

		return false;
	}

	void
	StaticEntity::setRenderingAbilityState (bool state) noexcept
	{
		m_flags[IsRenderable] = state;
	}

	void
	StaticEntity::setPhysicalObjectPropertiesState (bool state) noexcept
	{
		m_flags[HasPhysicalObjectProperties] = state;
	}

	bool
	StaticEntity::onUnhandledNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept
	{
#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled event from observable @" << observable << " (code:" << notificationCode << ") ! "
			"Forgetting it ...";
#endif

		return false;
	}

	bool
	StaticEntity::playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept
	{
		return false;
	}

	void
	StaticEntity::enableSphereCollision (bool state) noexcept
	{
		m_flags[SphereCollisionEnabled] = state;
	}

	bool
	StaticEntity::sphereCollisionIsEnabled () const noexcept
	{
		return m_flags[SphereCollisionEnabled];
	}

	Matrix< 4, float >
	StaticEntity::getModelMatrix () const noexcept
	{
		return m_coordinates.modelMatrix();
	}

	Matrix< 4, float >
	StaticEntity::getViewMatrix (bool rotateOnly) const noexcept
	{
		return m_coordinates.viewMatrix(rotateOnly);
	}
}
