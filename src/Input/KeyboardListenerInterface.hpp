/*
 * Emeraude/Input/KeyboardListenerInterface.hpp
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

/* Local inclusion for inheritances. */
#include "AbstractInputListener.hpp"

/* Local inclusions for usages. */
#include "KeyboardTypes.hpp"

namespace Emeraude::Input
{
	/**
	 * @brief The class defines a keyboard input listener interface to be implemented by a service.
	 * @extends Emeraude::Input::AbstractInputListener
	 */
	class KeyboardListenerInterface : public AbstractInputListener
	{
		friend class Manager;

		public:

			/**
			 * @brief Destructs the keyboard input listener.
			 */
			~KeyboardListenerInterface () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			KeyboardListenerInterface (const KeyboardListenerInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			KeyboardListenerInterface (KeyboardListenerInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			KeyboardListenerInterface & operator= (const KeyboardListenerInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			KeyboardListenerInterface & operator= (KeyboardListenerInterface && copy) noexcept = default;

			/**
			 * @brief Enables the text mode.
			 * @param state The state.
			 */
			virtual void enableTextMode (bool state) noexcept final;

			/**
			 * @brief Returns whether the text mode is enabled or not.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isTextModeEnabled () const noexcept final;

			/**
			 * @brief Enables or not the keyboard listening with the input manager.
			 * @param state  The state.
			 * @return void
			 */
			virtual void enableKeyboardListening (bool state) noexcept final;

		protected:

			/**
			 * @brief Constructs a keyboard input listener.
			 * @param isOpaque Set whether the listener is opaque or not.
			 * @param enableTextMode Enable text mode.
			 * @param autoRegister Enable the auto registration of this listener to the manager.
			 */
			KeyboardListenerInterface (bool isOpaque, bool enableTextMode, bool autoRegister) noexcept;

		private:

			/**
			 * @brief Method to override to handle key pressing.
			 * @param key The keyboard universal key code.
			 * @param scanCode The system-dependent key code.
			 * @param modifiers The modifier keys mask.
			 * @param repeat Repeat state.
			 * @return bool
			 */
			virtual bool onKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept;

			/**
			 * @brief Method to override to handle key releasing.
			 * @param key The keyboard universal key code.
			 * @param scanCode The system-dependent key code.
			 * @param modifiers The modifier keys mask.
			 * @return bool
			 */
			virtual bool onKeyRelease (int key, int scanCode, int modifiers) noexcept;

			/**
			 * @brief Method to override to handle text typing.
			 * @param unicode The character unicode value.
			 * @param modifiers The modification keys state.
			 * @return bool
			 */
			virtual bool onCharacterType (unsigned int unicode, int modifiers) noexcept;

			/* Flag names. */
			static constexpr auto TextMode = 1UL;
	};
}
