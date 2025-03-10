/*
 * src/Libraries/LockableTrait.hpp
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
	 * @brief The lockable trait class. This adds the ability to lock the usage of an object.
	 */
	class LockableTrait
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			LockableTrait (const LockableTrait & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			LockableTrait (LockableTrait && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return LockableTrait &
			 */
			LockableTrait & operator= (const LockableTrait & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return LockableTrait &
			 */
			LockableTrait & operator= (LockableTrait && copy) noexcept = default;

			/**
			 * @brief virtual destructor.
			 */
			virtual ~LockableTrait () = default;

			/**
			 * @brief Returns whether the buffer is actually used in a transfer.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isLocked () const noexcept
			{
				return m_locked;
			}

			/**
			 * @brief Locks the usage.
			 * @return void
			 */
			void
			lock () noexcept
			{
				m_locked = true;
			}

			/**
			 * @brief Unlock the usage.
			 * @return void
			 */
			void
			unlock () noexcept
			{
				m_locked = false;
			}

		protected:

			/**
			 * @brief Default constructor.
			 */
			LockableTrait () noexcept = default;

		private:

			bool m_locked{false};
	};
}
