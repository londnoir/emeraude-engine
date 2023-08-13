/*
 * Emeraude/Graphics/Renderable/WaterLevelResource.cpp
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

#include "WaterLevelResource.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Renderable::WaterLevelResource >::ClassId{"WaterLevelContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Renderable::WaterLevelResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;

	const size_t WaterLevelResource::ClassUID{Observable::getClassUID()};

	WaterLevelResource::WaterLevelResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: AbstractSeaLevel(name, resourceFlagBits)
	{

	}

	bool
	WaterLevelResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	size_t
	WaterLevelResource::layerCount () const noexcept
	{
		return 1;
	}

	bool
	WaterLevelResource::isOpaque (size_t) const noexcept
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
	WaterLevelResource::material (size_t) const noexcept
	{
		return m_material.get();
	}

	const Cuboid< float > &
	WaterLevelResource::boundingBox () const noexcept
	{
		if ( m_geometry == nullptr )
			return Interface::NullBoundingBox;

		return m_geometry->boundingBox();
	}

	const Sphere< float > &
	WaterLevelResource::boundingSphere () const noexcept
	{
		if ( m_geometry == nullptr )
			return Interface::NullBoundingSphere;

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
			return false;

		auto geometryResource = std::make_shared< Geometry::VertexGridResource >("DefaultWaterLevelGeometry");

		if ( !geometryResource->load(DefaultSize, DefaultDivision) )
		{
			TraceError{ClassId} << "Unable to create default GridGeometry to generate the default WaterLevel !";

			return this->setLoadSuccess(false);
		}

		if ( !this->setGeometry(geometryResource) )
			return this->setLoadSuccess(false);

		if ( !this->setMaterial(Material::BasicResource::getDefault()) )
			return this->setLoadSuccess(false);

		return this->setLoadSuccess(true);
	}

	bool
	WaterLevelResource::load (const Json::Value & /*data*/) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		/* TODO... */

		return this->setLoadSuccess(false);
	}

	bool
	WaterLevelResource::load (const std::shared_ptr< Geometry::VertexGridResource > & geometryResource, const std::shared_ptr< Material::Interface > & materialResource) noexcept
	{
		if ( !this->beginLoading() )
			return false;

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

		this->setReadyForInstanciation(false);

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

		this->setReadyForInstanciation(false);

		/* Change the material. */
		m_material = materialResource;

		/* Checks if all is loaded */
		return this->addDependency(m_material.get());
	}

	bool
	WaterLevelResource::prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept
	{
		TraceWarning{ClassId} << "Not done yet !";

		return false;
	}

	std::shared_ptr< WaterLevelResource >
	WaterLevelResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->waterLevels().getResource(resourceName, directLoad);
	}

	std::shared_ptr< WaterLevelResource >
	WaterLevelResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->waterLevels().getDefaultResource();
	}
}
