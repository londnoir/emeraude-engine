/*
 * src/ConsoleControllable.hpp
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

#pragma once

/* STL inclusions. */
#include <map>
#include <string>

/* Local inclusions for usages. */
#include "Libraries/BlobTrait.hpp"
#include "CommandContainer.hpp"
#include "ConsoleExpression.hpp"
#include "Types.hpp"

namespace Emeraude
{
	/**
	 * @brief Interface to register an object controllable with the console.
	 */
	class ConsoleControllable
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ConsoleControllable (const ConsoleControllable & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ConsoleControllable (ConsoleControllable && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return ConsoleControllable &
			 */
			ConsoleControllable & operator= (const ConsoleControllable & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return ConsoleControllable &
			 */
			ConsoleControllable & operator= (ConsoleControllable && copy) noexcept = default;

			/**
			 * @brief The destructor auto remove this object from the console.
			 */
			virtual ~ConsoleControllable ();

			/**
			 * @brief Returns the identifier of this object in the console.
			 * @return std::string
			 */
			[[nodiscard]]
			const std::string &
			identifier () const noexcept
			{
				return m_identifier;
			}

			/**
			 * @brief Register this controllable object below an other one.
			 * @param object A reference to the parent object.
			 * @return bool
			 */
			bool registerToObject (ConsoleControllable & object) noexcept;

			/**
			 * @brief Executes an expression from the console.
			 * @note This is a recursive method.
			 * @param expression An expression object from the console.
			 * @return bool
			 */
			bool execute (ConsoleExpression & expression) noexcept;

			/**
			 * @brief Tries to complete a expression from the console.
			 * @param expression An expression object from the console.
			 * @param identifier The identifier of the controlled object.
			 * @param suggestions List of suggestions to complete the expression.
			 */
			void complete (ConsoleExpression & expression, std::string & identifier, std::vector< std::string > & suggestions) const noexcept;

		protected:

			/**
			 * @brief Constructor that identifies by a name the new controllable object.
			 * @param consoleIdentifier A string to for the name of the object [std::move].
			 */
			explicit ConsoleControllable (std::string consoleIdentifier) noexcept;

			/**
			 * @brief Register a command for this console controllable object.
			 * @param commandNames The way of calling the command inside the console.
			 * @param command The command to execute in the container.
			 * @param help A way to explain that command. By default "NoHelp" will be display.
			 */
			void bindCommand (const std::string & commandNames, const ConsoleCommand & command, const std::string & help = {"No help"}) noexcept;

			/**
			 * @brief Removes a command from the console.
			 * @param commandNames The way of calling the command inside the console.
			 */
			void unbindCommand (const std::string & commandNames) noexcept;

			/**
			 * @brief Register this controllable object directly to the console.
			 * @return bool
			 */
			bool registerToConsole () noexcept;

			/**
			 * @brief Writes a message directly to the console.
			 * @param message The message to display in the console.
			 * @param severity The severity is used to color or emphasis the message. Default info.
			 * @return void
			 */
			void writeToConsole (const std::string & message, Severity severity = Severity::Info) noexcept;

			/**
			 * @brief Writes a message directly to the console.
			 * @note This is a shortcut to user the Libraries::Blob() utility.
			 * @param message The message to display in the console.
			 * @param severity The severity is used to color or emphasis the message. Default info.
			 * @return void
			 */
			void
			writeToConsole (const Libraries::BlobTrait & message, Severity severity = Severity::Info) noexcept
			{
				this->writeToConsole(message.get(), severity);
			}

		private:

			/**
			 * @brief checkBuiltInCommands
			 * @param expression
			 * @return bool
			 */
			[[nodiscard]]
			bool checkBuiltInCommands (const ConsoleExpression & expression) noexcept;

			std::string m_identifier;
			std::map< std::string, CommandContainer > m_commands;
			std::map< std::string, ConsoleControllable * > m_consoleObjects;
	};
}
