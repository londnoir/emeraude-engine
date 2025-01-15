/*
 * src/Vulkan/VertexBufferObject.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "VertexBufferObject.hpp"

/* Local inclusions. */
#include "TransferManager.hpp"
#include "MemoryRegion.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	VertexBufferObject::VertexBufferObject (const std::shared_ptr< Device > & device, size_t vertexCount, size_t vertexElementCount) noexcept
		: AbstractDeviceBuffer(device, 0, static_cast< VkDeviceSize >(vertexCount * vertexElementCount * sizeof(float)), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT),
		  m_vertexCount(vertexCount),
		  m_vertexElementCount(vertexElementCount)
	{

	}

	bool
	VertexBufferObject::create (TransferManager & transferManager, const std::vector< float > & data) noexcept
	{
		const auto bytes = data.size() * sizeof(float);

		if ( !this->createOnHardware() )
		{
			TraceError{ClassId} << "Unable to allocate " << bytes << " bytes !";

			return false;
		}

		if ( !this->AbstractDeviceBuffer::writeData(transferManager, {data.data(), bytes}) )
		{
			TraceError{ClassId} << "Unable to write " << bytes << " bytes into the buffer !";

			return false;
		}

		return true;
	}

	bool
	VertexBufferObject::writeData (TransferManager & transferManager, const std::vector< float > & data) noexcept
	{
		const auto bytes = data.size() * sizeof(float);

		if ( !this->AbstractDeviceBuffer::writeData(transferManager, {data.data(), bytes}) )
		{
			TraceError{ClassId} << "Unable to write " << bytes << " bytes into the buffer !";

			return false;
		}

		return true;
	}
}
