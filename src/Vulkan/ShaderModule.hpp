/*
 * src/Vulkan/ShaderModule.hpp
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

#pragma once

/* STL inclusions. */
#include <cstdint>
#include <memory>
#include <vector>

/* Local inclusions for inheritances. */
#include "AbstractDeviceDependentObject.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The ShaderModule class.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This Vulkan object needs a device.
	 */
	class ShaderModule final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanShaderModule"};

			/**
			 * @brief Constructs a shader module.
			 * @param device A reference to a device smart pointer.
			 * @param shaderType The vulkan shader type.
			 * @param binaryCode A reference to a binary data vector.
			 * @param createFlags The create info flags. Default none.
			 */
			ShaderModule (const std::shared_ptr< Device > & device, VkShaderStageFlagBits shaderType, const std::vector< uint32_t > & binaryCode, VkShaderModuleCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a shader module with a create info.
			 * @param device A reference to a smart pointer of the device.
			 * @param createInfo A reference to the create info.
			 * @param shaderType The vulkan shader type.
			 * @param binaryCode A reference to a binary data vector.
			 */
			ShaderModule (const std::shared_ptr< Device > & device, const VkShaderModuleCreateInfo & createInfo, VkShaderStageFlagBits shaderType, const std::vector< uint32_t > & binaryCode) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ShaderModule (const ShaderModule & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ShaderModule (ShaderModule && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			ShaderModule & operator= (const ShaderModule & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			ShaderModule & operator= (ShaderModule && copy) noexcept = default;

			/**
			 * @brief Destructs a shader module.
			 */
			~ShaderModule () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Returns the shader module handle.
			 * @return VkShaderModule
			 */
			[[nodiscard]]
			VkShaderModule
			handle () const noexcept
			{
				return m_handle;
			}

			/**
			 * @brief Returns the shader module create info.
			 * @return const VkShaderModuleCreateInfo &
			 */
			[[nodiscard]]
			const VkShaderModuleCreateInfo &
			createInfo () const noexcept
			{
				return m_createInfo;
			}

			/**
			 * @brief Returns the pipeline shader stage create info.
			 * @return const VkPipelineShaderStageCreateInfo &
			 */
			[[nodiscard]]
			const VkPipelineShaderStageCreateInfo &
			pipelineShaderStageCreateInfo () const noexcept
			{
				return m_pipelineShaderStageCreateInfo;
			}

		private:

			/**
			 * @brief Prepares the pipeline shader create info.
			 * @return bool
			 */
			bool preparePipelineShaderStageCreateInfo () noexcept;

			VkShaderModule m_handle{VK_NULL_HANDLE};
			VkShaderModuleCreateInfo m_createInfo{};
			VkShaderStageFlagBits m_shaderType{};
			std::vector< uint32_t > m_binaryCode;
			std::vector< VkSpecializationMapEntry > m_mapEntries;
			VkSpecializationInfo m_specializationInfo{};
			VkPipelineShaderStageCreateInfo m_pipelineShaderStageCreateInfo{};
	};
}
