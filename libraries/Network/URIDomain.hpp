/*
 * Libraries/Network/URIDomain.hpp
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
#include <cstdint>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

/* Local inclusions for usages. */
#include "Hostname.hpp"

namespace Libraries::Network
{
	/**
	 * @brief The URI domain class.
	 * @note [//[user-info@]host[:port]]
	 */
	class URIDomain final
	{
		public:

			static const std::array< std::string, 4 > Bases;

			/**
			 * @brief Constructs a default URI domain.
			 */
			URIDomain () noexcept = default;

			/**
			 * @brief Constructs an URI domain.
			 * @param hostname The host part of the URI domain [std::move].
			 * @param port The port used by the URI domain. Default 0.
			 * @param base The base [std::move]. Default "//".
			 * @param username The username used by the URI domain [std::move]. Default none.
			 * @param password The password used by the URI domain [std::move]. Default none.
			 * @param options The user login options used by the URI domain. Default none.
			 */
			explicit URIDomain (Hostname hostname, uint32_t port = 0, std::string base = "//", std::string username = {}, std::string password = {}, const std::map< std::string, std::string > & options = {}) noexcept;

			/**
			 * @brief Constructs an URI domain from a raw string.
			 * @param rawString A reference to a string.
			 */
			explicit URIDomain (std::string rawString) noexcept;

			/**
			 * @brief Sets the URI domain base.
			 * @param base A reference to a string.
			 * @return void
			 */
			void setBase (const std::string & base) noexcept;

			/**
			 * @brief Sets the URI domain user credentials.
			 * @param username A reference to a string.
			 * @param password A reference to a string.
			 * @return void
			 */
			void setUserinfo (const std::string & username, const std::string & password) noexcept;

			/**
			 * @brief Sets the URI domain user name.
			 * @note Separate method from URIDomain::setUserinfo().
			 * @param username A reference to a string.
			 * @return void
			 */
			void setUsername (const std::string & username) noexcept;

			/**
			 * @brief Sets the URI domain user password.
			 * @note Separate method from URIDomain::setUserinfo().
			 * @param password A reference to a string.
			 * @return void
			 */
			void setPassword (const std::string & password) noexcept;

			/**
			 * @brief Replaces the options of the URI domain.
			 * @param options A reference to a map.
			 * @return void
			 */
			void setOptions (const std::map< std::string, std::string > & options) noexcept;

			/**
			 * @brief Adds an option to the URI domain.
			 * @param name A reference to a string.
			 * @param value A reference to a string.
			 * @return void
			 */
			void addOption (const std::string & name, const std::string & value) noexcept;

			/**
			 * @brief Sets the hostname of the URI domain.
			 * @param hostname A reference to a Hostname.
			 * @return void
			 */
			void setHostname (const Hostname & hostname) noexcept;

			/**
			 * @brief Sets the port to the URI domain.
			 * @param port The port number as an unsigned 32 bits integer.
			 * @return void
			 */
			void setPort (uint32_t port) noexcept;

			/**
			 * @brief Returns the user informations part.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string userinfo () const noexcept;

			/**
			 * @brief Returns the username.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & username () const noexcept;

			/**
			 * @brief Returns the password.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & password () const noexcept;

			/**
			 * @brief Returns a list of URI domain options.
			 * @return const std::map< std::string, std::string > &
			 */
			[[nodiscard]]
			const std::map< std::string, std::string > & options () const noexcept;

			/**
			 * @brief Returns the URI domain hostname.
			 * @return const Hostname &
			 */
			[[nodiscard]]
			const Hostname & hostname () const noexcept;

			/**
			 * @brief Returns the URI domain host.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string host () const noexcept;

			/**
			 * @brief Returns the URI domain port.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t port () const noexcept;

			/**
			 * @brief Returns the URI domain base.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string base () const noexcept;

			/**
			 * @brief Returns whether the host is empty.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			empty () const noexcept
			{
				return m_host.empty();
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const URIDomain & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const URIDomain & obj) noexcept;

		private:

			/**
			 * @brief Extracts the port from a raw string.
			 * @param string A reference to a string.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string extractPort (const std::string & string) noexcept;

			/**
			 * @brief Extracts the base from a raw string.
			 * @param string A reference to a string.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string extractBase (const std::string & string) noexcept;

			/**
			 * @brief Extracts the user informations from a raw string.
			 * @param string A reference to a string.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string extractUserInfos (const std::string & string) noexcept;

			/**
			 * @brief Parses the user informations.
			 * @param string A reference to a string.
			 * @return void
			 */
			void parseUserInfos (const std::string & string) noexcept;

			std::string m_base{};
			std::string m_username{};
			std::string m_password{};
			std::map< std::string, std::string > m_options{};
			Hostname m_host{};
			uint32_t m_port{0};
	};
}
