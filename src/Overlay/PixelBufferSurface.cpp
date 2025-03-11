/*
 * src/Overlay/PixelBufferSurface.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "PixelBufferSurface.hpp"

/* STL inclusions. */
#include <array>
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions. */
#include "AbstractSurface.hpp"
#include "FramebufferProperties.hpp"
#include "Libs/PixelFactory/Pixmap.hpp"
#include "Libs/Math/Rectangle.hpp"
#include "Libs/PixelFactory/Types.hpp"
#include "Graphics/Renderer.hpp"
#include "Tracer.hpp"
#include "Vulkan/DescriptorSet.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"
#include "Vulkan/MemoryRegion.hpp"
#include "Manager.hpp"

namespace EmEn::Overlay
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::Math;
	using namespace EmEn::Libs::PixelFactory;
	using namespace Graphics;
	using namespace Vulkan;

	PixelBufferSurface::PixelBufferSurface (const FramebufferProperties & framebufferProperties, const std::string & name, const Rectangle< float > & geometry, float depth) noexcept
		: AbstractSurface(framebufferProperties, name, geometry, depth)
	{

	}

	bool
	PixelBufferSurface::createDescriptorSet (Renderer & renderer) noexcept
	{
		const auto descriptorSetLayout = Manager::getDescriptorSetLayout(renderer.layoutManager());

		if ( descriptorSetLayout == nullptr )
		{
			TraceError{ClassId} << "Unable to get the overlay descriptor set layout for the surface '" << this->name() << "' !";

			return false;
		}

		m_descriptorSet = std::make_unique< DescriptorSet >(renderer.descriptorPool(), descriptorSetLayout);
		m_descriptorSet->setIdentifier(ClassId, this->name(), "DescriptorSet");

		if ( !m_descriptorSet->create() )
		{
			m_descriptorSet.reset();

			TraceError{ClassId} << "Unable to create the surface descriptor set for the surface '" << this->name() << "' !";

			return false;
		}

		if ( !m_descriptorSet->writeCombinedImageSampler(0, *m_image, *m_imageView, *m_sampler) )
		{
			TraceError{ClassId} << "Unable to write to the surface descriptor set of the surface '" << this->name() << "' !";

			return false;
		}

		return true;
	}

	bool
	PixelBufferSurface::createImage (Renderer & renderer) noexcept
	{
		if ( !m_localData.isValid() )
		{
			TraceError{ClassId} << "The local pixmap is invalid !";

			return false;
		}

		if ( m_image != nullptr && m_image->isCreated() )
		{
			TraceError{ClassId} << "The image is already created ! Destroy it before.";

			return false;
		}

		TraceInfo{ClassId} << "Creating an image of " << m_localData.width() << 'x' << m_localData.height() << "px on the GPU ...";

		const auto width = static_cast< uint32_t >(m_localData.width());
		const auto height = static_cast< uint32_t >(m_localData.height());

		m_image = std::make_shared< Image >(
			renderer.device(),
			VK_IMAGE_TYPE_2D,
			Image::getFormat< uint8_t >(m_localData.colorCount()),
			VkExtent3D{width, height, 1U},
			VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
			VK_IMAGE_LAYOUT_UNDEFINED,
			0,
			1,
			1,
			VK_SAMPLE_COUNT_1_BIT,
			VK_IMAGE_TILING_OPTIMAL
		);
		m_image->setIdentifier(ClassId, this->name(), "Image");

		if ( !m_image->create(renderer.transferManager(), m_localData) )
		{
			TraceError{ClassId} << "Unable to create the image for the surface '" << this->name() << "' !";

			m_image.reset();

			return false;
		}

		return true;
	}

	bool
	PixelBufferSurface::createImageView () noexcept
	{
		if ( m_imageView != nullptr && m_imageView->isCreated() )
		{
			TraceError{ClassId} << "The image view is created ! Destroy it before.";

			return false;
		}

		m_imageView = std::make_shared< ImageView >(
			m_image,
			VK_IMAGE_VIEW_TYPE_2D,
			VkImageSubresourceRange{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = m_image->createInfo().mipLevels,
				.baseArrayLayer = 0,
				.layerCount = m_image->createInfo().arrayLayers
			}
		);
		m_imageView->setIdentifier(ClassId, this->name(), "ImageView");

		if ( !m_imageView->createOnHardware() )
		{
			TraceError{ClassId} << "Unable to create the image view for the surface '" << this->name() << "' !";

			return false;
		}

		return true;
	}

	bool
	PixelBufferSurface::getSampler (Renderer & renderer) noexcept
	{
		if ( m_sampler != nullptr && m_sampler->isCreated() )
		{
			TraceError{ClassId} << "The sampler is created ! Destroy it before.";

			return false;
		}

		m_sampler = renderer.getSampler(0, 0);
		m_sampler->setIdentifier(ClassId, this->name(), "Sampler");

		if ( m_sampler == nullptr )
		{
			TraceError{ClassId} << "Unable to get a sampler for the surface '" << this->name() << "' !";

			return false;
		}

		TraceSuccess{ClassId} << "The sampler for the '" << this->name() << "' surface is created !";

		return true;
	}

	bool
	PixelBufferSurface::createOnHardware (Renderer & renderer) noexcept
	{
		const auto & framebuffer = this->framebufferProperties();
		const auto & geometry = this->geometry();

		const auto textureWidth = framebuffer.getSurfaceWidth(geometry.width());
		const auto textureHeight = framebuffer.getSurfaceHeight(geometry.height());

		if ( !m_localData.initialize(textureWidth, textureHeight, ChannelMode::RGBA) )
		{
			TraceError{ClassId} << "Unable to initialize a " << textureWidth << "x" << textureHeight << "px pixmap for the surface '" << this->name() << "' !";

			return false;
		}

		if ( !this->createImage(renderer) )
		{
			return false;
		}

		if ( !this->createImageView() )
		{
			return false;
		}

		if ( !this->getSampler(renderer) )
		{
			return false;
		}

		return this->createDescriptorSet(renderer);
	}

	bool
	PixelBufferSurface::onPhysicalRepresentationUpdate (Renderer & renderer) noexcept
	{
		const auto & framebuffer = this->framebufferProperties();
		const auto & geometry = this->geometry();

		const auto textureWidth = framebuffer.getSurfaceWidth(geometry.width());
		const auto textureHeight = framebuffer.getSurfaceHeight(geometry.height());

		if ( m_localData.width() == textureWidth && m_localData.height() == textureHeight )
		{
#ifdef DEBUG
			TraceInfo{ClassId} << "The surface '" << this->name() << "' already had the right dimensions.";
#endif

			return true;
		}

#ifdef DEBUG
		TraceDebug{ClassId} <<
			"Resizing the pixel buffer from " << m_localData.width() << 'x' << m_localData.height() << " "
			"to " << textureWidth << 'x' << textureHeight << " for the '" << this->name() << "' surface ...";
#endif

		if ( !m_localData.initialize(textureWidth, textureHeight, ChannelMode::RGBA) )
		{
			TraceError{ClassId} << "Unable to resize the pixmap for the surface '" << this->name() << "' !";

			return false;
		}

		/* First destroy the image and the image view from GPU first. */
		{
			m_descriptorSet->destroy();
			m_descriptorSet.reset();

			m_imageView->destroyFromHardware();
			m_imageView.reset();

			m_image->destroyFromHardware();
			m_image.reset();
		}

		/* Then recreate the framebuffer. */
		if ( !this->createImage(renderer) )
		{
			return false;
		}

		if ( !this->createImageView() )
		{
			return false;
		}

		return this->createDescriptorSet(renderer);
	}

	bool
	PixelBufferSurface::onVideoMemoryUpdate (Renderer & renderer) noexcept
	{
		return m_image->writeData(renderer.transferManager(), {m_localData.data().data(), m_localData.bytes()});
	}

	bool
	PixelBufferSurface::destroyFromHardware () noexcept
	{
		if ( m_descriptorSet != nullptr )
		{
			m_descriptorSet->destroy();
			m_descriptorSet.reset();
		}

		if ( m_sampler != nullptr )
		{
			m_sampler->destroyFromHardware();
			m_sampler.reset();
		}

		if ( m_imageView != nullptr )
		{
			m_imageView->destroyFromHardware();
			m_imageView.reset();
		}

		if ( m_image != nullptr )
		{
			m_image->destroyFromHardware();
			m_image.reset();
		}

		return true;
	}

	const DescriptorSet *
	PixelBufferSurface::descriptorSet () const noexcept
	{
		return m_descriptorSet.get();
	}
}
