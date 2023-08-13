/*
 * Emeraude/Resources/Collection.hpp
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
#include <memory>
#include <vector>

/* Local inclusions */
#include "Utility.hpp"

namespace Emeraude::Resources
{
	/**
	 * @brief Resource collection hold several resource from the same type to ease random pick.
	 * @tparam resource_t The resource type.
	 */
	template< typename resource_t >
	class Collection
	{
		public:

			/**
			 * @brief Default constructors.
			 */
			Collection () noexcept = default;

			/**
			 * @brief add
			 * @param resource
			 */
			inline
			void
			add (const std::shared_ptr< resource_t > & resource)
			{
				m_collection.emplace_back(resource);
			}

			/**
			 * @brief pickOne
			 * @return std::shared_ptr< resource_t >
			 */
			std::shared_ptr< resource_t >
			pickOne () noexcept
			{
				if ( m_collection.empty() )
					return nullptr;

				if ( m_collection.size() == 1 )
					return *(m_collection.begin());

				const auto index = Libraries::Utility::random(0UL, m_collection.size() - 1);

				return m_collection.at(index);
			}

			/**
			 * @brief Returns whether the collection is empty;
			 * @return bool
			 */
			inline
			bool
			empty () noexcept
			{
				return m_collection.empty();
			}

			/**
			 * @brief clear
			 */
			inline
			void
			clear () noexcept
			{
				m_collection.clear();
			}

		private:

			std::vector< std::shared_ptr< resource_t > > m_collection;
	};
}
