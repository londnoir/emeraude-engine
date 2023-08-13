/*
 * Emeraude/Input/AbstractInputListener.hpp
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

/* C/C++ standard libraries. */
#include <array>

namespace Emeraude::Input
{
	/**
	 * @brief This abstract class defines every input listener.
	 */
	class AbstractInputListener
	{
		public:

			enum class KeyState
			{
				Pressed,
				Released
			};

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractInputListener (const AbstractInputListener & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractInputListener (AbstractInputListener && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractInputListener &
			 */
			AbstractInputListener & operator= (const AbstractInputListener & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractInputListener &
			 */
			AbstractInputListener & operator= (AbstractInputListener && copy) noexcept = default;

			/**
			 * @brief Destructs the input listener.
			 */
			virtual ~AbstractInputListener () = default;

			/**
			 * @brief Sets whether the listener stops the propagation of processed events.
			 * @param state The state.
			 * @return void
			 */
			virtual void setOpaqueState (bool state) noexcept final;

			/**
			 * @brief Returns whether the listener stops the propagation of processed events.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isOpaque () const noexcept final;

		protected:

			/* Flag names. */
			static constexpr auto IsOpaque = 0UL;

			/**
			 * @brief Constructs an input listener.
			 * @param isOpaque Set whether the listener is opaque or not. Default false.
			 */
			explicit AbstractInputListener (bool isOpaque) noexcept;

			std::array< bool, 8 > m_listenerFlags{ // NOLINT NOTE: Managed by all listener in input directory for simplicity.
				false/*IsOpaque*/,
				false/*IsAbsoluteMode for pointerListener*/,
				false/*TextMode for keyboardListener*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
