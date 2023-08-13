/*
 * Emeraude/Vulkan/CommandPool.hpp
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
#include <mutex>
#include <vector>

/* Local inclusions */
#include "AbstractDeviceDependentObject.hpp"

namespace Emeraude::Vulkan
{
	class CommandBuffer;

	/**
	 * @brief The CommandPool class.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This Vulkan object needs a device.
	 */
	class CommandPool final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanCommandPool"};

			/**
			 * @brief Constructs a command pool.
			 * @param device A reference to a smart pointer of a device.
			 * @param queueFamilyIndex Set which family queue will used by the command pool.
			 * @param createFlags The create info flags. Default none.
			 */
			CommandPool (const std::shared_ptr< Device > & device, uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a command pool with create info.
			 * @param device A reference to a smart pointer of a device.
			 * @param createInfo A reference to a create info.
			 */
			CommandPool (const std::shared_ptr< Device > & device, const VkCommandPoolCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			CommandPool (const CommandPool & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			CommandPool (CommandPool && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			CommandPool & operator= (const CommandPool & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			CommandPool & operator= (CommandPool && copy) noexcept = delete;


			/**
			 * @brief Destructs the command pool.
			 */
			~CommandPool () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Returns the command pool vulkan handle.
			 * @return VkCommandPool
			 */
			[[nodiscard]]
			VkCommandPool handle () const noexcept;

			/**
			 * @brief Returns the command pool create info.
			 * @return VkCommandPoolCreateInfo
			 */
			[[nodiscard]]
			VkCommandPoolCreateInfo createInfo () const noexcept;

			/**
			 * @brief Returns the queue family index used at creation.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t queueFamilyIndex () const noexcept;

			/**
			 * @brief Allocates one command buffer from this pool.
			 * @param primaryLevel
			 * @return bool
			 */
			[[nodiscard]]
			VkCommandBuffer allocateCommandBuffer (bool primaryLevel) noexcept;

			/**
			 * @brief Frees one command buffer.
			 * @param commandBuffer A command buffer handle.
			 * @return void
			 */
			void freeCommandBuffer (VkCommandBuffer commandBufferHandle) noexcept;

		private:

			VkCommandPool m_handle{VK_NULL_HANDLE};
			VkCommandPoolCreateInfo m_createInfo{};
			mutable std::mutex m_allocationMutex{};
	};
}
