/*
 * Emeraude/Physics/Manager.cpp
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

#include "Manager.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Arguments.hpp"
#include "Settings.hpp"
#include "Vulkan/Instance.hpp"
#include "Vulkan/DescriptorPool.hpp"
#include "Vulkan/DescriptorSetLayout.hpp"
#include "Vulkan/CommandPool.hpp"
#include "Vulkan/PipelineLayout.hpp"
#include "Vulkan/ComputePipeline.hpp"

namespace Emeraude::Physics
{
	using namespace Vulkan;

	const size_t Manager::ClassUID{Observable::getClassUID()};

	Manager::Manager (const Arguments & arguments, Settings & coreSettings, Instance & instance) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_coreSettings(coreSettings), m_vulkanInstance(instance)
	{

	}

	bool
	Manager::onInitialize () noexcept
	{
		m_flags[AccelerationAvailable] =
			!m_arguments.get("--disable-physics-acceleration").isPresent() &&
			m_coreSettings.getAs< bool >(AccelerationEnabledKey, DefaultAccelerationEnabled);

		if ( !m_flags[AccelerationAvailable] )
		{
			Tracer::warning(ClassId, "Physics acceleration disabled at startup.");

			return true;
		}

		if ( !m_vulkanInstance.usable() )
		{
			Tracer::fatal(ClassId, "The Vulkan instance is not usable !");

			return false;
		}

		/* Compute device selection. */
		{
			m_device = m_vulkanInstance.getComputeDevice();

			if ( m_device == nullptr )
			{
				Tracer::fatal(ClassId, "Unable to find a suitable compute device !");

				return false;
			}

			/* Create a descriptor pool
			 * FIXME: maybe not the right place ! */
			const auto sizes = std::vector< VkDescriptorPoolSize >{
				{VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 16}
			};

			m_descriptorPool = std::make_shared< DescriptorPool >(m_device, sizes, 64, VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT);
			m_descriptorPool->setIdentifier("Physics-Main-DescriptorPool");

			if ( !m_descriptorPool->createOnHardware() )
			{
				Tracer::fatal(ClassId, "Unable to create the descriptor pool !");

				return false;
			}

			m_commandPool = std::make_shared< CommandPool >(m_device, m_device->getComputeFamilyIndex(), VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
			m_commandPool->setIdentifier("Physics-Main-CommandPool");

			if ( !m_commandPool->createOnHardware() )
			{
				Tracer::fatal(ClassId, "Unable to create the command pool !");

				return false;
			}
		}

		m_flags[Usable] = true;

		return true;
	}

	bool
	Manager::onTerminate () noexcept
	{
		m_flags[Usable] = false;

		m_pipelines.clear();
		m_pipelineLayouts.clear();

		m_descriptorSetLayouts.clear();
		m_descriptorPool.reset();

		if ( m_device != nullptr )
		{
			m_device->waitIdle();

			this->clearCommandBuffers();
			m_commandPool.reset();

			/* Release the pointer on the device. */
			m_device.reset();
		}

		return true;
	}

	void
	Manager::clearCommandBuffers () noexcept
	{
		if ( m_commandBuffers.empty() )
		{
			return;
		}

		m_device->waitIdle();

		// FIXME !!! Check with the bit flag a command pool creation.
		//m_commandPool->freeCommandBuffers(static_cast< uint32_t >(m_commandBuffers.size()), m_commandBuffers.data());

		m_commandBuffers.clear();
	}

	bool
	Manager::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Manager::usable () const noexcept
	{
		if ( !m_vulkanInstance.usable() )
		{
			return false;
		}

		return m_flags[Usable];
	}

	const std::shared_ptr< Device > &
	Manager::device () const noexcept
	{
		return m_device;
	}

	const std::shared_ptr< DescriptorPool > &
	Manager::descriptorPool () const noexcept
	{
		return m_descriptorPool;
	}

	std::shared_ptr< PipelineLayout >
	Manager::getPipelineLayout (const std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts) noexcept
	{
		const auto hash = PipelineLayout::getHash(descriptorSetLayouts, {}, 0);

		const auto pipelineLayoutIt = m_pipelineLayouts.find(hash);

		if ( pipelineLayoutIt != m_pipelineLayouts.cend() )
		{
			return pipelineLayoutIt->second;
		}

		auto pipelineLayout = std::make_shared< PipelineLayout >(m_device, descriptorSetLayouts);
		pipelineLayout->setIdentifier("PhysicsManager-Main-PipelineLayout");

		if ( !pipelineLayout->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create the pipeline layout !");

			return {};
		}

		auto result = m_pipelineLayouts.emplace(hash, pipelineLayout);

		return result.first->second;
	}

	std::shared_ptr< ComputePipeline >
	Manager::getPipeline (const std::shared_ptr< PipelineLayout > & pipelineLayout) noexcept
	{
		const auto hash = ComputePipeline::getHash();

		const auto pipelineIt = m_pipelines.find(hash);

		if ( pipelineIt != m_pipelines.cend() )
		{
			return pipelineIt->second;
		}

		auto pipeline = std::make_shared< ComputePipeline >(pipelineLayout);
		pipeline->setIdentifier("PhysicsManager-Main-ComputePipeline");

		if ( !pipeline->createOnHardware() )
		{
			Tracer::error(ClassId, "Unable to create the compute pipeline !");

			return {};
		}

		auto result = m_pipelines.emplace(hash, pipeline);

		return result.first->second;
	}

	bool
	Manager::isPhysicsAccelerationAvailable () noexcept
	{
		return m_flags[AccelerationAvailable];
	}
}
