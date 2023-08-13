/*
 * Libraries/Network/Query.cpp
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

#include "Query.hpp"

/* C/C++ standard libraries. */
#include <algorithm>
#include <vector>

/* Local inclusions. */
#include "String.hpp"

namespace Libraries::Network
{
	Query::Query (const std::map< std::string, std::string > & variables) noexcept
		: m_variables(variables)
	{

	}

	Query::Query (const std::string & rawString) noexcept
	{
		auto chunks = String::explode(rawString, '&');

		for ( auto & chunk : chunks )
		{
			auto variable = String::explode(chunk, '=');

			if ( variable.size() == 2 )
			{
				m_variables.emplace(variable[0], variable[1]);
			}
			else
			{
				m_variables.emplace(variable[0], "");
			}
		}
	}

	void
	Query::setVariables (const std::map< std::string, std::string > & variables) noexcept
	{
		m_variables = variables;
	}

	void
	Query::addVariable (const std::string & key, const std::string & value) noexcept
	{
		m_variables.emplace(key, value);
	}

	const std::map< std::string, std::string > &
	Query::variables () const noexcept
	{
		return m_variables;
	}

	std::ostream &
	operator<< (std::ostream & out, const Query & obj)
	{
		std::vector< std::string > variables{};
		variables.resize(obj.m_variables.size());

		std::transform(obj.m_variables.cbegin(), obj.m_variables.cend(), std::back_inserter(variables), [] (const auto & variable) {
			return variable.first + '=' + variable.second;
		});

		return out << String::implode(variables, '&');
	}

	std::string
	to_string (const Query & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
