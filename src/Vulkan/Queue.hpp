/*
 * Emeraude/Vulkan/Queue.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractObject.hpp"

/* Local inclusions for usages. */
#include "CommandBuffer.hpp"
#include "Sync/Fence.hpp"
#include "Sync/Semaphore.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief Defines a device working queue.
	 * @extends Emeraude::Vulkan::AbstractObject A queue is directly created by the device, so a simple object is perfect.
	 */
	class Queue final : public AbstractObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanQueue"};

			/**
			 * @brief Constructs a device queue.
			 * @param queue The handle of the queue.
			 * @param familyQueueIndex Set which family queue is used to create this queue.
			 */
			Queue (VkQueue queue, uint32_t familyQueueIndex) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Queue (const Queue & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Queue (Queue && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Queue & operator= (const Queue & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Queue & operator= (Queue && copy) noexcept = default;

			/**
			 * @brief Destructs the device queue.
			 */
			~Queue () override;

			/**
			 * @brief Creates the transfer fence for the queue.
			 * @return bool
			 */
			bool createTransferFence (const std::shared_ptr< Device > & device) noexcept;

			/**
			 * @brief Returns the vulkan queue handle.
			 * @return VkQueue
			 */
			[[nodiscard]]
			VkQueue handle () const noexcept;

			/**
			 * @brief Returns the queue family index of the physical device is used by this queue.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t familyQueueIndex () const noexcept;

			/**
			 * @brief Returns the transfer fence of the queue.
			 * @return std::shared_ptr< Sync::Fence >
			 */
			[[nodiscard]]
			std::shared_ptr< Sync::Fence > transferFence () const noexcept;

			/**
			 * @brief Submit a transfer command buffer with a fence.
			 * @param buffer A reference to a command buffer smart pointer.
			 * @return bool
			 */
			[[nodiscard]]
			bool submitTransfer (const std::shared_ptr< CommandBuffer > & buffer) const noexcept;

			/**
			 * @brief Submit a single command buffer with semaphores.
			 * @param buffer A reference to a command buffer smart pointer.
			 * @param waitSemaphore
			 * @param waitStageFlags
			 * @param signalSemaphore
			 * @return bool
			 */
			[[nodiscard]]
			bool submit (const std::shared_ptr< CommandBuffer > & buffer, const Sync::Semaphore & waitSemaphore, VkPipelineStageFlags waitStageFlags, const Sync::Semaphore & signalSemaphore, const Sync::Fence & fence) const noexcept;

			/**
			 * @brief Submits a present info.
			 * @param presentInfo A pointer to a present info.
			 * @param swapChainRecreationNeeded A bool to switch on bad presentation.
			 * @return bool
			 */
			[[deprecated("Bad design")]]
			bool present (const VkPresentInfoKHR * presentInfo, bool & swapChainRecreationNeeded) const noexcept;

			/**
			 * @brief Waits for the queue to complete work.
			 * @return void
			 */
			[[deprecated("Don't use this as synchronization.")]]
			[[nodiscard]]
			bool waitIdle () const noexcept;

		private:

			static std::mutex s_mutex;

			VkQueue m_handle;
			uint32_t m_familyQueueIndex;
			std::shared_ptr< Sync::Fence > m_transferFence{};
	};
}
