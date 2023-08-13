/*
 * Emeraude/Vulkan/DescriptorSetLayout.hpp
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

/* C/C++ standard libraries */
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "AbstractDeviceDependentObject.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The DescriptorSetLayout class
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This is a device dependant vulkan object.
	 */
	class DescriptorSetLayout final : public AbstractDeviceDependentObject
	{
		public:

			enum Flag
			{
				UseLocationVBO = 1
			};

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanDescriptorSetLayout"};

			/**
			 * @brief Constructs a descriptor set layout.
			 * @param device A reference to a smart pointer of a device.
			 * @param createFlags The create info flags. Default none.
			 */
			explicit DescriptorSetLayout (const std::shared_ptr< Device > & device, VkDescriptorSetLayoutCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a descriptor set layout with create info.
			 * @param device A reference to a smart pointer to device where the render pass will be performed.
			 * @param createInfo A reference to a create info.
			 */
			DescriptorSetLayout (const std::shared_ptr< Device > & device, const VkDescriptorSetLayoutCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			DescriptorSetLayout (const DescriptorSetLayout & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			DescriptorSetLayout (DescriptorSetLayout && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			DescriptorSetLayout & operator= (const DescriptorSetLayout & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			DescriptorSetLayout & operator= (DescriptorSetLayout && copy) noexcept = default;

			/**
			 * @brief Destructs the descriptor set layout.
			 */
			~DescriptorSetLayout () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Declares a set layout binding.
			 * @param setLayoutBinding
			 * @return bool
			 */
			bool declare (VkDescriptorSetLayoutBinding setLayoutBinding) noexcept;

			/**
			 * @brief Declares a sampler binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @param pImmutableSamplers The immutable samplers to bind. Default none.
			 * @return bool
			 */
			bool declareSampler (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1, const VkSampler * pImmutableSamplers = nullptr) noexcept;

			/**
			 * @brief Declare combined image sampler binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @param pImmutableSamplers he immutable samplers to bind. Default none.
			 * @return bool
			 */
			bool declareCombinedImageSampler (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1, const VkSampler * pImmutableSamplers = nullptr) noexcept;

			/**
			 * @brief Declares sampled image binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareSampledImage (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares storage image binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareStorageImage (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares uniform texel buffer binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareUniformTexelBuffer (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares storage texel buffer binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareStorageTexelBuffer (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares uniform buffer binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareUniformBuffer (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares storage buffer binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareStorageBuffer (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares uniform buffer dynamic binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareUniformBufferDynamic (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares storage texel dynamic binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareStorageTexelDynamic (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares input attachment binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareInputAttachment (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares inline uniform block binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareInlineUniformBlockEXT (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares acceleration structure binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareAccelerationStructureKHR (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Declares acceleration structure binding.
			 * @param binding The binding point.
			 * @param stageFlags Define at which stage of the shader the bond appears. Default all.
			 * @param descriptorCount Define the number of descriptor to bind. Default 1.
			 * @return bool
			 */
			bool declareAccelerationStructureNV (uint32_t binding, VkShaderStageFlags stageFlags = VK_SHADER_STAGE_ALL, uint32_t descriptorCount = 1) noexcept;

			/**
			 * @brief Returns the descriptor pool handle.
			 * @return VkDescriptorSetLayout
			 */
			[[nodiscard]]
			VkDescriptorSetLayout handle () const noexcept;

			/**
			 * @brief Returns the descriptor pool create info.
			 * @return VkDescriptorSetLayoutCreateInfo
			 */
			[[nodiscard]]
			VkDescriptorSetLayoutCreateInfo createInfo () const noexcept;

			/**
			 * @brief Returns the descriptor set layout hash.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t hash () const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const DescriptorSetLayout & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const DescriptorSetLayout & obj) noexcept;

			/**
			 * @brief Returns a hash for a descriptor layout according to constructor params.
			 * @return size_t
			 */
			[[nodiscard]]
			static size_t getHash (const std::vector< VkDescriptorSetLayoutBinding > & bindings, VkDescriptorSetLayoutCreateFlags flags) noexcept;

		private:

			VkDescriptorSetLayout m_handle{VK_NULL_HANDLE};
			VkDescriptorSetLayoutCreateInfo m_createInfo{};
			std::vector< VkDescriptorSetLayoutBinding > m_setLayoutBindings;
	};
}
