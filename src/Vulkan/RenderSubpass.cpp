/*
 * Emeraude/Vulkan/RenderSubpass.cpp
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

#include "RenderSubpass.hpp"

namespace Emeraude::Vulkan
{
	RenderSubpass::RenderSubpass (VkPipelineBindPoint pipelineBindPoint, VkSubpassDescriptionFlags flags) noexcept
		: m_flags(flags), m_pipelineBindPoint(pipelineBindPoint)
	{

	}

	VkSubpassDescription
	RenderSubpass::generateSubpassDescription () const noexcept
	{
		VkSubpassDescription subpassDescription{};
		subpassDescription.flags = m_flags;
		subpassDescription.pipelineBindPoint = m_pipelineBindPoint;

		if ( m_inputAttachments.empty() )
		{
			subpassDescription.inputAttachmentCount = 0;
			subpassDescription.pInputAttachments = nullptr;
		}
		else
		{
			subpassDescription.inputAttachmentCount = static_cast< uint32_t >(m_inputAttachments.size());
			subpassDescription.pInputAttachments = m_inputAttachments.data();
		}

		if ( m_colorAttachments.empty() )
		{
			subpassDescription.colorAttachmentCount = 0;
			subpassDescription.pColorAttachments = nullptr;
		}
		else
		{
			subpassDescription.colorAttachmentCount = static_cast< uint32_t >(m_colorAttachments.size());
			subpassDescription.pColorAttachments = m_colorAttachments.data();
		}

		if ( m_resolveAttachments.empty() )
		{
			subpassDescription.pResolveAttachments = nullptr;
		}
		else
		{
			/* FIXME: Check if vulkan authorize resolve attachments without color. */
			if ( m_colorAttachments.empty() )
			{
				subpassDescription.colorAttachmentCount = static_cast< uint32_t >(m_resolveAttachments.size());
			}

			subpassDescription.pResolveAttachments = m_resolveAttachments.data();
		}

		if ( m_depthStencilAttachmentSet )
		{
			subpassDescription.pDepthStencilAttachment = &m_depthStencilAttachment;
		}

		if ( m_preserveAttachments.empty() )
		{
			subpassDescription.preserveAttachmentCount = 0;
			subpassDescription.pPreserveAttachments = nullptr;
		}
		else
		{
			subpassDescription.preserveAttachmentCount = static_cast< uint32_t >(m_preserveAttachments.size());
			subpassDescription.pPreserveAttachments = m_preserveAttachments.data();
		}

		return subpassDescription;
	}

	void
	RenderSubpass::addInputAttachment (uint32_t attachment, VkImageLayout layout) noexcept
	{
		m_inputAttachments.emplace_back(VkAttachmentReference{
			.attachment = attachment,
			.layout = layout
		});
	}

	void
	RenderSubpass::addColorAttachment (uint32_t attachment, VkImageLayout layout) noexcept
	{
		m_colorAttachments.emplace_back(VkAttachmentReference{
			.attachment = attachment,
			.layout = layout
		});
	}

	void
	RenderSubpass::addResolveAttachment (uint32_t attachment, VkImageLayout layout) noexcept
	{
		m_resolveAttachments.emplace_back(VkAttachmentReference{
			.attachment = attachment,
			.layout = layout
		});
	}

	void
	RenderSubpass::setDepthStencilAttachment (uint32_t attachment, VkImageLayout layout) noexcept
	{
		m_depthStencilAttachment.attachment = attachment;
		m_depthStencilAttachment.layout = layout;
		m_depthStencilAttachmentSet = true;
	}

	void
	RenderSubpass::addPreserveAttachement (uint32_t index) noexcept
	{
		m_preserveAttachments.emplace_back(index);
	}
}
