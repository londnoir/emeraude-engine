/*
 * Emeraude/Vulkan/TransferManager.cpp
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

#include "TransferManager.hpp"

/* C/C++ standard libraries. */
#include <sstream>

/* Local inclusions. */
#include "AbstractDeviceBuffer.hpp"
#include "Arguments.hpp"
#include "Device.hpp"
#include "Image.hpp"
#include "Settings.hpp"
#include "StagingBuffer.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	const size_t TransferManager::ClassUID{Observable::getClassUID()};
	std::array< TransferManager *, 2 > TransferManager::s_instances{nullptr, nullptr}; // NOLINT NOTE: Singleton behavior

	TransferManager::TransferManager (const Arguments & arguments, Settings & coreSettings, TransferType type) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_coreSettings(coreSettings)
	{
		if ( s_instances[static_cast< size_t >(type)] != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			std::terminate();
		}

		s_instances[static_cast< size_t >(type)] = this;
	}

	TransferManager::~TransferManager ()
	{
		for ( auto & pointer : s_instances )
		{
			if ( pointer == this )
			{
				pointer = nullptr;

				break;
			}
		}
	}

	TransferManager *
	TransferManager::instance (TransferType type) noexcept
	{
		return s_instances[static_cast< size_t >(type)];
	}

	bool
	TransferManager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	TransferManager::usable () const noexcept
	{
		return m_flags[Usable];
	}

	void
	TransferManager::setDevice (const std::shared_ptr< Device > & device) noexcept
	{
		m_device = device;
	}

	const std::shared_ptr< Device > &
	TransferManager::device () const noexcept
	{
		return m_device;
	}

	bool
	TransferManager::onInitialize () noexcept
	{
		if ( m_device == nullptr || !m_device->isCreated() )
		{
			Tracer::error(ClassId, "No device set !");

			return false;
		}

		m_transferCommandPool = std::make_shared< CommandPool >(m_device, m_device->getTransferFamilyIndex());
		m_transferCommandPool->setIdentifier("TransferManager-Transfer-CommandPool");

		if ( !m_transferCommandPool->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create the transfer command pool !");

			m_transferCommandPool.reset();

			return false;
		}

		/* FIXME: Check the idea beyond this with the new queue system. */

		/* Read the queue configuration from the device. */
		if ( !m_device->hasBasicSupport() )
		{
			m_flags[SeparatedQueues] = true;

			m_specificCommandPool = std::make_shared< CommandPool >(m_device, m_device->getGraphicsFamilyIndex());
			m_specificCommandPool->setIdentifier("TransferManager-Specific-CommandPool");

			if ( !m_specificCommandPool->createOnHardware() )
			{
				Tracer::error(ClassId, "Unable to create the specific command pool !");

				m_specificCommandPool.reset();

				return false;
			}
		}
		else
		{
			m_specificCommandPool = m_transferCommandPool;
		}

		m_flags[Usable] = true;

		return true;
	}

	bool
	TransferManager::onTerminate () noexcept
	{
		const std::lock_guard< std::mutex > lockA{m_stagingBufferMutex};
		const std::lock_guard< std::mutex > lockB{m_transferMutex};

		m_device->waitIdle();

		m_specificCommandPool.reset();
		m_transferCommandPool.reset();

		m_stagingBuffers.clear();

		m_device.reset();

		return true;
	}

	std::string
	TransferManager::getStagingBuffersStatistics () const noexcept
	{
		std::stringstream output{};

		output << "Allocated staging buffers :" "\n";

		for ( const auto & stagingBuffer : m_stagingBuffers )
		{
			output << " - Buffer @" << stagingBuffer.get() << " size " << stagingBuffer->bytes() << " bytes" "\n";
		}

		return output.str();
	}

	std::shared_ptr< StagingBuffer >
	TransferManager::getStagingBuffer (size_t bytes) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_stagingBufferMutex};

		/* Try to get an existing one... */
		auto buffer = this->searchFreeStagingBuffer(bytes);

		if ( buffer == nullptr )
		{
			/* ... Or create a new one. */
			buffer = this->createStagingBuffer(bytes);

			if ( buffer == nullptr )
			{
				return nullptr;
			}

			m_stagingBuffers.emplace_back(buffer);
		}

		/* Lock the buffer for the outside world. */
		buffer->lock();

		return buffer;
	}

	std::shared_ptr< StagingBuffer >
	TransferManager::createStagingBuffer (size_t bytes) const noexcept
	{
		auto buffer = std::make_shared< StagingBuffer >(m_device, bytes);
		buffer->setIdentifier((std::stringstream{} << "TransferManager-Buffer" << m_stagingBuffers.size() << "-StagingBuffer").str());

		if ( !buffer->createOnHardware() )
		{
			TraceError{ClassId} << "Unable to create a new staging buffer of " << bytes << " bytes !";

			return nullptr;
		}

		TraceSuccess{ClassId} <<
			"A new staging buffer of " << bytes << " bytes is successfully created !" "\n"
			<< this->getStagingBuffersStatistics();

		return buffer;
	}

	std::shared_ptr< StagingBuffer >
	TransferManager::searchFreeStagingBuffer (size_t bytes) const noexcept
	{
		if ( m_stagingBuffers.empty() )
		{
			Tracer::info(ClassId, "No staging buffer allocated yet.");

			return nullptr;
		}

		/* Get the first free buffer with sufficient space ... */
		for ( const auto & stagingBuffer : m_stagingBuffers )
		{
			const auto currentSize = stagingBuffer->bytes();

			if ( stagingBuffer->isLocked() )
			{
				continue;
			}

			if ( bytes > stagingBuffer->bytes() )
			{
				continue;
			}

			TraceSuccess{ClassId} <<
				"Found an unused staging buffer of " << currentSize << " bytes sufficient for " << bytes << " bytes !" "\n"
				<< this->getStagingBuffersStatistics();

			return stagingBuffer;
		}

		/* ... Or get the first free buffer and reallocate it ... */
		for ( const auto & stagingBuffer : m_stagingBuffers )
		{
			const auto currentSize = stagingBuffer->bytes();

			if ( stagingBuffer->isLocked() )
			{
				continue;
			}

			if ( bytes > stagingBuffer->bytes() )
			{
				if ( !stagingBuffer->recreate(bytes) )
				{
					continue;
				}
			}

			TraceSuccess{ClassId} <<
				"Found an unused staging buffer reallocated from " << currentSize << " to " << bytes << " bytes !" "\n"
				<< this->getStagingBuffersStatistics();

			return stagingBuffer;
		}

		TraceInfo{ClassId} <<
			"No existing staging buffer available for now." "\n"
			<< this->getStagingBuffersStatistics();

		return nullptr;
	}

	bool
	TransferManager::transfer (const StagingBuffer & stagingBuffer, AbstractDeviceBuffer & dstBuffer, VkDeviceSize offset) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_transferMutex};

#ifdef DEBUG
		const auto endCopyOffset = offset + dstBuffer.bytes();

		if ( endCopyOffset > stagingBuffer.bytes() )
		{
			const auto overflow = endCopyOffset - stagingBuffer.bytes();

			TraceError{ClassId} <<
				"Source buffer overflow with " << overflow << " bytes !" "\n"
				"(offset:" << offset << " + length:" << dstBuffer.bytes() << ") > srcBuffer:" << stagingBuffer.bytes();

			return false;
		}
#endif

		auto commandBuffer = std::make_shared< CommandBuffer >(m_transferCommandPool, true);
		commandBuffer->setIdentifier("TransferManager-ToBuffer-CommandBuffer");

		if ( !commandBuffer->isCreated() )
		{
			Tracer::error(ClassId, "Unable to create a transfer command buffer !");

			return false;
		}

		if ( !commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) )
		{
			return false;
		}

		commandBuffer->copy(stagingBuffer, dstBuffer, offset, 0, dstBuffer.bytes());

		if ( !commandBuffer->end() )
		{
			return false;
		}

		TraceInfo{ClassId} << "Submitting the transfer command (Buffer to Buffer) for buffer '" << dstBuffer.identifier() << "' !";

		if ( !m_device->getQueue(QueueJob::Transfer, QueuePriority::Medium)->submitTransfer(commandBuffer) )
		{
			return false;
		}

		TraceSuccess{ClassId} << stagingBuffer.bytes() << " bytes successfully transferred to the buffer in device memory !";

		return true;
	}

	bool
	TransferManager::transfer (const StagingBuffer & stagingBuffer, Image & dstImage, VkDeviceSize offset) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_transferMutex};

		/* CPU -> GPU with transfer queue. */
		{
			auto commandBuffer = std::make_shared< CommandBuffer >(m_transferCommandPool, true);
			commandBuffer->setIdentifier("TransferManager-ToImageA-CommandBuffer");

			if ( !commandBuffer->isCreated() )
			{
				Tracer::error(ClassId, "Unable to create a transfer command buffer !");

				return false;
			}

			if ( !commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) )
			{
				return false;
			}

			/* Prepare the image layout to receive data. */
			const VkImageLayout newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;

			Sync::ImageMemoryBarrier barrier{dstImage,
				VK_IMAGE_LAYOUT_UNDEFINED, newLayout,
				VK_ACCESS_NONE, VK_ACCESS_TRANSFER_WRITE_BIT
			};
			barrier.setIdentifier("TransferManager-ToImageA-ImageMemoryBarrier");

			commandBuffer->pipelineBarrier(barrier, VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT);

			commandBuffer->copy(stagingBuffer, dstImage, offset);

			if ( !commandBuffer->end() )
			{
				return false;
			}

			TraceInfo{ClassId} << "Submitting the transfer command (Buffer to Image, 1/2) for image '" << dstImage.identifier() << "' !";

			if ( !m_device->getQueue(QueueJob::Transfer, QueuePriority::Medium)->submitTransfer(commandBuffer) )
			{
				return false;
			}

			dstImage.setCurrentImageLayout(newLayout);
		}

		/* GPU -> GPU with graphics queue. */
		{
			auto commandBuffer = std::make_shared< CommandBuffer >(m_specificCommandPool, true);
			commandBuffer->setIdentifier("TransferManager-ToImageB-CommandBuffer");

			if ( !commandBuffer->isCreated() )
			{
				Tracer::error(ClassId, "Unable to create a specific command buffer !");

				return false;
			}

			if ( !commandBuffer->begin(VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT) )
			{
				return false;
			}

			/* Prepare the image layout to be used by a fragment shader. */
			const VkImageLayout newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;

			Sync::ImageMemoryBarrier barrier{dstImage,
				VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, newLayout,
				VK_ACCESS_TRANSFER_WRITE_BIT, VK_ACCESS_SHADER_READ_BIT
			};
			barrier.setIdentifier("TransferManager-ToImageB-ImageMemoryBarrier");

			commandBuffer->pipelineBarrier(barrier, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT);

			if ( !commandBuffer->end() )
			{
				return false;
			}

			TraceInfo{ClassId} << "Submitting the transfer command (Buffer to Image, 2/2) for image '" << dstImage.identifier() << "' !";

			if ( !m_device->getQueue(QueueJob::GraphicsTransfer, QueuePriority::Medium)->submitTransfer(commandBuffer) )
			{
				return false;
			}

			dstImage.setCurrentImageLayout(newLayout);
		}

		TraceSuccess{ClassId} << stagingBuffer.bytes() << " bytes successfully transferred to the image in device memory !";

		return true;
	}
}
