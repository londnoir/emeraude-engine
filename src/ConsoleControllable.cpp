/*
 * Emeraude/ConsoleControllable.cpp
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

#include "ConsoleControllable.hpp"

/* C/C++ standard libraries. */
#include <iostream>

/* Local inclusions */
#include "Console.hpp"
#include "String.hpp"
#include "Tracer.hpp"

namespace Emeraude
{
	using namespace Libraries;

	constexpr auto TracerTag{"ConsoleControllable"};

	ConsoleControllable::ConsoleControllable (std::string consoleIdentifier) noexcept
		: m_identifier(std::move(consoleIdentifier))
	{

	}

	ConsoleControllable::~ConsoleControllable ()
	{
		auto * console = Console::instance();

		/* Auto remove from console. */
		if ( console != nullptr )
		{
			console->remove(*this);
		}
	}

	bool
	ConsoleControllable::execute (ConsoleExpression & expression) noexcept
	{
		/* Checks for next identifier. */
		auto identifier = expression.nextIdentifier();

		/* If we got a next identifier. */
		if ( !identifier.empty() )
		{
			/* Checks for sub object */
			auto objectIt = std::ranges::find_if(m_consoleObjects, [identifier] (const auto & objectIt) {
				return objectIt.first == identifier;
			});

			if ( objectIt != m_consoleObjects.cend() )
			{
				return objectIt->second->execute(expression);
			}

			TraceError{TracerTag} << "Identifier '" << identifier << "' not found !";

			return false;
		}

		/* If empty we are at the right level, and we try to execute the command. */

		/* Checks for built-in function about a level. */
		if ( this->checkBuiltInCommands(expression) )
		{
			return true;
		}

		/* Checks for object commands */
		auto commandIt = std::ranges::find_if(m_commands, [expression] (const auto & commandIt) {
			return commandIt.first == expression.commandName();
		});

		if ( commandIt != m_commands.cend() )
		{
			const auto & command = commandIt->second.command();

			return ( command(expression.parameters()) == 0 );
		}

		TraceError{TracerTag} << "Object command '" << expression.commandName() << "()' not found !";

		return false;
	}

	void
	ConsoleControllable::complete (ConsoleExpression & expression, std::string & identifier, std::vector< std::string > & suggestions) const noexcept
	{
		identifier = expression.nextIdentifier();

		if ( identifier.empty() )
		{
			return;
		}

		/* For each register object in the console.
		 * If we got a perfect match, we stop the search. */
		if ( Console::loopOverObjectsName(m_consoleObjects, expression, identifier, suggestions) )
		{
			return;
		}

		/* For each possible command. */
		for ( const auto & commandIt : m_commands )
		{
			/* Object name is smaller than input, skip it. */
			if ( identifier.length() > commandIt.first.length() )
			{
				continue;
			}

			/* Perfect match. */
			if ( identifier == commandIt.first )
			{
				continue;
			}

			/* Checks for mismatching. */
			auto mismatch = false;

			for ( auto chr = 0U; chr < identifier.length(); chr++ )
			{
				/* Object name mismatch characters from input. */
				if ( commandIt.first[chr] != identifier[chr] )
				{
					mismatch = true;

					break;
				}
			}

			if ( !mismatch )
			{
				suggestions.emplace_back(commandIt.first + "()");
			}
		}
	}

	const std::string &
	ConsoleControllable::identifier () const noexcept
	{
		return m_identifier;
	}

	void
	ConsoleControllable::bindCommand (const std::string & commandNames, const ConsoleCommand & command, const std::string & help) noexcept
	{
		auto commandNamesList = String::explode(commandNames, ',', false);

		for ( auto & commandName : commandNamesList )
		{
			auto commandIt = m_commands.find(commandName);

			if ( commandIt != m_commands.cend() )
			{
				TraceError{TracerTag} << "Command '" << commandName << "' already exists !";

				continue;
			}

			m_commands.emplace(commandName, CommandContainer(command, help));
		}
	}

	void
	ConsoleControllable::unbindCommand (const std::string & commandNames) noexcept
	{
		auto commandNamesList = String::explode(commandNames, ',', false);

		for ( auto & commandName : commandNamesList )
		{
			auto commandIt = m_commands.find(commandName);

			if ( commandIt != m_commands.end() )
			{
				m_commands.erase(commandIt);
			}
		}
	}

	bool
	ConsoleControllable::registerToConsole () noexcept
	{
		if ( !Console::instance()->add(*this) )
		{
			TraceError{TracerTag} << "Unable to register this object to the console.";

			return false;
		}

		return true;
	}

	void
	ConsoleControllable::writeToConsole (const std::string & message, Severity severity) noexcept
	{
		Console::instance()->write(message, severity);
	}

	bool
	ConsoleControllable::registerToObject (ConsoleControllable & object) noexcept
	{
		if ( object.m_consoleObjects.find(m_identifier) != object.m_consoleObjects.cend() )
		{
			TraceError{TracerTag} << "Sub object named '" << m_identifier << "' already exists !";

			return false;
		}

		object.m_consoleObjects.emplace(m_identifier, this);

		return true;
	}

	bool
	ConsoleControllable::checkBuiltInCommands (const ConsoleExpression & expression) noexcept
	{
		if ( expression.commandName() == "lsfunc" )
		{
			for ( const auto & commandIt : m_commands )
			{
				this->writeToConsole(Blob() << commandIt.first << " (" << commandIt.second.help() << ')');
			}

			return true;
		}

		if ( expression.commandName() == "lsobj" )
		{
			for ( const auto & objectIt : m_consoleObjects )
			{
				this->writeToConsole(Blob() << "'" << objectIt.first << "'");
			}

			return true;
		}

		return false;
	}
}
