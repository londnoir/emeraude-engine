/*
 * Libraries/SourceCodeParser.hpp
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
#include <map>
#include <string>
#include <vector>

namespace Libraries
{
	/**
	 * @brief Manipulates a source code to annote it.
	 */
	class SourceCodeParser final
	{
		public:

			/**
			 * @brief Constructs a source code parser.
			 * @param sourceCode A pointer to a source code C string.
			 */
			explicit SourceCodeParser (const std::string & sourceCode) noexcept;

			/**
			 * @brief Adds a notice to the source code.
			 * @param line The number of the line.
			 * @param column The number of the character in the line.
			 * @param notice A reference to string.
			 * @return void
			 */
			void notice (size_t line, size_t column, const std::string & notice) noexcept;

			/**
			 * @brief Adds a notice to the end of the source code.
			 * @param notice A reference to string.
			 * @return void
			 */
			void notice (const std::string & notice) noexcept;

			/**
			 * @brief Returns the parsed source code with line number.
			 * @param number Line number char width. Default 5.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string getParsedSourceCode (int numberWidth = 5) const noexcept;

		private:

			std::vector< std::string > m_lines{};
			std::map< size_t, std::multimap< size_t, std::string > > m_notices{};
			std::vector< std::string > m_endNotices{};
	};
}
