/*
 * Libraries/Network/URL.hpp
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

/* Local inclusions for inheritances. */
#include "URI.hpp"

namespace Libraries::Network
{
	/**
	 * @brief Old class to define a URL.
	 * @deprecated Use URI directly instead.
	 * @extends Libraries::Network::URI
	 */
	class URL final : public URI
	{
		public:

			/**
			 * @brief Constructs a default URL.
			 */
			URL () noexcept = default;

			/**
			 * @brief Constructs an URL from a string.
			 * @param path A reference to a string.
			 */
			explicit URL (const std::string & path) noexcept;

			/**
			 * @brief Returns whether the URL is valid.
			 * @return bool.
			 */
			[[nodiscard]]
			bool isValid () const noexcept;

			/**
			 * @brief Returns whether the URL is valid.
			 * @param path A reference to a string.
			 * @return bool.
			 */
			[[nodiscard]]
			static bool isURL (const std::string & path) noexcept;
	};
}
