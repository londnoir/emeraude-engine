/*
 * src/Scenes/Component/Abstract.cpp
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

#include "Abstract.hpp"

/* STL inclusions. */
#include <cstddef>
#include <memory>
#include <string>

/* Local inclusions. */
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Cuboid.hpp"
#include "Libraries/Math/Sphere.hpp"
#include "Libraries/Math/Vector.hpp"
#include "Libraries/NameableTrait.hpp"
#include "Physics/MovableTrait.hpp"
#include "Physics/PhysicalObjectProperties.hpp"
#include "Scenes/AbstractEntity.hpp"
#include "Tracer.hpp"

namespace Emeraude::Scenes::Component
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Graphics;
	using namespace Physics;

	static constexpr auto TracerTag{"EntityComponent"};

	const size_t Abstract::ClassUID{getClassUID("AbstractEntityComponent")};
	const Cuboid< float > Abstract::NullBoundingBox{};
	const Sphere< float > Abstract::NullBoundingSphere{};

	Abstract::Abstract (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: NameableTrait(name), m_parentEntity(parentEntity)
	{

	}

	size_t
	Abstract::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	Abstract::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	const AbstractEntity &
	Abstract::parentEntity () const noexcept
	{
		return m_parentEntity;
	}

	bool
	Abstract::isParentEntityMovable () const noexcept
	{
		return dynamic_cast< const MovableTrait * >(&m_parentEntity) != nullptr;
	}

	bool
	Abstract::initialize (const Json::Value & /*unused*/) noexcept
	{
		Tracer::warning(TracerTag, "This entity didn't reimplement the JSON initialization method !");

		return false;
	}

	bool
	Abstract::isRenderable () const noexcept
	{
		return this->getRenderableInstance() != nullptr;
	}

	std::shared_ptr< RenderableInstance::Abstract >
	Abstract::getRenderableInstance () const noexcept
	{
		return nullptr;
	}

	const Renderable::Interface *
	Abstract::getRenderable () const noexcept
	{
		const auto renderableInstance = this->getRenderableInstance();

		if ( renderableInstance == nullptr )
		{
			return nullptr;
		}

		return renderableInstance->renderable();
	}

	const PhysicalObjectProperties &
	Abstract::physicalObjectProperties () const noexcept
	{
		return m_physicalObjectProperties;
	}

	PhysicalObjectProperties &
	Abstract::physicalObjectProperties () noexcept
	{
		return m_physicalObjectProperties;
	}

	CartesianFrame< float >
	Abstract::getWorldCoordinates () const noexcept
	{
		return m_parentEntity.getWorldCoordinates();
	}

	Vector< 3, float >
	Abstract::getWorldVelocity () const noexcept
	{
		const auto * movable = dynamic_cast< const MovableTrait * >(&m_parentEntity);

		if ( movable == nullptr )
		{
			return {};
		}

		return movable->getWorldVelocity();
	}
}
