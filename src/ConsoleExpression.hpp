/*
 * Emeraude/ConsoleExpression.hpp
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

/* C/C++ standard libraries. */
#include <sstream>
#include <string>
#include <vector>

namespace Emeraude
{
	/**
	 * @brief The ConsoleExpression class
	 */
	class ConsoleExpression
	{
		public:

			/**
			 * @brief Constructs a console expression.
			 * @param command A reference to a string for the command.
			 */
			explicit ConsoleExpression (const std::string & command = {}) noexcept;

			/**
			 * @brief Returns whether the expression is valid.
			 * @return bool
			 */
			[[nodiscard]]
			bool isValid () const noexcept;

			/**
			 * @brief Returns whether the expression has parameter.
			 * @return bool
			 */
			[[nodiscard]]
			bool hasParameter () const noexcept;

			/**
			 * @brief Returns the next identifier.
			 * @return std::string
			 */
			std::string nextIdentifier () noexcept;

			/**
			 * @brief Returns a reference to the list of identifiers.
			 * @return const std::vector< std::string > &
			 */
			[[nodiscard]]
			const std::vector< std::string > & identifiers () const noexcept;

			/**
			 * @brief Returns the command name.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & commandName () const noexcept;

			/**
			 * @brief Returns the first parameter.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string firstParameter () const noexcept;

			/**
			 * @brief Returns a reference to the list of parameters.
			 * @return const std::vector< std::string > &
			 */
			[[nodiscard]]
			const std::vector< std::string > & parameters () const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const ConsoleExpression & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const ConsoleExpression & obj) noexcept;

		private:

			/**
			 * @brief complete
			 * @param buffer
			 * @param where
			 */
			static void complete (std::string & buffer, std::vector< std::string > & where) noexcept;

			/**
			 * @brief complete
			 * @param buffer
			 * @param where
			 */
			static void complete (std::string & buffer, std::string & where) noexcept;

			std::vector< std::string > m_identifiers{};
			std::string m_functionName{};
			std::vector< std::string > m_parameters{};
			size_t m_identifierLevel = 0;
	};
}
