/*
 * src/Graphics/FontResource.cpp
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

#include "FontResource.hpp"

/* STL inclusions. */
#include <bitset>

/* Local inclusions. */
#include "Libs/PixelFactory/DefaultFont.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const EmEn::Resources::Container< EmEn::Graphics::FontResource >::ClassId{"FontContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t EmEn::Resources::Container< EmEn::Graphics::FontResource >::ClassUID{getClassUID(ClassId)};

namespace EmEn::Graphics
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::PixelFactory;

	const size_t FontResource::ClassUID{getClassUID(ClassId)};

	FontResource::FontResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	bool
	FontResource::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		constexpr auto BitmapSize{256};

		const std::bitset< BitmapSize * BitmapSize > bitmap{DefaultFont};

		Pixmap< uint8_t > image{BitmapSize, BitmapSize, ChannelMode::RGBA};

		for ( size_t index = 0; index < bitmap.size(); index++ )
		{
			image.setPixel(index, bitmap[index] ? White : Black);
		}

		return this->setLoadSuccess(m_data.parsePixmap(image));
	}

	bool
	FontResource::load (const std::filesystem::path & filepath) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		return this->setLoadSuccess(m_data.readFile(filepath));
	}

	bool
	FontResource::load (const Json::Value & /*data*/) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		Tracer::warning(ClassId, "FIXME: This function is not available yet !");

		return this->setLoadSuccess(false);
	}

	bool
	FontResource::onDependenciesLoaded () noexcept
	{
		return true;
	}

	std::shared_ptr< FontResource >
	FontResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->fonts().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< FontResource >
	FontResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->fonts().getDefaultResource();
	}
}
