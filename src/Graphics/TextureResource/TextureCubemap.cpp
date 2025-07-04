/*
 * src/Graphics/TextureResource/TextureCubemap.cpp
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

#include "TextureCubemap.hpp"

/* STL inclusions. */
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions. */
#include "Abstract.hpp"
#include "Graphics/ImageResource.hpp"
#include "Graphics/Renderer.hpp"
#include "Libs/PixelFactory/Color.hpp"
#include "Resources/Container.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"

/* Defining the resource manager class id. */
template<>
const char * const EmEn::Resources::Container< EmEn::Graphics::TextureResource::TextureCubemap >::ClassId{"TextureCubemapContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t EmEn::Resources::Container< EmEn::Graphics::TextureResource::TextureCubemap >::ClassUID{getClassUID(ClassId)};

namespace EmEn::Graphics::TextureResource
{
	using namespace EmEn::Libs;
	using namespace Vulkan;

	const size_t TextureCubemap::ClassUID{getClassUID(ClassId)};

	TextureCubemap::TextureCubemap (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Abstract(name, resourceFlagBits)
	{

	}

	TextureCubemap::~TextureCubemap ()
	{
		this->destroyFromHardware();
	}

	bool
	TextureCubemap::isCreated () const noexcept
	{
		if ( m_image == nullptr || !m_image->isCreated() )
		{
			return false;
		}

		if ( m_imageView == nullptr || !m_imageView->isCreated() )
		{
			return false;
		}

		if ( m_sampler == nullptr || !m_sampler->isCreated() )
		{
			return false;
		}

		return true;
	}

	bool
	TextureCubemap::createOnHardware (Renderer & renderer) noexcept
	{
		/* Create a Vulkan image. */
		m_image = std::make_shared< Image >(
			renderer.device(),
			VK_IMAGE_TYPE_2D,
			Image::getFormat< uint8_t >(m_localData->data(0).colorCount()),
			VkExtent3D{m_localData->cubeSize(), m_localData->cubeSize(), 1U},
			VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_CREATE_CUBE_COMPATIBLE_BIT, /* flags */
			1, /* mipLevels */
			static_cast< uint32_t >(CubemapFaceCount), /* arrayLayers */
			VK_SAMPLE_COUNT_1_BIT,
			VK_IMAGE_TILING_OPTIMAL
		);
		m_image->setIdentifier(ClassId, this->name(), "Image");

		if ( !m_image->create(renderer.transferManager(), m_localData) )
		{
			Tracer::error(ClassId, "Unable to create an image !");

			m_image.reset();

			return false;
		}

		/* Create a Vulkan image view. */
		m_imageView = std::make_shared< ImageView >(
			m_image,
			VK_IMAGE_VIEW_TYPE_CUBE,
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
			Tracer::error(ClassId, "Unable to create an image view !");

			return false;
		}

		/* Get a Vulkan sampler. */
		m_sampler = Renderer::instance()->getSampler(0, 0);
		m_sampler->setIdentifier(ClassId, this->name(), "Sampler");

		if ( m_sampler == nullptr )
		{
			Tracer::error(ClassId, "Unable to get a sampler !");

			return false;
		}

		return true;
	}

	bool
	TextureCubemap::destroyFromHardware () noexcept
	{
		if ( m_image != nullptr )
		{
			m_image->destroyFromHardware();
			m_image.reset();
		}

		if ( m_imageView != nullptr )
		{
			m_imageView->destroyFromHardware();
			m_imageView.reset();
		}

		if ( m_sampler != nullptr )
		{
			m_sampler->destroyFromHardware();
			m_sampler.reset();
		}

		return true;
	}

	size_t
	TextureCubemap::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	TextureCubemap::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	Type
	TextureCubemap::type () const noexcept
	{
		return Type::TextureCube;
	}

	bool
	TextureCubemap::isGrayScale () const noexcept
	{
		if ( !this->isLoaded() )
		{
			return false;
		}

		return m_localData->isGrayScale();
	}

	PixelFactory::Color< float >
	TextureCubemap::averageColor () const noexcept
	{
		if ( !this->isLoaded() )
		{
			return PixelFactory::Black;
		}

		return m_localData->averageColor();
	}

	uint32_t
	TextureCubemap::dimensions () const noexcept
	{
		return 3;
	}

	bool
	TextureCubemap::isCubemapTexture () const noexcept
	{
		return true;
	}

	uint32_t
	TextureCubemap::frameCount () const noexcept
	{
		if ( !this->isLoaded() )
		{
			return 0;
		}

		return static_cast< uint32_t >(CubemapFaceCount);
	}

	uint32_t
	TextureCubemap::duration () const noexcept
	{
		return 0;
	}

	uint32_t
	TextureCubemap::frameIndexAt (uint32_t /*sceneTime*/) const noexcept
	{
		return 0;
	}

	std::shared_ptr< Image >
	TextureCubemap::image () const noexcept
	{
		return m_image;
	}

	std::shared_ptr< ImageView >
	TextureCubemap::imageView () const noexcept
	{
		return m_imageView;
	}

	std::shared_ptr< Sampler >
	TextureCubemap::sampler () const noexcept
	{
		return m_sampler;
	}

	bool
	TextureCubemap::request3DTextureCoordinates () const noexcept
	{
		return true;
	}

	const char *
	TextureCubemap::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	TextureCubemap::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		m_localData = CubemapResource::getDefault();

		if ( !this->addDependency(m_localData) )
		{
			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	TextureCubemap::load (const std::filesystem::path & filepath) noexcept
	{
		return this->load(CubemapResource::get(getResourceNameFromFilepath(filepath, "Cubemaps"), true));
	}

	bool
	TextureCubemap::load (const Json::Value & /*data*/) noexcept
	{
		/* NOTE: This resource has no local store,
		 * so this method won't be called from a resource container ! */
		Tracer::error(ClassId, "This type of resource is not intended to be loaded this way !");

		return false;
	}

	bool
	TextureCubemap::load (const std::shared_ptr< CubemapResource > & cubemapResource) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		if ( cubemapResource == nullptr )
		{
			Tracer::error(ClassId, "The cubemap resource is an empty smart pointer !");

			return this->setLoadSuccess(false);
		}

		m_localData = cubemapResource;

		if ( !this->addDependency(m_localData) )
		{
			TraceError{ClassId} << "Unable to add the cubemap '" << cubemapResource->name() << "' as dependency !";

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	std::shared_ptr< TextureCubemap >
	TextureCubemap::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->textureCubemaps().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< TextureCubemap >
	TextureCubemap::getDefault () noexcept
	{
		return Resources::Manager::instance()->textureCubemaps().getDefaultResource();
	}
}
