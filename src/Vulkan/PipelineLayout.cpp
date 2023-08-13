/*
 * Emeraude/Vulkan/PipelineLayout.cpp
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

#include "PipelineLayout.hpp"

/* Local inclusions */
#include "Device.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	PipelineLayout::PipelineLayout (const std::shared_ptr< Device > & device, const std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts, const std::vector< VkPushConstantRange > & pushConstantRanges, VkPipelineLayoutCreateFlags flags) noexcept
		: AbstractDeviceDependentObject(device), m_descriptorSetLayouts(descriptorSetLayouts), m_pushConstantRanges(pushConstantRanges)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = flags;
		m_createInfo.setLayoutCount = 0;
		m_createInfo.pSetLayouts = nullptr;
		m_createInfo.pushConstantRangeCount = 0;
		m_createInfo.pPushConstantRanges = nullptr;
	}

	PipelineLayout::PipelineLayout (const std::shared_ptr< Device > & device, const VkPipelineLayoutCreateInfo & createInfo, const std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts, const std::vector< VkPushConstantRange > & pushConstantRanges) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo), m_descriptorSetLayouts(descriptorSetLayouts), m_pushConstantRanges(pushConstantRanges)
	{

	}

	bool
	PipelineLayout::operator== (const PipelineLayout & operand) const noexcept
	{
		if ( this == &operand )
		{
			return true;
		}

		/* FIXME: Find a way to serialize the create info to reduce the equality check complexity. */

		if ( m_createInfo.flags != operand.m_createInfo.flags )
		{
			return false;
		}

		if ( m_createInfo.setLayoutCount != operand.m_createInfo.setLayoutCount )
		{
			return false;
		}

		if ( m_createInfo.pushConstantRangeCount != operand.m_createInfo.pushConstantRangeCount )
		{
			return false;
		}

		/* NOTE: Vector comparison */
		if ( m_descriptorSetLayouts != operand.m_descriptorSetLayouts )
		{
			return false;
		}

		/* NOTE: Vector comparison */
		for ( size_t i = 0; i < m_pushConstantRanges.size(); i++ )
		{
			if ( m_pushConstantRanges[i].stageFlags != operand.m_pushConstantRanges[i].stageFlags )
			{
				return false;
			}

			if ( m_pushConstantRanges[i].offset != operand.m_pushConstantRanges[i].offset )
			{
				return false;
			}

			if ( m_pushConstantRanges[i].size != operand.m_pushConstantRanges[i].size )
			{
				return false;
			}
		}

		return false;
	}

	bool
	PipelineLayout::operator!= (const PipelineLayout & operand) const noexcept
	{
		return !this->operator==(operand);
	}

	PipelineLayout::~PipelineLayout ()
	{
		this->destroyFromHardware();
	}

	bool
	PipelineLayout::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this pipeline layout !");

			return false;
		}

		/* Repack vulkan handles to use within the createInfo. */
		std::vector< VkDescriptorSetLayout > setLayouts{};
		setLayouts.reserve(m_descriptorSetLayouts.size());

		std::transform(m_descriptorSetLayouts.begin(), m_descriptorSetLayouts.end(), std::back_inserter(setLayouts), [] (const auto & item) -> VkDescriptorSetLayout {
			return item->handle();
		});

		m_createInfo.setLayoutCount = setLayouts.size();
		m_createInfo.pSetLayouts = setLayouts.data();
		m_createInfo.pushConstantRangeCount = m_pushConstantRanges.size();
		m_createInfo.pPushConstantRanges = m_pushConstantRanges.data();

		const auto result = vkCreatePipelineLayout(
			this->device()->handle(),
			&m_createInfo,
			VK_NULL_HANDLE,
			&m_handle
		);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create a pipeline layout : " << vkResultToCString(result) << " !";

			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The pipeline layout " << m_handle << " (" << this->identifier() << ") is successfully created !";

		return true;
	}

	bool
	PipelineLayout::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the pipeline layout " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroyPipelineLayout(
				this->device()->handle(),
				m_handle,
				VK_NULL_HANDLE
			);

			TraceSuccess{ClassId} << "The pipeline layout " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkPipelineLayout
	PipelineLayout::handle () const noexcept
	{
		return m_handle;
	}

	VkPipelineLayoutCreateInfo
	PipelineLayout::createInfo () const noexcept
	{
		return m_createInfo;
	}

	const std::vector< std::shared_ptr< DescriptorSetLayout > > &
	PipelineLayout::descriptorSetLayouts () const noexcept
	{
		return m_descriptorSetLayouts;
	}

	const std::vector< VkPushConstantRange > &
	PipelineLayout::pushConstantRanges () const noexcept
	{
		return m_pushConstantRanges;
	}

	size_t
	PipelineLayout::getHash (const std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts, const std::vector< VkPushConstantRange > & pushConstantRanges, VkPipelineLayoutCreateFlags flags) noexcept
	{
		/* FIXME: Weak and unstable hash method !! */
		size_t hash = 0;

		hash += descriptorSetLayouts.size();
		hash += pushConstantRanges.size();
		hash += flags;

		for ( const auto & descriptorSetLayout : descriptorSetLayouts )
		{
			hash += descriptorSetLayout->createInfo().bindingCount;
			hash += descriptorSetLayout->createInfo().flags;
		}

		for ( const auto & pushConstantRange : pushConstantRanges )
		{
			hash += pushConstantRange.offset;
			hash += pushConstantRange.size;
			hash += pushConstantRange.stageFlags;
		}

		return hash;
	}

	std::ostream &
	operator<< (std::ostream & out, const PipelineLayout & obj)
	{
		out << "Pipeline layout @" << &obj << " :" "\n";

		for ( const auto & descriptorSetLayout : obj.m_descriptorSetLayouts )
		{
			out << descriptorSetLayout;
		}

		return out;
	}

	std::string
	to_string (const PipelineLayout & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
