/*
 * src/Graphics/Material/BasicResource.cpp
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

#include "BasicResource.hpp"

/* STL inclusions. */
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions. */
#include "Libs/Math/Base.hpp"
#include "Libs/PixelFactory/Color.hpp"
#include "Libs/FastJSON.hpp"
#include "Saphir/Declaration/Function.hpp"
#include "Saphir/Declaration/Types.hpp"
#include "Saphir/Generator/Abstract.hpp"
#include "Saphir/Code.hpp"
#include "Saphir/Keys.hpp"
#include "Saphir/LightGenerator.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Types.hpp"
#include "Vulkan/DescriptorSetLayout.hpp"
#include "Helpers.hpp"
#include "Resources/Manager.hpp"
#include "Component/Texture.hpp"
#include "Tracer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const EmEn::Resources::Container< EmEn::Graphics::Material::BasicResource >::ClassId{"BasicResourceContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t EmEn::Resources::Container< EmEn::Graphics::Material::BasicResource >::ClassUID{getClassUID(ClassId)};

namespace EmEn::Graphics::Material
{
	using namespace EmEn::Libs;
	using namespace Math;
	using namespace Saphir;
	using namespace Keys;
	using namespace Vulkan;

	const size_t BasicResource::ClassUID{getClassUID(ClassId)};

	BasicResource::BasicResource (const std::string & name, int resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	BasicResource::~BasicResource ()
	{
		this->destroy();
	}

	bool
	BasicResource::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		if ( !this->setColor(PixelFactory::Grey) )
		{
			return false;
		}

		return this->setLoadSuccess(true);
	}

	bool
	BasicResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		/* NOTE: We only check the diffuse component in material JSON. */
		FillingType fillingType{};

		Json::Value componentData{};

		if ( !parseComponentBase(data, DiffuseString, fillingType, componentData, false) )
		{
			TraceError{ClassId} << "Unable to parse the diffuse component in material '" << this->name() << "' resource JSON file ! " "\n" << data;

			return this->setLoadSuccess(false);
		}

		switch ( fillingType )
		{
			case FillingType::Color :
			{
				const auto color = parseColorComponent(componentData);

				if ( !this->setColor(color) )
				{
					return this->setLoadSuccess(false);
				}
			}
				break;

			case FillingType::Gradient :
			case FillingType::Texture :
			case FillingType::VolumeTexture :
			case FillingType::Cubemap :
			case FillingType::AnimatedTexture :
			{
				m_textureComponent = std::make_unique< Component::Texture >(Uniform::PrimarySampler, SurfaceColor, componentData, fillingType, *Resources::Manager::instance());

				const auto textureResource = m_textureComponent->textureResource();

				if ( !this->addDependency(textureResource) )
				{
					m_textureComponent.reset();

					return this->setLoadSuccess(false);
				}

				this->enableFlag(TexturingEnabled);
				this->enableFlag(UsesPrimaryTextureCoordinates);
				if ( textureResource->request3DTextureCoordinates() )
				{
					this->enableFlag(PrimaryTextureCoordinatesUses3D);
				}
			}
				break;

			case FillingType::Value :
			case FillingType::AlphaChannelAsValue :
			case FillingType::None :
				TraceError{ClassId} << "Invalid filling type for material '" << this->name() << "' !";

				return this->setLoadSuccess(false);
		}

		/* Check specular color value and shininess. */
		if ( data.isMember(SpecularString) )
		{
			if ( !data[SpecularString].isObject() )
			{
				TraceError{ClassId} << "The key '" << SpecularString << "' in '" << this->name() << "' Json file must be an object ! ";

				return this->setLoadSuccess(false);
			}

			const auto & specularData = data[SpecularString];

			this->setSpecularComponent(
				FastJSON::getColor(specularData, JKColor, DefaultSpecularColor),
				FastJSON::getNumber< float >(specularData, JKShininess, DefaultShininess)
			);
		}

		/* Check the blending mode. */
		this->enableBlendingFromJson(data);

		/* Check the optional global auto-illumination amount. */
		if ( data.isMember(AutoIlluminationString) )
		{
			if ( !data[AutoIlluminationString].isObject() )
			{
				TraceError{ClassId} << "The key '" << AutoIlluminationString << "' in '" << this->name() << "' Json file must be an object ! ";

				return this->setLoadSuccess(false);
			}

			const auto & autoIlluminationData = data[AutoIlluminationString];

			this->setAutoIlluminationAmount(FastJSON::getNumber< float >(autoIlluminationData, JKValue, DefaultAutoIllumination));
		}

		/* Check the optional global opacity. */
		auto value = 1.0F;

		if ( getComponentAsValue(data, OpacityString, value) )
		{
			this->setOpacity(value);
		}

		return this->setLoadSuccess(true);
	}

	bool
	BasicResource::create (Renderer & renderer) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is already created !";

			return true;
		}

		/* Component creation (optional). */
		if ( this->usingTexture() )
		{
			/* NOTE: Starts to 1 because there is the UBO in the first place. */
			uint32_t binding = 1;

			if ( !m_textureComponent->create(renderer, binding) )
			{
				Tracer::error(ClassId, "Unable to create the texture component !");

				return false;
			}
		}

		/* Create the material UBO, sampler, descriptor set ... */
		if ( !this->createVideoMemory(renderer) )
		{
			Tracer::error(ClassId, "Unable to the material onto the GPU !");

			return false;
		}

		/* Initialize the material data in the GPU. */
		if ( !this->updateVideoMemory() )
		{
			Tracer::error(ClassId, "Unable to update the initial video memory !");

			return false;
		}

		this->enableFlag(Created);

		return true;
	}

	std::string
	BasicResource::getSharedUniformBufferIdentifier () const noexcept
	{
		std::string identifier{ClassId};

		identifier += this->usingTexture() ? "Textured" : "Simple";

		return identifier;
	}

	bool
	BasicResource::createElementInSharedBuffer (Renderer & renderer, const std::string & identifier) noexcept
	{
		m_sharedUniformBuffer = this->getSharedUniformBuffer(renderer, identifier);

		if ( m_sharedUniformBuffer == nullptr )
		{
			TraceError{ClassId} << "Unable to get the shared uniform buffer for material '" << this->name() << "' !";

			return false;
		}

		if ( !m_sharedUniformBuffer->addElement(this, m_sharedUBOIndex) )
		{
			TraceError{ClassId} << "Unable to add the material to the shared uniform buffer for material '" << this->name() << "' !";

			return false;
		}

		return m_sharedUniformBuffer->writeElementData(m_sharedUBOIndex, m_materialProperties.data());
	}

	bool
	BasicResource::createDescriptorSetLayout (LayoutManager & layoutManager, const std::string & identifier) noexcept
	{
		m_descriptorSetLayout = layoutManager.getDescriptorSetLayout(identifier);

		if ( m_descriptorSetLayout == nullptr )
		{
			m_descriptorSetLayout = layoutManager.prepareNewDescriptorSetLayout(identifier);
			m_descriptorSetLayout->setIdentifier(ClassId, identifier, "DescriptorSetLayout");

			/* Declare the UBO for the material properties. */
			m_descriptorSetLayout->declareUniformBuffer(0, VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT);

			/* Declare the sampler used by the material if needed. */
			if ( this->usingTexture() )
			{
				m_descriptorSetLayout->declareCombinedImageSampler(1, VK_SHADER_STAGE_FRAGMENT_BIT);
			}

			if ( !layoutManager.createDescriptorSetLayout(m_descriptorSetLayout) )
			{
				return false;
			}
		}

		return true;
	}

	bool
	BasicResource::createDescriptorSet (Renderer & renderer, const UniformBufferObject & uniformBufferObject) noexcept
	{
		m_descriptorSet = std::make_unique< DescriptorSet >(renderer.descriptorPool(), m_descriptorSetLayout);
		m_descriptorSet->setIdentifier(ClassId, this->name(), "DescriptorSet");

		if ( !m_descriptorSet->create() )
		{
			TraceError{ClassId} << "Unable to create the descriptor set for material '" << this->name() << "' !";

			return false;
		}

		if ( !m_descriptorSet->writeUniformBufferObject(0, uniformBufferObject, m_sharedUBOIndex) )
		{
			TraceError{ClassId} << "Unable to write the uniform buffer object to the descriptor set for material '" << this->name() << "' !";

			return false;
		}

		if ( this->usingTexture() )
		{
			if ( !m_descriptorSet->writeCombinedImageSampler(1, *m_textureComponent->textureResource()) )
			{
				TraceError{ClassId} << "Unable to write the sampler to the descriptor set for material '" << this->name() << "' !";

				return false;
			}
		}

		return true;
	}

	void
	BasicResource::onMaterialLoaded () noexcept
	{
		if ( m_textureComponent != nullptr && m_textureComponent->textureResource()->duration() > 0 )
		{
			this->enableFlag(Animated);
		}
	}

	bool
	BasicResource::createVideoMemory (Renderer & renderer) noexcept
	{
		const auto identifier = this->getSharedUniformBufferIdentifier();

		if ( !this->createElementInSharedBuffer(renderer, identifier) )
		{
			TraceError{ClassId} << "Unable to create the data inside the shared uniform buffer '" << identifier << "' for material '" << this->name() << "' !";

			return false;
		}

		if ( !this->createDescriptorSetLayout(renderer.layoutManager(), identifier) )
		{
			TraceError{ClassId} << "Unable to create the descriptor set layout for material '" << this->name() << "' !";

			return false;
		}

		if ( !this->createDescriptorSet(renderer, *m_sharedUniformBuffer->uniformBufferObject(m_sharedUBOIndex)) )
		{
			TraceError{ClassId} << "Unable to create the descriptor set for material '" << this->name() << "' !";

			return false;
		}

		return true;
	}

	bool
	BasicResource::updateVideoMemory () const noexcept
	{
		if ( !this->isCreated() )
		{
			return true;
		}

		if ( m_sharedUniformBuffer == nullptr )
		{
			TraceError{ClassId} << "There is no shared uniform buffer for material '" << this->name() << "' !";

			return false;
		}

		return m_sharedUniformBuffer->writeElementData(m_sharedUBOIndex, m_materialProperties.data());
	}

	void
	BasicResource::destroy () noexcept
	{
		if ( m_sharedUniformBuffer != nullptr )
		{
			m_sharedUniformBuffer->removeElement(this);
		}

		/* Reset to defaults. */
		this->resetFlags();

		/* Reset member variables. */
		m_physicalSurfaceProperties.reset();
		m_textureComponent.reset();
		m_blendingMode = BlendingMode::None;
		m_materialProperties = {
			/* Diffuse color (4), */
			DefaultDiffuseColor.red(), DefaultDiffuseColor.green(), DefaultDiffuseColor.blue(), DefaultDiffuseColor.alpha(),
			/* Specular color (4), */
			DefaultSpecularColor.red(), DefaultSpecularColor.green(), DefaultSpecularColor.blue(), DefaultSpecularColor.alpha(),
			/* Shininess (1), Opacity (1), AutoIlluminationColor (1), Unused (1). */
			DefaultShininess, DefaultOpacity, DefaultAutoIllumination, 0.0F
		};
		m_descriptorSetLayout.reset();
		m_descriptorSet.reset();
		m_sharedUniformBuffer.reset();
		m_sharedUBOIndex = 0;
		m_flags[DynamicColorEnabled] = false;
		m_flags[EnableAutoIllumination] = false;
	}

	uint32_t
	BasicResource::frameCount () const noexcept
	{
		if ( !this->isFlagEnabled(Animated) || m_textureComponent == nullptr )
		{
			return 1;
		}

		const auto textureResource = m_textureComponent->textureResource();

		if ( textureResource == nullptr )
		{
			return 1;
		}

		return textureResource->frameCount();
	}

	uint32_t
	BasicResource::duration () const noexcept
	{
		if ( !this->isFlagEnabled(Animated) || m_textureComponent == nullptr )
		{
			return 0;
		}

		const auto textureResource = m_textureComponent->textureResource();

		if ( textureResource == nullptr )
		{
			return 0;
		}

		return textureResource->duration();
	}

	uint32_t
	BasicResource::frameIndexAt (uint32_t sceneTime) const noexcept
	{
		if ( !this->isFlagEnabled(Animated) || m_textureComponent == nullptr )
		{
			return 0;
		}

		const auto textureResource = m_textureComponent->textureResource();

		if ( textureResource == nullptr )
		{
			return 0;
		}

		return textureResource->frameIndexAt(sceneTime);
	}

	void
	BasicResource::enableBlending (BlendingMode mode) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is already created ! Unable to enabled a blending mode.";

			return;
		}

		this->enableFlag(BlendingEnabled);

		m_blendingMode = mode;
	}

	BlendingMode
	BasicResource::blendingMode () const noexcept
	{
		if ( !this->isFlagEnabled(BlendingEnabled) )
		{
			return BlendingMode::None;
		}

		return m_blendingMode;
	}

	std::string
	BasicResource::fragmentColor () const noexcept
	{
		if ( m_flags[EnableOpacity] )
		{
			std::stringstream surfaceColor;
			surfaceColor << "vec4(" << SurfaceColor << ".rgb, " << MaterialUB(UniformBlock::Component::Opacity) << ')';
			return surfaceColor.str();
		}

		return SurfaceColor;
	}

	bool
	BasicResource::setupLightGenerator (LightGenerator & lightGenerator) const noexcept
	{
		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The basic material '" << this->name() << "' is not created !"
				"It can't configure the light generator.";

			return false;
		}

		lightGenerator.declareSurfaceAmbient((std::stringstream{} << "desaturate(" << SurfaceColor << ")").str());
		lightGenerator.declareSurfaceDiffuse(SurfaceColor);
		lightGenerator.declareSurfaceSpecular(MaterialUB(UniformBlock::Component::SpecularColor), MaterialUB(UniformBlock::Component::Shininess));

		if ( m_flags[EnableOpacity] )
		{
			lightGenerator.declareSurfaceOpacity(MaterialUB(UniformBlock::Component::Opacity));
		}

		if ( m_flags[EnableAutoIllumination] )
		{
			lightGenerator.declareSurfaceAutoIllumination(MaterialUB(UniformBlock::Component::AutoIlluminationAmount));
		}

		return true;
	}

	Declaration::UniformBlock
	BasicResource::getUniformBlock (uint32_t set, uint32_t binding) const noexcept
	{
		Declaration::UniformBlock block{set, binding, Declaration::MemoryLayout::Std140, UniformBlock::Type::BasicMaterial, UniformBlock::Material};
		block.addMember(Declaration::VariableType::FloatVector4, UniformBlock::Component::DiffuseColor);
		block.addMember(Declaration::VariableType::FloatVector4, UniformBlock::Component::SpecularColor);
		block.addMember(Declaration::VariableType::Float, UniformBlock::Component::Shininess);
		block.addMember(Declaration::VariableType::Float, UniformBlock::Component::Opacity);
		block.addMember(Declaration::VariableType::Float, UniformBlock::Component::AutoIlluminationAmount);

		return block;
	}

	bool
	BasicResource::generateVertexShaderCode (Generator::Abstract & generator, VertexShader & vertexShader) const noexcept
	{
		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The basic material '" << this->name() << "' is not created !"
				"It can't generates a vertex shader source code.";

			return false;
		}

		const auto * geometry = generator.getGeometryInterface();

		if ( !generator.highQualityLightEnabled() && !generator.declareMaterialUniformBlock(*this, vertexShader, 0) )
		{
			return false;
		}

		/* Check texture coordinate attributes. */
		if ( this->usingTexture() && !checkPrimaryTextureCoordinates(generator, vertexShader, *this, *geometry) )
		{
			return false;
		}

		/* Check if the material needs vertex colors. */
		if ( this->usingVertexColors() )
		{
			if ( !geometry->vertexColorEnabled() )
			{
				TraceError{ClassId} << "The geometry " << geometry->name() << " has no vertex color for basic material '" << this->name() << "' !";

				return false;
			}

			vertexShader.requestSynthesizeInstruction(ShaderVariable::PrimaryVertexColor);
		}

		return true;
	}

	bool
	BasicResource::generateFragmentShaderCodeWithTexture (FragmentShader & fragmentShader, uint32_t materialSet) const noexcept
	{
		const auto * texCoordVariable =
			m_textureComponent->isVolumetricTexture() ?
			ShaderVariable::Primary3DTextureCoordinates :
			ShaderVariable::Primary2DTextureCoordinates;

		if ( !fragmentShader.declare(Declaration::Sampler{materialSet, 1, m_textureComponent->textureType(), m_textureComponent->samplerName()}) )
		{
			return false;
		}

		if ( this->usingVertexColors() )
		{
			if ( m_flags[DynamicColorEnabled] )
			{
				Code{fragmentShader, Location::Top} << "const vec4 " << m_textureComponent->variableName() << " = texture(" << m_textureComponent->samplerName() << ", " << texCoordVariable << ") * " << MaterialUB(UniformBlock::Component::DiffuseColor) << " * " << ShaderVariable::PrimaryVertexColor << ';';
			}
			else
			{
				Code{fragmentShader, Location::Top} << "const vec4 " << m_textureComponent->variableName() << " = texture(" << m_textureComponent->samplerName() << ", " << texCoordVariable << ") * " << ShaderVariable::PrimaryVertexColor << ';';
			}
		}
		else if ( m_flags[DynamicColorEnabled] )
		{
			Code{fragmentShader, Location::Top} << "const vec4 " << m_textureComponent->variableName() << " = texture(" << m_textureComponent->samplerName() << ", " << texCoordVariable << ") * " << MaterialUB(UniformBlock::Component::DiffuseColor) << ';';
		}
		else
		{
			Code{fragmentShader, Location::Top} << "const vec4 " << m_textureComponent->variableName() << " = texture(" << m_textureComponent->samplerName() << ", " << texCoordVariable << ");";
		}

		return true;
	}

	bool
	BasicResource::generateFragmentShaderCodeWithoutTexture (FragmentShader & fragmentShader) const noexcept
	{
		if ( this->usingVertexColors() )
		{
			if ( m_flags[DynamicColorEnabled] )
			{
				Code{fragmentShader, Location::Top} << "const vec4 " << SurfaceColor << " = " << MaterialUB(UniformBlock::Component::DiffuseColor) << " * " << ShaderVariable::PrimaryVertexColor << ';';
			}
			else
			{
				Code{fragmentShader, Location::Top} << "const vec4 " << SurfaceColor << " = " << ShaderVariable::PrimaryVertexColor << ';';
			}
		}
		else
		{
			Code{fragmentShader, Location::Top} << "const vec4 " << SurfaceColor << " = " << MaterialUB(UniformBlock::Component::DiffuseColor) << ';';
		}

		return true;
	}

	bool
	BasicResource::generateFragmentShaderCode (Generator::Abstract & generator, LightGenerator & /*lightGenerator*/, FragmentShader & fragmentShader) const noexcept
	{
		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The basic material '" << this->name() << "' is not created !"
				"It can't generates a fragment shader source code.";

			return false;
		}

		if ( !generator.declareMaterialUniformBlock(*this, fragmentShader, 0) )
		{
			return false;
		}

		Declaration::Function desaturate{"desaturate", GLSL::FloatVector4};
		desaturate.addInParameter(GLSL::FloatVector4, "color");
		Code{desaturate} << "float average = (min(color.r, min(color.g, color.b)) + max(color.r, max(color.g, color.b))) * 0.5;";
		Code{desaturate, Location::Output} << "return vec4(average, average, average, 1.0);";

		if ( !fragmentShader.declare(desaturate) )
		{
			return false;
		}

		if ( m_textureComponent != nullptr )
		{
			const uint32_t materialSet = generator.shaderProgram()->setIndex(SetType::PerModelLayer);

			return this->generateFragmentShaderCodeWithTexture(fragmentShader, materialSet);
		}

		return this->generateFragmentShaderCodeWithoutTexture(fragmentShader);
	}

	void
	BasicResource::enableVertexColor () noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to enable vertex color.";

			return;
		}

		this->enableFlag(UsesVertexColors);
	}

	bool
	BasicResource::setColor (const PixelFactory::Color< float > & color) noexcept
	{
		if ( this->isCreated() && !m_flags[DynamicColorEnabled] )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created without the dynamic color enabled ! "
				"Unable to change the dynamic color.";

			return false;
		}

		m_materialProperties[DiffuseColorOffset] = color.red();
		m_materialProperties[DiffuseColorOffset+1] = color.green();
		m_materialProperties[DiffuseColorOffset+2] = color.blue();
		m_materialProperties[DiffuseColorOffset+3] = color.alpha();

		m_flags[DynamicColorEnabled] = true;

		return this->updateVideoMemory();
	}

	bool
	BasicResource::setTexture (const std::shared_ptr< TextureResource::Abstract > & texture, bool enableAlpha) noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to set a texture.";

			return false;
		}

		if ( !this->addDependency(texture) )
		{
			TraceError{ClassId} << "Unable to link the texture '" << texture->name() << "' dependency to material '" << this->name() << "' !";

			return false;
		}

		m_textureComponent = std::make_unique< Component::Texture >(Uniform::PrimarySampler, SurfaceColor, texture);
		m_textureComponent->enableAlpha(enableAlpha);

		this->enableFlag(TexturingEnabled);
		this->enableFlag(UsesPrimaryTextureCoordinates);
		if ( texture->request3DTextureCoordinates() )
		{
			this->enableFlag(PrimaryTextureCoordinatesUses3D);
		}

		return true;
	}

	bool
	BasicResource::setSpecularComponent (const PixelFactory::Color< float > & color) noexcept
	{
		m_materialProperties[SpecularColorOffset] = color.red();
		m_materialProperties[SpecularColorOffset+1] = color.green();
		m_materialProperties[SpecularColorOffset+2] = color.blue();
		m_materialProperties[SpecularColorOffset+3] = color.alpha();

		return this->updateVideoMemory();
	}

	bool
	BasicResource::setSpecularComponent (const PixelFactory::Color< float > & color, float shininess) noexcept
	{
		m_materialProperties[SpecularColorOffset] = color.red();
		m_materialProperties[SpecularColorOffset+1] = color.green();
		m_materialProperties[SpecularColorOffset+2] = color.blue();
		m_materialProperties[SpecularColorOffset+3] = color.alpha();

		m_materialProperties[ShininessOffset] = shininess;

		return this->updateVideoMemory();
	}

	bool
	BasicResource::setShininess (float value) noexcept
	{
		m_materialProperties[ShininessOffset] = value;

		return this->updateVideoMemory();
	}

	bool
	BasicResource::setOpacity (float value) noexcept
	{
		if ( this->isCreated() && !m_flags[EnableOpacity] )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is already created ! Changing the state of opacity or its value is disallowed.";

			return false;
		}

		this->enableFlag(BlendingEnabled);

		m_materialProperties[OpacityOffset] = clampToUnit(value);

		m_flags[EnableOpacity] = true;

		return this->updateVideoMemory();
	}

	bool
	BasicResource::setAutoIlluminationAmount (float amount) noexcept
	{
		if ( this->isCreated() && !m_flags[EnableAutoIllumination] )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is already created ! Unable to enable the auto-illumination or change the value.";

			return false;
		}

		m_materialProperties[AutoIlluminationOffset] = amount;

		m_flags[EnableAutoIllumination] = true;

		return this->updateVideoMemory();
	}

	std::shared_ptr< BasicResource >
	BasicResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->basicMaterials().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< BasicResource >
	BasicResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->basicMaterials().getDefaultResource();
	}
}
