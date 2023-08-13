/*
 * Emeraude/Scenes/AbstractComponent.cpp
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

#include "AbstractComponent.hpp"

/* C/C++ standard */
#include <iostream>

/* Local inclusions */
#include "Physics/MovableTrait.hpp"
#include "Scenes/AbstractEntity.hpp"
#include "Tracer.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/json.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Graphics;
	using namespace Physics;

	constexpr auto TracerTag{"EntityComponent"};

	const size_t AbstractComponent::ClassUID{Observable::getClassUID()};

	AbstractComponent::AbstractComponent (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: NamedItem(name), m_parentEntity(parentEntity)
	{

	}

	bool
	AbstractComponent::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(TracerTag, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	const AbstractEntity &
	AbstractComponent::parentEntity () const noexcept
	{
		return m_parentEntity;
	}

	bool
	AbstractComponent::isParentEntityMovable () const noexcept
	{
		return dynamic_cast< const Physics::MovableTrait * >(&m_parentEntity) != nullptr;
	}

	bool
	AbstractComponent::initialize (const Json::Value & /*unused*/) noexcept
	{
		Tracer::warning(TracerTag, "This entity didn't reimplement the JSON initialization method !");

		return false;
	}

	bool
	AbstractComponent::isRenderable () const noexcept
	{
		return this->getRenderableInstance() != nullptr;
	}

	const RenderableInstance::Abstract *
	AbstractComponent::getRenderableInstance () const noexcept
	{
		return nullptr;
	}

	RenderableInstance::Abstract *
	AbstractComponent::getRenderableInstance () noexcept
	{
		return nullptr;
	}

	const Physics::PhysicalObjectProperties &
	AbstractComponent::physicalObjectProperties () const noexcept
	{
		return m_physicalObjectProperties;
	}

	Physics::PhysicalObjectProperties &
	AbstractComponent::physicalObjectProperties () noexcept
	{
		return m_physicalObjectProperties;
	}

	Coordinates< float >
	AbstractComponent::getWorldCoordinates () const noexcept
	{
		return m_parentEntity.getWorldCoordinates();
	}

	Vector< 3, float >
	AbstractComponent::getWorldVelocity () const noexcept
	{
		const auto * movable = dynamic_cast< const Physics::MovableTrait * >(&m_parentEntity);

		if ( movable == nullptr )
		{
			return {};
		}

		return movable->getWorldVelocity();
	}

	const Cuboid< float > &
	AbstractComponent::boundingBox () const noexcept
	{
		return m_boundingBox;
	}

	Cuboid< float > &
	AbstractComponent::boundingBox () noexcept
	{
		return m_boundingBox;
	}

	const Sphere< float > &
	AbstractComponent::boundingSphere () const noexcept
	{
		return m_boundingSphere;
	}

	Sphere< float > &
	AbstractComponent::boundingSphere () noexcept
	{
		return m_boundingSphere;
	}
}
