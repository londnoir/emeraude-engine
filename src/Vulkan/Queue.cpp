/*
 * Emeraude/Vulkan/Queue.cpp
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

#include "Queue.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	std::mutex Queue::s_mutex{};

	Queue::Queue (VkQueue queue, uint32_t familyQueueIndex) noexcept
		: m_handle(queue), m_familyQueueIndex(familyQueueIndex)
	{
		this->setCreated();
	}

	Queue::~Queue ()
	{
		this->setDestroyed();
	}

	bool
	Queue::createTransferFence (const std::shared_ptr< Device > & device) noexcept
	{
		m_transferFence.reset();
		m_transferFence = std::make_shared< Sync::Fence >(device);
		m_transferFence->setIdentifier("Queue-Main-Fence");

		return m_transferFence->createOnHardware();
	}

	VkQueue
	Queue::handle () const noexcept
	{
		return m_handle;
	}

	uint32_t
	Queue::familyQueueIndex () const noexcept
	{
		return m_familyQueueIndex;
	}

	std::shared_ptr< Sync::Fence >
	Queue::transferFence () const noexcept
	{
		return m_transferFence;
	}

	bool
	Queue::submitTransfer (const std::shared_ptr< CommandBuffer > & buffer) const noexcept
	{
		const std::lock_guard< std::mutex > lock{s_mutex};

		/* Wait for transfer on this queue to finish. */
		if ( !m_transferFence->wait() )
		{
			return false;
		}

		m_transferFence->reset();

		auto * commandBufferHandle = buffer->handle();

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pNext = nullptr;
		submitInfo.waitSemaphoreCount = 0;
		submitInfo.pWaitSemaphores = nullptr;
		submitInfo.pWaitDstStageMask = nullptr;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBufferHandle;
		submitInfo.signalSemaphoreCount = 0;
		submitInfo.pSignalSemaphores = nullptr;

		//TraceInfo{ClassId} << "Submitting on queue '" << this->identifier() << "' ...";

		const auto result = vkQueueSubmit(
			m_handle,
			1, &submitInfo,
			m_transferFence->handle()
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to submit command buffers to a queue : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}

	bool
	Queue::submit (const std::shared_ptr< CommandBuffer > & buffer, const Sync::Semaphore & waitSemaphore, VkPipelineStageFlags waitStageFlags, const Sync::Semaphore & signalSemaphore, const Sync::Fence & fence) const noexcept
	{
		const std::lock_guard< std::mutex > lock{s_mutex};

		/* Wait for transfer on this queue to finish. */
		if ( !m_transferFence->wait() )
		{
			return false;
		}

		auto * commandBufferHandle = buffer->handle();
		auto * waitSemaphoreHandle = waitSemaphore.handle();
		auto * signalSemaphoreHandle = signalSemaphore.handle();

		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.pNext = nullptr;

		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = &waitSemaphoreHandle;
		submitInfo.pWaitDstStageMask = &waitStageFlags;

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBufferHandle;

		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &signalSemaphoreHandle;

		//TraceInfo{ClassId} << "Submitting on queue '" << this->identifier() << "' ...";

		const auto result = vkQueueSubmit(
			m_handle,
			1, &submitInfo,
			fence.handle()
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to submit command buffers to a queue : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}

	bool
	Queue::present (const VkPresentInfoKHR * presentInfo, bool & swapChainRecreationNeeded) const noexcept
	{
		/* Wait for transfer on this queue to finish. */
		if ( !m_transferFence->wait() )
		{
			return false;
		}

		//TraceInfo{ClassId} << "Presenting on queue '" << this->identifier() << "' ...";

		switch ( vkQueuePresentKHR(m_handle, presentInfo) )
		{
			case VK_SUCCESS :
				return true;

			case VK_ERROR_OUT_OF_DATE_KHR :
				Tracer::info(ClassId, "VK_ERROR_OUT_OF_DATE_KHR @ presentation !");

				swapChainRecreationNeeded = true;

				return false;

			case VK_SUBOPTIMAL_KHR :
				Tracer::info(ClassId, "VK_SUBOPTIMAL_KHR @ presentation !");

				swapChainRecreationNeeded = true;

				return false;

			default :
				Tracer::error(ClassId, "Unable to present an image !");

				return false;
		}
	}

	bool
	Queue::waitIdle () const noexcept
	{
		const auto result = vkQueueWaitIdle(m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to wait the queue to complete : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}
}
