/*
 * Emeraude/Graphics/RenderTarget/ShadowMap/Cubemap.cpp
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

#include "Cubemap.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Saphir/ShaderManager.hpp"
#include "Saphir/ShaderGenerator.hpp"
#include "Vulkan/ShaderModule.hpp"

namespace Emeraude::Graphics::RenderTarget::ShadowMap
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Vulkan;
	using namespace Saphir;
	using namespace Saphir::Keys;

	Cubemap::Cubemap (const std::string & name, uint32_t resolution) noexcept
		: Abstract(name, {}, {resolution, resolution, 1}, RenderType::ShadowCubemap)
	{

	}

	float
	Cubemap::aspectRatio () const noexcept
	{
		return 1.0F;
	}

	bool
	Cubemap::isCubemap () const noexcept
	{
		return true;
	}

	const ViewMatricesInterface &
	Cubemap::viewMatrices () const noexcept
	{
		return m_viewMatrices;
	}

	ViewMatricesInterface &
	Cubemap::viewMatrices () noexcept
	{
		return m_viewMatrices;
	}

	std::vector< VkPipelineShaderStageCreateInfo >
	Cubemap::getShaderStageCreateInfos (const std::shared_ptr< Device > & device, ModelMatrixType modelMatricesType, bool outputAsColor) const noexcept
	{
		std::vector< VkPipelineShaderStageCreateInfo > createInfos{};

		/* Vertex Shader stage. */
		{
			auto shader = std::make_shared< VertexShader >("Cubemap");

			ShaderGenerator generator(shader, modelMatricesType, RenderPassType::SimplePass);
			generator.setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

			generator.requestVertexShaderSynthesizeInstruction(ShaderVariables::GLPositionWorldSpace);

			if ( !generator.writeShader() )
			{
				Tracer::error(ClassId, "Unable to generate the Cubemap vertex shader source code !");

				return {};
			}

			auto shaderModule = ShaderManager::instance()->getShaderModuleFromGeneratedShader(device, shader);

			if ( shaderModule == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the Cubemap vertex shader module !");

				return {};
			}

			createInfos.emplace_back(shaderModule->pipelineShaderStageCreateInfo());
		}

		/* Geometry shader stage */
		{
			auto shader = std::make_shared< GeometryShader >("Cubemap");

			ShaderGenerator gen{shader, modelMatricesType, RenderPassType::SimplePass};
			gen.setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

			/* Input declarations. */
			gen.declare(Cubemap::getViewUniformBlock(0));
			gen.declare(Declaration::InputPrimitive{GLSL::Geometry::In::Primitive::Triangles});

			/* Output declarations. */
			gen.declare(Declaration::OutputPrimitive{GLSL::Geometry::Out::Primitive::TriangleStrip, 18});
			gen.declare(Declaration::StageOutput{ShaderVariables::FragCoord, GLSL::Smooth});

			Code{gen} <<
				"for ( int faceIndex = 0; faceIndex < 6; ++faceIndex )" << Line::End <<
				"{" << Line::End <<
				"	gl_Layer = faceIndex;" << Line::Blank <<

				"	for ( int i = 0; i < gl_in.length(); ++i )" << Line::End <<
				"	{" << Line::End <<
				"		" << ShaderVariables::FragCoord << " = gl_in[i].gl_Position;" << Line::End <<
				"		gl_Position = " << ShaderGenerator::viewIndexedUniform(UniformBlocks::Component::Instance, "faceIndex", UniformBlocks::Component::ViewProjectionMatrix) << " * " << ShaderVariables::FragCoord << ";" << Line::End <<
				"		EmitVertex();" << Line::End <<
				"	}" << Line::Blank <<

				"	EndPrimitive();" << Line::End <<
				"}";

			if ( !gen.writeShader() )
			{
				Tracer::error(ClassId, "Unable to generate the Cubemap geometry shader source code !");

				return {};
			}

			auto shaderModule = ShaderManager::instance()->getShaderModuleFromGeneratedShader(device, shader);

			if ( shaderModule == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the Cubemap geometry shader module !");

				return {};
			}

			createInfos.emplace_back(shaderModule->pipelineShaderStageCreateInfo());
		}

		/* Fragment Shader stage. */
		{
			auto shader = std::make_shared< FragmentShader >("Cubemap");

			ShaderGenerator gen{shader, modelMatricesType, RenderPassType::SimplePass};
			gen.setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

			/* Input declarations. */
			gen.declare(Cubemap::getViewUniformBlock(0));
			gen.declare(Declaration::StageInput{ShaderVariables::FragCoord, GLSL::Smooth});

			/* Output declarations. */
			if ( outputAsColor )
			{
				gen.declareDefaultOutputFragment();
			}

			const auto position = ShaderGenerator::viewIndexedUniform(UniformBlocks::Component::Instance, "0", UniformBlocks::Component::PositionWorldSpace);
			const auto viewProperties = ShaderGenerator::viewIndexedUniform(UniformBlocks::Component::Instance, "0", UniformBlocks::Component::ViewProperties);

			Code{gen} <<
				GLSL::ConstFloat << "const float distance = distance(" << ShaderVariables::FragCoord << ", " << position << ") / " << viewProperties << ".w;";

			/* Fragment as a color output for visualization. */
			if ( outputAsColor )
			{
				Code{gen, Location::Output} <<
											ShaderVariables::OutputFragment << " = vec4(distance, distance, distance, 1.0);";
			}
			else
			{
				Code{gen, Location::Output} <<
											"gl_FragDepth = distance;";
			}

			if ( !gen.writeShader() )
			{
				Tracer::error(ClassId, "Unable to generate the Cubemap fragment shader source code !");

				return {};
			}

			auto shaderModule = ShaderManager::instance()->getShaderModuleFromGeneratedShader(device, shader);

			if ( shaderModule == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the Cubemap fragment shader module !");

				return {};
			}

			createInfos.emplace_back(shaderModule->pipelineShaderStageCreateInfo());
		}

		return createInfos;
	}

	void
	Cubemap::updateDeviceFromCoordinates (const Coordinates< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
	{
		m_viewMatrices.updateViewCoordinates(worldCoordinates, worldVelocity);
	}

	void
	Cubemap::updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept
	{
		const auto & extent = this->extent();

		if ( isPerspectiveProjection )
		{
			m_viewMatrices.updatePerspectiveViewProperties(static_cast< float >(extent.width), static_cast< float >(extent.height), distance, fovOrNear);
		}
		else
		{
			m_viewMatrices.updateOrthographicViewProperties(static_cast< float >(extent.width), static_cast< float >(extent.height), distance, fovOrNear);
		}
	}

	void
	Cubemap::onSourceConnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.create(*this);
	}

	void
	Cubemap::onSourceDisconnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.destroy();
	}

	Declaration::UniformBlock
	Cubemap::getViewUniformBlock (uint32_t set, uint32_t binding) noexcept
	{
		Declaration::Structure structure{Structs::CubemapFace, UniformBlocks::Component::Instance};
		structure.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ViewMatrix);
		structure.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ProjectionMatrix);
		structure.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ViewProjectionMatrix);
		structure.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::PositionWorldSpace);
		structure.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::Velocity);
		structure.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::ViewProperties);
		structure.addMember(Declaration::VariableType::FloatVector4, "_padding");

		Declaration::UniformBlock block{set, binding, Declaration::MemoryLayout::Std140, UniformBlocks::View, BufferBackedBlocks::View};
		block.addArrayMember(structure, 6);

		return block;
	}
}
