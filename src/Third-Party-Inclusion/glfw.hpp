/*
 * Emeraude/Third-Party-Inclusion/glfw.hpp
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

#include "emeraude_config.hpp"

COMPILATION_SILENCE_WARNINGS

//#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

/* NOTE: Enable the exposition of native code from GLFW library. */
#ifdef ENABLE_GLFW_NATIVE_CODE_EXPOSITION
	#include "platform.hpp"

	#if IS_LINUX
		#define GLFW_EXPOSE_NATIVE_X11
		//#define GLFW_EXPOSE_NATIVE_GLX
		//#define GLFW_EXPOSE_NATIVE_WAYLAND

		#define VK_USE_PLATFORM_XCB_KHR
	#elif IS_WINDOWS
		#define GLFW_EXPOSE_NATIVE_WIN32
		#define GLFW_EXPOSE_NATIVE_WGL

		#define VK_USE_PLATFORM_WIN32_KHR
	#elif IS_MACOS
		// FIXME: Unsure if it works !
		#define GLFW_EXPOSE_NATIVE_COCOA
		#define GLFW_EXPOSE_NATIVE_NSGL

		#define VK_USE_PLATFORM_XLIB_KHR
	#endif

	#include <GLFW/glfw3native.h>
#endif

COMPILATION_RESTORE_WARNINGS
