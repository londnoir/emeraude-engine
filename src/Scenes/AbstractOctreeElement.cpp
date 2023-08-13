/*
 * Emeraude/Scenes/AbstractOctreeElement.cpp
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

#include "AbstractOctreeElement.hpp"

/* Local inclusions. */
#include "OctreeSector.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;

	AbstractOctreeElement::AbstractOctreeElement (const std::string & name) noexcept
		: NamedItem(name)
	{

	}

	bool
	AbstractOctreeElement::isPresentIn (const std::shared_ptr< OctreeSector > & sector, bool checkOnlyLeaves) const noexcept
	{
		if ( checkOnlyLeaves )
		{
			return std::find(m_leafSectors.cbegin(), m_leafSectors.cend(), sector) != m_leafSectors.cend();
		}

		for ( auto leafSector : m_leafSectors )
		{
			do
			{
				if ( leafSector == sector )
				{
					return true;
				}

				leafSector = leafSector->parentSector();
			}
			while ( leafSector != nullptr );
		}

		return false;
	}

	bool
	AbstractOctreeElement::hasSharedLeafSector (AbstractOctreeElement & entityA, AbstractOctreeElement & entityB) noexcept
	{
		return std::ranges::find_first_of(entityA.m_leafSectors, entityB.m_leafSectors) != entityA.m_leafSectors.end();
	}

	std::vector< std::shared_ptr< OctreeSector > >
	AbstractOctreeElement::getSharedLeafSectors (AbstractOctreeElement & entityA, AbstractOctreeElement & entityB) noexcept
	{
		std::vector< std::shared_ptr< OctreeSector > > intersections{};

		std::ranges::set_intersection(entityA.m_leafSectors,entityB.m_leafSectors,std::back_inserter(intersections));

		return intersections;
	}

	std::shared_ptr< OctreeSector >
	AbstractOctreeElement::mainSector () const noexcept
	{
		return m_mainSector;
	}

	const std::unordered_set< std::shared_ptr< OctreeSector > > &
	AbstractOctreeElement::leafSectors () const noexcept
	{
		return m_leafSectors;
	}

	bool
	AbstractOctreeElement::addLeafSector (const std::shared_ptr< OctreeSector > & sector) noexcept
	{
		return m_leafSectors.emplace(sector).second;
	}

	bool
	AbstractOctreeElement::removeLeafSector (const std::shared_ptr< OctreeSector > & sector) noexcept
	{
		return m_leafSectors.erase(sector) > 0;
	}
}
