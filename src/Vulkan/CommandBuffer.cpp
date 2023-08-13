/*
 * Emeraude/Vulkan/CommandBuffer.cpp
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

#include "CommandBuffer.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	CommandBuffer::CommandBuffer (const std::shared_ptr< CommandPool > & commandPool, bool primaryLevel) noexcept
		: m_commandPool(commandPool), m_primaryLevel(primaryLevel)
	{
#ifdef DEBUG
		if ( commandPool == nullptr || !commandPool->isCreated() )
		{
			Tracer::error(ClassId, "Command pool is null or not created to allocate this command buffer !");

			return;
		}
#endif
		m_handle = m_commandPool->allocateCommandBuffer(primaryLevel);

		if ( m_handle == VK_NULL_HANDLE )
		{
			return;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The command buffer " << m_handle << " successfully allocated !";
	}

	CommandBuffer::~CommandBuffer ()
	{
		if ( m_commandPool == nullptr || !m_commandPool->isCreated() )
		{
			Tracer::error(ClassId, "No or uninitialized command pool to destroy this command buffer !");

			return;
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			m_commandPool->freeCommandBuffer(m_handle);

			TraceSuccess{ClassId} << "The command buffer " << m_handle << " gracefully freed !";

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();
	}

	VkCommandBuffer
	CommandBuffer::handle () const noexcept
	{
		return m_handle;
	}

	const std::shared_ptr< CommandPool > &
	CommandBuffer::commandPool () const noexcept
	{
		return m_commandPool;
	}

	bool
	CommandBuffer::isBufferLevelPrimary () const noexcept
	{
		return m_primaryLevel;
	}

	bool
	CommandBuffer::begin (VkCommandBufferUsageFlagBits usage) noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return false;
		}

		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.pNext = nullptr;
		beginInfo.flags = usage;
		beginInfo.pInheritanceInfo = nullptr;

		const auto result = vkBeginCommandBuffer(m_handle, &beginInfo);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to begin record to the command buffer " << m_handle << " : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}

	bool
	CommandBuffer::end () noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return false;
		}

		const auto result = vkEndCommandBuffer(m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to end record to the command buffer " << m_handle << " : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}

	bool
	CommandBuffer::reset (VkCommandBufferResetFlags flags) noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return false;
		}

		const auto result = vkResetCommandBuffer(m_handle, flags);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to reset the command buffer " << m_handle << " : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}

	void
	CommandBuffer::beginRenderPass (const RenderPass & renderPass, const Framebuffer & framebuffer, const VkRect2D & renderArea, const std::array< VkClearValue, 2 > & clearValues, VkSubpassContents subpassContents) const noexcept
	{
#ifdef DEBUG
		if ( !renderPass.isCreated() )
		{
			Tracer::error(ClassId, "The render pass is not created.");

			return;
		}

		if ( !framebuffer.isCreated() )
		{
			Tracer::error(ClassId, "The framebuffer is not created.");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to begin the render pass " << renderPass.handle() << " with the framebuffer " << framebuffer.handle();

			return;
		}
#endif

		VkRenderPassBeginInfo renderPassBeginInfo{};
		renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassBeginInfo.pNext = nullptr;
		renderPassBeginInfo.renderPass = renderPass.handle();
		renderPassBeginInfo.framebuffer = framebuffer.handle();
		renderPassBeginInfo.renderArea= renderArea;
		renderPassBeginInfo.clearValueCount = static_cast< uint32_t >(clearValues.size());
		renderPassBeginInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(m_handle, &renderPassBeginInfo, subpassContents);
	}

	void
	CommandBuffer::endRenderPass () const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return;
		}
#endif

		vkCmdEndRenderPass(m_handle);
	}

	void
	CommandBuffer::update (const Buffer & buffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void * pData) const noexcept
	{
#ifdef DEBUG
		if ( !buffer.isCreated() )
		{
			Tracer::error(ClassId, "The buffer is not created.");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to update the buffer " << buffer.handle();

			return;
		}
#endif

		vkCmdUpdateBuffer(
			m_handle,
			buffer.handle(),
			dstOffset, dataSize, pData
		);
	}

	void
	CommandBuffer::fill (const Buffer & buffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) const noexcept
	{
#ifdef DEBUG
		if ( !buffer.isCreated() )
		{
			Tracer::error(ClassId, "The buffer is not created.");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to fill the buffer " << buffer.handle();

			return;
		}
#endif

		vkCmdFillBuffer(
			m_handle,
			buffer.handle(),
			dstOffset, size, data
		);
	}

	void
	CommandBuffer::copy (const Buffer & src, const Buffer & dst, VkDeviceSize srcOffset, VkDeviceSize dstOffset, VkDeviceSize size) const noexcept
	{
#ifdef DEBUG
		if ( !src.isCreated() )
		{
			Tracer::error(ClassId, "The source buffer is not created.");

			return;
		}

		if ( !dst.isCreated() )
		{
			Tracer::error(ClassId, "The destination buffer is not created.");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to copy buffer " << src.handle() << " to buffer " << dst.handle();

			return;
		}
#endif

		VkBufferCopy bufferCopy{};
		bufferCopy.srcOffset = srcOffset;
		bufferCopy.dstOffset = dstOffset;
		bufferCopy.size = size;

		vkCmdCopyBuffer(
			m_handle,
			src.handle(),
			dst.handle(),
			1, &bufferCopy
		);
	}

	void
	CommandBuffer::copy (const Image & src, const Image & dst) const noexcept
	{
#ifdef DEBUG
		if ( !src.isCreated() )
		{
			Tracer::error(ClassId, "The source image is not created.");

			return;
		}

		if ( !dst.isCreated() )
		{
			Tracer::error(ClassId, "The destination image is not created.");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to copy image " << src.handle() << " to image " << dst.handle();

			return;
		}
#endif

		/* FIXME: Check parameters and what to expose for a correct copy. */
		VkImageCopy imageCopy{};
		imageCopy.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageCopy.srcSubresource.mipLevel = 0;
		imageCopy.srcSubresource.baseArrayLayer = 0;
		imageCopy.srcSubresource.layerCount = src.createInfo().arrayLayers;
		imageCopy.srcOffset = {0, 0, 0};
		imageCopy.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageCopy.dstSubresource.mipLevel = 0;
		imageCopy.dstSubresource.baseArrayLayer = 0;
		imageCopy.dstSubresource.layerCount = dst.createInfo().arrayLayers;
		imageCopy.dstOffset = {0, 0, 0};
		/* FIXME: Use the source image extent for now. */
		imageCopy.extent = src.createInfo().extent; //

		/* FIXME: Check the image layout consistency with the operation. */
		vkCmdCopyImage(
			m_handle,
			src.handle(), src.createInfo().initialLayout,
			dst.handle(), dst.createInfo().initialLayout,
			1, &imageCopy
		);
	}

	void
	CommandBuffer::copy (const Buffer & src, const Image & dst, VkDeviceSize /*srcOffset*/) const noexcept
	{
#ifdef DEBUG
		if ( !src.isCreated() )
		{
			Tracer::error(ClassId, "The source buffer is not created.");

			return;
		}

		if ( !dst.isCreated() )
		{
			Tracer::error(ClassId, "The destination image is not created.");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to copy buffer " << src.handle() << " to image " << dst.handle();

			return;
		}
#endif

		const auto layerCount = dst.createInfo().arrayLayers;
		const auto mipLevelCount = dst.createInfo().mipLevels;
		const auto baseWidth = dst.createInfo().extent.width;
		const auto baseHeight = dst.createInfo().extent.height;

		std::vector< VkBufferImageCopy > regions{};
		regions.reserve(static_cast< size_t >(layerCount) * static_cast< size_t >(mipLevelCount));

		for ( uint32_t layerIndex = 0; layerIndex < layerCount; layerIndex++ )
		{
			// TODO : compute offset to skip one layer with all mip levels.
			const uint32_t layerOffset = layerIndex * (baseWidth * baseHeight * 4);

			for ( uint32_t mipLevelIndex = 0; mipLevelIndex < mipLevelCount; mipLevelIndex++ )
			{
				// TODO : compute sub-offset to pass mip level to this layer.
				const uint32_t offset = layerOffset + 0;

				/* FIXME: Check parameters and what to expose for a correct copy. */
				VkBufferImageCopy bufferImageCopy{};
				bufferImageCopy.bufferOffset = offset;
				bufferImageCopy.bufferRowLength = 0;
				bufferImageCopy.bufferImageHeight = 0;
				bufferImageCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
				bufferImageCopy.imageSubresource.mipLevel = mipLevelIndex;
				bufferImageCopy.imageSubresource.baseArrayLayer = layerIndex;
				bufferImageCopy.imageSubresource.layerCount = 1;
				bufferImageCopy.imageOffset.x = 0;
				bufferImageCopy.imageOffset.y = 0;
				bufferImageCopy.imageOffset.z = 0;
				bufferImageCopy.imageExtent.width = baseWidth >> mipLevelIndex;
				bufferImageCopy.imageExtent.height = baseHeight >> mipLevelIndex;
				bufferImageCopy.imageExtent.depth = 1;

				regions.emplace_back(bufferImageCopy);
			}
		}

		vkCmdCopyBufferToImage(
			m_handle,
			src.handle(),
			dst.handle(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			static_cast< uint32_t >(regions.size()), regions.data()
		);
	}

	void
	CommandBuffer::copy (const Image & src, const Buffer & dst) const noexcept
	{
#ifdef DEBUG
		if ( !src.isCreated() )
		{
			Tracer::error(ClassId, "The source image is not created.");

			return;
		}

		if ( !dst.isCreated() )
		{
			Tracer::error(ClassId, "The destination buffer is not created.");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to copy image " << src.handle() << " to buffer " << dst.handle();

			return;
		}
#endif

		/* FIXME: Check parameters and what to expose for a correct copy. */
		VkBufferImageCopy bufferImageCopy{};
		bufferImageCopy.bufferOffset = 0;
		bufferImageCopy.bufferRowLength = 0;
		bufferImageCopy.bufferImageHeight = 0;
		bufferImageCopy.imageSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		bufferImageCopy.imageSubresource.mipLevel = 0;
		bufferImageCopy.imageSubresource.baseArrayLayer = 0;
		bufferImageCopy.imageSubresource.layerCount = src.createInfo().arrayLayers;
		bufferImageCopy.imageOffset = {0, 0, 0};
		bufferImageCopy.imageExtent = src.createInfo().extent;

		/* FIXME: Check the image layout consistency with the operation. */
		vkCmdCopyImageToBuffer(
			m_handle,
			src.handle(), src.createInfo().initialLayout,
			dst.handle(),
			1, &bufferImageCopy
		);
	}

	void
	CommandBuffer::blit (const Image & src, const Image & dst) const noexcept
	{
#ifdef DEBUG
		if ( !src.isCreated() )
		{
			Tracer::error(ClassId, "The source image is not created.");

			return;
		}

		if ( !dst.isCreated() )
		{
			Tracer::error(ClassId, "The destination image is not created.");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to blit image " << src.handle() << " to image " << dst.handle();

			return;
		}
#endif

		/* FIXME: Pass parameters ! */
		VkImageBlit imageBlit{};
		imageBlit.srcSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageBlit.srcSubresource.mipLevel = 0;
		imageBlit.srcSubresource.baseArrayLayer = 0;
		imageBlit.srcSubresource.layerCount = src.createInfo().arrayLayers;
		imageBlit.srcOffsets[0] = {0, 0, 0};
		imageBlit.srcOffsets[1] = {0, 0, 0};
		imageBlit.dstSubresource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		imageBlit.dstSubresource.mipLevel = 0;
		imageBlit.dstSubresource.baseArrayLayer = 0;
		imageBlit.dstSubresource.layerCount = dst.createInfo().arrayLayers;
		imageBlit.dstOffsets[0] = {0, 0, 0};
		imageBlit.dstOffsets[1] = {0, 0, 0};

		vkCmdBlitImage(
			m_handle,
			src.handle(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			dst.handle(), VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
			1, &imageBlit,
			VK_FILTER_CUBIC_EXT
		);
	}

	void
	CommandBuffer::clearColor (const Image & image, VkImageLayout imageLayout, const PixelFactory::Color< float > & color) const noexcept
	{
#ifdef DEBUG
		if ( !image.isCreated() )
		{
			Tracer::error(ClassId, "The image is not created.");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to clear the color of image " << image.handle();

			return;
		}
#endif

		/* FIXME: Check if the image is a color one. */

		VkClearColorValue colorValue{};
		colorValue.float32[0] = color.red();
		colorValue.float32[1] = color.green();
		colorValue.float32[2] = color.blue();
		colorValue.float32[3] = color.alpha();

		/* NOTE: The whole image as color for now. */
		VkImageSubresourceRange subresourceRange{};
		subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		subresourceRange.baseMipLevel = 0;
		subresourceRange.levelCount = image.createInfo().mipLevels;
		subresourceRange.baseArrayLayer = 0;
		subresourceRange.layerCount = image.createInfo().arrayLayers;

		vkCmdClearColorImage(
			m_handle,
			image.handle(), imageLayout,
			&colorValue,
			1, &subresourceRange
		);
	}

	void
	CommandBuffer::clearDepthStencil (const Image & image, VkImageLayout imageLayout) const noexcept
	{
#ifdef DEBUG
		if ( !image.isCreated() )
		{
			Tracer::error(ClassId, "The image is not created.");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to clear the depth and the stencil of image " << image.handle();

			return;
		}
#endif

		/* FIXME: Check if the image is a color one. */
		/* FIXME: Set the possibility to choose the depth, or stencil and the value. */

		const VkClearDepthStencilValue depthStencilValue{};

		/* NOTE: The whole image as depth/stencil for now. */
		VkImageSubresourceRange subresourceRange{};
		subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT | VK_IMAGE_ASPECT_STENCIL_BIT;
		subresourceRange.baseMipLevel = 0;
		subresourceRange.levelCount = image.createInfo().mipLevels;
		subresourceRange.baseArrayLayer = 0;
		subresourceRange.layerCount = image.createInfo().arrayLayers;

		vkCmdClearDepthStencilImage(
			m_handle,
			image.handle(), imageLayout,
			&depthStencilValue,
			1, &subresourceRange
		);
	}

	void
	CommandBuffer::pipelineBarrier (const std::vector< VkMemoryBarrier > & memoryBarriers, const std::vector< VkBufferMemoryBarrier > & bufferMemoryBarriers, const std::vector< VkImageMemoryBarrier > & imageMemoryBarriers, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return;
		}

		if ( memoryBarriers.empty() && bufferMemoryBarriers.empty() && imageMemoryBarriers.empty() )
		{
			Tracer::warning(ClassId, "There is no memory barrier in the list !");

			return;
		}
#endif

		vkCmdPipelineBarrier(
			m_handle,
			srcStageMask, dstStageMask,
			dependencyFlags,
			static_cast< uint32_t >(memoryBarriers.size()), memoryBarriers.data(),
			static_cast< uint32_t >(bufferMemoryBarriers.size()), bufferMemoryBarriers.data(),
			static_cast< uint32_t >(imageMemoryBarriers.size()), imageMemoryBarriers.data()
		);
	}

	void
	CommandBuffer::pipelineBarrier (const std::vector< VkMemoryBarrier > & memoryBarriers, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return;
		}

		if ( memoryBarriers.empty() )
		{
			Tracer::warning(ClassId, "There is no memory barrier in the list !");

			return;
		}
#endif

		vkCmdPipelineBarrier(
			m_handle,
			srcStageMask, dstStageMask,
			dependencyFlags,
			static_cast< uint32_t >(memoryBarriers.size()), memoryBarriers.data(),
			0, VK_NULL_HANDLE,
			0, VK_NULL_HANDLE
		);
	}

	void
	CommandBuffer::pipelineBarrier (const std::vector< VkBufferMemoryBarrier > & bufferMemoryBarriers, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return;
		}

		if ( bufferMemoryBarriers.empty() )
		{
			Tracer::warning(ClassId, "There is no buffer memory barrier in the list !");

			return;
		}
#endif

		vkCmdPipelineBarrier(
			m_handle,
			srcStageMask, dstStageMask,
			dependencyFlags,
			0, VK_NULL_HANDLE,
			static_cast< uint32_t >(bufferMemoryBarriers.size()), bufferMemoryBarriers.data(),
			0, VK_NULL_HANDLE
		);
	}

	void
	CommandBuffer::pipelineBarrier (const std::vector< VkImageMemoryBarrier > & imageMemoryBarriers, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return;
		}

		if ( imageMemoryBarriers.empty() )
		{
			Tracer::warning(ClassId, "There is no image memory barrier in the list !");

			return;
		}
#endif

		vkCmdPipelineBarrier(
			m_handle,
			srcStageMask, dstStageMask,
			dependencyFlags,
			0, VK_NULL_HANDLE,
			0, VK_NULL_HANDLE,
			static_cast< uint32_t >(imageMemoryBarriers.size()), imageMemoryBarriers.data()
		);
	}

	void
	CommandBuffer::pipelineBarrier (const Sync::MemoryBarrier & memoryBarrier, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return;
		}
#endif

		vkCmdPipelineBarrier(
			m_handle,
			srcStageMask, dstStageMask,
			dependencyFlags,
			1, &memoryBarrier.get(),
			0, VK_NULL_HANDLE,
			0, VK_NULL_HANDLE
		);
	}

	void
	CommandBuffer::pipelineBarrier (const Sync::BufferMemoryBarrier & bufferMemoryBarrier, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return;
		}
#endif

		vkCmdPipelineBarrier(
			m_handle,
			srcStageMask, dstStageMask,
			dependencyFlags,
			0, VK_NULL_HANDLE,
			1, &bufferMemoryBarrier.get(),
			0, VK_NULL_HANDLE
		);
	}

	void
	CommandBuffer::pipelineBarrier (const Sync::ImageMemoryBarrier & imageMemoryBarrier, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags) const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return;
		}
#endif

		vkCmdPipelineBarrier(
			m_handle,
			srcStageMask, dstStageMask,
			dependencyFlags,
			0, VK_NULL_HANDLE,
			0, VK_NULL_HANDLE,
			1, &imageMemoryBarrier.get()
		);
	}

	void
	CommandBuffer::setEvent (const Sync::Event & event, VkPipelineStageFlags flags) const noexcept
	{
#ifdef DEBUG
		if ( !event.isCreated() )
		{
			Tracer::error(ClassId, "The event is not created !");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to set event " << event.handle();

			return;
		}
#endif

		vkCmdSetEvent(
			m_handle,
			event.handle(),
			flags
		);
	}

	void
	CommandBuffer::resetEvent (const Sync::Event & event, VkPipelineStageFlags flags) const noexcept
	{
#ifdef DEBUG
		if ( !event.isCreated() )
		{
			Tracer::error(ClassId, "The event is not created !");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to reset event " << event.handle();

			return;
		}
#endif

		vkCmdResetEvent(
			m_handle,
			event.handle(),
			flags
		);
	}

	void
	CommandBuffer::waitEvents (const std::vector< VkEvent > & events, VkPipelineStageFlags srcFlags, VkPipelineStageFlags dstFlags, const std::vector< VkMemoryBarrier > & memoryBarriers, const std::vector< VkBufferMemoryBarrier > & bufferMemoryBarriers, const std::vector< VkImageMemoryBarrier > & imageMemoryBarriers) noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return;
		}

		if ( events.empty() )
		{
			Tracer::warning(ClassId, "There is no event in the list !");

			return;
		}

		if ( events.empty() && memoryBarriers.empty() && bufferMemoryBarriers.empty() && imageMemoryBarriers.empty() )
		{
			Tracer::warning(ClassId, "There is no memory barrier in the list !");

			return;
		}
#endif

		vkCmdWaitEvents(
			m_handle,
			static_cast< uint32_t >(events.size()), events.data(),
			srcFlags, dstFlags,
			static_cast< uint32_t >(memoryBarriers.size()), memoryBarriers.data(),
			static_cast< uint32_t >(bufferMemoryBarriers.size()), bufferMemoryBarriers.data(),
			static_cast< uint32_t >(imageMemoryBarriers.size()), imageMemoryBarriers.data()
		);
	}

	void
	CommandBuffer::bind (const GraphicsPipeline & graphicsPipeline) const noexcept
	{
#ifdef DEBUG
		if ( !graphicsPipeline.isCreated() )
		{
			Tracer::error(ClassId, "The graphics pipeline is not created !");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to bind graphics pipeline " << graphicsPipeline.handle();

			return;
		}
#endif

		vkCmdBindPipeline(
			m_handle,
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			graphicsPipeline.handle()
		);
	}

	void
	CommandBuffer::bind (const ComputePipeline & computePipeline) const noexcept
	{
#ifdef DEBUG
		if ( !computePipeline.isCreated() )
		{
			Tracer::error(ClassId, "The compute pipeline is not created !");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to bind compute pipeline " << computePipeline.handle();

			return;
		}
#endif

		vkCmdBindPipeline(
			m_handle,
			VK_PIPELINE_BIND_POINT_COMPUTE,
			computePipeline.handle()
		);
	}

	void
	CommandBuffer::bind (const VertexBufferObject & vertexBufferObject, VkDeviceSize offset) const noexcept
	{
#ifdef DEBUG
		if ( !vertexBufferObject.isCreated() )
		{
			Tracer::error(ClassId, "The vertex buffer object is not created !");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to bind vertex buffer object " << vertexBufferObject.handle();

			return;
		}
#endif

		const uint32_t firstBinding = 0;

		std::array< VkBuffer, 1 > vertexBuffers{
			vertexBufferObject.handle()
		};

		std::array< VkDeviceSize, 1 > offsets{
			offset
		};

		vkCmdBindVertexBuffers(
			m_handle,
			firstBinding,
			vertexBuffers.size(), vertexBuffers.data(), offsets.data()
		);
	}

	void
	CommandBuffer::bind (const IndexBufferObject & indexBufferObject, VkDeviceSize offset, VkIndexType indexType) const noexcept
	{
#ifdef DEBUG
		if ( !indexBufferObject.isCreated() )
		{
			Tracer::error(ClassId, "The index buffer object is not created !");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to bind index buffer object " << indexBufferObject.handle();

			return;
		}
#endif

		vkCmdBindIndexBuffer(
			m_handle,
			indexBufferObject.handle(),
			offset,
			indexType
		);
	}

	void
	CommandBuffer::bind (const DescriptorSet & descriptorSet, const PipelineLayout & pipelineLayout, VkPipelineBindPoint bindPoint, uint32_t firstSet, const std::vector< uint32_t > & dynamicOffsets) const noexcept
	{
#ifdef DEBUG
		if ( !pipelineLayout.isCreated() )
		{
			Tracer::error(ClassId, "The pipeline layout is not created !");

			return;
		}

		if ( !descriptorSet.isCreated() )
		{
			Tracer::error(ClassId, "The descriptor set is not created !");

			return;
		}

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to bind descriptor set " << descriptorSet.handle() << " with pipeline layout " << pipelineLayout.handle();

			return;
		}
#endif

		auto * descriptorSetHandle = descriptorSet.handle();

		vkCmdBindDescriptorSets(
			m_handle,
			bindPoint,
			pipelineLayout.handle(),
			firstSet,
			1, &descriptorSetHandle,
			static_cast< uint32_t >(dynamicOffsets.size()), dynamicOffsets.data()
		);
	}

	void
	CommandBuffer::bind (const Graphics::Geometry::Interface & geometry, size_t subGeometryIndex) const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to bind geometry '" << geometry.name() << "'";

			return;
		}
#endif

		/* Binding vertex buffer object if exists. */
		{
			auto * vertexBufferObjectHandle = geometry.vertexBufferObject()->handle();

			const VkDeviceSize offset = geometry.subGeometryOffset(subGeometryIndex);

			vkCmdBindVertexBuffers(
				m_handle,
				0,
				1, &vertexBufferObjectHandle,
				&offset
			);
		}

		/* Binding index buffer object if exists. */
		if ( geometry.useIndexBuffer() )
		{
			const VkDeviceSize offset = 0;
			const VkIndexType indexType = VK_INDEX_TYPE_UINT32;

			vkCmdBindIndexBuffer(
				m_handle,
				geometry.indexBufferObject()->handle(),
				offset,
				indexType
			);
		}
	}

	void
	CommandBuffer::bind (const Graphics::Geometry::Interface & geometry, const VertexBufferObject & modelVBO, size_t subGeometryIndex, VkDeviceSize modelVBOOffset) const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The command buffer is not created !" "\n"
				"Unable to bind geometry '" << geometry.name() << "' with model VBO " << modelVBO.handle();

			return;
		}
#endif

		/* Binding vertex buffer object if exists. */
		{
			const uint32_t firstBinding = 0;

			std::array< VkBuffer, 2 > vertexBuffers{
				geometry.vertexBufferObject()->handle(),
				modelVBO.handle()
			};

			std::array< VkDeviceSize, 2 > offsets{
				geometry.subGeometryOffset(subGeometryIndex),
				modelVBOOffset
			};

			vkCmdBindVertexBuffers(
				m_handle,
				firstBinding,
				vertexBuffers.size(), vertexBuffers.data(), offsets.data()
			);
		}

		/* Binding index buffer object if exists. */
		if ( geometry.useIndexBuffer() )
		{
			const VkDeviceSize offset = 0;
			const VkIndexType indexType = VK_INDEX_TYPE_UINT32;

			vkCmdBindIndexBuffer(
				m_handle,
				geometry.indexBufferObject()->handle(),
				offset,
				indexType
			);
		}
	}

	void
	CommandBuffer::draw (const Graphics::Geometry::Interface & geometry, size_t subGeometryIndex, uint32_t instanceCount) const noexcept
	{
#ifdef DEBUG
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The command buffer is not created !");

			return;
		}

		if ( instanceCount == 0 )
		{
			Tracer::error(ClassId, "No instance count !");

			return;
		}
#endif

		if ( geometry.useIndexBuffer() )
		{
			const uint32_t firstIndex = 0;
			const int32_t vertexOffset = 0;
			const uint32_t firstInstance = 0;

			vkCmdDrawIndexed(
				m_handle,
				geometry.indexBufferObject()->indexCount(),
				instanceCount,
				firstIndex,
				vertexOffset,
				firstInstance
			);
		}
		else
		{
			const uint32_t firstVertex = 0;
			const uint32_t firstInstance = 0;

			vkCmdDraw(
				m_handle,
				geometry.subGeometryLength(subGeometryIndex),
				instanceCount,
				firstVertex,
				firstInstance
			);
		}
	}
}
