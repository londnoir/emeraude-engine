/*
 * Libraries/Network/Query.hpp
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

/* C/C++ standard libraries */
#include <iostream>
#include <map>
#include <string>

namespace Libraries::Network
{
	/**
	 * @brief The URL query class.
	 */
	class Query final
	{
		public:

			/**
			 * @brief Constructs a default query.
			 */
			Query () noexcept = default;

			/**
			 * @brief Constructs a query.
			 * @warning There is no check with this version.
			 * @param variables Query variables.
			 */
			explicit Query (const std::map< std::string, std::string > & variables) noexcept;

			/**
			 * @brief Constructs a query from a raw string.
			 * @param rawString std::string.
			 */
			explicit Query (const std::string & rawString) noexcept;

			/**
			 * @brief Replaces the query variables.
			 * @param variables A reference to a map of variables.
			 * @return void
			 */
			void setVariables (const std::map< std::string, std::string > & variables) noexcept;

			/**
			 * @brief Adds a variable to the existing ones.
			 * @param key A reference to a string for the variable name.
			 * @param value A reference to a string for the variable value.
			 * @return void
			 */
			void addVariable (const std::string & key, const std::string & value) noexcept;

			/**
			 * @brief Returns the list of query variables.
			 * @return const std::map< std::string, std::string > &
			 */
			[[nodiscard]]
			const std::map< std::string, std::string > & variables () const noexcept;

			/**
			 * @brief Returns whether the query variables are empty.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			empty () const noexcept
			{
				return m_variables.empty();
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Query & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const Query & obj) noexcept;

		private:

			std::map< std::string, std::string > m_variables{};
	};
}
