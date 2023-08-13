/*
 * Emeraude/Input/PointerListenerInterface.hpp
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
#include "PointerTypes.hpp"

namespace Emeraude::Input
{
	// NOLINTBEGIN(readability-identifier-length)

	/**
	 * @brief The class defines a pointer input listener interface to be implemented by a service.
	 * @extends Emeraude::Input::AbstractInputListener
	 */
	class PointerListenerInterface : public AbstractInputListener
	{
		friend class Manager;

		public:

			/**
			 * @brief Destructs the pointer input listener.
			 */
			~PointerListenerInterface () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			PointerListenerInterface (const PointerListenerInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			PointerListenerInterface (PointerListenerInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			PointerListenerInterface & operator= (const PointerListenerInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			PointerListenerInterface & operator= (PointerListenerInterface && copy) noexcept = default;

			/**
			 * @brief Sets the absolute mode as pointing method.
			 * @param state The state.
			 */
			virtual void setAbsoluteMode (bool state) noexcept final;

			/**
			 * @brief Returns whether the pointing mode is absolute or relative.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isAbsoluteModeEnabled () const noexcept final;

			/**
			 * @brief Enables or not the pointer listening with the input manager.
			 * @param state  The state.
			 * @return void
			 */
			virtual void enablePointerListening (bool state) noexcept final;

		protected:

			/**
			 * @brief Constructs a pointer input listener.
			 * @param isOpaque Set whether the listener is opaque or not.
			 * @param isAbsoluteMode Enable absolute mode.
			 * @param autoRegister Enable the auto registration of this listener to the manager.
			 */
			PointerListenerInterface (bool isOpaque, bool isAbsoluteMode, bool autoRegister) noexcept;

		private:

			/**
			 * @brief Method to override to handle pointer entering this listener surface.
			 * @param x The X position of the pointer according to absolute or relative mode.
			 * @param y The Y position of the pointer according to absolute or relative mode.
			 * @return bool
			 */
			virtual bool onPointerEnter (float x, float y) noexcept;

			/**
			 * @brief Method to override to handle pointer leaving this listener surface.
			 * @param x The X position of the pointer according to absolute or relative mode.
			 * @param y The Y position of the pointer according to absolute or relative mode.
			 * @return bool
			 */
			virtual bool onPointerLeave (float x, float y) noexcept;

			/**
			 * @brief Method to override to handle pointer move.
			 * @param x The X position of the pointer according to absolute or relative mode.
			 * @param y The Y position of the pointer according to absolute or relative mode.
			 * @return bool
			 */
			virtual bool onPointerMove (float x, float y) noexcept;

			/**
			 * @brief Method to override to handle a pointer button press.
			 * @param x The X position of the pointer according to absolute or relative mode.
			 * @param y The Y position of the pointer according to absolute or relative mode.
			 * @param buttonNumber The button number of the pointer.
			 * @param modifiers The modification keys state. (From keyboard)
			 * @return bool
			 */
			virtual bool onButtonPress (float x, float y, int buttonNumber, int modifiers) noexcept;

			/**
			 * @brief Method to override to handle a pointer button release.
			 * @param x The X position of the pointer according to absolute or relative mode.
			 * @param y The Y position of the pointer according to absolute or relative mode.
			 * @param buttonNumber The button number of the pointer.
			 * @param modifiers The modification keys state.  (From keyboard)
			 * @return bool
			 */
			virtual bool onButtonRelease (float x, float y, int buttonNumber, int modifiers) noexcept;

			/**
			 * @brief Method to override to handle a pointer wheel change.
			 * @param x The X position of the pointer according to absolute or relative mode.
			 * @param y The Y position of the pointer according to absolute or relative mode.
			 * @param xOffset The X offset of the wheel.
			 * @param yOffset The Y offset of the wheel.
			 * @return bool
			 */
			virtual bool onMouseWheel (float x, float y, float xOffset, float yOffset) noexcept;

			/* Flag names. */
			static constexpr auto IsAbsoluteMode = 1UL;
	};

	// NOLINTEND(readability-identifier-length)
}
