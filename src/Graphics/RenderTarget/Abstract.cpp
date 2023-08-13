/*
 * Emeraude/Graphics/RenderTarget/Abstract.cpp
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

#include "Abstract.hpp"

/* Local inclusions. */
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Instance.hpp"

namespace Emeraude::Graphics::RenderTarget
{
	using namespace Libraries;
	using namespace Vulkan;

	constexpr auto TracerTag{"RenderTarget"};

	Abstract::Abstract (const std::string & name, const FramebufferPrecisions & precisions, const VkExtent3D & extent, RenderType renderType, MasterControl::ConnexionType allowedConnexionType) noexcept
		: MasterControl::AbstractVirtualVideoDevice(name, allowedConnexionType), m_precisions(precisions), m_extent(extent), m_renderType(renderType)
	{

	}

	void
	Abstract::setExtent (const VkExtent3D & extent) noexcept
	{
		m_extent = extent;
	}

	bool
	Abstract::isRenderOutOfDate () const noexcept
	{
		return m_flags[RenderOutOfDate];
	}

	bool
	Abstract::isAutomaticRendering () const noexcept
	{
		return m_flags[AutomaticRendering];
	}

	void
	Abstract::setAutomaticRenderingState (bool state) noexcept
	{
		m_flags[AutomaticRendering] = state;

		if ( this->isAutomaticRendering() )
		{
			m_flags[RenderOutOfDate] = true;
		}
	}

	void
	Abstract::setRenderOutOfDate () noexcept
	{
		if ( this->isAutomaticRendering() )
		{
			return;
		}

		m_flags[RenderOutOfDate] = true;
	}

	void
	Abstract::setRenderFinished () noexcept
	{
		if ( this->isAutomaticRendering() )
		{
			return;
		}

		m_flags[RenderOutOfDate] = false;
	}

	const FramebufferPrecisions &
	Abstract::precisions () const noexcept
	{
		return m_precisions;
	}

	const VkExtent3D &
	Abstract::extent () const noexcept
	{
		return m_extent;
	}

	RenderType
	Abstract::renderType () const noexcept
	{
		return m_renderType;
	}

	float
	Abstract::aspectRatio () const noexcept
	{
		if ( m_extent.height == 0 )
		{
			return 0.0F;
		}

		return static_cast< float >(m_extent.width) / static_cast< float >(m_extent.height);
	}

	bool
	Abstract::createColorBuffer (const std::shared_ptr< Device > & device, std::shared_ptr< Image > & image, std::shared_ptr< ImageView > & imageView, const std::string & purposeId) const noexcept
	{
		image = std::make_shared< Image >(
			device,
			VK_IMAGE_TYPE_2D,
			Instance::findDepthStencilFormat(device, this->precisions()),
			this->extent(),
			VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
			VK_IMAGE_LAYOUT_UNDEFINED,
			0, // flags
			1, // Image mip levels
			1, //m_createInfo.imageArrayLayers, // Image array layers
			VK_SAMPLE_COUNT_1_BIT, // Image multi sampling
			VK_IMAGE_TILING_OPTIMAL // Image tiling
		);
		image->setIdentifier(purposeId + "-Image");

		if ( !image->createOnHardware() )
		{
			TraceError{TracerTag} << "Unable to create image '" << purposeId << "' !";

			return false;
		}

		const auto & imageCreateInfo = image->createInfo();

		imageView = std::make_shared< ImageView >(
			image,
			VK_IMAGE_VIEW_TYPE_2D,
			VkImageSubresourceRange{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = imageCreateInfo.mipLevels,
				.baseArrayLayer = 0,
				.layerCount = imageCreateInfo.arrayLayers
			}
			);
		imageView->setIdentifier(purposeId + "-ImageView");

		if ( !imageView->createOnHardware() )
		{
			TraceFatal{TracerTag} << "Unable to create image view '" << purposeId << "' !";

			return false;
		}

		return true;
	}

	bool
	Abstract::createDepthBuffer (const std::shared_ptr< Device > & device, std::shared_ptr< Image > & image, std::shared_ptr< ImageView > & imageView, const std::string & purposeId) const noexcept
	{
		image = std::make_shared< Image >(
			device,
			VK_IMAGE_TYPE_2D,
			Instance::findDepthStencilFormat(device, this->precisions()),
			this->extent(),
			VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
			VK_IMAGE_LAYOUT_UNDEFINED,
			0, // flags
			1, // Image mip levels
			1, //m_createInfo.imageArrayLayers, // Image array layers
			VK_SAMPLE_COUNT_1_BIT, // Image multi sampling
			VK_IMAGE_TILING_OPTIMAL // Image tiling
		);
		image->setIdentifier(purposeId + "-Image");

		if ( !image->createOnHardware() )
		{
			TraceError{TracerTag} << "Unable to create image '" << purposeId << "' !";

			return false;
		}

		const auto & imageCreateInfo = image->createInfo();

		imageView = std::make_shared< ImageView >(
			image,
			VK_IMAGE_VIEW_TYPE_2D,
			VkImageSubresourceRange{
				.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
				.baseMipLevel = 0,
				.levelCount = imageCreateInfo.mipLevels,
				.baseArrayLayer = 0,
				.layerCount = imageCreateInfo.arrayLayers
			}
		);
		imageView->setIdentifier(purposeId + "D-ImageView");

		if ( !imageView->createOnHardware() )
		{
			TraceFatal{TracerTag} << "Unable to create image view '" << purposeId << "' !";

			return false;
		}

		return true;
	}

	bool
	Abstract::createDepthStencilBuffer (const std::shared_ptr< Device > & device, std::shared_ptr< Image > & image, std::shared_ptr< ImageView > & depthImageView, std::shared_ptr< ImageView > & stencilImageView, const std::string & purposeId) noexcept
	{
		if ( !this->createDepthBuffer(device, image, depthImageView, purposeId) )
		{
			return false;
		}

		const auto & imageCreateInfo = image->createInfo();

		stencilImageView = std::make_shared< ImageView >(
			image,
			VK_IMAGE_VIEW_TYPE_2D,
			VkImageSubresourceRange{
				.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
				.baseMipLevel = 0,
				.levelCount = imageCreateInfo.mipLevels,
				.baseArrayLayer = 0,
				.layerCount = imageCreateInfo.arrayLayers
			}
		);
		stencilImageView->setIdentifier(purposeId + "S-ImageView");

		if ( !stencilImageView->createOnHardware() )
		{
			TraceFatal{TracerTag} << "Unable to create image view '" << purposeId << "' !";

			return false;
		}

		return true;
	}
}
