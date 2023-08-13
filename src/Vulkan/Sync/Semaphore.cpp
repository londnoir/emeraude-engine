/*
 * Emeraude/Vulkan/Sync/Semaphore.cpp
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

#include "Semaphore.hpp"

/* Local inclusions. */
#include "../Device.hpp"
#include "../Utility.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan::Sync
{
	Semaphore::Semaphore (const std::shared_ptr< Device > & device, VkSemaphoreCreateFlags createFlags) noexcept
		: AbstractDeviceDependentObject(device)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
	}

	Semaphore::Semaphore (const std::shared_ptr< Device > & device, const VkSemaphoreCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo)
	{

	}

	Semaphore::~Semaphore ()
	{
		this->destroyFromHardware();
	}

	bool
	Semaphore::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this semaphore !");

			return false;
		}

		const auto result = vkCreateSemaphore(this->device()->handle(), &m_createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create a semaphore : " << vkResultToCString(result) << " !";

			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The semaphore " << m_handle << " (" << this->identifier() << ") is successfully created !";

		return true;
	}

	bool
	Semaphore::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the semaphore " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		if (  m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroySemaphore(this->device()->handle(), m_handle, nullptr);

			TraceSuccess{ClassId} << "The semaphore " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkSemaphore
	Semaphore::handle () const noexcept
	{
		return m_handle;
	}

	VkSemaphoreCreateInfo
	Semaphore::createInfo () const noexcept
	{
		return m_createInfo;
	}
}
