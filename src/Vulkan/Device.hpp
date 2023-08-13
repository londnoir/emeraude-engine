/*
 * Emeraude/Vulkan/Device.hpp
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
#include <algorithm>
#include <array>
#include <memory>
#include <optional>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "AbstractObject.hpp"
#include "NamedItem.hpp"

/* Local inclusions for usages. */
#include "DeviceRequirements.hpp"
#include "PhysicalDevice.hpp"
#include "QueueFamilyInterface.hpp"

namespace Emeraude::Vulkan
{
	class Instance;

	/**
	 * @brief Defines a logical device from a physical device.
	 * @extends Emeraude::Vulkan::AbstractObject Obviously this is the device, so simple object is ok.
	 * @extends Libraries::NamedItem to set a name on a device.
	 */
	class Device final : public std::enable_shared_from_this< Device >, public AbstractObject, public Libraries::NamedItem
	{
		public:

			/* Settings keys */
			static constexpr auto EnableDeviceDebugKey = "Video/Vulkan/EnableDeviceDebug";
			static constexpr auto ShowAvailableDeviceExtensionsKey = "Video/Vulkan/Extensions/ShowAvailableForDevice";

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanDevice"};

			/**
			 * @brief Constructs a device.
			 * @param physicalDevice A reference to a physical device smart pointer.
			 */
			explicit Device (const std::shared_ptr< PhysicalDevice > & physicalDevice) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Device (const Device & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Device (Device && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Device & operator= (const Device & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Device & operator= (Device && copy) noexcept = delete;

			/**
			 * @brief Destructs the device.
			 */
			~Device () override;

			/**
			 * @brief Creates the device.
			 * @param requirements A reference to a device requirements.
			 * @param extensions A reference to a vector of extensions.
			 * @return bool
			 */
			[[nodiscard]]
			bool create (const DeviceRequirements & requirements, const std::vector< const char * > & extensions) noexcept;

			/**
			 * @brief Destroys the device.
			 * @return void
			 */
			void destroy () noexcept;

			/**
			 * @brief Returns the physical device smart pointer.
			 * @return const std::shared_ptr< PhysicalDevice > &
			 */
			[[nodiscard]]
			const std::shared_ptr< PhysicalDevice > & physicalDevice () const noexcept;

			/**
			 * @brief Returns the device handle.
			 * @return VkDevice
			 */
			[[nodiscard]]
			VkDevice handle () const noexcept;

			/**
			 * @brief Returns the Vulkan validation layer state.
			 * @return bool
			 */
			[[nodiscard]]
			bool isDebugModeEnabled () const noexcept;

			/**
			 * @brief Set the debug mode state.
			 * @param state The state.
			 * @return void
			 */
			void enableDebugMode (bool state) noexcept;

			/**
			 * @brief Returns whether the device has only one family queue for all.
			 * @return bool
			 */
			[[nodiscard]]
			bool hasBasicSupport () const noexcept;

			/**
			 * @brief Returns whether the device has been setup for graphics.
			 * @return bool
			 */
			[[nodiscard]]
			bool hasGraphicsQueues () const noexcept;

			/**
			 * @brief Returns the queue family index for graphics.
			 * @warning Be sure of calling hasGraphicsQueues() before trusting the index.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t getGraphicsFamilyIndex () const noexcept;

			/**
			 * @brief Returns whether the device has been setup for compute queues.
			 * @return bool
			 */
			[[nodiscard]]
			bool hasComputeQueues () const noexcept;

			/**
			 * @brief Returns the queue family index for compute queues.
			 * @warning Be sure of calling hasComputeQueues() before trusting the index.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t getComputeFamilyIndex () const noexcept;

			/**
			 * @brief Returns whether the device has been setup to have separated transfer queue.
			 * @return bool
			 */
			[[nodiscard]]
			bool hasTransferQueues () const noexcept;

			/**
			 * @brief Returns the queue family index for transfer-only queues.
			 * @warning Be sure of calling hasTransferQueues() before trusting the index.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t getTransferFamilyIndex () const noexcept;

			/**
			 * @brief Returns a queue for a specific purpose.
			 * @note This can return always the same queue for a basic device.
			 * @warning This can also return nullptr.
			 * @param job The requested job type from the queue.
			 * @param priority The priority of the queue.
			 * @return Queue *
			 */
			[[nodiscard]]
			Queue * getQueue (QueueJob job, QueuePriority priority) const noexcept;

			/**
			 * @brief Waits for a device to become idle.
			 * @return bool
			 */
			bool waitIdle () const noexcept;

			/**
			 * @brief Finds the suitable memory type.
			 * @param memoryTypeFilter The memory type.
			 * @param propertyFlags The access type of memory requested.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t findMemoryType (uint32_t memoryTypeFilter, VkMemoryPropertyFlags propertyFlags) const noexcept;

			/**
			 * @brief Finds a supported format from device.
			 * @param candidates A reference to a format vector.
			 * @param tiling
			 * @param featureFlags
			 * @return VkFormat
			 */
			[[nodiscard]]
			VkFormat findSupportedFormat (const std::vector< VkFormat > & formats, VkImageTiling tiling, VkFormatFeatureFlags featureFlags) const noexcept;

		private:

			/**
			 * @brief Prepares queues configuration from requirements.
			 * @param requirements A reference to a device requirements.
			 * @param queueCreateInfos A reference to a a list of CreateInfo for Vulkan queues to complete.
			 * @return bool
			 */
			[[nodiscard]]
			bool prepareQueues (const DeviceRequirements & requirements, std::vector< VkDeviceQueueCreateInfo > & queueCreateInfos) noexcept;

			/**
			 * @brief Declares queues for a device with a single queue family.
			 * @param requirements A reference to a device requirements.
			 * @param queueFamilyProperty A reference to the queue family properties.
			 * @return bool
			 */
			[[nodiscard]]
			bool declareQueuesFromSingleQueueFamily (const DeviceRequirements & requirements, const VkQueueFamilyProperties & queueFamilyProperty) noexcept;

			/**
			 * @brief Declares queues for a device with multiple queue family.
			 * @param requirements A reference to a device requirements.
			 * @param queueFamilyProperties A reference to a vector of queue family properties.
			 * @return bool
			 */
			[[nodiscard]]
			bool declareQueuesFromMultipleQueueFamilies (const DeviceRequirements & requirements, const std::vector< VkQueueFamilyProperties > & queueFamilyProperties) noexcept;

			/**
			 * @brief Creates the device with the defined and verified queues.
			 * @param requirements A reference to a device requirements.
			 * @param queueCreateInfos A reference to a list of CreateInfo for Vulkan queues.
			 * @param extensions A reference to a list of extensions to enable with the device.
			 * @return bool
			 */
			[[nodiscard]]
			bool createDevice (const DeviceRequirements & requirements, const std::vector< VkDeviceQueueCreateInfo > & queueCreateInfos, const std::vector< const char * > & extensions) noexcept;

			/* Flag names. */
			static constexpr auto DebugMode = 0UL;
			static constexpr auto HasBasicSupport = 1UL;

			std::shared_ptr< PhysicalDevice > m_physicalDevice;
			VkDevice m_handle{VK_NULL_HANDLE};
			std::vector< std::shared_ptr< QueueFamilyInterface > > m_queueFamilies{};
			std::map< QueueJob, std::shared_ptr< QueueFamilyInterface > > m_queueFamilyPerJob{};
			mutable std::mutex m_mutex{};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*DebugMode*/,
				false/*HasBasicSupport*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
