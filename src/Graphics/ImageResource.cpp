/*
 * src/Graphics/ImageResource.cpp
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

#include "ImageResource.hpp"

/* STL inclusions. */
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions. */
#include "Libraries/PixelFactory/Color.hpp"
#include "Libraries/PixelFactory/FileIO.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::ImageResource >::ClassId{"ImageContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::ImageResource >::ClassUID{getClassUID(ClassId)};

namespace Emeraude::Graphics
{
	using namespace Libraries;

	const size_t ImageResource::ClassUID{getClassUID(ClassId)};

	ImageResource::ImageResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	size_t
	ImageResource::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	ImageResource::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	const char *
	ImageResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	ImageResource::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		constexpr size_t size = 32;

		if ( !m_data.initialize(size, size, PixelFactory::ChannelMode::RGB) )
		{
			Tracer::error(ClassId, "Unable to load the default pixmap !");

			return this->setLoadSuccess(false);
		}

		if ( !m_data.fill(PixelFactory::Magenta) )
		{
			Tracer::error(ClassId, "Unable to fill the default pixmap !");

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	ImageResource::load (const std::filesystem::path & filepath) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		if ( !PixelFactory::FileIO::read(filepath, m_data) )
		{
			TraceError{ClassId} << "Unable to load the image file '" << filepath << "' !";

			return this->setLoadSuccess(false);
		}

		if ( !TextureResource::Abstract::validatePixmap(ClassId, m_data) )
		{
			TraceError{ClassId} << "Unable to use the pixmap from file '" << filepath << "' to create an image !";

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	ImageResource::load (const Json::Value & /*data*/) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		Tracer::error(ClassId, "This method can't be used !");

		return this->setLoadSuccess(false);
	}

	bool
	ImageResource::onDependenciesLoaded () noexcept
	{
		return true;
	}

	std::shared_ptr< ImageResource >
	ImageResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->images().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< ImageResource >
	ImageResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->images().getDefaultResource();
	}

	const PixelFactory::Pixmap< uint8_t > &
	ImageResource::data () const noexcept
	{
		return m_data;
	}

	uint32_t
	ImageResource::width () const noexcept
	{
		return static_cast< uint32_t >(m_data.width());
	}

	uint32_t
	ImageResource::height () const noexcept
	{
		return static_cast< uint32_t >(m_data.height());
	}

	bool
	ImageResource::isGrayScale () const noexcept
	{
		return m_data.isGrayScale();
	}

	PixelFactory::Color< float >
	ImageResource::averageColor () const noexcept
	{
		return m_data.averageColor();
	}
}
