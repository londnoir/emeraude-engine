/*
 * src/Vulkan/VertexBufferObject.hpp
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

#pragma once

/* STL inclusions. */
#include <cstddef>
#include <memory>
#include <vector>

/* Local inclusions for inheritances. */
#include "AbstractDeviceBuffer.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief Defines a convenient way to build a vertex buffer object (VBO).
	 * @extends Emeraude::Vulkan::AbstractDeviceBuffer This is a device-side buffer.
	 */
	class VertexBufferObject final : public AbstractDeviceBuffer
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanVertexBufferObject"};

			/**
			 * @brief Constructs a vertex buffer object (VBO).
			 * @warning The buffer assumes we will only use float value.
			 * @param device A reference to the device smart pointer.
			 * @param vertexCount The number of vertex that buffer will hold.
			 * @param vertexElementCount The number of sub-element that composes one vertex.
			 */
			VertexBufferObject (const std::shared_ptr< Device > & device, size_t vertexCount, size_t vertexElementCount) noexcept;

			/**
			 * @brief Returns the number of vertex in this buffer.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			vertexCount () const noexcept
			{
				return m_vertexCount;
			}

			/**
			 * @brief Returns the number of sub-element of one vertex in this buffer.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			vertexElementCount () const noexcept
			{
				return m_vertexElementCount;
			}

			/**
			 * @brief Returns the total number of element in this buffer.
			 * @note Same as VertexBufferObject::vertexCount() * VertexBufferObject::vertexElementCount().
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			elementCount () const noexcept
			{
				return m_vertexCount * m_vertexElementCount;
			}

			/**
			 * @brief Creates a vertex buffer object with initial data.
			 * @param transferManager A reference to a transfer manager.
			 * @param data A reference to a vector.
			 * @return bool
			 */
			[[nodiscard]]
			bool create (TransferManager & transferManager, const std::vector< float > & data) noexcept;

			[[nodiscard]]
			bool writeData (TransferManager & transferManager, const std::vector< float > & data) noexcept;

		private:

			size_t m_vertexCount;
			size_t m_vertexElementCount;
	};
}
