/*
 * Emeraude/Vulkan/GraphicsPipeline.cpp
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

#include "GraphicsPipeline.hpp"

/* C/C++ standard libraries */
//#include <utility> c++23 std::to_underlying()

/* Local inclusions */
#include "Device.hpp"
#include "Graphics/RenderableInstance/Abstract.hpp"
#include "ShaderModule.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"
/* FIXME: Remove this */
#include "Saphir/LightGenerator.hpp"
#include "Saphir/ShaderManager.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;
	using namespace Graphics;
	using namespace Saphir;
	using namespace Saphir::Keys;

	size_t GraphicsPipeline::s_fakeHash = 0;

	GraphicsPipeline::GraphicsPipeline (const std::shared_ptr< PipelineLayout > & pipelineLayout, const std::shared_ptr< RenderableInstance::VertexBufferFormat > & vertexBufferFormat, const GraphicsShaderContainer & shaders, VkPipelineCreateFlags createFlags) noexcept
		: AbstractDeviceDependentObject(pipelineLayout->device()),
		m_pipelineLayout(pipelineLayout),
		m_vertexBufferFormat(vertexBufferFormat),
		m_shaders(shaders.getShaderList())
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
		m_createInfo.stageCount = 0;
		m_createInfo.pStages = nullptr;
		m_createInfo.pVertexInputState = nullptr;
		m_createInfo.pInputAssemblyState = nullptr;
		m_createInfo.pTessellationState = nullptr;
		m_createInfo.pViewportState = nullptr;
		m_createInfo.pRasterizationState = nullptr;
		m_createInfo.pMultisampleState = nullptr;
		m_createInfo.pDepthStencilState = nullptr;
		m_createInfo.pColorBlendState = nullptr;
		m_createInfo.pDynamicState = nullptr;
		m_createInfo.layout = VK_NULL_HANDLE;
		m_createInfo.renderPass = VK_NULL_HANDLE;
		m_createInfo.subpass = 0;
		m_createInfo.basePipelineHandle = VK_NULL_HANDLE;
		m_createInfo.basePipelineIndex = -1;
	}

	GraphicsPipeline::GraphicsPipeline (const std::shared_ptr< PipelineLayout > & pipelineLayout, const std::shared_ptr< RenderableInstance::VertexBufferFormat > & vertexBufferFormat, const GraphicsShaderContainer & shaders, const VkGraphicsPipelineCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(pipelineLayout->device()),
		m_createInfo(createInfo),
		m_pipelineLayout(pipelineLayout),
		m_vertexBufferFormat(vertexBufferFormat),
		m_shaders(shaders.getShaderList())
	{

	}

	GraphicsPipeline::~GraphicsPipeline ()
	{
		this->destroyFromHardware();
	}

	bool
	GraphicsPipeline::checkPrerequisites (const RenderTarget::Abstract & renderTarget, const RenderableInstance::Abstract & renderableInstance) noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this graphics pipeline !");

			return false;
		}

		if ( m_pipelineLayout == nullptr )
		{
			Tracer::error(ClassId, "No pipeline layout to create this graphics pipeline !");

			return false;
		}

		/* NOTE: Checking the vertex buffer format. */
		if ( m_vertexBufferFormat == nullptr )
		{
			Tracer::error(ClassId, "The vertex buffer format is a null pointer !");

			return false;
		}

		if ( m_vertexBufferFormat->binding(0) == nullptr )
		{
			Tracer::error(ClassId, "Vertex buffer format binding #0 is null !");

			return false;
		}

		/* NOTE: Checking the shaders. */
		if ( m_shaders.empty() )
		{
			Tracer::error(ClassId, "The shader list is empty !");

			return false;
		}

		if ( std::ranges::any_of(m_shaders, [] (const auto & shader) {return shader == nullptr;}) )
		{
			Tracer::error(ClassId, "Some shader in the list is a null pointer !");

			return false;
		}

		if ( !renderTarget.isValid() )
		{
			TraceError{ClassId} << "The renderable target '" << renderTarget.id() << "' is not valid !";

			return false;
		}

		/*if ( !renderableInstance.isReadyToRender() )
		{
			Tracer::error(ClassId, "The renderable instance is not ready to render !");

			return false;
		}*/

		return true;
	}

	bool
	GraphicsPipeline::create (const RenderTarget::Abstract & renderTarget, const RenderableInstance::Abstract & renderableInstance) noexcept
	{
		if ( !this->checkPrerequisites(renderTarget, renderableInstance) )
		{
			Tracer::error(ClassId, "Prerequisites are not met, cancelling pipeline creation ...");

			return false;
		}

		if ( !this->generateShaderStages() )
		{
			Tracer::error(ClassId, "Unable to configure shader modules !");

			return false;
		}

		if ( !this->generateVertexInputState() )
		{
			Tracer::error(ClassId, "Unable to configure vertex input state !");

			return false;
		}

		if ( !this->generateInputAssemblyState() )
		{
			Tracer::error(ClassId, "Unable to configure input assembly state !");

			return false;
		}

		/*if ( !this->generateTessellationState(0) )
		{
			Tracer::error(ClassId, "Unable to configure tessellation state !");

			return false;
		}*/

		if ( !this->generateViewportState(renderTarget) )
		{
			Tracer::error(ClassId, "Unable to configure viewport state !");

			return false;
		}

		if ( !this->generateRasterizationState() )
		{
			Tracer::error(ClassId, "Unable to configure rasterization state !");

			return false;
		}

		if ( !this->generateMultisampleState() )
		{
			Tracer::error(ClassId, "Unable to configure multisample state !");

			return false;
		}

		if ( !this->generateDepthStencilState(renderableInstance) )
		{
			Tracer::error(ClassId, "Unable to configure depth/stencil state !");

			return false;
		}

		if ( !this->generateColorBlendState() )
		{
			Tracer::error(ClassId, "Unable to configure color blend state !");

			return false;
		}

		/* NOTE: determine the dynamic states. */
		/*std::vector< VkDynamicState > dynamicStates{
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR,
			VK_DYNAMIC_STATE_LINE_WIDTH,
			VK_DYNAMIC_STATE_DEPTH_BIAS,
			VK_DYNAMIC_STATE_BLEND_CONSTANTS,
			VK_DYNAMIC_STATE_DEPTH_BOUNDS,
			VK_DYNAMIC_STATE_STENCIL_COMPARE_MASK,
			VK_DYNAMIC_STATE_STENCIL_WRITE_MASK,
			VK_DYNAMIC_STATE_STENCIL_REFERENCE,
			VK_DYNAMIC_STATE_VIEWPORT_W_SCALING_NV, // Provided by VK_NV_clip_space_w_scaling
			VK_DYNAMIC_STATE_DISCARD_RECTANGLE_EXT, // Provided by VK_EXT_discard_rectangles
			VK_DYNAMIC_STATE_SAMPLE_LOCATIONS_EXT, // Provided by VK_EXT_sample_locations
			VK_DYNAMIC_STATE_RAY_TRACING_PIPELINE_STACK_SIZE_KHR, // Provided by VK_KHR_ray_tracing_pipeline
			VK_DYNAMIC_STATE_VIEWPORT_SHADING_RATE_PALETTE_NV, // Provided by VK_NV_shading_rate_image
			VK_DYNAMIC_STATE_VIEWPORT_COARSE_SAMPLE_ORDER_NV, // Provided by VK_NV_shading_rate_image
			VK_DYNAMIC_STATE_EXCLUSIVE_SCISSOR_NV, // Provided by VK_NV_scissor_exclusive
			VK_DYNAMIC_STATE_FRAGMENT_SHADING_RATE_KHR, // Provided by VK_KHR_fragment_shading_rate
			VK_DYNAMIC_STATE_LINE_STIPPLE_EXT, // Provided by VK_EXT_line_rasterization
			VK_DYNAMIC_STATE_CULL_MODE_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_FRONT_FACE_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_VIEWPORT_WITH_COUNT_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_SCISSOR_WITH_COUNT_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_VERTEX_INPUT_BINDING_STRIDE_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_DEPTH_TEST_ENABLE_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_DEPTH_WRITE_ENABLE_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_DEPTH_COMPARE_OP_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_DEPTH_BOUNDS_TEST_ENABLE_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_STENCIL_TEST_ENABLE_EXT, // Provided by VK_EXT_extended_dynamic_state
			VK_DYNAMIC_STATE_STENCIL_OP_EXT // Provided by VK_EXT_extended_dynamic_state
		};

		if ( !this->generateDynamicState(dynamicStates) )
		{
			Tracer::error(ClassId, "Unable to configure dynamic state !");

			return false;
		};*/

		m_createInfo.layout = m_pipelineLayout->handle();
		m_createInfo.renderPass = renderTarget.renderPass()->handle();

		return this->createOnHardware();
	}

	bool
	GraphicsPipeline::recreate () noexcept
	{
		Tracer::error(ClassId, "This method is disable, use recreate(renderTarget) instead.");

		return false;
	}

	bool
	GraphicsPipeline::recreate (const RenderTarget::Abstract & renderTarget, const RenderableInstance::Abstract & renderableInstance) noexcept
	{
		if ( !this->checkPrerequisites(renderTarget, renderableInstance) )
		{
			Tracer::error(ClassId, "Prerequisites are not met, cancelling pipeline creation ...");

			return false;
		}

		if ( !this->generateViewportState(renderTarget) )
		{
			Tracer::error(ClassId, "Unable to configure viewport state !");

			return false;
		}

		if ( !this->generateDepthStencilState(renderableInstance) )
		{
			Tracer::error(ClassId, "Unable to configure depth/stencil state !");

			return false;
		}

		m_createInfo.renderPass = renderTarget.renderPass()->handle();

		return this->createOnHardware();
	}

	bool
	GraphicsPipeline::createOnHardware () noexcept
	{
		const auto result = vkCreateGraphicsPipelines(this->device()->handle(), VK_NULL_HANDLE, 1, &m_createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create a graphics pipeline : " << vkResultToCString(result) << " !";

			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The graphics pipeline " << m_handle << " (" << this->identifier() << ") is successfully created !";

		return true;
	}

	bool
	GraphicsPipeline::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the graphics pipeline " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		if ( m_handle != nullptr )
		{
			this->device()->waitIdle();

			vkDestroyPipeline(this->device()->handle(), m_handle, nullptr);

			TraceSuccess{ClassId} << "The graphics pipeline " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		m_pipelineLayout.reset();

		this->setDestroyed();

		return true;
	}

	VkPipeline
	GraphicsPipeline::handle () const noexcept
	{
		return m_handle;
	}

	std::shared_ptr< PipelineLayout >
	GraphicsPipeline::pipelineLayout () const noexcept
	{
		return m_pipelineLayout;
	}

	const std::vector< VkPipelineColorBlendAttachmentState > &
	GraphicsPipeline::colorBlendAttachments () const noexcept
	{
		return m_colorBlendAttachments;
	}

	bool
	GraphicsPipeline::generateShaderStages () noexcept
	{
		m_shaderStages.clear();

		for ( const auto & shader : m_shaders )
		{
			auto shaderModule = ShaderManager::instance()->getShaderModuleFromGeneratedShader(this->device(), shader);

			if ( shaderModule == nullptr )
			{
				TraceError{ClassId} << "Unable to create the shader module from the shader '" << shader->name() << "' source code !";

				return false;
			}

			m_shaderStages.emplace_back(shaderModule->pipelineShaderStageCreateInfo());
		}

		m_createInfo.stageCount = m_shaderStages.size();
		m_createInfo.pStages = m_shaderStages.data();

		return true;
	}

	bool
	GraphicsPipeline::generateVertexInputState (VkPipelineVertexInputStateCreateFlags flags) noexcept
	{
		m_vertexInputState.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		m_vertexInputState.pNext = nullptr;
		m_vertexInputState.flags = flags;

		if ( m_vertexBufferFormat != nullptr )
		{
			const auto & bindings = m_vertexBufferFormat->bindings();
			const auto & attributes = m_vertexBufferFormat->attributes();

			m_vertexInputState.vertexBindingDescriptionCount = bindings.size();
			m_vertexInputState.pVertexBindingDescriptions = bindings.data();
			m_vertexInputState.vertexAttributeDescriptionCount = attributes.size();
			m_vertexInputState.pVertexAttributeDescriptions = attributes.data();
		}
		else
		{
			m_vertexInputState.vertexBindingDescriptionCount = 0;
			m_vertexInputState.pVertexBindingDescriptions = nullptr;
			m_vertexInputState.vertexAttributeDescriptionCount = 0;
			m_vertexInputState.pVertexAttributeDescriptions = nullptr;
		}

		m_createInfo.pVertexInputState = &m_vertexInputState;

		return true;
	}

	bool
	GraphicsPipeline::generateInputAssemblyState (VkPipelineInputAssemblyStateCreateFlags flags) noexcept
	{
		const auto * binding = m_vertexBufferFormat->binding(0);

		m_inputAssemblyState.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		m_inputAssemblyState.pNext = nullptr;
		m_inputAssemblyState.flags = flags;

		switch ( binding->topology() )
		{
			case Topology::PointList :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
				break;

			case Topology::LineLine :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
				break;

			case Topology::LineStrip :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
				break;

			case Topology::TriangleList :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
				break;

			case Topology::TriangleStrip :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
				break;

			case Topology::TriangleFan :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
				break;

			case Topology::LineListWithAdjacency :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
				break;

			case Topology::LineStripWithAdjacency :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
				break;

			case Topology::TriangleListWithAdjacency :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
				break;

			case Topology::TriangleStripWithAdjacency :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
				break;

			case Topology::PatchList :
				m_inputAssemblyState.topology = VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
				break;

			case Topology::CustomData :
			case Topology::Invalid :
				return false;
		}

		m_inputAssemblyState.primitiveRestartEnable = binding->requestPrimitiveRestart() ? VK_TRUE : VK_FALSE;

		m_createInfo.pInputAssemblyState = &m_inputAssemblyState;

		return true;
	}

	bool
	GraphicsPipeline::generateTessellationState (uint32_t patchControlPoints, VkPipelineTessellationStateCreateFlags flags) noexcept
	{
		if ( patchControlPoints == 0 )
		{
			Tracer::error(ClassId, "There is no patch control points for the tesselation state !");

			return false;
		}

		m_tessellationState.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
		m_tessellationState.pNext = nullptr;
		m_tessellationState.flags = flags;
		m_tessellationState.patchControlPoints = patchControlPoints;

		m_createInfo.pTessellationState = &m_tessellationState;

		return true;
	}

	bool
	GraphicsPipeline::generateViewportState (const RenderTarget::Abstract & renderTarget, VkPipelineViewportStateCreateFlags flags) noexcept
	{
		const auto & extent = renderTarget.extent();

		TraceInfo{ClassId} << "The graphics pipeline viewport is " << extent.width << "X" << extent.height << ".";

		if ( m_viewports.empty() )
		{
			m_viewports.resize(1);
		}

		m_viewports[0].x = 0.0F;
		m_viewports[0].y = 0.0F;
		m_viewports[0].width = static_cast< float >(extent.width);
		m_viewports[0].height = static_cast< float >(extent.height);
		m_viewports[0].minDepth = 0.0F;
		m_viewports[0].maxDepth = 1.0F;


		if ( m_scissors.empty() )
		{
			m_scissors.resize(1);
		}

		m_scissors[0].offset = {0, 0};
		m_scissors[0].extent.width = extent.width;
		m_scissors[0].extent.height = extent.height;

		m_viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		m_viewportState.pNext = nullptr;
		m_viewportState.flags = flags;
		m_viewportState.viewportCount = m_viewports.size();
		m_viewportState.pViewports = m_viewports.data();
		m_viewportState.scissorCount = m_scissors.size();
		m_viewportState.pScissors = m_scissors.data();

		m_createInfo.pViewportState = &m_viewportState;

		return true;
	}

	bool
	GraphicsPipeline::generateRasterizationState (VkPipelineRasterizationStateCreateFlags flags) noexcept
	{
		m_rasterizationState.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		m_rasterizationState.pNext = nullptr;
		m_rasterizationState.flags = flags;
		m_rasterizationState.depthClampEnable = VK_FALSE;
		m_rasterizationState.rasterizerDiscardEnable = VK_FALSE;
		/*
			VK_POLYGON_MODE_FILL = 0,
			VK_POLYGON_MODE_LINE = 1,
			VK_POLYGON_MODE_POINT = 2,
			VK_POLYGON_MODE_FILL_RECTANGLE_NV = 1000153000,
		*/
		m_rasterizationState.polygonMode = VK_POLYGON_MODE_FILL;//VK_POLYGON_MODE_LINE;
		m_rasterizationState.cullMode = VK_CULL_MODE_BACK_BIT;
		m_rasterizationState.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		m_rasterizationState.depthBiasEnable = VK_FALSE;
		m_rasterizationState.depthBiasConstantFactor = 0.0F;
		m_rasterizationState.depthBiasClamp = 0.0F;
		m_rasterizationState.depthBiasSlopeFactor = 0.0F;
		m_rasterizationState.lineWidth = 1.0F;

		m_createInfo.pRasterizationState = &m_rasterizationState;

		return true;
	}

	bool
	GraphicsPipeline::generateMultisampleState (VkPipelineMultisampleStateCreateFlags flags) noexcept
	{
		m_multisampleState.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		m_multisampleState.pNext = nullptr;
		m_multisampleState.flags = flags;
		m_multisampleState.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
		m_multisampleState.sampleShadingEnable = VK_FALSE;
		m_multisampleState.minSampleShading = 1.0F;
		m_multisampleState.pSampleMask = nullptr;
		m_multisampleState.alphaToCoverageEnable = VK_FALSE;
		m_multisampleState.alphaToOneEnable = VK_FALSE;

		m_createInfo.pMultisampleState = &m_multisampleState;

		return true;
	}

	bool
	GraphicsPipeline::generateDepthStencilState (const RenderableInstance::Abstract & renderableInstance, VkPipelineDepthStencilStateCreateFlags flags) noexcept
	{
		m_depthStencilState.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		m_depthStencilState.pNext = nullptr;
		m_depthStencilState.flags = flags;
		m_depthStencilState.depthTestEnable = renderableInstance.isDepthTestDisabled() ? VK_FALSE : VK_TRUE;
		m_depthStencilState.depthWriteEnable = renderableInstance.isDepthWriteDisabled() ? VK_FALSE : VK_TRUE;
		m_depthStencilState.depthCompareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		m_depthStencilState.depthBoundsTestEnable = VK_FALSE;
		m_depthStencilState.stencilTestEnable = VK_FALSE;
		/*m_depthStencilState.front.failOp = VK_STENCIL_OP_ZERO;
		m_depthStencilState.front.passOp = VK_STENCIL_OP_KEEP;
		m_depthStencilState.front.depthFailOp = VK_STENCIL_OP_ZERO;
		m_depthStencilState.front.compareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		m_depthStencilState.front.compareMask = 0;
		m_depthStencilState.front.writeMask = 0;
		m_depthStencilState.front.reference = 0;
		m_depthStencilState.back.failOp = VK_STENCIL_OP_ZERO;
		m_depthStencilState.back.passOp = VK_STENCIL_OP_KEEP;
		m_depthStencilState.back.depthFailOp = VK_STENCIL_OP_ZERO;
		m_depthStencilState.back.compareOp = VK_COMPARE_OP_LESS_OR_EQUAL;
		m_depthStencilState.back.compareMask = 0;
		m_depthStencilState.back.writeMask = 0;
		m_depthStencilState.back.reference = 0;*/
		m_depthStencilState.minDepthBounds = 0.0F;
		m_depthStencilState.maxDepthBounds = 1.0F;

		m_createInfo.pDepthStencilState = &m_depthStencilState;

		return true;
	}

	bool
	GraphicsPipeline::generateColorBlendState (VkPipelineColorBlendStateCreateFlags flags) noexcept
	{
		if ( m_colorBlendAttachments.empty() )
		{
			m_colorBlendAttachments.resize(1);

			m_colorBlendAttachments[0].blendEnable = VK_FALSE;
			m_colorBlendAttachments[0].srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
			m_colorBlendAttachments[0].dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
			m_colorBlendAttachments[0].colorBlendOp = VK_BLEND_OP_ADD;
			m_colorBlendAttachments[0].srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
			m_colorBlendAttachments[0].dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
			m_colorBlendAttachments[0].alphaBlendOp = VK_BLEND_OP_ADD;
			m_colorBlendAttachments[0].colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		}

		m_colorBlendState.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		m_colorBlendState.pNext = nullptr;
		m_colorBlendState.flags = flags;
		m_colorBlendState.logicOpEnable = VK_FALSE;
		m_colorBlendState.logicOp = VK_LOGIC_OP_COPY;
		m_colorBlendState.attachmentCount = m_colorBlendAttachments.size();
		m_colorBlendState.pAttachments = m_colorBlendAttachments.data();
		m_colorBlendState.blendConstants[0] = 0.0F;
		m_colorBlendState.blendConstants[1] = 0.0F;
		m_colorBlendState.blendConstants[2] = 0.0F;
		m_colorBlendState.blendConstants[3] = 0.0F;

		m_createInfo.pColorBlendState = &m_colorBlendState;

		return true;
	}

	bool
	GraphicsPipeline::generateDynamicState (const std::vector< VkDynamicState > & dynamicStates, VkPipelineDynamicStateCreateFlags flags) noexcept
	{
		m_dynamicStates = dynamicStates;

		m_dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		m_dynamicState.pNext = nullptr;
		m_dynamicState.flags = flags;
		m_dynamicState.dynamicStateCount = m_dynamicStates.size();
		m_dynamicState.pDynamicStates = m_dynamicStates.data();

		m_createInfo.pDynamicState = &m_dynamicState;

		return true;
	}

	size_t
	GraphicsPipeline::getHash () noexcept
	{
		/* FIXME: Weak and unstable hash method !! */
		return s_fakeHash++;
	}
}
