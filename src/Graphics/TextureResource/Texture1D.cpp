/*
 * Emeraude/Graphics/TextureResource/Texture1D.cpp
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

#include "Texture1D.hpp"

/* Local inclusions */
#include "Graphics/ImageResource.hpp"
#include "Graphics/Renderer.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"
#include "Vulkan/TransferManager.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::TextureResource::Texture1D >::ClassId{"Texture1DContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::TextureResource::Texture1D >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::TextureResource
{
	using namespace Libraries;
	using namespace Vulkan;

	const size_t Texture1D::ClassUID{Observable::getClassUID()};

	Texture1D::Texture1D (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Abstract(name, resourceFlagBits)
	{

	}

	Texture1D::~Texture1D ()
	{
		this->destroyFromHardware();
	}

	bool
	Texture1D::isCreated () const noexcept
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
	Texture1D::createOnHardware () noexcept
	{
		Tracer::error(ClassId, "Not yet implemented !");

		return false;
	}

	bool
	Texture1D::destroyFromHardware () noexcept
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
	Texture1D::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Texture1D::isGrayScale () const noexcept
	{
		if ( m_localData == nullptr )
			return false;

		return m_localData->data().isGrayScale();
	}

	PixelFactory::Color< float >
	Texture1D::averageColor () const noexcept
	{
		if ( m_localData == nullptr )
			return PixelFactory::Black;

		return m_localData->data().averageColor();
	}

	uint32_t
	Texture1D::dimensions () const noexcept
	{
		return 1;
	}

	bool
	Texture1D::isCubemapTexture () const noexcept
	{
		return false;
	}

	size_t
	Texture1D::frameCount () const noexcept
	{
		if ( !this->isLoaded() )
			return 0;

		return 1;
	}

	size_t
	Texture1D::duration () const noexcept
	{
		return 0;
	}

	const std::shared_ptr< Image > &
	Texture1D::image () const noexcept
	{
		return m_image;
	}

	const std::shared_ptr< ImageView > &
	Texture1D::imageView () const noexcept
	{
		return m_imageView;
	}

	const std::shared_ptr< Sampler > &
	Texture1D::sampler () const noexcept
	{
		return m_sampler;
	}

	const char *
	Texture1D::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	Texture1D::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		m_localData = ImageResource::getDefault();

		if ( !this->addDependency(m_localData.get()) )
			return this->setLoadSuccess(false);

		return this->setLoadSuccess(false);
	}

	bool
	Texture1D::load (const Path::File & filepath) noexcept
	{
		/* ie: "/foo/bar/datastores/Images/test.png" -> "Images/test.png" */
		const auto filename = String::right(to_string(filepath), std::string("Images") + Path::Separator);
		const auto imageName = String::removeFileExtension(filename);

		return this->load(ImageResource::get(imageName, this->isDirectLoading()));
	}

	bool
	Texture1D::load (const Json::Value &) noexcept
	{
		/* NOTE: This resouce has no local store,
		 * so this method won't be called from a resource container ! */
		Tracer::error(ClassId, "This type of resource is not intended to be loaded this way !");

		return false;
	}

	bool
	Texture1D::load (const std::shared_ptr< ImageResource > & imageResource) noexcept
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
	Texture1D::localData () noexcept
	{
		return m_localData;
	}

	std::shared_ptr< Texture1D >
	Texture1D::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->texture1Ds().getResource(resourceName, directLoad);
	}

	std::shared_ptr< Texture1D >
	Texture1D::getDefault () noexcept
	{
		return Resources::Manager::instance()->texture1Ds().getDefaultResource();
	}
}
