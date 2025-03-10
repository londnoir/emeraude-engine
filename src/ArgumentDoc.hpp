/*
 * src/ArgumentDoc.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <ostream>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "AbstractDoc.hpp"

namespace Emeraude
{
	/**
	 * @brief Class for argument documentation.
	 * @extends Emeraude::AbstractDoc The base documentation class.
	 */
	class ArgumentDoc final : public AbstractDoc
	{
		public:

			/**
			 * @brief Constructs an argumentation documentation.
			 * @param description A reference to a string [std::move].
			 * @param longName A reference to as string for the long name [std::move].
			 * @param shortName A char for the short name. Default none.
			 * @param options A reference to a string vector as options for the argument. Default none.
			 */
			ArgumentDoc (std::string description, std::string longName, char shortName = 0, const std::vector< std::string > & options = {}) noexcept;

			/**
			 * @brief Returns the argument long name.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string &
			longName () const noexcept
			{
				return m_longName;
			}

			/**
			 * @brief Returns the argument short name.
			 * @return char
			 */
			[[nodiscard]]
			char
			shortName () const noexcept
			{
				return m_shortName;
			}

			/**
			 * @brief Returns the list of options for the arguments. (optional)
			 * @return const std::vector< std::string > &
			 */
			[[nodiscard]]
			const std::vector< std::string > &
			options () const noexcept
			{
				return m_options;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const ArgumentDoc & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const ArgumentDoc & obj) noexcept;

		private:

			std::string m_longName;
			char m_shortName;
			std::vector< std::string > m_options;
	};
}
