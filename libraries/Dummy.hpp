/*
 * Libraries/Dummy.hpp
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

namespace Libraries
{
	/**
	 * @brief Dummy abstract class to identify special method in use.
	 */
	class [[maybe_unused]] Dummy
	{
		public:

			/**
			 * @brief Default constructor.
			 */
			Dummy () noexcept;

			/**
			 * @brief Parametric constructor.
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
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Dummy & operator= (const Dummy & copy) noexcept;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Dummy & operator= (Dummy && copy) noexcept;

			/**
			 * @brief Destructor.
			 */
			virtual ~Dummy ();

			/**
			 * @brief Sets a value.
			 * @param value The value.
			 * @return void
			 */
			void setValue (int value);

			/**
			 * @brief Returns the value.
			 * @return int
			 */
			[[nodiscard]]
			int value () const;

		private:

			int m_value{-1};
	};
}
