/*
 * src/Graphics/TextureResource/Texture1D.cpp
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

#include "Texture1D.hpp"

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
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"
#include "Tracer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const EmEn::Resources::Container< EmEn::Graphics::TextureResource::Texture1D >::ClassId{"Texture1DContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t EmEn::Resources::Container< EmEn::Graphics::TextureResource::Texture1D >::ClassUID{getClassUID(ClassId)};

namespace EmEn::Graphics::TextureResource
{
	using namespace EmEn::Libs;
	using namespace Vulkan;

	const size_t Texture1D::ClassUID{getClassUID(ClassId)};

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
	Texture1D::createOnHardware (Renderer & /*renderer*/) noexcept
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

	size_t
	Texture1D::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	Texture1D::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	Type
	Texture1D::type () const noexcept
	{
		return Type::Texture1D;
	}

	bool
	Texture1D::isGrayScale () const noexcept
	{
		if ( m_localData == nullptr )
		{
			return false;
		}

		return m_localData->data().isGrayScale();
	}

	PixelFactory::Color< float >
	Texture1D::averageColor () const noexcept
	{
		if ( m_localData == nullptr )
		{
			return PixelFactory::Black;
		}

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

	uint32_t
	Texture1D::frameCount () const noexcept
	{
		if ( !this->isLoaded() )
		{
			return 0;
		}

		return 1;
	}

	uint32_t
	Texture1D::duration () const noexcept
	{
		return 0;
	}

	uint32_t
	Texture1D::frameIndexAt (uint32_t /*sceneTime*/) const noexcept
	{
		return 0;
	}

	std::shared_ptr< Image >
	Texture1D::image () const noexcept
	{
		return m_image;
	}

	std::shared_ptr< ImageView >
	Texture1D::imageView () const noexcept
	{
		return m_imageView;
	}

	std::shared_ptr< Sampler >
	Texture1D::sampler () const noexcept
	{
		return m_sampler;
	}

	bool
	Texture1D::request3DTextureCoordinates () const noexcept
	{
		return false;
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
		{
			return false;
		}

		m_localData = ImageResource::getDefault();

		if ( !this->addDependency(m_localData) )
		{
			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(false);
	}

	bool
	Texture1D::load (const std::filesystem::path & filepath) noexcept
	{
		return this->load(ImageResource::get(getResourceNameFromFilepath(filepath, "Images"), true));
	}

	bool
	Texture1D::load (const Json::Value & /*data*/) noexcept
	{
		/* NOTE: This resource has no local store,
		 * so this method won't be called from a resource container ! */
		Tracer::error(ClassId, "This type of resource is not intended to be loaded this way !");

		return false;
	}

	bool
	Texture1D::load (const std::shared_ptr< ImageResource > & imageResource) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		if ( imageResource == nullptr )
		{
			Tracer::error(ClassId, "The image resource is an empty smart pointer !");

			return this->setLoadSuccess(false);
		}

		m_localData = imageResource;

		if ( !this->addDependency(m_localData) )
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
		return Resources::Manager::instance()->texture1Ds().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< Texture1D >
	Texture1D::getDefault () noexcept
	{
		return Resources::Manager::instance()->texture1Ds().getDefaultResource();
	}
}
