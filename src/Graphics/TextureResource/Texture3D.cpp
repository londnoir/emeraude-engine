/*
 * Emeraude/Graphics/TextureResource/Texture3D.cpp
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

#include "Texture3D.hpp"

/* Local inclusions */
#include "Resources/Manager.hpp"
#include "Tracer.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::TextureResource::Texture3D >::ClassId{"Texture3DContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::TextureResource::Texture3D >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::TextureResource
{
	using namespace Libraries;
	using namespace Vulkan;

	const size_t Texture3D::ClassUID{Observable::getClassUID()};

	Texture3D::Texture3D (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Abstract(name, resourceFlagBits)
	{

	}

	Texture3D::~Texture3D ()
	{
		this->destroyFromHardware();
	}

	bool
	Texture3D::isCreated () const noexcept
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
	Texture3D::createOnHardware () noexcept
	{
		Tracer::error(ClassId, "Not yet implemented !");

		return false;
	}

	bool
	Texture3D::destroyFromHardware () noexcept
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
	Texture3D::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Texture3D::isGrayScale () const noexcept
	{
		/* FIXME: No local data for now. */
		return false;
	}

	PixelFactory::Color< float >
	Texture3D::averageColor () const noexcept
	{
		/* FIXME: No local data for now. */
		return PixelFactory::Black;
	}

	uint32_t
	Texture3D::dimensions () const noexcept
	{
		return 3;
	}

	bool
	Texture3D::isCubemapTexture () const noexcept
	{
		return false;
	}

	size_t
	Texture3D::frameCount () const noexcept
	{
		if ( !this->isLoaded() )
			return 0;

		return 1;
	}

	size_t
	Texture3D::duration () const noexcept
	{
		return 0;
	}

	const std::shared_ptr< Image > &
	Texture3D::image () const noexcept
	{
		return m_image;
	}

	const std::shared_ptr< ImageView > &
	Texture3D::imageView () const noexcept
	{
		return m_imageView;
	}

	const std::shared_ptr< Sampler > &
	Texture3D::sampler () const noexcept
	{
		return m_sampler;
	}

	const char *
	Texture3D::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	Texture3D::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		constexpr size_t size = 32;

		m_localData.resize(size * size * size * 4);

		for ( size_t x = 0; x < size; x++ )
		{
			for ( size_t y = 0; y < size; y++ )
			{
				for ( size_t z = 0; z < size; z++ )
				{
					const auto index = (x * y * size) * z;

					m_localData[index] = x * 8;
					m_localData[index+1] = y * 8;
					m_localData[index+2] = z * 8;
					m_localData[index+3] = 255;
				}
			}
		}

		return this->setLoadSuccess(false);
	}

	bool
	Texture3D::load (const Path::File & filepath) noexcept
	{
		/* ie: "/foo/bar/datastores/Images/test.png" -> "Images/test.png" */
		const auto filename = String::right(to_string(filepath), std::string("Images") + Path::Separator);
		const auto imageName = String::removeFileExtension(filename);

		return this->load(ImageResource::get(imageName, this->isDirectLoading()));
	}

	bool
	Texture3D::load (const Json::Value &) noexcept
	{
		/* NOTE: This resouce has no local store,
		 * so this method won't be called from a resource container ! */
		Tracer::error(ClassId, "This type of resource is not intended to be loaded this way !");

		return false;
	}

	bool
	Texture3D::load (const std::shared_ptr< ImageResource > & imageResource) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( imageResource == nullptr )
		{
			Tracer::error(ClassId, "The image resource is an empty smart pointer !");

			return this->setLoadSuccess(false);
		}

		Tracer::warning(ClassId, "This function is not available yet !");

		/*m_localData = imageResource;

		if ( !this->addDependency(m_localData.get()) )
		{
			TraceError{ClassId} << "Unable to add the image '" << imageResource->name() << "' as dependency !";

			return this->setLoadSuccess(false);
		}*/

		return this->setLoadSuccess(true);
	}

	std::shared_ptr< Texture3D >
	Texture3D::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->texture3Ds().getResource(resourceName, directLoad);
	}

	std::shared_ptr< Texture3D >
	Texture3D::getDefault () noexcept
	{
		return Resources::Manager::instance()->texture3Ds().getDefaultResource();
	}
}
