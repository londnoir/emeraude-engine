/*
 * Emeraude/Input/JoystickController.hpp
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
#include "JoystickTypes.hpp"

namespace Emeraude::Input
{
	static constexpr auto JoystickMaxAxis  = 6;
	static constexpr auto JoystickMaxButtons = 16;
	static constexpr auto JoystickMaxHats = 4;

	struct JoystickState
	{
		std::array< float, 6 > axes{0.0F}; // NOLINT(*-magic-numbers)
		std::array< bool, JoystickMaxButtons > buttons{false};
		std::array< JoystickHatDirection, JoystickMaxHats >hats{Center};
	};

	/**
	 * @brief The joystick controller class.
	 * @extends Emeraude::Input::ControllerInterface This is an input controller.
	 */
	class JoystickController final : public ControllerInterface
	{
		public:

			/**
			 * @brief Constructs a joystick controller.
			 * @param deviceID The joystick identifier.
			 */
			explicit JoystickController (int deviceID = -1) noexcept;

			/** @copydoc Emeraude::Input::ControllerInterface::isConnected() */
			[[nodiscard]]
			bool isConnected () const noexcept override;

			/** @copydoc Emeraude::Input::ControllerInterface::showRawState() */
			[[nodiscard]]
			std::string getRawState () const noexcept override;

			/**
			 * @brief Returns the device id.
			 * @return int
			 */
			[[nodiscard]]
			int deviceID () const noexcept;

			/**
			 * @brief Attaches the to device identifier.
			 * @param deviceID The joystick identifier.
			 * @return void
			 */
			void attachDeviceID (int deviceID) noexcept;

			/**
			 * @brief Detaches the device.
			 * @return void
			 */
			inline
			void
			detachDevice () noexcept
			{
				this->attachDeviceID(-1);
			}

			/**
			 * @brief setAxisThreshold
			 * @param value
			 */
			void setAxisThreshold (float value) noexcept;

			/**
			 * @brief setAxisSensitivity
			 * @param multiplier
			 */
			void setAxisSensitivity (float multiplier) noexcept;

			/**
			 * @brief axisThreshold
			 * @return float
			 */
			[[nodiscard]]
			float axisThreshold () const noexcept;

			/**
			 * @brief axisSensitivity
			 * @return float
			 */
			[[nodiscard]]
			float axisSensitivity () const noexcept;

			/**
			 * @brief axeValue
			 * @param axe
			 * @return float
			 */
			[[nodiscard]]
			float axeValue (JoystickAxis axe) const noexcept;

			/**
			 * @brief isButtonPressed
			 * @param buttonNum
			 * @return bool
			 */
			[[nodiscard]]
			bool isButtonPressed (int buttonNum) const noexcept;

			/**
			 * @brief isButtonReleased
			 * @param buttonNum
			 * @return bool
			 */
			[[nodiscard]]
			bool isButtonReleased (int buttonNum) const noexcept;

			/**
			 * @brief hatValue
			 * @param hatNum
			 * @return JoystickHatDirection
			 */
			[[nodiscard]]
			JoystickHatDirection hatValue (int hatNum) const noexcept;

			/**
			 * @brief This function is called by the input manager to update device state.
			 * @note This must be called by the main thread.
			 */
			static void readDeviceState (GLFWwindow * window, int deviceID) noexcept;

			/**
			 * @brief clearDeviceState
			 * @param deviceID
			 */
			static void clearDeviceState (int deviceID) noexcept;

		private:

			static std::array< JoystickState, 16 > s_devicesState; // NOLINT NOTE: Special state copy.

			int m_deviceID{-1};
			float m_threshold{0.15F}; // NOLINT(*-magic-numbers)
			float m_multiplier{4.0F}; // NOLINT(*-magic-numbers)
	};
}
