/*
 * Emeraude/Input/KeyboardController.hpp
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

/* Local inclusions for inheritances. */
#include "ControllerInterface.hpp"

/* Local inclusions for usages. */
#include "KeyboardTypes.hpp"

namespace Emeraude::Input
{
	/**
	 * @brief The keyboard controller class
	 * @extends Emeraude::Input::ControllerInterface This is an input controller.
	 */
	class KeyboardController final : public ControllerInterface
	{
		public:

			/**
			 * @brief Construct a default keyboard controller.
			 */
			KeyboardController () noexcept = default;

			/** @copydoc Emeraude::Input::ControllerInterface::isConnected() */
			[[nodiscard]]
			bool isConnected () const noexcept override;

			/** @copydoc Emeraude::Input::ControllerInterface::showRawState() */
			[[nodiscard]]
			std::string getRawState () const noexcept override;

			/**
			 * @brief Returns whether a specific key is pressed.
			 * @param key The keycode.
			 * @return bool
			 */
			[[nodiscard]]
			bool isKeyPressed (int key) const noexcept;

			/**
			 * @brief Returns whether any key on keyboard is pressed.
			 * @return bool
			 */
			[[nodiscard]]
			bool isAnyKeyPressed () const noexcept;

			/**
			 * @brief Returns whether a specific key is released.
			 * @param key The keycode.
			 * @return bool
			 */
			[[nodiscard]]
			bool isKeyReleased (int key) const noexcept;

			/**
			 * @brief This function is called by the input manager to update device state.
			 * @note This must be called by the main thread.
			 * @param window The handle responsible for input listening.
			 */
			static void readDeviceState (GLFWwindow * window) noexcept;

			/**
			 * @brief Returns whether a modifier key is pressed.
			 * @param modKey The modifier key being tested.
			 * @param modifiers The current state of modifier keys.
			 * @return bool
			 */
			[[nodiscard]]
			static
			inline
			bool
			isModifierKeyPressed (ModKey modKey, int modifiers) noexcept
			{
				return ( modifiers & modKey ) > 0;
			}

		private:

			static std::array< bool, 349 > s_deviceState; // NOLINT NOTE: Special state copy.
	};
}
