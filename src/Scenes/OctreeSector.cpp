/*
 * Emeraude/Scenes/OctreeSector.cpp
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

#include "OctreeSector.hpp"

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Scenes
{
	using namespace Libraries;
	using namespace Libraries::Math;

	bool OctreeSector::s_enableAutoExpand = true;
	size_t OctreeSector::s_autoExpandAt = 32;

	OctreeSector::OctreeSector (const Vector< 3, float > & maximum, const Vector< 3, float > & minimum) noexcept
		: Cuboid(maximum, minimum)
	{

	}

	OctreeSector::OctreeSector (const Vector< 3, float > & maximum, const Vector< 3, float > & minimum, const std::shared_ptr< OctreeSector > & parentSector, size_t slot) noexcept
		: Cuboid(maximum, minimum), m_parentSector(parentSector), m_slot(slot)
	{

	}

	size_t
	OctreeSector::slot () const noexcept
	{
		return m_slot;
	}

	bool
	OctreeSector::isRoot () const noexcept
	{
		return m_parentSector == nullptr;
	}

	bool
	OctreeSector::isLeaf () const noexcept
	{
		/*return std::any_of(m_subSectors.cbegin(), m_subSectors.cend(), [] (const auto & sectorSPtr) {
			return sectorSPtr == nullptr;
		});*/

		/* NOTE: Testing only the first sub-sector is fine. */
		return m_subSectors[XPositiveYPositiveZPositive] == nullptr;
	}

	size_t
	OctreeSector::getDepth () const noexcept
	{
		if ( this->isRoot() )
			return 0;

		size_t depth = 1;

		auto parent = m_parentSector;

		while ( !parent->isRoot() )
		{
			depth++;

			parent = parent->m_parentSector;
		}

		return depth;
	}

	std::shared_ptr< OctreeSector >
	OctreeSector::parentSector () noexcept
	{
		return m_parentSector;
	}

	std::shared_ptr< const OctreeSector >
	OctreeSector::parentSector () const noexcept
	{
		return m_parentSector;
	}

	std::shared_ptr< OctreeSector >
	OctreeSector::getRootSector () noexcept
	{
		auto currentSector = this->shared_from_this();

		while ( !currentSector->isRoot() )
			currentSector = currentSector->m_parentSector;

		return currentSector;
	}

	std::shared_ptr< const OctreeSector >
	OctreeSector::getRootSector () const noexcept
	{
		auto currentSector = this->shared_from_this();

		while ( !currentSector->isRoot() )
			currentSector = currentSector->m_parentSector;

		return currentSector;
	}

	std::array< std::shared_ptr< OctreeSector >, 8 > &
	OctreeSector::subSectors () noexcept
	{
		return m_subSectors;
	}

	const std::array< std::shared_ptr< OctreeSector >, 8 > &
	OctreeSector::subSectors () const noexcept
	{
		return m_subSectors;
	}

	bool
	OctreeSector::isStillLeaf () noexcept
	{
		if ( s_enableAutoExpand )
		{
			const auto elementCount = this->elementCount();

			/* If the number of elements ...
			 * ... exceeds the sector limit, we split down the sector. */
			if ( elementCount > s_autoExpandAt )
			{
				if ( this->expand() )
					return false;
			}
			/* ... is below the sector limit, we merge the sub-sectors. */
			else if ( elementCount < s_autoExpandAt / 2 )
			{
				if ( this->collapse() )
					return true;
			}
		}

		return this->isLeaf();
	}


	bool
	OctreeSector::addElement (const std::shared_ptr< AbstractOctreeElement > & element) noexcept
	{
		/* If a valid bounding box is available we will use it. */
		const auto & boundingBox = element->getWorldBoundingBox();

		if ( boundingBox.isValid() )
			return this->addElement(element, boundingBox);

		/* ... Else we will use the absolute position of the scene node. */
		return this->addElement(element, element->getWorldCoordinates().position());
	}

	bool
	OctreeSector::addElement (const std::shared_ptr< AbstractOctreeElement > & element, const Cuboid< float > & boundingBox) noexcept
	{
		if ( !this->isCollidingWith(boundingBox) )
			return false;

		if ( !this->makeLink(element) )
			return false;

		if ( !this->isStillLeaf() )
			for ( auto & subSector : m_subSectors )
				subSector->addElement(element, boundingBox);

		return true;
	}

	bool
	OctreeSector::addElement (const std::shared_ptr< AbstractOctreeElement > & element, const Vector< 3, float > & position) noexcept
	{
		if ( !this->isCollidingWith(position) )
			return false;

		if ( !this->makeLink(element) )
			return false;

		if ( !this->isStillLeaf() )
			for ( auto & subSector : m_subSectors )
				subSector->addElement(element, position);

		return true;
	}

	bool
	OctreeSector::makeLink (const std::shared_ptr< AbstractOctreeElement > & element) noexcept
	{
		if ( !m_elements.emplace(element).second )
			return false;

		/* If the sector is a leaf, link the node back to it (Class friendship). */
		if ( this->isLeaf() )
			element->addLeafSector(this->shared_from_this());

		return true;
	}

	bool
	OctreeSector::removeElement (const std::shared_ptr< AbstractOctreeElement > & element) noexcept
	{
		/* The node is not present in this sector. */
		if ( m_elements.find(element) == m_elements.end() )
			return false;

		/* Unlink the sector from the node (Class friendship). */
		element->removeLeafSector(this->shared_from_this());

		/* Removes the node from the set. */
		m_elements.erase(element);

		/* If this sector is a leaf, we are done. */
		if ( !this->isStillLeaf() )
		{
			for ( auto & subSector : m_subSectors )
				subSector->removeElement(element);
		}

		return true;
	}

	bool
	OctreeSector::checkElementOverlap (const std::shared_ptr< AbstractOctreeElement > & element) noexcept
	{
		/* If a valid bounding box is available we will use it. */
		{
			const auto & boundingBox = element->getWorldBoundingBox();

			if ( boundingBox.isValid() )
				return this->checkElementOverlap(element, boundingBox);
		}

		/* ... Else we will use the absolute position of the scene node. */
		return this->checkElementOverlap(element, element->getWorldCoordinates().position());
	}

	bool
	OctreeSector::checkElementOverlap (const std::shared_ptr< AbstractOctreeElement > & element, const Cuboid< float > & boundingBox) noexcept
	{
		if ( this->isCollidingWith(boundingBox) )
		{
			/* If the node is not registered to this sector, we add it. */
			if ( m_elements.find(element) == m_elements.cend() )
				return this->addElement(element, boundingBox);

			/* It this sector is not a leaf, we propagate the test. */
			if ( !this->isLeaf() )
			{
				for ( auto & subSector : m_subSectors )
					subSector->checkElementOverlap(element, boundingBox);
			}

			return true;
		}

		/* If this sector is not the root, we remove the node. */
		if ( !this->isRoot() )
			this->removeElement(element);

		return false;
	}

	bool
	OctreeSector::checkElementOverlap (const std::shared_ptr< AbstractOctreeElement > & element, const Vector< 3, float > & position) noexcept
	{
		if ( this->isCollidingWith(position) )
		{
			/* If the node is not registered to this sector, we add it. */
			if ( m_elements.find(element) == m_elements.cend() )
				return this->addElement(element, position);

			/* It this sector is not a leaf, we propagate the test. */
			if ( !this->isLeaf() )
			{
				for ( auto & subSector : m_subSectors )
					subSector->checkElementOverlap(element, position);
			}

			return true;
		}

		/* If this sector is not the root, we remove the node. */
		if ( !this->isRoot() )
			this->removeElement(element);

		return false;
	}

	size_t
	OctreeSector::elementCount () const noexcept
	{
		return m_elements.size();
	}

	const std::set< std::shared_ptr< AbstractOctreeElement > > &
	OctreeSector::elements () const noexcept
	{
		return m_elements;
	}

	[[nodiscard]]
	std::shared_ptr< AbstractOctreeElement >
	OctreeSector::getFirstElementNamed (const std::string & name) const noexcept
	{
		for ( const auto & element : m_elements )
			if ( element->name() == name )
				return element;

		return nullptr;
	}

	std::vector< std::shared_ptr< const OctreeSector > >
	OctreeSector::getSurroundingSectors (bool includeThisSector) const noexcept
	{
		std::vector< std::shared_ptr< const OctreeSector > > sectors;

		auto currentSector = this->shared_from_this();

		if ( includeThisSector )
			sectors.emplace_back(currentSector);

		auto level = 0UL;

		while ( !currentSector->isRoot() )
		{
			if ( level == 0UL )
			{
				/* Get its direct neighbors from parent sector. */
				for ( const auto & sector : this->parentSector()->m_subSectors )
				{
					if ( sector.get() == this )
						continue;

					sectors.emplace_back(sector);
				}

				continue;
			}

			level++;
		}

		return sectors;
	}

	void
	OctreeSector::enableAutoExpand (bool state) noexcept
	{
		s_enableAutoExpand = state;
	}

	void
	OctreeSector::setAutoExpandAt (size_t count) noexcept
	{
		s_autoExpandAt = std::max(8UL, count);
	}

	bool
	OctreeSector::expand () noexcept
	{
		/* NOTE: Only a leaf can expand itself. */
		if ( !this->isLeaf() )
			return false;

		const auto size = this->width() * 0.5F;
		const auto max = this->maximum();

		const auto minX = max[X] - size;
		const auto minY = max[Y] - size;
		const auto minZ = max[Z] - size;

		/* Init to max. */
		auto tmp = max;

		//tmp[X] = max[X];
		//tmp[Y] = max[Y];
		//tmp[Z] = max[Z];

		m_subSectors[XPositiveYPositiveZPositive] = std::make_shared< OctreeSector >(tmp, tmp - size, this->shared_from_this(), XPositiveYPositiveZPositive);

		//tmp[X] = max[X];
		//tmp[Y] = max[Y];
		tmp[Z] = minZ;

		m_subSectors[XPositiveYPositiveZNegative] = std::make_shared< OctreeSector >(tmp, tmp - size, this->shared_from_this(), XPositiveYPositiveZNegative);

		/* Reset only the Z axis to max. */
		//tmp[X] = max[X];
		tmp[Y] = minY;
		tmp[Z] = max[Z];

		m_subSectors[XPositiveYNegativeZPositive] = std::make_shared< OctreeSector >(tmp, tmp - size, this->shared_from_this(), XPositiveYNegativeZPositive);

		/* Y-axis is already to min. */
		//tmp[X] = max[X];
		//tmp[Y] = minY;
		tmp[Z] = minZ;

		m_subSectors[XPositiveYNegativeZNegative] = std::make_shared< OctreeSector >(tmp, tmp - size, this->shared_from_this(), XPositiveYNegativeZNegative);

		/* Reset to max except for X axis */
		tmp[X] = minX;
		tmp[Y] = max[Y];
		tmp[Z] = max[Z];

		m_subSectors[XNegativeYPositiveZPositive] = std::make_shared< OctreeSector >(tmp, tmp - size, this->shared_from_this(), XNegativeYPositiveZPositive);

		//tmp[X] = minX;
		//tmp[Y] = max[Y];
		tmp[Z] = minZ;

		m_subSectors[XNegativeYPositiveZNegative] = std::make_shared< OctreeSector >(tmp, tmp - size, this->shared_from_this(), XNegativeYPositiveZNegative);

		/* Reset only the Z axis to max. */
		//tmp[X] = minX;
		tmp[Y] = minY;
		tmp[Z] = max[Z];

		m_subSectors[XNegativeYNegativeZPositive] = std::make_shared< OctreeSector >(tmp, tmp - size, this->shared_from_this(), XNegativeYNegativeZPositive);

		/* Y-axis is already to min. */
		//tmp[X] = minX;
		//tmp[Y] = minY;
		tmp[Z] = minZ;

		m_subSectors[XNegativeYNegativeZNegative] = std::make_shared< OctreeSector >(tmp, tmp - size, this->shared_from_this(), XNegativeYNegativeZNegative);

		/* Now we redistribute the sector scene nodes to each sub-sector. */
		for ( auto & element : m_elements )
			for ( auto & subSector : m_subSectors )
				subSector->addElement(element);

		return true;
	}

	bool
	OctreeSector::collapse () noexcept
	{
		/* Cannot collapse a leaf or the root. */
		if ( this->isLeaf() || this->isRoot() )
			return false;

		/* Clear all sub sectors (and below sectors). */
		for ( auto & subSector : m_subSectors )
		{
			subSector->collapse();
			subSector.reset();
		}

		return true;
	}

	void
	OctreeSector::destroyTree () noexcept
	{
		if ( !this->isRoot() )
		{
			Tracer::error(ClassId, "This must be called from the root sector !");

			return;
		}

		m_elements.clear();

		if ( this->isLeaf() )
			return;

		for ( auto & subSector : m_subSectors )
		{
			subSector->collapse();
			subSector.reset();
		}
	}
}
