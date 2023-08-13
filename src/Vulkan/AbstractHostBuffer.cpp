/*
 * Emeraude/Vulkan/AbstractHostBuffer.cpp
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

#include "AbstractHostBuffer.hpp"

/* C/C++ standard libraries. */
#include <cstring>

/* Local inclusions. */
#include "Device.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	AbstractHostBuffer::AbstractHostBuffer (const std::shared_ptr< Device > & device, VkBufferCreateFlags createFlags, VkDeviceSize deviceSize, VkBufferUsageFlags bufferUsageFlags) noexcept
		: Buffer(device, createFlags, deviceSize, bufferUsageFlags, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	{

	}

	bool
	AbstractHostBuffer::writeData (const MemoryRegion & memoryRegion) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_memoryAccess};

		TraceDebug{ClassId} << memoryRegion;

		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The buffer is not created ! Use one of the Buffer::create() methods first.");

			return false;
		}

		/* Lock the buffer for access. */
		auto * pointer = this->deviceMemory()->mapMemory(memoryRegion.offset(), memoryRegion.bytes());

		if ( pointer == nullptr )
		{
			TraceError{ClassId} << "Unable to map the buffer from offset " << memoryRegion.offset() << " for " << memoryRegion.bytes() << " bytes.";

			return false;
		}

		/* Raw data copy... */
		std::memcpy(pointer, memoryRegion.source(), memoryRegion.bytes());

		/* Unlock the buffer. */
		this->deviceMemory()->unmapMemory();

		return true;
	}

	bool
	AbstractHostBuffer::writeData (const std::vector< MemoryRegion > & memoryRegions) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_memoryAccess};

		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The buffer is not created ! Use one of the Buffer::create() methods first.");

			return false;
		}

		if ( memoryRegions.empty() )
		{
			Tracer::error(ClassId, "No memory region to write !");

			return false;
		}

		/* TODO: Check for performance improvement on mapping the buffer once with larger boundaries. */

		/* Raw data copy... */
		for ( const auto & memoryRegion : memoryRegions )
		{
			/* Lock the buffer for access. */
			auto * pointer = this->deviceMemory()->mapMemory(memoryRegion.offset(), this->bytes());

			if ( pointer == nullptr )
			{
				TraceError{ClassId} << "Unable to map the buffer from offset " << memoryRegion.offset() << " for " << this->bytes() << " bytes.";

				return false;
			}

			/* Raw data copy... */
			std::memcpy(pointer, memoryRegion.source(), memoryRegion.bytes());

			/* Unlock the buffer. */
			this->deviceMemory()->unmapMemory();
		}

		return true;
	}
}
