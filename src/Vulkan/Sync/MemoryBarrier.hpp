/*
 * Emeraude/Vulkan/Sync/MemoryBarrier.hpp
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

/* Local inclusions for inheritances. */
#include "../AbstractObject.hpp"

namespace Emeraude::Vulkan::Sync
{
	/**
	 * @brief The memory barrier class. This is used for synchronize command buffers.
	 * @extends Emeraude::Vulkan::AbstractObject This is a sample Vulkan structure.
	 */
	class MemoryBarrier final : public AbstractObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanMemoryBarrier"};

			/**
			 * @brief Constructs a memory barrier.
			 * @param srcAccessMask A bitmask of VkAccessFlagBits specifying a source access mask.
			 * @param dstAccessMask A bitmask of VkAccessFlagBits specifying a destination access mask.
			 */
			MemoryBarrier (VkAccessFlags srcAccessMask, VkAccessFlags dstAccessMask) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			MemoryBarrier (const MemoryBarrier & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			MemoryBarrier (MemoryBarrier && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			MemoryBarrier & operator= (const MemoryBarrier & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			MemoryBarrier & operator= (MemoryBarrier && copy) noexcept = default;

			/**
			 * @brief Destructs the memory barrier.
			 */
			~MemoryBarrier () override;

			/**
			 * @brief Returns a reference to the memory barrier vulkan structure.
			 * @param const VkMemoryBarrier &
			 */
			[[nodiscard]]
			const VkMemoryBarrier & get () const noexcept;

		private:

			VkMemoryBarrier m_barrier{};
	};
}
