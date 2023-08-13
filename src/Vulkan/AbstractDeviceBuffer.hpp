/*
 * Emeraude/Vulkan/AbstractDeviceBuffer.hpp
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

#pragma once

/* C/C++ standard libraries. */
#include <memory>

/* Local inclusions for inheritances. */
#include "MemoryRegion.hpp"
#include "Buffer.hpp"

namespace Emeraude::Vulkan
{
	class TransferManager;

	/**
	 * @brief Defines an abstract class for all device-side buffers in Vulkan API.
	 * @extends Emeraude::Vulkan::Buffer This is the base for Vulkan buffer logics.
	 */
	class AbstractDeviceBuffer : public Buffer
	{
		public:

			/**
			 * @brief Destructs the device buffer.
			 */
			~AbstractDeviceBuffer () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractDeviceBuffer (const AbstractDeviceBuffer & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractDeviceBuffer (AbstractDeviceBuffer && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractDeviceBuffer & operator= (const AbstractDeviceBuffer & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			AbstractDeviceBuffer & operator= (AbstractDeviceBuffer && copy) noexcept = delete;

			/**
			 * @brief Writes data into the device (GPU side) video memory.
			 * @param transferManager A reference to a transfer manager.
			 * @param memoryRegion A reference to the memory region.
			 * @return bool
			 */
			bool writeData (TransferManager & transferManager, const MemoryRegion & memoryRegion) noexcept;

		protected:

			/**
			 * @brief Constructs a device buffer.
			 * @param device A reference to the device smart pointer.
			 * @param createFlags The create info flags.
			 * @param deviceSize The size in bytes.
			 * @param bufferUsageFlags The buffer usage flags.
			 */
			AbstractDeviceBuffer (const std::shared_ptr< Device > & device, VkBufferCreateFlags createFlags, VkDeviceSize deviceSize, VkBufferUsageFlags bufferUsageFlags) noexcept;
	};
}
