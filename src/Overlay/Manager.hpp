/*
 * src/Overlay/Manager.hpp
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
#include <cstddef>
#include <array>
#include <unordered_map>
#include <vector>
#include <memory>
#include <string>
#include <any>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "Input/KeyboardListenerInterface.hpp"
#include "Input/PointerListenerInterface.hpp"
#include "Libraries/ObserverTrait.hpp"

/* Local inclusions for usages. */
#include "Input/Manager.hpp"
#include "FramebufferProperties.hpp"
#include "UIScreen.hpp"
#ifdef IMGUI_ENABLED
#include "imgui.h"
#include "ImGUIScreen.hpp"
#endif

/* Forward declarations. */
namespace Emeraude::Graphics::Geometry
{
	class IndexedVertexResource;
}

namespace Emeraude::Overlay
{
	/**
	 * @brief The overlay manager service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Emeraude::Input::KeyboardListenerInterface The manager needs to listen to the keyboard.
	 * @extends Emeraude::Input::PointerListenerInterface The manager needs to listen to the pointer.
	 */
	class Manager final : public ServiceInterface, public Input::KeyboardListenerInterface, public Input::PointerListenerInterface, public Libraries::ObserverTrait
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"OverlayManagerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			enum NotificationCode
			{
				UIScreenCreated,
				UIScreenDestroying,
				UIScreenDestroyed,
				OverlayResized,
				MaxEnum
			};

			/**
			 * @brief Constructs an overlay manager.
			 * @param primaryServices A reference to primary services.
			 * @param window A reference to the window.
			 * @param graphicsRenderer A reference to the graphics renderer.
			 */
			Manager (PrimaryServices & primaryServices, Window & window, Graphics::Renderer & graphicsRenderer) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Manager (const Manager & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Manager (Manager && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Manager &
			 */
			Manager & operator= (const Manager & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Manager &
			 */
			Manager & operator= (Manager && copy) noexcept = delete;

			/**
			 * @brief Destructs the overlay manager service.
			 */
			~Manager () override = default;

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

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool
			usable () const noexcept override
			{
				return m_flags[ServiceInitialized];
			}

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onKeyPress() */
			bool onKeyPress (int32_t key, int32_t scancode, int32_t modifiers, bool repeat) noexcept override;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onKeyRelease() */
			bool onKeyRelease (int32_t key, int32_t scancode, int32_t modifiers) noexcept override;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onCharacterType() */
			bool onCharacterType (uint32_t unicode) noexcept override;

			/** @copydoc Emeraude::Input::PointerListenerInterface::onPointerMove() */
			bool onPointerMove (float positionX, float positionY) noexcept override;

			/** @copydoc Emeraude::Input::PointerListenerInterface::onButtonPress() */
			bool onButtonPress (float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept override;

			/** @copydoc Emeraude::Input::PointerListenerInterface::onButtonRelease() */
			bool onButtonRelease (float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept override;

			/** @copydoc Emeraude::Input::PointerListenerInterface::onMouseWheel() */
			bool onMouseWheel (float positionX, float positionY, float xOffset, float yOffset) noexcept override;

			/**
			 * @brief Returns the reference to the primary services.
			 * @return PrimaryServices &
			 */
			[[nodiscard]]
			PrimaryServices &
			primaryServices () const noexcept
			{
				return m_primaryServices;
			}

			/**
			 * @brief Changes the master control state of overlaying.
			 * @param inputManager A reference to the input manager.
			 * @param state The state.
			 * @return void
			 */
			void enable (Input::Manager & inputManager, bool state) noexcept;

			/**
			 * @brief Returns whether the overlaying is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isEnabled () const noexcept
			{
				return m_flags[Enabled];
			}

			/**
			 * @brief Creates a new screen.
			 * @param name A reference to a string.
			 * @param enableKeyboardListener Enables the keyboard listener at creation.
			 * @param enablePointerListener Enables the pointer listener at creation.
			 * @return std::shared_ptr< UIScreen >
			 */
			[[nodiscard]]
			std::shared_ptr< UIScreen > createScreen (const std::string & name, bool enableKeyboardListener, bool enablePointerListener) noexcept;

#ifdef IMGUI_ENABLED
			/**
			 * @brief Creates an ImGUI screen.
			 * @param name A reference to a string.
			 * @param drawFunction A reference to a function.
			 * @return std::shared_ptr< ImGUIScreen >
			 */
			[[nodiscard]]
			std::shared_ptr< ImGUIScreen > createImGUIScreen (const std::string & name, const std::function< void () > & drawFunction) noexcept;
#endif

			/**
			 * @brief Destroys a named screen.
			 * @param name A reference to a string.
			 * @return bool
			 */
			bool destroyScreen (const std::string & name) noexcept;

			/**
			 * @brief Gets the named screen and if it's found it will be active on top.
			 * @param name A reference to a string.
			 * @return bool
			 */
			bool enableScreen (const std::string & name) noexcept;

			/**
			 * @brief Toggle screens activity.
			 * @param name A reference to a string.
			 * @return bool
			 */
			bool toggleScreen (const std::string & name) noexcept;

			/**
			 * @brief Disables a named active screen.
			 * @param name A reference to a string.
			 * @return bool
			 */
			bool disableScreen (const std::string & name) noexcept;

			/**
			 * @brief Disables all active screens.
			 * @return void
			 */
			void disableAllScreens () noexcept;

			/**
			 * @brief Makes a named screen on top and eventually disable all others screen.
			 * @param screenName A reference to a string.
			 * @return bool
			 */
			bool bringScreenOnTop (const std::string & screenName) noexcept;

			/**
			 * @brief Returns a list of screen names.
			 * @return std::vector< std::string >
			 */
			[[nodiscard]]
			std::vector< std::string > screensNameList () const noexcept;

			/**
			 * @brief Returns a list of active screen names.
			 * @return std::vector< std::string >
			 */
			[[nodiscard]]
			std::vector< std::string > activeScreensNameList () const noexcept;

			/**
			 * @brief Returns a named screen.
			 * @param screenName A reference to a string.
			 * @return std::shared_ptr< const Screen >
			 */
			[[nodiscard]]
			std::shared_ptr< const UIScreen > screen (const std::string & screenName) const noexcept;

			/**
			 * @brief Returns a named screen.
			 * @param screenName A reference to a string.
			 * @return std::shared_ptr< Screen >
			 */
			std::shared_ptr< UIScreen > screen (const std::string & screenName) noexcept;

			/**
			 * @brief Updates necessary data in video memory.
			 * @return bool
			 */
			bool updateVideoMemory () noexcept;

			/**
			 * @brief Draws actives screens over the 3D render.
			 * @param renderTarget A reference to a render target smart pointer.
			 * @param commandBuffer A reference to a command buffer.
			 * @return void
			 */
			void render (const std::shared_ptr< Graphics::RenderTarget::Abstract > & renderTarget, const Vulkan::CommandBuffer & commandBuffer) const noexcept;

			/**
			 * @brief Returns the framebuffer properties used to build the UI.
			 * @return const FramebufferProperties &
			 */
			[[nodiscard]]
			const FramebufferProperties &
			framebufferProperties () const noexcept
			{
				return m_framebufferProperties;
			}

			/**
			 * @brief Returns the surface geometry.
			 * @return std::shared_ptr< const Graphics::Geometry::IndexedVertexResource >
			 */
			[[nodiscard]]
			std::shared_ptr< const Graphics::Geometry::IndexedVertexResource >
			surfaceGeometry () const noexcept
			{
				return m_surfaceGeometry;
			}

			/**
			 * @brief Sets an exclusive screen to receive inputs.
			 * @param name A reference to a string.
			 * @return bool
			 */
			[[nodiscard]]
			bool setInputExclusiveScreen (const std::string & name) noexcept;

			/**
			 * @brief Disables a previous input exclusive screen.
			 * @return void
			 */
			void
			disableInputExclusiveScreen () noexcept
			{
				m_inputExclusiveScreen.reset();
			}

			/**
			 * @bries Returns whether an input exclusive screen has been set.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isInputExclusiveScreenEnabled () const noexcept
			{
				return m_inputExclusiveScreen != nullptr;
			}

			/**
			 * @brief Returns the screen set as input exclusive.
			 * @warning This can be nullptr.
			 * @return std::shared_ptr< UIScreen >
			 */
			[[nodiscard]]
			std::shared_ptr< UIScreen >
			inputExclusiveScreen () const noexcept
			{
				return m_inputExclusiveScreen;
			}

			/**
			 * @brief Gets or creates the descriptor set layout for this surface.
			 * @note The descriptor set layout is common for all the overlay.
			 * @warning Can be nullptr !
			 * @param layoutManager A reference to the layout manager.
			 * @return std::shared_ptr< Vulkan::DescriptorSetLayout >
			 */
			[[nodiscard]]
			static std::shared_ptr< Vulkan::DescriptorSetLayout > getDescriptorSetLayout (Vulkan::LayoutManager & layoutManager) noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/** @copydoc Libraries::ObserverTrait::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::ObservableTrait * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief Resize the overlay.
			 * @param fromResize Tells a resize occurred.
			 * @return void
			 */
			void updateContent (bool fromResize) noexcept;

			/**
			 * @brief Generates the overlay graphics pipeline.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateProgram () noexcept;

			/**
			 * @brief Updates the overlay graphics pipeline after a resize.
			 * @return bool
			 */
			[[nodiscard]]
			bool updateProgram () const noexcept;

#ifdef IMGUI_ENABLED

			/**
			* @brief Initializes the ImGUI library.
			* @return bool
			*/
			[[nodiscard]]
			bool initImGUI () noexcept;

			/**
			* @brief Releases the ImGUI library.
			* @return void
			*/
			void releaseImGUI () noexcept;

#endif

			/* Flag names. */
			static constexpr auto ServiceInitialized{0UL};
			static constexpr auto Enabled{1UL};

			PrimaryServices & m_primaryServices;
			Window & m_window;
			Graphics::Renderer & m_graphicsRenderer;
			std::shared_ptr< Graphics::Geometry::IndexedVertexResource > m_surfaceGeometry;
			std::shared_ptr< Saphir::Program > m_program;
			std::unordered_map< std::string, std::shared_ptr< UIScreen > > m_screens;
			std::shared_ptr< UIScreen > m_inputExclusiveScreen;
			FramebufferProperties m_framebufferProperties;
#ifdef IMGUI_ENABLED
			std::string m_iniFilepath;
			std::string m_logFilepath;
			std::shared_ptr< Vulkan::DescriptorPool > m_ImGUIDescriptorPool;
			std::unordered_map< std::string, std::shared_ptr< ImGUIScreen > > m_ImGUIScreens;
#endif
			std::array< bool, 8 > m_flags{
				false/*ServiceInitialized*/,
				false/*Enabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
