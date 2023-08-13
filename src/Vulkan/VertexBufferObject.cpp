/*
 * Emeraude/Vulkan/VertexBufferObject.cpp
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

#include "VertexBufferObject.hpp"

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	VertexBufferObject::VertexBufferObject (const std::shared_ptr< Device > & device, size_t vertexCount, size_t vertexElementCount) noexcept
		: AbstractDeviceBuffer(device, 0, static_cast< VkDeviceSize >(vertexCount * vertexElementCount * sizeof(float)), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT),
		  m_vertexCount(vertexCount),
		  m_vertexElementCount(vertexElementCount)
	{

	}

	size_t
	VertexBufferObject::vertexCount () const noexcept
	{
		return m_vertexCount;
	}

	size_t
	VertexBufferObject::vertexElementCount () const noexcept
	{
		return m_vertexElementCount;
	}

	size_t
	VertexBufferObject::elementCount () const noexcept
	{
		return m_vertexCount * m_vertexElementCount;
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

		if ( !this->writeData(transferManager, {data.data(), bytes}) )
		{
			TraceError{ClassId} << "Unable to write " << bytes << " bytes into the buffer !";

			return false;
		}

		return true;
	}
}
