/*
 * src/ConsoleExpression.cpp
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

#include "ConsoleExpression.hpp"

/* STL inclusions. */
#include <iostream>

/* Local inclusions. */
#include "Libraries/BlobTrait.hpp"
#include "Libraries/String.hpp"

namespace Emeraude
{
	using namespace Libraries;

	ConsoleExpression::ConsoleExpression (const std::string & command) noexcept
	{
		std::string buffer{};

		for ( auto character : command )
		{
			switch ( character )
			{
				/* Identifier separator. */
				case '.' :
					ConsoleExpression::complete(buffer, m_identifiers);
					break;

				/* Start of arguments. */
				case '(' :
					ConsoleExpression::complete(buffer, m_functionName);
					break;

				/* Argument separator. */
				case ',' :
				case ')' :
					ConsoleExpression::complete(buffer, m_parameters);
					break;

				default :
					buffer += character;
					break;
			}
		}

		/* Checks left character in 'buffer'. */
		if ( m_functionName.empty() )
		{
			ConsoleExpression::complete(buffer, m_identifiers);
		}
		else
		{
			ConsoleExpression::complete(buffer, m_parameters);
		}
	}

	bool
	ConsoleExpression::isValid () const noexcept
	{
		/* NOTE: It should be at least one identifier. */
		if ( m_identifiers.empty() )
		{
			return false;
		}

		/* NOTE: If there is no function name found, the command is pointless. */
		if ( m_functionName.empty() )
		{
			return false;
		}

		return true;
	}

	bool
	ConsoleExpression::hasParameter () const noexcept
	{
		return !m_parameters.empty();
	}

	std::string
	ConsoleExpression::nextIdentifier () noexcept
	{
		/* If no identifier or current level is at the end, return an empty string. */
		if ( m_identifiers.empty() || m_identifierLevel >= m_identifiers.size() )
		{
			return {};
		}

		auto identifier = m_identifiers[m_identifierLevel];

		m_identifierLevel++;

		return identifier;
	}

	const std::vector< std::string > &
	ConsoleExpression::identifiers () const noexcept
	{
		return m_identifiers;
	}

	const std::string &
	ConsoleExpression::commandName () const noexcept
	{
		return m_functionName;
	}

	std::string
	ConsoleExpression::firstParameter () const noexcept
	{
		if ( m_parameters.empty() )
		{
			return {};
		}

		return m_parameters[0];
	}

	const std::vector< std::string > &
	ConsoleExpression::parameters () const noexcept
	{
		return m_parameters;
	}

	void
	ConsoleExpression::complete (std::string & buffer, std::vector< std::string > & where) noexcept
	{
		if ( buffer.empty() )
		{
			return;
		}

		auto cleanBuffer = String::trim(buffer);

		if ( !cleanBuffer.empty() )
		{
			where.emplace_back(cleanBuffer);
		}

		buffer.clear();
	}

	void
	ConsoleExpression::complete (std::string & buffer, std::string & where) noexcept
	{
		if ( buffer.empty() )
		{
			return;
		}

		where = String::trim(buffer);

		buffer.clear();
	}

	std::ostream &
	operator<< (std::ostream & out, const ConsoleExpression & obj)
	{
		out << "Identifiers tree :\n";

		size_t num = 0;

		for ( const auto & identifier : obj.m_identifiers )
		{
			out << num++ << " : '" << identifier << "'\n";
		}

		out << "Function name : " << obj.m_functionName << "()\n";

		if ( !obj.m_parameters.empty() )
		{
			out << "Function parameters :\n";

			num = 0;

			for ( const auto & parameter : obj.m_parameters )
			{
				out << num++ << " : " << parameter << '\n';
			}
		}

		return out;
	}

	std::string
	to_string (const ConsoleExpression & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
