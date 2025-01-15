/*
 * src/Vulkan/RenderPass.cpp
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

#include "RenderPass.hpp"

/* STL inclusions. */
#include <cstdint>
#include <algorithm>

/* Local inclusions. */
#include "Device.hpp"
#include "RenderSubPass.hpp"
#include "Utility.hpp"
#include "Tracer.hpp"

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
	RenderPass::getSubPassDescriptions () const noexcept
	{
		std::vector< VkSubpassDescription > descriptions{};
		descriptions.reserve(m_renderSubPasses.size());

		std::ranges::transform(m_renderSubPasses, std::back_inserter(descriptions), [] (const auto & renderSubPass) {
			return renderSubPass.generateSubPassDescription();
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

		const auto subPassDescriptions = this->getSubPassDescriptions();

		if ( subPassDescriptions.empty() )
		{
			Tracer::warning(ClassId, "There is no sub-pass description for this render pass !");
		}
		else
		{
			m_createInfo.subpassCount = static_cast< uint32_t >(subPassDescriptions.size());
			m_createInfo.pSubpasses = subPassDescriptions.data();
		}

		if ( !m_subPassDependencies.empty() )
		{
			m_createInfo.dependencyCount = static_cast< uint32_t >(m_subPassDependencies.size());
			m_createInfo.pDependencies = m_subPassDependencies.data();
		}

		const auto result = vkCreateRenderPass(this->device()->handle(), &m_createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create a render pass : " << vkResultToCString(result) << " !";

			return false;
		}

		this->setCreated();

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

			m_handle = VK_NULL_HANDLE;
		}

		m_attachmentDescriptions.clear();
		m_renderSubPasses.clear();
		m_subPassDependencies.clear();

		this->setDestroyed();

		return true;
	}
}
