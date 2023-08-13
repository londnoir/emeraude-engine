/*
 * Emeraude/Vulkan/Buffer.cpp
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

#include "Buffer.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

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
		m_deviceMemory->setIdentifier(this->identifier() + "-Main-DeviceMemory");

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

		TraceSuccess{ClassId} <<
			"The buffer " << m_handle << " (" << this->identifier() << ") is successfully created !" "\n"
			"Device memory size : " << m_deviceMemory->bytes() << " bytes" "\n"
			"Create info size : " << this->bytes() << " bytes";

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
			this->device()->waitIdle();

			vkDestroyBuffer(
				this->device()->handle(),
				m_handle,
				VK_NULL_HANDLE
			);

			TraceSuccess{ClassId} << "The buffer " << m_handle << " is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	bool
	Buffer::recreate (VkDeviceSize size) noexcept
	{
		m_createInfo.size = size;

		return this->AbstractDeviceDependentObject::recreate();
	}

	VkBuffer
	Buffer::handle () const noexcept
	{
		return m_handle;
	}

	VkBufferCreateInfo
	Buffer::createInfo () const noexcept
	{
		return m_createInfo;
	}

	VkBufferCreateFlags
	Buffer::createFlags () const noexcept
	{
		return m_createInfo.flags;
	}

	VkDeviceSize
	Buffer::bytes () const noexcept
	{
		return m_createInfo.size;
	}

	VkBufferUsageFlags
	Buffer::usageFlags () const noexcept
	{
		return m_createInfo.usage;
	}

	VkMemoryPropertyFlags
	Buffer::memoryPropertyFlags () const noexcept
	{
		return m_memoryPropertyFlag;
	}

	const DeviceMemory *
	Buffer::deviceMemory () const noexcept
	{
		return m_deviceMemory.get();
	}

	VkDescriptorBufferInfo
	Buffer::getDescriptorInfo () const noexcept
	{
		VkDescriptorBufferInfo descriptorInfo{};
		descriptorInfo.buffer = m_handle;
		descriptorInfo.offset = 0;
		descriptorInfo.range = m_createInfo.size;

		return descriptorInfo;
	}
}
