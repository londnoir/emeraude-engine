/*
 * src/Vulkan/Buffer.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "Buffer.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "DeviceMemory.hpp"
#include "Utility.hpp"
#include "Tracer.hpp"

namespace EmEn::Vulkan
{
	using namespace EmEn::Libs;

	Buffer::Buffer (const std::shared_ptr< Device > & device, VkBufferCreateFlags createFlags, VkDeviceSize size, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlag) noexcept
		: AbstractDeviceDependentObject(device), m_memoryPropertyFlag(memoryPropertyFlag)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
		m_createInfo.size = size;
		m_createInfo.usage = usageFlags;
		m_createInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		m_createInfo.queueFamilyIndexCount = 0;
		m_createInfo.pQueueFamilyIndices = nullptr;
	}

	Buffer::Buffer (const std::shared_ptr< Device > & device, const VkBufferCreateInfo & createInfo, VkMemoryPropertyFlags memoryPropertyFlag) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo), m_memoryPropertyFlag(memoryPropertyFlag)
	{

	}

	Buffer::~Buffer ()
	{
		this->destroyFromHardware();
	}

	bool
	Buffer::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this buffer !");

			return false;
		}

		auto result = vkCreateBuffer(
			this->device()->handle(),
			&m_createInfo,
			VK_NULL_HANDLE,
			&m_handle
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create a buffer : " << vkResultToCString(result) << " !";

			return false;
		}

		/* Allocate memory for the new image. */
		VkMemoryRequirements memoryRequirement{};

		vkGetBufferMemoryRequirements(
			this->device()->handle(),
			m_handle,
			&memoryRequirement
		);

		m_deviceMemory = std::make_unique< DeviceMemory >(this->device(), memoryRequirement, m_memoryPropertyFlag);
		m_deviceMemory->setIdentifier(ClassId, this->identifier(), "DeviceMemory");

		if ( !m_deviceMemory->createOnHardware() )
		{
			TraceError{ClassId} << "Unable to create a device memory for the buffer " << m_handle << " !";

			this->destroyFromHardware();

			return false;
		}

		/* Bind the buffer to the device memory */
		result = vkBindBufferMemory(
			this->device()->handle(),
			m_handle,
			m_deviceMemory->handle(),
			0// offset
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} <<
				"Unable to bind the buffer " << m_handle << " to the device memory " << m_deviceMemory->handle() <<
				" : " << vkResultToCString(result) << " !";

			this->destroyFromHardware();

			return false;
		}

		this->setCreated();

		return true;
	}

	bool
	Buffer::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to destroy this buffer !");

			return false;
		}

		if ( m_deviceMemory != nullptr )
		{
			m_deviceMemory->destroyFromHardware();
			m_deviceMemory.reset();
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle("Destroying a buffer");

			vkDestroyBuffer(
				this->device()->handle(),
				m_handle,
				VK_NULL_HANDLE
			);

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkDescriptorBufferInfo
	Buffer::getDescriptorInfo (uint32_t /*offset*/, uint32_t range) const noexcept
	{
		/* FIXME: Setting the offset to break some scenes ! */

		VkDescriptorBufferInfo descriptorInfo{};
		descriptorInfo.buffer = m_handle;
		descriptorInfo.offset = 0;
		descriptorInfo.range = range;

		return descriptorInfo;
	}
}
