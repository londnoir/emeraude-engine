/*
 * Emeraude/Audio/Buffer.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractObject.hpp"

/* Local inclusions for usages.*/
#include "WaveFactory/Wave.hpp"

namespace Emeraude::Audio
{
	/**
	 * @brief The Buffer class.
	 * @extends Emeraude::Audio::AbstractObject
	 */
	class Buffer final : public AbstractObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"AudioBuffer"};

			/**
			 * @brief Constructs a buffer.
			 */
			Buffer () noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Buffer (const Buffer & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Buffer (Buffer && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Buffer & operator= (const Buffer & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Buffer & operator= (Buffer && copy) noexcept = default;

			/**
			 *  @brief Destructs the buffer.
			 */
			~Buffer () override;

			/** @copydoc Emeraude::Engine::Audio::AbstractObject::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept override;

			/**
			 * @brief Copies data to the buffer.
			 * @param wave A reference to wave.
			 * @param chunkIndex The index of the chunk being copied. Default 0.
			 * @param length The length of the chunk. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool feedData (const Libraries::WaveFactory::Wave< short int > & wave, size_t chunkIndex = 0, size_t length = 0) noexcept;

			/**
			 * @brief Returns the frequency of the buffer.
			 * @return int
			 */
			[[nodiscard]]
			int frequency () const noexcept;

			/**
			 * @brief Returns the depth of the buffer.
			 * @return int
			 */
			[[nodiscard]]
			int bits () const noexcept;

			/**
			 * @brief Returns the number of channel of the buffer.
			 * @return int
			 */
			[[nodiscard]]
			int channels () const noexcept;

			/**
			 * @brief Returns the size in bytes of the buffer.
			 * @return int
			 */
			[[nodiscard]]
			int size () const noexcept;
	};
}
