/*
 * Emeraude/Vulkan/RenderSubpass.hpp
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
#include <vector>

/* Third-party libraries */
#include "Third-Party-Inclusion/vulkan.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The RenderSubpass class.
	 */
	class RenderSubpass final
	{
		public:

			/**
			 * @brief Default constructor.
			 * @param pipelineBindPoint Set the type of pipeline being bound to this render subpass. Default VK_PIPELINE_BIND_POINT_GRAPHICS.
			 * @param flags Set flags of the subpass. Default none.
			 */
			explicit RenderSubpass (VkPipelineBindPoint pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS, VkSubpassDescriptionFlags flags = 0) noexcept;

			/**
			 * @brief Returns the description for the render pass.
			 * @return VkSubpassDescription
			 */
			[[nodiscard]]
			VkSubpassDescription generateSubpassDescription () const noexcept;

			/**
			 * @brief Adds an input attachment to the subpass.
			 * @param attachment The index of attachment.
			 * @param layout The image layout.
			 */
			void addInputAttachment (uint32_t attachment, VkImageLayout layout) noexcept;

			/**
			 * @brief Adds a color attachment to the subpass.
			 * @param attachment The index of attachment.
			 * @param layout The image layout.
			 */
			void addColorAttachment (uint32_t attachment, VkImageLayout layout) noexcept;

			/**
			 * @brief Adds a resolve attachment to the subpass.
			 * @warning If there is resolve attachment, it must be the same count as color attachments.
			 * @param attachment The index of attachment.
			 * @param layout The image layout.
			 */
			void addResolveAttachment (uint32_t attachment, VkImageLayout layout) noexcept;

			/**
			 * @brief Sets the only possible attachment depth/stencil reference.
			 * @param attachment The index of attachment.
			 * @param layout The image layout.
			 */
			void setDepthStencilAttachment (uint32_t attachment, VkImageLayout layout) noexcept;

			/**
			 * @brief Adds a preserved attachement between subpass.
			 * @param index An index to the attachment.
			 */
			void addPreserveAttachement (uint32_t index) noexcept;

		private:

			VkSubpassDescriptionFlags m_flags;
			VkPipelineBindPoint m_pipelineBindPoint;
			std::vector< VkAttachmentReference > m_inputAttachments{};
			std::vector< VkAttachmentReference > m_colorAttachments{};
			std::vector< VkAttachmentReference > m_resolveAttachments{}; // Use the color attachments count.
			VkAttachmentReference m_depthStencilAttachment{};
			std::vector< uint32_t > m_preserveAttachments{};
			bool m_depthStencilAttachmentSet = false;
	};
}
