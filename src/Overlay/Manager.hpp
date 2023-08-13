/*
 * Emeraude/Overlay/Manager.hpp
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
#include <string>
#include <unordered_map>
#include <memory>
#include <array>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "Input/KeyboardListenerInterface.hpp"
#include "Input/PointerListenerInterface.hpp"
#include "Observer.hpp"

/* Local inclusions for usages. */
#include "Math/Vector.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Graphics
	{
		class Renderer;
	}

	class Arguments;
	class Settings;
	class Window;
}

namespace Emeraude::Overlay
{
	class Screen;

	/**
	 * @brief The overlay manager service class.
	 * @extends Emeraude::ServiceInterface The is a service.
	 * @extends Emeraude::Input::KeyboardListenerInterface The manager needs to listen to the keyboard.
	 * @extends Emeraude::Input::PointerListenerInterface The manager needs to listen to the pointer.
	 * @extends Libraries::Observer The manager needs to listen to each screen events.
	 */
	class Manager final : public ServiceInterface, public Emeraude::Input::KeyboardListenerInterface, public Emeraude::Input::PointerListenerInterface, public Libraries::Observer
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"OverlayManagerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* Program variables */
			static constexpr auto SurfaceOffset = "SurfaceOffset";
			static constexpr auto TextureOffset = "TextureOffset";

			/**
			 * @brief Constructs an overlay manager.
			 * @param arguments A reference to the core arguments.
			 * @param coreSettings A reference to the core settings.
			 * @param window A reference to the window.
			 * @param renderer A reference to the graphics renderer.
			 */
			Manager (const Arguments & arguments, Settings & coreSettings, const Window & window, const Graphics::Renderer & renderer) noexcept;

			/** @brief Destructor. */
			~Manager () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onKeyPress() */
			bool onKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept override;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onKeyRelease() */
			bool onKeyRelease (int key, int scanCode, int modifiers) noexcept override;

			/** @copydoc Emeraude::Input::KeyboardListenerInterface::onCharacterType() */
			bool onCharacterType (unsigned int unicode, int modifiers) noexcept override;

			/** @copydoc Emeraude::Input::PointerListenerInterface::onPointerMove() */
			bool onPointerMove (float x, float y) noexcept override;

			/** @copydoc Emeraude::Input::PointerListenerInterface::onButtonPress() */
			bool onButtonPress (float x, float y, int buttonNumber, int mods) noexcept override;

			/** @copydoc Emeraude::Input::PointerListenerInterface::onButtonRelease() */
			bool onButtonRelease (float x, float y, int buttonNumber, int mods) noexcept override;

			/** @copydoc Emeraude::Input::PointerListenerInterface::onMouseWheel() */
			bool onMouseWheel (float x, float y, float xOffset, float yOffset) noexcept override;

			/**
			 * @brief Returns the arguments reference.
			 * @return const Arguments &
			 */
			[[nodiscard]]
			const Arguments & arguments () const noexcept;

			/**
			 * @brief Returns the core settings reference.
			 * @return
			 */
			[[nodiscard]]
			const Settings & coreSettings () const noexcept;

			/**
			 * @brief Returns the renderer reference.
			 * @return const Settings &
			 */
			[[nodiscard]]
			const Graphics::Renderer & renderer () const noexcept;

			/**
			 * @brief Changes the master control state of overlaying.
			 * @param state The state.
			 */
			void enable (bool state) noexcept;

			/**
			 * @brief Returns whether the overlaying is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool enabled () const noexcept;

			/**
			 * @brief Creates a new screen.
			 * @param screenName A reference to a string.
			 * @return std::shared_ptr< Screen >
			 */
			[[nodiscard]]
			std::shared_ptr< Screen > createScreen (const std::string & screenName) noexcept;

			/**
			 * @brief Disables if active and destroy a named screen.
			 * @param screenName A reference to a string.
			 * @return bool
			 */
			bool destroyScreen (const std::string & screenName) noexcept;

			/**
			 * @brief Gets the named screen and if it's found it will be active on top.
			 * @param screenName A reference to a string.
			 * @return bool
			 */
			bool enableScreen (const std::string & screenName) noexcept;

			/**
			 * @brief Toggle screens activity.
			 * @param screenName A reference to a string.
			 * @return bool
			 */
			bool toggleScreen (const std::string & screenName) noexcept;

			/**
			 * @brief Disables a named active screen.
			 * @param screenName A reference to a string.
			 * @return bool
			 */
			bool disableScreen (const std::string & screenName) noexcept;

			/**
			 * @brief Disables all active screens.
			 */
			void disableAllScreens () noexcept;

			/**
			 * @brief Makes a named screen on top and eventually disable all others screen.
			 * @param screenName A reference to a string.
			 * @param disableOthersScreens
			 * @return bool
			 */
			bool bringScreenOnTop (const std::string & screenName, bool disableOthersScreens) noexcept;

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
			std::shared_ptr< const Screen > screen (const std::string & screenName) const noexcept;

			/**
			 * @brief Returns a named screen.
			 * @param screenName A reference to a string.
			 * @return std::shared_ptr< Screen >
			 */
			std::shared_ptr< Screen > screen (const std::string & screenName) noexcept;

			/**
			 * @brief This method is called when the main handle is updated.
			 * @param windowSize The width and height in pixels of the handle.
			 * @param scale The desired scale for high DPI screen. Default = 1.0.
			 * @return bool
			 */
			bool setPhysicalObjectProperties (const Libraries::Math::Vector< 2, size_t > & windowSize, float scale = 1.0F) noexcept;

			/**
			 * @brief Updates necessary data in video memory. This is the main call.
			 * @return bool
			 */
			bool updateVideoMemory () noexcept;

			/**
			 * @brief Draws actives screens over the 3D render.
			 * @param renderer
			 */
			void render (Graphics::Renderer & renderer) const noexcept;

			/**
			 * @brief Returns the screen width.
			 * @return float
			 */
			[[nodiscard]]
			static float screenWidth () noexcept;

			/**
			 * @brief Returns the screen height.
			 * @return float
			 */
			[[nodiscard]]
			static float screenHeight () noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/** @copydoc Libraries::Observer::onNotification() */
			[[nodiscard]]
			bool onNotification (const Libraries::Observable * observable, int notificationCode, const std::any & data) noexcept override;

			/**
			 * @brief Refreshes the overlay surface size.
			 * @return bool
			 */
			[[nodiscard]]
			bool updateSurfaceSize () const noexcept;

			/**
			 * @brief loadProgram
			 * @return bool
			 */
			bool loadProgram () noexcept;

			/* Flag names. */
			static constexpr auto Usable = 0UL;
			static constexpr auto Enabled = 1UL;

			static std::array< float, 2 > s_surfaceSize; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables)

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members)
			const Arguments & m_arguments;
			Settings & m_coreSettings;
			const Window & m_window;
			const Graphics::Renderer & m_renderer;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members)
			std::unordered_map< std::string, std::shared_ptr< Screen > > m_screens{};
			std::unordered_map< std::string, std::shared_ptr< Screen > > m_activeScreens{};
			/* VULKAN_DEV */
			//std::shared_ptr< Graphics::Program > m_program{};
			//Graphics::RasterizationMode m_rasterizationMode{};
			float m_scale = 1.0F;
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*Usable*/,
				true/*Enabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
