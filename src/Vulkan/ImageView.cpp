/*
 * Emeraude/Vulkan/ImageView.cpp
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

#include "ImageView.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "Image.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	ImageView::ImageView (const std::shared_ptr< Image > & image, VkImageViewType viewType, VkImageSubresourceRange subresourceRange, VkComponentMapping components, VkImageViewCreateFlags createFlags) noexcept
		: AbstractDeviceDependentObject(image->device()), m_image(image)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
		m_createInfo.image = VK_NULL_HANDLE;
		m_createInfo.viewType = viewType;
		m_createInfo.format = VK_FORMAT_UNDEFINED;
		m_createInfo.components = components;
		m_createInfo.subresourceRange = subresourceRange;
	}

	ImageView::ImageView (const std::shared_ptr< Image > & image, const VkImageViewCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(image->device()), m_createInfo(createInfo), m_image(image)
	{

	}

	ImageView::~ImageView ()
	{
		this->destroyFromHardware();
	}

	bool
	ImageView::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this image view !");

			return false;
		}

		if ( m_image != nullptr && m_image->isCreated() )
		{
			m_createInfo.image = m_image->handle();
			m_createInfo.format = m_image->createInfo().format;
		}
		else
		{
			Tracer::error(ClassId, "The image is null or not created ! Cannot make a view of it !");

			return false;
		}

		const auto result = vkCreateImageView(
			this->device()->handle(),
			&m_createInfo,
			VK_NULL_HANDLE,
			&m_handle
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create an image view : " << vkResultToCString(result) << " !";

			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The image view " << m_handle << " (" << this->identifier() << ") is successfully created !";

		return true;
	}

	bool
	ImageView::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the image view " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroyImageView(
				this->device()->handle(),
				m_handle,
				VK_NULL_HANDLE
			);

			TraceSuccess{ClassId} << "The image view " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;

			this->setDestroyed();
		}

		return true;
	}

	VkImageView
	ImageView::handle () const noexcept
	{
		return m_handle;
	}

	VkImageViewCreateInfo
	ImageView::createInfo () const noexcept
	{
		return m_createInfo;
	}

	std::shared_ptr< Image >
	ImageView::image () const noexcept
	{
		return m_image;
	}
}
