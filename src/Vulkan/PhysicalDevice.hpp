/*
 * Emeraude/Vulkan/PhysicalDevice.hpp
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
#include <optional>
#include <string>
#include <vector>

/* Local inclusions for usages. */
#include "Version.hpp"

/* Third-party libraries. */
#include "Third-Party-Inclusion/vulkan.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The physical device class to build a logical vulkan device.
	 */
	class PhysicalDevice final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanPhysicalDevice"};

			/**
			 * @brief Constructs a physical device.
			 * @param physicalDevice The handle from vulkan instance.
			 */
			explicit PhysicalDevice (const VkPhysicalDevice & physicalDevice) noexcept;

			/**
			 * @brief Returns the vulkan handle.
			 * @return const VkPhysicalDevice &
			 */
			[[nodiscard]]
			const VkPhysicalDevice & handle () const noexcept;

			/**
			 * @brief features
			 * @return const VkPhysicalDeviceFeatures &
			 */
			[[nodiscard]]
			const VkPhysicalDeviceFeatures & features () const noexcept;

			/**
			 * @brief Returns prefetched physical device properties.
			 * @return const VkPhysicalDeviceProperties &
			 */
			[[nodiscard]]
			const VkPhysicalDeviceProperties & properties () const noexcept;

			/**
			 * @brief Returns the device type as a string.
			 * @note Shortcut to PhysicalDevice::properties().
			 * @return std::string
			 */
			[[nodiscard]]
			inline
			std::string
			deviceType () const noexcept
			{
				switch ( m_properties.deviceType )
				{
					case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU :
						return "Integrated GPU device";

					case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU :
						return "Discrete GPU device";

					case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU :
						return "Virtual GPU device";

					case VK_PHYSICAL_DEVICE_TYPE_CPU :
						return "CPU device";

					case VK_PHYSICAL_DEVICE_TYPE_OTHER :
					default :
						return "Other device";
				}
			}

			/**
			 * @brief Returns the device name as a string.
			 * @note Shortcut to PhysicalDevice::properties().
			 * @return std::string
			 */
			[[nodiscard]]
			inline
			std::string
			deviceName () const noexcept
			{
				return m_properties.deviceName;
			}

			/**
			 * @brief Returns the API driver version.
			 * @note Shortcut to PhysicalDevice::properties().
			 * @return Libraries::Version
			 */
			[[nodiscard]]
			inline
			Libraries::Version
			APIDriver () const noexcept
			{
				return Libraries::Version{m_properties.apiVersion};
			}

			/**
			 * @brief Returns the API driver as a string.
			 * @note Shortcut to PhysicalDevice::properties().
			 * @return std::string
			 */
			[[nodiscard]]
			inline
			std::string
			APIDriverString () const noexcept
			{
				return to_string(this->APIDriver());
			}

			/**
			 * @brief Returns the driver version.
			 * @note Shortcut to PhysicalDevice::properties().
			 * @return Libraries::Version
			 */
			[[nodiscard]]
			inline
			Libraries::Version
			DriverVersion () const noexcept
			{
				return Libraries::Version{m_properties.driverVersion};
			}

			/**
			 * @brief Returns the driver version as a string.
			 * @note Shortcut to PhysicalDevice::properties().
			 * @return std::string
			 */
			[[nodiscard]]
			inline
			std::string
			DriverVersionString () const noexcept
			{
				return to_string(this->DriverVersion());
			}

			/**
			 * @brief Returns the vendor ID as a string.
			 * @note Shortcut to PhysicalDevice::properties().
			 * @return std::string
			 */
			[[nodiscard]]
			inline
			std::string
			vendorId () const noexcept
			{
				// NOLINTBEGIN(*-magic-numbers)
				switch ( m_properties.vendorID )
				{
					case 0x1002 :
						return "AMD (" + std::to_string(m_properties.vendorID) + ")";

					case 0x1010 :
						return "ImgTec (" + std::to_string(m_properties.vendorID) + ")";

					case 0x10DE :
						return "Nvidia (" + std::to_string(m_properties.vendorID) + ")";

					case 0x13B5 :
						return "ARM (" + std::to_string(m_properties.vendorID) + ")";

					case 0x5143 :
						return "Qualcomm (" + std::to_string(m_properties.vendorID) + ")";

					case 0x8086 :
						return "Intel (" + std::to_string(m_properties.vendorID) + ")";

					default :
						return std::to_string(m_properties.vendorID);
				}
				// NOLINTEND(*-magic-numbers)
			}

			/**
			 * @brief Returns the device ID as a string.
			 * @note Shortcut to PhysicalDevice::properties().
			 * @return std::string
			 */
			[[nodiscard]]
			inline
			std::string
			deviceId () const noexcept
			{
				return std::to_string(m_properties.deviceID);
			}

			/**
			 * @brief Returns the pipeline cache UUID as a string.
			 * @note Shortcut to PhysicalDevice::properties().
			 * @return std::string
			 */
			[[nodiscard]]
			inline
			std::string
			pipelineCacheUUID () const noexcept
			{
				return PhysicalDevice::UUIDToString(m_properties.pipelineCacheUUID);
			}

			/**
			 * @brief Returns prefetched physical device memory properties.
			 * @return const VkPhysicalDeviceMemoryProperties &
			 */
			[[nodiscard]]
			const VkPhysicalDeviceMemoryProperties & memoryProperties () const noexcept;

			/**
			 * @brief Returns prefetched physical device queue family properties.
			 * @return const std::vector< VkQueueFamilyProperties > &
			 */
			[[nodiscard]]
			const std::vector< VkQueueFamilyProperties > & queueFamilyProperties () const noexcept;

			/**
			 * @brief Returns the index of the family queue type from the physical device.
			 * @param type The type of the family queue.
			 * @return uint32_t
			 */
			[[nodiscard]]
			std::optional< uint32_t > getFamilyQueueIndex (VkQueueFlagBits type) noexcept;

			/**
			 * @brief Returns prefetched physical device tool properties.
			 * @return const std::vector< VkPhysicalDeviceToolProperties > &
			 */
			[[nodiscard]]
			const std::vector< VkPhysicalDeviceToolProperties > & toolProperties () const noexcept;

			/**
			 * @brief Returns prefetched physical device display properties.
			 * @return const std::vector< VkDisplayPropertiesKHR > &
			 */
			[[nodiscard]]
			const std::vector< VkDisplayPropertiesKHR > & displayProperties () const noexcept;

			/**
			 * @brief Returns prefetched physical device display plane properties.
			 * @return const std::vector< VkDisplayPlanePropertiesKHR > &
			 */
			[[nodiscard]]
			const std::vector< VkDisplayPlanePropertiesKHR > & displayPlaneProperties () const noexcept;

			/**
			 * @brief Returns prefetched physical device fragment shading rates.
			 * @return const std::vector< VkDisplayPlanePropertiesKHR > &
			 */
			[[nodiscard]]
			const std::vector< VkPhysicalDeviceFragmentShadingRateKHR > & fragmentShadingRates () const noexcept;

			/**
			 * @brief Returns prefetched physical device time domains.
			 * @return const std::vector< VkTimeDomainEXT > &
			 */
			[[nodiscard]]
			const std::vector< VkTimeDomainEXT > & timeDomains () const noexcept;

			/**
			 * @brief Returns prefetched physical device framebuffer mixed samples combinations.
			 * @return const std::vector< VkTimeDomainEXT > &
			 */
			[[nodiscard]]
			const std::vector< VkFramebufferMixedSamplesCombinationNV > & framebufferMixedSamplesCombinations () const noexcept;

			/**
			 * @brief Returns the physical device format properties.
			 * @param format
			 * @return VkFormatProperties
			 */
			[[nodiscard]]
			VkFormatProperties getFormatProperties (VkFormat format) const noexcept;

			/**
			 * @brief Returns the physical device image format properties.
			 * @param format
			 * @param type
			 * @param tiling
			 * @param usage
			 * @param flags
			 * @return VkImageFormatProperties
			 */
			[[nodiscard]]
			VkImageFormatProperties getImageFormatProperties (VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags) const noexcept;

			/**
			 * @brief Returns the physical device sparse image format properties.
			 * @param format
			 * @param type
			 * @param tiling
			 * @param usage
			 * @param samples
			 * @return std::vector< VkSparseImageFormatProperties >
			 */
			[[nodiscard]]
			std::vector< VkSparseImageFormatProperties > getSparseImageFormatProperties (VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkSampleCountFlagBits samples) const noexcept;

			/**
			 * @brief Returns the physical device external image format properties.
			 * @param format
			 * @param type
			 * @param tiling
			 * @param usage
			 * @param flags
			 * @param externalHandleType
			 * @return VkExternalImageFormatPropertiesNV
			 */
			[[nodiscard]]
			VkExternalImageFormatPropertiesNV getExternalFormatProperties (VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType) const noexcept;

			/**
			 * @brief Returns the physical device external buffer properties.
			 * @param pExternalBufferInfo
			 * @return VkExternalBufferProperties
			 */
			[[nodiscard]]
			VkExternalBufferProperties getExternalBufferProperties (const VkPhysicalDeviceExternalBufferInfo * pExternalBufferInfo) const noexcept;

			/**
			 * @brief Returns the physical device external fence properties.
			 * @param pExternalFenceInfo
			 * @return VkExternalFenceProperties
			 */
			[[nodiscard]]
			VkExternalFenceProperties getExternalFenceProperties (const VkPhysicalDeviceExternalFenceInfo * pExternalFenceInfo) const noexcept;

			/**
			 * @brief Returns the physical device external semaphore properties.
			 * @param pExternalSemaphoreInfo
			 * @return VkExternalSemaphoreProperties
			 */
			[[nodiscard]]
			VkExternalSemaphoreProperties getExternalSemaphoreProperties (const VkPhysicalDeviceExternalSemaphoreInfo * pExternalSemaphoreInfo) const noexcept;

			/**
			 * @brief Returns the physical device surface support.
			 * @param surface
			 * @param queueFamilyIndex
			 * @return bool
			 */
			[[nodiscard]]
			bool getSurfaceSupport (VkSurfaceKHR surface, uint32_t queueFamilyIndex) const noexcept;

			/**
			 * @brief Returns the physical device surface capabilities.
			 * @param surface
			 * @return VkSurfaceCapabilitiesKHR
			 */
			[[nodiscard]]
			VkSurfaceCapabilitiesKHR getSurfaceCapabilities (VkSurfaceKHR surface) const noexcept;

			/**
			 * @brief Returns the physical device surface formats.
			 * @param surface
			 * @return std::vector< VkSurfaceFormatKHR >
			 */
			[[nodiscard]]
			std::vector< VkSurfaceFormatKHR > getSurfaceFormats (VkSurfaceKHR surface) const noexcept;

			/**
			 * @brief Returns the physical device surface present modes.
			 * @param surface
			 * @return std::vector< VkPresentModeKHR >
			 */
			[[nodiscard]]
			std::vector< VkPresentModeKHR > getSurfacePresentModes (VkSurfaceKHR surface) const noexcept;

			/**
			 * @brief Returns the physical device present rectangles.
			 * @param surface
			 * @return std::vector< VkRect2D >
			 */
			[[nodiscard]]
			std::vector< VkRect2D > getPresentRectangles (VkSurfaceKHR surface) const noexcept;

			/**
			 * @brief Returns the physical device queue family performance query passes.
			 * @param pPerformanceQueryCreateInfos
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t getQueueFamilyPerformanceQueryPasses (const VkQueryPoolPerformanceCreateInfoKHR * pPerformanceQueryCreateInfos) const noexcept;

			/**
			 * @brief Returns the physical device multisample properties.
			 * @param samples
			 * @return VkMultisamplePropertiesEXT
			 */
			[[nodiscard]]
			VkMultisamplePropertiesEXT getMultisampleProperties (VkSampleCountFlagBits samples) const noexcept;

			/**
			 * @brief Returns a list of validation layers available from physical device.
			 * @return std::vector< VkLayerProperties >
			 */
			[[deprecated("Vulkan has deprecated the device layer for instance layer only.")]]
			[[nodiscard]]
			std::vector< VkLayerProperties > getValidationLayers () const noexcept;

			/**
			 * @brief Returns a list of extensions available from physical device.
			 * @param pLayerName Default nullptr.
			 * @return std::vector< VkExtensionProperties >
			 */
			[[nodiscard]]
			std::vector< VkExtensionProperties > getExtensions (const char * pLayerName = nullptr) const noexcept;

			/**
			 * @brief Returns printable information about the physical device.
			 * @return std::string
			 */
			[[nodiscard]]
			std::string getPhysicalDeviceInformation () const noexcept;

			/**
			 * @brief Returns the total queue the device can handle.
			 * @note This is mainly to have a raw score from the device for selection.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t getTotalQueueCount () const noexcept;

			/**
			 * @brief Converts UUID from vulkan to a printable string.
			 * @param uuid A point to uuid structure.
			 * @return string
			 */
			[[nodiscard]]
			static std::string UUIDToString (const uint8_t uuid[]) noexcept;

		private:

			VkPhysicalDevice m_physicalDevice;
			VkPhysicalDeviceFeatures m_features{};
			VkPhysicalDeviceProperties m_properties{};
			VkPhysicalDeviceMemoryProperties m_memoryProperties{};
			std::vector< VkQueueFamilyProperties > m_queueFamilyProperties{};
			std::vector< VkPhysicalDeviceToolProperties > m_toolProperties{};
			std::vector< VkDisplayPropertiesKHR > m_displayProperties{};
			std::vector< VkDisplayPlanePropertiesKHR > m_displayPlaneProperties{};
			std::vector< VkPhysicalDeviceFragmentShadingRateKHR > m_fragmentShadingRates{};
			std::vector< VkTimeDomainEXT > m_timeDomains{};
			std::vector< VkFramebufferMixedSamplesCombinationNV > m_framebufferMixedSamplesCombinations{};
	};
}
