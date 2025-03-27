/*
 * src/Saphir/Generator/Abstract.cpp
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

#include "Abstract.hpp"

/* Local inclusions. */
#include "Saphir/Declaration/PushConstantBlock.hpp"
#include "Saphir/Declaration/Structure.hpp"
#include "Saphir/Declaration/Types.hpp"
#include "Saphir/Declaration/UniformBlock.hpp"
#include "Saphir/Code.hpp"
#include "Saphir/Keys.hpp"
#include "Graphics/Geometry/Interface.hpp"
#include "Graphics/Material/Interface.hpp"
#include "Graphics/RenderTarget/Abstract.hpp"
#include "Graphics/VertexBufferFormatManager.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/Types.hpp"
#include "Graphics/ViewMatricesInterface.hpp"
#include "Vulkan/DescriptorSetLayout.hpp"
#include "Vulkan/GraphicsPipeline.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"

namespace EmEn::Saphir::Generator
{
	using namespace EmEn::Libs;
	using namespace Graphics;
	using namespace Vulkan;
	using namespace Keys;

	static constexpr auto TracerTag{"ShaderGenerator"};
	
	Abstract::Abstract (Settings & settings, const std::string & name, const std::shared_ptr< const Graphics::RenderTarget::Abstract > & renderTarget) noexcept
		: NameableTrait(name), m_renderTarget(renderTarget)
	{
		/* FIXME: This should not be done here, but rather in the Renderer */
		m_flags[NormalMappingEnabled] = settings.get< bool >(NormalMappingEnabledKey, DefaultNormalMappingEnabled);
		m_flags[HighQualityLightEnabled] = settings.get< bool >(HighQualityLightEnabledKey, DefaultHighQualityLightEnabled);
		m_flags[HighQualityReflectionEnabled] = settings.get< bool >(HighQualityReflectionEnabledKey, DefaultHighQualityReflectionEnabled);
	}

	bool
	Abstract::generateFallBackVertexShader (Program & program) noexcept
	{
		if ( program.setIndexes().isSetEnabled(SetType::PerView) )
		{
			auto * vertexShader = program.initVertexShader(
				this->name( ) + "FallbackMVPVertexShader",
				program.wasInstancingEnabled(),
				program.wasAdvancedMatricesEnabled(),
				program.wasBillBoardingEnabled()
			);
			vertexShader->setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

			if ( !vertexShader->declare(Declaration::InputAttribute{VertexAttributeType::Position}, true) )
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

			if ( !vertexShader->generateSourceCode(*this) )
			{
				return false;
			}
		}
		else
		{
			auto * vertexShader = program.initVertexShader(
				this->name( ) + "FallbackVertexShader",
				program.wasInstancingEnabled(),
				program.wasAdvancedMatricesEnabled(),
				program.wasBillBoardingEnabled()
			);
			vertexShader->setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

			if ( !vertexShader->declare(Declaration::InputAttribute{VertexAttributeType::Position}, true) )
			{
				return false;
			}

			/* TODO: Try to use at least the model view if exists */
			Code{*vertexShader, Location::Output} << "gl_Position = vec4(" << Attribute::Position << ", 1.0);";

			if ( !vertexShader->generateSourceCode(*this) )
			{
				return false;
			}
		}

		return true;
	}

	bool
	Abstract::generateFallBackFragmentShader (Program & program) noexcept
	{
		auto * fragmentShader = program.initFragmentShader(this->name( ) + "FallbackFragmentShader");
		fragmentShader->setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

		/* Automatic input declarations from the vertex shader. */
		if ( !fragmentShader->connectFromPreviousShader(*program.vertexShader()) )
		{
			return false;
		}

		if ( !fragmentShader->declareDefaultOutputFragment() )
		{
			return false;
		}

		Code{*fragmentShader, Location::Output} << ShaderVariable::OutputFragment << " = vec4(1.0, 0.0, 1.0, 1.0);";

		return fragmentShader->generateSourceCode(*this);
	}

	bool
	Abstract::generateProgram (VertexBufferFormatManager & vertexBufferFormatManager, const std::string & GLSLVersion, const std::string & GLSLProfile) noexcept
	{
		m_program = std::make_shared< Program >(this->name(), GLSLVersion, GLSLProfile);

		/* Prepare the number of binding set and identifier. */
		this->prepareUniformSets(m_program->setIndexes());

		if ( !this->onGenerateProgram(*m_program) )
		{
			Tracer::error(TracerTag, "Unable to generate the program at child shader generator level !");

			return false;
		}

		/* We need the vertex shader to get all vertex attributes really used from the pipeline. */
		const auto * vertexShader = m_program->vertexShader();

		if ( vertexShader == nullptr )
		{
			Tracer::error(TracerTag, "There is no vertex shader to build the vertex buffer format !");

			return false;
		}

		const auto * geometry = this->geometry();

		if ( geometry == nullptr )
		{
			Tracer::error(TracerTag, "There is no geometry to build the vertex buffer format !");

			return false;
		}

		/* Prepare the vertex buffer format. */
		const auto vertexBufferFormat = vertexBufferFormatManager.getVertexBufferFormat(*geometry, *vertexShader);

		if ( vertexBufferFormat == nullptr )
		{
			TraceError{TracerTag} << "Unable to get a vertex buffer format for geometry '" << geometry->name() << "' !";

			return false;
		}

		m_program->setVertexBufferFormat(vertexBufferFormat);

		return true;
	}

	bool
	Abstract::generateProgramLayout (Renderer & renderer) noexcept
	{
		if ( m_program == nullptr || !m_program->isComplete() )
		{
			Tracer::error(TracerTag, "The program pointer is null or the program is not complete !");

			return false;
		}

		std::vector< std::shared_ptr< DescriptorSetLayout > > descriptorSetLayouts{};
		std::vector< VkPushConstantRange > pushConstantRanges{};

		const auto & setIndexes = m_program->setIndexes();

		/* Prepare the descriptor set layout for the view. */
		if ( setIndexes.isSetEnabled(SetType::PerView) )
		{
			/* FIXME: This could be general for render target type. */
			const auto descriptorSetLayout = m_renderTarget->viewMatrices().getDescriptorSetLayout();

			if ( descriptorSetLayout == nullptr )
			{
				Tracer::error(TracerTag, "Unable to get the view descriptor set layout !");

				return false;
			}

			descriptorSetLayouts.emplace_back(descriptorSetLayout);
		}

		/* Let child class generate all other descriptor set layouts. */
		if ( !this->onGenerateProgramLayout(setIndexes, descriptorSetLayouts, pushConstantRanges) )
		{
			return false;
		}

		/* Get the proper pipeline layout according to all descriptor set layouts to build the graphics pipeline.
		 * NOTE: This step will check if the pipeline layout already exists. */
		const auto pipelineLayout = renderer.layoutManager().getPipelineLayout(descriptorSetLayouts, pushConstantRanges);

		if ( pipelineLayout == nullptr )
		{
			Tracer::error(TracerTag, "Unable to get the pipeline layout !");

			return false;
		}

		m_program->setPipelineLayout(pipelineLayout);

		return true;
	}

	bool
	Abstract::createGraphicsPipeline (Renderer & renderer) noexcept
	{
		if ( m_program == nullptr || !m_program->isDescribed() )
		{
			Tracer::error(TracerTag, "The program pointer is null or the program is not described in layouts !");

			return false;
		}

		/* Create a graphics pipeline base and configure it before letting the renderer handle the final invocation on GPU.  */
		auto graphicsPipeline = std::make_shared< GraphicsPipeline >(renderer.device());
		graphicsPipeline->setIdentifier(TracerTag, this->name(), "Pipeline");

		{
			auto shaderModules = renderer.shaderManager().getShaderModules(renderer.device(), m_program);

			if ( shaderModules.empty() || !graphicsPipeline->configureShaderStages(shaderModules) )
			{
				Tracer::error(TracerTag, "Unable to configure the graphics pipeline with shader stages !");

				return false;
			}
		}

		const auto & vertexBufferFormat = *m_program->vertexBufferFormat();

		if ( !graphicsPipeline->configureVertexInputState(vertexBufferFormat) )
		{
			Tracer::error(TracerTag, "Unable to configure the graphics pipeline vertex input state !");

			return false;
		}

		if ( !graphicsPipeline->configureInputAssemblyState(vertexBufferFormat) )
		{
			Tracer::error(TracerTag, "Unable to configure the graphics pipeline input assembly state !");

			return false;
		}

		/* NOTE: If tesselation wasn't enabled, there is no point to configure it. */
		if ( m_program->useTesselation() )
		{
			if ( !graphicsPipeline->configureTessellationState(0) )
			{
				Tracer::error(TracerTag, "Unable to configure the graphics pipeline tesselation state !");

				return false;
			}
		}

		/* FIXME: Only to get the width/height. This can become a dynamic state ! */
		const auto & extent = m_renderTarget->extent();

		if ( !graphicsPipeline->configureViewportState(extent.width, extent.height) )
		{
			Tracer::error(TracerTag, "Unable to configure the graphics pipeline viewport state !");

			return false;
		}

		/* FIXME: Only to get the framebuffer sampler. This can become a dynamic state or a global settings. ! */
		if ( !graphicsPipeline->configureMultisampleState(*m_renderTarget) )
		{
			Tracer::error(TracerTag, "Unable to configure the graphics pipeline multisample state !");

			return false;
		}

		if ( !this->onGraphicsPipelineConfiguration(*m_program, *graphicsPipeline) )
		{
			Tracer::error(TracerTag, "Unable to configure the graphics pipeline at child shader generator level !");

			return false;
		}

		/* FIXME: Only to get the render pass handle. This can become general for the render target type. ! */
		if ( !renderer.finalizeGraphicsPipeline(*m_renderTarget, *m_program, graphicsPipeline) )
		{
			TraceError{TracerTag} << "Unable to finalize the graphics pipeline of the program '" << m_program->name() << "' !";

			return false;
		}

		m_program->setGraphicsPipeline(graphicsPipeline);

		return true;
	}

	uint32_t
	Abstract::getNextShaderVariableLocation (uint32_t increment) noexcept
	{
		const auto location = m_nextShaderVariableLocation;

		m_nextShaderVariableLocation += increment;

		return location;
	}

	bool
	Abstract::declareMatrixPushConstantBlock (AbstractShader & shader) const noexcept
	{
		/* [VULKAN-PUSH-CONSTANT:1] Declare push constant usage by analyzing needs. */
		Declaration::PushConstantBlock pushConstantBlock{PushConstant::Type::Matrices, PushConstant::Matrices};

		if ( m_program->wasInstancingEnabled() )
		{
			if ( m_program->wasAdvancedMatricesEnabled() || m_program->wasBillBoardingEnabled() )
			{
				/* NOTE: Push the view matrix (V) and the view projection matrix (VP). */
				pushConstantBlock.addMember(Declaration::VariableType::Matrix4, PushConstant::Component::ViewMatrix);
				pushConstantBlock.addMember(Declaration::VariableType::Matrix4, PushConstant::Component::ViewProjectionMatrix);
			}
			else
			{
				/* NOTE: Push the view projection matrix (VP). */
				pushConstantBlock.addMember(Declaration::VariableType::Matrix4, PushConstant::Component::ViewProjectionMatrix);
			}
		}
		else
		{
			if ( m_program->wasAdvancedMatricesEnabled() )
			{
				/* NOTE: Push the view matrix (V) and the model matrix (M). */
				pushConstantBlock.addMember(Declaration::VariableType::Matrix4, PushConstant::Component::ViewMatrix);
				pushConstantBlock.addMember(Declaration::VariableType::Matrix4, PushConstant::Component::ModelMatrix);
			}
			else
			{
				/* NOTE: Push the model view projection matrix (MVP). */
				pushConstantBlock.addMember(Declaration::VariableType::Matrix4, PushConstant::Component::ModelViewProjectionMatrix);
			}
		}

		return shader.declare(pushConstantBlock);
	}

	void
	Abstract::generatePushConstantRanges (const std::vector< Declaration::PushConstantBlock > & pushConstantBlocks, std::vector< VkPushConstantRange > & pushConstantRanges, VkShaderStageFlags stageFlags) noexcept
	{
		/* [VULKAN-PUSH-CONSTANT:2] Prepare the push constants declaration for pipeline. */
		uint32_t offset = 0;

		for ( const auto & pushConstantBlock : pushConstantBlocks )
		{
			const auto bytes = static_cast< uint32_t >(pushConstantBlock.bytes());

			pushConstantRanges.push_back({
				.stageFlags = stageFlags,
				.offset = offset,
				.size = bytes
			});

			offset += bytes;
		}

		/*for ( const auto & pushConstantBlock : pushConstantBlocks )
		{
			uint32_t offset = 0;

			for ( const auto & range : pushConstantBlock.members() )
			{
				const uint32_t bytes = range.second.bytes();

				pushConstantRanges.push_back({
					.stageFlags = stageFlags,
					.offset = offset,
					.size = bytes
				});

				offset += bytes;
			}
		}*/
	}

	bool
	Abstract::declareViewUniformBlock (AbstractShader & shader, uint32_t binding) const noexcept
	{
		const auto setIndex = m_program->setIndex(SetType::PerView);

		/* FIXME: This information could bet set at generator constructor. */
		if ( m_renderTarget->isCubemap() )
		{
			/* FIXME: Rework this to split common data between each cubemap faces ! */
			Declaration::Structure structure{Struct::CubemapFace, UniformBlock::Component::Instance};
			structure.addMember(Declaration::VariableType::Matrix4, UniformBlock::Component::ProjectionMatrix);
			structure.addMember(Declaration::VariableType::FloatVector4, UniformBlock::Component::PositionWorldSpace);
			structure.addMember(Declaration::VariableType::FloatVector4, UniformBlock::Component::Velocity);
			structure.addMember(Declaration::VariableType::FloatVector4, UniformBlock::Component::ViewProperties);
			structure.addMember(Declaration::VariableType::FloatVector4, "_padding");

			Declaration::UniformBlock uniformBlock{setIndex, binding, Declaration::MemoryLayout::Std140, UniformBlock::Type::CubemapView, UniformBlock::View};
			uniformBlock.addArrayMember(structure, 6);

			return shader.declare(uniformBlock);
		}

		Declaration::UniformBlock uniformBlock{setIndex, binding, Declaration::MemoryLayout::Std140, UniformBlock::Type::View, UniformBlock::View};
		uniformBlock.addMember(Declaration::VariableType::Matrix4, UniformBlock::Component::ProjectionMatrix);
		uniformBlock.addMember(Declaration::VariableType::FloatVector4, UniformBlock::Component::PositionWorldSpace);
		uniformBlock.addMember(Declaration::VariableType::FloatVector4, UniformBlock::Component::Velocity);
		uniformBlock.addMember(Declaration::VariableType::FloatVector4, UniformBlock::Component::ViewProperties);
		uniformBlock.addMember(Declaration::VariableType::FloatVector4, UniformBlock::Component::AmbientLightColor);
		uniformBlock.addMember(Declaration::VariableType::Float, UniformBlock::Component::AmbientLightIntensity);

		return shader.declare(uniformBlock);
	}

	bool
	Abstract::declareMaterialUniformBlock (const Material::Interface & material, AbstractShader & shader, uint32_t binding) const noexcept
	{
		const auto setIndex = m_program->setIndex(SetType::PerModelLayer);
		const auto uniformBlock = material.getUniformBlock(setIndex, binding);

		return shader.declare(uniformBlock);
	}
}
