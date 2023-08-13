/*
 * Emeraude/Vulkan/Buffer.hpp
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
#include "AbstractDeviceDependentObject.hpp"
#include "DeviceMemory.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief Defines the base class of all buffers in Vulkan API.
	 * @extends std::enable_shared_from_this Adds to ability to self replicate the smart pointer.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject to allocate memory on device.
	 */
	class Buffer : public AbstractDeviceDependentObject
	{
		public:

			using AbstractDeviceDependentObject::recreate;

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanBuffer"};

			/**
			 * @brief Constructs a buffer.
			 * @param device A reference to a device smart pointer.
			 * @param createFlags The create info flags.
			 * @param size The size in bytes.
			 * @param usageFlags The buffer usage flags.
			 * @param memoryPropertyFlag The type of memory.
			 */
			Buffer (const std::shared_ptr< Device > & device, VkBufferCreateFlags createFlags, VkDeviceSize size, VkBufferUsageFlags usageFlags, VkMemoryPropertyFlags memoryPropertyFlag) noexcept;

			/**
			 * @brief Constructs a buffer with a create info.
			 * @param device A reference to a smart pointer of the device.
			 * @param createInfo A reference to the create info.
			 */
			Buffer (const std::shared_ptr< Device > & device, const VkBufferCreateInfo & createInfo, VkMemoryPropertyFlags memoryPropertyFlag) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Buffer (const Buffer & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Buffer (Buffer && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Buffer & operator= (const Buffer & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Buffer & operator= (Buffer && copy) noexcept = delete;

			/**
			 * @brief Destructs the buffer.
			 */
			~Buffer () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept final;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept final;

			/**
			 * @brief Recreates the buffer.
			 * @param size The new size of the buffer in bytes.
			 * @return bool
			 */
			virtual bool recreate (VkDeviceSize size) noexcept final;

			/**
			 * @brief Returns the buffer vulkan handle.
			 * @param VkBuffer
			 */
			[[nodiscard]]
			virtual VkBuffer handle () const noexcept final;

			/**
			 * @brief Returns the buffer create info.
			 * @param VkBufferCreateInfo
			 */
			[[nodiscard]]
			virtual VkBufferCreateInfo createInfo () const noexcept final;

			/**
			 * @brief Returns the buffer creation flags.
			 * @return VkBufferCreateFlags
			 */
			[[nodiscard]]
			virtual VkBufferCreateFlags createFlags () const noexcept final;

			/**
			 * @brief Returns the buffer size in bytes.
			 * @warning This information come from the create info, not the device memory.
			 * @return VkDeviceSize
			 */
			[[nodiscard]]
			virtual VkDeviceSize bytes () const noexcept final;

			/**
			 * @brief Returns the buffer usage flags.
			 * @return VkBufferUsageFlags
			 */
			[[nodiscard]]
			virtual VkBufferUsageFlags usageFlags () const noexcept final;

			/**
			 * @brief Returns the buffer usage memory property flags.
			 * @return VkMemoryPropertyFlags
			 */
			[[nodiscard]]
			virtual VkMemoryPropertyFlags memoryPropertyFlags () const noexcept final;

			/**
			 * @brief Returns the descriptor buffer info.
			 * @return VkDescriptorBufferInfo
			 */
			[[nodiscard]]
			virtual VkDescriptorBufferInfo getDescriptorInfo () const noexcept final;

		protected:

			/**
			 * @brief Returns the device memory pointer.
			 * @return const DeviceMemory *
			 */
			[[nodiscard]]
			virtual const DeviceMemory * deviceMemory () const noexcept final;

		private:

			VkBuffer m_handle{VK_NULL_HANDLE};
			VkBufferCreateInfo m_createInfo{};
			VkMemoryPropertyFlags m_memoryPropertyFlag;
			std::unique_ptr< DeviceMemory > m_deviceMemory{};
	};
}
