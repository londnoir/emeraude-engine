/*
 * Emeraude/Input/JoystickListenerInterface.hpp
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
#include "JoystickTypes.hpp"

namespace Emeraude::Input
{
	/**
	 * @brief The class defines a joystick input listener interface to be implemented by a service.
	 * @warning Unusable for now. GLFW doesn't provide a way to listen to a gamepad/joystick.
	 * @extends Emeraude::Input::AbstractInputListener
	 */
	class [[deprecated("Unusable for now. GLFW doesn't provide a way to listen to a gamepad/joystick. Use JoystickController instead.")]]
			JoystickListenerInterface : public AbstractInputListener
	{
		friend class Manager;

		public:

			/**
			 * @brief Destructs the joystick input listener.
			 */
			~JoystickListenerInterface () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			JoystickListenerInterface (const JoystickListenerInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			JoystickListenerInterface (JoystickListenerInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			JoystickListenerInterface & operator= (const JoystickListenerInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			JoystickListenerInterface & operator= (JoystickListenerInterface && copy) noexcept = default;

		protected:

			/**
			 * @brief Constructs a joystick input listener.
			 * @param autoRegister Enable the auto registration of this listener to the manager.
			 */
			explicit JoystickListenerInterface (bool isOpaque) noexcept;
	};
}
