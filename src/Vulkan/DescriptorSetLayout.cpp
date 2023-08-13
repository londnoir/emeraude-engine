/*
 * Emeraude/Vulkan/DescriptorSetLayout.cpp
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

#include "DescriptorSetLayout.hpp"

/* Local inclusions. */
#include "Device.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	DescriptorSetLayout::DescriptorSetLayout (const std::shared_ptr< Device > & device, VkDescriptorSetLayoutCreateFlags flags) noexcept
		: AbstractDeviceDependentObject(device)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = flags;
		m_createInfo.bindingCount = 0;
		m_createInfo.pBindings = nullptr;
	}

	DescriptorSetLayout::DescriptorSetLayout (const std::shared_ptr< Device > & device, const VkDescriptorSetLayoutCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo)
	{

	}

	DescriptorSetLayout::~DescriptorSetLayout ()
	{
		this->destroyFromHardware();
	}

	bool
	DescriptorSetLayout::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this descriptor set layout !");

			return false;
		}

		if ( m_setLayoutBindings.empty() )
		{
			Tracer::error(ClassId, "No binding to create this descriptor set layout !");

			return false;
		}

		m_createInfo.bindingCount = m_setLayoutBindings.size();
		m_createInfo.pBindings = m_setLayoutBindings.data();

		const auto result = vkCreateDescriptorSetLayout(this->device()->handle(), &m_createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create descriptor set layout : " << vkResultToCString(result) << " !";

			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The descriptor set layout " << m_handle << " (" << this->identifier() << ") is successfully created !";

		return true;
	}

	bool
	DescriptorSetLayout::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the descriptor set layout " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		if ( m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroyDescriptorSetLayout(this->device()->handle(), m_handle, nullptr);

			TraceSuccess{ClassId} << "The descriptor set layout " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		/* FIXME: Descriptor set layout can be instanced without the need of being created. */
		this->setCreated();
		this->setDestroyed();

		return true;
	}

	bool
	DescriptorSetLayout::declare (VkDescriptorSetLayoutBinding setLayoutBinding) noexcept
	{
		if ( this->isCreated() )
		{
			Tracer::error(ClassId, "Cannot declares binding when the descriptor set layout is created !");

			return false;
		}

		if ( setLayoutBinding.descriptorType >= VK_DESCRIPTOR_TYPE_MAX_ENUM )
		{
			Tracer::error(ClassId, "Invalid descriptor type !");

			return false;
		}

		auto bindingExists = std::any_of(m_setLayoutBindings.cbegin(), m_setLayoutBindings.cend(), [setLayoutBinding] (const auto & current) {
			return current.binding == setLayoutBinding.binding;
		});

		if ( bindingExists )
		{
			TraceError{ClassId} << "Binding #" << setLayoutBinding.binding << " already declared in this descriptor set layout !";

			return false;
		}

		m_setLayoutBindings.emplace_back(setLayoutBinding);

		return true;
	}

	bool
	DescriptorSetLayout::declareSampler (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount, const VkSampler * pImmutableSamplers) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_SAMPLER,
			descriptorCount,
			stageFlags,
			pImmutableSamplers
		});
	}

	bool
	DescriptorSetLayout::declareCombinedImageSampler (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount, const VkSampler * pImmutableSamplers) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			descriptorCount,
			stageFlags,
			pImmutableSamplers
		});
	}

	bool
	DescriptorSetLayout::declareSampledImage (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareStorageImage (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareUniformTexelBuffer (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareStorageTexelBuffer (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareUniformBuffer (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareStorageBuffer (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareUniformBufferDynamic (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareStorageTexelDynamic (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareInputAttachment (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareInlineUniformBlockEXT (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareAccelerationStructureKHR (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	bool
	DescriptorSetLayout::declareAccelerationStructureNV (uint32_t binding, VkShaderStageFlags stageFlags, uint32_t descriptorCount) noexcept
	{
		return this->declare(VkDescriptorSetLayoutBinding{
			binding,
			VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV,
			descriptorCount,
			stageFlags,
			nullptr
		});
	}

	VkDescriptorSetLayout
	DescriptorSetLayout::handle () const noexcept
	{
		return m_handle;
	}

	VkDescriptorSetLayoutCreateInfo
	DescriptorSetLayout::createInfo () const noexcept
	{
		return m_createInfo;
	}

	size_t
	DescriptorSetLayout::hash () const noexcept
	{
		return DescriptorSetLayout::getHash(m_setLayoutBindings, m_createInfo.flags);
	}

	size_t
	DescriptorSetLayout::getHash (const std::vector< VkDescriptorSetLayoutBinding > & bindings, VkDescriptorSetLayoutCreateFlags flags) noexcept
	{
		/* FIXME: Weak and unstable hash method !! */
		size_t hashValue = 0;
		hashValue += bindings.size();
		hashValue += flags;

		for ( const auto & binding : bindings )
		{
			hashValue += binding.binding;
			hashValue += binding.descriptorCount;
			hashValue += binding.stageFlags;
		}

		return hashValue;
	}

	std::ostream &
	operator<< (std::ostream & out, const DescriptorSetLayout & obj)
	{
		out << "Descriptor set layout @" << obj.m_handle << " (" << obj.identifier() << ") :\n";

		for ( const auto & setLayoutBinding : obj.m_setLayoutBindings )
		{
			out <<
				"Set layout binding : " << setLayoutBinding.binding << "\n"
				"\t" "Descriptor type: " << setLayoutBinding.descriptorType << "\n"
				"\t" "Descriptor count: " << setLayoutBinding.descriptorCount << "\n"
				"\t" "Stage flags: " << setLayoutBinding.stageFlags << "\n"
				"\t" "Immutable Samplers: " << setLayoutBinding.pImmutableSamplers << "\n\n";
		}

		return out;
	}

	std::string
	to_string (const DescriptorSetLayout & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
