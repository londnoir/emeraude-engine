/*
 * src/Libraries/Network/Hostname.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "Hostname.hpp"

#include <ranges>

/* Local inclusions. */
#include "Libraries/String.hpp"

namespace Libraries::Network
{
	Hostname::Hostname (std::string subdomain, std::string domain) noexcept
		: m_subdomain(std::move(subdomain)), m_domain(std::move(domain))
	{

	}

	Hostname
	Hostname::fromString (const std::string & string) noexcept
	{
		Hostname hostname;

		if ( string.empty() )
		{
			return hostname;
		}

		const auto chunks = String::explode(string, '.');

		auto domainDone = false;

		std::vector< std::string > subdomain;
		std::vector< std::string > domain;

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
			hostname.setSubdomain(String::implode(subdomain, '.'));
		}

		if ( !domain.empty() )
		{
			hostname.setDomain(String::implode(domain, '.'));
		}

		return hostname;
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

	std::ostream &
	operator<< (std::ostream & out, const Hostname & obj)
	{
		return out << obj.name();
	}

	std::string
	to_string (const Hostname & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
