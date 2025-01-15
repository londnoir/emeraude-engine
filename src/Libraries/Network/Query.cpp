/*
 * src/Libraries/Network/Query.cpp
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

#include "Query.hpp"

/* STL inclusions. */
#include <algorithm>
#include <vector>

/* Local inclusions. */
#include "Libraries/String.hpp"

namespace Libraries::Network
{
	Query::Query (const std::map< std::string, std::string > & variables) noexcept
		: m_variables(variables)
	{

	}

	Query
	Query::fromString (const std::string & string) noexcept
	{
		Query query;

		const auto variables = String::explode(string, '&');

		for ( const auto & variable : variables )
		{
			const auto definition = String::explode(variable, '=');

			if ( definition.size() == 2 )
			{
				query.addVariable(definition[0], definition[1]);
			}
			else
			{
				query.addVariable(definition[0], "");
			}
		}

		return query;
	}

	std::ostream &
	operator<< (std::ostream & out, const Query & obj)
	{
		std::vector< std::string > variables(obj.m_variables.size());

		std::transform(obj.m_variables.cbegin(), obj.m_variables.cend(), std::back_inserter(variables), [] (const auto & variable) {
			return variable.first + '=' + variable.second;
		});

		return out << String::implode(variables, '&');
	}

	std::string
	to_string (const Query & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
