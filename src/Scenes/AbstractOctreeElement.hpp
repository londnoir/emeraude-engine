/*
 * Emeraude/Scenes/AbstractOctreeElement.hpp
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

#pragma once

/* C/C++ standard libraries. */
#include <unordered_set>
#include <memory>

/* Local inclusions for inheritances. */
#include "NamedItem.hpp"
#include "LocatableInterface.hpp"

namespace Emeraude::Scenes
{
	/* Forward declarations */
	class OctreeSector;

	/**
	 * @brief An abstract class defining an element insertable to the octree sector system.
	 * @extends Libraries::NamedItem A element in the octree must be named to ease identification.
	 * @extends Emeraude::Scenes::LocatableInterface A octree element has a position in the 3D world. The inheritance is virtual because of MovableTrait usage.
	 */
	class AbstractOctreeElement : public Libraries::NamedItem, virtual public LocatableInterface
	{
		friend class OctreeSector;

		public:

			/**
			 * @brief Destructs the abstract octree element.
			 */
			~AbstractOctreeElement () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractOctreeElement (const AbstractOctreeElement & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractOctreeElement (AbstractOctreeElement && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractOctreeElement & operator= (const AbstractOctreeElement & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractOctreeElement & operator= (AbstractOctreeElement && copy) noexcept = default;

			/**
			 * @brief Returns whether this entity is present on a specific sector.
			 * @param sector A reference to an OctreeSector smart pointer.
			 * @param checkOnlyLeaves Set to check only the end-of-tree sectors. Default false.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isPresentIn (const std::shared_ptr< OctreeSector > & sector, bool checkOnlyLeaves = false) const noexcept final;

			/**
			 * @brief Returns whether at least one sector is shared between two entities.
			 * @param entityA A reference to the first entity.
			 * @param entityB A reference to the second entity.
			 * @return bool
			 */
			[[nodiscard]]
			static bool hasSharedLeafSector (AbstractOctreeElement & entityA, AbstractOctreeElement & entityB) noexcept;

			/**
			 * @brief Returns the list of shared leaf sectors with an other entity.
			 * @note If you only want to know if entities are sharing the same sector, use AbstractOctreeSectorElement::hasSharedLeafSector() instead.
			 * @param a A reference to the first entity.
			 * @param b A reference to the second entity.
			 * @return bool
			 */
			[[nodiscard]]
			static std::vector< std::shared_ptr< OctreeSector > > getSharedLeafSectors (AbstractOctreeElement & entityA, AbstractOctreeElement & entityB) noexcept;

			/**
			 * @brief Returns the main sector smart pointer of the entity.
			 * @return shared_ptr< OctreeSector >
			 */
			[[nodiscard]]
			virtual std::shared_ptr< OctreeSector > mainSector () const noexcept final;

			/**
			 * @brief Returns sectors where the entity is present.
			 * @return const unordered_set< shared_ptr< OctreeSector > > &
			 */
			[[nodiscard]]
			virtual const std::unordered_set< std::shared_ptr< OctreeSector > > & leafSectors () const noexcept final;

			/**
			 * @brief Returns whether the octree element is renderable or not.
			 * @todo Poorly designed. Find an other way to complete this early need.
			 * @return bool
			 */
			[[deprecated("Must be replaced by a better mechanism of detection")]]
			[[nodiscard]]
			virtual bool isRenderable () const noexcept = 0;

			/**
			 * @brief Returns whether the octree element is physical or not.
			 * @todo Poorly designed. Find an other way to complete this early need.
			 * @return bool
			 */
			[[deprecated("Must be replaced by a better mechanism of detection")]]
			[[nodiscard]]
			virtual bool hasPhysicalObjectProperties () const noexcept = 0;

		protected:

			/**
			 * @brief Constructs an abstract octree element.
			 * @param name A reference to a string for the name of the element.
			 */
			explicit AbstractOctreeElement (const std::string & name) noexcept;

		private:

			/**
			 * @brief Adds leaf sector.
			 * @param sector A reference to an octree sector smart pointer.
			 * @return bool
			 */
			virtual bool addLeafSector (const std::shared_ptr< OctreeSector > & sector) noexcept final;

			/**
			 * @brief Removes leaf sector.
			 * @param sector sector A reference to an octree sector smart pointer.
			 * @return bool
			 */
			virtual bool removeLeafSector (const std::shared_ptr< OctreeSector > & sector) noexcept final;

			std::shared_ptr< OctreeSector > m_mainSector{};
			std::unordered_set< std::shared_ptr< OctreeSector > > m_leafSectors{};
	};
}
