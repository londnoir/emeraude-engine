/*
 * Emeraude/Vulkan/ShaderModule.hpp
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

/* C/C++ standard libraries. */
#include <memory>
#include <vector>

/* Local inclusions for inheritances. */
#include "AbstractDeviceDependentObject.hpp"

/* Local inclusions for usages. */
#include "Saphir/AbstractShader.hpp"

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
			 * @param shader A reference to smart pointer of the saphir shader.
			 * @param createFlags The create info flags. Default none.
			 */
			ShaderModule (const std::shared_ptr< Device > & device, const std::shared_ptr< Saphir::AbstractShader > & shader, VkShaderModuleCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a shader module with a create info.
			 * @param device A reference to a smart pointer of the device.
			 * @param createInfo A reference to the create info.
			 * @param shader A reference to smart pointer of the saphir shader.
			 */
			ShaderModule (const std::shared_ptr< Device > & device, const VkShaderModuleCreateInfo & createInfo, const std::shared_ptr< Saphir::AbstractShader > & shader) noexcept;

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
			VkShaderModule handle () const noexcept;

			/**
			 * @brief Returns the shader module create info.
			 * @return VkShaderModuleCreateInfo
			 */
			[[nodiscard]]
			VkShaderModuleCreateInfo createInfo () const noexcept;

			/**
			 * @brief Returns the pipeline shader stage create info.
			 * @return const VkPipelineShaderStageCreateInfo &
			 */
			[[nodiscard]]
			const VkPipelineShaderStageCreateInfo & pipelineShaderStageCreateInfo () const noexcept;

			/**
			 * @brief Returns the saphir shader.
			 * @return std::shared_ptr< Saphir::AbstractShader >
			 */
			[[nodiscard]]
			std::shared_ptr< Saphir::AbstractShader > shader () const noexcept;

		private:

			/**
			 * @brief Prepares the pipeline shader create info.
			 * @return bool
			 */
			bool preparePipelineShaderStageCreateInfo () noexcept;

			VkShaderModule m_handle{VK_NULL_HANDLE};
			VkShaderModuleCreateInfo m_createInfo{};
			std::shared_ptr< Saphir::AbstractShader > m_shader;
			std::vector< VkSpecializationMapEntry > m_mapEntries{};
			VkSpecializationInfo m_specializationInfo{};
			VkPipelineShaderStageCreateInfo m_pipelineShaderStageCreateInfo{};
	};
}
