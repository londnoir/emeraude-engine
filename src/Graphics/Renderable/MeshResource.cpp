/*
 * Emeraude/Graphics/Renderable/MeshResource.cpp
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

#include "MeshResource.hpp"

/* Local inclusion */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "Saphir/ShaderGenerator.hpp"
#include "Saphir/LightGenerator.hpp"
#include "Vulkan/GraphicsShaderContainer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Renderable::MeshResource >::ClassId{"MeshContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Renderable::MeshResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;

	const size_t MeshResource::ClassUID{Observable::getClassUID()};

	MeshResource::MeshResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	bool
	MeshResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	void
	MeshResource::setReadyForInstanciation (bool state) noexcept
	{
		if ( state )
			this->enableFlag(IsReadyForInstanciation);
		else
			this->disableFlag(IsReadyForInstanciation);
	}

	bool
	MeshResource::isReadyForInstantiation () const noexcept
	{
		return this->isFlagEnabled(IsReadyForInstanciation);
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

		auto materialResource = m_layers[layerIndex].material();

		if ( materialResource != nullptr )
			return materialResource->isOpaque();

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

	const Cuboid< float > &
	MeshResource::boundingBox () const noexcept
	{
		if ( m_geometry == nullptr )
			return Interface::NullBoundingBox;

		return m_geometry->boundingBox();
	}

	const Sphere< float > &
	MeshResource::boundingSphere () const noexcept
	{
		if ( m_geometry == nullptr )
			return Interface::NullBoundingSphere;

		return m_geometry->boundingSphere();
	}

	int
	MeshResource::flags (size_t layerIndex) const noexcept
	{
		if ( layerIndex >= m_layers.size() )
		{
			TraceError{ClassId} << "MeshResource::flags(), layer index " << layerIndex << " overflow on '" << this->name() << "' !";

			layerIndex = 0;
		}

		return m_layers[layerIndex].flags();
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
			return false;

		if ( !this->setGeometry(Geometry::VertexResource::getDefault()) )
			return this->setLoadSuccess(false);

		if ( !this->setMaterial(Material::BasicResource::getDefault()) )
			return this->setLoadSuccess(false);

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
		auto geometryType = data[GeometryTypeKey].asString();

		if ( geometryType == Geometry::IndexedVertexResource::ClassId )
		{
			auto geometryName = data[GeometryNameKey].asString();

			auto geometryResource = Geometry::IndexedVertexResource::get(geometryName);

			if ( geometryResource == nullptr )
			{
				TraceError{ClassId} << "Geometry '" << geometryName << "' not found to complete the Mesh !";

				return nullptr;
			}

			return geometryResource;
		}
		else
		{
			TraceWarning{ClassId} << "Geometry resource type '" << geometryType << "' is not handled !";

			return nullptr;
		}
	}

	void
	MeshResource::parseLayerOptions (const Json::Value & data) noexcept
	{
		/*if ( data.isMember(EnableDoubleSidedFaceKey) && data[EnableDoubleSidedFaceKey].isBool() )
		{
			if ( data[EnableDoubleSidedFaceKey] )
				rasterizationMode.setCullingMode(CullingMode::None);
			else
				rasterizationMode.setCullingMode(CullingMode::Back);
		}

		if ( data.isMember(DrawingModeKey) && data[DrawingModeKey].isString() )
		{
			if ( data[DrawingModeKey] == "Fill" )
				rasterizationMode.setPolygonMode(PolygonMode::Fill);
			else if ( data[DrawingModeKey] == "Line" )
				rasterizationMode.setPolygonMode(PolygonMode::Line);
			else if ( data[DrawingModeKey] == "Point" )
				rasterizationMode.setPolygonMode(PolygonMode::Point);
		}*/
	}

	std::shared_ptr< Material::Interface >
	MeshResource::parseLayer (const Json::Value & data) noexcept
	{
		if ( !data.isMember(MaterialTypeKey) || !data[MaterialTypeKey].isString() )
		{
			TraceError{ClassId} << "The key '" << MaterialTypeKey << "' is not present or not a string !";

			return nullptr;
		}

		if ( !data.isMember(MaterialNameKey) || !data[MaterialTypeKey].isString() )
		{
			TraceError{ClassId} << "The key '" << MaterialNameKey << "' is not present or not a string !";

			return nullptr;
		}

		/* Gets the resource from material store. */
		auto materialType = data[MaterialTypeKey].asString();

		if ( materialType == Material::StandardResource::ClassId )
		{
			auto materialName = data[MaterialNameKey].asString();

			auto materialResource = Material::StandardResource::get(materialName);

			if ( materialResource == nullptr )
			{
				TraceError{ClassId} << "Material '" << materialName << "' not found to complete submesh !";

				return nullptr;
			}

			return materialResource;
		}
		else
		{
			TraceWarning{ClassId} << "Material resource type '" << materialType << "' is not handled !";

			return nullptr;
		}
	}

	bool
	MeshResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		/* FIXME: Physics properties from Mesh definitions. */
		//this->parseOptions(data);

		/* Parse geometry definition and get default if error occurs. */
		auto geometryResource = this->parseGeometry(data);

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

		auto & layerRules = data[LayersKey];

		if ( !layerRules.isArray() )
		{
			TraceError{ClassId} << "'" << LayersKey << "' key must be a JSON array !";

			return this->setLoadSuccess(false);
		}

		if ( layerRules.size() <= 0 )
		{
			TraceError{ClassId} << "'" << LayersKey << "' array is empty !";

			return this->setLoadSuccess(false);
		}

		m_layers.clear();

		for ( auto & layerRule : layerRules )
		{
			/* Parse material definition and get default if error occurs. */
			auto materialResource = this->parseLayer(layerRule);

			/* Gets a default material. */
			if ( materialResource == nullptr )
			{
				Tracer::error(ClassId, "No suitable material resource found !");

				return this->setLoadSuccess(false);
			}

			if ( this->addMaterial(materialResource) )
			{
				/* FIXME */
				//this->parseLayerOptions(layerRule, m_geometry->rasterizationMode(m_layers.size() - 1));
			}
			else
			{
				Tracer::error(ClassId, "Unable to add material layer !");

				return this->setLoadSuccess(false);
			}
		}

		return this->setLoadSuccess(true);
	}

	bool
	MeshResource::load (const std::shared_ptr< Geometry::Interface > & geometry, const std::shared_ptr< Material::Interface > & material) noexcept
	{
		if ( !this->beginLoading() )
			return false;

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

		this->setMaterial(material);

		return this->setLoadSuccess(true);
	}

	bool
	MeshResource::load (const std::shared_ptr< Geometry::Interface > & geometry, const std::vector< std::shared_ptr< Material::Interface > > & materialList) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		/* 1. Check the geometry. */
		if ( geometry == nullptr )
		{
			TraceError{ClassId} << "Unable to set geometry for mesh '" << this->name() << "' !";

			return this->setLoadSuccess(false);
		}

		this->setGeometry(geometry);

		/* 2. Check the materials. */
		m_layers.clear();

		for ( auto & material : materialList )
		{
			if ( material == nullptr )
			{
				Tracer::error(ClassId, "One material of the list is empty !");

				return this->setLoadSuccess(false);
			}

			this->addMaterial(material);
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

		this->setReadyForInstanciation(false);

		m_geometry = geometry;

		return this->addDependency(m_geometry.get());
	}

	bool
	MeshResource::addMaterial (const std::shared_ptr< Material::Interface > & material) noexcept
	{
		if ( material == nullptr )
		{
			TraceError{ClassId} << "Material pointer tried to be attached to renderable object '" << this->name() << "' " << this << " is null !";

			return false;
		}

		this->setReadyForInstanciation(false);

		m_layers.emplace_back("MeshLayer" + std::to_string(m_layers.size()), material);

		return this->addDependency(material.get());
	}

	float
	MeshResource::baseSize () const noexcept
	{
		return m_baseSize;
	}

	bool
	MeshResource::prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept
	{
		using namespace Saphir;
		
		const auto modelMatrixType = enableInstancing ? ModelMatrixType::VertexBufferObject : ModelMatrixType::UniformBufferObject;

		SetIndexes indexes{};
		indexes.enableSet(SetType::PerView);
		if ( !enableInstancing )
		{
			indexes.enableSet(SetType::PerModel);
		}
		indexes.enableSet(SetType::PerObjectLayer);

		/* Vertex shader stage creation. */
		{
			auto shader = shaders.initVertexShader("CustomVertexShader");

			ShaderGenerator generator{shader, modelMatrixType, renderPassType};
			generator.setIndexes(indexes);
			generator.setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

			/* The position is always required and available. */
			generator.requestVertexShaderSynthesizeInstruction(Keys::GLSL::Vertex::Out::Position);

			if ( !material.generateShaderCode(generator, geometry) )
			{
				TraceError{ClassId} << "Unable to generate material source code for the vertex shader '" << shader->name() << "' !";

				return false;
			}

			LightGenerator lightGenerator{};
			lightGenerator.useSpecularComponent(ShaderGenerator::materialUniform(Keys::UniformBlocks::Component::Shininess));

			if ( !lightGenerator.generateShaderCode(generator, geometry) )
			{
				TraceError{ClassId} << "Unable to generate light to the vertex shader '" << shader->name() << "' source code !";

				return false;
			}

			if ( !generator.writeShader() )
			{
				TraceError{ClassId} << "Unable to write the vertex shader '" << shader->name() << "' !";

				return false;
			}
		}

		/* Tesselation control shader stage creation. */
		{
			//auto shader = shaders.initTesselationControlShader("DefaultTesselationControlShader");
		}

		/* Tesselation evaluation shader stage creation. */
		{
			//auto shader = shaders.initTesselationEvaluationShader("DefaultTesselationEvaluationShader");
		}

		/* Geometry shader stage creation. */
		{
			//auto shader = shaders.initGeometryShader("DefaultGeometryShader");
		}

		/* Fragment shader stage creation. */
		{
			auto shader = shaders.initFragmentShader("CustomFragmentShader");

			ShaderGenerator generator{shader, modelMatrixType, renderPassType};
			generator.setIndexes(indexes);
			generator.setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

			if ( !material.generateShaderCode(generator, geometry) )
			{
				TraceError{ClassId} << "Unable to generate material source code for the fragment shader '" << shader->name() << "' !";

				return false;
			}

			LightGenerator lightGenerator{};
			lightGenerator.useSpecularComponent(ShaderGenerator::materialUniform(Keys::UniformBlocks::Component::Shininess));

			if ( !lightGenerator.generateShaderCode(generator, geometry) )
			{
				TraceError{ClassId} << "Unable to generate light to the fragment shader '" << shader->name() << "' source code !";

				return false;
			}

			if ( !generator.writeShader() )
			{
				TraceError{ClassId} << "Unable to write the fragment shader '" << shader->name() << "' !";

				return false;
			}
		}

		return true;
	}

	std::shared_ptr< MeshResource >
	MeshResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->meshes().getResource(resourceName, directLoad);
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
			resourceName = (std::stringstream{} << "Mesh(" << geometryResource->name() << ',' << materialResource->name() << ')').str();

		auto meshResource = Resources::Manager::instance()->meshes().getOrCreateResource(resourceName);

		if ( meshResource->isUnloaded() && !meshResource->load(geometryResource, materialResource) )
		{
			Tracer::error(ClassId, "Unable to load the mesh resource !");

			return {};
		}

		return meshResource;
	}

	std::shared_ptr< MeshResource >
	MeshResource::getOrCreate (const std::shared_ptr< Geometry::Interface > & geometryResource, const std::vector< std::shared_ptr< Material::Interface > > & materialResources, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{
			std::stringstream ss{};

			ss << "Mesh(" << geometryResource->name();

			for ( const auto & materialResource : materialResources )
				ss << ',' << materialResource->name();

			ss << ')';

			resourceName = ss.str();
		}

		auto meshResource = Resources::Manager::instance()->meshes().getOrCreateResource(resourceName);

		if ( meshResource->isUnloaded() && !meshResource->load(geometryResource, materialResources) )
		{
			Tracer::error(ClassId, "Unable to load the mesh resource !");

			return {};
		}

		return meshResource;
	}
}
