/*
 * Emeraude/Audio/Effects/Abstract.hpp
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
#include "Audio/AbstractObject.hpp"

namespace Emeraude::Audio::Effects
{
	/**
	 * @brief The base class for all OpenAL effects.
	 * @extends Emeraude::Audio::AbstractObject This is a base OpenAL object.
	 */
	class Abstract : public AbstractObject
	{
		public:

			/**
			 * @brief Destructs the effect.
			 */
			~Abstract () override;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Abstract (const Abstract & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Abstract (Abstract && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Abstract & operator= (const Abstract & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Abstract & operator= (Abstract && copy) noexcept = default;

			/** @copydoc Emeraude::Engine::Audio::AbstractObject::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept final;

			/**
			 * @brief Reset all properties to default value.
			 */
			virtual void resetProperties () noexcept = 0;

		protected:

			/**
			 * @brief Constructs a effect.
			 */
			Abstract () noexcept;
	};
}
