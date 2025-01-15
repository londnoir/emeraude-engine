/*
 * src/Vulkan/QueueFamilySQ.hpp
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

/* Local inclusions for usages. */
#include "Queue.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief Describe a queue family for a device using one queue.
	 * @extends Emeraude::Vulkan::QueueFamilyInterface The base class of queue family.
	 */
	class QueueFamilySQ final : public QueueFamilyInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanQueueFamilySQ"};

			/**
			 * @brief Constructs a queue family structure.
			 * @param index The index inside the physical device.
			 */
			explicit QueueFamilySQ (uint32_t index) noexcept;

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
				return 1;
			}

			/** @copydoc Emeraude::Vulkan::QueueFamilyInterface::hasSingleQueue() */
			[[nodiscard]]
			bool
			hasSingleQueue () const noexcept override
			{
				return true;
			}

			/** @copydoc Emeraude::Vulkan::QueueFamilyInterface::declareQueueStructure() */
			[[nodiscard]]
			bool
			declareQueueStructure (const std::vector< std::pair< QueueJob, float > > & /*structure*/) noexcept override
			{
				Tracer::error(ClassId, "This is a single queue family !");

				return false;
			}

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
				/* NOTE: There is no use for job or priority here. */
				return m_queue.get();
			}

		private:

			uint32_t m_queueFamilyIndex;
			float m_queuePriority{1.0F};
			std::unique_ptr< Queue > m_queue;
	};
}
