/*
 * src/MasterControl/Console.hpp
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
#include <any>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

/* Local inclusions for inheritances. */
#include "Libraries/NameableTrait.hpp"
#include "ConsoleControllable.hpp"
#include "Libraries/ObserverTrait.hpp"
#include "Libraries/ObservableTrait.hpp"

/* Local inclusions for usages. */
#include "AbstractVirtualAudioDevice.hpp"
#include "AbstractVirtualVideoDevice.hpp"
#include "Graphics/FramebufferPrecisions.hpp"
#include "Graphics/RenderTarget/ShadowMap/Abstract.hpp"
#include "Graphics/RenderTarget/ShadowMap/Cubemap.hpp"
#include "Graphics/RenderTarget/ShadowMap/Texture2D.hpp"
#include "Graphics/RenderTarget/Texture/Abstract.hpp"
#include "Graphics/RenderTarget/Texture/Cubemap.hpp"
#include "Graphics/RenderTarget/Texture/Texture2D.hpp"
#include "Graphics/RenderTarget/View/Abstract.hpp"
#include "Graphics/RenderTarget/View/Cubemap.hpp"
#include "Graphics/RenderTarget/View/Texture2D.hpp"
#include "Audio/Manager.hpp"
#include "Types.hpp"

namespace Emeraude
{
	class Settings;
}

namespace Emeraude::MasterControl
{
	/**
	 * @brief The master control links every virtual audio/video input/output from the scene.
	 * @extends Libraries::NameableTrait The master control can have a name according to the scene.
	 * @extends Emeraude::ConsoleControllable The master control is usable from the console.
	 * @extends Libraries::ObserverTrait The master control wants to get notifications from devices.
	 * @extends Libraries::ObserverTrait The master control dispatch device configuration changes.
	 */
	class Console final : public Libraries::NameableTrait, public ConsoleControllable, public Libraries::ObserverTrait, public Libraries::ObservableTrait
	{
		public:

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				VideoDeviceAdded,
				VideoDeviceRemoved,
				AudioDeviceAdded,
				AudioDeviceRemoved,
				RenderToShadowMapAdded,
				RenderToTextureAdded,
				RenderToViewAdded,
				/* Enumeration boundary. */
				MaxEnum
			};


			/** @brief Observable class identification. */
			static constexpr auto ClassId{"MasterControlConsole"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/** @brief The reserved name for the default view device. */
			static const std::string DefaultViewName;
			static const std::string DefaultSpeakerName;

			/**
			 * @brief Constructs the master control console.
			 * @param name A reference to a string.
			 */
			explicit Console (const std::string & name) noexcept;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

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
			std::shared_ptr< AbstractVirtualVideoDevice >
			getPrimaryVideoDevice () const noexcept
			{
				if ( m_primaryOutputVideoDeviceId.empty() )
				{
					return nullptr;
				}

				return this->getVideoDevice(m_primaryOutputVideoDeviceId);
			}

			/**
			 * @brief Returns the primary audio device.
			 * @return std::shared_ptr< AbstractVirtualAudioDevice >
			 */
			[[nodiscard]]
			std::shared_ptr< AbstractVirtualAudioDevice >
			getPrimaryAudioDevice () const noexcept
			{
				if ( m_primaryOutputAudioDeviceId.empty() )
				{
					return nullptr;
				}

				return this->getAudioDevice(m_primaryOutputAudioDeviceId);
			}

			/**
			 * @brief Returns a printable device List.
			 * @param deviceType
			 * @param directionType
			 * @return std::string
			 */
			[[nodiscard]]
			std::string getDeviceList (DeviceType deviceType = DeviceType::Both, ConnexionType directionType = ConnexionType::Both) const noexcept;

			/**
			 * @brief Returns available render to shadow maps from the scene.
			 * @return const std::set< std::shared_ptr< Graphics::RenderTarget::ShadowMapSampler::Abstract > > &
			 */
			[[nodiscard]]
			const std::set< std::shared_ptr< Graphics::RenderTarget::ShadowMap::Abstract > > &
			renderToShadowMaps () const noexcept
			{
				return m_renderToShadowMaps;
			}

			/**
			 * @brief Returns available render to texture2Ds from the scene.
			 * @return const std::set< std::shared_ptr< Graphics::RenderTarget::Texture::Abstract > > &
			 */
			[[nodiscard]]
			const std::set< std::shared_ptr< Graphics::RenderTarget::Texture::Abstract > > &
			renderToTextures () const noexcept
			{
				return m_renderToTextures;
			}

			/**
			 * @brief Returns available render to views from the scene.
			 * @return const std::set< std::shared_ptr< Graphics::RenderTarget::View::Abstract > > &
			 */
			[[nodiscard]]
			const std::set< std::shared_ptr< Graphics::RenderTarget::View::Abstract > > &
			renderToViews () const noexcept
			{
				return m_renderToViews;
			}

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
			 * @brief Creates a render to shadow map (Texture2D) device.
			 * @param renderer A reference to the graphics renderer.
			 * @param name A reference to a string to name the virtual video device.
			 * @param resolution The resolution of the shadow map.
			 * @return std::shared_ptr< Graphics::RenderTarget::ShadowMapSampler::Texture2D >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::ShadowMap::Texture2D > createRenderToShadowMap (Graphics::Renderer & renderer, const std::string & name, uint32_t resolution) noexcept;

			/**
			 * @brief Creates a render to cubic shadow map (Cubemap) device.
			 * @param renderer A reference to the graphics renderer.
			 * @param name A reference to a string to name the virtual video device.
			 * @param resolution The resolution of the shadow map.
			 * @return std::shared_ptr< Graphics::RenderTarget::ShadowMapSampler::Cubemap >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::ShadowMap::Cubemap > createRenderToCubicShadowMap (Graphics::Renderer & renderer, const std::string & name, uint32_t resolution) noexcept;

			/**
			 * @brief Creates a render to texture 2D device.
			 * @param renderer A reference to the graphics renderer.
			 * @param name A reference to a string to name the virtual video device.
			 * @param width The width of the surface.
			 * @param height The height of the surface.
			 * @param colorCount The number of color channel desired for the texture2Ds. Default 4.
			 * @return std::shared_ptr< Graphics::RenderTarget::Texture::Texture2D >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::Texture::Texture2D > createRenderToTexture2D (Graphics::Renderer & renderer, const std::string & name, uint32_t width, uint32_t height, uint32_t colorCount = 4) noexcept;

			/**
			 * @brief Creates a render to cubemap device.
			 * @param renderer A reference to the graphics renderer.
			 * @param name A reference to a string to name the virtual video device.
			 * @param size The size of the cubemap.
			 * @param colorCount The number of color channel desired for the texture2Ds. Default 4.
			 * @return std::shared_ptr< Graphics::RenderTarget::Texture::Texture::Cubemap >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::Texture::Cubemap > createRenderToCubemap (Graphics::Renderer & renderer, const std::string & name, uint32_t size, uint32_t colorCount = 4) noexcept;

			/**
			 * @brief Creates a render to view (Texture 2D) device.
			 * @param renderer A reference to the graphics renderer.
			 * @param name A reference to a string to name the virtual video device.
			 * @param width The width of the surface.
			 * @param height The height of the surface.
			 * @param precisions A reference to a framebuffer precisions structure.
			 * @param primaryDevice Set the device as primary output. Default false.
			 * @return std::shared_ptr< Graphics::RenderTarget::View::Texture2D >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::View::Texture2D > createRenderToView (Graphics::Renderer & renderer, const std::string & name, uint32_t width, uint32_t height, const Graphics::FramebufferPrecisions & precisions = {}, bool primaryDevice = false) noexcept;

			/**
			 * @brief Creates a render to cubic view (Cubemap) device.
			 * @param renderer A reference to the graphics renderer.
			 * @param name A reference to a string to name the virtual video device.
			 * @param size The size of the cubemap.
			 * @param precisions A reference to a framebuffer precisions structure.
			 * @param primaryDevice Set the device as primary output. Default false.
			 * @return std::shared_ptr< Graphics::RenderTarget::View::Cubemap >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderTarget::View::Cubemap > createRenderToCubicView (Graphics::Renderer & renderer, const std::string & name, uint32_t size, const Graphics::FramebufferPrecisions & precisions = {}, bool primaryDevice = false) noexcept;

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
			 * @param graphicsRenderer A reference to the graphics renderer.
			 * @param settings A reference to the core settings.
			 * @return bool
			 */
			bool autoConnectPrimaryVideoDevices (Graphics::Renderer & graphicsRenderer, Settings & settings) noexcept;

			/**
			 * @brief Auto-connects the primary audio devices.
			 * @param audioManager A reference to the audio manager.
			 * @param settings A reference to the core settings.
			 * @return bool
			 */
			bool autoConnectPrimaryAudioDevices (Audio::Manager & audioManager, Settings & settings) noexcept;

			/**
			 * @brief Returns a printable state of connexions.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string getConnexionStates () const noexcept;

			/**
			 * @brief Creates the default view.
			 * @param graphicsRenderer A reference to the graphics renderer.
			 * @param settings A reference to the core settings.
			 * @return bool
			 */
			[[nodiscard]]
			bool createDefaultView (Graphics::Renderer & graphicsRenderer, Settings & settings) noexcept;

			/**
			 * @brief Creates the default speaker.
			 * @param audioManager A reference to the audio manager.
			 * @param settings A reference to the core settings.
			 * @return bool
			 */
			[[nodiscard]]
			bool createDefaultSpeaker (Audio::Manager & audioManager, Settings & settings) noexcept;

			/**
			 * @brief Clears all device from the console.
			 */
			void clear () noexcept;

		private:

			/** @copydoc Libraries:ObserverTrait::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::ObservableTrait * observable, int notificationCode, const std::any & data) noexcept override;

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

			std::unordered_map< std::string, std::shared_ptr< AbstractVirtualVideoDevice > > m_virtualVideoDevices;
			std::unordered_map< std::string, std::shared_ptr< AbstractVirtualAudioDevice > > m_virtualAudioDevices;
			std::set< std::shared_ptr< Graphics::RenderTarget::ShadowMap::Abstract > > m_renderToShadowMaps;
			std::set< std::shared_ptr< Graphics::RenderTarget::Texture::Abstract > > m_renderToTextures;
			std::set< std::shared_ptr< Graphics::RenderTarget::View::Abstract > > m_renderToViews;
			std::string m_primaryInputVideoDeviceId; /* A camera */
			std::string m_primaryOutputVideoDeviceId; /* A view */
			std::string m_primaryInputAudioDeviceId; /* A microphone */
			std::string m_primaryOutputAudioDeviceId; /* A speaker */
	};
}
