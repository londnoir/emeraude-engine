/*
 * Emeraude/Vulkan/RenderPass.cpp
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

#include "RenderPass.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	RenderPass::RenderPass (const std::shared_ptr< Device > & device, VkRenderPassCreateFlags createFlags) noexcept
		: AbstractDeviceDependentObject(device)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
		m_createInfo.attachmentCount = 0;
		m_createInfo.pAttachments = nullptr;
		m_createInfo.subpassCount = 0;
		m_createInfo.pSubpasses = nullptr;
		m_createInfo.dependencyCount = 0;
		m_createInfo.pDependencies = nullptr;
	}

	RenderPass::RenderPass (const std::shared_ptr< Device > & device, const VkRenderPassCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo)
	{

	}

	RenderPass::~RenderPass ()
	{
		this->destroyFromHardware();
	}

	std::vector< VkSubpassDescription >
	RenderPass::getSubpassDescriptions () const noexcept
	{
		std::vector< VkSubpassDescription > descriptions{};
		descriptions.reserve(m_renderSubPasses.size());

		//for ( const auto & renderSubpass : m_renderSubPasses )
		//	descriptions.emplace_back(renderSubpass.generateSubpassDescription());

		std::transform(m_renderSubPasses.cbegin(), m_renderSubPasses.cend(), std::back_inserter(descriptions), [] (const auto & renderSubpass) {
			return renderSubpass.generateSubpassDescription();
		});

		return descriptions;
	}

	bool
	RenderPass::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this render pass !");

			return false;
		}

		if ( m_attachmentDescriptions.empty() )
		{
			Tracer::warning(ClassId, "There is no attachment for this render pass !");
		}
		else
		{
			m_createInfo.attachmentCount = static_cast< uint32_t >(m_attachmentDescriptions.size());
			m_createInfo.pAttachments = m_attachmentDescriptions.data();
		}

		auto subpassDescriptions = this->getSubpassDescriptions();

		if ( subpassDescriptions.empty() )
		{
			Tracer::warning(ClassId, "There is no subpass description for this render pass !");
		}
		else
		{
			m_createInfo.subpassCount = static_cast< uint32_t >(subpassDescriptions.size());
			m_createInfo.pSubpasses = subpassDescriptions.data();
		}

		if ( !m_subpassDependencies.empty() )
		{
			m_createInfo.dependencyCount = static_cast< uint32_t >(m_subpassDependencies.size());
			m_createInfo.pDependencies = m_subpassDependencies.data();
		}

		const auto result = vkCreateRenderPass(this->device()->handle(), &m_createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			Tracer::error(ClassId, Blob() << "Unable to create a render pass : " << vkResultToCString(result) << " !");

			return false;
		}

		this->setCreated();

		Tracer::success(ClassId, Blob() << "The render pass " << m_handle << " (" << this->identifier() << ") is successfully created !");

		return true;
	}

	bool
	RenderPass::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the render pass " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroyRenderPass(this->device()->handle(), m_handle, nullptr);

			TraceSuccess{ClassId} << "The render pass " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		m_attachmentDescriptions.clear();
		m_renderSubPasses.clear();
		m_subpassDependencies.clear();

		this->setDestroyed();

		return true;
	}

	void
	RenderPass::addAttachmentDescription (const VkAttachmentDescription & attachmentDescription) noexcept
	{
		m_attachmentDescriptions.emplace_back(attachmentDescription);
	}

	void
	RenderPass::addSubpass (const RenderSubpass & renderSubpass) noexcept
	{
		m_renderSubPasses.emplace_back(renderSubpass);
	}

	void
	RenderPass::addSubpassDependency (const VkSubpassDependency & subpassDependency) noexcept
	{
		m_subpassDependencies.emplace_back(subpassDependency);
	}

	VkRenderPass
	RenderPass::handle () const noexcept
	{
		return m_handle;
	}

	VkRenderPassCreateInfo
	RenderPass::createInfo() const noexcept
	{
		return m_createInfo;
	}
}
