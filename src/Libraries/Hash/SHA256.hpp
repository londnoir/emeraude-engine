/*
 * src/Libraries/Hash/SHA256.hpp
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
#include <array>
#include <cstddef>
#include <cstdint>

namespace Libraries::Hash
{
	/**
	 * @brief The SHA256 class
	 * @note http://www.zedwood.com/article/cpp-sha256-function
	 */
	class SHA256 final
	{
		public:

			static constexpr auto HashLength = 64UL;

			/**
			 * @brief Constructs the SHA512 hash object.
			 */
			SHA256 () noexcept = default;

			/**
			 * @brief processLogics
			 * @param message
			 * @param length
			 * @return void
			 */
			void update (const uint8_t * message, size_t length) noexcept;

			/**
			 * @brief final
			 * @param digest
			 * @return void
			 */
			void final (std::array< uint8_t, 32 > & digest) noexcept;

			/**
			 * @brief reset
			 * @return void
			 */
			void reset () noexcept;

		private:

			static constexpr auto BlockSize = 512UL / 8UL;

			static const std::array< uint32_t, 64 > sha256_k;

			/**
			 * @brief transform
			 * @param message
			 * @param length
			 * @return void
			 */
			void transform (const uint8_t * message, size_t length) noexcept;

			size_t m_totalLength{0};
			size_t m_length{0};
			std::array< uint8_t, 2 * BlockSize > m_block{};
			std::array< uint32_t, 8 > m_h{
				0x6a09e667,
				0xbb67ae85,
				0x3c6ef372,
				0xa54ff53a,
				0x510e527f,
				0x9b05688c,
				0x1f83d9ab,
				0x5be0cd19
			};
	};
}
