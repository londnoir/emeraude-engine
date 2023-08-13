/*
 * Emeraude/Vulkan/DeviceRequirements.cpp
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

#include "DeviceRequirements.hpp"

/* C/C++ standard libraries */
#include <algorithm>

/* Local inclusions. */
#include "Math/Base.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	DeviceRequirements::DeviceRequirements (DeviceJobHint deviceJobHint) noexcept
		: m_deviceJobHint(deviceJobHint)
	{

	}

	DeviceJobHint
	DeviceRequirements::jobHint () const noexcept
	{
		return m_deviceJobHint;
	}

	VkPhysicalDeviceFeatures &
	DeviceRequirements::features () noexcept
	{
		return m_deviceFeatures;
	}

	const VkPhysicalDeviceFeatures &
	DeviceRequirements::features () const noexcept
	{
		return m_deviceFeatures;
	}

	void
	DeviceRequirements::requireGraphicsQueues (const std::vector< float > & queues, const std::vector< float > & transferQueues) noexcept
	{
		if ( queues.empty() )
		{
			Tracer::error(ClassId, "The queue vector is empty !");

			return;
		}

		std::transform(queues.cbegin(), queues.cend(), std::back_inserter(m_graphicsQueues), [] (float priority) {
			return Math::clampToUnit< float >(priority);
		});

		/* NOTE: Transfer on graphics will use a simple graphics queue. */
		if ( transferQueues.empty() )
		{
			return;
		}

		std::transform(transferQueues.cbegin(), transferQueues.cend(), std::back_inserter(m_graphicsTransferQueues), [] (float priority) {
			return Math::clampToUnit< float >(priority);
		});
	}

	void
	DeviceRequirements::requirePresentationQueues (const std::vector< float > & queues, VkSurfaceKHR surface, bool separate) noexcept
	{
		if ( queues.empty() )
		{
			Tracer::error(ClassId, "The queue vector is empty !");

			return;
		}

		if ( surface == VK_NULL_HANDLE )
		{
			Tracer::error(ClassId, "The surface handle must be valid to check the queue validity !");

			return;
		}

		std::transform(queues.cbegin(), queues.cend(), std::back_inserter(m_presentationQueues), [] (float priority) {
			return Math::clampToUnit< float >(priority);
		});

		m_surface = surface;
		m_presentationSeparated = separate;
	}

	void
	DeviceRequirements::requireComputeQueues (const std::vector< float > & queues, const std::vector< float > & transferQueues) noexcept
	{
		if ( queues.empty() )
		{
			Tracer::error(ClassId, "The queue vector is empty !");

			return;
		}

		std::transform(queues.cbegin(), queues.cend(), std::back_inserter(m_computeQueues), [] (float priority) {
			return Math::clampToUnit< float >(priority);
		});

		/* NOTE: Transfer on graphics will use a simple graphics queue. */
		if ( transferQueues.empty() )
		{
			return;
		}

		std::transform(transferQueues.cbegin(), transferQueues.cend(), std::back_inserter(m_computeTransferQueues), [] (float priority) {
			return Math::clampToUnit< float >(priority);
		});
	}

	void
	DeviceRequirements::requireTransferQueues (const std::vector< float > & queues) noexcept
	{
		if ( queues.empty() )
		{
			Tracer::error(ClassId, "The queue vector is empty !");

			return;
		}

		std::transform(queues.cbegin(), queues.cend(), std::back_inserter(m_transferQueues), [] (float priority) {
			return Math::clampToUnit< float >(priority);
		});
	}

	bool
	DeviceRequirements::needsGraphics () const noexcept
	{
		return !m_graphicsQueues.empty();
	}

	bool
	DeviceRequirements::needsCompute () const noexcept
	{
		return !m_computeQueues.empty();
	}

	bool
	DeviceRequirements::needsPresentation () const noexcept
	{
		return !m_presentationQueues.empty();
	}

	bool
	DeviceRequirements::tryPresentationSeparateFromGraphics () const noexcept
	{
		return m_presentationSeparated;
	}

	bool
	DeviceRequirements::needsTransfer () const noexcept
	{
		return !m_transferQueues.empty();
	}

	size_t
	DeviceRequirements::getRequiredQueueCount () const noexcept
	{
		size_t count = 0;

		count += m_graphicsQueues.size();
		count += m_graphicsTransferQueues.size();
		count += m_presentationQueues.size();
		count += m_computeQueues.size();
		count += m_computeTransferQueues.size();
		count += m_transferQueues.size();

		return count;
	}

	VkSurfaceKHR
	DeviceRequirements::surface () const noexcept
	{
		return m_surface;
	}

	const std::vector< float > &
	DeviceRequirements::graphicsQueuePriorities () const noexcept
	{
		return m_graphicsQueues;
	}

	const std::vector< float > &
	DeviceRequirements::graphicsTransferQueuePriorities () const noexcept
	{
		return m_graphicsTransferQueues;
	}

	const std::vector< float > &
	DeviceRequirements::presentationQueuePriorities () const noexcept
	{
		return m_presentationQueues;
	}

	const std::vector< float > &
	DeviceRequirements::computeQueuePriorities () const noexcept
	{
		return m_computeQueues;
	}

	const std::vector< float > &
	DeviceRequirements::computeTransferQueuePriorities () const noexcept
	{
		return m_presentationQueues;
	}

	const std::vector< float > &
	DeviceRequirements::transferQueuePriorities () const noexcept
	{
		return m_transferQueues;
	}

	bool
	DeviceRequirements::hasQueueDeclared () const noexcept
	{
		if ( !m_graphicsQueues.empty() )
		{
			return true;
		}

		if ( !m_computeQueues.empty() )
		{
			return true;
		}

		if ( !m_transferQueues.empty() )
		{
			return true;
		}

		return false;
	}

	std::ostream &
	operator<< (std::ostream & out, const DeviceRequirements & obj)
	{
		auto printInfo = [&out] (const char * title, const std::vector< float > & queues) {
			out << title << " : " << queues.size();

			if ( !queues.empty() )
			{
				out << " priorities : ";

				for ( auto priority : queues )
				{
					out << priority << ' ';
				}
			}

			out << '\n';
		};

		printInfo("Graphics queue requested", obj.m_graphicsQueues);

		printInfo("Graphics transfer queue requested", obj.m_graphicsTransferQueues);

		printInfo("Presentation queue requested", obj.m_presentationQueues);

		printInfo("Compute queue requested", obj.m_computeQueues);

		printInfo("Compute transfer queue requested", obj.m_computeTransferQueues);

		printInfo("Transfer queue requested", obj.m_transferQueues);

		return out;
	}

	std::string
	to_string (const DeviceRequirements & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
