/*
 * Emeraude/MasterControl/Console.cpp
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

#include "Console.hpp"

/* Local inclusions. */
#include "Graphics/RenderTarget/View/Texture2D.hpp"
#include "Settings.hpp"
#include "Window.hpp"
#include "Tracer.hpp"

namespace Emeraude::MasterControl
{
	using namespace Libraries;
	using namespace Graphics;

	const size_t Console::ClassUID{Observable::getClassUID()};
	const std::string Console::DefaultViewName{"DefaultView"};

	Console::Console (const std::string & name) noexcept
		: NamedItem(name + ClassId), ConsoleControllable(ClassId)
	{
		/* Console commands bindings. */
		this->bindCommand("listDevices", std::bind(&Console::CFListDevices, this, std::placeholders::_1), "Get a list of input/output audio/video devices.");
		this->bindCommand("registerRoute", std::bind(&Console::CFRegisterRoute, this, std::placeholders::_1), "Register a route from input device to output device.");
	}

	bool
	Console::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	const std::set< std::shared_ptr< RenderTarget::View::Abstract > > &
	Console::renderToViews () const noexcept
	{
		return m_renderToViews;
	}

	const std::set< std::shared_ptr< RenderTarget::Texture::Abstract > > &
	Console::renderToTextures () const noexcept
	{
		return m_renderToTextures;
	}

	const std::set< std::shared_ptr< RenderTarget::ShadowMap::Abstract > > &
	Console::renderToShadowMaps () const noexcept
	{
		return m_renderToShadowMaps;
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

			/* NOTE: Save the video device to a specific container for rendering update. */
			switch ( device->videoType() )
			{
				case VideoType::View :
				{
					auto renderToView = std::static_pointer_cast< Graphics::RenderTarget::View::Abstract >(device);

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
					auto renderToTexture = std::static_pointer_cast< Graphics::RenderTarget::Texture::Abstract >(device);

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
					auto renderToShadowMap = std::static_pointer_cast< Graphics::RenderTarget::ShadowMap::Abstract >(device);

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
			auto abstractView = std::dynamic_pointer_cast< RenderTarget::View::Abstract >(device);

			if ( abstractView != nullptr )
			{
				m_renderToViews.erase(abstractView);
			}
			else
			{
				auto abstractTextures = std::dynamic_pointer_cast< RenderTarget::Texture::Abstract >(device);

				if ( abstractTextures != nullptr )
				{
					m_renderToTextures.erase(abstractTextures);
				}
				else
				{
					auto abstractShadowMaps = std::dynamic_pointer_cast< RenderTarget::ShadowMap::Abstract >(device);

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
	Console::createRenderToView (const std::string & name, uint32_t width, uint32_t height, const FramebufferPrecisions & precisions, bool primaryDevice) noexcept
	{
		/* Checks name availability. */
		auto deviceIt = m_virtualVideoDevices.find(name);

		if ( deviceIt != m_virtualVideoDevices.cend() )
		{
			TraceError{ClassId} << "A virtual device named '" << name << "' already exists ! Render to view creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::View::Texture2D >(name, width, height, precisions);

		if ( !renderTarget->createOnHardware() )
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
	Console::createRenderToCubicView (const std::string & name, uint32_t size, const FramebufferPrecisions & precisions, bool primaryDevice) noexcept
	{
		/* Checks name availability. */
		auto deviceIt = m_virtualVideoDevices.find(name);

		if ( deviceIt != m_virtualVideoDevices.cend() )
		{
			TraceError{ClassId} << "A virtual device named '" << name << "' already exists ! Render to cubic view creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::View::Cubemap >(name, size, precisions);

		if ( !renderTarget->createOnHardware() )
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
	Console::createRenderToTexture2D (const std::string & name, uint32_t width, uint32_t height, uint32_t colorCount) noexcept
	{
		/* Checks name availability. */
		auto deviceIt = m_virtualVideoDevices.find(name);

		if ( deviceIt != m_virtualVideoDevices.cend() )
		{
			TraceError{ClassId} <<
				"A virtual video device named '" << name << "' already exists ! "
				"Render to texture 2D creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::Texture::Texture2D >(name, width, height, colorCount);

		if ( !renderTarget->createOnHardware() )
		{
			TraceError{ClassId} << "Unable to create the render to texture 2D '" << name << "' !";

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
	Console::createRenderToCubemap (const std::string & name, uint32_t size, uint32_t colorCount) noexcept
	{
		/* Checks name availability. */
		auto deviceIt = m_virtualVideoDevices.find(name);

		if ( deviceIt != m_virtualVideoDevices.cend() )
		{
			TraceError{ClassId} <<
				"A virtual video device named '" << name << "' already exists ! "
				"Render to cubemap creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::Texture::Cubemap >(name, size, colorCount);

		if ( !renderTarget->createOnHardware() )
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
	Console::createRenderToShadowMap (const std::string & name, uint32_t resolution) noexcept
	{
		/* Checks name availability. */
		auto deviceIt = m_virtualVideoDevices.find(name);

		if ( deviceIt != m_virtualVideoDevices.cend() )
		{
			TraceError{ClassId} <<
				"A virtual video device named '" << name << "' already exists ! "
				"Render to shadow map creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::ShadowMap::Texture2D >(name, resolution);

		if ( !renderTarget->createOnHardware() )
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
	Console::createRenderToCubicShadowMap (const std::string & name, uint32_t resolution) noexcept
	{
		/* Checks name availability. */
		auto deviceIt = m_virtualVideoDevices.find(name);

		if ( deviceIt != m_virtualVideoDevices.cend() )
		{
			TraceError{ClassId} <<
				"A virtual video device named '" << name << "' already exists ! "
				"Render to cubic shadow map creation canceled ...";

			return {};
		}

		/* Create the render target. */
		auto renderTarget = std::make_shared< RenderTarget::ShadowMap::Cubemap >(name, resolution);

		if ( !renderTarget->createOnHardware() )
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
		auto deviceIt = m_virtualVideoDevices.find(deviceId);

		if ( deviceIt == m_virtualVideoDevices.end() )
		{ 
			return nullptr; 
		}

		return deviceIt->second;
	}

	std::shared_ptr< AbstractVirtualAudioDevice >
	Console::getAudioDevice (const std::string & deviceId) const noexcept
	{
		auto deviceIt = m_virtualAudioDevices.find(deviceId);

		if ( deviceIt == m_virtualAudioDevices.end() )
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

		for ( const auto & device : m_virtualVideoDevices )
		{
			if ( device.second->allowedConnexionType() == ConnexionType::Output )
			{
				list.emplace_back(device.second);
			}
		}
		
		return list;
	}

	std::vector< std::shared_ptr< AbstractVirtualAudioDevice > >
	Console::getAudioDeviceSources () const noexcept
	{
		std::vector< std::shared_ptr< AbstractVirtualAudioDevice > > list{};
		list.reserve(m_virtualAudioDevices.size());
		
		for ( const auto & device : m_virtualAudioDevices )
		{
			if ( device.second->allowedConnexionType() == ConnexionType::Output )
			{
				list.emplace_back(device.second);
			}
		}
		
		return list;
	}

	std::shared_ptr< AbstractVirtualVideoDevice >
	Console::getPrimaryVideoDevice () const noexcept
	{
		if ( m_primaryOutputVideoDeviceId.empty() )
		{ 
			return nullptr; 
		}

		return this->getVideoDevice(m_primaryOutputVideoDeviceId);
	}

	std::shared_ptr< AbstractVirtualAudioDevice >
	Console::getPrimaryAudioDevice () const noexcept
	{
		if ( m_primaryOutputAudioDeviceId.empty() )
		{
			return nullptr;
		}

		return this->getAudioDevice(m_primaryOutputAudioDeviceId);
	}

	bool
	Console::connectVideoDevices (const std::string & sourceDeviceId, const std::string & targetDeviceId) const noexcept
	{
		auto sourceDevice = this->getVideoDevice(sourceDeviceId);

		if ( sourceDevice == nullptr )
		{
			TraceError{ClassId} << "Unable to find virtual video device '" << sourceDeviceId << "' as source device to connect !";

			return false;
		}

		auto targetDevice = this->getVideoDevice(targetDeviceId);

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
		auto sourceDevice = this->getAudioDevice(sourceDeviceId);

		if ( sourceDevice == nullptr )
		{
			TraceError{ClassId} << "Unable to find virtual audio device '" << sourceDeviceId << "' as source device to connect !";

			return false;
		}

		auto targetDevice = this->getAudioDevice(targetDeviceId);

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
	Console::createDefaultView (Settings & coreSettings) noexcept
	{
		auto deviceIt = m_virtualVideoDevices.find(DefaultViewName);

		if ( deviceIt != m_virtualVideoDevices.cend() )
		{ 
			return true; 
		}

		/* Read the default configuration. */
		const auto width = RenderTarget::View::Texture2D::getWidth();
		const auto height = RenderTarget::View::Texture2D::getHeight();

		const FramebufferPrecisions precisions{
			coreSettings.getAs< uint32_t >(FramebufferPrecisions::RedBitsKey, FramebufferPrecisions::DefaultRedBits),
			coreSettings.getAs< uint32_t >(FramebufferPrecisions::GreenBitsKey, FramebufferPrecisions::DefaultGreenBits),
			coreSettings.getAs< uint32_t >(FramebufferPrecisions::BlueBitsKey, FramebufferPrecisions::DefaultBlueBits),
			coreSettings.getAs< uint32_t >(FramebufferPrecisions::AlphaBitsKey, FramebufferPrecisions::DefaultAlphaBits),
			coreSettings.getAs< uint32_t >(FramebufferPrecisions::DepthBitsKey, FramebufferPrecisions::DefaultDepthBits),
			coreSettings.getAs< uint32_t >(FramebufferPrecisions::StencilBitsKey, FramebufferPrecisions::DefaultStencilBits),
			coreSettings.getAs< uint32_t >(FramebufferPrecisions::SamplesKey, FramebufferPrecisions::DefaultSamples)
		};

		return this->createRenderToView(DefaultViewName, width, height, precisions, true) != nullptr;
	}

	bool
	Console::autoConnectPrimaryVideoDevices (Settings & coreSettings) noexcept
	{
		if ( !this->autoSelectPrimaryInputVideoDevice() )
		{
			Tracer::error(ClassId, "There is no input primary video device declared !");

			return false;
		}

		if ( m_primaryOutputVideoDeviceId.empty() )
		{
			Tracer::info(ClassId, "There is no output primary video device declared ! Creating a view ...");

			if ( !this->createDefaultView(coreSettings) )
			{
				Tracer::error(ClassId, "Unable to create the default view !");

				return false;
			}
		}

		return this->connectVideoDevices(m_primaryInputVideoDeviceId, m_primaryOutputVideoDeviceId);
	}

	bool
	Console::autoConnectPrimaryAudioDevices (Settings & coreSettings) noexcept
	{
		if ( !this->autoSelectPrimaryInputAudioDevice() )
		{
			Tracer::error(ClassId, "There is no input primary audio device declared !");

			return false;
		}

		/* FIXME: Create a default output ! */
		if ( m_primaryOutputAudioDeviceId.empty() )
		{
			Tracer::error(ClassId, "There is no output primary audio device declared !");

			return false;
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

				for ( const auto & device : m_virtualVideoDevices )
				{
					auto deviceConnexionType = device.second->allowedConnexionType();

					if ( deviceConnexionType == ConnexionType::Input || deviceConnexionType == ConnexionType::Both )
					{
						string << " - '" << device.first << "'" "\n";

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

				for ( const auto & device : m_virtualVideoDevices )
				{
					auto deviceConnexionType = device.second->allowedConnexionType();

					if ( deviceConnexionType == ConnexionType::Output || deviceConnexionType == ConnexionType::Both )
					{
						string << " - '" << device.first << "'" "\n";

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

				for ( const auto & device : m_virtualAudioDevices )
				{
					auto deviceConnexionType = device.second->allowedConnexionType();

					if ( deviceConnexionType == ConnexionType::Input || deviceConnexionType == ConnexionType::Both )
					{
						string << " - '" << device.first << "'" "\n";

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

				for ( const auto & device : m_virtualAudioDevices )
				{
					auto deviceConnexionType = device.second->allowedConnexionType();

					if ( deviceConnexionType == ConnexionType::Output || deviceConnexionType == ConnexionType::Both )
					{
						string << " - '" << device.first << "'" "\n";

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

	int
	Console::CFListDevices (const std::vector< std::string > & parameters) noexcept
	{
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
	}

	int
	Console::CFRegisterRoute (const std::vector< std::string > & parameters) noexcept
	{
		if ( parameters.size() != 3 )
		{
			this->writeToConsole("This method need 3 parameters.", Severity::Error);

			return 1;
		}

		if ( parameters[0] == "video" )
		{
			this->connectVideoDevices(parameters[1], parameters[2]);
		}
		else if ( parameters[0] == "audio" )
		{
			this->connectAudioDevices(parameters[1], parameters[2]);
		}
		else
		{
			this->writeToConsole("First parameter must be 'video' or 'audio'.", Severity::Error);

			return 2;
		}

		return 0;
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

		for ( auto & item : m_virtualAudioDevices )
		{
			item.second->disconnectFromAll();
		}

		m_virtualAudioDevices.clear();

		for ( auto & item : m_virtualVideoDevices )
		{
			item.second->disconnectFromAll();
		}

		m_virtualVideoDevices.clear();
	}

	bool
	Console::onNotification (const Observable * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled event from observable @" << observable << " (code:" << notificationCode << ") ! "
			"Forgetting it ...";
#endif

		return false;
	}

	bool
	Console::autoSelectPrimaryInputVideoDevice () noexcept
	{
		if ( m_primaryInputVideoDeviceId.empty() )
		{
			auto deviceIt = std::find_if(m_virtualVideoDevices.cbegin(), m_virtualVideoDevices.cend(), [] (const auto & deviceIt) {
				return deviceIt.second->allowedConnexionType() == ConnexionType::Output;
			});

			if ( deviceIt == m_virtualVideoDevices.cend() )
			{
				return false;
			}

			m_primaryInputVideoDeviceId = deviceIt->first;
		}

		return true;
	}

	bool
	Console::autoSelectPrimaryInputAudioDevice () noexcept
	{
		if ( m_primaryInputAudioDeviceId.empty() )
		{
			auto deviceIt = std::find_if(m_virtualAudioDevices.cbegin(), m_virtualAudioDevices.cend(), [] (const auto & deviceIt) {
				return deviceIt.second->allowedConnexionType() == ConnexionType::Output;
			});

			if ( deviceIt == m_virtualAudioDevices.cend() )
			{
				return false;
			}

			m_primaryInputAudioDeviceId = deviceIt->first;
		}

		return true;
	}
}
