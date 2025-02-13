/*
 * src/Overlay/Manager.cpp
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

#include "Manager.hpp"

/* STL inclusions. */
#include <algorithm>
#include <iterator>
#include <ranges>

/* Third-party inclusions */
#ifdef IMGUI_ENABLED
#include "imgui.h"
#include "backends/imgui_impl_vulkan.h"
#include "backends/imgui_impl_glfw.h"

#include "Vulkan/Instance.hpp"
#include "Vulkan/PhysicalDevice.hpp"
#include "Vulkan/Queue.hpp"
#include "Vulkan/DescriptorPool.hpp"
#include "Vulkan/Framebuffer.hpp"
#endif

/* Local inclusions. */
#include "Graphics/Renderer.hpp"
#include "Libraries/VertexFactory/ShapeGenerator.hpp"
#include "PrimaryServices.hpp"
#include "Resources/Manager.hpp"
#include "Saphir/Generator/OverlayRendering.hpp"
#include "UIScreen.hpp"
#include "Vulkan/SwapChain.hpp"
#include "Vulkan/GraphicsPipeline.hpp"
#include "Vulkan/CommandBuffer.hpp"
#include "Window.hpp"

namespace Emeraude::Overlay
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::VertexFactory;
	using namespace Saphir;
	using namespace Graphics;
	using namespace Vulkan;

	const size_t Manager::ClassUID{getClassUID(ClassId)};

	Manager::Manager (PrimaryServices & primaryServices, Window & window, Renderer & graphicsRenderer) noexcept
		: ServiceInterface(ClassId), KeyboardListenerInterface(false, true), PointerListenerInterface(false, false, true),
		  m_primaryServices(primaryServices),
		  m_window(window),
		  m_graphicsRenderer(graphicsRenderer)
	{
		this->observe(&m_window);
	}

	bool
	Manager::onKeyPress (int32_t key, int32_t scancode, int32_t modifiers, bool repeat) noexcept
	{
		if ( m_screens.empty() )
		{
			return false;
		}

		if ( m_inputExclusiveScreen )
		{
			if ( m_inputExclusiveScreen->empty() || !m_inputExclusiveScreen->isVisible() || !m_inputExclusiveScreen->isListeningKeyboard() )
			{
				return false;
			}

			return m_inputExclusiveScreen->onKeyPress(key, scancode, modifiers, repeat);
		}

		return std::ranges::any_of(m_screens, [key, scancode, modifiers, repeat] (const auto & pair) {
			const auto & screen = pair.second;

			if ( screen->empty() || !screen->isVisible() || !screen->isListeningKeyboard() )
			{
				return false;
			}

			return screen->onKeyPress(key, scancode, modifiers, repeat);
		});
	}

	bool
	Manager::onKeyRelease (int32_t key, int32_t scancode, int32_t modifiers) noexcept
	{
		if ( m_screens.empty() )
		{
			return false;
		}

		if ( m_inputExclusiveScreen )
		{
			if ( m_inputExclusiveScreen->empty() || !m_inputExclusiveScreen->isVisible() || !m_inputExclusiveScreen->isListeningKeyboard() )
			{
				return false;
			}

			return m_inputExclusiveScreen->onKeyRelease(key, scancode, modifiers);
		}

		return std::ranges::any_of(m_screens, [key, scancode, modifiers] (const auto & pair) {
			const auto & screen = pair.second;

			if ( screen->empty() || !screen->isVisible() || !screen->isListeningKeyboard() )
			{
				return false;
			}

			return screen->onKeyRelease(key, scancode, modifiers);
		});
	}

	bool
	Manager::onCharacterType (uint32_t unicode) noexcept
	{
		if ( m_screens.empty() )
		{
			return false;
		}

		if ( m_inputExclusiveScreen )
		{
			if ( m_inputExclusiveScreen->empty() || !m_inputExclusiveScreen->isVisible() || !m_inputExclusiveScreen->isListeningKeyboard() )
			{
				return false;
			}

			return m_inputExclusiveScreen->onCharacterType(unicode);
		}

		return std::ranges::any_of(m_screens, [unicode] (const auto & pair) {
			const auto & screen = pair.second;

			if ( screen->empty() || !screen->isVisible() || !screen->isListeningKeyboard() )
			{
				return false;
			}

			return screen->onCharacterType(unicode);
		});
	}

	bool
	Manager::onPointerMove (float positionX, float positionY) noexcept
	{
		if ( m_screens.empty() )
		{
			return false;
		}

		if ( m_inputExclusiveScreen )
		{
			if ( m_inputExclusiveScreen->empty() || !m_inputExclusiveScreen->isVisible() || !m_inputExclusiveScreen->isListeningPointer() )
			{
				return false;
			}

			return m_inputExclusiveScreen->onPointerMove(m_framebufferProperties, positionX, positionY);
		}

		return std::ranges::any_of(m_screens, [&] (const auto & pair) {
			const auto & screen = pair.second;

			if ( screen->empty() || !screen->isVisible() || !screen->isListeningPointer() )
			{
				return false;
			}

			return screen->onPointerMove(m_framebufferProperties, positionX, positionY);
		});
	}

	bool
	Manager::onButtonPress (float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept
	{
		if ( m_screens.empty() )
		{
			return false;
		}

		if ( m_inputExclusiveScreen )
		{
			if ( m_inputExclusiveScreen->empty() || !m_inputExclusiveScreen->isVisible() || !m_inputExclusiveScreen->isListeningPointer() )
			{
				return false;
			}

			return m_inputExclusiveScreen->onButtonPress(m_framebufferProperties, positionX, positionY, buttonNumber, modifiers);
		}

		return std::ranges::any_of(m_screens, [&] (const auto & pair) {
			const auto & screen = pair.second;

			if ( screen->empty() || !screen->isVisible() || !screen->isListeningPointer() )
			{
				return false;
			}

			return screen->onButtonPress(m_framebufferProperties, positionX, positionY, buttonNumber, modifiers);
		});
	}

	bool
	Manager::onButtonRelease (float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept
	{
		if ( m_screens.empty() )
		{
			return false;
		}

		if ( m_inputExclusiveScreen )
		{
			if ( m_inputExclusiveScreen->empty() || !m_inputExclusiveScreen->isVisible() || !m_inputExclusiveScreen->isListeningPointer() )
			{
				return false;
			}

			return m_inputExclusiveScreen->onButtonRelease(m_framebufferProperties, positionX, positionY, buttonNumber, modifiers);
		}

		return std::ranges::any_of(m_screens, [&] (const auto & pair) {
			const auto & screen = pair.second;

			if ( screen->empty() || !screen->isVisible() || !screen->isListeningPointer() )
			{
				return false;
			}

			return screen->onButtonRelease(m_framebufferProperties, positionX, positionY, buttonNumber, modifiers);
		});
	}

	bool
	Manager::onMouseWheel (float positionX, float positionY, float xOffset, float yOffset) noexcept
	{
		if ( m_screens.empty() )
		{
			return false;
		}

		if ( m_inputExclusiveScreen )
		{
			if ( m_inputExclusiveScreen->empty() || !m_inputExclusiveScreen->isVisible() || !m_inputExclusiveScreen->isListeningPointer() )
			{
				return false;
			}

			return m_inputExclusiveScreen->onMouseWheel(m_framebufferProperties, positionX, positionY, xOffset, yOffset);
		}

		return std::ranges::any_of(m_screens, [&] (const auto & pair) {
			const auto & screen = pair.second;

			if ( screen->empty() || !screen->isVisible() || !screen->isListeningPointer() )
			{
				return false;
			}

			return screen->onMouseWheel(m_framebufferProperties, positionX, positionY, xOffset, yOffset);
		});
	}

	bool
	Manager::generateProgram () noexcept
	{
		Generator::OverlayRendering generator{*this, m_graphicsRenderer.swapChain()};

		if ( m_graphicsRenderer.shaderManager().showGeneratedSourceCode() )
		{
			generator.enableDebugging();
		}

		/* The vertex buffer format, responsible for the specific VBO is handled with the shaders. */
		if ( !generator.generateProgram(m_graphicsRenderer.vertexBufferFormatManager()) )
		{
			return false;
		}

		/* The second step is to check every resource needed by shaders (UBO, Samples, etc.).
		 * NOTE: VBO is an exception done before. */
		if ( !generator.generateProgramLayout(m_graphicsRenderer) )
		{
			return false;
		}

		/* The third step is to check if separate shaders already exists to avoid an extra compilation.
		 * Retrieve the graphics pipeline for the combination of the current renderable instance layer and the render pass. */
		if ( !generator.createGraphicsPipeline(m_graphicsRenderer) )
		{
			return false;
		}

		m_program = generator.program();

		return true;
	}

	void
	Manager::enable (Input::Manager & inputManager, bool state) noexcept
	{
		if ( !this->usable() )
		{
			Tracer::warning(ClassId, "The overlay manager is not available !");

			return;
		}

		if ( state )
		{
			inputManager.addKeyboardListener(this);
			inputManager.addPointerListener(this);
		}
		else
		{
			inputManager.removeKeyboardListener(this);
			inputManager.removePointerListener(this);
		}

		m_flags[Enabled] = state;
	}

	bool
	Manager::updateProgram () const noexcept
	{
		if ( m_program == nullptr )
		{
			return true;
		}

		return m_program->graphicsPipeline()->recreateOnHardware(
			*m_graphicsRenderer.swapChain(),
			m_framebufferProperties.width(),
			m_framebufferProperties.height()
		);
	}

	bool
	Manager::onInitialize () noexcept
	{
		m_surfaceGeometry = std::make_shared< Geometry::IndexedVertexResource >("OverlayQuad", Geometry::EnablePrimaryTextureCoordinates);

		if ( !m_surfaceGeometry->load(ShapeGenerator::generateQuad(2.0F, 2.0F)) )
		{
			TraceError{ClassId} << "Unable to generate a geometry for UI surfaces !";

			m_surfaceGeometry.reset();

			return false;
		}

		if ( !this->generateProgram() )
		{
			TraceError{ClassId} << "Unable to generate a program to render the overlay !";

			return false;
		}

#ifdef IMGUI_ENABLED
		if ( this->initImGUI() )
		{
			TraceSuccess{ClassId} << "ImGUI library initialized !";
		}
		else
		{
			TraceError{ClassId} << "Unable to initialize ImGUI library !";

			return false;
		}
#endif

		m_flags[ServiceInitialized] = true;

		return true;
	}

	bool
	Manager::onTerminate () noexcept
	{
		m_flags[ServiceInitialized] = false;

#ifdef IMGUI_ENABLED
		TraceInfo{ClassId} << "Releasing ImGUI library ...";

		this->releaseImGUI();
#endif

		this->forget(&m_window);

		m_screens.clear();

		m_program.reset();
		m_surfaceGeometry.reset();

		return true;
	}

	std::shared_ptr< UIScreen >
	Manager::createScreen (const std::string & name, bool enableKeyboardListener, bool enablePointerListener) noexcept
	{
#ifdef DEBUG
		if ( !m_framebufferProperties.isValid() )
		{
			TraceError{ClassId} << "The screen size are not initialized !";

			return nullptr;
		}
#endif

		if ( m_screens.contains(name) )
		{
			TraceError{ClassId} << "An UI screen named '" << name << "' already exists !";

			return nullptr;
		}

		auto screen = std::make_shared< UIScreen >(name, m_framebufferProperties, m_graphicsRenderer, enableKeyboardListener, enablePointerListener);

		m_screens[name] = screen;

		this->notify(UIScreenCreated, screen);

		return screen;
	}

#ifdef IMGUI_ENABLED
	std::shared_ptr< ImGUIScreen >
	Manager::createImGUIScreen (const std::string & name, const std::function< void () > & drawFunction) noexcept
	{
		if ( m_ImGUIScreens.contains(name) )
		{
			TraceError{ClassId} << "An ImGUI screen named '" << name << "' already exists !";

			return nullptr;
		}

		auto screen = std::make_shared< ImGUIScreen >(name, drawFunction);

		m_ImGUIScreens[name] = screen;

		return screen;
	}
#endif

	bool
	Manager::destroyScreen (const std::string & name) noexcept
	{
		const auto screenIt = m_screens.find(name);

		if ( screenIt == m_screens.end() )
		{
			TraceError{ClassId} << "Unable to find '" << name << "' UI screen to erase it !";

			return false;
		}

		this->notify(UIScreenDestroying, screenIt->second);

		m_screens.erase(screenIt);

		this->notify(UIScreenDestroyed, name);

		return true;
	}

	bool
	Manager::enableScreen (const std::string & name) noexcept
	{
		const auto screenIt = m_screens.find(name);

		if ( screenIt == m_screens.cend() )
		{
			TraceWarning{ClassId} << "Unable to find the UI screen '" << name << "' to activate it !";

			return false;
		}

		screenIt->second->setVisibility(true);

		return true;
	}

	bool
	Manager::toggleScreen (const std::string & name) noexcept
	{
		const auto screenIt = m_screens.find(name);

		if ( screenIt == m_screens.cend() )
		{
			TraceWarning{ClassId} << "Unable to find the UI screen '" << name << "' to toggle it !";

			return false;
		}

		screenIt->second->setVisibility(!screenIt->second->isVisible());

		return true;
	}

	bool
	Manager::disableScreen (const std::string & name) noexcept
	{
		const auto screenIt = m_screens.find(name);

		if ( screenIt == m_screens.cend() )
		{
			TraceWarning{ClassId} << "Unable to find the UI screen '" << name << "' to disable it !";

			return false;
		}

		screenIt->second->setVisibility(false);

		return true;
	}

	void
	Manager::disableAllScreens () noexcept
	{
		for ( const auto & screen : std::views::values(m_screens) )
		{
			screen->setVisibility(false);
		}
	}

	bool
	Manager::bringScreenOnTop (const std::string & screenName) noexcept
	{
		const auto screenIt = m_screens.find(screenName);

		if ( screenIt == m_screens.cend() )
		{
			TraceWarning{ClassId} << "Unable to find the UI screen '" << screenName << "' to bring it on top !";

			return false;
		}

		// TODO : Re-order the map.

		return true;
	}

	std::vector< std::string >
	Manager::screensNameList () const noexcept
	{
		std::vector< std::string > screenNames{};
		screenNames.reserve(m_screens.size());

		std::ranges::transform(m_screens, std::back_inserter(screenNames), [] (const auto & screenIt) {
			return screenIt.first;
		});

		return screenNames;
	}

	std::vector< std::string >
	Manager::activeScreensNameList () const noexcept
	{
		std::vector< std::string > screenNames{};
		screenNames.reserve(m_screens.size());

		for ( const auto & [screenName, screen] : m_screens )
		{
			if ( screen->isVisible() )
			{
				screenNames.emplace_back(screenName);
			}
		}

		return screenNames;
	}

	std::shared_ptr< const UIScreen >
	Manager::screen (const std::string & screenName) const noexcept
	{
		const auto screenIt = m_screens.find(screenName);

		if ( screenIt == m_screens.cend() )
		{
			TraceWarning{ClassId} << "There is no screen named '" << screenName << "' !";

			return nullptr;
		}

		return screenIt->second;
	}

	std::shared_ptr< UIScreen >
	Manager::screen (const std::string & screenName) noexcept
	{
		const auto screenIt = m_screens.find(screenName);

		if ( screenIt == m_screens.cend() )
		{
			TraceWarning{ClassId} << "There is no screen named '" << screenName << "' !";

			return nullptr;
		}

		return screenIt->second;
	}

	bool
	Manager::updateVideoMemory () noexcept
	{
		if ( !this->isEnabled() || m_screens.empty() )
		{
			return true;
		}

		size_t errors = 0;

		for ( const auto & screen : std::views::values(m_screens) )
		{
			if ( !screen->isVisible() )
			{
				continue;
			}

			if ( !screen->updateVideoMemory(m_graphicsRenderer) )
			{
				errors++;
			}
		}

		return errors == 0;
	}

	void
	Manager::render (const std::shared_ptr< RenderTarget::Abstract > & /*renderTarget*/, const CommandBuffer & commandBuffer) const noexcept
	{
		/* Check if the overlay is enabled or there is something to render. */
		if ( !this->isEnabled() || m_screens.empty() )
		{
			return;
		}

#ifdef DEBUG
		if ( m_surfaceGeometry == nullptr || !m_surfaceGeometry->isCreated() )
		{
			TraceError{ClassId} << "The surface geometry is no ready !";

			return;
		}
#endif

		const auto pipelineLayout = m_program->pipelineLayout();

		/* Bind the graphics pipeline. */
		commandBuffer.bind(*m_program->graphicsPipeline());

		/* Bind the geometry VBO and the optional IBO. */
		commandBuffer.bind(*m_surfaceGeometry, 0);

		for ( const auto & screen : std::views::values(m_screens) )
		{
			if ( screen->empty() || !screen->isVisible() )
			{
				continue;
			}

			for ( const auto & surface : screen->surfaces() | std::views::values )
			{
				if ( surface->descriptorSet() == nullptr || !surface->descriptorSet()->isCreated() )
				{
					TraceWarning{ClassId} << "The surface " << surface->name() << " doesn't have a descriptor set !";

					continue;
				}

				/* [VULKAN-PUSH-CONSTANT:4] Push the transformation matrix. */
				vkCmdPushConstants(
					commandBuffer.handle(),
					pipelineLayout->handle(),
					VK_SHADER_STAGE_VERTEX_BIT,
					0,
					Matrix4Alignment * sizeof(float),
					surface->transformationMatrix().data()
				);

				/* Bind the surface texture. */
				commandBuffer.bind(
					*surface->descriptorSet(),
					*pipelineLayout,
					VK_PIPELINE_BIND_POINT_GRAPHICS,
					0
				);

				/* Draw the surface. */
				commandBuffer.draw(*m_surfaceGeometry);
			}
		}

#ifdef IMGUI_ENABLED
		for ( const auto screen : m_ImGUIScreens | std::views::values )
		{
			if ( !screen->isVisible() )
			{
				continue;
			}

			screen->render(commandBuffer);
		}
#endif
	}

	void
	Manager::updateContent (bool fromResize) noexcept
	{
		const auto forceScaleX = m_primaryServices.settings().get< float >(VideoOverlayForceScaleXKey, DefaultVideoOverlayForceScale);
		const auto forceScaleY = m_primaryServices.settings().get< float >(VideoOverlayForceScaleYKey, DefaultVideoOverlayForceScale);
		const auto & windowState = m_window.state();

		m_framebufferProperties.updateProperties(
			windowState.framebufferWidth,
			windowState.framebufferHeight,
			forceScaleX > 0 ? forceScaleX : windowState.contentXScale,
			forceScaleY > 0 ? forceScaleY : windowState.contentYScale
		);

		if ( this->updateProgram() )
		{
			for ( const auto & [name, screen] : m_screens )
			{
				if ( !screen->updatePhysicalRepresentation(m_graphicsRenderer, m_framebufferProperties) )
				{
					TraceError{ClassId} << "The UI screen '" << name << "' physical representation update failed ! Disabling it ...";

					screen->setVisibility(false);
				}
			}

			if ( fromResize )
			{
				this->notify(OverlayResized, std::array< uint32_t, 2 >{
				   windowState.framebufferWidth,
				   windowState.framebufferHeight
			   });
			}
		}
	}

	bool
	Manager::onNotification (const ObservableTrait * observable, int notificationCode, const std::any & /*data*/) noexcept
	{
		if ( observable->is(Window::ClassUID) )
		{
			switch ( notificationCode )
			{
				case Window::Created :
					this->updateContent(false);

					return true;

				case Window::OSNotifiesFramebufferResized :
					this->updateContent(true);

					return true;

				default :
#ifdef EMERAUDE_DEBUG_OBSERVER_PATTERN
					TraceDebug{ClassId} << "Event #" << notificationCode << " from the window ignored.";
#endif
					break;
			}

			return true;
		}

#ifdef DEBUG
		/* NOTE: Don't know what is it, goodbye ! */
		TraceInfo{ClassId} <<
			"Received an unhandled notification (Code:" << notificationCode << ") from observable '" << whoIs(observable->classUID()) << "' (UID:" << observable->classUID() << ")  ! "
			"Forgetting it ...";
#endif

		return false;
	}

	std::shared_ptr< DescriptorSetLayout >
	Manager::getDescriptorSetLayout (LayoutManager & layoutManager) noexcept
	{
		auto descriptorSetLayout = layoutManager.getDescriptorSetLayout(ClassId);

		if ( descriptorSetLayout == nullptr )
		{
			descriptorSetLayout = layoutManager.prepareNewDescriptorSetLayout(ClassId);
			descriptorSetLayout->setIdentifier(ClassId, ClassId, "DescriptorSetLayout");

			descriptorSetLayout->declareCombinedImageSampler(0, VK_SHADER_STAGE_FRAGMENT_BIT);

			if ( !layoutManager.createDescriptorSetLayout(descriptorSetLayout) )
			{
				return nullptr;
			}
		}

		return descriptorSetLayout;
	}

	bool
	Manager::setInputExclusiveScreen (const std::string & name) noexcept
	{
		const auto screen = this->screen(name);

		if ( screen == nullptr )
		{
			return false;
		}

		m_inputExclusiveScreen = screen;

		return true;
	}

#ifdef IMGUI_ENABLED

	bool
	Manager::initImGUI () noexcept
	{
		if ( !m_graphicsRenderer.usable() )
		{
			TraceError{ClassId} << "No Vulkan graphics layer !";

			return false;
		}

		const auto & filesystem = m_primaryServices.fileSystem();

		m_iniFilepath = filesystem.configDirectory("imgui.ini");
		m_logFilepath = filesystem.cacheDirectory("imgui_log.txt");

		/* NOTE: Initialize ImGUI library. */
		{
			// this initializes the core structures of imgui
			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();

			ImGui::CreateContext();

			ImGuiIO & io = ImGui::GetIO(); (void)io;
			io.IniFilename = m_iniFilepath.c_str();
			io.LogFilename = m_logFilepath.c_str();
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
			//ImGui::StyleColorsClassic();
		}

		/* NOTE: Initialize ImGUI with GLFW. */
		if ( !ImGui_ImplGlfw_InitForVulkan(m_window.handle(), true) )
		{
			Tracer::error(ClassId, "Unable to initialize ImGUI with GLFW !");

			return false;
		}

		/* NOTE: Initialize ImGUI with Vulkan. */
		{
			const auto swapChain = m_graphicsRenderer.swapChain();
			const auto device = swapChain->device();

			/* Create a descriptor pool */
			/* FIXME: These are fancy numbers ! */
			const auto sizes = std::vector< VkDescriptorPoolSize >{
				{VK_DESCRIPTOR_TYPE_SAMPLER, 1000},
				{VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000},
				{VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE, 1000},
				{VK_DESCRIPTOR_TYPE_STORAGE_IMAGE, 1000},
				{VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER, 1000},
				{VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER, 1000},
				{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1000},
				{VK_DESCRIPTOR_TYPE_STORAGE_BUFFER, 1000},
				{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000},
				{VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000},
				{VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT, 1000}
			};

			m_ImGUIDescriptorPool = std::make_shared< DescriptorPool >(device, sizes, 1000, VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT);
			m_ImGUIDescriptorPool->setIdentifier(ClassId, "ImGUI", "DescriptorPool");

			if ( !m_ImGUIDescriptorPool->createOnHardware() )
			{
				Tracer::fatal(ClassId, "Unable to create the ImGUI descriptor pool !");

				return false;
			}

			// Setup Platform/Renderer backends
			ImGui_ImplVulkan_InitInfo info{};
			info.Instance = m_graphicsRenderer.vulkanInstance().handle();
			info.PhysicalDevice = device->physicalDevice()->handle();
			info.Device = device->handle();
			info.QueueFamily = device->getGraphicsFamilyIndex();
			info.Queue = device->getQueue(QueueJob::Graphics, QueuePriority::High)->handle();
			info.PipelineCache = VK_NULL_HANDLE;
			info.DescriptorPool = m_ImGUIDescriptorPool->handle();
			info.RenderPass = swapChain->framebuffer()->renderPass()->handle();
			info.Subpass = 0;
			info.MinImageCount = swapChain->createInfo().minImageCount;
			info.ImageCount = swapChain->imageCount();
			info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
			info.Allocator = VK_NULL_HANDLE;
			info.CheckVkResultFn = nullptr;

			if ( !ImGui_ImplVulkan_Init(&info) )
			{
				Tracer::error(ClassId, "Unable to initialize ImGUI with Vulkan !");

				return false;
			}

			if ( !ImGui_ImplVulkan_CreateFontsTexture() )
			{
				Tracer::error(ClassId, "Unable to create ImGUI fonts texture !");

				return false;
			}
		}

		return true;
	}

	void
	Manager::releaseImGUI () noexcept
	{
		ImGui_ImplVulkan_DestroyFontsTexture();

		ImGui_ImplVulkan_Shutdown();

		ImGui_ImplGlfw_Shutdown();

		ImGui::DestroyContext();

		m_ImGUIDescriptorPool->destroyFromHardware();
		m_ImGUIDescriptorPool.reset();
	}

#endif
}
