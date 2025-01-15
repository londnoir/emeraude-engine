/*
 * src/Vulkan/QueueFamily.hpp
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
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>
#include <memory>

/* Local inclusions for inheritances. */
#include "QueueFamilyInterface.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief Describe a queue family for a device using multiple queues.
	 * @extends Emeraude::Vulkan::QueueFamilyInterface The base class of queue family.
	 */
	class QueueFamily final : public QueueFamilyInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanQueueFamily"};

			/**
			 * @brief Constructs a queue family structure.
			 * @param index The index inside the physical device.
			 * @param maxQueueCount The max number of queue for this family available with the physical device.
			 */
			QueueFamily (uint32_t index, size_t maxQueueCount) noexcept;

			/** @copydoc Emeraude::Vulkan::QueueFamilyInterface::index() */
			[[nodiscard]]
			uint32_t
			index () const noexcept override
			{
				return m_queueFamilyIndex;
			}

			/** @copydoc Emeraude::Vulkan::QueueFamilyInterface::maxQueueCount() */
			[[nodiscard]]
			size_t
			maxQueueCount () const noexcept override
			{
				return m_maxQueueCount;
			}

			/** @copydoc Emeraude::Vulkan::QueueFamilyInterface::hasSingleQueue() */
			[[nodiscard]]
			bool
			hasSingleQueue () const noexcept override
			{
				return false;
			}

			/** @copydoc Emeraude::Vulkan::QueueFamilyInterface::declareQueueStructure() */
			[[nodiscard]]
			bool declareQueueStructure (const std::vector< std::pair< QueueJob, float > > & structure) noexcept override;

			/** @copydoc Emeraude::Vulkan::QueueFamilyInterface::getCreateInfo() */
			[[nodiscard]]
			VkDeviceQueueCreateInfo getCreateInfo (VkDeviceQueueCreateFlags createFlag) const noexcept override;

			/** @copydoc Emeraude::Vulkan::QueueFamilyInterface::retrieveQueuesFromDevice() */
			[[nodiscard]]
			bool retrieveQueuesFromDevice (const std::shared_ptr< Device > & device) noexcept override;

			/** @copydoc Emeraude::Vulkan::QueueFamilyInterface::queue() */
			[[nodiscard]]
			Queue *
			queue (QueueJob /*job*/, QueuePriority /*priority*/) noexcept override
			{
				// FIXME : Use parameters to get the right queue !
				return m_queues[0].get();
			}

		private:

			uint32_t m_queueFamilyIndex;
			size_t m_maxQueueCount;
			std::vector< QueueJob > m_queueJobs;
			std::vector< float > m_queuePriorities;
			std::vector< std::unique_ptr< Queue > > m_queues;
	};
}
