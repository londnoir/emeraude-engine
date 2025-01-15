/*
 * src/Saphir/Generator/SceneRendering.cpp
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

#include "SceneRendering.hpp"

/* Local inclusions. */
#include "Libraries/SourceCodeParser.hpp"
#include "Graphics/Renderer.hpp"
#include "Vulkan/GraphicsPipeline.hpp"
#include "Saphir/Code.hpp"
#include "Saphir/Keys.hpp"
#include "Scenes/Scene.hpp"
#include "Tracer.hpp"

namespace Emeraude::Saphir::Generator
{
	using namespace Libraries;
	using namespace Graphics;
	using namespace Vulkan;
	using namespace Keys;

	SceneRendering::SceneRendering (Settings & settings, const std::string & name, const std::shared_ptr< const RenderTarget::Abstract > & renderTarget, const std::shared_ptr< const RenderableInstance::Abstract > & renderableInstance, size_t layerIndex, RenderPassType renderPassType, const Scenes::Scene & scene) noexcept
		: Abstract(settings, name, renderTarget), m_renderPassType(renderPassType), m_lightGenerator(renderPassType), m_renderableInstance(renderableInstance), m_layerIndex(layerIndex), m_scene(&scene)
	{

	}

	void
	SceneRendering::prepareUniformSets (SetIndexes & setIndexes) noexcept
	{
		setIndexes.enableSet(SetType::PerView);

		if ( m_renderableInstance->isLightingEnabled() )
		{
			switch ( m_renderPassType )
			{
				case RenderPassType::DirectionalLightPass :
				case RenderPassType::DirectionalLightPassNoShadow :
				case RenderPassType::PointLightPass :
				case RenderPassType::PointLightPassNoShadow :
				case RenderPassType::SpotLightPass :
				case RenderPassType::SpotLightPassNoShadow :
					setIndexes.enableSet(SetType::PerLight);
					break;

				default:
					break;
			}
		}

		if ( this->materialEnabled() )
		{
			setIndexes.enableSet(SetType::PerModelLayer);
		}
	}

	bool
	SceneRendering::onGenerateProgram (Program & program) noexcept
	{
		/* Configure the light generator with the material for all shaders. */
		if ( m_renderableInstance->isLightingEnabled() )
		{
			if ( m_renderPassType == RenderPassType::SimplePass && m_scene->lightSet().isUsingStaticLighting() )
			{
				const auto * staticLighting = m_scene->lightSet().getStaticLighting();

				if ( staticLighting == nullptr )
				{
					TraceError{ClassId} << "The static lighting is not available from the scene !";

					return false;
				}

				m_lightGenerator.setStaticLighting(staticLighting);
			}

			if ( this->materialEnabled() )
			{
				if ( !this->material()->setupLightGenerator(m_lightGenerator) )
				{
					TraceError{ClassId} << "Unable to configure the light generator with material '" << this->material()->name() << "' !";

					return false;
				}
			}
		}

		/* Generate the vertex shader stage. */
		if ( this->generateVertexShader(program) )
		{
			if ( this->debuggingEnabled() )
			{
				const auto * shader = program.vertexShader();

				TraceSuccess{ClassId} << "Vertex shader source '" << shader->name() << "' code generated.";

				TraceDebug{ClassId} << "\n" <<
					"****** START OF GENERATED GLSL VERTEX SHADER CODE ******" "\n" <<
					SourceCodeParser::parse(shader->sourceCode()) <<
					"****** END OF GENERATED GLSL VERTEX SHADER CODE ******" "\n" <<
					shader->getDeclarationStats() << "\n";
			}
		}
		else
		{
			Tracer::error(ClassId, "Unable to generate source code for the vertex shader stage !");

			return false;
		}

		/* Generate the fragment shader stage. */
		if ( this->generateFragmentShader(program) )
		{
			if ( this->debuggingEnabled() )
			{
				const auto * shader = program.fragmentShader();

				TraceSuccess{ClassId} << "Fragment shader source '" << shader->name() << "' code generated.";

				TraceDebug{ClassId} << "\n" <<
					"****** START OF GENERATED GLSL FRAGMENT SHADER CODE ******" "\n" <<
					SourceCodeParser::parse(shader->sourceCode()) <<
					"****** END OF GENERATED GLSL FRAGMENT SHADER CODE ******" "\n" <<
					shader->getDeclarationStats() << "\n";
			}
		}
		else
		{
			Tracer::error(ClassId, "Unable to generate source code for the fragment shader stage !");

			return false;
		}

		if ( this->debuggingEnabled() )
		{
			const auto shaderList = program.getShaderList();

			for ( const auto & shader: shaderList )
			{
				TraceDebug{ClassId} <<
					to_string(shader->type()) << " '" << shader->name() << "' generated into "
					"a source code of " << shader->sourceCode().size() << " bytes !";
			}
		}

		return true;
	}

	bool
	SceneRendering::isAdvancedRendering () const noexcept
	{
		if ( this->material()->isComplex() )
		{
			return true;
		}

		switch ( m_renderPassType )
		{
			case RenderPassType::SimplePass :
				return m_scene->lightSet().isUsingStaticLighting();

			case RenderPassType::DirectionalLightPass :
			case RenderPassType::DirectionalLightPassNoShadow :
			case RenderPassType::PointLightPass :
			case RenderPassType::PointLightPassNoShadow :
			case RenderPassType::SpotLightPass :
			case RenderPassType::SpotLightPassNoShadow :
				return true;

			case RenderPassType::AmbientPass :
			default:
				return false;
		}
	}

	bool
	SceneRendering::onGenerateProgramLayout (const SetIndexes & setIndexes, std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts, std::vector< VkPushConstantRange > & pushConstantRanges) noexcept
	{
		if ( m_scene != nullptr && setIndexes.isSetEnabled(SetType::PerLight) )
		{
			auto descriptorSetLayout = Scenes::LightSet::getDescriptorSetLayout(Renderer::instance()->layoutManager());

			if ( descriptorSetLayout == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the light descriptor set layout !");

				return false;
			}

			descriptorSetLayouts.emplace_back(descriptorSetLayout);
		}

		/* Prepare the descriptor set layout for the model layer. */
		if ( this->materialEnabled() && setIndexes.isSetEnabled(SetType::PerModelLayer) )
		{
			auto descriptorSetLayout = this->material()->descriptorSetLayout();

			if ( descriptorSetLayout == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the material descriptor set layout !");

				return false;
			}

			descriptorSetLayouts.emplace_back(descriptorSetLayout);
		}

		Abstract::generatePushConstantRanges(this->program()->vertexShader()->pushConstantBlockDeclarations(), pushConstantRanges, VK_SHADER_STAGE_VERTEX_BIT);

		return true;
	}

	bool
	SceneRendering::generateVertexShader (Program & program) noexcept
	{
		/* Create the vertex shader. */
		auto * vertexShader = program.initVertexShader(
			this->name( ) + "VertexShader",
			m_renderableInstance->instancingEnabled(),
			this->isAdvancedRendering(),
			m_renderableInstance->isFacingCamera()
		);
		vertexShader->setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

		if ( !this->declareMatrixPushConstantBlock(*vertexShader) )
		{
			return false;
		}

		/* Declare the view uniform block. */
		if ( !this->declareViewUniformBlock(*vertexShader) )
		{
			return false;
		}

		/* NOTE: The position is always required and available. */
		if ( !vertexShader->requestSynthesizeInstruction(ShaderVariable::PositionScreenSpace) )
		{
			return false;
		}

		/* If present, generate the material shader code. */
		if ( this->materialEnabled() && !this->material()->generateVertexShaderCode(*this, *vertexShader) )
		{
			TraceError{ClassId} << "Unable to generate vertex shader code part for material '" << this->material()->name() << "' !";

			return false;
		}

		/* Generate the lighting shader code. */
		if ( m_scene->lightSet().isEnabled() && m_renderableInstance->isLightingEnabled() )
		{
			if ( !m_lightGenerator.generateVertexShaderCode(*this, *vertexShader) )
			{
				Tracer::error(ClassId, "Unable to generate vertex shader code part for lighting !");

				return false;
			}
		}

		return vertexShader->generateSourceCode(*this);
	}

	bool
	SceneRendering::generateFragmentShader (Program & program) noexcept
	{
		/* Create the fragment shader. */
		auto * fragmentShader = program.initFragmentShader(this->name( ) + "FragmentShader");
		fragmentShader->setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

		/* Automatic input declarations from vertex shader. */
		if ( !fragmentShader->connectFromPreviousShader(*program.vertexShader()) )
		{
			return false;
		}

		/* Common part of fragment shader. */
		fragmentShader->declareDefaultOutputFragment();

		/* If a material is present, generate the shader code (optional). */
		if ( this->materialEnabled() && !this->material()->generateFragmentShaderCode(*this, m_lightGenerator, *fragmentShader) )
		{
			TraceError{ClassId} << "Unable to generate fragment shader code part for material '" << this->material()->name() << "' !";

			return false;
		}

		/* If the light is enabled, generate the shader code (optional). */
		if ( m_scene->lightSet().isEnabled() && m_renderableInstance->isLightingEnabled() )
		{
			/* Declare the view uniform block. */
			if ( !m_scene->lightSet().isUsingStaticLighting() && !this->declareViewUniformBlock(*fragmentShader) )
			{
				return false;
			}

			if ( !m_lightGenerator.generateFragmentShaderCode(*this, *fragmentShader) )
			{
				Tracer::error(ClassId, "Unable to generate fragment shader code part for lighting !");

				return false;
			}
		}

		/* Generates the fragment output. */
		if ( m_scene->lightSet().isEnabled() && m_renderableInstance->isLightingEnabled() )
		{
			Code{*fragmentShader, Location::Output} << ShaderVariable::OutputFragment << " = " << m_lightGenerator.fragmentColor() << ';';
		}
		else if ( this->materialEnabled() )
		{
			Code{*fragmentShader, Location::Output} << ShaderVariable::OutputFragment << " = " << this->material()->fragmentColor() << ';';
		}
		else
		{
			Code{*fragmentShader, Location::Output} << ShaderVariable::OutputFragment << " = vec4(1.0, 0.0, 1.0, 1.0);";
		}

		/* TODO: Try to discard before ! */
		if ( this->materialEnabled() && this->material()->blendingMode() != BlendingMode::None )
		{
			Code{*fragmentShader, Location::Output} << "if ( " << ShaderVariable::OutputFragment << ".a <= 0.0 ) discard;";
		}

		return fragmentShader->generateSourceCode(*this);
	}
	
	bool
	SceneRendering::onGraphicsPipelineConfiguration (const Program & /*program*/, GraphicsPipeline & graphicsPipeline) noexcept
	{
		const auto * renderable = m_renderableInstance->renderable();

		if ( !graphicsPipeline.configureRasterizationState(m_renderPassType, renderable->layerRasterizationOptions(m_layerIndex)) )
		{
			Tracer::error(ClassId, "Unable to configure the graphics pipeline rasterization state !");

			return false;
		}

		if ( !graphicsPipeline.configureDepthStencilState(m_renderPassType, *m_renderableInstance) )
		{
			Tracer::error(ClassId, "Unable to configure the graphics pipeline depth/stencil state !");

			return false;
		}

		if ( !graphicsPipeline.configureColorBlendState(m_renderPassType, *renderable->material(m_layerIndex)) )
		{
			Tracer::error(ClassId, "Unable to configure the graphics pipeline color blend state !");

			return false;
		}
		
		return true;
	}
}
