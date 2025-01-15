/*
 * src/Argument.hpp
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
#include <ostream>
#include <string>

namespace Emeraude
{
	/**
	 * @brief This class describe one argument.
	 */
	class Argument final
	{
		public:

			/**
			 * @brief Constructs a argument.
			 * @param noValue Set to true for simple argument with no value.
			 */
			explicit Argument (bool noValue = false) noexcept;

			/**
			 * @brief Constructs an argument with a value.
			 * @param value A reference to a string [std::move].
			 */
			explicit Argument (std::string value) noexcept;

			/**
			 * @brief Returns whether the argument is a simple switch with no value.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isSwitch () const noexcept
			{
				return m_isSwitch;
			}

			/**
			 * @brief Returns whether the argument is present.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isPresent () const noexcept
			{
				if ( m_isSwitch )
				{
					return true;
				}

				return !m_value.empty();
			}

			/**
			 * @brief Returns the value associated to the argument.
			 * @note This can be empty.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string &
			value () const noexcept
			{
				return m_value;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Argument & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const Argument & obj) noexcept;

		private:

			std::string m_value;
			bool m_isSwitch{false};
	};
}
