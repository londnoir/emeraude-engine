/*
 * src/MasterControl/AbstractVirtualAudioDevice.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "AbstractVirtualDevice.hpp"

namespace Emeraude::MasterControl
{
	/**
	 * @brief This class define a virtual audio device. This can be player's ears, a microphone or in-game speaker.
	 * @extends Emeraude::MasterControl::AbstractVirtualDevice This is a virtual device.
	 */
	class AbstractVirtualAudioDevice : public AbstractVirtualDevice
	{
		public:

			/**
			 * @brief Destructs an abstract audio device.
			 */
			~AbstractVirtualAudioDevice () override = default;

		protected:

			/**
			 * @brief Constructs a virtual audio device.
			 * @param name The name of the device to find it withing the master control console.
			 * @param allowedConnexionType The type of connexion this virtual device allows. Default Both.
			 */
			explicit AbstractVirtualAudioDevice (const std::string & name, ConnexionType allowedConnexionType = ConnexionType::Both) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractVirtualAudioDevice (const AbstractVirtualAudioDevice & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractVirtualAudioDevice (AbstractVirtualAudioDevice && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractVirtualAudioDevice & operator= (const AbstractVirtualAudioDevice & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractVirtualAudioDevice & operator= (AbstractVirtualAudioDevice && copy) noexcept = default;

			/**
			 * @brief Event fired when a virtual audio device is connected to input.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param sourceDevice A pointer to the virtual audio device.
			 */
			virtual void onSourceConnected (AbstractVirtualAudioDevice * sourceDevice) noexcept;

			/**
			 * @brief Event fired when a virtual audio device is connected to output.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param targetDevice A pointer to the virtual audio device.
			 */
			virtual void onTargetConnected (AbstractVirtualAudioDevice * targetDevice) noexcept;

			/**
			 * @brief Event fired when a virtual audio device is disconnected to input.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param sourceDevice A pointer to the virtual audio device.
			 */
			virtual void onSourceDisconnected (AbstractVirtualAudioDevice * sourceDevice) noexcept;

			/**
			 * @brief Event fired when a virtual audio device is disconnected to output.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param targetDevice A pointer to the virtual audio device.
			 */
			virtual void onTargetDisconnected (AbstractVirtualAudioDevice * targetDevice) noexcept;

		private:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::onSourceConnected(AbstractVirtualDevice *) */
			void onSourceConnected (AbstractVirtualDevice * sourceDevice) noexcept final;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::onTargetConnected(AbstractVirtualDevice *) */
			void onTargetConnected (AbstractVirtualDevice * targetDevice) noexcept final;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::onSourceDisconnected(AbstractVirtualDevice *) */
			void onSourceDisconnected (AbstractVirtualDevice * sourceDevice) noexcept final;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::onTargetDisconnected(AbstractVirtualDevice *) */
			void onTargetDisconnected (AbstractVirtualDevice * targetDevice) noexcept final;
	};
}
