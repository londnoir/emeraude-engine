/*
 * Emeraude/Vulkan/QueueFamilySQ.cpp
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

#include "QueueFamilySQ.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	QueueFamilySQ::QueueFamilySQ (uint32_t index) noexcept
		: m_queueFamilyIndex(index)
	{

	}

	uint32_t
	QueueFamilySQ::index () const noexcept
	{
		return m_queueFamilyIndex;
	}

	size_t
	QueueFamilySQ::maxQueueCount () const noexcept
	{
		return 1;
	}

	bool
	QueueFamilySQ::hasSingleQueue () const noexcept
	{
		return true;
	}

	bool
	QueueFamilySQ::declareQueueStructure (const std::vector< std::pair< QueueJob, float > > & /*structure*/) noexcept
	{
		Tracer::error(ClassId, "This is a single queue family !");

		return false;
	}

	VkDeviceQueueCreateInfo
	QueueFamilySQ::getCreateInfo (VkDeviceQueueCreateFlags createFlag) const noexcept
	{
		VkDeviceQueueCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		createInfo.pNext = nullptr;
		createInfo.flags = createFlag;
		createInfo.queueFamilyIndex = m_queueFamilyIndex;
		createInfo.queueCount = 1;
		createInfo.pQueuePriorities = &m_queuePriority;

		return createInfo;
	}

	bool
	QueueFamilySQ::retrieveQueuesFromDevice (const std::shared_ptr< Device > & device) noexcept
	{
		VkQueue queueHandle{};

		vkGetDeviceQueue(device->handle(), m_queueFamilyIndex, 0, &queueHandle);

		if ( queueHandle == VK_NULL_HANDLE )
		{
			TraceError{ClassId} << "Unable to retrieve the queue (family #" << m_queueFamilyIndex << ") from the device  !";

			return false;
		}

		m_queue = std::make_unique< Queue >(queueHandle, m_queueFamilyIndex);
		m_queue->setIdentifier((std::stringstream{} << "Device-" << m_queueFamilyIndex << ".0-Queue").str());

		if ( !m_queue->createTransferFence(device) )
		{
			TraceError{ClassId} << "Unable to create the transfer fence for the queue (family #" << m_queueFamilyIndex << ") @" << queueHandle << " !";

			return false;
		}

		return true;
	}

	Queue *
	QueueFamilySQ::queue (QueueJob /*job*/, QueuePriority /*priority*/) noexcept
	{
		/* NOTE: There is no use for job or priority here. */
		return m_queue.get();
	}
}
