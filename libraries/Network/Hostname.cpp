/*
 * Libraries/Network/Hostname.cpp
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

#include "Hostname.hpp"

#include <ranges>

/* Local inclusions */
#include "String.hpp"

namespace Libraries::Network
{
	Hostname::Hostname (std::string subdomain, std::string domain) noexcept
		: m_subdomain(std::move(subdomain)), m_domain(std::move(domain))
	{

	}

	Hostname::Hostname (const std::string & rawHostname) noexcept
	{
		if ( !this->parseRawString(rawHostname) )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", empty string !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
		}
	}

	Hostname &
	Hostname::operator= (const std::string & rawHostname) noexcept
	{
		if ( !this->parseRawString(rawHostname) )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", empty string !" << "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
		}

		return *this;
	}

	bool
	Hostname::parseRawString (const std::string & rawString) noexcept
	{
		if ( rawString.empty() )
		{
			return false;
		}

		const auto chunks = String::explode(rawString, '.');

		auto domainDone = false;

		std::vector< std::string > subdomain{};
		std::vector< std::string > domain{};

		for ( const auto & chunk : std::ranges::reverse_view(chunks) )
		{
			if ( domainDone )
			{
				subdomain.insert(subdomain.begin(), chunk);

				continue;
			}

			if ( chunk.length() > 3 )
			{
				domainDone = true;
			}

			domain.insert(domain.begin(), chunk);
		}

		if ( !subdomain.empty() )
		{
			m_subdomain = String::implode(subdomain, '.');
		}

		if ( !domain.empty() )
		{
			m_domain = String::implode(domain, '.');
		}

		return true;
	}

	void
	Hostname::setSubdomain (const std::string & name) noexcept
	{
		m_subdomain = name;
	}

	void
	Hostname::setDomain (const std::string & name) noexcept
	{
		m_domain = name;
	}

	std::string
	Hostname::tld () const noexcept
	{
		const auto position = m_domain.find('.');

		if ( position != std::string::npos )
		{
			return m_domain.substr(position + 1);
		}

		return {};
	}

	const std::string &
	Hostname::subdomain () const noexcept
	{
		return m_subdomain;
	}

	const std::string &
	Hostname::domain () const noexcept
	{
		return m_domain;
	}

	std::string
	Hostname::name () const noexcept
	{
		if ( m_subdomain.empty() )
		{
			return m_domain;
		}

		return m_subdomain + '.' + m_domain;
	}

	std::ostream &
	operator<< (std::ostream & out, const Hostname & obj)
	{
		return out << obj.name();
	}

	std::string
	to_string (const Hostname & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
