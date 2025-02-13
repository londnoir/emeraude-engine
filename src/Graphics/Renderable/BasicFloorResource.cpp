/*
 * src/Graphics/Renderable/BasicFloorResource.cpp
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

#include "BasicFloorResource.hpp"

/* STL inclusions. */
#include <fstream>

/* Local inclusions. */
#include "Libraries/FastJSON.hpp"
#include "Resources/Manager.hpp"
#include "Graphics/Material/StandardResource.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Renderable::BasicFloorResource >::ClassId{"BasicFloorContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Renderable::BasicFloorResource >::ClassUID{getClassUID(ClassId)};

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::VertexFactory;
	using namespace Scenes;

	const size_t BasicFloorResource::ClassUID{getClassUID(ClassId)};

	BasicFloorResource::BasicFloorResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: SceneAreaInterface(name, resourceFlagBits)
	{

	}

	size_t
	BasicFloorResource::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	BasicFloorResource::is (size_t classUID) const noexcept
	{
		return classUID == ClassUID;
	}

	size_t
	BasicFloorResource::layerCount () const noexcept
	{
		return 1;
	}

	bool
	BasicFloorResource::isOpaque (size_t /*layerIndex*/) const noexcept
	{
		if ( m_material != nullptr )
		{
			return m_material->isOpaque();
		}

		return true;
	}

	const Geometry::Interface *
	BasicFloorResource::geometry () const noexcept
	{
		return m_geometry.get();
	}

	const Material::Interface *
	BasicFloorResource::material (size_t /*layerIndex*/) const noexcept
	{
		return m_material.get();
	}

	const RasterizationOptions *
	BasicFloorResource::layerRasterizationOptions (size_t /*layerIndex*/) const noexcept
	{
		return nullptr;
	}

	const Cuboid< float > &
	BasicFloorResource::boundingBox () const noexcept
	{
		if ( m_geometry == nullptr )
		{
			return NullBoundingBox;
		}

		return m_geometry->boundingBox();
	}

	const Sphere< float > &
	BasicFloorResource::boundingSphere () const noexcept
	{
		if ( m_geometry == nullptr )
		{
			return NullBoundingSphere;
		}

		return m_geometry->boundingSphere();
	}

	float
	BasicFloorResource::getLevelAt (const Vector< 3, float > & worldPosition) const noexcept
	{
		/* NOTE: If no geometry available,
		 * we send the -Y boundary limit. */
		if ( m_geometry == nullptr )
		{
			return 0.0F;
		}

		return m_geometry->localData().getHeightAt(worldPosition[X], worldPosition[Z]);
	}

	Vector< 3, float >
	BasicFloorResource::getLevelAt (float positionX, float positionZ, float deltaY) const noexcept
	{
		/* NOTE: If no geometry available,
		 * we send the -Y boundary limit. */
		if ( m_geometry == nullptr )
		{
			return {positionX, 0.0F + deltaY, positionZ};
		}

		return {positionX, m_geometry->localData().getHeightAt(positionX, positionZ) + deltaY, positionZ};
	}

	Vector< 3, float >
	BasicFloorResource::getNormalAt (const Vector< 3, float > & worldPosition) const noexcept
	{
		/* NOTE: If no geometry available,
		 * we send a y+ normal vector. */
		if ( m_geometry == nullptr )
		{
			return Vector< 3, float >::positiveY();
		}

		return m_geometry->localData().getNormalAt(worldPosition[X], worldPosition[Z]);
	}

	const char *
	BasicFloorResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	BasicFloorResource::load () noexcept
	{
		/* 1. Creating a default GridGeometry. */
		const auto defaultGeometry = std::make_shared< Geometry::VertexGridResource >("DefaultBasicFloorGeometry");

		if ( !defaultGeometry->load(DefaultSize, DefaultDivision) )
		{
			TraceError{ClassId} << "Unable to create default GridGeometry to generate the default BasicFloor !";

			return this->setLoadSuccess(false);
		}

		/* 2. Retrieving the default material. */
		const auto defaultMaterial = Material::StandardResource::getDefault();

		if ( defaultMaterial == nullptr )
		{
			TraceError{ClassId} << "Unable to get default Material to generate the default BasicFloor !";

			return this->setLoadSuccess(false);
		}

		/* 3. Use the common func. */
		return this->load(defaultGeometry, defaultMaterial);
	}

	bool
	BasicFloorResource::load (const std::filesystem::path & filepath) noexcept
	{
		Json::Value root;

	    if ( !FastJSON::getRootFromFile(filepath, root) )
		{
		    TraceError{ClassId} << "Unable to parse the resource file " << filepath << " !" "\n";

			return this->setLoadSuccess(false);
		}

		/* Checks if additional stores before loading (optional) */
		Resources::Manager::instance()->stores().update(root);

		if ( !root.isMember(DefinitionResource::SceneAreaKey) )
		{
			TraceError{ClassId} << "The key '" << DefinitionResource::SceneAreaKey << "' is not present !";

			return this->setLoadSuccess(false);
		}

		auto sceneAreaObject = root[DefinitionResource::SceneAreaKey];

		if ( !sceneAreaObject.isMember(FastJSON::TypeKey) && !sceneAreaObject[FastJSON::TypeKey].isString() )
		{
			TraceError{ClassId} << "The key '" << FastJSON::TypeKey << "' is not present or not a string !";

			return this->setLoadSuccess(false);
		}

		if ( sceneAreaObject[FastJSON::TypeKey].asString() != ClassId || !sceneAreaObject.isMember(FastJSON::DataKey) )
		{
			TraceError{ClassId} << "This file doesn't contains a BasicFloor definition !";

			return this->setLoadSuccess(false);
		}

		return this->load(sceneAreaObject[FastJSON::DataKey]);
	}

	bool
	BasicFloorResource::load (const Json::Value & data) noexcept
	{
		auto * resources = Resources::Manager::instance();

		/* 1. Creating a geometry. */
		/* Checks size option. */
		if ( !data.isMember(SizeKey) || !data[SizeKey].isNumeric() )
		{
			TraceError{ClassId} << "The key '" << SizeKey << "' is not present or not numeric !";

			return this->setLoadSuccess(false);
		}

		/* Checks division option. */
		if ( !data.isMember(DivisionKey) || !data[DivisionKey].isNumeric() )
		{
			TraceError{ClassId} << "The key '" << DivisionKey << "' is not present or not numeric !";

			return this->setLoadSuccess(false);
		}

		const auto geometryResource = std::make_shared< Geometry::VertexGridResource >(this->name() + "Geometry");

		if ( !geometryResource->load(data[SizeKey].asFloat(), data[DivisionKey].asUInt(), DefaultGeometryFlags) )
		{
			TraceError{ClassId} << "Unable to create GridGeometry to generate the BasicFloor !";

			return this->setLoadSuccess(false);
		}

		/* 2. Check for geometry options. */
		if ( data.isMember(HeightMapKey) )
		{
			const auto & subData = data[HeightMapKey];

			if ( subData.isMember(ImageNameKey) && subData[ImageNameKey].isString() )
			{
				const auto imageName = subData[ImageNameKey].asString();

				const auto imageResource = resources->images().getResource(imageName);

				if ( imageResource != nullptr )
				{
					/* Color inversion if requested. */
					auto inverse = false;

					if ( subData.isMember(InverseKey) )
					{
						inverse = subData[InverseKey].asBool();
					}

					/* Checks for scaling. */
					auto scale = 1.0F;

					if ( subData.isMember(ScaleKey) )
					{
						if ( subData[ScaleKey].isNumeric() )
						{
							scale = subData[ScaleKey].asFloat();
						}
						else
						{
							TraceWarning{ClassId} << "The key '" << ScaleKey << "' is not numeric !";
						}
					}

					/* Applies the height map on the geometry. */
					geometryResource->localData().applyDisplacementMapping(imageResource->data(), inverse ? -scale : scale);
				}
				else
				{
					TraceWarning{ClassId} << "Image '" << imageName << "' is not available in data stores !";
				}
			}
			else
			{
				TraceWarning{ClassId} << "The key '" << ImageNameKey << "' is not present or not a string !";
			}
		}

		/* 3. Check material properties. */
		if ( !data.isMember(MaterialTypeKey) || !data[MaterialTypeKey].isString() )
		{
			TraceError{ClassId} << "The key '" << MaterialTypeKey << "' is not present or not a string !";

			return this->setLoadSuccess(false);
		}

		if ( !data.isMember(MaterialNameKey) || !data[MaterialTypeKey].isString() )
		{
			TraceError{ClassId} << "The key '" << MaterialNameKey << "' is not present or not a string !";

			return this->setLoadSuccess(false);
		}

		/* Checks if the UV multiplier parameter. */
		if ( data.isMember(UVMultiplierKey) )
		{
			if ( data[UVMultiplierKey].isNumeric() )
			{
				geometryResource->localData().setUVMultiplier(data[UVMultiplierKey].asFloat());
			}
			else
			{
				TraceWarning{ClassId} << "The key '" << UVMultiplierKey << "' is not numeric !";
			}
		}

		/* Gets the resource from geometry store. */
		std::shared_ptr< Material::Interface > materialResource;

		const auto materialType = data[MaterialTypeKey].asString();

		if ( materialType == Material::StandardResource::ClassId )
		{
			materialResource = resources->standardMaterials().getResource(data[MaterialNameKey].asString());
		}
		else
		{
			TraceWarning{ClassId} << "Material resource type '" << materialType << "' is not handled !";
		}

		/* 3. Use the common func. */
		return this->load(geometryResource, materialResource);
	}

	bool
	BasicFloorResource::load (const std::shared_ptr< Geometry::VertexGridResource > & geometry, const std::shared_ptr< Material::Interface > & material) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		/* 1. Check the grid geometry. */
		if ( !this->setGeometry(geometry) )
		{
			TraceError{ClassId} << "Unable to set grid geometry for basic floor '" << this->name() << "' !";

			return this->setLoadSuccess(false);
		}

		/* 2. Check the material. */
		if ( !this->setMaterial(material) )
		{
			TraceError{ClassId} << "Unable to set material for basic floor '" << this->name() << "' !";

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	BasicFloorResource::load (float size, size_t division, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier) noexcept
	{
		const auto geometryResource = std::make_shared< Geometry::VertexGridResource >(this->name() + "GridGeometry", DefaultGeometryFlags);

		if ( !geometryResource->load(size, division, UVMultiplier) )
		{
			Tracer::error(ClassId, "Unable to generate a basic floor geometry !");

			return false;
		}

		return this->load(geometryResource, materialResource);
	}

	bool
	BasicFloorResource::loadDiamondSquare (float size, size_t division, float factor, unsigned int seed, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier) noexcept
	{
		Grid< float > grid{};

		if ( grid.initializeData(size, division) )
		{
			grid.setUVMultiplier(UVMultiplier);
			grid.applyDiamondSquare(factor, seed);
		}
		else
		{
			Tracer::error(ClassId, "Unable to generate a grid shape !");

			return false;
		}

		/* Create the geometry resource from the shape. */
		const auto geometryResource = std::make_shared< Geometry::VertexGridResource >(this->name() + "GridGeometryDiamondSquare", DefaultGeometryFlags);

		if ( !geometryResource->load(grid) )
		{
			Tracer::error(ClassId, "Unable to generate a basic floor geometry !");

			return false;
		}

		return this->load(geometryResource, materialResource);
	}

	bool
	BasicFloorResource::loadPerlinNoise (float size, size_t division, float noiseSize, float noiseFactor, const std::shared_ptr< Material::Interface > & materialResource, float UVMultiplier) noexcept
	{
		Grid< float > grid{};

		if ( grid.initializeData(size, division) )
		{
			grid.setUVMultiplier(UVMultiplier);
			grid.applyPerlinNoise(noiseSize, noiseFactor);
		}
		else
		{
			Tracer::error(ClassId, "Unable to generate a grid shape !");

			return false;
		}

		/* Create the geometry resource from the shape. */
		const auto geometryResource = std::make_shared< Geometry::VertexGridResource >(this->name() + "GridGeometryPerlinNoise", DefaultGeometryFlags);

		if ( !geometryResource->load(grid) )
		{
			Tracer::error(ClassId, "Unable to generate a basic floor geometry !");

			return false;
		}

		return this->load(geometryResource, materialResource);
	}

	bool
	BasicFloorResource::setGeometry (const std::shared_ptr< Geometry::VertexGridResource > & geometryResource) noexcept
	{
		if ( geometryResource == nullptr )
		{
			TraceError{ClassId} << "Geometry pointer tried to be attached to renderable object '" << this->name() << "' " << this << " is null !";

			return false;
		}

		this->setReadyForInstantiation(false);

		m_geometry = geometryResource;

		return this->addDependency(m_geometry.get());
	}

	bool
	BasicFloorResource::setMaterial (const std::shared_ptr< Material::Interface > & materialResource) noexcept
	{
		if ( materialResource == nullptr )
		{
			TraceError{ClassId} << "Material pointer tried to be attached to renderable object '" << this->name() << "' " << this << " is null !";

			return false;
		}

		this->setReadyForInstantiation(false);

		m_material = materialResource;

		return this->addDependency(m_material.get());
	}

	std::shared_ptr< BasicFloorResource >
	BasicFloorResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->basicFloors().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< BasicFloorResource >
	BasicFloorResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->basicFloors().getDefaultResource();
	}
}
