/*
 * Emeraude/PlatformManager.cpp
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

#include "PlatformManager.hpp"

/* Local inclusions */
#include "Arguments.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/glfw.hpp"

namespace Emeraude
{
	using namespace Libraries;

	const size_t PlatformManager::ClassUID{Observable::getClassUID()};

	PlatformManager::PlatformManager (const Arguments & argument, Settings & coreSettings) noexcept
		: ServiceInterface(ClassId), m_arguments(argument), m_coreSettings(coreSettings)
	{

	}

	bool
	PlatformManager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	PlatformManager::usable () const noexcept
	{
		return m_usable;
	}

	bool
	PlatformManager::onInitialize () noexcept
	{
		glfwSetErrorCallback(Tracer::traceGLFW);

		if ( glfwInit() == GL_TRUE )
		{
			Tracer::success(ClassId, "GLFW initialized.");

			/* Print GLFW3 version. */
			int glfwMajor = 0;
			int glfwMin = 0;
			int glfwRev = 0;

			glfwGetVersion(&glfwMajor, &glfwMin, &glfwRev);

			Tracer::info(ClassId, Blob() << "GLFW version : " << glfwMajor << '.' << glfwMin << '.' << glfwRev);
		}
		else
		{
			Tracer::fatal(ClassId, "Unable to initialize GLFW. Aborting ...");

			return false;
		}

		/* Checks vulkan support */
		if ( glfwVulkanSupported() == GLFW_FALSE )
		{
			Tracer::fatal(ClassId, "Vulkan API is not supported by this system ! Aborting ...");

			return false;
		}

		m_usable = true;

		return true;
	}

	bool
	PlatformManager::onTerminate () noexcept
	{
		glfwTerminate();

		/* Removing callback. */
		glfwSetErrorCallback(nullptr);

		return true;
	}
}
