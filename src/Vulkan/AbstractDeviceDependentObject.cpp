/*
 * Emeraude/Vulkan/AbstractDeviceDependentObject.cpp
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

#include "AbstractDeviceDependentObject.hpp"

/* Local inclusions */
#include "Device.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	AbstractDeviceDependentObject::AbstractDeviceDependentObject (const std::shared_ptr< Device > & device) noexcept
		: m_device(device)
	{
		if ( m_device == nullptr )
		{
			Tracer::error("VulkanDeviceDependentObject", "Device is null !");
		}

		if ( !m_device->isCreated() )
		{
			Tracer::warning("VulkanDeviceDependentObject", "Device is not yet usable !");
		}
	}

	std::shared_ptr< Device >
	AbstractDeviceDependentObject::device () const noexcept
	{
		return m_device;
	}

	bool
	AbstractDeviceDependentObject::hasDevice () const noexcept
	{
		return m_device != nullptr && m_device->handle() != VK_NULL_HANDLE;
	}

	bool
	AbstractDeviceDependentObject::recreate () noexcept
	{
		if ( !this->destroyFromHardware() )
		{
			return false;
		}

		return this->createOnHardware();
	}
}
