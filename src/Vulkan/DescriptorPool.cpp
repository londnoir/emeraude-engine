/*
 * Emeraude/Vulkan/DescriptorPool.cpp
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

#include "DescriptorPool.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	DescriptorPool::DescriptorPool (const std::shared_ptr< Device > & device, const std::vector< VkDescriptorPoolSize > & descriptorPoolSizes, uint32_t maxSets, VkDescriptorPoolCreateFlags createFlags) noexcept
		: AbstractDeviceDependentObject(device), m_descriptorPoolSizes(descriptorPoolSizes)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
		m_createInfo.maxSets = maxSets;
		m_createInfo.poolSizeCount = m_descriptorPoolSizes.size();
		m_createInfo.pPoolSizes = m_descriptorPoolSizes.data();
	}

	DescriptorPool::DescriptorPool (const std::shared_ptr< Device > & device, const VkDescriptorPoolCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo)
	{

	}

	DescriptorPool::~DescriptorPool ()
	{
		this->destroyFromHardware();
	}

	bool
	DescriptorPool::createOnHardware() noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this descriptor pool !");

			return false;
		}

		/* Refresh pool sizes. */
		m_createInfo.poolSizeCount = m_descriptorPoolSizes.size();
		m_createInfo.pPoolSizes = m_descriptorPoolSizes.data();

		const auto result = vkCreateDescriptorPool(
			this->device()->handle(),
			&m_createInfo,
			VK_NULL_HANDLE,
			&m_handle
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create descriptor pool : " << vkResultToCString(result) << " !";

			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The descriptor pool " << m_handle << " (" << this->identifier() << ") is successfully created !";

		return true;
	}

	bool
	DescriptorPool::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to destroy this descriptor pool !");

			return false;
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroyDescriptorPool(
				this->device()->handle(),
				m_handle,
				VK_NULL_HANDLE
			);

			TraceSuccess{ClassId} << "The descriptor pool " << m_handle << " is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkDescriptorPool
	DescriptorPool::handle () const noexcept
	{
		return m_handle;
	}

	VkDescriptorPoolCreateInfo
	DescriptorPool::createInfo () const noexcept
	{
		return m_createInfo;
	}

	const std::vector< VkDescriptorPoolSize > &
	DescriptorPool::descriptorPoolSizes () const noexcept
	{
		return m_descriptorPoolSizes;
	}

	uint32_t
	DescriptorPool::maxSets () const noexcept
	{
		return m_createInfo.maxSets;
	}

	VkDescriptorSet
	DescriptorPool::allocateDescriptorSet (const DescriptorSetLayout & descriptorSetLayout) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_allocationMutex};

		auto * descriptorSetLayoutHandle = descriptorSetLayout.handle();

		VkDescriptorSetAllocateInfo allocateInfo{};
		allocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		allocateInfo.pNext = nullptr;
		allocateInfo.descriptorPool = m_handle;
		allocateInfo.descriptorSetCount = 1;
		allocateInfo.pSetLayouts = &descriptorSetLayoutHandle;

		VkDescriptorSet descriptorSetHandle = VK_NULL_HANDLE;

		const auto result = vkAllocateDescriptorSets(
			this->device()->handle(),
			&allocateInfo,
			&descriptorSetHandle
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to allocate a descriptor set : " << vkResultToCString(result) << " !";

			return VK_NULL_HANDLE;
		}

		return descriptorSetHandle;
	}

	bool
	DescriptorPool::freeDescriptorSet (VkDescriptorSet descriptorSetHandle) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_allocationMutex};

		this->device()->waitIdle();

		const auto result = vkFreeDescriptorSets(
			this->device()->handle(),
			m_handle,
			1, &descriptorSetHandle
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to allocate a descriptor set : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}
}
