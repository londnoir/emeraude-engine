/*
 * Emeraude/Vulkan/CommandPool.cpp
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

#include "CommandPool.hpp"

/* Local inclusions */
#include "Device.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	CommandPool::CommandPool (const std::shared_ptr< Device > & device, uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags) noexcept
		: AbstractDeviceDependentObject(device)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
		m_createInfo.queueFamilyIndex = queueFamilyIndex;
	}

	CommandPool::CommandPool (const std::shared_ptr< Device > & device, const VkCommandPoolCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo)
	{

	}

	CommandPool::~CommandPool ()
	{
		this->destroyFromHardware();
	}

	bool
	CommandPool::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this command pool !");

			return false;
		}

		const auto result = vkCreateCommandPool(this->device()->handle(), &m_createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			Tracer::error(ClassId, Blob() << "Unable to create command pool : " << vkResultToCString(result) << " !");

			return false;
		}

		this->setCreated();

		Tracer::success(ClassId, Blob() << "The command pool " << m_handle << " (" << this->identifier() << ") is successfully created !");

		return true;
	}

	bool
	CommandPool::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to destroy this command pool !");

			return false;
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroyCommandPool(this->device()->handle(), m_handle, nullptr);

			Tracer::success(ClassId, Blob() << "The command pool " << m_handle << " is gracefully destroyed !");

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkCommandPool
	CommandPool::handle () const noexcept
	{
		return m_handle;
	}

	VkCommandPoolCreateInfo
	CommandPool::createInfo () const noexcept
	{
		return m_createInfo;
	}

	uint32_t
	CommandPool::queueFamilyIndex () const noexcept
	{
		return m_createInfo.queueFamilyIndex;
	}

	VkCommandBuffer
	CommandPool::allocateCommandBuffer (bool primaryLevel) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_allocationMutex};

		VkCommandBufferAllocateInfo allocateInfo{};
		allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocateInfo.pNext = nullptr;
		allocateInfo.commandPool = m_handle;
		allocateInfo.level = primaryLevel ? VK_COMMAND_BUFFER_LEVEL_PRIMARY : VK_COMMAND_BUFFER_LEVEL_SECONDARY;
		allocateInfo.commandBufferCount = 1;

		VkCommandBuffer commandBufferHandle = VK_NULL_HANDLE;

		const auto result = vkAllocateCommandBuffers(
			this->device()->handle(),
			&allocateInfo,
			&commandBufferHandle
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to allocate a command buffer : " << vkResultToCString(result) << " !";

			return VK_NULL_HANDLE;
		}

		return commandBufferHandle;
	}

	void
	CommandPool::freeCommandBuffer (VkCommandBuffer commandBufferHandle) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_allocationMutex};

		this->device()->waitIdle();

		vkFreeCommandBuffers(
			this->device()->handle(),
			m_handle,
			1, &commandBufferHandle
		);
	}
}
