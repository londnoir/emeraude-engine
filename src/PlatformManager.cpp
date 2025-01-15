/*
 * src/PlatformManager.cpp
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

#include "PlatformManager.hpp"

/* STL inclusions. */
#include <cstddef>

/* Third-party inclusions. */
#include "GLFW/glfw3.h"

/* Local inclusions. */
#include "Arguments.hpp"
#include "ServiceInterface.hpp"
#include "PrimaryServices.hpp"
#include "SettingKeys.hpp"
#include "Tracer.hpp"

namespace Emeraude
{
	using namespace Libraries;

	const size_t PlatformManager::ClassUID{getClassUID(ClassId)};

	PlatformManager::PlatformManager (PrimaryServices & primaryServices) noexcept
		: ServiceInterface(ClassId), m_primaryServices(primaryServices)
	{

	}

	size_t
	PlatformManager::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	PlatformManager::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	bool
	PlatformManager::usable () const noexcept
	{
		return m_flags[ServiceInitialized];
	}

	bool
	PlatformManager::onInitialize () noexcept
	{
		m_flags[ShowInformation] = m_primaryServices.settings().get< bool >(GLFWShowInformationKey, BOOLEAN_FOLLOWING_DEBUG);

		glfwSetErrorCallback(Tracer::traceGLFW);

		/* GLFW_JOYSTICK_HAT_BUTTONS specifies whether to also expose joystick hats as buttons,
		 * for compatibility with earlier versions of GLFW that did not have glfwGetJoystickHats.
		 * Possible values are GLFW_TRUE and GLFW_FALSE. */
		glfwInitHint(GLFW_JOYSTICK_HAT_BUTTONS, GLFW_TRUE);

#if IS_MACOS
		/* GLFW_COCOA_CHDIR_RESOURCES specifies whether to set the current directory to the application
		 * to the Contents/Resources subdirectory of the application's bundle, if present. */
		glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_TRUE);
		/* GLFW_COCOA_MENUBAR specifies whether to create a basic menu bar, either from a nib or manually,
		 * when the first window is created, which is when AppKit is initialized. */
		glfwInitHint(GLFW_COCOA_MENUBAR, GLFW_TRUE);

		glfwInitVulkanLoader(nullptr);
#endif

		if ( glfwInit() == GLFW_FALSE )
		{
			Tracer::fatal(ClassId, "Unable to initialize GLFW. Aborting ...");

			return false;
		}

		/* Checks for Vulkan API support. */
		if ( glfwVulkanSupported() == GLFW_FALSE )
		{
			Tracer::fatal(ClassId, "Vulkan API is not supported by this system ! Aborting ...");

			return false;
		}

		if ( m_flags[ShowInformation] )
		{
			int glfwMajor = 0;
			int glfwMin = 0;
			int glfwRev = 0;

			glfwGetVersion(&glfwMajor, &glfwMin, &glfwRev);

			TraceSuccess{ClassId} << "GLFW version : " << glfwMajor << '.' << glfwMin << '.' << glfwRev << " initialized !";
		}

		m_flags[ServiceInitialized] = true;

		return true;
	}

	bool
	PlatformManager::onTerminate () noexcept
	{
		m_flags[ServiceInitialized] = false;

		glfwTerminate();

		/* Removing callback. */
		glfwSetErrorCallback(nullptr);

		return true;
	}
}
