/*
 * Emeraude/Input/PointerController.hpp
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
#include "PointerTypes.hpp"

namespace Emeraude::Input
{
	/**
	 * @brief The pointer controller class.
	 * @extends Emeraude::Input::PointerController This is an input controller.
	 */
	class PointerController final : public ControllerInterface
	{
		public:

			/**
			 * @brief Constructs a default pointer.
			 */
			PointerController () noexcept = default;

			/** @copydoc Emeraude::Input::ControllerInterface::isConnected() */
			[[nodiscard]]
			bool isConnected () const noexcept override;

			/** @copydoc Emeraude::Input::ControllerInterface::showRawState() */
			[[nodiscard]]
			std::string getRawState () const noexcept override;

			/**
			 * @brief Returns the state of the pointer button.
			 * @param button
			 * @return bool
			 */
			[[nodiscard]]
			bool isButtonPressed (MouseButton button) const noexcept;

			/**
			 * @brief Returns whether any button is pressed.
			 * @return bool
			 */
			[[nodiscard]]
			bool isAnyButtonPressed () const noexcept;

			/**
			 * @brief Returns the state of the pointer button.
			 * @param button
			 * @return bool
			 */
			[[nodiscard]]
			bool isButtonReleased (MouseButton button) const noexcept;

			/**
			 * @brief xPosition
			 * @return double
			 */
			[[nodiscard]]
			double xPosition () const noexcept;

			/**
			 * @brief yPosition
			 * @return double
			 */
			[[nodiscard]]
			double yPosition () const noexcept;

			/** This function is called by the input manager to update device state.
			 * @note This must be called by the main thread. */
			static void readDeviceState (GLFWwindow * window) noexcept;

		private:

			static std::array< bool, 8 > s_deviceState; // NOLINT NOTE: Special state copy.
			static std::array< double, 2 > s_pointerPosition; // NOLINT NOTE: Special state copy.
	};
}
