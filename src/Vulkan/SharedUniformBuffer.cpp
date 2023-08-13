/*
 * Emeraude/Vulkan/SharedUniformBuffer.cpp
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

#include "SharedUniformBuffer.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	SharedUniformBuffer::SharedUniformBuffer (const std::shared_ptr< Device > & device, Saphir::Declaration::UniformBlock uniformBlock, size_t maxElementCount) noexcept
		: m_device(device), m_uniformBlock(std::move(uniformBlock)), m_uniformBlockSize(m_uniformBlock.bytes())
	{
		/* NOTE: nvidia GTX 1070 : 65536 bytes and 256 bytes alignment, so 256 optimal elements. */
		const auto & limits = device->physicalDevice()->properties().limits;
		const auto maxUBOSize = limits.maxUniformBufferRange;
		const auto minUBOAlignment =  limits.minUniformBufferOffsetAlignment;

		m_blockAlignedSize = minUBOAlignment * Math::alignCount(m_uniformBlockSize, minUBOAlignment);
		m_maxElementCountPerUBO = maxUBOSize / m_blockAlignedSize;


		if ( maxElementCount == 0 )
		{
#ifdef DEBUG
			TraceDebug{ClassId} << "Preparing 1 uniform buffer object ...";
#endif
			if ( !this->addBuffer() )
			{
				return;
			}
		}
		else
		{
			const auto bufferCount = Math::alignCount(maxElementCount * m_blockAlignedSize, static_cast< size_t >(maxUBOSize));
#ifdef DEBUG
			TraceDebug{ClassId} << "Preparing " << bufferCount << " uniform buffer object ...";
#endif
			for ( size_t index = 0; index < bufferCount; index++ )
			{
				if ( !this->addBuffer() )
				{
					return;
				}
			}
		}

#ifdef DEBUG
		TraceDebug{ClassId} <<
			"Shared uniform buffer object data : " "\n"
			"UBO maximum size : " << maxUBOSize << " bytes" "\n"
			"UBO minimum alignment : " << minUBOAlignment << " bytes" "\n"
			"Uniform block structure size : " << m_uniformBlockSize << " bytes" "\n"
			"Uniform block aligned size : " << m_blockAlignedSize << " bytes" "\n"
			"Max element per UBO : " << m_maxElementCountPerUBO << "\n";
#endif
	}

	bool
	SharedUniformBuffer::usable () const noexcept
	{
		return !m_uniformBufferObjects.empty();
	}

	const UniformBufferObject *
	SharedUniformBuffer::uniformBufferObject (uint32_t index) const noexcept
	{
		const auto bufferIndex = this->bufferIndex(index);

		if ( bufferIndex >= m_uniformBufferObjects.size() )
		{
			TraceError{ClassId} << "There is no uniform buffer object #" << bufferIndex << " !";

			return nullptr;
		}

		return m_uniformBufferObjects[bufferIndex].get();
	}

	UniformBufferObject *
	SharedUniformBuffer::uniformBufferObject (uint32_t index) noexcept
	{
		const auto bufferIndex = this->bufferIndex(index);

		if ( bufferIndex >= m_uniformBufferObjects.size() )
		{
			TraceError{ClassId} << "There is no uniform buffer object #" << bufferIndex << " !";

			return nullptr;
		}

		return m_uniformBufferObjects[bufferIndex].get();
	}

	bool
	SharedUniformBuffer::addElement (const void * element, uint32_t & offset) noexcept
	{
		offset = 0;

		for ( auto & seat : m_elements )
		{
			if ( seat == nullptr )
			{
				seat = element;

				return true;
			}

			offset++;
		}

		return false;
	}

	void
	SharedUniformBuffer::removeElement (const void * element) noexcept
	{
		auto elementIt = std::find_if(m_elements.begin(), m_elements.end(), [element] (const auto & seat) {
			return seat == element;
		});

		if ( elementIt != m_elements.end() )
		{
			*elementIt = nullptr;
		}
	}

	size_t
	SharedUniformBuffer::elementCount () const noexcept
	{
		size_t count = 0;

		for ( const auto & seat : m_elements )
		{
			if ( seat != nullptr )
			{
				count++;
			}
		}

		return count;
	}

	bool
	SharedUniformBuffer::writeElementData (uint32_t index, const void * data) noexcept
	{
		const auto bufferIndex = this->bufferIndex(index);

		if ( bufferIndex >= m_uniformBufferObjects.size() )
		{
			TraceError{ClassId} << "There is no uniform buffer object #" << bufferIndex << " !";

			return false;
		}

		return m_uniformBufferObjects[bufferIndex]->writeData({data, m_uniformBlockSize, m_blockAlignedSize * index});
	}

	bool
	SharedUniformBuffer::addBuffer () noexcept
	{
		const auto & limits = m_device->physicalDevice()->properties().limits;
		const auto identifier = (std::stringstream{} << "SharedUniformBuffer-Chunk#" << m_uniformBufferObjects.size() << "-UniformBufferObject").str();

		m_uniformBufferObjects.emplace_back(std::make_unique< UniformBufferObject >(m_device, limits.maxUniformBufferRange));
		m_uniformBufferObjects.back()->setIdentifier(identifier);

		if ( !m_uniformBufferObjects.back()->createOnHardware() )
		{
			TraceError{ClassId} << "Unable to create an UBO of " << limits.maxUniformBufferRange << " bytes !";

			return false;
		}

		m_elements.resize(m_uniformBufferObjects.size() * m_maxElementCountPerUBO, nullptr);

		return true;
	}

	size_t
	SharedUniformBuffer::bufferIndex (uint32_t index) const noexcept
	{
		return std::floor(index / m_maxElementCountPerUBO);
	}
}
