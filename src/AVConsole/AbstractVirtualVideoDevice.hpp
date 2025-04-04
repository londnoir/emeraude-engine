/*
 * src/AVConsole/AbstractVirtualVideoDevice.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "AbstractVirtualDevice.hpp"

namespace EmEn::AVConsole
{
	/**
	 * @brief This class define a virtual video device. This can be player's eyes, a camera or in-game screen.
	 * @extends EmEn::AVConsole::AbstractVirtualDevice This is a virtual device.
	 */
	class AbstractVirtualVideoDevice : public AbstractVirtualDevice
	{
		public:

			/**
			 * @brief Destructs an abstract video device.
			 */
			~AbstractVirtualVideoDevice () override = default;

			/**
			 * @brief Returns the video device type.
			 * @return VideoType
			 */
			[[nodiscard]]
			virtual VideoType videoType () const noexcept = 0;

			/**
			 * @brief Updates the video device properties.
			 * @param isPerspectiveProjection Declares the perspective type of image.
			 * @param distance The maximal distance of the view.
			 * @param fovOrNear The field of view. Ignored if the projection is orthographic and can be used as near value override.
			 * @return void
			 */
			virtual void updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept = 0;

		protected:

			/**
			 * @brief Constructs a virtual video device.
			 * @param name The name of the device to find it withing the master control console.
			 * @param allowedConnexionType The type of connexion this virtual device allows. Default Both.
			 */
			explicit AbstractVirtualVideoDevice (const std::string & name, ConnexionType allowedConnexionType = ConnexionType::Both) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractVirtualVideoDevice (const AbstractVirtualVideoDevice & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractVirtualVideoDevice (AbstractVirtualVideoDevice && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractVirtualVideoDevice & operator= (const AbstractVirtualVideoDevice & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractVirtualVideoDevice & operator= (AbstractVirtualVideoDevice && copy) noexcept = default;

			/**
			 * @brief Event fired when a virtual video device is connected to input.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param sourceDevice A pointer to the virtual video device.
			 */
			virtual void onSourceConnected (AbstractVirtualVideoDevice * sourceDevice) noexcept;

			/**
			 * @brief Event fired when a virtual video device is connected to output.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param targetDevice A pointer to the virtual video device.
			 */
			virtual void onTargetConnected (AbstractVirtualVideoDevice * targetDevice) noexcept;

			/**
			 * @brief Event fired when a virtual video device is disconnected to input.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param sourceDevice A pointer to the virtual video device.
			 */
			virtual void onSourceDisconnected (AbstractVirtualVideoDevice * sourceDevice) noexcept;

			/**
			 * @brief Event fired when a virtual video device is disconnected to output.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param targetDevice A pointer to the virtual video device.
			 */
			virtual void onTargetDisconnected (AbstractVirtualVideoDevice * targetDevice) noexcept;

		private:

			/** @copydoc EmEn::AVConsole::AbstractVirtualDevice::onSourceConnected(AbstractVirtualDevice *) */
			void onSourceConnected (AbstractVirtualDevice * sourceDevice) noexcept final;

			/** @copydoc EmEn::AVConsole::AbstractVirtualDevice::onTargetConnected(AbstractVirtualDevice *) */
			void onTargetConnected (AbstractVirtualDevice * targetDevice) noexcept final;

			/** @copydoc EmEn::AVConsole::AbstractVirtualDevice::onSourceDisconnected(AbstractVirtualDevice *) */
			void onSourceDisconnected (AbstractVirtualDevice * sourceDevice) noexcept final;

			/** @copydoc EmEn::AVConsole::AbstractVirtualDevice::onTargetDisconnected(AbstractVirtualDevice *) */
			void onTargetDisconnected (AbstractVirtualDevice * targetDevice) noexcept final;
	};
}
