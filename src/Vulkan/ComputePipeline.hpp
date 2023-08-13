/*
 * Emeraude/Vulkan/ComputePipeline.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractDeviceDependentObject.hpp"

/* Local inclusions for usages. */
#include "PipelineLayout.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The ComputePipeline class.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This object needs a device.
	 */
	class ComputePipeline final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanComputePipeline"};

			/**
			 * @brief Constructs a compute pipeline.
			 * @param pipelineLayout A reference to pipeline layout smart pointer.
			 * @param createFlags The create info flags. Default none.
			 */
			explicit ComputePipeline (const std::shared_ptr< PipelineLayout > & pipelineLayout, VkPipelineCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a compute pipeline with a create info.
			 * @param pipelineLayout A reference to pipeline layout smart pointer.
			 * @param createInfo A reference to a create info.
			 */
			ComputePipeline (const std::shared_ptr< PipelineLayout > & pipelineLayout, const VkComputePipelineCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ComputePipeline (const ComputePipeline & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ComputePipeline (ComputePipeline && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			ComputePipeline & operator= (const ComputePipeline & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			ComputePipeline & operator= (ComputePipeline && copy) noexcept = default;

			/**
			 * @brief Destructs the compute pipeline.
			 */
			~ComputePipeline () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Returns the pipeline vulkan handle.
			 * @return VkPipeline
			 */
			[[nodiscard]]
			VkPipeline handle () const noexcept;

			/**
			 * @brief Returns the pipeline create info.
			 * @return VkComputePipelineCreateInfo
			 */
			[[nodiscard]]
			VkComputePipelineCreateInfo createInfo () const noexcept;

			/**
			 * @brief Returns the associated pipeline layout smart pointer.
			 * @return std::shared_ptr< PipelineLayout >
			 */
			[[nodiscard]]
			std::shared_ptr< PipelineLayout > pipelineLayout () const noexcept;

			/**
			 * @brief Returns a hash for this graphics pipeline according to constructor params.
			 * @return size_t
			 */
			[[nodiscard]]
			static size_t getHash () noexcept;

		private:

			/* FIXME: Remove this !!!! */
			static size_t s_fakeHash;

			VkPipeline m_handle{VK_NULL_HANDLE};
			VkComputePipelineCreateInfo m_createInfo{};
			std::shared_ptr< PipelineLayout > m_pipelineLayout;
	};
}
