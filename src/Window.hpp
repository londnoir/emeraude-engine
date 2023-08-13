/*
 * Emeraude/Window.hpp
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
#include <array>
#include <functional>
#include <memory>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "Math/Vector.hpp"
#include "Vulkan/Surface.hpp"
#include "emeraude_config.hpp"

/* Third-Party */
#include "Third-Party-Inclusion/glfw.hpp"

/* Forward declarations. */
namespace Emeraude::Vulkan
{
	class Instance;
}

namespace Emeraude
{
	/* Forward declarations. */
	class Arguments;
	class Settings;

	/**
	 * @brief The handle service class is responsible for the physical screen.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class Window final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"WindowService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* Settings keys */
			static constexpr auto ShowInformationKey = "Video/Window/ShowInformation";
			static constexpr auto DefaultShowInformation = BOOLEAN_FOLLOWING_DEBUG;
			static constexpr auto PreferredMonitorKey = "Video/Window/PreferredMonitor";
			static constexpr auto DefaultPreferredMonitor = 0;
			static constexpr auto FullscreenEnabledKey = "Video/Window/FullscreenEnabled";
			static constexpr auto DefaultFullscreenEnabled = false;
			static constexpr auto RefreshRateKey = "Video/Window/RefreshRate";
			static constexpr auto DefaultRefreshRate = -1;
			static constexpr auto FramelessWindowKey = "Video/Window/FramelessWindow";
			static constexpr auto DefaultFramelessWindow = false;
			static constexpr auto VSyncEnabledKey = "Video/Window/VSyncEnabled";
			static constexpr auto DefaultVSyncEnabled = false;
			static constexpr auto FullscreenGammaKey = "Video/Window/FullscreenGamma";
			static constexpr auto DefaultFullscreenGamma = 1.0;
			static constexpr auto CreateSurfaceWithGLFWKey = "Video/Window/CreateSurfaceWithGLFW";
			static constexpr auto DefaultCreateSurfaceWithGLFW = true;
			static constexpr auto AlwaysCenterWindowOnStartupKey = "Video/Window/AlwaysCenterWindowOnStartup";
			static constexpr auto WindowXPositionKey = "Video/Window/WindowXPosition";
			static constexpr auto DefaultWindowXPosition = 0;
			static constexpr auto WindowYPositionKey = "Video/Window/WindowYPosition";
			static constexpr auto DefaultWindowYPosition = 0;
			static constexpr auto WindowWidthKey = "Video/Window/WindowWidth";
			static constexpr auto DefaultWidth = 1920U;
			static constexpr auto WindowHeightKey = "Video/Window/WindowHeight";
			static constexpr auto DefaultHeight = 1080U;
			static constexpr auto FullscreenWidthKey = "Video/Window/FullscreenWidth";
			static constexpr auto FullscreenHeightKey = "Video/Window/FullscreenHeight";

			/* NOTE: OpenGL specific settings */
			static constexpr auto VideoEnableSwapControlTearKey = "Video/Framebuffer/EnableSwapControlTear";
			static constexpr auto VideoDoubleBufferEnabledKey = "Video/Framebuffer/DoubleBufferEnabled";
			static constexpr auto VideoFramebufferColorBufferBitsKey = "Video/Framebuffer/ColorBufferBits";
			static constexpr auto DefaultColorBufferBits = 32;
			static constexpr auto VideoFramebufferDepthBufferBitsKey = "Video/Framebuffer/DepthBufferBits";
			static constexpr auto DefaultDepthBufferBits = 24;
			static constexpr auto VideoFramebufferStencilBufferBitsKey = "Video/Framebuffer/StencilBufferBits";
			static constexpr auto DefaultStencilBufferBits = 0;
			static constexpr auto VideoFramebufferMultisamplingKey = "Video/Framebuffer/Multisampling";
			static constexpr auto DefaultSamples = 1;
			static constexpr auto VideosRGBEnabledKey = "Video/Framebuffer/sRGBEnabled";

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				Created,
				Destroyed,
				Centered,
				OSNotifiesWindowGetFocus,
				OSNotifiesWindowLostFocus,
				OSNotifiesWindowMovedTo,
				OSNotifiesWindowVisible,
				OSNotifiesWindowHidden,
				OSNotifiesWindowSizeMaximized,
				OSNotifiesWindowSizeMinimized,
				OSNotifiesWindowResized,
				OSNotifiesFramebufferResized,
				OSRequestsToRescaleContentBy,
				OSRequestsToRefreshContent,
				OSRequestsToTerminate,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Automatic
			 */
			static constexpr auto Automatic = 0;

			/**
			 * @brief Constructs a Window.
			 * @param arguments A reference to Arguments.
			 * @param coreSettings A reference to the core settings to read the window configuration.
			 * @param instance A reference to the Vulkan instance.
			 * @param title A reference to a string for the window title [std::move].
			 */
			Window (const Arguments & arguments, Settings & coreSettings, const Vulkan::Instance & instance, std::string title) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Returns the handle of the GLFW window object.
			 * @return const GLFWwindow *
			 */
			[[nodiscard]]
			const GLFWwindow * handle () const noexcept;

			/**
			 * @brief Returns the handle of the GLFW window object.
			 * @return GLFWwindow *
			 */
			[[nodiscard]]
			GLFWwindow * handle () noexcept;

			/**
			 * @brief Returns the vulkan handle of the surface.
			 * @return const Vulkan::Surface *
			 */
			[[nodiscard]]
			const Vulkan::Surface * surface () const noexcept;

			/**
			 * @brief Returns the vulkan handle of the surface.
			 * @return Vulkan::Surface *
			 */
			[[nodiscard]]
			Vulkan::Surface * surface () noexcept;

			/**
			 * @brief Resizes programmatically the window size. This function takes care of the fullscreen/window mode.
			 * @param width The new width.
			 * @param height The new height.
			 * @return bool
			 */
			bool resize (int32_t width, int32_t height) noexcept;

			/**
			 * @brief Sets the window position on the desktop.
			 * @param xPosition The X position in screen coordinates.
			 * @param yPosition The Y position in screen coordinates.
			 * @return bool
			 */
			bool setPosition (int32_t xPosition, int32_t yPosition) noexcept;

			/**
			 * @brief Set the screen gamma.
			 * @param value A positive value.
			 * @return void
			 */
			void setGamma (float value) noexcept;

			/**
			 * @todo Finish this method.
			 * @return void
			 */
			void setCustomGamma () noexcept;

			/**
			 * @brief Sets fullscreen mode.
			 * @param state The state.
			 * @return void
			 */
			void setFullscreenMode (bool state) noexcept;

			/**
			 * @brief Set vertical synchronization state.
			 * @param state The state.
			 * @return void
			 */
			void setVSyncState (bool state) noexcept;

			/**
			 * @brief Returns the vertical synchronization state.
			 * @return bool
			 */
			[[nodiscard]]
			bool getVSyncState () const noexcept;

			/**
			 * @brief Returns the centered position for the window.
			 * @param monitorNumber The number of the monitor for multiple monitors configuration.
			 * @return std::array< int32_t, 2 >
			 */
			[[nodiscard]]
			std::array< int32_t, 2 > getCenteredPosition (uint32_t monitorNumber = DefaultPreferredMonitor) const noexcept;

			/**
			 * @brief Returns whether the window is visible on the user view.
			 * @return bool
			 */
			[[nodiscard]]
			bool isVisibleOnDesktop () const noexcept;

			/**
			 * @brief Returns whether the window is hidden from the user view.
			 * @return bool
			 */
			[[nodiscard]]
			bool isIconified () const noexcept;

			/**
			 * @brief Reduces the window to the OS toolbar or similar.
			 * @return void
			 */
			void iconify () const noexcept;

			/**
			 * @brief Restores the window on the user desktop view.
			 * @return void
			 */
			void getBackOnDesktop () const noexcept;

			/**
			 * @brief Returns whether the window cover the whole desktop.
			 * @return bool
			 */
			[[nodiscard]]
			bool isSizeMaximized () const noexcept;

			/**
			 * @brief Returns whether the window is a floating window.
			 * @return bool
			 */
			[[nodiscard]]
			bool isSizeReduced () const noexcept;

			/**
			 * @brief Maximizes the window size on the user desktop.
			 * @return void
			 */
			void maximizeSize () const noexcept;

			/**
			 * @brief Restores the window to previous size.
			 * @return void
			 */
			void restoreSize () const noexcept;

			/**
			 * @brief Returns whether the window is focused by the system host.
			 * @return bool
			 */
			[[nodiscard]]
			bool isFocused () const noexcept;

			/**
			 * @brief Returns whether the window is blurred by the system host.
			 * @return bool
			 */
			[[nodiscard]]
			bool isBlurred () const noexcept;

			/**
			 * @brief Asks the host system to focus on the window.
			 * @return bool
			 */
			void focus () const noexcept;

			/**
			 * @brief Returns whether the window is visible.
			 * @return bool
			 */
			[[nodiscard]]
			bool isVisible () const noexcept;

			/**
			 * @brief Returns whether the window is hidde.
			 * @return bool
			 */
			[[nodiscard]]
			bool isHidden () const noexcept;

			/**
			 * @brief hides the window.
			 * @return bool
			 */
			void hide () const noexcept;

			/**
			 * @brief Shows the window.
			 * @return bool
			 */
			void show () const noexcept;

			/**
			 * @brief Returns whether the fullscreen mode is enabled.
			 * @return bool
			 */
			[[nodiscard]]
			bool isFullscreenMode () const noexcept;

			/**
			 * @brief Returns the position, in screen coordinates, of the upper-left corner of the content area of the window.
			 * @return std::array< int32_t, 2 >
			 */
			[[nodiscard]]
			std::array< int32_t, 2 > getPosition () const noexcept;

			/**
			 * @brief Returns the size, in screen coordinates, of the content area of the window.
			 * @return std::array< uint32_t, 2 >
			 */
			[[nodiscard]]
			std::array< uint32_t, 2 > getSize () const noexcept;

			/**
			 * @brief Returns the size, in screen coordinates, of each edge of the frame of the window.
			 * @note The array will hold left, top, right and bottom.
			 * @return std::array< uint32_t, 4 >
			 */
			[[nodiscard]]
			std::array< uint32_t, 4 > getBorderSize () const noexcept;

			/**
			 * @brief Returns the size, in pixels, of the framebuffer of the window.
			 * @return std::array< uint32_t, 2 >
			 */
			[[nodiscard]]
			std::array< uint32_t, 2 > getFramebufferSize () const noexcept;

			/**
			 * @brief Returns the content scale for the window.
			 * @return std::array< float, 2 >
			 */
			[[nodiscard]]
			std::array< float, 2 > getContentScale () const noexcept;

			/**
			 * @brief Returns the aspect ratio of the window.
			 * @return float
			 */
			[[nodiscard]]
			float aspectRatio () const noexcept;

			/**
			 * @brief Waits for a valid window size.
			 * @return bool
			 */
			[[nodiscard]]
			bool waitValidWindowSize () const noexcept;

			/**
			 * @brief Prints the windows geometry for debugging purpose.
			 * @return void
			 */
			void DEV_printWindowGeometry () const noexcept;

			/**
			 * @brief Prints the windows attributes for debugging purpose.
			 * @return void
			 */
			void DEV_printWindowAttrib () const noexcept;

			/**
			 * @brief Returns the position, in screen coordinates, of the upper-left corner of the content area of the window.
			 * @param monitor A pointer to the monitor.
			 * @return std::array< int32_t, 2 >
			 */
			[[nodiscard]]
			static std::array< int32_t, 2 > getDesktopPosition (GLFWmonitor * monitor) noexcept;

			/**
			 * @brief Returns the desktop resolution.
			 * @param monitor A pointer to the monitor. Default primary.
			 * @return std::array< uint32_t, 2 >
			 */
			[[nodiscard]]
			static std::array< uint32_t, 2 > getDesktopSize (GLFWmonitor * monitor = nullptr) noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Checks monitors information and keep it to a static member from here.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkMonitors () const noexcept;

			/**
			 * @brief Creates the window related objects.
			 * @param width The width of the window.
			 * @param height The height of the window.
			 * @param monitorNumber The number of the monitor for multiple monitors configuration.
			 * @param fullscreenMode Request the fullscreen mode.
			 * @return bool
			 */
			bool create (int width, int height, int monitorNumber, bool fullscreenMode) noexcept;

			/**
			 * @brief Returns a list of available monitors on the system.
			 * @return std::vector< GLFWmonitor * >
			 */
			[[nodiscard]]
			static std::vector< GLFWmonitor * > getMonitors () noexcept;

			/**
			 * @brief Returns the monitor handles at monitor index.
			 * @param monitorNumber The monitor index.
			 * @return GLFWmonitor *
			 */
			[[nodiscard]]
			static GLFWmonitor * getMonitor (uint32_t monitorNumber) noexcept;

			/**
			 * @brief Returns a list of available mode for a specified monitor.
			 * @return std::vector< GLFWvidmode >
			 */
			[[nodiscard]]
			static std::vector< GLFWvidmode > getMonitorModes (GLFWmonitor * monitor) noexcept;

			/**
			 * @brief This callback for GLFW is called when the allocated framebuffer of the window is resized.
			 * @note The order of call is : framebufferSizeCallback(), windowSizeCallback() then windowRefreshCallback().
			 * @param window A pointer to the system window handle.
			 * @param width The width of the framebuffer in pixel.
			 * @param height The height of the framebuffer in pixel.
			 * @return void
			 */
			static void framebufferSizeCallback (GLFWwindow * window, int width, int height) noexcept;

			/**
			 * @brief This callback for GLFW is called when the allocated framebuffer of the window is resized.
			 * @note Do not pass the window size to glViewport or other pixel-based OpenGL calls.
			 * The window size is in screen coordinates, not pixels.
			 * Use the framebuffer size, which is in pixels, for pixel-based calls.
			 * @param window A pointer to the system window handle.
			 * @param width The new width of the window in screen coordinates.
			 * @param height The new height of the window in screen coordinates.
			 * @return void
			 */
			static void windowSizeCallback (GLFWwindow * window, int width, int height) noexcept;

			/**
			 * @brief This callback for GLFW is called when the window is modified by the system. ie: a resize.
			 * @param window A pointer to the system window handle.
			 * @return void
			 */
			static void windowRefreshCallback (GLFWwindow * window) noexcept;

			/**
			 * @brief Notifies a monitor configuration change.
			 * @param monitor A pointer to the system monitor handle.
			 * @param event The type of event.
			 * @return void
			 */
			static void monitorConfigurationChanged (GLFWmonitor * monitor, int event) noexcept;

			/**
			 * @brief Notifies a window position change on the user desktop.
			 * @param window A pointer to the system window handle.
			 * @param xPosition The new x position of the window.
			 * @param yPosition The new y position of the window.
			 * @return void
			 */
			static void windowPositionCallback (GLFWwindow * window, int xPosition, int yPosition) noexcept;

			/**
			 * @brief Notifies a use try to close the window from the host system.
			 * @param window A pointer to the system window handle.
			 */
			static void windowCloseCallback (GLFWwindow * window) noexcept;

			/**
			 * @brief Notifies the window is focused by the host system.
			 * @param window A pointer to the system window handle.
			 * @param focused The state from the OS.
			 * @return void
			 */
			static void windowFocusCallback (GLFWwindow * window, int focused) noexcept;

			/**
			 * @brief Notifies the window is hidden from the desktop in the host system.
			 * @param window A pointer to the system window handle.
			 * @param hidden The state from the OS.
			 * @return void
			 */
			static void windowIconifyCallback (GLFWwindow * window, int hidden) noexcept;

			/**
			 * @brief Notifies whether the window is enlarged to cover the whole desktop in the host system.
			 * @param window A pointer to the system window handle.
			 * @param maximized The state from the OS.
			 * @return void
			 */
			static void windowMaximizeCallback (GLFWwindow * window, int maximized) noexcept;

			/**
			 * @brief Notifies the window content request a scale by the host system.
			 * @param window A pointer to the system window handle.
			 * @param xScale The scale in X of the window content.
			 * @param yScale TThe scale in Y of the window content.
			 * @return void
			 */
			static void windowContentScaleCallback (GLFWwindow * window, float xScale, float yScale) noexcept;

			/**
			 * @brief Returns the centered position for the window.
			 * @note The window size is forced due to a GLFW bug at startup.
			 * @param windowSize
			 * @param monitorNumber The number of the monitor for multiple monitors configuration.
			 * @return std::array< int32_t, 2 >
			 */
			[[nodiscard]]
			static std::array< int32_t, 2 > getCenteredPosition (const std::array< uint32_t , 2 > & windowSize, uint32_t monitorNumber = DefaultPreferredMonitor) noexcept;

			/* Flag names. */
			static constexpr auto ShowInformation = 0UL;
			static constexpr auto VerticalSyncEnabled = 1UL;

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			Settings & m_coreSettings;
			const Vulkan::Instance & m_instance;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			std::string m_title;
			std::unique_ptr< GLFWwindow, std::function< void (GLFWwindow *) > > m_handle{};
			std::unique_ptr< Vulkan::Surface > m_surface{};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*ShowInformation*/,
				false/*VerticalSyncEnabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
