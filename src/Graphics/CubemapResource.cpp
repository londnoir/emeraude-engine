/*
 * Emeraude/Graphics/CubemapResource.cpp
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

#include "CubemapResource.hpp"

/* Local inclusions */
#include "Graphics/TextureResource/Abstract.hpp"
#include "PixelFactory/FileIO.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::CubemapResource >::ClassId{"CubemapContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::CubemapResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics
{
	using namespace Libraries;
	using namespace Libraries::PixelFactory;

	const size_t CubemapResource::ClassUID{Observable::getClassUID()};

	CubemapResource::CubemapResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	bool
	CubemapResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	const char *
	CubemapResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	CubemapResource::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		constexpr size_t size = 32;

		const std::array< Color< float >, 6 > colors{
			Red, Cyan,
			Green, Magenta,
			Blue, Yellow
		};

		for ( size_t faceIndex = 0; faceIndex < 6; faceIndex++ )
		{
			if ( !m_data[faceIndex].initialize(size, size, ChannelMode::RGBA) )
			{
				TraceError{ClassId} << "Unable to load the default pixmap for face #" << faceIndex << " !";

				return this->setLoadSuccess(false);
			}

			if ( !m_data[faceIndex].fill(colors[faceIndex]) )
			{
				TraceError{ClassId} << "Unable to fill the default pixmap for face #" << faceIndex << " !";

				return this->setLoadSuccess(false);
			}
		}

		return this->setLoadSuccess(true);
	}

	bool
	CubemapResource::load (const Path::File & filepath) noexcept
	{
		/* Check for a JSON file. */
		if ( filepath.hasExtension("json") )
			return Resources::ResourceTrait::load(filepath);

		/* Tries to read the pixmap. */
		Pixmap< uint8_t > basemap{};

		if ( !FileIO::read(filepath, basemap) )
		{
			TraceError{ClassId} << "Unable to load the image file '" << filepath << "' !";

			return false;
		}

		return this->load(basemap);
	}

	bool
	CubemapResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		/* Checks file format. */
		if ( !data.isMember(FileFormatKey) || !data[FileFormatKey].isString() )
		{
			TraceError{ClassId} << "There is no valid '" << FileFormatKey << "' key in cubemap definition !";

			return this->setLoadSuccess(false);
		}

		const auto fileFormat = data[FileFormatKey].asString();

		/* Checks if cubemap is packed onto one image. */
		if ( !data.isMember(PackedKey) )
		{
			TraceError{ClassId} << "There is no '" << PackedKey << "' key in cubemap definition !";

			return this->setLoadSuccess(false);
		}

		if ( data[PackedKey].asBool() )
		{
			const auto filepath = Path::File{Resources::Stores::namedStore("Cubemaps"), this->name() + '.' + PackedKey + '.' + fileFormat};

			Pixmap< uint8_t > basemap{};

			if ( !FileIO::read(filepath, basemap) )
			{
				TraceError{ClassId} << "Unable to read the packed cubemap file '" << filepath << "' !";

				return this->setLoadSuccess(false);
			}

			return this->load(basemap);
		}
		else
		{
			for ( size_t faceIndex = 0; faceIndex < 6; faceIndex++ )
			{
				const auto filepath = Path::File{Resources::Stores::namedStore("Cubemaps"), this->name() + '.' + s_texturesName[faceIndex] + '.' + fileFormat};

				if ( !FileIO::read(filepath, m_data[faceIndex]) )
				{
					TraceError{ClassId} << "Unable to load plane '" << s_texturesName[faceIndex] << "' from file '" << filepath << "' !";

					return this->setLoadSuccess(false);
				}

				if ( !TextureResource::Abstract::validatePixmap(ClassId, m_data[faceIndex]) )
				{
					TraceError{ClassId} << "Unable to use the pixmap #" << faceIndex << " for face '" << s_texturesName[faceIndex] << "' to create a cubemap !";

					return this->setLoadSuccess(false);
				}
			}

			return this->setLoadSuccess(true);
		}
	}

	bool
	CubemapResource::load (const Pixmap< uint8_t > & pixmap) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !pixmap.isValid() )
		{
			Tracer::error(ClassId, "Unable to use this pixmap to create a cubemap !");

			return this->setLoadSuccess(false);
		}

		const auto width = static_cast< size_t >(pixmap.width() / 3);
		const auto height = static_cast< size_t >(pixmap.height() / 2);

		std::array< Area< size_t >, 6 > areas{{
			{0, height, width, height}, {0, 0, width, height}, /* PositiveX, NegativeX */
			{width, height, width, height}, {width, 0, width, height}, /* PositiveY, NegativeY */
			{width + width, height, width, height}, {width + width, 0, width, height} /* PositiveZ, NegativeZ */
		}};

		for ( size_t faceIndex = 0; faceIndex < 6; faceIndex++ )
		{
			m_data[faceIndex] = Processor< uint8_t >::crop(pixmap, areas[faceIndex]);

			if ( !TextureResource::Abstract::validatePixmap(ClassId, m_data[faceIndex]) )
			{
				TraceError{ClassId} << "Unable to use the pixmap #" << faceIndex << " for face '" << s_texturesName[faceIndex] << "' to create a cubemap !";

				return this->setLoadSuccess(false);
			}
		}

		return this->setLoadSuccess(false);
	}

	bool
	CubemapResource::load (const std::array< Pixmap< uint8_t >, 6 > & pixmaps) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		for ( size_t faceIndex = 0; faceIndex < 6; faceIndex++ )
		{
			m_data[faceIndex] = pixmaps[faceIndex];

			if ( !TextureResource::Abstract::validatePixmap(ClassId, m_data[faceIndex]) )
			{
				TraceError{ClassId} << "Unable to use the pixmap #" << faceIndex << " for face '" << s_texturesName[faceIndex] << "' to create a cubemap !";

				return this->setLoadSuccess(false);
			}
		}

		return this->setLoadSuccess(true);
	}

	bool
	CubemapResource::onDependenciesLoaded () noexcept
	{
		return true;
	}

	std::shared_ptr< CubemapResource >
	CubemapResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->cubemaps().getResource(resourceName, directLoad);
	}

	std::shared_ptr< CubemapResource >
	CubemapResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->cubemaps().getDefaultResource();
	}

	const Pixmap< uint8_t > &
	CubemapResource::data (size_t faceIndex) const noexcept
	{
		if ( faceIndex >= 6 )
		{
			Tracer::error(ClassId, "Face index overflow !");

			faceIndex = 0;
		}

		return m_data[faceIndex];
	}

	const std::array< Pixmap< uint8_t >, 6 > &
	CubemapResource::faces () const noexcept
	{
		return m_data;
	}

	size_t
	CubemapResource::size () const noexcept
	{
		return m_data[0].width();
	}

	bool
	CubemapResource::isGrayScale () const noexcept
	{
		return std::all_of(m_data.cbegin(), m_data.cend(), [] (const auto & pixmap) {
			if ( !pixmap.isValid() )
				return false;

			return pixmap.isGrayScale();
		});
	}

	Color< float >
	CubemapResource::averageColor () const noexcept
	{
		if ( !this->isLoaded() )
			return {};

		const auto ratio = 1.0F / 6.0F;

		auto red = 0.0F;
		auto green = 0.0F;
		auto blue = 0.0F;

		for ( const auto & face : m_data )
		{
			const auto averageColor = face.averageColor();

			red += averageColor.red() * ratio;
			green += averageColor.green() * ratio;
			blue += averageColor.blue() * ratio;
		}

		return {red, green, blue, 1.0F};
	}
}
