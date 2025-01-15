/*
 * src/Graphics/Renderable/DynamicSkyResource.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "DynamicSkyResource.hpp"

/* Local inclusions. */
#include "Resources/Manager.hpp"
#include "Tracer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Renderable::DynamicSkyResource >::ClassId{"DynamicSkyContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Renderable::DynamicSkyResource >::ClassUID{getClassUID(ClassId)};

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Scenes;

	const size_t DynamicSkyResource::ClassUID{getClassUID(ClassId)};

	DynamicSkyResource::DynamicSkyResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: AbstractBackground(name, resourceFlagBits)
	{

	}

	size_t
	DynamicSkyResource::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	DynamicSkyResource::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	bool
	DynamicSkyResource::isOpaque (size_t /*layerIndex*/) const noexcept
	{
		return true;
	}

	size_t
	DynamicSkyResource::layerCount () const noexcept
	{
		return 1;
	}

	const Geometry::Interface *
	DynamicSkyResource::geometry () const noexcept
	{
		return m_geometry.get();
	}

	const Material::Interface *
	DynamicSkyResource::material (size_t) const noexcept
	{
		return m_material.get();
	}

	const RasterizationOptions *
	DynamicSkyResource::layerRasterizationOptions (size_t /*layerIndex*/) const noexcept
	{
		return nullptr;
	}

	const char *
	DynamicSkyResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	DynamicSkyResource::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		/* TODO: Empty function. */

		return this->setLoadSuccess(false);
	}

	bool
	DynamicSkyResource::load (const Json::Value &) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		/* TODO: Empty function. */

		return this->setLoadSuccess(false);
	}

	bool
	DynamicSkyResource::setGeometry (const std::shared_ptr< Geometry::Interface > & geometry) noexcept
	{
		if ( geometry == nullptr )
		{
			Tracer::error(ClassId, BlobTrait() << "Geometry pointer tried to be attached to renderable object '" << this->name() << "' " << this << " is null !");

			return false;
		}

		this->setReadyForInstantiation(false);

		m_geometry = geometry;

		return this->addDependency(m_geometry.get());
	}

	bool
	DynamicSkyResource::setMaterial (const std::shared_ptr< Material::Interface > & material) noexcept
	{
		if ( material == nullptr )
		{
			Tracer::error(ClassId, BlobTrait() << "Material pointer tried to be attached to renderable object '" << this->name() << "' " << this << " is null !");

			return false;
		}

		this->setReadyForInstantiation(false);

		m_material = material;

		return this->addDependency(m_material.get());
	}

	std::shared_ptr< DynamicSkyResource >
	DynamicSkyResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->dynamicSkies().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< DynamicSkyResource >
	DynamicSkyResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->dynamicSkies().getDefaultResource();
	}
}
