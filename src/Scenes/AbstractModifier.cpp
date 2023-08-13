/*
 * Emeraude/Scenes/AbstractModifier.cpp
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

#include "AbstractModifier.hpp"

/* Local inclusions */
#include "Node.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;

	AbstractModifier::AbstractModifier (const std::string & name, const AbstractEntity & parentEntity) noexcept
		: AbstractComponent(name, parentEntity)
	{

	}

	std::shared_ptr< CubicInfluenceArea >
	AbstractModifier::createCubicInfluenceArea (float size) noexcept
	{
		auto influenceArea = std::make_shared< CubicInfluenceArea >(this->parentEntity(), size);

		this->addInfluenceArea(influenceArea);

		return influenceArea;
	}

	std::shared_ptr< CubicInfluenceArea >
	AbstractModifier::createCubicInfluenceArea (float xSize, float ySize, float zSize) noexcept
	{
		auto influenceArea = std::make_shared< CubicInfluenceArea >(this->parentEntity(), xSize, ySize, zSize);

		this->addInfluenceArea(influenceArea);

		return influenceArea;
	}

	std::shared_ptr< SphericalInfluenceArea >
	AbstractModifier::createSphericalInfluenceArea (float outerRadius, float innerRadius) noexcept
	{
		auto influenceArea = std::make_shared< SphericalInfluenceArea >(this->parentEntity(), outerRadius, innerRadius);

		this->addInfluenceArea(influenceArea);

		return influenceArea;
	}

	void
	AbstractModifier::addInfluenceArea (const std::shared_ptr< InfluenceAreaInterface > & influenceArea) noexcept
	{
		this->removeInfluenceArea();

		m_influenceArea = influenceArea;
	}

	void
	AbstractModifier::removeInfluenceArea () noexcept
	{
		if ( m_influenceArea != nullptr )
			m_influenceArea.reset();
	}

	bool
	AbstractModifier::hasInfluenceArea () const noexcept
	{
		return m_influenceArea != nullptr;
	}

	std::shared_ptr< InfluenceAreaInterface >
	AbstractModifier::influenceArea () const noexcept
	{
		return m_influenceArea;
	}
}
