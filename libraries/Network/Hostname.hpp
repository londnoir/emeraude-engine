/*
 * Libraries/Network/Hostname.hpp
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

namespace Libraries::Network
{
	/**
	 * @brief The Hostname class.
	 */
	class Hostname final
	{
		public:

			/**
			 * @brief Constructs a default hostname.
			 */
			Hostname () noexcept = default;

			/**
			 * @brief Constructs an hostname.
			 * @warning There is no check with this version.
			 * @param subdomain The subdomain part of the host [std::move].
			 * @param domain The domain part of the host [std::move].
			 */
			Hostname (std::string subdomain, std::string domain) noexcept;

			/**
			 * @brief Tries to construct an hostname from a raw string.
			 * @param rawHostname A reference to string for the hostname.
			 */
			explicit Hostname (const std::string & rawHostname) noexcept;

			/**
			 * @brief Assignment operator for std::string.
			 * @param rawHostname A reference to string for the hostname.
			 * @return Hostname &
			 */
			Hostname & operator= (const std::string & rawHostname) noexcept;

			/**
			 * @brief Sets the subdomain part of the host.
			 * @param name The subdomain name.
			 * @return void
			 */
			void setSubdomain (const std::string & name) noexcept;

			/**
			 * @brief Sets the domain part of the host.
			 * @param name The domain name.
			 * @return void
			 */
			void setDomain (const std::string & name) noexcept;

			/**
			 * @brief Returns the subdomain part of the host. ie, [www].example.co.uk
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & subdomain () const noexcept;

			/**
			 * @brief Returns the domain part of the host. ie, www.[example.co.uk]
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & domain () const noexcept;

			/**
			 * @brief Returns the name of the host. ie, [www.example.co.uk]
			 * @return std::string
			 */
			[[nodiscard]]
			std::string name () const noexcept;

			/**
			 * @brief Returns the TLD part of the host. ie, www.example.[co.uk]
			 * @return std::string
			 */
			[[nodiscard]]
			std::string tld () const noexcept;

			/**
			 * @brief Returns whether the hostname is empty.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			empty () const noexcept
			{
				return m_domain.empty();
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Hostname & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const Hostname & obj) noexcept;

		private:

			/**
			 * @brief Parses a raw string to create the hostname.
			 * @param rawString A reference to a string.
			 * @return bool
			 */
			bool parseRawString (const std::string & rawString) noexcept;

			std::string m_subdomain{};
			std::string m_domain{};
	};
}
