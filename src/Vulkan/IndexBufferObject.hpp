/*
 * src/Vulkan/IndexBufferObject.hpp
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
#include <cstdint>
#include <vector>
#include <memory>

/* Local inclusions for inheritances. */
#include "AbstractDeviceBuffer.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief Defines a convenient way to build an index buffer object (IBO).
	 * @extends Emeraude::Vulkan::AbstractDeviceBuffer This is a device-side buffer.
	 */
	class IndexBufferObject final : public AbstractDeviceBuffer
	{
		public:

			/**
			 * @brief Constructs an index buffer object (IBO).
			 * @param device A reference to the device smart pointer.
			 * @param indexCount The number of indices the buffer will hold
			 */
			IndexBufferObject (const std::shared_ptr< Device > & device, size_t indexCount) noexcept;

			/**
			 * @brief Returns the number of index in this buffer.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			indexCount () const noexcept
			{
				return m_indexCount;
			}

			/**
			 * @brief Creates an index buffer object with initial data.
			 * @param transferManager A reference to a transfer manager.
			 * @param data A reference to a vector.
			 * @return bool
			 */
			[[nodiscard]]
			bool create (TransferManager & transferManager, const std::vector< uint32_t > & data) noexcept;

		private:

			size_t m_indexCount;
	};
}
