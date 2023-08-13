/*
 * Emeraude/MasterControl/Console.hpp
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
#include <any>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>

/* Local inclusions for inheritances. */
#include "ConsoleControllable.hpp"
#include "Observable.hpp"
#include "Observer.hpp"

/* Local inclusions for usages. */
#include "AbstractVirtualAudioDevice.hpp"
#include "AbstractVirtualVideoDevice.hpp"
#include "Graphics/FramebufferPrecisions.hpp"
#include "Graphics/RenderTarget/ShadowMap/Cubemap.hpp"
#include "Graphics/RenderTarget/ShadowMap/Texture2D.hpp"
#include "Graphics/RenderTarget/Texture/Cubemap.hpp"
#include "Graphics/RenderTarget/Texture/Texture2D.hpp"
#include "Graphics/RenderTarget/View/Cubemap.hpp"
#include "Graphics/RenderTarget/View/Texture2D.hpp"
#include "Types.hpp"

namespace Emeraude
{
	class Settings;
}

namespace Emeraude::MasterControl
{
	/**
	 * @brief The master control links every virtual audio/video input/output from the scene.
	 * @extends Libraries::NamedItem The master control can have a name according to the scene.
	 * @extends Emeraude::ConsoleControllable The master control is usable from the console.
	 * @extends Libraries::Observer The master control wants to get notifications from devices.
	 * @extends Libraries::Observer The master control dispatch device configuration changes.
	 */
	class Console final : public Libraries::NamedItem, public ConsoleControllable, public Libraries::Observer, public Libraries::Observable
	{
		public:

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				VideoDeviceAdded,
				VideoDeviceRemoved,
				AudioDeviceAdded,
				AudioDeviceRemoved,
				RenderToViewAdded,
				RenderToTextureAdded,
				RenderToShadowMapAdded,
				/* Enumeration boundary. */
				MaxEnum
			};


			/** @brief Observable class identification. */
			static constexpr auto ClassId{"MasterControlConsole"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/** @brief The reserved name for the default view device. */
			static const std::string DefaultViewName;

			/**
			 * @brief Constructs the master control console.
			 * @param name A reference to a string.
			 */
			explicit Console (const std::string & name) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/**
			 * @brief Returns a video device by its name.
			 * @param deviceId A reference to a string.
			 * @return std::shared_ptr< AbstractVirtualVideoDevice >
			 */
			[[nodiscard]]
			std::shared_ptr< AbstractVirtualVideoDevice > getVideoDevice (const std::string & deviceId) const noexcept;

			/**
			 * @brief Returns a audio device by its name.
			 * @param deviceId A reference to a string.
			 * @return std::shared_ptr< AbstractVirtualAudioDevice >
			 */
			[[nodiscard]]
			std::shared_ptr< AbstractVirtualAudioDevice > getAudioDevice (const std::string & deviceId) const noexcept;

			/**
			 * @brief Returns a list of video sources.
			 * @return std::vector< std::shared_ptr< AbstractVirtualVideoDevice > >
			 */
			[[nodiscard]]
			std::vector< std::shared_ptr< AbstractVirtualVideoDevice > > getVideoDeviceSources () const noexcept;

			/**
			 * @brief Returns a list of audio sources.
			 * @return std::vector< std::shared_ptr< AbstractVirtualAudioDevice > >
			 */
			[[nodiscard]]
			std::vector< std::shared_ptr< AbstractVirtualAudioDevice > > getAudioDeviceSources () const noexcept;

			/**
			 * @brief Returns the primary video device.
			 * @return std::shared_ptr< AbstractVirtualVideoDevice >
			 */
			[[nodiscard]]
			std::shared_ptr< AbstractVirtualVideoDevice > getPrimaryVideoDevice () const noexcept;

			/**
			 * @brief Returns the primary audio device.
			 * @return std::shared_ptr< AbstractVirtualAudioDevice >
			 */
			[[nodiscard]]
			std::shared_ptr< AbstractVirtualAudioDevice > getPrimaryAudioDevice () const noexcept;

			/**
			 * @brief Returns a printable device List.
			 * @param deviceType
			 * @param directionType
			 * @return std::string
			 */
			[[nodiscard]]
			std::string getDeviceList (DeviceType deviceType = DeviceType::Both, ConnexionType directionType = ConnexionType::Both) const noexcept;

			/**
			 * @brief Returns available render to views from the scene.
			 * @return const std::set< std::shared_ptr< Graphics::RenderTarget::View::Abstract > > &
			 */
			[[nodiscard]]
			const std::set< std::shared_ptr< Graphics::RenderTarget::View::Abstract > > & renderToViews () const noexcept;

			/**
			 * @brief Returns available render to texture2Ds from the scene.
			 * @return const std::set< std::shared_ptr< Graphics::RenderTarget::Texture::Abstract > > &
			 */
			[[nodiscard]]
			const std::set< std::shared_ptr< Graphics::RenderTarget::Texture::Abstract > > & renderToTextures () const noexcept;

			/**
			 * @brief Returns available render to shadow maps from the scene.
			 * @return const std::set< std::shared_ptr< Graphics::RenderTarget::ShadowMap::Abstract > > &
			 */
			[[nodiscard]]
			const std::set< std::shared_ptr< Graphics::RenderTarget::ShadowMap::Abstract > > & renderToShadowMaps () const noexcept;

			/**
			 * @brief Adds a virtual video device.
			 * @param device A reference to a virtual video device smart pointer.
			 * @param primaryDevice Set the device as primary for its connexion type. Default false.
			 * @return bool
			 */
			bool addVideoDevice (const std::shared_ptr< AbstractVirtualVideoDevice > & device, bool primaryDevice = false) noexcept;

			/**
			 * @brief Adds a virtual audio device.
			 * @param device A reference to a virtual audio device smart pointer.
			 * @param primaryDevice Set the device as primary for its connexion type. Default false.
			 * @return bool
			 */
			bool addAudioDevice (const std::shared_ptr< AbstractVirtualAudioDevice > & device, bool primaryDevice = false) noexcept;

			/**
			 * @brief Removes a virtual video device.
			 * @param device A reference to a virtual video device smart pointer.
			 * @return bool
			 */
			bool removeVideoDevice (const std::shared_ptr< AbstractVirtualVideoDevice > & device) noexcept;

			/**
			 * @brief Removes a virtual audio device.
			 * @param device A reference to a virtual audio device smart pointer.
			 * @return bool
			 */
			bool removeAudioDevice (const std::shared_ptr< AbstractVirtualAudioDevice > & device) noexcept;

			/**
			 * @brief Creates a render to view (Texture 2D) device.
			 * @param name A reference to a string to name the virtual video device.
			 * @param width The width of the surface.
			 * @param height The height of the surface.
			 * @param precisions A reference to a framebuffer precisions structure.
			 * @param primaryDevice Set the device as primary output. Default false.
			 * @return std::shared_ptr< Graphics::RenderTarget::View::Texture2D >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::View::Texture2D > createRenderToView (const std::string & name, uint32_t width, uint32_t height, const Graphics::FramebufferPrecisions & precisions = {}, bool primaryDevice = false) noexcept;

			/**
			 * @brief Creates a render to cubic view (Cubemap) device.
			 * @param name A reference to a string to name the virtual video device.
			 * @param size The size of the cubemap.
			 * @param precisions A reference to a framebuffer precisions structure.
			 * @param primaryDevice Set the device as primary output. Default false.
			 * @return std::shared_ptr< Graphics::RenderTarget::View::Cubemap >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::View::Cubemap > createRenderToCubicView (const std::string & name, uint32_t size, const Graphics::FramebufferPrecisions & precisions = {}, bool primaryDevice = false) noexcept;

			/**
			 * @brief Creates a render to texture 2D device.
			 * @param name A reference to a string to name the virtual video device.
			 * @param width The width of the surface.
			 * @param height The height of the surface.
			 * @param colorCount The number of color channel desired for the texture2Ds. Default 4.
			 * @return std::shared_ptr< Graphics::RenderTarget::Texture::Texture2D >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::Texture::Texture2D > createRenderToTexture2D (const std::string & name, uint32_t width, uint32_t height, uint32_t colorCount = 4) noexcept;

			/**
			 * @brief Creates a render to cubemap device.
			 * @param name A reference to a string to name the virtual video device.
			 * @param size The size of the cubemap.
			 * @param colorCount The number of color channel desired for the texture2Ds. Default 4.
			 * @return std::shared_ptr< Graphics::RenderTarget::Texture::Texture::Cubemap >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::Texture::Cubemap > createRenderToCubemap (const std::string & name, uint32_t size, uint32_t colorCount = 4) noexcept;

			/**
			 * @brief Creates a render to shadow map (Texture2D) device.
			 * @param name A reference to a string to name the virtual video device.
			 * @param resolution The resolution of the shadow map.
			 * @return std::shared_ptr< Graphics::RenderTarget::ShadowMap::Texture2D >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::ShadowMap::Texture2D > createRenderToShadowMap (const std::string & name, uint32_t resolution) noexcept;

			/**
			 * @brief Creates a render to cubic shadow map (Cubemap) device.
			 * @param name A reference to a string to name the virtual video device.
			 * @param resolution The resolution of the shadow map.
			 * @return std::shared_ptr< Graphics::RenderTarget::ShadowMap::Cubemap >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::ShadowMap::Cubemap > createRenderToCubicShadowMap (const std::string & name, uint32_t resolution) noexcept;

			/**
			 * @brief Connects two video devices.
			 * @param sourceDeviceId A reference to a string of output virtual video device id.
			 * @param targetDeviceId A reference to a string of input virtual video device id.
			 * @return bool
			 */
			bool connectVideoDevices (const std::string & sourceDeviceId, const std::string & targetDeviceId) const noexcept;

			/**
			 * @brief Connects two audio devices.
			 * @param sourceDeviceId A reference to a string of output virtual audio device id.
			 * @param targetDeviceId A reference to a string of input virtual audio device id.
			 * @return bool
			 */
			bool connectAudioDevices (const std::string & sourceDeviceId, const std::string & targetDeviceId) const noexcept;

			/**
			 * @brief Auto-connects the primary video devices.
			 * @param coreSettings A reference to the core settings.
			 * @return bool
			 */
			bool autoConnectPrimaryVideoDevices (Settings & coreSettings) noexcept;

			/**
			 * @brief Auto-connects the primary audio devices.
			 * @param coreSettings A reference to the core settings.
			 * @return bool
			 */
			bool autoConnectPrimaryAudioDevices (Settings & coreSettings) noexcept;

			/**
			 * @brief Returns a printable state of connexions.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string getConnexionStates () const noexcept;

			/**
			 * @brief Creates the default view.
			 * @param coreSettings A reference to the core settings.
			 * @return bool
			 */
			[[nodiscard]]
			bool createDefaultView (Settings & coreSettings) noexcept;

			/**
			 * @brief Console command to list devices.
			 * @param parameters A reference to a parameter list.
			 * @return int
			 */
			int CFListDevices (const std::vector< std::string > & parameters) noexcept;

			/**
			 * @brief Console command to register a route.
			 * @param parameters A reference to a parameter list.
			 * @return int
			 */
			int CFRegisterRoute (const std::vector< std::string > & parameters) noexcept;

			/**
			 * @brief Clears all device from the console.
			 */
			void clear () noexcept;

		private:

			/** @copydoc Libraries:Observer::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief Selects automatically a primary input video device.
			 * @note If a primary device is already selected, the function won't change anything.
			 * @return bool
			 */
			bool autoSelectPrimaryInputVideoDevice () noexcept;

			/**
			 * @brief Selects automatically a primary input audio device.
			 * @note If a primary device is already selected, the function won't change anything.
			 * @return bool
			 */
			bool autoSelectPrimaryInputAudioDevice () noexcept;

			std::unordered_map< std::string, std::shared_ptr< AbstractVirtualVideoDevice > > m_virtualVideoDevices{};
			std::unordered_map< std::string, std::shared_ptr< AbstractVirtualAudioDevice > > m_virtualAudioDevices{};
			std::set< std::shared_ptr< Graphics::RenderTarget::View::Abstract > > m_renderToViews{};
			std::set< std::shared_ptr< Graphics::RenderTarget::Texture::Abstract > > m_renderToTextures{};
			std::set< std::shared_ptr< Graphics::RenderTarget::ShadowMap::Abstract > > m_renderToShadowMaps{};
			std::string m_primaryInputVideoDeviceId{}; /* A camera */
			std::string m_primaryOutputVideoDeviceId{}; /* A view */
			std::string m_primaryInputAudioDeviceId{}; /* A microphone */
			std::string m_primaryOutputAudioDeviceId{}; /* A speaker */
	};
}
