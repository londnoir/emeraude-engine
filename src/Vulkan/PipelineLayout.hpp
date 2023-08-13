/*
 * Emeraude/Vulkan/PipelineLayout.hpp
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
#include "DescriptorSetLayout.hpp"

namespace Emeraude::Vulkan
{
	class Device;

	/**
	 * @brief The PipelineLayout class.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This Vulkan object needs a device.
	 */
	class PipelineLayout final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanPipelineLayout"};

			/**
			 * @brief Constructs a pipeline layout.
			 * @param device A reference to a smart pointer of a device.
			 * @param descriptorSetLayouts A reference to a list of descriptor set layouts. Default empty.
			 * @param pushConstantRanges A reference to a list of push constant ranges. Default empty.
			 * @param createFlags The create info flags. Default none.
			 */
			explicit PipelineLayout (const std::shared_ptr< Device > & device, const std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts = {}, const std::vector< VkPushConstantRange > & pushConstantRanges = {}, VkPipelineLayoutCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a pipeline layout with create info.
			 * @param device A reference to a smart pointer of a device.
			 * @param createInfo A reference to a create info.
			 * @param descriptorSetLayouts A reference to a list of descriptor set layouts. Default empty.
			 * @param pushConstantRanges A reference to a list of push constant ranges. Default empty.
			 */
			PipelineLayout (const std::shared_ptr< Device > & device, const VkPipelineLayoutCreateInfo & createInfo, const std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts = {}, const std::vector< VkPushConstantRange > & pushConstantRanges = {}) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			PipelineLayout (const PipelineLayout & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			PipelineLayout (PipelineLayout && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			PipelineLayout & operator= (const PipelineLayout & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			PipelineLayout & operator= (PipelineLayout && copy) noexcept = default;

			/**
			 * @brief Destructs the pipeline layout.
			 */
			~PipelineLayout () override;

			/**
			 * @brief Performs an equality comparison between pipeline layouts.
			 * @param operand A reference to an other pipeline layout.
			 * @return bool
			 */
			[[nodiscard]]
			bool operator== (const PipelineLayout & operand) const noexcept;

			/**
			 * @brief Performs an inequality comparison between pipeline layouts.
			 * @param operand A reference to an other pipeline layout.
			 * @return bool
			 */
			[[nodiscard]]
			bool operator!= (const PipelineLayout & operand) const noexcept;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Returns the pipeline layout vulkan handle.
			 * @param VkPipelineLayout
			 */
			[[nodiscard]]
			VkPipelineLayout handle () const noexcept;

			/**
			 * @brief Returns the pipeline layout create info.
			 * @param VkPipelineLayoutCreateInfo
			 */
			[[nodiscard]]
			VkPipelineLayoutCreateInfo createInfo () const noexcept;

			/**
			 * @brief Returns the list of descriptor set layouts associated to this pipeline layout.
			 * @param const vector< shared_ptr< DescriptorSetLayout > > &
			 */
			[[nodiscard]]
			const std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts () const noexcept;

			/**
			 * @brief Returns the push constant range list.
			 * @return const std::vector< VkPushConstantRange > &
			 */
			[[nodiscard]]
			const std::vector< VkPushConstantRange > & pushConstantRanges () const noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const PipelineLayout & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const PipelineLayout & obj) noexcept;

			/**
			 * @brief Returns a hash for a pipeline layout according to constructor params.
			 * @param descriptorSetLayouts A reference to a list of descriptor set layouts.
			 * @param pushConstantRanges A reference to a list of push constant ranges.
			 * @param flags Flags for the create info.
			 * @return size_t
			 */
			[[nodiscard]]
			static size_t getHash (const std::vector< std::shared_ptr< DescriptorSetLayout > > & descriptorSetLayouts, const std::vector< VkPushConstantRange > & pushConstantRanges, VkPipelineLayoutCreateFlags flags) noexcept;

		private:

			VkPipelineLayout m_handle{VK_NULL_HANDLE};
			VkPipelineLayoutCreateInfo m_createInfo{};
			std::vector< std::shared_ptr< DescriptorSetLayout > > m_descriptorSetLayouts;
			std::vector< VkPushConstantRange > m_pushConstantRanges;
	};
}
