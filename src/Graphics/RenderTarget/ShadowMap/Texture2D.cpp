/*
 * Emeraude/Graphics/RenderTarget/ShadowMap/Texture2D.cpp
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

#include "Texture2D.hpp"

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

	Texture2D::Texture2D (const std::string & name, uint32_t resolution) noexcept
		: Abstract(name, {}, {resolution, resolution, 1}, RenderType::ShadowMap)
	{

	}

	bool
	Texture2D::isCubemap () const noexcept
	{
		return false;
	}

	const ViewMatricesInterface &
	Texture2D::viewMatrices () const noexcept
	{
		return m_viewMatrices;
	}

	ViewMatricesInterface &
	Texture2D::viewMatrices () noexcept
	{
		return m_viewMatrices;
	}

	std::vector< VkPipelineShaderStageCreateInfo >
	Texture2D::getShaderStageCreateInfos (const std::shared_ptr< Device > & device, ModelMatrixType modelMatricesType, bool outputAsColor) const noexcept
	{
		std::vector< VkPipelineShaderStageCreateInfo > createInfos{};

		/* Vertex Shader stage. */
		{
			auto shader = std::make_shared< VertexShader >("Texture2D");

			ShaderGenerator generator(shader, modelMatricesType, RenderPassType::SimplePass);
			generator.setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

			generator.requestVertexShaderSynthesizeInstruction(GLSL::Vertex::Out::Position);

			if ( !generator.writeShader() )
			{
				Tracer::error(ClassId, "Unable to generate the Texture2D vertex shader source code !");

				return {};
			}

			auto shaderModule = ShaderManager::instance()->getShaderModuleFromGeneratedShader(device, shader);

			if ( shaderModule == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the Texture2D vertex shader module !");

				return {};
			}

			createInfos.emplace_back(shaderModule->pipelineShaderStageCreateInfo());
		}

		/* Fragment Shader stage. */
		{
			auto shader = std::make_shared< FragmentShader >("Texture2D");

			ShaderGenerator gen(shader, modelMatricesType, RenderPassType::SimplePass);
			gen.setExtensionBehavior("GL_ARB_separate_shader_objects", "enable");

			/* Output declarations.
			 * Fragment as a color output for visualization. */
			if ( outputAsColor )
			{
				gen.declareDefaultOutputFragment();

				Code{gen, Location::Output} <<
											ShaderVariables::OutputFragment << " = vec4(" << GLSL::Fragment::In::FragCoord << ".z);";
			}

			/* Instructions. */
			/* NOTE: Already done by the default behavior. */
			//gen.addOutputInstruction(Blob() << GLSL::Fragment::Out::FragDepth << " = " << GLSL::Fragment::In::FragCoord << ".z;");

			if ( !gen.writeShader() )
			{
				Tracer::error(ClassId, "Unable to generate the Texture2D fragment shader source code !");

				return {};
			}

			auto shaderModule = ShaderManager::instance()->getShaderModuleFromGeneratedShader(device, shader);

			if ( shaderModule == nullptr )
			{
				Tracer::error(ClassId, "Unable to get the Texture2D fragment shader module !");

				return {};
			}

			createInfos.emplace_back(shaderModule->pipelineShaderStageCreateInfo());
		}

		return createInfos;
	}

	void
	Texture2D::updateDeviceFromCoordinates (const Coordinates< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
	{
		m_viewMatrices.updateViewCoordinates(worldCoordinates, worldVelocity);
	}

	void
	Texture2D::updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept
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
	Texture2D::onSourceConnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.create(*this);
	}

	void
	Texture2D::onSourceDisconnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.destroy();
	}

	Declaration::UniformBlock
	Texture2D::getViewUniformBlock (uint32_t set, uint32_t binding) noexcept
	{
		Declaration::UniformBlock block{set, binding, Declaration::MemoryLayout::Std140, UniformBlocks::View, BufferBackedBlocks::View};
		block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ViewMatrix);
		block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ProjectionMatrix);
		block.addMember(Declaration::VariableType::Matrix4, UniformBlocks::Component::ViewProjectionMatrix);
		block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::PositionWorldSpace);
		block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::Velocity);
		block.addMember(Declaration::VariableType::FloatVector4, UniformBlocks::Component::ViewProperties);

		return block;
	}
}
