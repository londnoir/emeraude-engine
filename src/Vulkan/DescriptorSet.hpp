/*
 * Emeraude/Vulkan/DescriptorSet.hpp
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
#include "AbstractObject.hpp"

/* Local inclusions for usages. */
#include "DescriptorPool.hpp"
#include "DescriptorSetLayout.hpp"
#include "Graphics/TextureResource/Abstract.hpp"
#include "UniformBufferObject.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The descriptor set wrapper class.
	 * @extends Emeraude::Vulkan::AbstractObject This object will use the descriptor pool to get the device.
	 */
	class DescriptorSet final : public AbstractObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanDescriptorSet"};

			/**
			 * @brief Constructs a descriptor set.
			 * @param descriptorPool The reference to the descriptor pool smart pointer.
			 * @param descriptorSetLayout The reference to the descriptor layout smart pointer.
			 */
			DescriptorSet (const std::shared_ptr< DescriptorPool > & descriptorPool, const std::shared_ptr< DescriptorSetLayout > & descriptorSetLayout) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			DescriptorSet (const DescriptorSet & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			DescriptorSet (DescriptorSet && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			DescriptorSet & operator= (const DescriptorSet & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			DescriptorSet & operator= (DescriptorSet && copy) noexcept = default;

			/**
			 * @brief Destructs the descriptor set.
			 */
			~DescriptorSet () override;

			/**
			 * @brief Creates the descriptor set in video memory.
			 * @return bool
			 */
			bool create () noexcept;

			/**
			 * @brief Destroys the descriptor set from video memory.
			 * @return bool
			 */
			bool destroy () noexcept;

			/**
			 * @brief Returns the descriptor set vulkan handle.
			 * @return VkDescriptorSet
			 */
			[[nodiscard]]
			VkDescriptorSet handle () const noexcept;

			/**
			 * @brief Returns the responsible descriptor pool smart pointer.
			 * @return const std::shared_ptr< DescriptorPool > &
			 */
			[[nodiscard]]
			const std::shared_ptr< DescriptorPool > & descriptorPool () const noexcept;

			/**
			 * @brief Returns the descriptor layout smart pointer.
			 * @return const std::shared_ptr< DescriptorSetLayout > &
			 */
			[[nodiscard]]
			const std::shared_ptr< DescriptorSetLayout > & descriptorSetLayout () const noexcept;

			/**
			 * @brief Writes a uniform buffer object to the descriptor set.
			 * @param UBO A reference to the uniform buffer object smart pointer.
			 * @param bindingIndex The binding index of the UBO inside the descriptor set layout.
			 * @param offset The offset to the UBO where to data lies. Default at the beginning.
			 * @return bool
			 */
			[[nodiscard]]
			bool writeUniformBufferObject (UniformBufferObject & UBO, uint32_t bindingIndex, uint32_t offset = 0) const noexcept;

			/**
			 * @brief Writes a bunch of uniform buffer objects to the descriptor set.
			 * @param UBOs A reference to a list of uniform buffer object smart pointers.
			 * @param bindingIndex The binding index of the first UBO inside the descriptor set layout.
			 * @return bool
			 */
			[[nodiscard]]
			bool writeUniformBufferObjects (const std::vector< std::shared_ptr< UniformBufferObject > > & UBOs, uint32_t bindingIndex) const noexcept;

			/**
			 * @brief Writes a sampled texture to the descriptor set.
			 * @param image A reference to the texture smart pointer.
			 * @param bindingIndex The binding index of the texture inside the descriptor set layout.
			 * @return bool
			 */
			[[nodiscard]]
			bool writeSampler (const std::shared_ptr< Graphics::TextureResource::Abstract > & texture, uint32_t bindingIndex) const noexcept;

			/**
			 * @brief Writes a bunch of sampled texture2Ds to the descriptor set.
			 * @param image A reference to a list of texture2Ds smart pointer.
			 * @param bindingIndex The binding index of the first texture inside the descriptor set layout.
			 * @return bool
			 */
			[[nodiscard]]
			bool writeSamplers (const std::vector< std::shared_ptr< Graphics::TextureResource::Abstract > > & textures, uint32_t bindingIndex) const noexcept;

			/**
			 * @brief Writes a sampled texture to the descriptor set.
			 * @param image A reference to the texture smart pointer.
			 * @param bindingIndex The binding index of the texture inside the descriptor set layout.
			 * @return bool
			 */
			[[nodiscard]]
			bool writeCombinedImageSampler (const std::shared_ptr< Graphics::TextureResource::Abstract > & texture, uint32_t bindingIndex) const noexcept;

			/**
			 * @brief Writes a bunch of sampled texture2Ds to the descriptor set.
			 * @param image A reference to a list of texture2Ds smart pointer.
			 * @param bindingIndex The binding index of the first texture inside the descriptor set layout.
			 * @return bool
			 */
			[[nodiscard]]
			bool writeCombinedImageSamplers (const std::vector< std::shared_ptr< Graphics::TextureResource::Abstract > > & textures, uint32_t bindingIndex) const noexcept;

		private:

			VkDescriptorSet m_handle{VK_NULL_HANDLE};
			std::shared_ptr< DescriptorPool > m_descriptorPool;
			std::shared_ptr< DescriptorSetLayout > m_descriptorSetLayout;
	};
}
