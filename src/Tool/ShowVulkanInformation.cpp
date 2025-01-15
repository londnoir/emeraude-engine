/*
 * src/Tool/ShowVulkanInformation.cpp
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

#include "ShowVulkanInformation.hpp"

/* Local inclusions. */
#include "Vulkan/Instance.hpp"
#include "Vulkan/PhysicalDevice.hpp"
#include "Tracer.hpp"

namespace Emeraude::Tool
{
	using namespace Libraries;

	ShowVulkanInformation::ShowVulkanInformation (const Arguments & arguments, const Vulkan::Instance & vulkanInstance) noexcept
		: m_arguments(arguments), m_vulkanInstance(vulkanInstance)
	{

	}

	bool
	ShowVulkanInformation::execute () noexcept
	{
		const auto & physicalDevices = m_vulkanInstance.physicalDevices();

		TraceInfo info{ClassId};

		info << "Vulkan information :" "\n";

		if ( !physicalDevices.empty() )
		{
			info << "\n" << physicalDevices.size() << " physical device(s) available for Vulkan :\n\n";

			for ( const auto & physicalDevice : physicalDevices )
			{
				info << physicalDevice->getPhysicalDeviceInformation() << "\n";
			}
		}
		else
		{
			info << "\n" << "No physical device available !" << "\n";
		}

		Tracer::instance()->enableTracing(false);

		return true;
	}
}
