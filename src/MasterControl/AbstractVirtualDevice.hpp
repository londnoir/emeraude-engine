/*
 * Emeraude/MasterControl/AbstractVirtualDevice.hpp
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
#include <cstddef>
#include <memory>
#include <set>
#include <string>

/* Local inclusions for usages. */
#include "Math/Coordinates.hpp"
#include "Types.hpp"

namespace Emeraude::MasterControl
{
	/**
	 * @brief This is the base class of each virtual multimedia device in the 3D world.
	 * @extends std::enable_shared_from_this
	 */
	class AbstractVirtualDevice : public std::enable_shared_from_this< AbstractVirtualDevice >
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractVirtualDevice (const AbstractVirtualDevice & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractVirtualDevice (AbstractVirtualDevice && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractVirtualDevice &
			 */
			AbstractVirtualDevice & operator= (const AbstractVirtualDevice & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractVirtualDevice &
			 */
			AbstractVirtualDevice & operator= (AbstractVirtualDevice && copy) noexcept = default;

			/**
			 * @brief Destructs an abstract device.
			 */
			virtual ~AbstractVirtualDevice () = default;

			/**
			 * @brief Returns the device id.
			 * @return const std::string &
			 */
			[[nodiscard]]
			virtual const std::string & id () const noexcept final;

			/**
			 * @brief Returns the device type.
			 * @return DeviceType
			 */
			[[nodiscard]]
			virtual DeviceType type () const noexcept final;

			/**
			 * @brief Returns the device allowed connexion type.
			 * @return ConnexionType
			 */
			[[nodiscard]]
			virtual ConnexionType allowedConnexionType () const noexcept final;

			/**
			 * @brief Returns whether at least one virtual device is connected as input.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool hasInputConnected () const noexcept final;

			/**
			 * @brief Returns all virtual devices connected to input.
			 * @return const std::set< std::shared_ptr< AbstractVirtualAudioDevice > > &
			 */
			[[nodiscard]]
			virtual const std::set< std::shared_ptr< AbstractVirtualDevice > > & inputs () const noexcept final;

			/**
			 * @brief Returns whether at least one virtual device is connected as output.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool hasOutputConnected () const noexcept final;

			/**
			 * @brief Returns all virtual devices connected to output.
			 * @return const std::set< std::shared_ptr< AbstractVirtualAudioDevice > > &
			 */
			[[nodiscard]]
			virtual const std::set< std::shared_ptr< AbstractVirtualDevice > > & outputs () const noexcept final;

			/**
			 * @brief Returns whether a device is connected.
			 * @param device A reference to a virtual device smart pointer.
			 * @param direction The connexion direction tested. Both means as input or output.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isConnectedWith (const std::shared_ptr< AbstractVirtualDevice > & device, ConnexionType direction) const noexcept final;

			/**
			 * @brief Checks if a device can be connected to output.
			 * @param targetDevice A reference to a virtual device smart pointer.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool canConnect (const std::shared_ptr< AbstractVirtualDevice > & targetDevice) const noexcept final;

			/**
			 * @brief Connects a virtual device to output.
			 * @note this[Output] -> target[Input]
			 * @param targetDevice A reference to a virtual device smart pointer.
			 * @param quietly Do not fire connexion event. Default false.
			 * @return bool
			 */
			virtual bool connect (const std::shared_ptr< AbstractVirtualDevice > & targetDevice, bool quietly = false) noexcept final;

			/**
			 * @brief Interconnects a virtual device between existing output.
			 * @note this[Output] -> target[Input]
			 * @param targetDevice A reference to a virtual device smart pointer.
			 * @param filterDevice This will only target one device by its name. Default All.
			 * @return bool
			 */
			virtual bool interconnect (const std::shared_ptr< AbstractVirtualDevice > & targetDevice, const std::string & filterDevice = {}) noexcept final;

			/**
			 * @brief Disconnects the output of this virtual device from the input of a virtual device.
			 * @param targetDevice A reference to a virtual device smart pointer.
			 * @param quietly Do not fire disconnection event. Default false.
			 * @return bool
			 */
			virtual bool disconnect (const std::shared_ptr< AbstractVirtualDevice > & targetDevice, bool quietly = false) noexcept final;

			/**
			 * @brief Disconnects the device from everything.
			 * @return void
			 */
			virtual void disconnectFromAll () noexcept final;

			/**
			 * @brief Returns a printable state of connexions.
			 * @return std::string
			 */
			[[nodiscard]]
			virtual std::string getConnexionState () const noexcept final;

			/**
			 * @brief Updates the device from object coordinates in world space holding it.
			 * @param worldCoordinates A reference to the coordinates of the device.
			 * @param worldVelocity A reference to the velocity vector of the device.
			 */
			virtual void updateDeviceFromCoordinates (const Libraries::Math::Coordinates< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept = 0;

		protected:

			/**
			 * @brief Constructs an abstract device.
			 * @param name A reference to a string for the device name.
			 * @param type The type of the device.
			 * @param allowedConnexionType The type of connexion this virtual device allows.
			 */
			explicit AbstractVirtualDevice (const std::string & name, DeviceType type, ConnexionType allowedConnexionType) noexcept;

		private:

			static size_t s_deviceCount; // NOLINT

			/**
			 * @brief Builds a device id.
			 * @param name A reference to a string for the device name.
			 * @return std::string
			 */
			[[nodiscard]]
			static std::string buildDeviceId (const std::string & name) noexcept;

			/**
			 * @brief Connects back a connected virtual device.
			 * @param sourceDevice A reference to a virtual device smart pointer.
			 * @param quietly Do not fire connexion event. Default false.
			 * @return bool
			 */
			virtual bool connectBack (const std::shared_ptr< AbstractVirtualDevice > & sourceDevice, bool quietly) noexcept final;

			/**
			 * @brief Disconnects back a connected virtual device.
			 * @param sourceDevice A reference to a virtual device smart pointer.
			 * @param quietly Do not fire disconnection event. Default false.
			 * @return bool
			 */
			virtual bool disconnectBack (const std::shared_ptr< AbstractVirtualDevice > & sourceDevice, bool quietly) noexcept final;

			/**
			 * @brief Event fired when a virtual device is connected to input.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param sourceDevice A pointer to the virtual device.
			 */
			virtual void onSourceConnected (AbstractVirtualDevice * sourceDevice) noexcept = 0;

			/**
			 * @brief Event fired when a virtual device is connected to output.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param sourceDevice A pointer to the virtual device.
			 */
			virtual void onTargetConnected (AbstractVirtualDevice * targetDevice) noexcept = 0;

			/**
			 * @brief Event fired when a virtual device is disconnected to input.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param sourceDevice A pointer to the virtual device.
			 */
			virtual void onSourceDisconnected (AbstractVirtualDevice * sourceDevice) noexcept = 0;

			/**
			 * @brief Event fired when a virtual device is disconnected to output.
			 * @note This method uses a pointer instead of reference to ease the dynamic cast. It will never be null.
			 * @param sourceDevice A pointer to the virtual device.
			 */
			virtual void onTargetDisconnected (AbstractVirtualDevice * targetDevice) noexcept = 0;

			std::string m_id;
			DeviceType m_type;
			ConnexionType m_allowedConnexionType;
			std::set< std::shared_ptr< AbstractVirtualDevice > > m_inputs{};
			std::set< std::shared_ptr< AbstractVirtualDevice > > m_outputs{};
	};
}
