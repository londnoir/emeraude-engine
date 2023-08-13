/*
 * Libraries/Network/URI.cpp
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

#include "URI.hpp"

/* C/C++ standard libraries. */
#include <sstream>

/* Local inclusions */
#include "String.hpp"

namespace Libraries::Network
{
	URI::URI (const std::string & rawString) noexcept
	{
		if ( !this->parseRawString(rawString) )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", empty string !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
		}
	}

	URI &
	URI::operator= (const std::string & rawString) noexcept
	{
		if ( !this->parseRawString(rawString) )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", empty string !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
		}

		return *this;
	}

	bool
	URI::parseRawString (std::string rawString) noexcept
	{
		if ( rawString.empty() )
		{
			return false;
		}

		rawString = this->extractFragment(rawString);

		if ( rawString.empty() )
		{
			return false;
		}

		rawString = this->extractQuery(rawString);

		if ( rawString.empty() )
		{
			return false;
		}

		/* NOTE: Pre-check for simple path. */
		if ( this->checkSimplePath(rawString) )
		{
			return false;
		}

		rawString = this->extractScheme(rawString);

		if ( rawString.empty() )
		{
			return false;
		}

		rawString = this->extractURIDomain(rawString);

		if ( rawString.empty() )
		{
			return false;
		}

		m_path = Path::Path{rawString};

		return true;
	}

	[[nodiscard]]
	bool
	URI::checkSimplePath (const std::string & string) noexcept
	{
		for ( const auto & chunk : String::explode(string, '/') )
		{
			if ( chunk.find(':') != std::string::npos )
			{
				return false;
			}
		}

		this->setPath(Path::Path{string});

		return true;
	}

	std::string
	URI::extractScheme (const std::string & string) noexcept
	{
		auto chunks = String::explode(string, ':');

		if ( chunks.size() >= 2 )
		{
			this->setScheme(chunks[0]);

			chunks.erase(chunks.begin());

			return String::implode(chunks, ':');
		}

		return string;
	}

	std::string
	URI::extractFragment (const std::string & string) noexcept
	{
		const auto chunks = String::explode(string, '#');

		if ( chunks.size() >= 2 )
		{
			this->setFragment(chunks[1]);

			if ( chunks.size() > 2 )
			{
				std::cerr << __PRETTY_FUNCTION__ << ", multiple '#' char found in the URL !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
			}
		}

		return chunks[0];
	}

	std::string
	URI::extractQuery (const std::string & string) noexcept
	{
		const auto chunks = String::explode(string, '?');

		if ( chunks.size() >= 2 )
		{
			this->setQuery(Query{chunks[1]});

			if ( chunks.size() > 2 )
			{
				std::cerr << __PRETTY_FUNCTION__ << ", multiple '?' char found in the URL !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
			}
		}

		return chunks[0];
	}

	std::string
	URI::extractURIDomain (const std::string & string) noexcept
	{
		std::string tmpBase{};

		for ( const auto & base : URIDomain::Bases )
		{
			if ( string.starts_with(base) )
			{
				tmpBase = base;

				break;
			}
		}

		std::vector< std::string > chunks{};

		if ( tmpBase.empty() )
		{
			chunks = String::explode(string, '/');

			this->setURIDomain(URIDomain{chunks[0]});
		}
		else
		{
			chunks = String::explode(String::replace(tmpBase, "", string), '/');

			this->setURIDomain(URIDomain{tmpBase + chunks[0]});
		}

		chunks.erase(chunks.begin());

		return String::implode(chunks, '/');
	}

	void
	URI::setScheme (const std::string & scheme) noexcept
	{
		/* TODO: Le nom du schéma est une lettre suivie de n'importe quelle
		 * combinaison de lettres, de chiffres, du signe plus (+), du point (.)
		 * ou d'un tiret (-) et se termine par deux points (:). */
		m_scheme = scheme;
	}

	void
	URI::setURIDomain (const URIDomain & uriDomain) noexcept
	{
		m_uriDomain = uriDomain;
	}

	void
	URI::setPath (const Path::Path & path) noexcept
	{
		m_path = path;
	}

	void
	URI::setQuery (const Query & query) noexcept
	{
		m_query = query;
	}

	void
	URI::setFragment (const std::string & fragment) noexcept
	{
		m_fragment = fragment;
	}

	const std::string &
	URI::scheme () const noexcept
	{
		return m_scheme;
	}

	const URIDomain &
	URI::uriDomain () const noexcept
	{
		return m_uriDomain;
	}

	const Path::Path &
	URI::path () const noexcept
	{
		return m_path;
	}

	const Query &
	URI::query () const noexcept
	{
		return m_query;
	}

	const std::string &
	URI::fragment () const noexcept
	{
		return m_fragment;
	}

	std::string
	URI::resource () const noexcept
	{
		std::stringstream string{};

		if ( !m_path.empty() )
		{
			string << m_path;
		}

		if ( !m_query.empty() )
		{
			string << '?' << m_query;
		}

		return string.str();
	}

	bool
	URI::empty() const noexcept
	{
		if ( m_scheme.empty() )
		{
			return true;
		}

		if ( m_uriDomain.empty() )
		{
			return true;
		}

		return false;
	}

	std::ostream &
	operator<< (std::ostream & out, const URI & obj)
	{
		if ( !obj.m_scheme.empty() )
		{
			out << obj.m_scheme << ':';
		}

		if ( !obj.m_uriDomain.empty() )
		{
			out << obj.m_uriDomain;

			if ( !obj.m_path.empty() )
			{
				out << '/' << obj.m_path;
			}
		}
		else if ( !obj.m_path.empty() )
		{
			out << obj.m_path;
		}

		if ( !obj.m_query.empty() )
		{
			out << '?' << obj.m_query;
		}

		if ( !obj.m_fragment.empty() )
		{
			out << '#' << obj.m_fragment;
		}

		return out;
	}

	std::string
	to_string (const URI & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
