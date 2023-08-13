/*
 * Emeraude/Graphics/Renderable/TerrainResource.cpp
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

#include "TerrainResource.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "Scenes/Node.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Renderable::TerrainResource >::ClassId{"TerrainContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Renderable::TerrainResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::VertexFactory;
	using namespace Scenes;

	const size_t TerrainResource::ClassUID{Observable::getClassUID()};

	TerrainResource::TerrainResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: AbstractSceneArea(name, resourceFlagBits),
		  m_geometry(std::make_unique< Geometry::AdaptiveVertexGridResource >(name + "AdaptiveGrid"))
	{

	}

	bool
	TerrainResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	size_t
	TerrainResource::layerCount () const noexcept
	{
		return 1;
	}

	bool
	TerrainResource::isOpaque (size_t) const noexcept
	{
		if ( m_material != nullptr )
			return m_material->isOpaque();

		return true;
	}

	const Geometry::Interface *
	TerrainResource::geometry () const noexcept
	{
		return m_geometry.get();
	}

	const Material::Interface *
	TerrainResource::material (size_t) const noexcept
	{
		return m_material.get();
	}

	const Cuboid< float > &
	TerrainResource::boundingBox () const noexcept
	{
		return m_localData.boundingBox();
	}

	const Sphere< float > &
	TerrainResource::boundingSphere () const noexcept
	{
		return m_localData.boundingSphere();
	}

	/*void
	Terrain::updateVisibility (const Coordinates< float > & coordinates) noexcept
	{
		/ * Checks if the current position still close to the center of subdata. * /
		const auto position = coordinates.position();

		/ * Creates a new visible grid if position overlap the limit of the existing one. * /
		if ( Vector< 3, float >::distance(m_lastUpdatePosition, position) > m_geometry->getMinimalUpdateDistance() )
		{
			if ( !m_updatingActiveGeometryProcess )
			{
				m_lastUpdatePosition = position;

				std::thread process(&Terrain::updateActiveGeometryProcess, this);

				process.detach();
			}
			else
			{
				Tracer::warning(ClassId, "A new grid is already currently loading. Maybe the dimension of the active grid is to small !");
			}
		}

		/ * Updates the visibility of the active subgrid. * /
		m_geometry->updateVisibility(coordinates);
	}*/

	float
	TerrainResource::getLevelAt (const Vector< 3, float > & worldPosition) const noexcept
	{
		return m_localData.getHeightAt(worldPosition[X], worldPosition[Z]);
	}

	Vector< 3, float >
	TerrainResource::getLevelAt (float x, float z, float delta) const noexcept
	{
		return {x, m_localData.getHeightAt(x, z) + delta, z};
	}

	Vector< 3, float >
	TerrainResource::getNormalAt (const Vector< 3, float > & worldPosition) const noexcept
	{
		return m_localData.getNormalAt(worldPosition[X], worldPosition[Z]);
	}

	bool
	TerrainResource::isOnGround (Node & node) const noexcept
	{
		/* Gets the absolute position to test against the scene boundaries. */
		auto worldPosition = node.getWorldCoordinates().position();

		return Libraries::Utility::equal(worldPosition[Y], this->getLevelAt(worldPosition));
	}

	bool
	TerrainResource::setGeometry (const std::shared_ptr< Geometry::AdaptiveVertexGridResource > & geometryResource) noexcept
	{
		if ( geometryResource == nullptr )
		{
			Tracer::error(ClassId, Blob() << "Geometry smart pointer attached to Renderable '" << this->name() << "' " << this << " is null !");

			return false;
		}

		this->setReadyForInstanciation(false);

		/* Change the material. */
		m_geometry = geometryResource;

		/* Checks if all is loaded */
		return this->addDependency(m_geometry.get());
	}

	bool
	TerrainResource::setMaterial (const std::shared_ptr< Material::Interface > & materialResource) noexcept
	{
		if ( materialResource == nullptr )
		{
			Tracer::error(ClassId, Blob() << "Material smart pointer attached to Renderable '" << this->name() << "' " << this << " is null !");

			return false;
		}

		this->setReadyForInstanciation(false);

		/* Change the material. */
		m_material = materialResource;

		/* Checks if all is loaded */
		return this->addDependency(m_material.get());
	}

	void
	TerrainResource::updateActiveGeometryProcess () noexcept
	{
		m_updatingActiveGeometryProcess = true;

		Tracer::info(ClassId, "Update process started...");

		/* This will update local data from AdaptiveGridGeometry. */
		if ( m_geometry->updateLocalData(m_localData, m_lastUpdatePosition) )
		{
			//this->setRequestingVideoMemoryUpdate();
		}

		m_updatingActiveGeometryProcess = false;
	}

	bool
	TerrainResource::prepareGeometry (float size, size_t division) noexcept
	{
		/* 1. Create the local data. */
		if ( !m_localData.initializeData(size, division) )
		{
			Tracer::error(ClassId, "Unable to initialize local data !");

			return false;
		}

		/* 2. Create the adaptive geometry (visible part). */
		if ( !m_geometry->load(m_localData, division / 4, {0.0F, 0.0F, 0.0F}) )
		{
			Tracer::error(ClassId, "Unable to create adaptive grid from local data !");

			m_localData.clear();

			return false;
		}

		/* 3. Set scene area volume and boundaries. */
		this->setBoundary(m_localData.squaredSize() * 0.5F);

		return true;
	}

	const char *
	TerrainResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	TerrainResource::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !this->prepareGeometry(DefaultSize, DefaultDivision) )
			return this->setLoadSuccess(false);

		if ( !this->setMaterial(Material::StandardResource::getDefault()) )
		{
			m_localData.clear();

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	TerrainResource::load (const Path::File & filepath) noexcept
	{
		Json::CharReaderBuilder builder;

		std::ifstream json(to_string(filepath), std::ifstream::binary);

		Json::Value root;

		std::string errors;

		if ( !Json::parseFromStream(builder, json, &root, &errors) )
		{
			Tracer::error(ClassId, Blob() << "Unable to parse JSON file ! Errors :\n" << errors);

			return this->setLoadSuccess(false);
		}

		/* Checks if additional stores before loading (optional) */
		Resources::Manager::instance()->stores().update(root);

		if ( !root.isMember(DefinitionResource::SceneAreaKey) )
		{
			Tracer::error(ClassId, Blob() << "The key '" << DefinitionResource::SceneAreaKey << "' is not present !");

			return this->setLoadSuccess(false);
		}

		auto sceneAreaObject = root[DefinitionResource::SceneAreaKey];

		if ( !sceneAreaObject.isMember(FastJSON::TypeKey) && !sceneAreaObject[FastJSON::TypeKey].isString() )
		{
			Tracer::error(ClassId, Blob() << "The key '" << FastJSON::TypeKey << "' is not present or not a string !");

			return this->setLoadSuccess(false);
		}

		if ( sceneAreaObject[FastJSON::TypeKey].asString() != ClassId || !sceneAreaObject.isMember(FastJSON::DataKey) )
		{
			Tracer::error(ClassId, Blob() << "This file doesn't contains a Terrain definition !");

			return this->setLoadSuccess(false);
		}

		return this->load(sceneAreaObject[FastJSON::DataKey]);
	}

	bool
	TerrainResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		auto * resources = Resources::Manager::instance();

		/* First, we check every key from JSON data. */

		/* Checks size and division options... */
		auto size = FastJSON::getFloat(data, FastJSON::SizeKey, DefaultSize);

		auto division = FastJSON::getUnsignedInteger(data, FastJSON::DivisionKey, DefaultDivision);

		/* Checks material type. */
		auto materialType = FastJSON::getString(data, MaterialTypeKey);

		if ( materialType.empty() || materialType != Material::StandardResource::ClassId )
		{
			Tracer::error(ClassId, Blob() << "Material resource type '" << materialType << "' is not handled yet !");

			return this->setLoadSuccess(false);
		}

		/* Then, we actually load the data. */

		/* The geometry. */
		if ( !m_localData.initializeData(size, division) )
		{
			Tracer::error(ClassId, "Unable to initialize local data !");

			return false;
		}

		/* Checks for vertex color. */
		/*std::shared_ptr< Image > vertexColorMap;

		if ( data.isMember(VertexColorKey) )
		{
			auto vertexColorData = data[VertexColorKey];

			if ( vertexColorData.isObject() )
			{
				auto imageName = FastJSON::getString(vertexColorData, ImageNameKey);

				if ( !imageName.empty() )
				{
					vertexColorMap = resources.images().get(imageName, true);

					if ( vertexColorMap == nullptr )
						Tracer::warning(ClassId, Blob() << "Image '" << imageName << "' is not available in data stores !");
				}
				else
				{
					Tracer::warning(ClassId, Blob() << "The key '" << ImageNameKey << "' is not present or not a string !");
				}
			}
			else
			{
				Tracer::warning(ClassId, Blob() << "The key '" << VertexColorKey << "' must be an object !");
			}
		}

		m_farGeometry = std::make_shared< VertexGridResource >(this->name() + "FarGeometry");

		if ( vertexColorMap != nullptr )
			m_farGeometry->enableVertexColor(vertexColorMap);*/

		if ( !m_farGeometry->load(size, division / 64) )
		{
			Tracer::error(ClassId, "Unable to create the far geometry !");

			return this->setLoadSuccess(false);
		}

		/* The material. */
		std::shared_ptr< Material::Interface > materialResource{};

		auto & materials = resources->standardMaterials();

		auto materialName = FastJSON::getString(data, MaterialNameKey);

		if ( materialName.empty() )
		{
			TraceWarning{ClassId} << "The key '" << MaterialNameKey << "' is not present or not a string !";

			materialResource = materials.getDefaultResource();
		}
		else
		{
			materialResource = materials.getResource(materialName);

			if ( materialResource == nullptr )
			{
				TraceError{ClassId} << "Material '" << materialName << "' is not available in data stores, using default one !";

				materialResource = materials.getDefaultResource();
			}
		}

		if ( !this->setMaterial(materialResource) )
		{
			Tracer::error(ClassId, Blob() << "Unable to use material for Terrain '" << this->name() << "' !");

			return this->setLoadSuccess(false);
		}

		/* After we check after optionnal parameters. */

		/* Checks for geometry relief generation options. */
		if ( data.isMember(HeightMapKey) )
		{
			auto heightMapping = data[HeightMapKey];

			if ( heightMapping.isArray() )
			{
				for ( const auto & iteration : heightMapping )
				{
					auto imageName = FastJSON::getString(iteration, ImageNameKey);

					if ( imageName.empty() )
					{
						Tracer::warning(ClassId, Blob() << "The key '" << ImageNameKey << "' is not present or not a string !");

						continue;
					}

					auto imageResource = resources->images().getResource(imageName, true);

					if ( imageResource == nullptr )
					{
						Tracer::warning(ClassId, Blob() << "Image '" << imageName << "' is not available in data stores !");

						continue;
					}

					/* Color inversion if requested. */
					auto inverse = FastJSON::getBoolean(iteration, InverseKey, false);

					/* Checks for scaling. */
					auto scale = FastJSON::getFloat(iteration, FastJSON::ScaleKey, 1.0F);

					/* Checks the mode for leveling the vertices. */
					auto mode = Grid< float >::getMode(FastJSON::getString(iteration, FastJSON::ModeKey));

					/* Applies the height map on the geometry. */
					m_localData.applyDisplacementMapping(imageResource->data(), inverse ? -scale : scale, mode);

					m_farGeometry->localData().applyDisplacementMapping(imageResource->data(), inverse ? -scale : scale, mode);
				}
			}
			else
			{
				Tracer::warning(ClassId, Blob() << "The key '" << HeightMapKey << "' is not an array !");
			}
		}

		/* Perlin noise filtering application. */
		if ( data.isMember(PerlinNoiseKey) )
		{
			auto noiseFiltering = data[PerlinNoiseKey];

			if ( noiseFiltering.isArray() )
			{
				for ( const auto & iteration : noiseFiltering )
				{
					/* Size parameter for perling noise. */
					auto perlinSize = FastJSON::getFloat(iteration, FastJSON::SizeKey);

					/* Height scaling parameter. */
					auto perlinScale = FastJSON::getFloat(iteration, FastJSON::ScaleKey, 1.0F);

					/* Checks the mode for leveling the vertices. */
					auto perlinMode = Grid< float >::getMode(FastJSON::getString(iteration, FastJSON::ModeKey));

					m_localData.applyPerlinNoise(perlinSize, perlinScale, perlinMode);

					m_farGeometry->localData().applyPerlinNoise(perlinSize, perlinScale, perlinMode);
				}
			}
			else
			{
				Tracer::warning(ClassId, Blob() << "The key '" << PerlinNoiseKey << "' is not an array !");
			}
		}

		/* Checks if the UV multiplier parameter. */
		auto value = FastJSON::getFloat(data, FastJSON::UVMultiplierKey, 1.0F);

		m_localData.setUVMultiplier(value);

		m_farGeometry->localData().setUVMultiplier(value);

		/* Checks if all is loaded */
		if ( !this->addDependency(m_farGeometry.get()) )
			return this->setLoadSuccess(false);

		//if ( vertexColorMap != nullptr )
		//	m_geometry->enableVertexColor(vertexColorMap);

		/* Creates the adaptive geometry (visible part). */
		if ( !m_geometry->load(m_localData, division / 16, {0.0F, 0.0F, 0.0F}) )
		{
			Tracer::error(ClassId, "Unable to create adaptive grid from local data !");

			m_localData.clear();

			return this->setLoadSuccess(false);
		}

		/* Sets scene area volume and boundaries. */
		this->setBoundary(m_localData.squaredSize() * 0.5F);

		return this->setLoadSuccess(true);
	}

	bool
	TerrainResource::load (float size, size_t division, const std::shared_ptr< Material::Interface > & material) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !this->prepareGeometry(size, division) )
		{
			Tracer::error(ClassId, "Unable to prepare the geometry to generate the Terrain !");

			return this->setLoadSuccess(false);
		}

		if ( !this->setMaterial(material) )
		{
			Tracer::error(ClassId, Blob() << "Unable to use material for Terrain '" << this->name() << "' !");

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	TerrainResource::prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept
	{
		TraceWarning{ClassId} << "Not done yet !";

		return false;
	}

	std::shared_ptr< TerrainResource >
	TerrainResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->terrains().getResource(resourceName, directLoad);
	}

	std::shared_ptr< TerrainResource >
	TerrainResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->terrains().getDefaultResource();
	}
}
