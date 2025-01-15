/*
 * src/Scenes/Component/Weight.cpp
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

#include "Weight.hpp"

/* STL inclusions. */
#include <cstddef>
#include <string>

/* Local inclusions. */
#include "Abstract.hpp"
#include "Animations/Types.hpp"
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Cuboid.hpp"
#include "Libraries/Math/Sphere.hpp"
#include "Physics/PhysicalObjectProperties.hpp"
#include "Libraries/Variant.hpp"
#include "Scenes/Scene.hpp"

namespace Emeraude::Scenes::Component
{
	using namespace Libraries;
	using namespace Libraries::Math;

	Weight::Weight (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: Abstract(name, parentEntity)
	{

	}

	Weight::Weight (const std::string & name, const AbstractEntity & parentEntity, const Physics::PhysicalObjectProperties & initialProperties) noexcept
		: Abstract(name, parentEntity)
	{
		this->physicalObjectProperties().setProperties(initialProperties);
	}

	const char *
	Weight::getComponentType () const noexcept
	{
		return ClassId;
	}

	const Cuboid< float > &
	Weight::boundingBox () const noexcept
	{
		return m_boundingBox;
	}

	const Sphere< float > &
	Weight::boundingSphere () const noexcept
	{
		return m_boundingSphere;
	}

	void
	Weight::move (const CartesianFrame< float > & /*worldCoordinates*/) noexcept
	{

	}

	void
	Weight::processLogics (const Scene & scene) noexcept
	{
		this->updateAnimations(scene.cycle());
	}

	bool
	Weight::shouldRemove () const noexcept
	{
		return false;
	}

	bool
	Weight::playAnimation (Animations::id_t /*identifier*/, const Variant & /*value*/) noexcept
	{
		return false;
	}

	void
	Weight::setRadius (float radius) noexcept
	{
		m_boundingSphere.setRadius(radius);

		this->notify(ComponentContentModified);
	}

	void
	Weight::setBoxSize (float size) noexcept
	{
		m_boundingBox.set(size * 0.5F);

		this->notify(ComponentContentModified);
	}

	void
	Weight::setBoxSize (float xSize, float ySize, float zSize) noexcept
	{
		m_boundingBox.set({xSize * 0.5F, ySize * 0.5F, zSize * 0.5F}, {-xSize * 0.5F, -ySize * 0.5F, -zSize * 0.5F});

		this->notify(ComponentContentModified);
	}
}
