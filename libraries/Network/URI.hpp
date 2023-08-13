/*
 * Libraries/Network/URI.hpp
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
#include <sstream>
#include <string>

/* Local inclusions for usages. */
#include "Path/Path.hpp"
#include "Query.hpp"
#include "URIDomain.hpp"

namespace Libraries::Network
{
	/**
	 * @brief The URI class.
	 * @note [protocol:][//[user-info@]host[:port]][path]
	 */
	class URI
	{
		public:

			static constexpr auto HttpProtocol = "http:";
			static constexpr auto SecureHttpProtocol = "https:";

			/**
			 * @brief Constructs a default URI.
			 */
			URI () noexcept = default;

			/**
			 * @brief Constructs an URI from a raw string.
			 * @param rawURI A reference to a string.
			 */
			explicit URI (const std::string & rawURI) noexcept;

			/**
			 * @brief Assignment operator for std::string.
			 * @param rawURI A reference of a string for URI.
			 * @return URI &
			 */
			URI & operator= (const std::string & rawURI) noexcept;

			/**
			 * @brief Sets the scheme of the URI.
			 * @param scheme A reference to a string.
			 * @return void
			 */
			void setScheme (const std::string & scheme) noexcept;

			/**
			 * @brief Sets the URI domain.
			 * @param uriDomain A reference to an URIDomain.
			 * @return void
			 */
			void setURIDomain (const URIDomain & uriDomain) noexcept;

			/**
			 * @brief Sets the path of the URI.
			 * @param path A reference to a path.
			 * @return void
			 */
			void setPath (const Path::Path & path) noexcept;

			/**
			 * @brief Sets the query of the URI.
			 * @param query A reference to a query.
			 * @return void
			 */
			void setQuery (const Query & query) noexcept;

			/**
			 * @brief Sets the fragment of the URI.
			 * @param fragment A reference to a string.
			 * @return void
			 */
			void setFragment (const std::string & fragment) noexcept;

			/**
			 * @brief scheme
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & scheme () const noexcept;

			/**
			 * @brief uriDomain
			 * @return const URIDomain &
			 */
			[[nodiscard]]
			const URIDomain & uriDomain () const noexcept;

			/**
			 * @brief path
			 * @return const Path::Path &
			 */
			[[nodiscard]]
			const Path::Path & path () const noexcept;

			/**
			 * @brief query
			 * @return const Query &
			 */
			[[nodiscard]]
			const Query & query () const noexcept;

			/**
			 * @brief fragment
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & fragment () const noexcept;

			/**
			 * @brief resource
			 * @return std::string
			 */
			[[nodiscard]]
			std::string resource () const noexcept;

			/**
			 * @brief empty
			 * @return bool
			 */
			[[nodiscard]]
			bool empty () const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const URI & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const URI & obj) noexcept;

		private:

			/**
			 * @brief checkSimplePath
			 * @param string
			 * @return bool
			 */
			[[nodiscard]]
			bool checkSimplePath (const std::string & string) noexcept;

			/**
			 * @brief extractScheme
			 * @param string
			 * @return std::string
			 */
			[[nodiscard]]
			std::string extractScheme (const std::string & string) noexcept;

			/**
			 * @brief extractFragment
			 * @param string
			 * @return std::string
			 */
			[[nodiscard]]
			std::string extractFragment (const std::string & string) noexcept;

			/**
			 * @brief extractQuery
			 * @param string
			 * @return std::string
			 */
			[[nodiscard]]
			std::string extractQuery (const std::string & string) noexcept;

			/**
			 * @brief extractURIDomain
			 * @param string
			 * @return std::string
			 */
			[[nodiscard]]
			std::string extractURIDomain (const std::string & string) noexcept;

			/**
			 * @brief parseRawString
			 * @param rawString
			 * @return bool
			 */
			bool parseRawString (std::string rawString) noexcept;

			std::string m_scheme{};
			URIDomain m_uriDomain{};
			Path::Path m_path{};
			Query m_query{};
			std::string m_fragment{};
	};
}
