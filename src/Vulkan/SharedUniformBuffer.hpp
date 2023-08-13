/*
 * Emeraude/Vulkan/SharedUniformBuffer.hpp
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
#include <mutex>
#include <vector>

/* Local inclusions for usages. */
#include "Saphir/Declaration/UniformBlock.hpp"
#include "UniformBufferObject.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The shared uniform buffer class.
	 * @note This is a higher concept to manage an UBO to store multiple data with a fixed-sized structure.
	 */
	class SharedUniformBuffer final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanSharedUniformBuffer"};

			/**
			 * @brief Constructs a shared uniform buffer.
			 * @param device A reference to the device smart pointer.
			 * @param uniformBlock The declaration of a uniform block [std::move].
			 * @param maxElementCount The max number of element to hold in one UBO. Default, compute the maximum according to structure size and UBO properties.
			 */
			SharedUniformBuffer (const std::shared_ptr< Device > & device, Saphir::Declaration::UniformBlock uniformBlock, size_t maxElementCount = 0) noexcept;

			/**
			 * @brief Returns whether the shared uniform buffer is usable.
			 * @return
			 */
			[[nodiscard]]
			bool usable () const noexcept;

			/**
			 * @brief Returns the uniform buffer object pointer.
			 * @param index The element index.
			 * @return const UniformBufferObject *
			 */
			[[nodiscard]]
			const UniformBufferObject * uniformBufferObject (uint32_t index) const noexcept;

			/**
			 * @brief Returns the uniform buffer object pointer.
			 * @param index The element index.
			 * @return UniformBufferObject *
			 */
			[[nodiscard]]
			UniformBufferObject * uniformBufferObject (uint32_t index) noexcept;

			/**
			 * @brief Adds a new element to the uniform buffer object.
			 * @param element A raw pointer to link the element.
			 * @param offset A reference to an unsigned integer to get the offset.
			 * @return bool
			 */
			[[nodiscard]]
			bool addElement (const void * element, uint32_t & offset) noexcept;

			/**
			 * @brief Removes an element from the uniform buffer object.
			 * @param element A raw pointer from the linked element.
			 * @return void
			 */
			void removeElement (const void * element) noexcept;

			/**
			 * @brief Returns the number of element present in the buffer.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t elementCount () const noexcept;

			/**
			 * @brief Writes element data to the UBO.
			 * @note There is no check in this function. All have been done at initialization time.
			 * @param index The element index.
			 * @param data A pointer to the source data.
			 * @return bool
			 */
			[[nodiscard]]
			bool writeElementData (uint32_t index, const void * data) noexcept;

		private:

			/**
			 * @brief Adds a buffer to the UBO list.
			 * @return bool
			 */
			[[nodiscard]]
			bool addBuffer () noexcept;

			/**
			 * @brief Returns the right UBO index from element index.
			 * @param index The element index.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t bufferIndex (uint32_t index) const noexcept;

			std::shared_ptr< Device > m_device;
			Saphir::Declaration::UniformBlock m_uniformBlock;
			size_t m_uniformBlockSize;
			size_t m_maxElementCountPerUBO{0};
			size_t m_blockAlignedSize{0};
			std::vector< std::unique_ptr< UniformBufferObject > > m_uniformBufferObjects{};
			std::vector< const void * > m_elements{};
			mutable std::mutex m_memoryAccess{};
	};
}
