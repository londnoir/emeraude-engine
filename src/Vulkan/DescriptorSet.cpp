/*
 * Emeraude/Vulkan/DescriptorSet.cpp
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

#include "DescriptorSet.hpp"

/* Local inclusions */
#include "Device.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	DescriptorSet::DescriptorSet (const std::shared_ptr< DescriptorPool > & descriptorPool, const std::shared_ptr< DescriptorSetLayout > & descriptorSetLayout) noexcept
		: m_descriptorPool(descriptorPool), m_descriptorSetLayout(descriptorSetLayout)
	{

	}

	DescriptorSet::~DescriptorSet ()
	{
		this->destroy();
	}

	bool
	DescriptorSet::create () noexcept
	{
		if ( m_descriptorPool == nullptr || !m_descriptorPool->isCreated() )
		{
			Tracer::error(ClassId, "Descriptor pool is null or not created to allocate this descriptor set !");

			return false;
		}

		m_handle = m_descriptorPool->allocateDescriptorSet(*m_descriptorSetLayout);

		if ( m_handle == VK_NULL_HANDLE )
		{
			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The descriptor set " << m_handle << " successfully allocated !";

		return true;
	}

	bool
	DescriptorSet::destroy () noexcept
	{
		if ( m_descriptorPool == nullptr || !m_descriptorPool->isCreated() )
		{
			Tracer::error(ClassId, "No or uninitialized descriptor pool to destroy this descriptor set !");

			return false;
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			m_descriptorPool->freeDescriptorSet(m_handle);

			TraceSuccess{ClassId} << "The descriptor set " << m_handle << " gracefully freed !";

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkDescriptorSet
	DescriptorSet::handle () const noexcept
	{
		return m_handle;
	}

	const std::shared_ptr< DescriptorPool > &
	DescriptorSet::descriptorPool () const noexcept
	{
		return m_descriptorPool;
	}

	const std::shared_ptr< DescriptorSetLayout > &
	DescriptorSet::descriptorSetLayout () const noexcept
	{
		return m_descriptorSetLayout;
	}

	bool
	DescriptorSet::writeUniformBufferObject (UniformBufferObject & UBO, uint32_t bindingIndex, uint32_t offset) const noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The descriptor is not yet create ! Unable to write descriptor.");

			return false;
		}

		if ( !UBO.isCreated() )
		{
			Tracer::error(ClassId, "The uniform buffer object is not created !");

			return false;
		}

		const auto descriptorInfo = UBO.getDescriptorInfo();

		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSet.pNext = nullptr;
		writeDescriptorSet.dstSet = m_handle;
		writeDescriptorSet.dstBinding = bindingIndex;
		writeDescriptorSet.dstArrayElement = offset;
		writeDescriptorSet.descriptorCount = 1;
		writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		writeDescriptorSet.pImageInfo = nullptr;
		writeDescriptorSet.pBufferInfo = &descriptorInfo;
		writeDescriptorSet.pTexelBufferView = nullptr;

		vkUpdateDescriptorSets(
			m_descriptorPool->device()->handle(),
			1, &writeDescriptorSet,
			0, VK_NULL_HANDLE
		);

		return true;
	}

	bool
	DescriptorSet::writeUniformBufferObjects (const std::vector< std::shared_ptr< UniformBufferObject > > & UBOs, uint32_t bindingIndex) const noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The descriptor is not yet create ! Unable to write descriptor.");

			return false;
		}

		if ( UBOs.empty() )
		{
			Tracer::error(ClassId, "The uniform buffer object list is empty !");

			return false;
		}

		std::vector< VkDescriptorBufferInfo > descriptorInfos{};
		descriptorInfos.reserve(UBOs.size());

		for ( const auto & UBO : UBOs )
		{
			if ( !UBO->isCreated() )
			{
				Tracer::error(ClassId, "The uniform buffer object is not created !");

				return false;
			}

			descriptorInfos.emplace_back(UBO->getDescriptorInfo());
		}

		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSet.pNext = nullptr;
		writeDescriptorSet.dstSet = m_handle;
		writeDescriptorSet.dstBinding = bindingIndex;
		writeDescriptorSet.dstArrayElement = 0;
		writeDescriptorSet.descriptorCount = static_cast< uint32_t >(descriptorInfos.size());
		writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		writeDescriptorSet.pImageInfo = nullptr;
		writeDescriptorSet.pBufferInfo = descriptorInfos.data();
		writeDescriptorSet.pTexelBufferView = nullptr;

		vkUpdateDescriptorSets(
			m_descriptorPool->device()->handle(),
			1, &writeDescriptorSet,
			0, VK_NULL_HANDLE
		);

		return true;
	}

	bool
	DescriptorSet::writeSampler (const std::shared_ptr< Graphics::TextureResource::Abstract > & texture, uint32_t bindingIndex) const noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The descriptor is not yet create ! Unable to write descriptor.");

			return false;
		}

		if ( !texture->isCreated() )
		{
			Tracer::error(ClassId, "The texture is not created !");

			return false;
		}

		const auto descriptorInfo = texture->getDescriptorInfo();

		if ( descriptorInfo.sampler == VK_NULL_HANDLE || descriptorInfo.imageView == VK_NULL_HANDLE || descriptorInfo.imageLayout == VK_IMAGE_LAYOUT_UNDEFINED )
		{
			return false;
		}

		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSet.pNext = nullptr;
		writeDescriptorSet.dstSet = m_handle;
		writeDescriptorSet.dstBinding = bindingIndex;
		writeDescriptorSet.dstArrayElement = 0;
		writeDescriptorSet.descriptorCount = 1;
		writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
		writeDescriptorSet.pImageInfo = &descriptorInfo;
		writeDescriptorSet.pBufferInfo = nullptr;
		writeDescriptorSet.pTexelBufferView = nullptr;

		vkUpdateDescriptorSets(
			m_descriptorPool->device()->handle(),
			1, &writeDescriptorSet,
			0, VK_NULL_HANDLE
		);

		return true;
	}

	bool
	DescriptorSet::writeSamplers (const std::vector< std::shared_ptr< Graphics::TextureResource::Abstract > > & textures, uint32_t bindingIndex) const noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The descriptor is not yet create ! Unable to write descriptor.");

			return false;
		}

		if ( textures.empty() )
		{
			Tracer::error(ClassId, "The texture list is empty !");

			return false;
		}

		std::vector< VkDescriptorImageInfo > descriptorInfos{};
		descriptorInfos.reserve(textures.size());

		for ( const auto & texture : textures )
		{
			if ( !texture->isCreated() )
			{
				Tracer::error(ClassId, "The texture is not created !");

				return false;
			}

			descriptorInfos.emplace_back(texture->getDescriptorInfo());
		}

		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSet.pNext = nullptr;
		writeDescriptorSet.dstSet = m_handle;
		writeDescriptorSet.dstBinding = bindingIndex;
		writeDescriptorSet.dstArrayElement = 0;
		writeDescriptorSet.descriptorCount = static_cast< uint32_t >(descriptorInfos.size());
		writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
		writeDescriptorSet.pImageInfo = descriptorInfos.data();
		writeDescriptorSet.pBufferInfo = nullptr;
		writeDescriptorSet.pTexelBufferView = nullptr;

		vkUpdateDescriptorSets(
			m_descriptorPool->device()->handle(),
			1, &writeDescriptorSet,
			0, VK_NULL_HANDLE
		);

		return true;
	}

	bool
	DescriptorSet::writeCombinedImageSampler (const std::shared_ptr< Graphics::TextureResource::Abstract > & texture, uint32_t bindingIndex) const noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The descriptor is not yet create ! Unable to write descriptor.");

			return false;
		}

		if ( !texture->isCreated() )
		{
			Tracer::error(ClassId, "The texture is not created !");

			return false;
		}

		const auto descriptorInfo = texture->getDescriptorInfo();

		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSet.pNext = nullptr;
		writeDescriptorSet.dstSet = m_handle;
		writeDescriptorSet.dstBinding = bindingIndex;
		writeDescriptorSet.dstArrayElement = 0;
		writeDescriptorSet.descriptorCount = 1;
		writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		writeDescriptorSet.pImageInfo = &descriptorInfo;
		writeDescriptorSet.pBufferInfo = nullptr;
		writeDescriptorSet.pTexelBufferView = nullptr;

		vkUpdateDescriptorSets(
			m_descriptorPool->device()->handle(),
			1, &writeDescriptorSet,
			0, VK_NULL_HANDLE
		);

		return true;
	}

	bool
	DescriptorSet::writeCombinedImageSamplers (const std::vector< std::shared_ptr< Graphics::TextureResource::Abstract > > & textures, uint32_t bindingIndex) const noexcept
	{
		if ( !this->isCreated() )
		{
			Tracer::error(ClassId, "The descriptor is not yet created ! Unable to write descriptor.");

			return false;
		}

		if ( textures.empty() )
		{
			Tracer::error(ClassId, "The texture list is empty !");

			return false;
		}

		std::vector< VkDescriptorImageInfo > descriptorInfos{};
		descriptorInfos.reserve(textures.size());

		for ( const auto & texture : textures )
		{
			if ( !texture->isCreated() )
			{
				Tracer::error(ClassId, "The texture is not created !");

				return false;
			}

			descriptorInfos.emplace_back(texture->getDescriptorInfo());
		}

		VkWriteDescriptorSet writeDescriptorSet{};
		writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		writeDescriptorSet.pNext = nullptr;
		writeDescriptorSet.dstSet = m_handle;
		writeDescriptorSet.dstBinding = bindingIndex;
		writeDescriptorSet.dstArrayElement = 0;
		writeDescriptorSet.descriptorCount = static_cast< uint32_t >(descriptorInfos.size());
		writeDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
		writeDescriptorSet.pImageInfo = descriptorInfos.data();
		writeDescriptorSet.pBufferInfo = nullptr;
		writeDescriptorSet.pTexelBufferView = nullptr;

		vkUpdateDescriptorSets(
			m_descriptorPool->device()->handle(),
			1, &writeDescriptorSet,
			0, VK_NULL_HANDLE
		);

		return true;
	}
}
