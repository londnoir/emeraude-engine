/*
 * Emeraude/Vulkan/GraphicsPipeline.hpp
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

#pragma once

/* C/C++ standard libraries. */
#include <memory>
#include <vector>

/* Local inclusions for inheritances. */
#include "AbstractDeviceDependentObject.hpp"

/* Local inclusions for usages. */
#include "Graphics/Geometry/Interface.hpp"
#include "Graphics/Material/Interface.hpp"
#include "Graphics/RenderTarget/Abstract.hpp"
#include "Graphics/RenderableInstance/Abstract.hpp"
#include "Graphics/RenderableInstance/VertexBufferFormat.hpp"
#include "PipelineLayout.hpp"
#include "GraphicsShaderContainer.hpp"

/*

VertexInput
PreRasterisation (vs, tess, geo)
FragmentShader (fs)
FragmentOutput

VkGraphicsPipelineCreateInfo createInfo{};
createInfo.sType;
createInfo.pNext;
createInfo.flags;
createInfo.stageCount;
createInfo.pStages; // PreRasterisation + FragmentShader
createInfo.pVertexInputState; // VertexInput
createInfo.pInputAssemblyState; // VertexInput
createInfo.pTessellationState; // PreRasterisation
createInfo.pViewportState; // PreRasterisation
createInfo.pRasterizationState; //PreRasterisation
createInfo.pMultisampleState; // FragmentShader + FragmentOutput
createInfo.pDepthStencilState; // FragmentShader
createInfo.pColorBlendState; // fragment output stage
createInfo.pDynamicState; // VertexInput + PreRasterisation + FragmentShader + FragmentOutput
createInfo.layout; // PreRasterisation + FragmentShader
createInfo.renderPass; // PreRasterisation + FragmentShader + FragmentOutput
createInfo.subpass;
createInfo.basePipelineHandle;
createInfo.basePipelineIndex;

*/

namespace Emeraude::Vulkan
{
	/**
	 * @brief The graphics pipeline class.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This Vulkan Object needs a device.
	 */
	class GraphicsPipeline final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanGraphicsPipeline"};

			/**
			 * @brief Constructs a graphics pipeline.
			 * @param pipelineLayout A reference to pipeline layout smart pointer.
			 * @param vertexBufferFormat A reference to a vertex buffer format smart pointer to query the enabled geometry (VAO).
			 * @param shaders A reference to a list of shaders that render the instance.
			 * @param createFlags The create info flags. Default none.
			 */
			GraphicsPipeline (const std::shared_ptr< PipelineLayout > & pipelineLayout, const std::shared_ptr< Graphics::RenderableInstance::VertexBufferFormat > & vertexBufferFormat, const GraphicsShaderContainer & shaders, VkPipelineCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a graphics pipeline with a create info.
			 * @param pipelineLayout A reference to pipeline layout smart pointer.
			 * @param vertexBufferFormat A reference to a vertex buffer format smart pointer to query the enabled geometry (VAO).
			 * @param shaders A reference to a list of shaders that render the instance.
			 * @param createInfo A reference to a create info.
			 */
			GraphicsPipeline (const std::shared_ptr< PipelineLayout > & pipelineLayout, const std::shared_ptr< Graphics::RenderableInstance::VertexBufferFormat > & vertexBufferFormat, const GraphicsShaderContainer & shaders, const VkGraphicsPipelineCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			GraphicsPipeline (const GraphicsPipeline & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			GraphicsPipeline (GraphicsPipeline && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			GraphicsPipeline & operator= (const GraphicsPipeline & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			GraphicsPipeline & operator= (GraphicsPipeline && copy) noexcept = default;

			/**
			 * @brief Destructs the graphics pipeline.
			 */
			~GraphicsPipeline () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::recreate() */
			bool recreate () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Creates a graphics pipeline for a specific renderable instance in a render target with computed shaders and vertex buffer format.
			 * @param renderTarget A reference to a render target to query the viewport.
			 * @param renderableInstance A reference to the renderable instance to query options.
			 * @return bool
			 */
			[[nodiscard]]
			bool create (const Graphics::RenderTarget::Abstract & renderTarget, const Graphics::RenderableInstance::Abstract & renderableInstance) noexcept;

			/**
			 * @brief Recreates the graphics pipeline.
			 * @param renderTarget A reference to a render target to query the viewport.
			 * @param renderableInstance A reference to the renderable instance to query options.
			 * @return bool
			 */
			[[nodiscard]]
			bool recreate (const Graphics::RenderTarget::Abstract & renderTarget, const Graphics::RenderableInstance::Abstract & renderableInstance) noexcept;

			/**
			 * @brief Returns the pipeline vulkan handle.
			 * @return VkPipeline
			 */
			[[nodiscard]]
			VkPipeline handle () const noexcept;

			/**
			 * @brief Returns the associated pipeline layout smart pointer.
			 * @return std::shared_ptr< PipelineLayout >
			 */
			[[nodiscard]]
			std::shared_ptr< PipelineLayout > pipelineLayout () const noexcept;

			/**
			 * @brief Returns the list of color blend attachments.
			 * @return const std::vector< VkPipelineColorBlendAttachmentState > &
			 */
			[[nodiscard]]
			const std::vector< VkPipelineColorBlendAttachmentState > & colorBlendAttachments () const noexcept;

			/**
			 * @brief Returns a hash for this graphics pipeline according to constructor params.
			 * @return size_t
			 */
			[[nodiscard]]
			static size_t getHash () noexcept;

		private:

			/* FIXME: Remove this !!!! */
			static size_t s_fakeHash;

			/**
			 * @brief Checks the prerequisites to create a graphics pipeline.
			 * @param renderTarget A reference to the render target.
			 * @param renderableInstance A reference to a renderable instance.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkPrerequisites (const Graphics::RenderTarget::Abstract & renderTarget, const Graphics::RenderableInstance::Abstract & renderableInstance) noexcept;

			/**
			 * @brief Generates the shader stages into the graphics pipeline create info from a renderable.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateShaderStages () noexcept;

			/**
			 * @brief Generates vertex input state into the graphics pipeline create info.
			 * @param flags Flags value for this stage. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateVertexInputState (VkPipelineVertexInputStateCreateFlags flags = 0) noexcept;

			/**
			 * @brief Generates input assembly state into the graphics pipeline create info.
			 * @param flags Flags value for this stage. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateInputAssemblyState (VkPipelineInputAssemblyStateCreateFlags flags = 0) noexcept;

			/**
			 * @brief Generates tesselation state into the graphics pipeline create info.
			 * @param flags Flags value for this stage. Default 0.
			 * @param patchControlPoints
			 * @return bool
			 */
			[[nodiscard]]
			bool generateTessellationState (uint32_t patchControlPoints, VkPipelineTessellationStateCreateFlags flags = 0) noexcept;

			/**
			 * @brief Generates viewport state into the graphics pipeline create info.
			 * @param renderTarget A reference to the render target.
			 * @param flags Flags value for this stage. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateViewportState (const Graphics::RenderTarget::Abstract & renderTarget, VkPipelineViewportStateCreateFlags flags = 0) noexcept;

			/**
			 * @brief Generates rasterization state into the graphics pipeline create info.
			 * @param flags Flags value for this stage. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateRasterizationState (VkPipelineRasterizationStateCreateFlags flags = 0) noexcept;

			/**
			 * @brief Generates multisample state into the graphics pipeline create info.
			 * @param flags Flags value for this stage. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateMultisampleState (VkPipelineMultisampleStateCreateFlags flags = 0) noexcept;

			/**
			 * @brief Generates depth stencil state into the graphics pipeline create info.
			 * @param renderableInstance A reference to the renderable instance.
			 * @param flags Flags value for this stage. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateDepthStencilState (const Graphics::RenderableInstance::Abstract & renderableInstance, VkPipelineDepthStencilStateCreateFlags flags = 0) noexcept;

			/**
			 * @brief Generates color blend state into the graphics pipeline create info.
			 * @param flags Flags value for this stage. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateColorBlendState (VkPipelineColorBlendStateCreateFlags flags = 0) noexcept;

			/**
			 * @brief Generates dynamic state into the graphics pipeline create info.
			 * @param dynamicStates A vector of dynamic states desired.
			 * @param flags Flags value for this stage. Default 0.
			 * @return bool
			 */
			[[nodiscard]]
			bool generateDynamicState (const std::vector< VkDynamicState > & dynamicStates, VkPipelineDynamicStateCreateFlags flags = 0) noexcept;

			VkPipeline m_handle{VK_NULL_HANDLE};
			VkGraphicsPipelineCreateInfo m_createInfo{};
			std::shared_ptr< PipelineLayout > m_pipelineLayout{};
			std::shared_ptr< Graphics::RenderableInstance::VertexBufferFormat > m_vertexBufferFormat{};
			std::vector< std::shared_ptr< Saphir::AbstractShader > > m_shaders{};
			std::vector< VkPipelineShaderStageCreateInfo > m_shaderStages{};
			VkPipelineVertexInputStateCreateInfo m_vertexInputState{};
			VkPipelineInputAssemblyStateCreateInfo m_inputAssemblyState{};
			VkPipelineTessellationStateCreateInfo m_tessellationState{};
			std::vector< VkViewport > m_viewports{};
			std::vector< VkRect2D > m_scissors{};
			VkPipelineViewportStateCreateInfo m_viewportState{};
			VkPipelineRasterizationStateCreateInfo m_rasterizationState{};
			VkPipelineMultisampleStateCreateInfo m_multisampleState{};
			VkPipelineDepthStencilStateCreateInfo m_depthStencilState{};
			std::vector< VkPipelineColorBlendAttachmentState > m_colorBlendAttachments{};
			VkPipelineColorBlendStateCreateInfo m_colorBlendState{};
			std::vector< VkDynamicState > m_dynamicStates{};
			VkPipelineDynamicStateCreateInfo m_dynamicState{};
	};
}
