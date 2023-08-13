/*
 * Emeraude/Vulkan/Sync/ImageMemoryBarrier.cpp
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

#include "ImageMemoryBarrier.hpp"

/* Local inclusions. */
#include "../Image.hpp"

namespace Emeraude::Vulkan::Sync
{
	ImageMemoryBarrier::ImageMemoryBarrier (const Image & image, VkImageLayout oldLayout, VkImageLayout newLayout, VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask) noexcept
	{
		m_barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		m_barrier.pNext = nullptr;
		m_barrier.srcAccessMask = srcAccessMask;
		m_barrier.dstAccessMask = dstAccessMask;
		m_barrier.oldLayout = oldLayout;
		m_barrier.newLayout = newLayout;
		m_barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		m_barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
		m_barrier.image = image.handle();
		m_barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		m_barrier.subresourceRange.baseMipLevel = 0;
		m_barrier.subresourceRange.levelCount = image.createInfo().mipLevels;
		m_barrier.subresourceRange.baseArrayLayer = 0;
		m_barrier.subresourceRange.layerCount = image.createInfo().arrayLayers;

		this->setCreated();
	}

	ImageMemoryBarrier::~ImageMemoryBarrier ()
	{
		this->setDestroyed();
	}

	const VkImageMemoryBarrier &
	ImageMemoryBarrier::get () const noexcept
	{
		return m_barrier;
	}
}
