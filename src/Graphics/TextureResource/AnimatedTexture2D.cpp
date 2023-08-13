/*
 * Emeraude/Graphics/TextureResource/AnimatedTexture2D.cpp
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

#include "AnimatedTexture2D.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/MovieResource.hpp"
#include "Vulkan/TransferManager.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::TextureResource::AnimatedTexture2D >::ClassId{"AnimatedTexture2DContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::TextureResource::AnimatedTexture2D >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::TextureResource
{
	using namespace Libraries;
	using namespace Vulkan;

	const size_t AnimatedTexture2D::ClassUID{Observable::getClassUID()};

	AnimatedTexture2D::AnimatedTexture2D (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Abstract(name, resourceFlagBits)
	{

	}

	AnimatedTexture2D::~AnimatedTexture2D ()
	{
		this->destroyFromHardware();
	}

	bool
	AnimatedTexture2D::isCreated () const noexcept
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
	AnimatedTexture2D::createOnHardware () noexcept
	{
		Tracer::error(ClassId, "Not yet implemented !");

		return false;
	}

	bool
	AnimatedTexture2D::destroyFromHardware () noexcept
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
	AnimatedTexture2D::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	AnimatedTexture2D::isGrayScale () const noexcept
	{
		if ( !this->isLoaded() )
			return false;

		return m_localData->isGrayScale();
	}

	PixelFactory::Color< float >
	AnimatedTexture2D::averageColor () const noexcept
	{
		if ( !this->isLoaded() )
			return PixelFactory::Black;

		return m_localData->averageColor();
	}

	uint32_t
	AnimatedTexture2D::dimensions () const noexcept
	{
		return 2;
	}

	bool
	AnimatedTexture2D::isCubemapTexture () const noexcept
	{
		return false;
	}

	size_t
	AnimatedTexture2D::frameCount () const noexcept
	{
		if ( !this->isLoaded() )
			return 0;

		return m_localData->frameCount();
	}

	size_t
	AnimatedTexture2D::duration () const noexcept
	{
		if ( !this->isLoaded() )
			return 0;

		return m_localData->duration();
	}

	const std::shared_ptr< Image > &
	AnimatedTexture2D::image () const noexcept
	{
		return m_image;
	}

	const std::shared_ptr< ImageView > &
	AnimatedTexture2D::imageView () const noexcept
	{
		return m_imageView;
	}

	const std::shared_ptr< Sampler > &
	AnimatedTexture2D::sampler () const noexcept
	{
		return m_sampler;
	}

	const char *
	AnimatedTexture2D::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	AnimatedTexture2D::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		m_localData = MovieResource::getDefault();

		if ( !this->addDependency(m_localData.get()) )
			return this->setLoadSuccess(false);

		return this->setLoadSuccess(true);
	}

	bool
	AnimatedTexture2D::load (const Path::File & filepath) noexcept
	{
		/* ie: "/foo/bar/datastores/Movies/test.png" -> "Movies/test.png" */
		const auto filename = String::right(to_string(filepath), std::string("Movies") + Path::Separator);
		const auto imageName = String::removeFileExtension(filename);

		return this->load(MovieResource::get(imageName, this->isDirectLoading()));
	}

	bool
	AnimatedTexture2D::load (const Json::Value &) noexcept
	{
		/* NOTE: This resouce has no local store,
		 * so this method won't be called from a resource container ! */
		Tracer::error(ClassId, "This type of resource is not intended to be loaded this way !");

		return false;
	}

	bool
	AnimatedTexture2D::load (const std::shared_ptr< MovieResource > & movieResource) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( movieResource == nullptr )
		{
			Tracer::error(ClassId, "The movie resource is an empty smart pointer !");

			return this->setLoadSuccess(false);
		}

		m_localData = movieResource;

		if ( !this->addDependency(m_localData.get()) )
		{
			TraceError{ClassId} << "Unable to add the movie '" << movieResource->name() << "' as dependency !";

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	std::shared_ptr< AnimatedTexture2D >
	AnimatedTexture2D::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->animatedTextures().getResource(resourceName, directLoad);
	}

	std::shared_ptr< AnimatedTexture2D >
	AnimatedTexture2D::getDefault () noexcept
	{
		return Resources::Manager::instance()->animatedTextures().getDefaultResource();
	}
}
