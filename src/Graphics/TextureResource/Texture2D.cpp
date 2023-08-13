/*
 * Emeraude/Graphics/TextureResource/Texture2D.cpp
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

#include "Texture2D.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/ImageResource.hpp"
#include "Vulkan/TransferManager.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::TextureResource::Texture2D >::ClassId{"Texture2DContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::TextureResource::Texture2D >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::TextureResource
{
	using namespace Libraries;
	using namespace Vulkan;

	const size_t Texture2D::ClassUID{Observable::getClassUID()};

	Texture2D::Texture2D (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Abstract(name, resourceFlagBits)
	{

	}

	Texture2D::~Texture2D ()
	{
		this->destroyFromHardware();
	}

	bool
	Texture2D::isCreated () const noexcept
	{
		if ( m_image == nullptr || !m_image->isCreated() )
			return false;

		if ( m_imageView == nullptr || !m_imageView->isCreated() )
			return false;

		if ( m_sampler == nullptr || !m_sampler->isCreated() )
			return false;

		return true;
	}

	bool
	Texture2D::createOnHardware () noexcept
	{
		auto transferManager = TransferManager::instance(TransferType::Graphics);

		/* Create a Vulkan image. */
		m_image = std::make_shared< Image >(
			transferManager->device(),
			VK_IMAGE_TYPE_2D,
			Image::getFormat(m_localData->data()),
			VkExtent3D{static_cast< uint32_t >(m_localData->width()), static_cast< uint32_t >(m_localData->height()), 1U},
			VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT,
			VK_IMAGE_LAYOUT_UNDEFINED,
			0, /* createFlags */
			1, /* mipLevels */
			1, /* arrayLayers */
			VK_SAMPLE_COUNT_1_BIT,
			VK_IMAGE_TILING_OPTIMAL
		);
		m_image->setIdentifier(this->name() + "-Main-Image");

		if ( !m_image->create(*transferManager, m_localData) )
		{
			Tracer::error(ClassId, "Unable to create an image !");

			m_image.reset();

			return false;
		}

		/* Create a Vulkan image view. */
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
		m_imageView->setIdentifier(this->name() + "-Main-ImageView");

		if ( !m_imageView->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create an image view !");

			return false;
		}

		/* Get a Vulkan sampler. */
		m_sampler = Renderer::instance()->getSampler(0, 0);
		m_sampler->setIdentifier(this->name() + "-Main-Sampler");

		if ( m_sampler == nullptr )
		{
			Tracer::error(ClassId, "Unable to get a sampler !");

			return false;
		}

		return true;
	}

	bool
	Texture2D::destroyFromHardware () noexcept
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

	bool
	Texture2D::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Texture2D::isGrayScale () const noexcept
	{
		if ( !this->isLoaded() )
			return false;

		return m_localData->data().isGrayScale();
	}

	PixelFactory::Color< float >
	Texture2D::averageColor () const noexcept
	{
		if ( !this->isLoaded() )
			return PixelFactory::Black;

		return m_localData->data().averageColor();
	}

	uint32_t
	Texture2D::dimensions () const noexcept
	{
		return 2;
	}

	bool
	Texture2D::isCubemapTexture () const noexcept
	{
		return false;
	}

	size_t
	Texture2D::frameCount () const noexcept
	{
		if ( !this->isLoaded() )
			return 0;

		return 1;
	}

	size_t
	Texture2D::duration () const noexcept
	{
		return 0;
	}

	const std::shared_ptr< Image > &
	Texture2D::image () const noexcept
	{
		return m_image;
	}

	const std::shared_ptr< ImageView > &
	Texture2D::imageView () const noexcept
	{
		return m_imageView;
	}

	const std::shared_ptr< Sampler > &
	Texture2D::sampler () const noexcept
	{
		return m_sampler;
	}

	const char *
	Texture2D::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	Texture2D::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		m_localData = ImageResource::getDefault();

		if ( !this->addDependency(m_localData.get()) )
			return this->setLoadSuccess(false);

		return this->setLoadSuccess(true);
	}

	bool
	Texture2D::load (const Path::File & filepath) noexcept
	{
		/* ie: "/foo/bar/datastores/Images/test.png" -> "Images/test.png" */
		const auto filename = String::right(to_string(filepath), std::string("Images") + Path::Separator);
		const auto imageName = String::removeFileExtension(filename);

		return this->load(ImageResource::get(imageName, this->isDirectLoading()));
	}

	bool
	Texture2D::load (const Json::Value &) noexcept
	{
		/* NOTE: This resouce has no local store,
		 * so this method won't be called from a resource container ! */
		Tracer::error(ClassId, "This type of resource is not intended to be loaded this way !");

		return false;
	}

	bool
	Texture2D::load (const std::shared_ptr< ImageResource > & imageResource) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( imageResource == nullptr )
		{
			Tracer::error(ClassId, "The image resource is an empty smart pointer !");

			return this->setLoadSuccess(false);
		}

		m_localData = imageResource;

		if ( !this->addDependency(m_localData.get()) )
		{
			TraceError{ClassId} << "Unable to add the image '" << imageResource->name() << "' as dependency !";

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	std::shared_ptr< ImageResource >
	Texture2D::localData () noexcept
	{
		return m_localData;
	}

	std::shared_ptr< Texture2D >
	Texture2D::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->texture2Ds().getResource(resourceName, directLoad);
	}

	std::shared_ptr< Texture2D >
	Texture2D::getDefault () noexcept
	{
		return Resources::Manager::instance()->texture2Ds().getDefaultResource();
	}
}
