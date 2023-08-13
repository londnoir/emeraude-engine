/*
 * Emeraude/Scenes/OctreeSector.hpp
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

/* C++ standard libraries */
#include <array>
#include <set>
#include <memory>

/* Local inclusions for inheritances. */
#include "Math/Cuboid.hpp"

/* Local inclusions for usages. */
#include "AbstractOctreeElement.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief The OctreeSector class.
	 * @extends std::enable_shared_from_this A sector must be able to self give his smart pointer.
	 * @extends Libraries::Math::Cuboid A sector act as a cube in the 3D space.
	 */
	class OctreeSector final : public std::enable_shared_from_this< OctreeSector >, public Libraries::Math::Cuboid< float >
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"OctreeSector"};

			static constexpr auto XPositiveYPositiveZPositive = 0UL;
			static constexpr auto XPositiveYPositiveZNegative = 1UL;
			static constexpr auto XPositiveYNegativeZPositive = 2UL;
			static constexpr auto XPositiveYNegativeZNegative = 3UL;
			static constexpr auto XNegativeYPositiveZPositive = 4UL;
			static constexpr auto XNegativeYPositiveZNegative = 5UL;
			static constexpr auto XNegativeYNegativeZPositive = 6UL;
			static constexpr auto XNegativeYNegativeZNegative = 7UL;

			/** @brief The status of a sector after a content check. */
			enum class SectorStatus
			{
				Unchanged,
				Grew,
				Reduced
			};

			/**
			 * @brief Constructs the root sector.
			 * @note If parent is null, the sector will be a root sector.
			 * @param maximum The highest limit of the root sector.
			 * @param minimum The lowest limit of the root sector.
			 */
			OctreeSector (const Libraries::Math::Vector< 3, float > & maximum, const Libraries::Math::Vector< 3, float > & minimum) noexcept;

			/**
			 * @brief Constructs a child sector.
			 * @param maximum The highest limit of the child sector.
			 * @param minimum The lowest limit of the child sector.
			 * @param parentSector A reference to the parent sector smart pointer.
			 * @param slot The slot where the sub-sector is built.
			 */
			OctreeSector (const Libraries::Math::Vector< 3, float > & maximum, const Libraries::Math::Vector< 3, float > & minimum, const std::shared_ptr< OctreeSector > & parentSector, size_t slot) noexcept;

			/** @brief Deleted copy constructor. */
			OctreeSector (const OctreeSector & copy) = delete;

			/** @brief Deleted move constructor. */
			OctreeSector (OctreeSector && copy) = delete;

			/** @brief Deleted assignment operator. */
			OctreeSector & operator= (const OctreeSector & other) = delete;

			/** @brief Deleted move assignment operator. */
			OctreeSector & operator= (OctreeSector && other) = delete;

			/**
			 * @brief Returns the slot of a sub-sector.
			 * @warning It this sector is root, the value will be the max for a size_t.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t slot () const noexcept;

			/**
			 * @brief Returns true if the sector is the top of the tree.
			 * @return bool
			 */
			[[nodiscard]]
			bool isRoot () const noexcept;

			/**
			 * @brief Returns true if the sector is a endpoint in the tree.
			 * @return bool
			 */
			[[nodiscard]]
			bool isLeaf () const noexcept;

			/**
			 * @brief Returns the level below the root of this sector.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t getDepth () const noexcept;

			/**
			 * @brief Returns the parent sector.
			 * @warning this can be nullptr. Check if the sector is root before.
			 * @return shared_ptr< OctreeSector >
			 */
			[[nodiscard]]
			std::shared_ptr< OctreeSector > parentSector () noexcept;

			/**
			 * @brief Returns the parent sector.
			 * @warning this can be nullptr. Check if the sector is root before.
			 * @return shared_ptr< OctreeSector >
			 */
			[[nodiscard]]
			std::shared_ptr< const OctreeSector > parentSector () const noexcept;

			/**
			 * @brief Returns the root sector.
			 * @return shared_ptr< OctreeSector >.
			 */
			[[nodiscard]]
			std::shared_ptr< OctreeSector > getRootSector () noexcept;

			/**
			 * @brief Returns the root sector.
			 * @return shared_ptr< const OctreeSector >.
			 */
			[[nodiscard]]
			std::shared_ptr< const OctreeSector > getRootSector () const noexcept;

			/**
			 * @brief Returns the sub sector list.
			 * @warning This can be a list of empty sector. Check if the sector is leaf before.
			 * @return array< shared_ptr< OctreeSector >, 8 > &
			 */
			[[nodiscard]]
			std::array< std::shared_ptr< OctreeSector >, 8 > & subSectors () noexcept;

			/**
			 * @brief Returns the sub sector list.
			 * @warning This can be a list of empty sector. Check if the sector is leaf before.
			 * @return const array< shared_ptr< OctreeSector >, 8 > &
			 */
			[[nodiscard]]
			const std::array< std::shared_ptr< OctreeSector >, 8 > & subSectors () const noexcept;

			/**
			 * @brief Adds an element to the tree at the level of this sector and below.
			 * @param element A reference to an element smart pointer.
			 * @return bool
			 */
			bool addElement (const std::shared_ptr< AbstractOctreeElement > & element) noexcept;

			/**
			 * @brief Removes an element from the tree this level and below.
			 * @param element A reference to an element smart pointer.
			 * @return bool
			 */
			bool removeElement (const std::shared_ptr< AbstractOctreeElement > & element) noexcept;

			/**
			 * @brief Checks if an element is still or not in this sector and below.
			 * @param element A reference to an element smart pointer.
			 * @return bool
			 */
			bool checkElementOverlap (const std::shared_ptr< AbstractOctreeElement > & node) noexcept;

			/**
			 * @brief Returns the number of elements present in this sector.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t elementCount () const noexcept;

			/**
			 * @brief Returns the element list of the sector.
			 * @return const std::set< std::shared_ptr< AbstractOctreeElement > > &
			 */
			[[nodiscard]]
			const std::set< std::shared_ptr< AbstractOctreeElement > > & elements () const noexcept;

			/**
			 * @brief Tries to find the first named element in the octree.
			 * @param name A reference to a string
			 * @return std::shared_ptr< AbstractOctreeElement >
			 */
			[[nodiscard]]
			std::shared_ptr< AbstractOctreeElement > getFirstElementNamed (const std::string & name) const noexcept;

			/**
			 * @brief Returns a list of surrounding leaf sectors.
			 * @param includeThisSector Include the current sector to the list.
			 * @return vector< shared_ptr< OctreeSector > >
			 */
			[[nodiscard]]
			std::vector< std::shared_ptr< const OctreeSector > > getSurroundingSectors (bool includeThisSector) const noexcept;

			/**
			 * @brief Destroy the sector tree.
			 * @note This must be called from root sector.
			 * @return void
			 */
			void destroyTree () noexcept;

			/**
			 * @brief Enables or not the automatic subdivision of sectors.
			 * @param state The state.
			 */
			static void enableAutoExpand (bool state) noexcept;

			/**
			 * @brief Sets the element limit for a sector.
			 * @note Minimum is 8.
			 * @param count The numbe of element a sector can contains before expanding.
			 */
			static void setAutoExpandAt (size_t count) noexcept;

		private:

			static bool s_enableAutoExpand;
			static size_t s_autoExpandAt;

			/**
			 * @brief Checks the sector content to expand or collapse it and returns if the sector is a leaf or not.
			 * @return bool
			 */
			bool isStillLeaf () noexcept;

			/**
			 * @brief Adds an element to the tree at the level of this sector and below.
			 * @param element A reference to the element smart pointer.
			 * @param boundingBox The precomputed absolute bounding box of the element.
			 * @return bool
			 */
			bool addElement (const std::shared_ptr< AbstractOctreeElement > & element, const Cuboid< float > & boundingBox) noexcept;

			/**
			 * @brief Adds an element to the tree at the level of this sector and below.
			 * @param element A reference to the element smart pointer.
			 * @param position The precomputed absolute position of the element.
			 * @return bool
			 */
			bool addElement (const std::shared_ptr< AbstractOctreeElement > & element, const Libraries::Math::Vector< 3, float > & position) noexcept;

			/**
			 * @brief Adds an element to the sector node set and link it back to the sector (if its a leaf).
			 * @param element A reference to the element smart pointer.
			 * @return bool
			 */
			bool makeLink (const std::shared_ptr< AbstractOctreeElement > & element) noexcept;

			/**
			 * @brief Checks if an element is still or not in this sector and below.
			 * @param element A reference to the element smart pointer.
			 * @param boundingBox The precomputed absolute bounding box of the element.
			 * @return bool
			 */
			bool checkElementOverlap (const std::shared_ptr< AbstractOctreeElement > & element, const Cuboid< float > & boundingBox) noexcept;

			/**
			 * @brief Checks if an element is still or not in this sector and below.
			 * @param element A reference to the element smart pointer.
			 * @param position The precomputed absolute position of the element.
			 * @return bool
			 */
			bool checkElementOverlap (const std::shared_ptr< AbstractOctreeElement > & element, const Libraries::Math::Vector< 3, float > & position) noexcept;

			/**
			 * @brief Expands this sector to eight new ones.
			 * @return bool.
			 */
			bool expand () noexcept;

			/**
			 * @brief Merges the sectors underlying this one.
			 * @return bool.
			 */
			bool collapse () noexcept;

			std::shared_ptr< OctreeSector > m_parentSector{};
			std::array< std::shared_ptr< OctreeSector >, 8 > m_subSectors{};
			std::set< std::shared_ptr< AbstractOctreeElement > > m_elements{};
			size_t m_slot = std::numeric_limits< size_t >::max();
	};
}
