/*
 * Emeraude/Overlay/Manager.cpp
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

#include "Manager.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Arguments.hpp"
#include "Settings.hpp"
#include "Graphics/Renderer.hpp"
#include "Input/Manager.hpp"
#include "Window.hpp"
#include "Screen.hpp"
#include "Saphir/ShaderGenerator.hpp"

namespace Emeraude::Overlay
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Graphics;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Vulkan;

	const size_t Manager::ClassUID{Observable::getClassUID()};
	std::array< float, 2 > Manager::s_surfaceSize{0.0F, 0.0F}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

	Manager::Manager (const Arguments & arguments, Settings & coreSettings, const Window & window, const Graphics::Renderer & renderer) noexcept
		: ServiceInterface(ClassId), KeyboardListenerInterface(true, true, false), PointerListenerInterface(true, true, false),
		  m_arguments(arguments), m_coreSettings(coreSettings), m_window(window), m_renderer(renderer)
	{
		/* FIXME : Reestablish the observer. */
		//this->observe(&m_renderer.handle());
	}

	Manager::~Manager ()
	{
		m_activeScreens.clear();

		m_screens.clear();
	}

	bool
	Manager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Manager::usable () const noexcept
	{
		if ( !m_renderer.usable() )
		{
			return false;
		}

		return m_flags[Usable];
	}

	const Arguments &
	Manager::arguments () const noexcept
	{
		return m_arguments;
	}

	const Settings &
	Manager::coreSettings () const noexcept
	{
		return m_coreSettings;
	}

	const Graphics::Renderer &
	Manager::renderer () const noexcept
	{
		return m_renderer;
	}

	bool
	Manager::onInitialize () noexcept
	{
		if ( !m_renderer.usable() )
		{
			Tracer::warning(ClassId, "Overlay manager disabled at startup.");

			return true;
		}

		/* Prepare the rasterization mode for the surface */
		//m_rasterizationMode.setDepthBufferStates(false, false);

		if ( !this->loadProgram() )
		{
			Tracer::error(ClassId, "Unable to create the default program for overlaying render !");

			return false;
		}

		auto * inputManager = Input::Manager::instance();
		inputManager->addKeyboardListener(this);
		inputManager->addPointerListener(this);

		/* Initialize the surface from current handle. */
		if ( !this->updateSurfaceSize() )
		{
			return false;
		}

		m_flags[Usable] = true;

		return true;
	}

	bool
	Manager::updateSurfaceSize () const noexcept
	{
		const auto framebufferSize = m_window.getFramebufferSize();

		if ( framebufferSize[0] == 0 || framebufferSize[1] == 0 )
		{
			return false;
		}

		s_surfaceSize[0] = static_cast< float >(framebufferSize[0]);
		s_surfaceSize[1] = static_cast< float >(framebufferSize[1]);

		return true;
	}

	bool
	Manager::onTerminate () noexcept
	{
		m_activeScreens.clear();

		m_screens.clear();

		return true;
	}

	bool
	Manager::onKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept
	{
		return std::any_of(m_activeScreens.cbegin(), m_activeScreens.cend(), [key, scanCode, modifiers, repeat](const auto & pair) {
			return pair.second->onKeyPress(key, scanCode, modifiers, repeat);
		});
	}

	bool
	Manager::onKeyRelease (int key, int scanCode, int modifiers) noexcept
	{
		return std::any_of(m_activeScreens.cbegin(), m_activeScreens.cend(), [key, scanCode, modifiers](const auto & pair) {
			return pair.second->onKeyRelease(key, scanCode, modifiers);
		});
	}

	bool
	Manager::onCharacterType (unsigned int unicode, int modifiers) noexcept
	{
		return std::any_of(m_activeScreens.cbegin(), m_activeScreens.cend(), [unicode, modifiers](const auto & pair) {
			return pair.second->onCharacterType(unicode, modifiers);
		});
	}

	bool
	Manager::onPointerMove (float x, float y) noexcept
	{
		y = s_surfaceSize[1] - y;

		return std::any_of(m_activeScreens.cbegin(), m_activeScreens.cend(), [x, y](const auto & pair) {
			return pair.second->onPointerMove(x, y);
		});
	}

	bool
	Manager::onButtonPress (float x, float y, int buttonNumber, int mods) noexcept
	{
		y = s_surfaceSize[1] - y;

		return std::any_of(m_activeScreens.cbegin(), m_activeScreens.cend(), [x, y, buttonNumber, mods](const auto & pair) {
			return pair.second->onButtonPress(x, y, buttonNumber, mods);
		});
	}

	bool
	Manager::onButtonRelease (float x, float y, int buttonNumber, int mods) noexcept
	{
		y = s_surfaceSize[1] - y;

		return std::any_of(m_activeScreens.cbegin(), m_activeScreens.cend(), [x, y, buttonNumber, mods](const auto & pair) {
			return pair.second->onButtonRelease(x, y, buttonNumber, mods);
		});
	}

	bool
	Manager::onMouseWheel (float x, float y, float xOffset, float yOffset) noexcept
	{
		y = s_surfaceSize[1] - y;

		return std::any_of(m_activeScreens.cbegin(), m_activeScreens.cend(), [x, y, xOffset, yOffset](const auto & pair) {
			return pair.second->onMouseWheel(x, y, xOffset, yOffset);
		});
	}

	void
	Manager::enable (bool state) noexcept
	{
		if ( !this->usable() )
		{
			Tracer::warning(ClassId, "Overlay is not available !");

			return;
		}

		m_flags[Enabled] = state;
	}

	bool
	Manager::enabled () const noexcept
	{
		if ( !this->usable() )
		{
			return false;
		}

		return m_flags[Enabled];
	}

	std::shared_ptr< Screen >
	Manager::createScreen (const std::string & screenName) noexcept
	{
		auto screenIt = m_screens.find(screenName);

		if ( screenIt != m_screens.cend() )
		{
			Tracer::warning(ClassId, Blob() << "A screen named '" << screenName << "' already exists !");

			return screenIt->second;
		}

		return m_screens[screenName] = std::make_shared< Screen >();
	}

	bool
	Manager::destroyScreen (const std::string & screenName) noexcept
	{
		/* Checks for removing from active screen list before. */
		this->disableScreen(screenName);

		auto screenIt = m_screens.find(screenName);

		if ( screenIt != m_screens.end() )
		{
			m_screens.erase(screenIt);

			return true;
		}

		Tracer::warning(ClassId, Blob() << "Unable to find '" << screenName << "' Screen to erase it !");

		return false;
	}

	bool
	Manager::enableScreen (const std::string & screenName) noexcept
	{
		auto screenIt = m_screens.find(screenName);

		if ( screenIt == m_screens.end() )
		{
			Tracer::warning(ClassId, Blob() << "Unable to find '" << screenName << "' Screen to enable it !");

			return false;
		}

		return m_activeScreens.emplace(screenName, screenIt->second).second;
	}

	bool
	Manager::toggleScreen (const std::string & screenName) noexcept
	{
		auto screenIt = m_activeScreens.find(screenName);

		/* If enabled, disable it ! */
		if ( screenIt != m_activeScreens.end() )
		{
			m_activeScreens.erase(screenIt);

			return false;
		}

		return this->enableScreen(screenName);
	}

	bool
	Manager::disableScreen (const std::string & screenName) noexcept
	{
		return ( m_activeScreens.erase(screenName) > 0 );
	}

	void
	Manager::disableAllScreens () noexcept
	{
		m_activeScreens.clear();
	}

	bool
	Manager::bringScreenOnTop (const std::string & screenName, bool disableOthersScreens) noexcept
	{
		if ( disableOthersScreens )
		{
			m_activeScreens.clear();
		}

		const auto screenIt = m_screens.find(screenName);

		if ( screenIt != m_screens.cend() )
		{
			return m_activeScreens.emplace(screenName, screenIt->second).second;
		}

		TraceWarning{ClassId} << "Unable to find '" << screenName << "' Screen to bring it on top !";

		return false;
	}

	std::vector< std::string >
	Manager::screensNameList () const noexcept
	{
		std::vector< std::string > screenNames{};
		screenNames.reserve(m_screens.size());

		std::transform(m_screens.cbegin(), m_screens.cend(), std::back_inserter(screenNames), [] (const auto & screenIt) {
			return screenIt.first;
		});

		return screenNames;
	}

	std::vector< std::string >
	Manager::activeScreensNameList () const noexcept
	{
		std::vector< std::string > screenNames{};
		screenNames.reserve(m_screens.size());

		std::transform(m_activeScreens.cbegin(), m_activeScreens.cend(), std::back_inserter(screenNames), [] (const auto & screenIt) {
			return screenIt.first;
		});

		return screenNames;
	}

	std::shared_ptr< const Screen >
	Manager::screen (const std::string & screenName) const noexcept
	{
		auto screenIt = m_screens.find(screenName);

		if ( screenIt == m_screens.cend() )
		{
			return nullptr;
		}

		return screenIt->second;
	}

	std::shared_ptr< Screen >
	Manager::screen (const std::string & screenName) noexcept
	{
		auto screenIt = m_screens.find(screenName);

		if ( screenIt == m_screens.end() )
		{
			return nullptr;
		}

		return screenIt->second;
	}

	bool
	Manager::setPhysicalObjectProperties (const Vector< 2, size_t > & windowSize, float scale) noexcept
	{
		s_surfaceSize[0] = static_cast< float >(windowSize[Math::X]);
		s_surfaceSize[1] = static_cast< float >(windowSize[Math::Y]);

		/* Scale must be positive. */
		if ( scale > 0.0001F )
		{
			m_scale = scale;
		}
		else
		{
			Tracer::warning(ClassId, "Invalid scale parameter, it should be a non-zero positive floating number !");
		}

		return true;
	}

	bool
	Manager::updateVideoMemory () noexcept
	{
		for ( auto & pair : m_activeScreens )
		{
			pair.second->updateVideoMemory();
		}

		return true;
	}

	void
	Manager::render (Renderer & renderer) const noexcept
	{

	}

	float
	Manager::screenWidth () noexcept
	{
		return s_surfaceSize[0];
	}

	float
	Manager::screenHeight () noexcept
	{
		return s_surfaceSize[1];
	}

	bool
	Manager::onNotification (const Observable * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable->is(Window::ClassUID) )
		{
			//if ( !this->setPhysicalObjectProperties(std::any_cast< std::array< size_t, 2 > >(data)) )
			//	Tracer::error(ClassId, "Unable to resize the overlay manager ! UI won't work properly...");

			switch ( notificationCode )
			{
				case Window::Created :
				case Window::Destroyed :
				case Window::Centered :
				case Window::OSNotifiesWindowGetFocus :
				case Window::OSNotifiesWindowLostFocus :
				case Window::OSNotifiesWindowMovedTo :
				case Window::OSNotifiesWindowVisible :
				case Window::OSNotifiesWindowHidden :
				case Window::OSNotifiesWindowSizeMaximized :
				case Window::OSNotifiesWindowSizeMinimized :
				case Window::OSNotifiesWindowResized :
				case Window::OSNotifiesFramebufferResized :
				case Window::OSRequestsToRescaleContentBy :
				case Window::OSRequestsToRefreshContent :
				case Window::OSRequestsToTerminate :
				default :
					TraceDebug{ClassId} << "Event #" << notificationCode << " from the window ignored.";
					break;
			}

			return true;
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled event from observable @" << observable << " (code:" << notificationCode << ") ! "
			"Forgetting it ...";
#endif

		return false;
	}

	bool
	Manager::loadProgram () noexcept
	{
		/* Overlay vertex shader stage. */
		auto vertexShader = std::make_shared< VertexShader >("Overlay");

		{
			ShaderGenerator gen(vertexShader);

			//gen.declare(Declaration::Uniform{Declaration::VariableType::FloatVector3, SurfaceOffset, "vec3(0.0, 0.0, 0.0)"});
			//gen.declare(Declaration::Uniform{Declaration::VariableType::FloatVector2, TextureOffset, "vec2(0.0, 0.0)"});
			gen.declare(Declaration::InputAttribute{VertexAttributeType::Position});
			gen.declare(Declaration::InputAttribute{VertexAttributeType::Primary2DTextureCoordinates});

			gen.declare(Declaration::StageOutput{ShaderVariables::Primary2DTextureCoordinates, GLSL::Smooth});

			Code{gen, Location::Output} <<
				"gl_Position = vec4(" << Attributes::Position << " + " << SurfaceOffset << ", 1.0);" << Line::End <<
				ShaderVariables::Primary2DTextureCoordinates << " = " << Attributes::Primary2DTextureCoordinates << " + " << TextureOffset << ';';

			if ( !gen.writeShader() )
			{
				Tracer::error(ClassId, "Unable to generate the vertex shader source code for the overlay program !");

				return false;
			}
		}

		/* Fragment Shader stage. */
		auto fragmentShader = std::make_shared< FragmentShader >("Overlay");

		{
			ShaderGenerator gen(fragmentShader);

			gen.declare(Declaration::StageInput{ShaderVariables::Primary2DTextureCoordinates, GLSL::Smooth});
			//gen.declare(Declaration::Uniform{Declaration::VariableType::Sampler2DRectangle, Uniforms::PrimaryTexture});

			gen.declareDefaultOutputFragment();

			Code{gen} <<
				"ivec2 sizes = textureSize(" << Uniforms::PrimaryTexture << ");" << Line::Blank <<
				ShaderVariables::OutputFragment << " = texture(" << Uniforms::PrimaryTexture << ", vec2(sizes) * " << ShaderVariables::Primary2DTextureCoordinates << ");";

			if ( !gen.writeShader() )
			{
				Tracer::error(ClassId, "Unable to generate the fragment shader source code for the overlay program !");

				return false;
			}
		}

		return true;
	}
}
