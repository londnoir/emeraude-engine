/*
 * src/MasterControl/Console.cpp
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

#include "Console.hpp"

/* Local inclusions. */
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ranges>
#include <set>
#include <sstream>
#include <string>
#include <vector>

/* Local inclusions. */
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
#include "Graphics/Renderer.hpp"
#include "Audio/Manager.hpp"
#include "Audio/HardwareOutput.hpp"
#include "Physics/Physics.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"
#include "Types.hpp"
#include "Window.hpp"

namespace Emeraude::MasterControl
{
	using namespace Libraries;
	using namespace Graphics;

	const size_t Console::ClassUID{getClassUID(ClassId)};
	const std::string Console::DefaultViewName{"DefaultView"};
	const std::string Console::DefaultSpeakerName{"DefaultSpeaker"};

	Console::Console (const std::string & name) noexcept
		: NameableTrait(name + ClassId), ConsoleControllable(ClassId)
	{
		/* Console commands bindings. */
		this->bindCommand("listDevices", [this] (const std::vector< std::string > & parameters) {
			DeviceType deviceType{DeviceType::Both};
			ConnexionType directionType{ConnexionType::Both};

			if ( !parameters.empty() )
			{
				{
					const auto & param = parameters[0];

					if ( param == "video" )
					{
						deviceType = DeviceType::Video;
					}
					else if ( param == "audio" )
					{
						deviceType = DeviceType::Audio;
					}
					else if ( param == "both" )
					{
						deviceType = DeviceType::Both;
					}
				}

				if ( parameters.size() > 1 )
				{
					const auto & param = parameters[1];

					if ( param == "input" )
					{
						directionType = ConnexionType::Input;
					}
					else if ( param == "output" )
					{
						directionType = ConnexionType::Output;
					}
					else if ( param == "both" )
					{
						directionType = ConnexionType::Both;
					}
				}
			}

			this->writeToConsole(this->getDeviceList(deviceType, directionType), Severity::Info);

			return 0;
		}, "Get a list of input/output audio/video devices.");

		this->bindCommand("registerRoute", [this] (const std::vector< std::string > & parameters) {
			if ( parameters.size() != 3 )
			{
				this->writeToConsole("This method need 3 parameters.", Severity::Error);

				return 1;
			}

			if ( parameters[0] == "video" )
			{
				if ( !this->connectVideoDevices(parameters[1], parameters[2]) )
				{
					this->writeToConsole("Unable to connect the video device.", Severity::Error);

					return 3;
				}
			}
			else if ( parameters[0] == "audio" )
			{
				if ( !this->connectAudioDevices(parameters[1], parameters[2]) )
				{
					this->writeToConsole("Unable to connect the audio device.", Severity::Error);

					return 3;
				}
			}
			else
			{
				this->writeToConsole("First parameter must be 'video' or 'audio'.", Severity::Error);

				return 2;
			}

			return 0;
		}, "Register a route from input device to output device.");
	}

	bool
	Console::addVideoDevice (const std::shared_ptr< AbstractVirtualVideoDevice > & device, bool primaryDevice) noexcept
	{
		if ( !m_virtualVideoDevices.contains(device->id()) )
		{
			if ( !m_virtualVideoDevices.emplace(device->id(), device).second )
			{
				TraceWarning{ClassId} << "Unable to register the virtual video device '" << device->id() << "' !";

				return false;
			}

			/* NOTE: Save the video device to a specific container for rendering processLogics. */
			switch ( device->videoType() )
			{
				case VideoType::View :
				{
					auto renderToView = std::static_pointer_cast< RenderTarget::View::Abstract >(device);

					if ( m_renderToViews.emplace(renderToView).second )
					{
						this->notify(RenderToViewAdded, renderToView);
					}
					else
					{
						TraceError{ClassId} << "Unable to store the render to view '" << renderToView->id() << "' for rendering !";
					}
				}
					break;

				case VideoType::Texture :
				{
					auto renderToTexture = std::static_pointer_cast< RenderTarget::Texture::Abstract >(device);

					if ( m_renderToTextures.emplace(renderToTexture).second )
					{
						this->notify(RenderToTextureAdded, renderToTexture);
					}
					else
					{
						TraceError{ClassId} << "Unable to store the render to texture '" << device->id() << "' for rendering !";
					}
				}
					break;

				case VideoType::ShadowMap :
				{
					auto renderToShadowMap = std::static_pointer_cast< RenderTarget::ShadowMap::Abstract >(device);

					if ( m_renderToShadowMaps.emplace(renderToShadowMap).second )
					{
						this->notify(RenderToShadowMapAdded, renderToShadowMap);
					}
					else
					{
						TraceError{ClassId} << "Unable to store the render to shadow map '" << device->id() << "' for rendering !";
					}
				}
					break;

				default :
					/* Nothing to do with this type of device. */
					break;
			}

			TraceSuccess{ClassId} << "New virtual video device '" << device->id() << "' available !";

			this->notify(VideoDeviceAdded, device);
		}
		else
		{
			TraceInfo{ClassId} << "Virtual video device '" << device->id() << "' already registered !";
		}

		/* NOTE: Set the device as primary if requested and even if it is already registered. */
		if ( primaryDevice )
		{
			switch ( device->allowedConnexionType() )
			{
				case ConnexionType::Output :
					TraceInfo{ClassId} << "Virtual video device '" << device->id() << "' declared as primary input !";

					m_primaryInputVideoDeviceId = device->id();
					break;

				case ConnexionType::Input :
				case ConnexionType::Both :
					TraceInfo{ClassId} << "Virtual video device '" << device->id() << "' declared as primary output !";

					m_primaryOutputVideoDeviceId = device->id();
					break;
			}
		}

		return true;
	}

	bool
	Console::addAudioDevice (const std::shared_ptr< AbstractVirtualAudioDevice > & device, bool primaryDevice) noexcept
	{
		if ( !m_virtualAudioDevices.contains(device->id()) )
		{
			if ( !m_virtualAudioDevices.emplace(device->id(), device).second )
			{
				TraceWarning{ClassId} << "Unable to register the virtual audio device '" << device->id() << "' !";

				return false;
			}

			TraceSuccess{ClassId} << "New virtual audio device '" << device->id() << "' available !";

			this->notify(AudioDeviceAdded, device);
		}
		else
		{
			TraceInfo{ClassId} << "Virtual audio device '" << device->id() << "' already registered !";
		}

		/* NOTE: Set the device as primary if requested and even if it is already registered. */
		if ( primaryDevice )
		{
			switch ( device->allowedConnexionType() )
			{
				case ConnexionType::Output :
					TraceInfo{ClassId} << "Virtual audio device '" << device->id() << "' declared as primary input !";

					m_primaryInputAudioDeviceId = device->id();
					break;

				case ConnexionType::Input :
				case ConnexionType::Both :
					TraceInfo{ClassId} << "Virtual audio device '" << device->id() << "' declared as primary output !";

					m_primaryOutputAudioDeviceId = device->id();
					break;
			}
		}

		return true;
	}

	bool
	Console::removeVideoDevice (const std::shared_ptr< AbstractVirtualVideoDevice > & device) noexcept
	{
		/* FIXME: This is clearly shit ! */
		{
			const auto abstractView = std::dynamic_pointer_cast< RenderTarget::View::Abstract >(device);

			if ( abstractView != nullptr )
			{
				m_renderToViews.erase(abstractView);
			}
			else
			{
				const auto abstractTextures = std::dynamic_pointer_cast< RenderTarget::Texture::Abstract >(device);

				if ( abstractTextures != nullptr )
				{
					m_renderToTextures.erase(abstractTextures);
				}
				else
				{
					const auto abstractShadowMaps = std::dynamic_pointer_cast< RenderTarget::ShadowMap::Abstract >(device);

					if ( abstractShadowMaps != nullptr )
					{
						m_renderToShadowMaps.erase(abstractShadowMaps);
					}
				}
			}
		}

		if ( m_virtualVideoDevices.erase(device->id()) <= 0 )
		{
			TraceInfo{ClassId} << "There is no virtual video device '" << device->id() << "' registered !";

			return false;
		}

		TraceSuccess{ClassId} << "Virtual video device '" << device->id() << "' removed !";

		this->notify(VideoDeviceRemoved, device);

		return true;
	}

	bool
	Console::removeAudioDevice (const std::shared_ptr< AbstractVirtualAudioDevice > & device) noexcept
	{
		if ( m_virtualAudioDevices.erase(device->id()) <= 0 )
		{
			TraceInfo{ClassId} << "There is no virtual audio device '" << device->id() << "' registered !";

			return false;
		}

		TraceSuccess{ClassId} << "Virtual audio device '" << device->id() << "' removed !";

		this->notify(AudioDeviceRemoved, device);

		return true;
	}

	std::shared_ptr< RenderTarget::View::Texture2D >
	Console::createRenderToView (Renderer & renderer, const std::string & name, uint32_t width, uint32_t height, const FramebufferPrecisions & precisions, bool primaryDevice) noexcept
	{
		if ( m_virtualVideoDevices.contains(name) )
		{
			TraceError{ClassId} << "A virtual device named '" << name << "' already exists ! Render to view creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::View::Texture2D >(name, width, height, precisions);

		if ( !renderTarget->create(renderer) )
		{
			TraceError{ClassId} << "Unable to create the render to view '" << name << "' !";

			return {};
		}

		if ( !this->addVideoDevice(renderTarget, primaryDevice) )
		{
			TraceError{ClassId} << "Unable to add the render to view '" << name << "' as a virtual video device !";

			return {};
		}

		return renderTarget;
	}

	std::shared_ptr< RenderTarget::View::Cubemap >
	Console::createRenderToCubicView (Renderer & renderer, const std::string & name, uint32_t size, const FramebufferPrecisions & precisions, bool primaryDevice) noexcept
	{
		/* Checks name availability. */
		if ( m_virtualVideoDevices.contains(name) )
		{
			TraceError{ClassId} << "A virtual device named '" << name << "' already exists ! Render to cubic view creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::View::Cubemap >(name, size, precisions);

		if ( !renderTarget->create(renderer) )
		{
			TraceError{ClassId} << "Unable to create the render to cubic view '" << name << "' !";

			return {};
		}

		if ( !this->addVideoDevice(renderTarget, primaryDevice) )
		{
			TraceError{ClassId} << "Unable to add the render to cubic view '" << name << "' as a virtual video device !";

			return {};
		}

		return renderTarget;
	}

	std::shared_ptr< RenderTarget::Texture::Texture2D >
	Console::createRenderToTexture2D (Renderer & renderer, const std::string & name, uint32_t width, uint32_t height, uint32_t colorCount) noexcept
	{
		if ( m_virtualVideoDevices.contains(name) )
		{
			TraceError{ClassId} <<
				"A virtual video device named '" << name << "' already exists ! "
				"Render to texture 2D creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::Texture::Texture2D >(name, width, height, colorCount);

		if ( !renderTarget->enableManualLoading() )
		{
			return {};
		}

		auto success = renderTarget->createOnHardware(renderer);

		if ( !renderTarget->setManualLoadSuccess(success) )
		{
			return {};
		}

		if ( !this->addVideoDevice(renderTarget) )
		{
			TraceError{ClassId} << "Unable to add the render to texture 2D '" << name << "' as a virtual video device !";

			return {};
		}

		return renderTarget;
	}

	std::shared_ptr< RenderTarget::Texture::Cubemap >
	Console::createRenderToCubemap (Renderer & renderer, const std::string & name, uint32_t size, uint32_t colorCount) noexcept
	{
		if ( m_virtualVideoDevices.contains(name) )
		{
			TraceError{ClassId} <<
				"A virtual video device named '" << name << "' already exists ! "
				"Render to cubemap creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::Texture::Cubemap >(name, size, colorCount);

		if ( !renderTarget->createOnHardware(renderer) )
		{
			TraceError{ClassId} << "Unable to create the render to cubemap '" << name << "' !";

			return {};
		}

		if ( !this->addVideoDevice(renderTarget) )
		{
			TraceError{ClassId} << "Unable to add the render to cubemap '" << name << "' as a virtual video device !";

			return {};
		}

		return renderTarget;
	}

	std::shared_ptr< RenderTarget::ShadowMap::Texture2D >
	Console::createRenderToShadowMap (Renderer & renderer, const std::string & name, uint32_t resolution) noexcept
	{
		if ( m_virtualVideoDevices.contains(name) )
		{
			TraceError{ClassId} <<
				"A virtual video device named '" << name << "' already exists ! "
				"Render to shadow map creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::ShadowMap::Texture2D >(name, resolution);

		if ( !renderTarget->create(renderer) )
		{
			TraceError{ClassId} << "Unable to create the render to shadow map '" << name << "' !";

			return {};
		}

		if ( !this->addVideoDevice(renderTarget) )
		{
			TraceError{ClassId} << "Unable to add the render to shadow map '" << name << "' as a virtual video device !";

			return {};
		}

		return renderTarget;
	}

	std::shared_ptr< RenderTarget::ShadowMap::Cubemap >
	Console::createRenderToCubicShadowMap (Renderer & renderer, const std::string & name, uint32_t resolution) noexcept
	{
		if ( m_virtualVideoDevices.contains(name) )
		{
			TraceError{ClassId} <<
				"A virtual video device named '" << name << "' already exists ! "
				"Render to cubic shadow map creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::ShadowMap::Cubemap >(name, resolution);

		if ( !renderTarget->create(renderer) )
		{
			TraceError{ClassId} << "Unable to create the render to cubic shadow map '" << name << "' !";

			return {};
		}

		if ( !this->addVideoDevice(renderTarget) )
		{
			TraceError{ClassId} << "Unable to add the render to cubic shadow map '" << name << "' as a virtual video device !";

			return {};
		}

		return renderTarget;
	}

	std::shared_ptr< AbstractVirtualVideoDevice >
	Console::getVideoDevice (const std::string & deviceId) const noexcept
	{
		const auto deviceIt = m_virtualVideoDevices.find(deviceId);

		if ( deviceIt == m_virtualVideoDevices.cend() )
		{
			return nullptr;
		}

		return deviceIt->second;
	}

	std::shared_ptr< AbstractVirtualAudioDevice >
	Console::getAudioDevice (const std::string & deviceId) const noexcept
	{
		const auto deviceIt = m_virtualAudioDevices.find(deviceId);

		if ( deviceIt == m_virtualAudioDevices.cend() )
		{
			return nullptr;
		}

		return deviceIt->second;
	}

	std::vector< std::shared_ptr< AbstractVirtualVideoDevice > >
	Console::getVideoDeviceSources () const noexcept
	{
		std::vector< std::shared_ptr< AbstractVirtualVideoDevice > > list{};
		list.reserve(m_virtualVideoDevices.size());

		for ( const auto & device : std::ranges::views::values(m_virtualVideoDevices) )
		{
			if ( device->allowedConnexionType() == ConnexionType::Output )
			{
				list.emplace_back(device);
			}
		}

		return list;
	}

	std::vector< std::shared_ptr< AbstractVirtualAudioDevice > >
	Console::getAudioDeviceSources () const noexcept
	{
		std::vector< std::shared_ptr< AbstractVirtualAudioDevice > > list{};
		list.reserve(m_virtualAudioDevices.size());

		for ( const auto & device : std::ranges::views::values(m_virtualAudioDevices) )
		{
			if ( device->allowedConnexionType() == ConnexionType::Output )
			{
				list.emplace_back(device);
			}
		}

		return list;
	}

	bool
	Console::connectVideoDevices (const std::string & sourceDeviceId, const std::string & targetDeviceId) const noexcept
	{
		const auto sourceDevice = this->getVideoDevice(sourceDeviceId);

		if ( sourceDevice == nullptr )
		{
			TraceError{ClassId} << "Unable to find virtual video device '" << sourceDeviceId << "' as source device to connect !";

			return false;
		}

		const auto targetDevice = this->getVideoDevice(targetDeviceId);

		if ( targetDevice == nullptr )
		{
			TraceError{ClassId} << "Unable to find virtual video device '" << targetDeviceId << "' as target device to connect !";

			return false;
		}

		if ( sourceDevice->isConnectedWith(targetDevice, ConnexionType::Output) )
		{
			return true;
		}

		return sourceDevice->connect(targetDevice);
	}

	bool
	Console::connectAudioDevices (const std::string & sourceDeviceId, const std::string & targetDeviceId) const noexcept
	{
		const auto sourceDevice = this->getAudioDevice(sourceDeviceId);

		if ( sourceDevice == nullptr )
		{
			TraceError{ClassId} << "Unable to find virtual audio device '" << sourceDeviceId << "' as source device to connect !";

			return false;
		}

		const auto targetDevice = this->getAudioDevice(targetDeviceId);

		if ( targetDevice == nullptr )
		{
			TraceError{ClassId} << "Unable to find virtual audio device '" << targetDeviceId << "' as target device to connect !";

			return false;
		}

		if ( sourceDevice->isConnectedWith(targetDevice, ConnexionType::Output) )
		{
			return true;
		}

		return sourceDevice->connect(targetDevice);
	}

	bool
	Console::createDefaultView (Renderer & graphicsRenderer, Settings & settings) noexcept
	{
		const auto deviceIt = m_virtualVideoDevices.find(DefaultViewName);

		if ( deviceIt != m_virtualVideoDevices.cend() )
		{
			return true;
		}

		/* Read the default configuration. */
		const auto width = RenderTarget::View::Texture2D::getWidth();
		const auto height = RenderTarget::View::Texture2D::getHeight();

		const FramebufferPrecisions precisions{
			settings.get< uint32_t >(VideoFramebufferRedBitsKey, DefaultVideoFramebufferRedBits),
			settings.get< uint32_t >(VideoFramebufferGreenBitsKey, DefaultVideoFramebufferGreenBits),
			settings.get< uint32_t >(VideoFramebufferBlueBitsKey, DefaultVideoFramebufferBlueBits),
			settings.get< uint32_t >(VideoFramebufferAlphaBitsKey, DefaultVideoFramebufferAlphaBits),
			settings.get< uint32_t >(VideoFramebufferDepthBitsKey, DefaultVideoFramebufferDepthBits),
			settings.get< uint32_t >(VideoFramebufferStencilBitsKey, DefaultVideoFramebufferStencilBits),
			settings.get< uint32_t >(VideoFramebufferSamplesKey, DefaultVideoFramebufferSamples)
		};

		return this->createRenderToView(graphicsRenderer, DefaultViewName, width, height, precisions, true) != nullptr;
	}

	bool
	Console::createDefaultSpeaker (Audio::Manager & audioManager, Settings & settings) noexcept
	{
		const auto deviceIt = m_virtualAudioDevices.find(DefaultSpeakerName);

		if ( deviceIt != m_virtualAudioDevices.cend() )
		{
			return true;
		}

		if ( !audioManager.usable() )
		{
			return false;
		}

		return this->addAudioDevice(std::make_shared< Audio::HardwareOutput >(DefaultSpeakerName, audioManager), true);
	}

	bool
	Console::autoConnectPrimaryVideoDevices (Renderer & renderer, Settings & settings) noexcept
	{
		if ( !this->autoSelectPrimaryInputVideoDevice() )
		{
			Tracer::error(ClassId, "There is no input primary video device declared !");

			return false;
		}

		if ( m_primaryOutputVideoDeviceId.empty() )
		{
			Tracer::info(ClassId, "There is no output primary video device declared ! Creating a view ...");

			if ( !this->createDefaultView(renderer, settings) )
			{
				Tracer::error(ClassId, "Unable to create the default view !");

				return false;
			}
		}

		return this->connectVideoDevices(m_primaryInputVideoDeviceId, m_primaryOutputVideoDeviceId);
	}

	bool
	Console::autoConnectPrimaryAudioDevices (Audio::Manager & audioManager, Settings & settings) noexcept
	{
		if ( !this->autoSelectPrimaryInputAudioDevice() )
		{
			Tracer::error(ClassId, "There is no input primary audio device declared !");

			return false;
		}

		if ( m_primaryOutputAudioDeviceId.empty() )
		{
			Tracer::info(ClassId, "There is no output primary audio device declared ! Creating a speaker ...");

			if ( !this->createDefaultSpeaker(audioManager, settings) )
			{
				Tracer::error(ClassId, "Unable to create the default speaker !");

				return false;
			}
		}

		return this->connectAudioDevices(m_primaryInputAudioDeviceId, m_primaryOutputAudioDeviceId);
	}

	std::string
	Console::getConnexionStates () const noexcept
	{
		std::stringstream string{};

		string << "Video routes :" "\n";

		for ( const auto & device : this->getVideoDeviceSources() )
		{
			string << device->getConnexionState();
		}

		string << "Audio routes :" "\n";

		for ( const auto & device : this->getAudioDeviceSources() )
		{
			string << device->getConnexionState();
		}

		return string.str();
	}

	std::string
	Console::getDeviceList (DeviceType deviceType, ConnexionType directionType) const noexcept
	{
		std::stringstream string{};

		if ( deviceType == DeviceType::Video || deviceType == DeviceType::Both )
		{
			if ( directionType == ConnexionType::Input || directionType == ConnexionType::Both )
			{
				size_t count = 0;

				string << "Video input devices :" "\n";

				for ( const auto & [name, device] : m_virtualVideoDevices )
				{
					const auto deviceConnexionType = device->allowedConnexionType();

					if ( deviceConnexionType == ConnexionType::Input || deviceConnexionType == ConnexionType::Both )
					{
						string << " - '" << name << "'" "\n";

						count++;
					}
				}

				if ( count == 0 )
				{
					string << " None !" "\n";
				}
			}

			if ( directionType == ConnexionType::Output || directionType == ConnexionType::Both )
			{
				size_t count = 0;

				string << "Video output devices :" "\n";

				for ( const auto & [name, device] : m_virtualVideoDevices )
				{
					const auto deviceConnexionType = device->allowedConnexionType();

					if ( deviceConnexionType == ConnexionType::Output || deviceConnexionType == ConnexionType::Both )
					{
						string << " - '" << name << "'" "\n";

						count++;
					}
				}

				if ( count == 0 )
				{
					string << " None !" "\n";
				}
			}
		}

		if ( deviceType == DeviceType::Audio || deviceType == DeviceType::Both )
		{
			if ( directionType == ConnexionType::Input || directionType == ConnexionType::Both )
			{
				size_t count = 0;

				string << "Audio input devices :" "\n";

				for ( const auto & [name, device] : m_virtualAudioDevices )
				{
					const auto deviceConnexionType = device->allowedConnexionType();

					if ( deviceConnexionType == ConnexionType::Input || deviceConnexionType == ConnexionType::Both )
					{
						string << " - '" << name << "'" "\n";

						count++;
					}
				}

				if ( count == 0 )
				{
					string << " None !" "\n";
				}
			}

			if ( directionType == ConnexionType::Output || directionType == ConnexionType::Both )
			{
				size_t count = 0;

				string << "Audio output devices :" "\n";

				for ( const auto & [name, device] : m_virtualAudioDevices )
				{
					const auto deviceConnexionType = device->allowedConnexionType();

					if ( deviceConnexionType == ConnexionType::Output || deviceConnexionType == ConnexionType::Both )
					{
						string << " - '" << name << "'" "\n";

						count++;
					}
				}

				if ( count == 0 )
				{
					string << " None !" "\n";
				}
			}
		}

		return string.str();
	}

	void
	Console::clear () noexcept
	{
		/* NOTE: Clearing the primary device names. */
		m_primaryOutputAudioDeviceId.clear();
		m_primaryInputAudioDeviceId.clear();
		m_primaryOutputVideoDeviceId.clear();
		m_primaryInputVideoDeviceId.clear();

		/* NOTE: Removing the specific devices. */
		m_renderToShadowMaps.clear();
		m_renderToTextures.clear();
		m_renderToViews.clear();

		for ( const auto & device : std::ranges::views::values(m_virtualAudioDevices) )
		{
			device->disconnectFromAll();
		}

		m_virtualAudioDevices.clear();

		for ( const auto & device : std::ranges::views::values(m_virtualVideoDevices) )
		{
			device->disconnectFromAll();
		}

		m_virtualVideoDevices.clear();
	}

	bool
	Console::onNotification (const ObservableTrait * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled notification (Code:" << notificationCode << ") from observable '" << whoIs(observable->classUID()) << "' (UID:" << observable->classUID() << ")  ! "
			"Forgetting it ...";
#endif

		return false;
	}

	bool
	Console::autoSelectPrimaryInputVideoDevice () noexcept
	{
		if ( m_primaryInputVideoDeviceId.empty() )
		{
			const auto selectedDeviceIt = std::ranges::find_if(m_virtualVideoDevices, [] (const auto & deviceIt) {
				return deviceIt.second->allowedConnexionType() == ConnexionType::Output;
			});

			if ( selectedDeviceIt == m_virtualVideoDevices.cend() )
			{
				return false;
			}

			m_primaryInputVideoDeviceId = selectedDeviceIt->first;
		}

		return true;
	}

	bool
	Console::autoSelectPrimaryInputAudioDevice () noexcept
	{
		if ( m_primaryInputAudioDeviceId.empty() )
		{
			const auto selectedDeviceIt = std::ranges::find_if(m_virtualAudioDevices, [] (const auto & deviceIt) {
				return deviceIt.second->allowedConnexionType() == ConnexionType::Output;
			});

			if ( selectedDeviceIt == m_virtualAudioDevices.cend() )
			{
				return false;
			}

			m_primaryInputAudioDeviceId = selectedDeviceIt->first;
		}

		return true;
	}
}
