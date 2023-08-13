/*
 * Emeraude/Vulkan/Sampler.cpp
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

#include "Sampler.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	Sampler::Sampler (const std::shared_ptr< Device > & device, VkSamplerCreateFlags createFlags) noexcept
		: AbstractDeviceDependentObject(device)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
		m_createInfo.magFilter = VK_FILTER_NEAREST;
		m_createInfo.minFilter = VK_FILTER_NEAREST;
		m_createInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_NEAREST;
		m_createInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		m_createInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		m_createInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		m_createInfo.mipLodBias = 0.0F;
		m_createInfo.anisotropyEnable = VK_FALSE;
		m_createInfo.maxAnisotropy = 0.0F;
		m_createInfo.compareEnable = VK_FALSE;
		m_createInfo.compareOp = VK_COMPARE_OP_ALWAYS;
		m_createInfo.minLod = 0.0F;
		m_createInfo.maxLod = 0.0F;
		m_createInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
		m_createInfo.unnormalizedCoordinates = VK_FALSE;
	}

	Sampler::Sampler (const std::shared_ptr< Device > & device, const VkSamplerCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo)
	{

	}

	Sampler::~Sampler ()
	{
		this->destroyFromHardware();
	}

	bool
	Sampler::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this sampler !");

			return false;
		}

		const auto result = vkCreateSampler(this->device()->handle(), &m_createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			Tracer::error(ClassId, Blob() << "Unable to create a sampler : " << vkResultToCString(result) << " !");

			return false;
		}

		this->setCreated();

		Tracer::success(ClassId, Blob() << "The sampler " << m_handle << " (" << this->identifier() << ") is successfully created !");

		return true;
	}

	bool
	Sampler::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the sampler " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		if (  m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroySampler(this->device()->handle(), m_handle, nullptr);

			TraceSuccess{ClassId} << "The sampler " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkSampler
	Sampler::handle () const noexcept
	{
		return m_handle;
	}

	VkSamplerCreateInfo
	Sampler::createInfo () const noexcept
	{
		return m_createInfo;
	}
}
