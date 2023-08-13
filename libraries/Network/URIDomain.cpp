/*
 * Libraries/Network/URIDomain.cpp
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

#include "URIDomain.hpp"

/* C/C++ standard libraries. */
#include <iostream>
#include <sstream>

/* Local inclusions */
#include "String.hpp"

namespace Libraries::Network
{
	const std::array< std::string, 4 > URIDomain::Bases{{
		{"//"},
		{"./"},
		{"../"},
		{"/"},
	}};

	URIDomain::URIDomain (Hostname host, uint32_t port, std::string base, std::string user, std::string password, const std::map< std::string, std::string > & options) noexcept
		: m_base(std::move(base)), m_username(std::move(user)), m_password(std::move(password)), m_options(options), m_host(std::move(host)), m_port(port)
	{

	}

	URIDomain::URIDomain (std::string rawString) noexcept
	{
		if ( rawString.empty() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", empty string !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		rawString = this->extractPort(rawString);

		if ( rawString.empty() )
		{
			return;
		}

		rawString = this->extractBase(rawString);

		if ( rawString.empty() )
		{
			return;
		}

		m_host = this->extractUserInfos(rawString);
	}

	std::string
	URIDomain::extractPort (const std::string & string) noexcept
	{
		const auto chunks = String::explode(string, ':');

		switch ( chunks.size() )
		{
			/* Port information present with user information. */
			case 3 :
				this->setPort(String::toNumber< unsigned int >(chunks[2]));

				return chunks[0] + ':' + chunks[1];

			/* Port information present. */
			case 2 :
				this->setPort(String::toNumber< unsigned int >(chunks[1]));

				/* NOTE: The ':' char was separating the user information. */
				return m_port == 0 ? string : chunks[0];

			case 1 :
				return chunks[0];

			default:
				std::cerr << __PRETTY_FUNCTION__ << ", invalid URI domain, multiple ':' char found !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

				return string;
		}
	}

	std::string
	URIDomain::extractBase (const std::string & string) noexcept
	{
		for ( const auto & base : URIDomain::Bases )
		{
			if ( !string.starts_with(base) )
			{
				continue;
			}

			this->setBase(base);

			return String::replace(base, "", string);
		}

		m_base.clear();

		return string;
	}

	std::string
	URIDomain::extractUserInfos (const std::string & string) noexcept
	{
		const auto chunks = String::explode(string, '@');

		switch ( chunks.size() )
		{
			/* User information present. */
			case 2 :
				this->parseUserInfos(chunks[0]);

				return chunks[1];

			/* No user information. */
			case 1 :
				return chunks[0];

			default:
				std::cerr << __PRETTY_FUNCTION__ << ", invalid URI domain, multiple '@' char found !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

				return string;
		}
	}

	void
	URIDomain::parseUserInfos (const std::string & string) noexcept
	{
		/* NOTE: ";AUTH" */
		auto chunks = String::explode(string, ';');

		for ( size_t index = 1; index < chunks.size(); index++ )
		{
			const auto option = String::explode(chunks[index], '=');

			if ( option.size() != 2 )
			{
				std::cerr << __PRETTY_FUNCTION__ << ", invalid URI domain option '" << chunks[index] << "' !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

				continue;
			}

			this->addOption(option[0], option[1]);
		}

		/* NOTE: "USER:PASSWORD" */
		chunks = String::explode(chunks[0], ':');

		switch ( chunks.size() )
		{
			case 2 :
				this->setPassword(chunks[1]);

				[[fallthrough]];

			case 1 :
				this->setUsername(chunks[0]);
				break;

			default:
				std::cerr << __PRETTY_FUNCTION__ << ", invalid URI domain, multiple ':' char found in user informations !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

				break;
		}
	}

	void
	URIDomain::setBase (const std::string & base) noexcept
	{
		m_base = base;
	}

	void
	URIDomain::setUserinfo (const std::string & user, const std::string & password) noexcept
	{
		m_username = user;

		if ( !password.empty() )
		{
			this->setPassword(password);
		}
	}

	void
	URIDomain::setUsername (const std::string & username) noexcept
	{
		m_username = username;
	}

	void
	URIDomain::setPassword (const std::string & password) noexcept
	{
		m_password = password;
	}

	void
	URIDomain::setOptions (const std::map< std::string, std::string > & options) noexcept
	{
		m_options = options;
	}

	void
	URIDomain::addOption (const std::string & name, const std::string & value) noexcept
	{
		m_options.emplace(name, value);
	}

	void
	URIDomain::setHostname (const Hostname & host) noexcept
	{
		m_host = host;
	}

	void
	URIDomain::setPort (uint32_t port) noexcept
	{
		if ( port > 65535 ) // NOLINT(*-magic-numbers)
		{
			std::cerr << __PRETTY_FUNCTION__ << ", " << port << " is an invalid port ! It should be between 1 to 65535." "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		m_port = port;
	}

	std::string
	URIDomain::userinfo () const noexcept
	{
		auto output = m_username;

		if ( !m_password.empty() )
		{
			output += ':' + m_password;
		}

		if ( !m_options.empty() )
		{
			for ( const auto &option: m_options )
			{
				output += ';' + option.first + '=' + option.second;
			}
		}

		return output;
	}

	const std::string &
	URIDomain::username () const noexcept
	{
		return m_username;
	}

	const std::string &
	URIDomain::password () const noexcept
	{
		return m_password;
	}

	const std::map< std::string, std::string > &
	URIDomain::options () const noexcept
	{
		return m_options;
	}

	const Hostname &
	URIDomain::hostname () const noexcept
	{
		return m_host;
	}

	std::string
	URIDomain::host () const noexcept
	{
		std::stringstream string{};

		string << m_host;

		if ( m_port > 0 )
		{
			string << m_port;
		}

		return string.str();
	}

	uint32_t
	URIDomain::port () const noexcept
	{
		return m_port;
	}

	std::string
	URIDomain::base () const noexcept
	{
		return m_base;
	}

	std::ostream &
	operator<< (std::ostream & out, const URIDomain & obj)
	{
		out << obj.m_base;

		if ( !obj.m_username.empty() )
		{
			out << obj.m_username;

			if ( !obj.m_password.empty() )
			{
				out << ':' << obj.m_password;
			}

			if ( !obj.m_options.empty() )
			{
				for ( const auto &option: obj.m_options )
				{
					out << ';' << option.first << '=' << option.second;
				}
			}

			out << '@';
		}

		out << obj.m_host;

		if ( obj.m_port > 0 )
		{
			out << ':' << obj.m_port;
		}

		return out;
	}

	std::string
	to_string (const URIDomain & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
