/*
 * src/Libraries/Dummy.hpp
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

namespace Libraries
{
	/**
	 * @brief Dummy abstract class to identify special method in use.
	 */
	class Dummy final
	{
		public:

			/**
			 * @brief Default constructor.
			 */
			Dummy () noexcept;

			/**
			 * @brief Parametric constructor.
			 * @param value An arbitrary value.
			 */
			explicit Dummy (int value) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Dummy (const Dummy & copy) noexcept;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Dummy (Dummy && copy) noexcept;

			/**
			 * @brief Assignment operator.
			 * @param copy A reference to the copied instance.
			 * @return Dummy &
			 */
			Dummy & operator= (const Dummy & copy) noexcept;

			/**
			 * @brief Move operator.
			 * @param copy A reference to the copied instance.
			 * @return Dummy &
			 */
			Dummy & operator= (Dummy && copy) noexcept;

			/**
			 * @brief Destructor.
			 */
			~Dummy ();

			/**
			 * @brief Sets a value.
			 * @param value The value.
			 * @return void
			 */
			void
			value (int value)
			{
				m_value = value;
			}

			/**
			 * @brief Returns the value.
			 * @return int
			 */
			[[nodiscard]]
			int
			value () const
			{
				return m_value;
			}

		private:

			int m_value{-1};
	};
}
