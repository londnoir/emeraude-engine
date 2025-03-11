/*
 * src/Libs/FlagTrait.hpp
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
#include <cstdint>
#include <type_traits>

namespace EmEn::Libs
{
	/**
	 * @brief Adds the ability to use flags on object by using an integer and bitwise operations.
	 * @note Only the flags reading is public. This is intended for internal options of a class.
	 * @tparam data_t The size of the flag. Default uint32_t.
	 */
	template< typename data_t = uint32_t >
	requires (std::is_integral_v< data_t >, std::is_unsigned_v< data_t >)
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

			/**
			 * @brief Sets multiple flags in one shot.
			 * @warning This will erase all previous flags.
			 * @param flagBits The flag bits value.
			 * @return void
			 */
			void
			setFlagBits (data_t flagBits) noexcept
			{
				m_flags = flagBits;
			}

			/**
			 * @brief Resets all flag to zero.
			 * @note Sames as call FlagTrait::setFlagBits(0).
			 * @return void
			 */
			void
			resetFlagBits () noexcept
			{
				m_flags = 0;
			}

		private:

			data_t m_flags;
	};
}
