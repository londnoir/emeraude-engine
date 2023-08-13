/*
 * Emeraude/Scenes/OctreeSectorCrawler.hpp
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
#include <stack>
#include <type_traits>
#include <memory>

/* Local inclusions for usages. */
#include "OctreeSector.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief Utility class to crawl down the octree sector from a base sector.
	 */
	template< typename type_t, std::enable_if_t< std::is_class_v< OctreeSector >, bool > = false >
	class OctreeSectorCrawler final
	{
		public:

			/**
			 * @brief Constructs a crawler from a sector.
			 * @param baseSector From which sector to execute the crawling.
			 */
			OctreeSectorCrawler (const std::shared_ptr< type_t > & baseSector) noexcept
			{
				this->populateStack(baseSector);
			}

			/**
			 * @brief Returns whether a next sector exists.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			hasNextSector () const noexcept
			{
				return !m_sectors.empty();
			}

			/**
			 * @brief Returns the next sector.
			 * @return std::shared_ptr< type_t >
			 */
			[[nodiscard]]
			std::shared_ptr< type_t >
			nextSector () noexcept
			{
				if ( m_sectors.empty() )
					return nullptr;

				/* Gets the next sector */
				auto nextSector = m_sectors.top();

				/* Removes it from the stack. */
				m_sectors.pop();

				/* Prepares the next sectors. */
				this->populateStack(nextSector);

				return nextSector;
			}

		private:

			/**
			 * @brief Populates the stacks with sub sectors.
			 * @param currentSector A reference to the smart pointer of the current sector.
			 * @return void
			 */
			void
			populateStack (const std::shared_ptr< type_t > & currentSector) noexcept
			{
				if ( currentSector->isLeaf() )
					return;

				for ( const auto & sector : currentSector->subSectors() )
					m_sectors.emplace(sector);
			}

			std::stack< std::shared_ptr< type_t > > m_sectors{};
	};
}
