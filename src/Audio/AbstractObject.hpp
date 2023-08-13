/*
 * Emeraude/Audio/AbstractObject.hpp
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

/* Third-party libraries */
#include "Third-Party-Inclusion/openal.hpp"

namespace Emeraude::Audio
{
	/**
	 * @brief Base class for every OpenAL object which must be synced to audio memory.
	 */
	class AbstractObject
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractObject (const AbstractObject & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractObject (AbstractObject && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractObject &
			 */
			AbstractObject & operator= (const AbstractObject & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractObject &
			 */
			AbstractObject & operator= (AbstractObject && copy) noexcept = default;

			/**
			 * @brief Destructs an OpenAL object.
			 */
			virtual ~AbstractObject () = default;

			/**
			 * @brief Returns the OpenAL identifier on the hardware.
			 * @return ALuint
			 */
			[[nodiscard]]
			virtual ALuint identifier () const noexcept final;

			/**
			 * @brief Returns whether this object has an identifier on audio memory.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isCreated () const noexcept = 0;

		protected :

			/**
			 * @brief Constructs an OpenAL object.
			 */
			AbstractObject () noexcept = default;

			/**
			 * @brief Returns access to identifier for allocate and deallocate OpenAL object.
			 * @return ALuint *
			 */
			[[nodiscard]]
			ALuint * identifierPointer () noexcept;

			/**
			 * @brief Reset the OpenAL identifier.
			 * @return void
			 */
			void resetIdentifier () noexcept;

		private:

			ALuint m_identifier{0};
	};
}
