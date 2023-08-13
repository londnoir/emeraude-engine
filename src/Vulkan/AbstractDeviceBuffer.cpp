/*
 * Emeraude/Vulkan/AbstractDeviceBuffer.cpp
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

#include "AbstractDeviceBuffer.hpp"

/* Local inclusions */
#include "StagingBuffer.hpp"
#include "Tracer.hpp"
#include "TransferManager.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	AbstractDeviceBuffer::AbstractDeviceBuffer (const std::shared_ptr< Device > & device, VkBufferCreateFlags createFlags, VkDeviceSize deviceSize, VkBufferUsageFlags bufferUsageFlags) noexcept
		: Buffer(device, createFlags, deviceSize, bufferUsageFlags, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	{

	}

	bool
	AbstractDeviceBuffer::writeData (TransferManager & transferManager, const MemoryRegion & memoryRegion) noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The buffer is not created ! Use one of the Buffer::create() methods first.");

			return false;
		}

		/* Get an available staging buffer to prepare the transfer */
		auto stagingBuffer = transferManager.getStagingBuffer(memoryRegion.bytes());

		if ( stagingBuffer == nullptr )
		{
			return false;
		}

		/* NOTE: Already locked, but gives the ability to unlock the staging buffer automatically at function exit. */
		const std::lock_guard< StagingBuffer > lock{*stagingBuffer};

		if ( !stagingBuffer->writeData(memoryRegion) )
		{
			TraceError{ClassId} << "Unable to write " << memoryRegion.bytes() << " bytes of data in the staging buffer !";

			return false;
		}

		TraceSuccess{ClassId} << memoryRegion.bytes() << " bytes successfully written in the staging buffer !";

		/* Transfer the buffer data from host memory to device memory. */
		return transferManager.transfer(*stagingBuffer, *this);
	}
}
