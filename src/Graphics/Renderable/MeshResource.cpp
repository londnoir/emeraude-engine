/*
 * src/Graphics/Renderable/MeshResource.cpp
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

#include "MeshResource.hpp"

/* Local inclusions. */
#include "Graphics/Geometry/IndexedVertexResource.hpp"
#include "Graphics/Geometry/VertexResource.hpp"
#include "Graphics/Material/BasicResource.hpp"
#include "Graphics/Material/StandardResource.hpp"
#include "Resources/Manager.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Renderable::MeshResource >::ClassId{"MeshContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Renderable::MeshResource >::ClassUID{getClassUID(ClassId)};

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Geometry;
	using namespace Material;

	const size_t MeshResource::ClassUID{getClassUID(ClassId)};

	MeshResource::MeshResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	size_t
	MeshResource::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	MeshResource::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	size_t
	MeshResource::layerCount () const noexcept
	{
		return m_layers.size();
	}

	bool
	MeshResource::isOpaque (size_t layerIndex) const noexcept
	{
		if ( layerIndex >= m_layers.size() )
		{
			TraceError{ClassId} << "MeshResource::isOpaque(), layer index " << layerIndex << " overflow on '" << this->name() << "' !";

			layerIndex = 0;
		}

		const auto materialResource = m_layers[layerIndex].material();

		if ( materialResource != nullptr )
		{
			return materialResource->isOpaque();
		}

		return true;
	}

	const Geometry::Interface *
	MeshResource::geometry () const noexcept
	{
		return m_geometry.get();
	}

	const Material::Interface *
	MeshResource::material (size_t layerIndex) const noexcept
	{
		if ( layerIndex >= m_layers.size() )
		{
			TraceError{ClassId} << "MeshResource::material(), layer index " << layerIndex << " overflow on '" << this->name() << "' !";

			layerIndex = 0;
		}

		return m_layers[layerIndex].material().get();
	}

	const RasterizationOptions *
	MeshResource::layerRasterizationOptions (size_t layerIndex) const noexcept
	{
		if ( layerIndex >= m_layers.size() )
		{
			TraceError{ClassId} << "MeshResource::layerRasterizationOptions(), layer index " << layerIndex << " overflow on '" << this->name() << "' !";

			return nullptr;
		}

		return &m_layers[layerIndex].rasterizationOptions();
	}

	const Cuboid< float > &
	MeshResource::boundingBox () const noexcept
	{
		if ( m_geometry == nullptr )
		{
			return NullBoundingBox;
		}

		return m_geometry->boundingBox();
	}

	const Sphere< float > &
	MeshResource::boundingSphere () const noexcept
	{
		if ( m_geometry == nullptr )
		{
			return NullBoundingSphere;
		}

		return m_geometry->boundingSphere();
	}

	const char *
	MeshResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	MeshResource::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		if ( !this->setGeometry(VertexResource::getDefault()) )
		{
			return this->setLoadSuccess(false);
		}

		if ( !this->setMaterial(BasicResource::getDefault(), {}, 0) )
		{
			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	std::shared_ptr< Geometry::Interface >
	MeshResource::parseGeometry (const Json::Value & data) noexcept
	{
		/* Checks geometry type key */
		if ( !data.isMember(GeometryTypeKey) || !data[GeometryTypeKey].isString() )
		{
			TraceError{ClassId} << "The key '" << GeometryTypeKey << "' is not present or not a string !";

			return nullptr;
		}

		/* Checks geometry resource name key */
		if ( !data.isMember(GeometryNameKey) || !data[GeometryNameKey].isString() )
		{
			TraceError{ClassId} << "The key '" << GeometryNameKey << "' is not present or not a string !";

			return nullptr;
		}

		/* Checks size option */
		if ( data.isMember(BaseSizeKey) )
		{
			if ( data[BaseSizeKey].isNumeric() )
			{
				m_baseSize = data[BaseSizeKey].asFloat();
			}
			else
			{
				TraceWarning{ClassId} << "The key '" << BaseSizeKey << "' must be numeric !";
			}
		}

		/* Gets the resource from geometry store. */
		const auto geometryType = data[GeometryTypeKey].asString();

		if ( geometryType == IndexedVertexResource::ClassId )
		{
			const auto geometryName = data[GeometryNameKey].asString();

			auto geometryResource = IndexedVertexResource::get(geometryName);

			if ( geometryResource == nullptr )
			{
				TraceError{ClassId} << "Geometry '" << geometryName << "' not found to complete the Mesh !";

				return nullptr;
			}

			return geometryResource;
		}

		TraceWarning{ClassId} << "Geometry resource type '" << geometryType << "' is not handled !";

		return nullptr;
	}

	RasterizationOptions
	MeshResource::parseLayerOptions (const Json::Value & data) noexcept
	{
		RasterizationOptions layerRasterizationOptions{};

		if ( data.isMember(EnableDoubleSidedFaceKey) && data[EnableDoubleSidedFaceKey].isBool() )
		{
			if ( data[EnableDoubleSidedFaceKey] )
			{
				layerRasterizationOptions.setCullingMode(CullingMode::None);
			}
			else
			{
				layerRasterizationOptions.setCullingMode(CullingMode::Back);
			}
		}

		if ( data.isMember(DrawingModeKey) && data[DrawingModeKey].isString() )
		{
			if ( data[DrawingModeKey] == "Fill" )
			{
				layerRasterizationOptions.setPolygonMode(PolygonMode::Fill);
			}
			else if ( data[DrawingModeKey] == "Line" )
			{
				layerRasterizationOptions.setPolygonMode(PolygonMode::Line);
			}
			else if ( data[DrawingModeKey] == "Point" )
			{
				layerRasterizationOptions.setPolygonMode(PolygonMode::Point);
			}
		}

		return layerRasterizationOptions;
	}

	std::shared_ptr< Material::Interface >
	MeshResource::parseLayer (const Json::Value & data) noexcept
	{
		if ( !data.isMember(MaterialTypeKey) || !data[MaterialTypeKey].isString() )
		{
			TraceError{ClassId} << "The key '" << MaterialTypeKey << "' is not present or not a string !";

			return StandardResource::getDefault();
		}

		if ( !data.isMember(MaterialNameKey) || !data[MaterialTypeKey].isString() )
		{
			TraceError{ClassId} << "The key '" << MaterialNameKey << "' is not present or not a string !";

			return StandardResource::getDefault();
		}

		/* Gets the resource from material store. */
		const auto materialType = data[MaterialTypeKey].asString();

		if ( materialType == StandardResource::ClassId )
		{
			const auto materialName = data[MaterialNameKey].asString();

			auto materialResource = StandardResource::get(materialName);

			if ( materialResource == nullptr )
			{
				TraceError{ClassId} << "Material '" << materialName << "' not found to complete sub-mesh !";

				return StandardResource::getDefault();
			}

			return materialResource;
		}

		TraceWarning{ClassId} << "Material resource type '" << materialType << "' is not handled !";

		return StandardResource::getDefault();
	}

	bool
	MeshResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		/* FIXME: Physics properties from Mesh definitions. */
		//this->parseOptions(data);

		/* Parse geometry definition. */
		const auto geometryResource = this->parseGeometry(data);

		if ( geometryResource == nullptr )
		{
			Tracer::error(ClassId, "No suitable geometry resource found !");

			return this->setLoadSuccess(false);
		}

		this->setGeometry(geometryResource);

		/* Checks layers array presence and content. */
		if ( !data.isMember(LayersKey) )
		{
			TraceError{ClassId} << "'" << LayersKey << "' key doesn't exist !";

			return this->setLoadSuccess(false);
		}

		const auto & layerRules = data[LayersKey];

		if ( !layerRules.isArray() )
		{
			TraceError{ClassId} << "'" << LayersKey << "' key must be a JSON array !";

			return this->setLoadSuccess(false);
		}

		if ( layerRules.empty() )
		{
			TraceError{ClassId} << "'" << LayersKey << "' array is empty !";

			return this->setLoadSuccess(false);
		}

		m_layers.clear();

		for ( const auto & layerRule : layerRules )
		{
			/* Parse material definition and get default if error occurs. */
			auto materialResource = MeshResource::parseLayer(layerRule);

			/* Gets a default material. */
			if ( materialResource == nullptr )
			{
				Tracer::error(ClassId, "No suitable material resource found !");

				return this->setLoadSuccess(false);
			}

			auto layerRasterizationOptions = MeshResource::parseLayerOptions(layerRule);

			if ( !this->addMaterial(materialResource, layerRasterizationOptions, 0) )
			{
				Tracer::error(ClassId, "Unable to add material layer !");

				return this->setLoadSuccess(false);
			}
		}

		return this->setLoadSuccess(true);
	}

	bool
	MeshResource::load (const std::shared_ptr< Geometry::Interface > & geometry, const std::shared_ptr< Material::Interface > & material, const RasterizationOptions & rasterizationOptions) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		/* 1. Check the geometry. */
		if ( geometry == nullptr )
		{
			TraceError{ClassId} << "Unable to set geometry for mesh '" << this->name() << "' !";

			return this->setLoadSuccess(false);
		}

		this->setGeometry(geometry);

		/* 2. Check the materials. */
		if ( material == nullptr )
		{
			TraceError{ClassId} << "Unable to set material for mesh '" << this->name() << "' !";

			return this->setLoadSuccess(false);
		}

		this->setMaterial(material, rasterizationOptions, 0);

		return this->setLoadSuccess(true);
	}

	bool
	MeshResource::load (const std::shared_ptr< Geometry::Interface > & geometry, const std::vector< std::shared_ptr< Material::Interface > > & materialList, const std::vector< RasterizationOptions > & /*rasterizationOptions*/) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		/* Check the geometry. */
		if ( geometry == nullptr )
		{
			TraceError{ClassId} << "Unable to set geometry for mesh '" << this->name() << "' !";

			return this->setLoadSuccess(false);
		}

		this->setGeometry(geometry);

		/* Check the materials. */
		m_layers.clear();

		for ( const auto & material : materialList )
		{
			if ( material == nullptr )
			{
				Tracer::error(ClassId, "One material of the list is empty !");

				return this->setLoadSuccess(false);
			}

			/* TODO: Find a better solution to load a multiple layer mesh. */
			this->addMaterial(material, {}, 0);
		}

		return this->setLoadSuccess(true);
	}

	bool
	MeshResource::setGeometry (const std::shared_ptr< Geometry::Interface > & geometry) noexcept
	{
		if ( geometry == nullptr )
		{
			TraceError{ClassId} << "Geometry pointer tried to be attached to renderable object '" << this->name() << "' " << this << " is null !";

			return false;
		}

		this->setReadyForInstantiation(false);

		m_geometry = geometry;

		return this->addDependency(m_geometry.get());
	}

	bool
	MeshResource::addMaterial (const std::shared_ptr< Material::Interface > & material, const RasterizationOptions & options, int flags) noexcept
	{
		if ( material == nullptr )
		{
			TraceError{ClassId} << "Material pointer tried to be attached to renderable object '" << this->name() << "' " << this << " is null !";

			return false;
		}

		this->setReadyForInstantiation(false);

		const auto layerName = (std::stringstream{} << "MeshLayer" << m_layers.size()).str();

		m_layers.emplace_back(layerName, material, options, flags);

		return this->addDependency(material.get());
	}

	float
	MeshResource::baseSize () const noexcept
	{
		return m_baseSize;
	}

	std::shared_ptr< MeshResource >
	MeshResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->meshes().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< MeshResource >
	MeshResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->meshes().getDefaultResource();
	}

	std::shared_ptr< MeshResource >
	MeshResource::getOrCreate (const std::shared_ptr< Geometry::Interface > & geometryResource, const std::shared_ptr< Material::Interface > & materialResource, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{
			resourceName = (std::stringstream{} << "Mesh(" << geometryResource->name() << ',' << materialResource->name() << ')').str();
		}

		return Resources::Manager::instance()->meshes().getOrCreateResource(resourceName, [&geometryResource, &materialResource] (MeshResource & newMesh) {
			return newMesh.load(geometryResource, materialResource);
		});
	}

	std::shared_ptr< MeshResource >
	MeshResource::getOrCreate (const std::shared_ptr< Geometry::Interface > & geometryResource, const std::vector< std::shared_ptr< Material::Interface > > & materialResources, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{
			std::stringstream output;

			output << "Mesh(" << geometryResource->name();

			for ( const auto & materialResource : materialResources )
			{
				output << ',' << materialResource->name();
			}

			output << ')';

			resourceName = output.str();
		}

		return Resources::Manager::instance()->meshes().getOrCreateResource(resourceName, [&geometryResource, &materialResources] (MeshResource & newMesh) {
			return newMesh.load(geometryResource, materialResources);
		});
	}
}
