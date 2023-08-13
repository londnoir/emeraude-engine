/*
 * Emeraude/Graphics/Material/BasicResource.cpp
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

#include "BasicResource.hpp"

/* Local inclusions. */
#include "Component/TypeColor.hpp"
#include "Graphics/Renderer.hpp"
#include "Helpers.hpp"
#include "Resources/Manager.hpp"
#include "Saphir/Keys.hpp"
#include "Saphir/Code.hpp"
#include "Tracer.hpp"
#include "Vulkan/DescriptorSet.hpp"
#include "Vulkan/DescriptorSetLayout.hpp"
#include "Vulkan/SharedUniformBuffer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Material::BasicResource >::ClassId{"BasicResourceContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Material::BasicResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Material
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Saphir;
	using namespace Saphir::Keys;

	const size_t BasicResource::ClassUID{Observable::getClassUID()};
	std::unique_ptr< Vulkan::SharedUniformBuffer > BasicResource::s_sharedUniformBuffer{};

	BasicResource::BasicResource (const std::string & name, int resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	BasicResource::~BasicResource ()
	{
		this->destroy();
	}

	bool
	BasicResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	const char *
	BasicResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	BasicResource::load () noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		this->enableFlag(UsesVertexColors);

		this->setColor(PixelFactory::Magenta);

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
		if ( !data.isMember(DiffuseString) || !data[DiffuseString].isObject() )
		{
			TraceError{ClassId} << "Unable to reach the key '" << DiffuseString << "' key in '" << this->name() << "' Json file ! ";

			return this->setLoadSuccess(false);
		}

		FillingType fillingType{};
		Json::Value componentData{};

		if ( !Component::TypeInterface::parseBase(data[DiffuseString], fillingType, componentData) )
		{
			TraceError{ClassId} << "There is no valid component in '" << this->name() << "' Json file !" << data;

			return this->setLoadSuccess(false);
		}

		switch ( fillingType )
		{
			case FillingType::Color :
			{
				/* NOTE: We use a temporary color component here to keep simplicity on the final material. */
				const Component::TypeColor colorComponent{Saphir::Keys::Uniforms::PrimaryColor, componentData};

				this->setColor(colorComponent.color());
			}
				break;

			case FillingType::Gradient :
			case FillingType::Texture :
			case FillingType::VolumeTexture :
			case FillingType::Cubemap :
			case FillingType::AnimatedTexture :
				{
					m_textureComponent = std::make_unique< Component::TypeTexture >(Saphir::Keys::Uniforms::PrimaryTexture, componentData, fillingType);

					this->enableFlag(TexturingEnabled);
					this->enableFlag(UsesPrimaryTextureCoordinates);

					if ( !this->addDependency(m_textureComponent->texture().get()) )
					{
						return this->setLoadSuccess(false);
					}
				}
				break;

			case FillingType::Value :
			case FillingType::AlphaChannelAsValue :
			case FillingType::None :
				TraceError{ClassId} << "Invalid filling type for material '" << this->name() << "' !";

				return this->setLoadSuccess(false);
		}

		/* Check the optional global auto-illumination amount. */
		auto value = 0.0F;

		if ( Component::TypeInterface::getComponentAsValue(data, AutoIlluminationString, value) )
		{
			this->setAutoIlluminationAmount(value);
		}

		/* Check the optional global opacity. */
		if ( Component::TypeInterface::getComponentAsValue(data, OpacityString, value) )
		{
			this->setOpacity(value);
		}

		return this->setLoadSuccess(true);
	}

	bool
	BasicResource::createSharedUniformBuffer () noexcept
	{
		if ( s_sharedUniformBuffer != nullptr )
		{
			return true;
		}

		const auto uniformBlock = BasicResource::getMaterialUniformBlock(1);

		s_sharedUniformBuffer = std::make_unique< Vulkan::SharedUniformBuffer >(Graphics::Renderer::instance()->device(), uniformBlock, 0);

		return s_sharedUniformBuffer->usable();
	}

	bool
	BasicResource::registerToSharedUniformBuffer () noexcept
	{
		if ( !BasicResource::createSharedUniformBuffer() )
		{
			Tracer::error(ClassId, "Unable to create the shared uniform buffer object !");

			return false;
		}

		if ( !s_sharedUniformBuffer->addElement(this, m_sharedUBOIndex) )
		{
			Tracer::error(ClassId, "Unable to get an UBO !");

			return false;
		}

		return true;
	}

	void
	BasicResource::unregisterFromSharedUniformeBuffer () noexcept
	{
		s_sharedUniformBuffer->removeElement(this);

		if ( s_sharedUniformBuffer->elementCount() == 0 )
		{
			BasicResource::destroySharedUniformBuffer();
		}
	}

	void
	BasicResource::destroySharedUniformBuffer () noexcept
	{
		s_sharedUniformBuffer.reset();
	}

	bool
	BasicResource::create () noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is already created !";

			return true;
		}

		/* Save the material to the shared UBO */
		if ( !this->registerToSharedUniformBuffer() )
		{
			return false;
		}

		/* Component creation (optional). */
		if ( m_textureComponent != nullptr && !m_textureComponent->create() )
		{
			Tracer::error(ClassId, "Unable to create the texture component !");

			return false;
		}

		auto * renderer = Graphics::Renderer::instance();

		m_descriptorSetLayout = renderer->getMaterialDescriptorSetLayout(*this);

		/* Descriptor set creation. */
		m_descriptorSet = std::make_unique< Vulkan::DescriptorSet >(renderer->descriptorPool(), m_descriptorSetLayout);
		m_descriptorSet->setIdentifier("BasicResource-" + this->name() + "-DescriptorSet");

		if ( !m_descriptorSet->create() )
		{
			m_descriptorSet.reset();

			Tracer::error(ClassId, "Unable to create the descriptor set !");

			return false;
		}

		if ( !m_descriptorSet->writeUniformBufferObject(*s_sharedUniformBuffer->uniformBufferObject(m_sharedUBOIndex), 0) )
		{
			Tracer::error(ClassId, "Unable to write the uniform buffer object to the descriptor set !");

			return false;
		}

		if ( m_textureComponent != nullptr &&  !m_descriptorSet->writeCombinedImageSampler(m_textureComponent->texture(), 1) )
		{
			Tracer::error(ClassId, "Unable to write the combined image sampler to the descriptor set !");

			return false;
		}

		if ( !this->updateVideoMemory() )
		{
			Tracer::error(ClassId, "Unable to update the initial video memory !");

			return false;
		}

		this->enableFlag(Created);

		return true;
	}

	bool
	BasicResource::updateVideoMemory () noexcept
	{
		if ( s_sharedUniformBuffer == nullptr )
		{
			return false;
		}

		return s_sharedUniformBuffer->writeElementData(m_sharedUBOIndex, m_materialProperties.data());
	}

	void
	BasicResource::destroy () noexcept
	{
		m_descriptorSet.reset();
		m_descriptorSetLayout.reset();

		m_physicalSurfaceProperties.reset();

		m_textureComponent.reset();

		m_blendingMode = BlendingMode::None;
		m_materialProperties = {
			// Color (4)
			0.3F, 0.3F, 0.3F, 1.0F, // NOLINT(*-magic-numbers)
			// Opacity, auto-illumination, unused, unused.
			1.0F, 0.0F, 0.0F, 0.0F
		};

		m_sharedUBOIndex = 0;
		m_dynamicColorEnabled = false;

		/* Reset to defaults. */
		this->setFlagBits(0);

		this->unregisterFromSharedUniformeBuffer();
	}

	bool
	BasicResource::isCreated () const noexcept
	{
		return this->isFlagEnabled(Created);
	}

	const Physics::PhysicalSurfaceProperties &
	BasicResource::physicalSurfaceProperties () const noexcept
	{
		return m_physicalSurfaceProperties;
	}

	Physics::PhysicalSurfaceProperties &
	BasicResource::physicalSurfaceProperties () noexcept
	{
		return m_physicalSurfaceProperties;
	}

	size_t
	BasicResource::frameCount () const noexcept
	{
		if ( !this->isFlagEnabled(Animated) || m_textureComponent == nullptr )
		{
			return 1;
		}

		const auto * textureResource = m_textureComponent->texture().get();

		if ( textureResource == nullptr )
		{
			return 1;
		}

		return textureResource->frameCount();
	}

	float
	BasicResource::duration () const noexcept
	{
		if ( !this->isFlagEnabled(Animated) || m_textureComponent == nullptr )
		{
			return 0.0F;
		}

		const auto * textureResource = m_textureComponent->texture().get();

		if ( textureResource == nullptr )
		{
			return 0.0F;
		}

		return static_cast< float >(textureResource->duration());
	}

	bool
	BasicResource::isTranslucent () const noexcept
	{
		return this->isFlagEnabled(BlendingEnabled);
	}

	void
	BasicResource::enableBlending () noexcept
	{
		if ( this->isCreated() )
		{
			TraceWarning{ClassId} << "The resource '" << this->name() << "' is already created !";

			return;
		}

		this->enableFlag(BlendingEnabled);

		if ( m_blendingMode == BlendingMode::None )
		{
			m_blendingMode = BlendingMode::Normal;
		}
	}

	void
	BasicResource::setBlendingMode (BlendingMode mode) noexcept
	{
		if ( !this->isFlagEnabled(BlendingEnabled) )
		{
			TraceWarning{ClassId} << "The blending is not enabled with the material resource '" << this->name() << "' !";
		}

		m_blendingMode = mode;
	}

	BlendingMode
	BasicResource::blendingMode () const noexcept
	{
		if ( !this->isFlagEnabled(BlendingEnabled) )
		{
			TraceWarning{ClassId} << "The blending is not enabled with the material resource '" << this->name() << "' !";

			return BlendingMode::None;
		}

		return m_blendingMode;
	}

	std::shared_ptr< Vulkan::DescriptorSetLayout >
	BasicResource::descriptorSetLayout () const noexcept
	{
		return m_descriptorSetLayout;
	}

	const Vulkan::DescriptorSet *
	BasicResource::descriptorSet () const noexcept
	{
		return m_descriptorSet.get();
	}

	bool
	BasicResource::generateShaderCode (Saphir::ShaderGenerator & gen, const Geometry::Interface & geometry) const noexcept
	{
		using namespace Saphir;

		if ( !this->isCreated() )
		{
			TraceError{ClassId} <<
				"The basic material '" << this->name() << "' is not created !"
				"It can't generates a shader source code.";

			return false;
		}

		const auto materialSet = gen.indexes().set(SetType::PerObjectLayer);

		gen.declare(BasicResource::getMaterialUniformBlock(materialSet, 0));

		switch ( gen.shaderType() )
		{
			case ShaderType::VertexShader :
				/* Check texture coordinate attributes. */
				if ( m_textureComponent != nullptr && !checkPrimaryTextureCoordinates(gen, *this, geometry) )
				{
					return false;
				}

				/* Check if the material needs vertex colors. */
				if ( this->usingVertexColors() )
				{
					if ( !geometry.vertexColorEnabled() )
					{
						TraceError{ClassId} <<
							"The geometry " << geometry.name() << " has no vertex color "
							"for basic material '" << this->name() << "' !";

						return false;
					}

					gen.requestVertexShaderSynthesizeInstruction(ShaderVariables::Color);
				}

				return true;

			case ShaderType::FragmentShader :
			{
				gen.declareDefaultOutputFragment();

				if ( m_textureComponent == nullptr )
				{
					if ( this->usingVertexColors() )
					{
						gen.declare(Declaration::StageInput{ShaderVariables::Color, GLSL::Smooth});

						if ( m_dynamicColorEnabled )
						{
							Code{gen, Location::Output} <<
								ShaderVariables::OutputFragment << " = " << ShaderGenerator::materialUniform(UniformBlocks::Component::Color) << " * " << ShaderVariables::Color << ';';
						}
						else
						{
							Code{gen, Location::Output} <<
								ShaderVariables::OutputFragment << " = " << ShaderVariables::Color << ';';
						}
					}
					else
					{
						Code{gen, Location::Output} <<
							ShaderVariables::OutputFragment << " = " << ShaderGenerator::materialUniform(UniformBlocks::Component::Color) << ';';
					}
				}
				else
				{
					const auto * texCoordVariable = m_textureComponent->isVolumetricTexture() ?
						ShaderVariables::Primary3DTextureCoordinates :
						ShaderVariables::Primary2DTextureCoordinates;

					gen.declare(Declaration::Sampler{materialSet, 1, m_textureComponent->textureType(), Uniforms::Diffuse});
					gen.declare(Declaration::StageInput{texCoordVariable, GLSL::Smooth});

					if ( this->usingVertexColors() )
					{
						gen.declare(Declaration::StageInput{ShaderVariables::Color, GLSL::Smooth});

						if ( m_dynamicColorEnabled )
						{
							Code{gen, Location::Output} <<
								ShaderVariables::OutputFragment << " = texture(" << Uniforms::Diffuse << ", " << texCoordVariable << ") * " << ShaderGenerator::materialUniform(UniformBlocks::Component::Color) << " * " << ShaderVariables::Color << ';';
						}
						else
						{
							Code{gen, Location::Output} <<
								ShaderVariables::OutputFragment << " = texture(" << Uniforms::Diffuse << ", " << texCoordVariable << ") * " << ShaderVariables::Color << ';';
						}
					}
					else if ( m_dynamicColorEnabled )
					{
						Code{gen, Location::Output} <<
							ShaderVariables::OutputFragment << " = texture(" << Uniforms::Diffuse << ", " << texCoordVariable << ") * " << ShaderGenerator::materialUniform(UniformBlocks::Component::Color) << ';';
					}
					else
					{
						Code{gen, Location::Output} <<
							ShaderVariables::OutputFragment << " = texture(" << Uniforms::Diffuse << ", " << texCoordVariable << ");";
					}
				}
			}
				return true;

			default:
				break;
		}

		return false;
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

	void
	BasicResource::setColor (const PixelFactory::Color< float > & color) noexcept
	{
		if ( this->isCreated() && !m_dynamicColorEnabled )
		{
			TraceWarning{ClassId} <<
				"The resource '" << this->name() << "' is created ! "
				"Unable to change the dynamic color.";

			return;
		}

		m_materialProperties[0] = color.red();
		m_materialProperties[1] = color.green();
		m_materialProperties[2] = color.blue();
		m_materialProperties[3] = color.alpha();

		m_dynamicColorEnabled = true;

		this->updateVideoMemory();
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

		m_textureComponent = std::make_unique< Component::TypeTexture >(Saphir::Keys::Uniforms::PrimaryTexture, texture);
		m_textureComponent->enableAlpha(enableAlpha);

		this->enableFlag(TexturingEnabled);
		this->enableFlag(UsesPrimaryTextureCoordinates);

		if ( !this->addDependency(m_textureComponent->texture().get()) )
		{
			TraceError{ClassId} << "Unable to set a texture to basic material '" << this->name() << "'.";

			return false;
		}

		return true;
	}

	void
	BasicResource::setAutoIlluminationAmount (float amount) noexcept
	{
		m_materialProperties[5] = amount; // NOLINT(*-magic-numbers)

		this->updateVideoMemory();
	}

	float
	BasicResource::autoIlluminationAmount () noexcept
	{
		return m_materialProperties[5]; // NOLINT(*-magic-numbers)
	}

	void
	BasicResource::setOpacity (float value) noexcept
	{
		m_materialProperties[4] = clampToUnit(value);

		this->updateVideoMemory();
	}

	float
	BasicResource::opacity () noexcept
	{
		return m_materialProperties[4];
	}

	std::shared_ptr< BasicResource >
	BasicResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->basicMaterials().getResource(resourceName, directLoad);
	}

	std::shared_ptr< BasicResource >
	BasicResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->basicMaterials().getDefaultResource();
	}

	Declaration::UniformBlock
	BasicResource::getMaterialUniformBlock (uint32_t set, uint32_t binding) noexcept
	{
		Declaration::UniformBlock block{set, binding, Declaration::MemoryLayout::Std140, UniformBlocks::Material, BufferBackedBlocks::Material};
		block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::Color);
		block.addMember(Declaration::VariableType::Float, UniformBlocks::Component::Shininess);
		block.addMember(Declaration::VariableType::Float, UniformBlocks::Component::Opacity);
		block.addMember(Declaration::VariableType::Float, UniformBlocks::Component::AutoIllumination);

		return block;
	}
}
