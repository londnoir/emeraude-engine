/*
 * Emeraude/Vulkan/ComputePipeline.cpp
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

#include "ComputePipeline.hpp"

/* Local inclusions */
#include "Device.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	size_t ComputePipeline::s_fakeHash = 0;

	ComputePipeline::ComputePipeline (const std::shared_ptr< PipelineLayout > & pipelineLayout, VkPipelineCreateFlags createFlags) noexcept
		: AbstractDeviceDependentObject(pipelineLayout->device()), m_pipelineLayout(pipelineLayout)
	{
		/* FIXME: The compute pipeline is not developed yet. */
		m_createInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
		m_createInfo.stage = VkPipelineShaderStageCreateInfo{};
		m_createInfo.layout = m_pipelineLayout->handle();
		m_createInfo.basePipelineHandle = nullptr; // VkPipeline
		m_createInfo.basePipelineIndex = 0;
	}

	ComputePipeline::ComputePipeline (const std::shared_ptr< PipelineLayout > & pipelineLayout, const VkComputePipelineCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(pipelineLayout->device()), m_createInfo(createInfo), m_pipelineLayout(pipelineLayout)
	{

	}

	ComputePipeline::~ComputePipeline ()
	{
		this->destroyFromHardware();
	}

	bool
	ComputePipeline::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this compute pipeline !");

			return false;
		}

		if ( m_pipelineLayout == nullptr )
		{
			Tracer::error(ClassId, "No pipeline layout to create this compute pipeline !");

			return false;
		}

		const auto result = vkCreateComputePipelines(this->device()->handle(), VK_NULL_HANDLE, 1, &m_createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			Tracer::error(ClassId, Blob() << "Unable to create a compute pipeline : " << vkResultToCString(result) << " !");

			return false;
		}

		this->setCreated();

		Tracer::success(ClassId, Blob() << "The compute pipeline " << m_handle << " (" << this->identifier() << ") is successfully created !");

		return true;
	}

	bool
	ComputePipeline::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to destroy this compute pipeline !");

			return false;
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroyPipeline(this->device()->handle(), m_handle, nullptr);

			Tracer::success(ClassId, Blob() << "The compute pipeline " << m_handle << " is gracefully destroyed !");

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkPipeline
	ComputePipeline::handle () const noexcept
	{
		return m_handle;
	}

	VkComputePipelineCreateInfo
	ComputePipeline::createInfo () const noexcept
	{
		return m_createInfo;
	}

	std::shared_ptr< PipelineLayout >
	ComputePipeline::pipelineLayout () const noexcept
	{
		return m_pipelineLayout;
	}

	size_t
	ComputePipeline::getHash () noexcept
	{
		/* FIXME: Weak and unstable hash method !! */
		return s_fakeHash++;
	}
}
