/*
 * Libraries/FlagTrait.hpp
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

/* C/C++ standard libraries */
#include <cstdint>
#include <type_traits>

namespace Libraries
{
	/**
	 * @brief Adds the ability to use flags on object.
	 * @tparam The size of the flag. Default uint32_t.
	 */
	template< typename data_t = uint32_t, std::enable_if_t< std::is_integral_v< data_t >, bool > = false, std::enable_if_t< std::is_unsigned_v< data_t >, bool > = false >
	class FlagTrait
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			FlagTrait (const FlagTrait & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			FlagTrait (FlagTrait && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return FlagTrait &
			 */
			FlagTrait & operator= (const FlagTrait & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return FlagTrait &
			 */
			FlagTrait & operator= (FlagTrait && copy) noexcept = default;

			/**
			 * @brief Destructs the flag trait.
			 */
			virtual ~FlagTrait () = default;

			/**
			 * @brief Returns the raw flag value.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			flagBits () const noexcept
			{
				return m_flags;
			}

			/**
			 * @brief Returns whether a flag is enabled.
			 * @param flagBit The flag bit to check.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isFlagEnabled (data_t flagBit) const noexcept
			{
				return m_flags & flagBit;
			}

		protected:

			/**
			 * @brief Constructs a flag trait.
			 * @param flagBits The initial flag value.
			 */
			explicit FlagTrait (data_t flagBits) noexcept
				: m_flags(flagBits)
			{

			}

			/**
			 * @brief Set the flag bits value.
			 * @param flagBits The flag bits default value. Default reset to zero.
			 * @return void
			 */
			void
			setFlagBits (data_t flagBits = 0) noexcept
			{
				m_flags = flagBits;
			}

			/**
			 * @brief Enables a flag.
			 * @param flagBit The flag bit value.
			 * @return void
			 */
			void
			enableFlag (data_t flagBit) noexcept
			{
				m_flags |= flagBit;
			}

			/**
			 * @brief Disables a flag.
			 * @param flagBit The flag bit value.
			 * @return void
			 */
			void
			disableFlag (data_t flagBit) noexcept
			{
				m_flags = m_flags & ~flagBit;
			}

		private:

			data_t m_flags;
	};
}
