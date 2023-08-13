/*
 * Emeraude/Graphics/Renderable/SkyboxResource.cpp
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

#include "SkyboxResource.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "FastJSON.hpp"
#include "Saphir/ShaderGenerator.hpp"
#include "Vulkan/GraphicsShaderContainer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Renderable::SkyboxResource >::ClassId{"SkyboxContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Renderable::SkyboxResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;

	const size_t SkyboxResource::ClassUID{Observable::getClassUID()};

	SkyboxResource::SkyboxResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: AbstractBackground(name, resourceFlagBits)
	{

	}

	bool
	SkyboxResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	SkyboxResource::isOpaque (size_t) const noexcept
	{
		if ( m_material != nullptr )
			return m_material->isOpaque();

		return true;
	}

	size_t
	SkyboxResource::layerCount () const noexcept
	{
		return 1;
	}

	const Geometry::Interface *
	SkyboxResource::geometry () const noexcept
	{
		return m_geometry.get();
	}

	const Material::Interface *
	SkyboxResource::material (size_t) const noexcept
	{
		return m_material.get();
	}

	const char *
	SkyboxResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	SkyboxResource::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !this->setGeometry(AbstractBackground::getSkyboxGeometry()) )
			return this->setLoadSuccess(false);

		constexpr auto materialName = "DefaultSkyboxMaterial";

		auto flags = Material::MaterialFlagBits::ComputesPrimaryTextureCoordinates | Material::MaterialFlagBits::PrimaryTextureCoordinatesUses3D;

		auto materialResource = Resources::Manager::instance()
			->basicMaterials()
			.getOrCreateResource(materialName, flags, true, this->isDirectLoading());

		if ( materialResource->isUnloaded() )
		{
			if ( !materialResource->setTexture(TextureResource::TextureCubemap::getDefault()) )
				return this->setLoadSuccess(false);

			if ( !materialResource->setManualLoadSuccess(true) )
				return this->setLoadSuccess(false);
		}

		if ( !this->setMaterial(materialResource) )
			return this->setLoadSuccess(false);

		return this->setLoadSuccess(true);
	}

	bool
	SkyboxResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !this->setGeometry(AbstractBackground::getSkyboxGeometry()) )
			return this->setLoadSuccess(false);

		if ( !data.isMember(TextureKey) || !data[TextureKey].isString() )
		{
			TraceError{ClassId} << "The '" << TextureKey << "' key is not present or not a string in '" << this->name() << "' Json file ! ";

			return this->setLoadSuccess(false);
		}

		const auto textureName = data[TextureKey].asString();

		auto flags = Material::MaterialFlagBits::ComputesPrimaryTextureCoordinates | Material::MaterialFlagBits::PrimaryTextureCoordinatesUses3D;

		auto materialResource = Resources::Manager::instance()
			->basicMaterials()
			.getOrCreateResource(textureName + "SkyboxMaterial", flags, true, this->isDirectLoading());

		if ( materialResource->isUnloaded() )
		{
			auto cubemapResource = TextureResource::TextureCubemap::get(textureName, this->isDirectLoading());

			if ( cubemapResource == nullptr )
				return this->setLoadSuccess(false);

			if ( !materialResource->setTexture(cubemapResource) )
				return this->setLoadSuccess(false);

			if ( !materialResource->setManualLoadSuccess(true) )
				return this->setLoadSuccess(false);
		}

		if ( !this->setMaterial(materialResource) )
			return this->setLoadSuccess(false);

		this->setLightPosition(FastJSON::getVector< 3, float >(data, LightPositionKey));

		this->setLightAmbientColor(FastJSON::getColor(data, LightAmbientColorKey));

		this->setLightDiffuseColor(FastJSON::getColor(data, LightDiffuseColorKey));

		this->setLightSpecularColor(FastJSON::getColor(data, LightSpecularColorKey));

		return this->setLoadSuccess(true);
	}

	bool
	SkyboxResource::load (const std::shared_ptr< Material::Interface > & material) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !this->setGeometry(AbstractBackground::getSkyboxGeometry()) )
			return this->setLoadSuccess(false);

		if ( !this->setMaterial(material) )
			return this->setLoadSuccess(false);

		return this->setLoadSuccess(true);
	}

	bool
	SkyboxResource::setGeometry (const std::shared_ptr< Geometry::Interface > & geometry) noexcept
	{
		if ( geometry == nullptr )
		{
			TraceError{ClassId} << "Geometry pointer tried to be attached to renderable object '" << this->name() << "' " << this << " is null !";

			return false;
		}

		this->setReadyForInstanciation(false);

		m_geometry = geometry;

		if ( !this->addDependency(m_geometry.get()) )
		{
			TraceError{ClassId} << "Unable to set geometry for Skybox '" << this->name() << "' !";

			return false;
		}

		return true;
	}

	bool
	SkyboxResource::setMaterial (const std::shared_ptr< Material::Interface > & material) noexcept
	{
		if ( material == nullptr )
		{
			TraceError{ClassId} << "Material pointer tried to be attached to renderable object '" << this->name() << "' " << this << " is null !";

			return false;
		}

		this->setReadyForInstanciation(false);

		m_material = material;

		if ( !this->addDependency(m_material.get()) )
		{
			TraceError{ClassId} << "Unable to set material for Skybox '" << this->name() << "' !";

			return false;
		}

		return true;
	}

	bool
	SkyboxResource::prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept
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

			if ( !generator.writeShader() )
			{
				TraceError{ClassId} << "Unable to write the fragment shader '" << shader->name() << "' !";

				return false;
			}
		}

		return true;
	}

	std::shared_ptr< SkyboxResource >
	SkyboxResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->skyboxes().getResource(resourceName, directLoad);
	}

	std::shared_ptr< SkyboxResource >
	SkyboxResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->skyboxes().getDefaultResource();
	}
}
