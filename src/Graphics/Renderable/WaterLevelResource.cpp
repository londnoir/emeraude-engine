/*
 * src/Graphics/Renderable/WaterLevelResource.cpp
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

#include "WaterLevelResource.hpp"

/* Local inclusions. */
#include "Resources/Manager.hpp"
#include "Graphics/Material/BasicResource.hpp"

/* Defining the resource manager class id. */
template<>
const char * const EmEn::Resources::Container< EmEn::Graphics::Renderable::WaterLevelResource >::ClassId{"WaterLevelContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t EmEn::Resources::Container< EmEn::Graphics::Renderable::WaterLevelResource >::ClassUID{getClassUID(ClassId)};

namespace EmEn::Graphics::Renderable
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::Math;

	const size_t WaterLevelResource::ClassUID{getClassUID(ClassId)};

	WaterLevelResource::WaterLevelResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: SeaLevelInterface(name, resourceFlagBits)
	{

	}

	size_t
	WaterLevelResource::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	WaterLevelResource::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	size_t
	WaterLevelResource::layerCount () const noexcept
	{
		return 1;
	}

	bool
	WaterLevelResource::isOpaque (size_t /*layerIndex*/) const noexcept
	{
		if ( m_material == nullptr )
			return true;

		return m_material->isOpaque();
	}

	const Geometry::Interface *
	WaterLevelResource::geometry () const noexcept
	{
		return m_geometry.get();
	}

	const Material::Interface *
	WaterLevelResource::material (size_t /*layerIndex*/) const noexcept
	{
		return m_material.get();
	}

	const RasterizationOptions *
	WaterLevelResource::layerRasterizationOptions (size_t /*layerIndex*/) const noexcept
	{
		return nullptr;
	}

	const Cuboid< float > &
	WaterLevelResource::boundingBox () const noexcept
	{
		if ( m_geometry == nullptr )
		{
			return NullBoundingBox;
		}

		return m_geometry->boundingBox();
	}

	const Sphere< float > &
	WaterLevelResource::boundingSphere () const noexcept
	{
		if ( m_geometry == nullptr )
		{
			return NullBoundingSphere;
		}

		return m_geometry->boundingSphere();
	}

	const char *
	WaterLevelResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	WaterLevelResource::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		const auto geometryResource = std::make_shared< Geometry::VertexGridResource >("DefaultWaterLevelGeometry");

		if ( !geometryResource->load(DefaultSize, DefaultDivision) )
		{
			TraceError{ClassId} << "Unable to create default GridGeometry to generate the default WaterLevel !";

			return this->setLoadSuccess(false);
		}

		if ( !this->setGeometry(geometryResource) )
		{
			return this->setLoadSuccess(false);
		}

		if ( !this->setMaterial(Material::BasicResource::getDefault()) )
		{
			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	WaterLevelResource::load (const Json::Value & /*data*/) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		/* TODO... */

		return this->setLoadSuccess(false);
	}

	bool
	WaterLevelResource::load (const std::shared_ptr< Geometry::VertexGridResource > & geometryResource, const std::shared_ptr< Material::Interface > & materialResource) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		/* 1. Check the grid geometry. */
		if ( !this->setGeometry(geometryResource) )
		{
			TraceError{ClassId} << "Unable to use grid geometry for WaterLevel '" << this->name() << "' !";

			return this->setLoadSuccess(false);
		}

		/* 2. Check the material. */
		if ( !this->setMaterial(materialResource) )
		{
			TraceError{ClassId} << "Unable to use material for WaterLevel '" << this->name() << "' !";

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	WaterLevelResource::setGeometry (const std::shared_ptr< Geometry::VertexGridResource > & geometryResource) noexcept
	{
		if ( geometryResource == nullptr )
		{
			TraceError{ClassId} <<
				"The geometry resource is null ! "
				"Unable to attach it to the renderable object '" << this->name() << "' " << this << ".";

			return false;
		}

		this->setReadyForInstantiation(false);

		/* Change the geometry. */
		m_geometry = geometryResource;

		/* Checks if all is loaded */
		return this->addDependency(m_geometry.get());
	}

	bool
	WaterLevelResource::setMaterial (const std::shared_ptr< Material::Interface > & materialResource) noexcept
	{
		if ( materialResource == nullptr )
		{
			TraceError{ClassId} <<
				"The material resource is null ! "
				"Unable to attach it to the renderable object '" << this->name() << "' " << this << ".";

			return false;
		}

		this->setReadyForInstantiation(false);

		/* Change the material. */
		m_material = materialResource;

		/* Checks if all is loaded */
		return this->addDependency(m_material.get());
	}

	std::shared_ptr< WaterLevelResource >
	WaterLevelResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->waterLevels().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< WaterLevelResource >
	WaterLevelResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->waterLevels().getDefaultResource();
	}
}
