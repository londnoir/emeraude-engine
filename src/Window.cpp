/*
 * Emeraude/Window.cpp
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

#include "Window.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Arguments.hpp"
#include "Settings.hpp"
#include "Vulkan/Instance.hpp"
#include "Vulkan/Utility.hpp"

/* Third-party */
#include "Third-Party-Inclusion/glfw.hpp"

namespace Emeraude
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic, cppcoreguidelines-pro-type-reinterpret-cast, *-magic-numbers)
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Graphics;
	using namespace Vulkan;

	const size_t Window::ClassUID{Observable::getClassUID()};

	Window::Window (const Arguments & arguments, Settings & coreSettings, const Instance & instance, std::string title) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_coreSettings(coreSettings), m_instance(instance), m_title(std::move(title))
	{

	}

	bool
	Window::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Window::usable () const noexcept
	{
		return m_handle != nullptr;
	}

	bool
	Window::onInitialize () noexcept
	{
		m_flags[ShowInformation] = m_coreSettings.getAs< bool >(ShowInformationKey, DefaultShowInformation);

		if ( !m_instance.usable() )
		{
			Tracer::fatal(ClassId, "There is no vulkan instance available !");

			return false;
		}

		/* Checks monitor presence. */
		if ( !this->checkMonitors() )
		{
			Tracer::fatal(ClassId, "There is no monitor on the system, graphic API loading cancelled !");

			return false;
		}

		const auto preferredMonitor = m_coreSettings.getAs< int >(PreferredMonitorKey, DefaultPreferredMonitor);

		/* Disabling OpenGL context creation for Vulkan API */
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

		/* Creating window in window or fullscreen mode */
		if ( m_coreSettings.getAs< bool >(FullscreenEnabledKey, DefaultFullscreenEnabled) )
		{
			const auto fullscreenWidth = m_coreSettings.getAs< int32_t >(FullscreenWidthKey, DefaultWidth);
			const auto fullscreenHeight = m_coreSettings.getAs< int32_t >(FullscreenHeightKey, DefaultHeight);
			const auto refreshRate = m_coreSettings.getAs< int32_t >(RefreshRateKey, DefaultRefreshRate);

			if ( refreshRate > 0 )
			{
				glfwWindowHint(GLFW_REFRESH_RATE, refreshRate);

				if ( m_flags[ShowInformation] )
				{
					TraceInfo{ClassId} << refreshRate << "Hz monitor refresh rate requested.";
				}
			}
			else
			{
				glfwWindowHint(GLFW_REFRESH_RATE, GLFW_DONT_CARE);
			}

			/* GLFW_AUTO_ICONIFY specifies whether the full screen window will
			 * automatically iconify and restore the previous video mode on
			 * input focus loss. Possible values are GLFW_TRUE and GLFW_FALSE.
			 * This hint is ignored for windowed mode windows. */
			glfwWindowHint(GLFW_AUTO_ICONIFY, GLFW_TRUE);

			if ( !this->create(fullscreenWidth, fullscreenHeight, preferredMonitor, true) )
			{
				Tracer::fatal(ClassId, "Unable to get a valid fullscreen window !");

				return false;
			}
		}
		else
		{
			const auto windowWidth = m_coreSettings.getAs< int32_t >(WindowWidthKey, DefaultWidth);
			const auto windowHeight = m_coreSettings.getAs< int32_t >(WindowHeightKey, DefaultHeight);
			const auto frameless = m_coreSettings.getAs< bool >(FramelessWindowKey, DefaultFramelessWindow);

			/* GLFW_RESIZABLE specifies whether the windowed mode window
			 * will be resizable by the user. The window will still be resizable
			 * using the glfwSetWindowSize function. Possible values are
			 * GLFW_TRUE and GLFW_FALSE. This hint is ignored for full screen
			 * and undecorated windows. */
			glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

			/* GLFW_VISIBLE specifies whether the windowed mode window will
			 * be initially visible. Possible values are GLFW_TRUE
			 * and GLFW_FALSE. This hint is ignored for full screen windows. */
			glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE); /* NOTE: Start hidden ! */

			/* GLFW_DECORATED specifies whether the windowed mode window will
			 * have window decorations such as a border, a close widget, etc.
			 * An undecorated window will not be resizable by the user but will
			 * still allow the user to generate close events on some platforms.
			 * Possible values are GLFW_TRUE and GLFW_FALSE. This hint is ignored
			 * for full screen windows. */
			glfwWindowHint(GLFW_DECORATED, frameless ? GLFW_FALSE : GLFW_TRUE);

			/* GLFW_FOCUSED specifies whether the windowed mode window will be
			 * given input focus when created. Possible values are GLFW_TRUE
			 * and GLFW_FALSE. This hint is ignored for full screen and initially
			 * hidden windows. */
			glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);

			/* GLFW_FLOATING specifies whether the windowed mode window will be
			 * floating above other regular windows, also called topmost or always-on-top.
			 * This is intended primarily for debugging purposes and cannot be used to
			 * implement proper full screen windows. Possible values are GLFW_TRUE and GLFW_FALSE.
			 * This hint is ignored for full screen windows. */
			glfwWindowHint(GLFW_FLOATING, GLFW_FALSE);

			/* GLFW_MAXIMIZED specifies whether the windowed mode window will be maximized when created.
			 * Possible values are GLFW_TRUE and GLFW_FALSE. This hint is ignored for full screen windows. */
			glfwWindowHint(GLFW_MAXIMIZED, GLFW_FALSE);

			/* GLFW_CENTER_CURSOR specifies whether the cursor should be centered over newly
			 * created full screen windows. Possible values are GLFW_TRUE and GLFW_FALSE.
			 * This hint is ignored for windowed mode windows. */
			glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);

			/* GLFW_TRANSPARENT_FRAMEBUFFER specifies whether the window framebuffer will
			 * be transparent. If enabled and supported by the system, the window framebuffer
			 * alpha channel will be used to combine the framebuffer with the background.
			 * This does not affect window decorations. Possible values are GLFW_TRUE and GLFW_FALSE. */
			glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_FALSE);

			/* GLFW_FOCUS_ON_SHOW specifies whether the window will be given input
			 * focus when glfwShowWindow is called. Possible values are GLFW_TRUE and GLFW_FALSE. */
			glfwWindowHint(GLFW_FOCUS_ON_SHOW, GLFW_TRUE);

			/* GLFW_SCALE_TO_MONITOR specified whether the window content area should be
			 * resized based on the monitor content scale of any monitor it is placed on.
			 * This includes the initial placement when the window is created.
			 * Possible values are GLFW_TRUE and GLFW_FALSE.
			 *
			 * This hint only has an effect on platforms where screen coordinates
			 * and pixels always map 1:1 such as Windows and X11. On platforms like
			 * macOS the resolution of the framebuffer is changed independently
			 * of the window size.*/
			glfwWindowHint(GLFW_SCALE_TO_MONITOR, GLFW_TRUE);

			/* macOS specific window hints */
#if IS_MACOS
			//glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_TRUE);
			//glfwWindowHintString(GLFW_COCOA_FRAME_NAME, ""); // UTF-8 encoded frame autosave name
			//glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GLFW_FALSE);
#endif

			/* X11 specific window hints */
#if IS_LINUX
			glfwWindowHintString(GLFW_X11_CLASS_NAME, "Emeraude-Engine"); // An ASCII encoded WM_CLASS class name
			glfwWindowHintString(GLFW_X11_INSTANCE_NAME, "ProjetAlpha"); // An ASCII encoded WM_CLASS instance name
#endif

			if ( this->create(windowWidth, windowHeight, preferredMonitor, false) )
			{
				this->resize(windowWidth, windowHeight);
			}
			else
			{
				Tracer::fatal(ClassId, "Unable to get a valid window !");

				return false;
			}
		}

		/* V-Sync : After context creation ! */
		if ( m_coreSettings.getAs< bool >(VSyncEnabledKey, DefaultVSyncEnabled) )
		{
			if ( m_flags[ShowInformation] )
			{
				Tracer::info(ClassId, "Vertical synchronization requested.");
			}
			
			//this->setVSyncState(true);
		}

		if ( this->isFullscreenMode() )
		{
			const auto exponent = m_coreSettings.getAs< float >(FullscreenGammaKey, DefaultFullscreenGamma);

			this->setGamma(exponent);
		}
		else
		{
			if ( m_coreSettings.getAs< bool >(AlwaysCenterWindowOnStartupKey, false) )
			{
				const auto windowWidth = m_coreSettings.getAs< uint32_t >(WindowWidthKey, DefaultWidth);
				const auto windowHeight = m_coreSettings.getAs< uint32_t >(WindowHeightKey, DefaultHeight);
				const auto centeredPosition = Window::getCenteredPosition({windowWidth, windowHeight}, preferredMonitor);

				TraceInfo{ClassId} << "Center the window position to X: " << centeredPosition[0] << ", Y" << centeredPosition[1] << " ...";

				this->setPosition(centeredPosition[0], centeredPosition[1]);
			}
			else
			{
				const auto XPosition = m_coreSettings.getAs< int32_t >(WindowXPositionKey, DefaultWindowXPosition);
				const auto YPosition = m_coreSettings.getAs< int32_t >(WindowYPositionKey, DefaultWindowYPosition);

				TraceInfo{ClassId} << "Setting window position to X: " << XPosition << ", Y" << YPosition << " ...";

				this->setPosition(XPosition, YPosition);
			}
		}

		VkResult result = VK_SUCCESS;

		VkSurfaceKHR surfaceHandle{VK_NULL_HANDLE};

#ifdef ENABLE_GLFW_NATIVE_CODE_EXPOSITION
		if ( !m_coreSettings.getAs< bool >(CreateSurfaceWithGLFWKey, DefaultCreateSurfaceWithGLFW) )
		{
	#ifdef IS_LINUX
			VkXcbSurfaceCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_XCB_SURFACE_CREATE_INFO_KHR;
			createInfo.pNext = nullptr;
			createInfo.flags = 0; // VkXcbSurfaceCreateFlagsKHR
			createInfo.connection = nullptr; // xcb_connection_t *
			createInfo.handle = glfwGetX11Window(m_handle); // xcb_window_t

			result = vkCreateXcbSurfaceKHR(m_instance.handle(), &createInfo, nullptr, &surfaceHandle);
	#elif IS_WINDOWS
			VkWin32SurfaceCreateInfoKHR createInfo{};
			createInfo.sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR;
			createInfo.pNext = nullptr;
			createInfo.hwnd = glfwGetWin32Window(m_handle);
			createInfo.hinstance = GetModuleHandle(nullptr);

			result = vkCreateWin32SurfaceKHR(m_instance.handle(), &createInfo, nullptr, &surfaceHandle);
	#elif IS_MACOS
			/* FIXME: Don't know what to write for now ... */
	#endif
		}
		else
#endif
		{
			result = glfwCreateWindowSurface(m_instance.handle(), m_handle.get(), nullptr, &surfaceHandle);
		}

		if ( result != VK_SUCCESS )
		{
			TraceFatal{ClassId} << "Unable to create a Window : " << Vulkan::vkResultToCString(result) << " !";

			return false;
		}

		m_surface = std::make_unique< Surface >(m_instance, surfaceHandle);

		if ( m_flags[ShowInformation] )
		{
			this->DEV_printWindowAttrib();
			this->DEV_printWindowGeometry();
		}

		/* Window starts non-visible. */
		glfwShowWindow(m_handle.get());

		return true;
	}

	bool
	Window::onTerminate () noexcept
	{
		m_surface.reset();

		/* Reset the window pointer.
		 * NOTE: Will remove automatically all callback */
		m_handle.reset();

		return true;
	}

	bool
	Window::resize (int32_t width, int32_t height) noexcept
	{
		if ( width <= 0 || height <= 0 )
		{
			TraceError{ClassId} << width << "x" << height << " is an invalid resolution.";

			return false;
		}

		if ( this->isFullscreenMode() )
		{
			/* Gets the closest acceptable width/height. */
			auto perfectFitFound = false;

			std::array< int32_t, 2 > closest{
				DefaultWidth,
				DefaultHeight
			};

			auto * monitor = glfwGetWindowMonitor(m_handle.get());

			const auto modes = Window::getMonitorModes(monitor);

			for ( const auto & mode : modes )
			{
				if ( width == mode.width && height == mode.height )
				{
					perfectFitFound = true;

					break;
				}

				/* Checks for below sizes. */
				if ( mode.width < width && mode.width > closest[0] && mode.height < height && mode.height > closest[1] )
				{
					closest[0] = mode.width;
					closest[1] = mode.height;
				}
			}

			if ( !perfectFitFound )
			{
				TraceWarning{ClassId} <<
					"Monitor cannot window the desired resolution " << width << "x" << height << ". "
					"Setting to " << closest[0] << "x" << closest[1]<< ".";

				width = closest[0];
				height = closest[1];
			}
		}

		glfwSetWindowSize(m_handle.get(), width, height);

		return true;
	}

	bool
	Window::setPosition (int32_t xPosition, int32_t yPosition) noexcept
	{
		glfwSetWindowPos(m_handle.get(),xPosition,yPosition);

		switch ( glfwGetError(nullptr) )
		{
			case GLFW_NOT_INITIALIZED :
			case GLFW_PLATFORM_ERROR :
				return false;

			default:
				this->notify(Centered);

				return true;
		}
	}

	std::array< int32_t, 2 >
	Window::getCenteredPosition (uint32_t monitorNumber) const noexcept
	{
		const auto monitors = Window::getMonitors();

		if ( monitors.empty() )
		{
			Tracer::error(ClassId, "There is no monitor on the system !");

			return {0, 0};
		}

		if ( monitorNumber >= monitors.size() )
		{
			TraceError{ClassId} <<
				"The monitor #" << monitorNumber << " doesn't exists. "
				"Using the first one.";

			monitorNumber = 0;
		}

		auto * monitor = monitors[monitorNumber];

		/* Get the monitor virtual position and dimensions and the window dimension. */
		const auto desktopPosition = Window::getDesktopPosition(monitor);
		const auto desktopSize = Window::getDesktopSize(monitor);
		const auto windowSize = this->getSize();

#ifdef DEBUG
		TraceDebug{ClassId} <<
			"Desktop position (X: " << desktopPosition[0] << ", Y: " << desktopPosition[1] << ")" "\n"
			"Desktop dimension (Width: " << desktopSize[0] << ", Height: " << desktopSize[1] << ")" "\n"
			"Window dimension (Width: " << windowSize[0] << ", Height: " << windowSize[1] << ")" "\n";
#endif

		/* Get the window position center on the selected monitor. */
		return {
			static_cast< int32_t >((desktopSize[0] - windowSize[0]) / 2) + desktopPosition[0],
			static_cast< int32_t >((desktopSize[1] - windowSize[1]) / 2) + desktopPosition[1]
		};
	}

	std::array< int32_t, 2 >
	Window::getCenteredPosition (const std::array< uint32_t , 2 > & windowSize, uint32_t monitorNumber) noexcept
	{
		const auto monitors = Window::getMonitors();

		if ( monitors.empty() )
		{
			Tracer::error(ClassId, "There is no monitor on the system !");

			return {0, 0};
		}

		if ( monitorNumber >= monitors.size() )
		{
			TraceError{ClassId} <<
				"The monitor #" << monitorNumber << " doesn't exists. "
				"Using the first one.";

			monitorNumber = 0;
		}

		auto * monitor = monitors[monitorNumber];

		/* Get the monitor virtual position and dimensions and the window dimension. */
		const auto desktopPosition = Window::getDesktopPosition(monitor);
		const auto desktopSize = Window::getDesktopSize(monitor);

		/* Get the window position center on the selected monitor. */
		return {
			static_cast< int32_t >((desktopSize[0] - windowSize[0]) / 2) + desktopPosition[0],
			static_cast< int32_t >((desktopSize[1] - windowSize[1]) / 2) + desktopPosition[1]
		};
	}

	bool
	Window::isVisibleOnDesktop () const noexcept
	{
		return glfwGetWindowAttrib(m_handle.get(), GLFW_VISIBLE) == GLFW_TRUE;
	}

	bool
	Window::isIconified () const noexcept
	{
		return glfwGetWindowAttrib(m_handle.get(), GLFW_ICONIFIED) == GLFW_TRUE;
	}

	void
	Window::iconify () const noexcept
	{
		if ( this->isIconified() )
		{
			return;
		}

		glfwIconifyWindow(m_handle.get());
	}

	void
	Window::getBackOnDesktop () const noexcept
	{
		if ( this->isVisibleOnDesktop() )
		{
			return;
		}

		glfwRestoreWindow(m_handle.get());
	}

	bool
	Window::isSizeMaximized () const noexcept
	{
		return glfwGetWindowAttrib(m_handle.get(), GLFW_MAXIMIZED) == GLFW_TRUE;
	}

	bool
	Window::isSizeReduced () const noexcept
	{
		return !this->isSizeMaximized();
	}

	void
	Window::maximizeSize () const noexcept
	{
		if ( this->isSizeMaximized() )
		{
			return;
		}

		glfwMaximizeWindow(m_handle.get());
	}

	void
	Window::restoreSize () const noexcept
	{
		if ( this->isSizeReduced() )
		{
			return;
		}

		glfwRestoreWindow(m_handle.get());
	}

	bool
	Window::isFocused () const noexcept
	{
		return glfwGetWindowAttrib(m_handle.get(), GLFW_FOCUSED) == GLFW_TRUE;
	}

	bool
	Window::isBlurred () const noexcept
	{
		return !this->isFocused();
	}

	void
	Window::focus () const noexcept
	{
		if ( this->isFocused() )
		{
			return;
		}

		glfwFocusWindow(m_handle.get());
	}

	bool
	Window::isVisible () const noexcept
	{
		return glfwGetWindowAttrib(m_handle.get(), GLFW_VISIBLE) == GLFW_TRUE;
	}

	bool
	Window::isHidden () const noexcept
	{
		return !this->isVisible();
	}

	void
	Window::hide () const noexcept
	{
		if ( this->isHidden() )
		{
			return;
		}

		glfwHideWindow(m_handle.get());
	}

	void
	Window::show () const noexcept
	{
		if ( this->isVisible() )
		{
			return;
		}

		glfwShowWindow(m_handle.get());
	}

	void
	Window::setGamma (float value) noexcept
	{
		auto * monitor = glfwGetWindowMonitor(m_handle.get());

		if ( monitor == nullptr )
		{
			Tracer::error(ClassId, "Window::setGamma(), There is no available monitor !");

			return;
		}

		glfwSetGamma(monitor, value);
	}

	void
	Window::setCustomGamma () noexcept
	{
		auto * monitor = glfwGetWindowMonitor(m_handle.get());

		if ( monitor == nullptr )
		{
			Tracer::error(ClassId, "Window::setCustomGamma(), There is no available monitor !");

			return;
		}

		const auto colorNumber = 256U;

		std::array< unsigned short, colorNumber > red{};
		std::array< unsigned short, colorNumber > green{};
		std::array< unsigned short, colorNumber > blue{};

		/* FIXME: Check what to pass as value. */
		for ( size_t i = 0;  i < colorNumber;  i++ )
		{
			// NOLINTBEGIN(cppcoreguidelines-pro-bounds-constant-array-index)
			red[i] = 0;
			green[i] = 0;
			blue[i] = 0;
			// NOLINTEND(cppcoreguidelines-pro-bounds-constant-array-index)
		}

		/* Creates a gamma ramp to pass to monitor. */
		GLFWgammaramp ramp;
		ramp.red = red.data();
		ramp.green = green.data();
		ramp.blue = blue.data();
		ramp.size = colorNumber;

		glfwSetGammaRamp(monitor, &ramp);
	}

	void
	Window::setFullscreenMode (bool state) noexcept
	{
		/* State still the same. */
		if ( this->isFullscreenMode() == state )
		{
			return;
		}

		const auto preferredMonitor = m_coreSettings.getAs< int >(PreferredMonitorKey, DefaultPreferredMonitor);

		if ( state )
		{
			auto * monitor = Window::getMonitor(preferredMonitor);

			const auto fullscreenWidth = m_coreSettings.getAs< int32_t >(FullscreenWidthKey, DefaultWidth);
			const auto fullscreenHeight = m_coreSettings.getAs< int32_t >(FullscreenHeightKey, DefaultHeight);
			const auto refreshRate = m_coreSettings.getAs< int32_t >(RefreshRateKey, DefaultRefreshRate);

			glfwSetWindowMonitor(
				m_handle.get(),
				monitor,
				0, 0,
				fullscreenWidth, fullscreenHeight,
				refreshRate
			);
		}
		else
		{
			const auto windowWidth = m_coreSettings.getAs< int32_t >(WindowWidthKey, DefaultWidth);
			const auto windowHeight = m_coreSettings.getAs< int32_t >(WindowHeightKey, DefaultHeight);
			const auto XPosition = m_coreSettings.getAs< int32_t >(WindowXPositionKey, DefaultWindowXPosition);
			const auto YPosition = m_coreSettings.getAs< int32_t >(WindowYPositionKey, DefaultWindowYPosition);

			glfwSetWindowMonitor(
				m_handle.get(),
				nullptr,
				XPosition, YPosition,
				windowWidth, windowHeight,
				GLFW_DONT_CARE
			);
		}
	}

	void
	Window::setVSyncState (bool state) noexcept
	{
		m_flags[VerticalSyncEnabled] = state;
	}

	bool
	Window::getVSyncState () const noexcept
	{
		return m_flags[VerticalSyncEnabled];
	}

	bool
	Window::isFullscreenMode () const noexcept
	{
		/* If there is no monitor attached to the handle,
		 * so this is not a fullscreen mode. */
		return glfwGetWindowMonitor(m_handle.get()) != nullptr;
	}

	std::array< int32_t, 2 >
	Window::getDesktopPosition (GLFWmonitor * monitor) noexcept
	{
		int xPosition = -1;
		int yPosition = -1;

		glfwGetMonitorPos(monitor, &xPosition, &yPosition);

		/* NOTE : We use the glfw handler to display errors. */
		switch ( glfwGetError(nullptr) )
		{
			case GLFW_NOT_INITIALIZED :
			case GLFW_PLATFORM_ERROR :
				return {0, 0};

			case GLFW_NO_ERROR :
			default:
				break;
		}

		return {
			static_cast< int32_t >(xPosition),
			static_cast< int32_t >(yPosition)
		};
	}

	std::array< int32_t, 2 >
	Window::getPosition () const noexcept
	{
		int xPosition = -1;
		int yPosition = -1;

		glfwGetWindowPos(m_handle.get(), &xPosition, &yPosition);

		/* NOTE : We use the glfw handler to display errors. */
		switch ( glfwGetError(nullptr) )
		{
			case GLFW_NOT_INITIALIZED :
			case GLFW_PLATFORM_ERROR :
				return {0, 0};

			case GLFW_NO_ERROR :
			default:
				break;
		}

		return {
			static_cast< int32_t >(xPosition),
			static_cast< int32_t >(yPosition)
		};
	}

	std::array< uint32_t, 2 >
	Window::getSize () const noexcept
	{
		int widthPts = -1;
		int heightPts = -1;

		glfwGetWindowSize(m_handle.get(), &widthPts, &heightPts);

		/* NOTE : We use the glfw handler to display errors. */
		switch ( glfwGetError(nullptr) )
		{
			case GLFW_NOT_INITIALIZED :
			case GLFW_PLATFORM_ERROR :
				return {DefaultWidth, DefaultHeight};

			case GLFW_NO_ERROR :
			default:
				break;
		}

		return {
			static_cast< uint32_t >(widthPts),
			static_cast< uint32_t >(heightPts)
		};
	}

	std::array< uint32_t, 4 >
	Window::getBorderSize () const noexcept
	{
		int leftPts = -1;
		int topPts = -1;
		int rightPts = -1;
		int bottomPts = -1;

		glfwGetWindowFrameSize(m_handle.get(), &leftPts, &topPts, &rightPts, &bottomPts);

		/* NOTE : We use the glfw handler to display errors. */
		switch ( glfwGetError(nullptr) )
		{
			case GLFW_NOT_INITIALIZED :
			case GLFW_PLATFORM_ERROR :
				return {0, 0, 0, 0};

			case GLFW_NO_ERROR :
			default:
				break;
		}

		return {
			static_cast< uint32_t >(leftPts),
			static_cast< uint32_t >(topPts),
			static_cast< uint32_t >(rightPts),
			static_cast< uint32_t >(bottomPts)
		};
	}

	std::array< uint32_t, 2 >
	Window::getDesktopSize (GLFWmonitor * monitor) noexcept
	{
		/* Get the proper monitor to query */
		if ( monitor == nullptr )
		{
			monitor = glfwGetPrimaryMonitor();

			if ( monitor == nullptr )
			{
				Tracer::error(ClassId, "Unable to query the primary monitor !");

				return {0, 0};
			}
		}

		const auto * mode = glfwGetVideoMode(monitor);

		/* NOTE : We use the glfw handler to display errors. */
		if ( mode == nullptr )
		{
			return {0, 0};
		}

		return {
			static_cast< uint32_t >(mode->width),
			static_cast< uint32_t >(mode->height)
		};
	}

	std::array< uint32_t, 2 >
	Window::getFramebufferSize () const noexcept
	{
		int widthPx = -1;
		int heightPx = -1;

		glfwGetFramebufferSize(m_handle.get(), &widthPx, &heightPx);

		/* NOTE : We use the glfw handler to display errors. */
		switch ( glfwGetError(nullptr) )
		{
			case GLFW_NOT_INITIALIZED :
			case GLFW_PLATFORM_ERROR :
				return {DefaultWidth, DefaultHeight};

			case GLFW_NO_ERROR :
			default:
				break;
		}

		return {
			static_cast< uint32_t >(widthPx),
			static_cast< uint32_t >(heightPx)
		};
	}

	std::array< float, 2 >
	Window::getContentScale () const noexcept
	{
		std::array< float, 2 > scale{0.0F, 0.0F};

		glfwGetWindowContentScale(m_handle.get(), scale.data(), scale.data()+1);

		/* NOTE : We use the glfw handler to display errors. */
		switch ( glfwGetError(nullptr) )
		{
			case GLFW_NOT_INITIALIZED :
			case GLFW_PLATFORM_ERROR :
				return {1.0F, 1.0F};

			case GLFW_NO_ERROR :
			default:
				break;
		}

		return scale;
	}

	float
	Window::aspectRatio () const noexcept
	{
		auto framebufferSize = this->getFramebufferSize();

		if ( framebufferSize[0] == 0 || framebufferSize[1] == 0 )
		{
			return 1.0F;
		}

		return static_cast< float >(framebufferSize[0]) / static_cast< float >(framebufferSize[1]);
	}

	const GLFWwindow *
	Window::handle () const noexcept
	{
		return m_handle.get();
	}

	GLFWwindow *
	Window::handle () noexcept
	{
		return m_handle.get();
	}

	const Surface *
	Window::surface () const noexcept
	{
		return m_surface.get();
	}

	Surface *
	Window::surface () noexcept
	{
		return m_surface.get();
	}

	bool
	Window::waitValidWindowSize () const noexcept
	{
		bool validSizeFound = false;

		while ( !validSizeFound )
		{
			const auto size = this->getFramebufferSize();

			if ( size[0] > 0 || size[1] > 0 )
			{
				validSizeFound = true;
			}

			glfwWaitEvents();
		}

		return true;
	}

	void
	Window::DEV_printWindowGeometry () const noexcept
	{
		{
			const auto position = this->getPosition();
			const auto size = this->getSize();

			TraceInfo{ClassId} <<
				"Window position and size (Screen coordinates) - "
				"X: " << position[0] <<
				"Y: " << position[1] <<
				"width: " << size[0] << "pts, "
				"height: " << size[1] << "pts.";
		}

		{
			const auto borderSize = this->getBorderSize();

			TraceInfo{ClassId} <<
				"Window frame borders (Screen coordinates) - "
				"left border:" << borderSize[0] << "pts, "
				"top border:" << borderSize[1] << "pts, "
				"right border: " << borderSize[2] << "pts, "
				"bottom border:" << borderSize[3] << "pts.";
		}

		{
			const auto scale = this->getContentScale();

			TraceInfo{ClassId} <<
				"Window content scale - "
				"X scale:" << scale[0] << ", "
				"Y scale:" << scale[1];
		}

		{
			const auto size = this->getFramebufferSize();

			TraceInfo{ClassId} <<
				"Framebuffer size (In pixels) - "
				"width: " << size[0] << "px, "
				"height: " << size[1] << "px.";
		}
	}

	void
	Window::DEV_printWindowAttrib () const noexcept
	{
		TraceInfo{ClassId} <<
			"Window related attributes:" "\n" <<
			/* indicates whether the specified window has input focus.
			* Initial input focus is controlled by the window hint with the same name. */
			" - GLFW_FOCUSED : " << glfwGetWindowAttrib(m_handle.get(), GLFW_FOCUSED) << "\n"
			/* indicates whether the specified window is iconified,
			* whether by the user or with glfwIconifyWindow. */
			" - GLFW_ICONIFIED : " << glfwGetWindowAttrib(m_handle.get(), GLFW_ICONIFIED) << "\n"
			/* indicates whether the specified window is visible.
			* Window visibility can be controlled with glfwShowWindow and glfwHideWindow
			* and initial visibility is controlled by the window hint with the same name. */
			" - GLFW_VISIBLE : " << glfwGetWindowAttrib(m_handle.get(), GLFW_VISIBLE) << "\n"
			/* indicates whether the specified window is resizable by the user.
			* This is set on creation with the window hint with the same name. */
			" - GLFW_RESIZABLE : " << glfwGetWindowAttrib(m_handle.get(), GLFW_RESIZABLE) << "\n"
			/* indicates whether the specified window has decorations such as a border,
			* a close widget, etc. This is set on creation with the handle
			* hint with the same name. */
			" - GLFW_DECORATED : " << glfwGetWindowAttrib(m_handle.get(), GLFW_DECORATED) << "\n"
			/* indicates whether the specified window is floating, also called topmost
			* or always-on-top. This is controlled by the window hint with the same name. */
			" - GLFW_FLOATING : " << glfwGetWindowAttrib(m_handle.get(), GLFW_FLOATING) << '\n';

		TraceInfo{ClassId} <<
						   "Context related attributes:\n" <<
			/* indicates the client API provided by the handle's context; either GLFW_OPENGL_API or GLFW_OPENGL_ES_API. */
			" - GLFW_CLIENT_API : " << glfwGetWindowAttrib(m_handle.get(), GLFW_CLIENT_API) << "\n"
			/* indicate the client API version of the handle's context. */
			" - GLFW_CONTEXT_VERSION_MAJOR : " << glfwGetWindowAttrib(m_handle.get(), GLFW_CONTEXT_VERSION_MAJOR) << "\n"
			" - GLFW_CONTEXT_VERSION_MINOR : " << glfwGetWindowAttrib(m_handle.get(), GLFW_CONTEXT_VERSION_MINOR) << "\n"
			" - GLFW_CONTEXT_REVISION : " << glfwGetWindowAttrib(m_handle.get(), GLFW_CONTEXT_REVISION) << "\n"
			/* is GLFW_TRUE if the handle's context is an OpenGL forward-compatible one, or GLFW_FALSE otherwise. */
			" - GLFW_OPENGL_FORWARD_COMPAT : " << glfwGetWindowAttrib(m_handle.get(), GLFW_OPENGL_FORWARD_COMPAT) << "\n"
			/* is GLFW_TRUE if the handle's context is an OpenGL debug context, or GLFW_FALSE otherwise. */
			" - GLFW_OPENGL_DEBUG_CONTEXT : " << glfwGetWindowAttrib(m_handle.get(), GLFW_OPENGL_DEBUG_CONTEXT) << "\n"
			/* indicates the OpenGL profile used by the context. This is GLFW_OPENGL_CORE_PROFILE or
			* GLFW_OPENGL_COMPAT_PROFILE if the context uses a known profile, or GLFW_OPENGL_ANY_PROFILE
			* if the OpenGL profile is unknown or the context is an OpenGL ES context. Note that the returned
			* profile may not match the profile bits of the context flags, as GLFW will try other means of
			* detecting the profile when no bits are set. */
			" - GLFW_OPENGL_PROFILE : " << glfwGetWindowAttrib(m_handle.get(), GLFW_OPENGL_PROFILE) << "\n"
			/* indicates the robustness strategy used by the context. This is GLFW_LOSE_CONTEXT_ON_RESET or
			* GLFW_NO_RESET_NOTIFICATION if the handle's context supports robustness,
			* or GLFW_NO_ROBUSTNESS otherwise. */
			" - GLFW_CONTEXT_ROBUSTNESS : " << glfwGetWindowAttrib(m_handle.get(), GLFW_CONTEXT_ROBUSTNESS) << '\n';
	}

	bool
	Window::create (int width, int height, int monitorNumber, bool fullscreenMode) noexcept
	{
		/* Parameters for creating the handle. */
		GLFWmonitor * monitor = nullptr;

		if ( fullscreenMode )
		{
			monitor = Window::getMonitor(monitorNumber);

			/* If one of the size is automatic,
			 * we use the current mode of the monitor */
			if ( width == Automatic || height == Automatic )
			{
				const auto * currentMode = glfwGetVideoMode(monitor);

				width = currentMode->width;
				height = currentMode->height;
			}
		}

		/* Checks sizes parameters. */
		if ( width <= 0 || height <= 0 )
		{
			TraceFatal{ClassId} << "Trying to create a window with invalid size (" << width << "x" << height << ") !";

			return false;
		}

		/* Creates the new handle. */
		m_handle = std::unique_ptr< GLFWwindow, std::function< void (GLFWwindow *) > >(
			glfwCreateWindow(width, height, m_title.c_str(), monitor, nullptr),
			glfwDestroyWindow
		);

		if ( m_handle == nullptr )
		{
			TraceFatal{ClassId} << "Unable to create a " << width << "x" << height << " window !";

			return false;
		}

		TraceSuccess{ClassId} << "A new " << width << "x" << height << " window created.";

		this->notify(Created, Vector< 2, size_t >{static_cast< size_t >(width), static_cast< size_t >(height)});

		/* Register all callbacks related to the window object. */
		glfwSetWindowUserPointer(m_handle.get(), this);
		glfwSetWindowPosCallback(m_handle.get(), Window::windowPositionCallback);
		glfwSetWindowSizeCallback(m_handle.get(), Window::windowSizeCallback);
		glfwSetWindowCloseCallback(m_handle.get(), Window::windowCloseCallback);
		glfwSetWindowRefreshCallback(m_handle.get(), Window::windowRefreshCallback);
		glfwSetWindowFocusCallback(m_handle.get(), Window::windowFocusCallback);
		glfwSetWindowIconifyCallback(m_handle.get(), Window::windowIconifyCallback);
		glfwSetWindowMaximizeCallback(m_handle.get(), Window::windowMaximizeCallback);
		glfwSetFramebufferSizeCallback(m_handle.get(), Window::framebufferSizeCallback);
		glfwSetWindowContentScaleCallback(m_handle.get(), Window::windowContentScaleCallback);

		return true;
	}

	bool
	Window::checkMonitors () const noexcept
	{
		const auto monitors = Window::getMonitors();

		if ( monitors.empty() )
		{
			Tracer::fatal(ClassId, "There is no monitor on the system !");

			return false;
		}

		if ( m_flags[ShowInformation] )
		{
			TraceInfo{ClassId} << monitors.size() << " monitor(s) available(s).";
		}

		for ( auto * monitor : monitors )
		{
			/* NOTE: Display monitors information. */
			if ( m_flags[ShowInformation] )
			{
				TraceInfo{ClassId} << glfwGetMonitorName(monitor) << " monitor added.";

				const auto modes = Window::getMonitorModes(monitor);

				TraceInfo{ClassId} << modes.size() << " modes available for this monitor.";

				for ( const auto & mode : modes )
				{
					const auto bits = mode.redBits + mode.greenBits + mode.blueBits;

					TraceInfo{ClassId} << mode.width << 'x' << mode.height << 'x' << bits << '@' << mode.refreshRate << "hz.";
				}
			}
		}

		glfwSetMonitorCallback(Window::monitorConfigurationChanged);

		return true;
	}

	std::vector< GLFWmonitor * >
	Window::getMonitors () noexcept
	{
		std::vector< GLFWmonitor * > list{};

		int count = 0;

		GLFWmonitor * * monitors = glfwGetMonitors(&count);

		if ( count > 0 && monitors != nullptr )
		{
			list.reserve(count);

			for ( int index = 0; index < count; index++ )
			{
				list.emplace_back(monitors[index]);
			}
		}

		return list;
	}

	GLFWmonitor *
	Window::getMonitor (uint32_t monitorNumber) noexcept
	{
		const auto monitors = Window::getMonitors();

		if ( monitors.empty() )
		{
			Tracer::error(ClassId, "The is no monitor on this system !");

			return nullptr;
		}

		if ( monitorNumber >= monitors.size() )
		{
			TraceError{ClassId} <<
				"The monitor #" << monitorNumber << " doesn't exists. "
				"Using the primary monitor.";

			return glfwGetPrimaryMonitor();
		}

		return monitors[monitorNumber];
	}

	std::vector< GLFWvidmode >
	Window::getMonitorModes (GLFWmonitor * monitor) noexcept
	{
		std::vector< GLFWvidmode > list{};

		int count = 0;

		const GLFWvidmode * modes = glfwGetVideoModes(monitor, &count);

		if ( count > 0 && modes != nullptr )
		{
			list.reserve(count);

			for ( int index = 0; index < count; index++ )
			{
				list.emplace_back(modes[index]);
			}
		}

		return list;
	}

	void
	Window::framebufferSizeCallback (GLFWwindow * window, int width, int height) noexcept
	{
		auto * _this = reinterpret_cast< Window * >(glfwGetWindowUserPointer(window));

		if ( _this == nullptr )
		{
			return;
		}

		_this->notify(OSNotifiesFramebufferResized, std::array< size_t, 2 >{static_cast< size_t >(width), static_cast< size_t >(height)});
	}

	void
	Window::windowSizeCallback (GLFWwindow * window, int width, int height) noexcept
	{
		auto * _this = reinterpret_cast< Window * >(glfwGetWindowUserPointer(window));

		if ( _this == nullptr )
		{
			return;
		}

		/* NOTE: Saves the window position. */
		if ( !_this->isFullscreenMode() )
		{
			_this->m_coreSettings.set(WindowWidthKey, width);
			_this->m_coreSettings.set(WindowHeightKey, height);
		}

		std::array< int, 6 > windowData{
			width,
			height,
			0, // Left
			0, // Top
			0, // Right
			0  // Bottom
		};

		glfwGetWindowFrameSize(window, &windowData[2], &windowData[3], &windowData[4], &windowData[5]);

		_this->notify(OSNotifiesWindowResized, windowData);
	}

	void
	Window::windowRefreshCallback (GLFWwindow * window) noexcept
	{
		auto * _this = reinterpret_cast< Window * >(glfwGetWindowUserPointer(window));

		if ( _this == nullptr )
		{
			return;
		}

		_this->notify(OSRequestsToRefreshContent);
	}

	void
	Window::monitorConfigurationChanged (GLFWmonitor * /*monitor*/, int event) noexcept
	{
		switch ( event )
		{
			case GLFW_CONNECTED :
				Tracer::info(ClassId, "New monitor add to the configuration !");
				break;

			case GLFW_DISCONNECTED :
				Tracer::info(ClassId, "New monitor removed to the configuration !");
				break;

			default:
				break;
		}
	}

	void
	Window::windowPositionCallback (GLFWwindow * window, int xPosition, int yPosition) noexcept
	{
		auto * _this = reinterpret_cast< Window * >(glfwGetWindowUserPointer(window));

		if ( _this == nullptr )
		{
			return;
		}

		/* NOTE: Saves the window position. */
		if ( !_this->isFullscreenMode() )
		{
			_this->m_coreSettings.set(WindowXPositionKey, xPosition);
			_this->m_coreSettings.set(WindowYPositionKey, yPosition);
		}
		
		_this->notify(OSNotifiesWindowMovedTo, std::array< int, 2 >{xPosition, yPosition});
	}

	void
	Window::windowCloseCallback (GLFWwindow * window) noexcept
	{
		auto * _this = reinterpret_cast< Window * >(glfwGetWindowUserPointer(window));

		if ( _this == nullptr )
		{
			return;
		}

		/* We clear the close bit.
		 * The engine window itself the running state. */
		glfwSetWindowShouldClose(window, GLFW_FALSE);

		/* Send the signal to the engine */
		_this->notify(OSRequestsToTerminate);
	}

	void
	Window::windowFocusCallback (GLFWwindow * window, int focused) noexcept
	{
		auto * _this = reinterpret_cast< Window * >(glfwGetWindowUserPointer(window));

		if ( _this == nullptr )
		{
			return;
		}

		_this->notify(focused == GLFW_TRUE ? OSNotifiesWindowGetFocus : OSNotifiesWindowLostFocus);
	}

	void
	Window::windowIconifyCallback (GLFWwindow * window, int hidden) noexcept
	{
		auto * _this = reinterpret_cast< Window * >(glfwGetWindowUserPointer(window));

		if ( _this == nullptr )
		{
			return;
		}

		_this->notify(hidden == GLFW_TRUE ? OSNotifiesWindowHidden : OSNotifiesWindowVisible);
	}

	void
	Window::windowMaximizeCallback (GLFWwindow * window, int maximized) noexcept
	{
		auto * _this = reinterpret_cast< Window * >(glfwGetWindowUserPointer(window));

		if ( _this == nullptr )
		{
			return;
		}

		_this->notify(maximized == GLFW_TRUE ? OSNotifiesWindowSizeMaximized : OSNotifiesWindowSizeMinimized);
	}

	void
	Window::windowContentScaleCallback (GLFWwindow * window, float xScale, float yScale) noexcept
	{
		auto * _this = reinterpret_cast< Window * >(glfwGetWindowUserPointer(window));

		if ( _this == nullptr )
		{
			return;
		}
		
		_this->notify(OSRequestsToRescaleContentBy, std::array< float, 2 >{xScale, yScale});
	}
	// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic, cppcoreguidelines-pro-type-reinterpret-cast, *-magic-numbers)
}
