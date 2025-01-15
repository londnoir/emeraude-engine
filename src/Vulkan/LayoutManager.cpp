/*
 * src/Vulkan/LayoutManager.cpp
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

#include "LayoutManager.hpp"

/* STL inclusions. */
#include <exception>
#include <iostream>

/* Local inclusions. */
#include "Device.hpp"
#include "PipelineLayout.hpp"
#include "DescriptorSetLayout.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	const size_t LayoutManager::ClassUID{getClassUID(ClassId)};

	std::array< LayoutManager *, 2 > LayoutManager::s_instances{nullptr, nullptr};

	LayoutManager::LayoutManager (GPUWorkType type) noexcept
		: ServiceInterface(ClassId)
	{
		auto & instance = s_instances.at(static_cast< size_t >(type));

		if ( instance != nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", constructor called twice !" "\n";

			std::terminate();
		}

		instance = this;
	}

	LayoutManager::~LayoutManager ()
	{
		for ( auto & pointer : s_instances )
		{
			if ( pointer == this )
			{
				pointer = nullptr;

				break;
			}
		}
	}

	bool
	LayoutManager::usable () const noexcept
	{
		if ( !m_flags[ServiceInitialized] )
		{
			return false;
		}

		if ( m_device == nullptr )
		{
			return false;
		}

		return m_device->isCreated();
	}

	bool
	LayoutManager::onInitialize () noexcept
	{
		if ( m_device == nullptr || !m_device->isCreated() )
		{
			Tracer::error(ClassId, "No device set !");

			return false;
		}

		m_flags[ServiceInitialized] = true;

		return true;
	}

	bool
	LayoutManager::onTerminate () noexcept
	{
		m_flags[ServiceInitialized] = false;

		m_descriptorSetLayouts.clear();
		m_pipelineLayouts.clear();

		m_device.reset();

		return true;
	}

	std::shared_ptr< DescriptorSetLayout >
	LayoutManager::getDescriptorSetLayout (const std::string & UUID) const noexcept
	{
		const auto descriptorSetLayoutIt = m_descriptorSetLayouts.find(UUID);

		if ( descriptorSetLayoutIt == m_descriptorSetLayouts.cend() )
		{
			return nullptr;
		}

		return descriptorSetLayoutIt->second;
	}

	std::shared_ptr< DescriptorSetLayout >
	LayoutManager::prepareNewDescriptorSetLayout (const std::string & UUID, VkDescriptorSetLayoutCreateFlags createFlags) const noexcept
	{
		return std::make_shared< DescriptorSetLayout >(m_device, UUID, createFlags);
	}

	bool
	LayoutManager::createDescriptorSetLayout (const std::shared_ptr< DescriptorSetLayout > & descriptorSetLayout) noexcept
	{
		/* NOTE : Descriptor set layout identifier must be unique. */
		if ( m_descriptorSetLayouts.contains(descriptorSetLayout->UUID()) )
		{
			TraceError{ClassId} << "The manager already holds a descriptor set layout named '" << descriptorSetLayout->UUID() << "' !";

			return false;
		}

		/* NOTE : Do not save incomplete descriptor set layout. */
		if ( !descriptorSetLayout->createOnHardware() )
		{
			TraceError{ClassId} << "The descriptor set layout '" << descriptorSetLayout->UUID() << "' is not created !";

			return false;
		}

		return m_descriptorSetLayouts.emplace(descriptorSetLayout->UUID(), descriptorSetLayout).second;
	}

	std::shared_ptr< PipelineLayout >
	LayoutManager::getPipelineLayout (const std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts, const std::vector< VkPushConstantRange > & pushConstantRanges, VkPipelineLayoutCreateFlags createFlags) noexcept
	{
		/* FIXME: Find a better way to create an UUID. */
		std::stringstream pipelineLayoutUUIDStream;

		for ( const auto & descriptorSetLayout : descriptorSetLayouts )
		{
			pipelineLayoutUUIDStream << descriptorSetLayout->UUID();
		}

		for ( const auto & pushConstantRange : pushConstantRanges )
		{
			pipelineLayoutUUIDStream << "PC" << pushConstantRange.stageFlags << ':' << pushConstantRange.offset << ':' << pushConstantRange.size;
		}

		const auto pipelineLayoutUUID = pipelineLayoutUUIDStream.str();

		const auto pipelineLayoutIt = m_pipelineLayouts.find(pipelineLayoutUUID);

		if ( pipelineLayoutIt != m_pipelineLayouts.cend() )
		{
			TraceDebug{ClassId} << "Reusing pipeline layout named '" << pipelineLayoutUUID << "' ...";

			return pipelineLayoutIt->second;
		}

		auto pipelineLayout = std::make_shared< PipelineLayout >(m_device, pipelineLayoutUUID, descriptorSetLayouts, pushConstantRanges, createFlags);
		pipelineLayout->setIdentifier(ClassId, pipelineLayout->UUID(), "PipelineLayout");

		if ( !pipelineLayout->createOnHardware() )
		{
			TraceError{ClassId} << "The pipeline layout '" << pipelineLayout->UUID() << "' is not created !";

			return nullptr;
		}

		return m_pipelineLayouts.emplace(pipelineLayout->UUID(), pipelineLayout).first->second;
	}
}
