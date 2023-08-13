/*
 * Emeraude/Vulkan/PhysicalDevice.cpp
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

#include "PhysicalDevice.hpp"

/* C/C++ standard libraries */
#include <iomanip> // std::setfill, std::setw
#include <sstream>

/* Local inclusions */
#include "String.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	PhysicalDevice::PhysicalDevice (const VkPhysicalDevice & physicalDevice) noexcept
		: m_physicalDevice(physicalDevice)
	{
		vkGetPhysicalDeviceFeatures(m_physicalDevice, &m_features);

		vkGetPhysicalDeviceProperties(m_physicalDevice, &m_properties);

		vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &m_memoryProperties);

		{
			uint32_t count = 0;

			vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &count, nullptr);

			if ( count > 0 )
			{
				m_queueFamilyProperties.resize(count);

				vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice, &count, m_queueFamilyProperties.data());
			}
		}

		/*{
			count = 0;

			result = vkGetPhysicalDeviceToolProperties(m_physicalDevice, &count, nullptr);

			if ( result == VK_SUCCESS )
			{
				if ( count > 0 )
				{
					m_toolProperties.resize(count);

					result = vkGetPhysicalDeviceToolProperties(m_physicalDevice, &count, m_toolProperties.data());

					if ( result != VK_SUCCESS )
						TraceError{ClassId} << "Unable to get tool properties : " << vkResultToCString(result) << " !";
				}
			}
			else
			{
				TraceError{ClassId} << "Unable to get tool property count : " << vkResultToCString(result) << " !";
			}
		}*/

		/*{
			count = 0;

			result = vkGetPhysicalDeviceDisplayPropertiesKHR(m_physicalDevice, &count, nullptr);

			if ( result == VK_SUCCESS )
			{
				if ( count > 0 )
				{
					m_displayProperties.resize(count);

					result = vkGetPhysicalDeviceDisplayPropertiesKHR(m_physicalDevice, &count, m_displayProperties.data());

					if ( result != VK_SUCCESS )
						TraceError{ClassId} << "Unable to get display properties : " << vkResultToCString(result) << " !";
				}
			}
			else
			{
				TraceError{ClassId} << "Unable to get display property count : " << vkResultToCString(result) << " !";
			}
		}*/

		/*{
			count = 0;

			result = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(m_physicalDevice, &count, nullptr);

			if ( result == VK_SUCCESS )
			{
				if ( count > 0 )
				{
					m_displayPlaneProperties.resize(count);

					result = vkGetPhysicalDeviceDisplayPlanePropertiesKHR(m_physicalDevice, &count, m_displayPlaneProperties.data());

					if ( result != VK_SUCCESS )
						TraceError{ClassId} << "Unable to get display plane properties : " << vkResultToCString(result) << " !";
				}
			}
			else
			{
				TraceError{ClassId} << "Unable to get display plane property count : " << vkResultToCString(result) << " !";
			}
		}*/

		/*{
			count = 0;

			result = vkGetPhysicalDeviceFragmentShadingRatesKHR(m_physicalDevice, &count, nullptr);

			if ( result == VK_SUCCESS )
			{
				if ( count > 0 )
				{
					m_fragmentShadingRates.resize(count);

					result = vkGetPhysicalDeviceFragmentShadingRatesKHR(m_physicalDevice, &count, m_fragmentShadingRates.data());

					if ( result != VK_SUCCESS )
						TraceError{ClassId} << "Unable to get fragment shading rates : " << vkResultToCString(result) << " !";
				}
			}
			else
			{
				TraceError{ClassId} << "Unable to get fragment shading rate count : " << vkResultToCString(result) << " !";
			}
		}*/

		/*{
			count = 0;

			result = vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(m_physicalDevice, &count, nullptr);

			if ( result == VK_SUCCESS )
			{
				if ( count > 0 )
				{
					m_timeDomains.resize(count);

					result = vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(m_physicalDevice, &count, m_timeDomains.data());

					if ( result != VK_SUCCESS )
						TraceError{ClassId} << "Unable to get time domains : " << vkResultToCString(result) << " !";
				}
			}
			else
			{
				TraceError{ClassId} << "Unable to get time domain count : " << vkResultToCString(result) << " !";
			}
		}*/

		/*{
			count = 0;

			result = vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(m_physicalDevice, &count, nullptr);

			if ( result == VK_SUCCESS )
			{
				if ( count > 0 )
				{
					m_framebufferMixedSamplesCombinations.resize(count);

					result = vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(m_physicalDevice, &count, m_framebufferMixedSamplesCombinations.data());

					if ( result != VK_SUCCESS )
						TraceError{ClassId} << "Unable to get framebuffer mixed samples combinations : " << vkResultToCString(result) << " !";
				}
			}
			else
			{
				TraceError{ClassId} << "Unable to get framebuffer mixed samples combination count : " << vkResultToCString(result) << " !";
			}
		}*/
	}

	const VkPhysicalDevice &
	PhysicalDevice::handle () const noexcept
	{
		return m_physicalDevice;
	}

	const VkPhysicalDeviceFeatures &
	PhysicalDevice::features () const noexcept
	{
		return m_features;
	}

	const VkPhysicalDeviceProperties &
	PhysicalDevice::properties () const noexcept
	{
		return m_properties;
	}

	const VkPhysicalDeviceMemoryProperties &
	PhysicalDevice::memoryProperties () const noexcept
	{
		return m_memoryProperties;
	}

	const std::vector< VkQueueFamilyProperties > &
	PhysicalDevice::queueFamilyProperties () const noexcept
	{
		return m_queueFamilyProperties;
	}

	std::optional< uint32_t >
	PhysicalDevice::getFamilyQueueIndex (VkQueueFlagBits type) noexcept
	{
		if ( m_queueFamilyProperties.empty() )
		{
			TraceError{ClassId} << "The physical device " << m_physicalDevice << " has no family queue !";

			return {};
		}

		for ( auto it = m_queueFamilyProperties.cbegin(); it != m_queueFamilyProperties.cend(); ++it )
		{
			auto index = std::distance(m_queueFamilyProperties.cbegin(), it);

			if ( m_queueFamilyProperties[index].queueFlags & type )
			{
				return index;
			}
		}

		TraceError{ClassId} << "The physical device " << m_physicalDevice << " don't have this family queue type (" << type << ") !";

		return {};
	}

	const std::vector< VkPhysicalDeviceToolProperties > &
	PhysicalDevice::toolProperties() const noexcept
	{
		return m_toolProperties;
	}

	const std::vector< VkDisplayPropertiesKHR > &
	PhysicalDevice::displayProperties () const noexcept
	{
		return m_displayProperties;
	}

	const std::vector< VkDisplayPlanePropertiesKHR > &
	PhysicalDevice::displayPlaneProperties () const noexcept
	{
		return m_displayPlaneProperties;
	}

	const std::vector< VkPhysicalDeviceFragmentShadingRateKHR > &
	PhysicalDevice::fragmentShadingRates () const noexcept
	{
		return m_fragmentShadingRates;
	}

	const std::vector< VkTimeDomainEXT > &
	PhysicalDevice::timeDomains () const noexcept
	{
		return m_timeDomains;
	}

	const std::vector< VkFramebufferMixedSamplesCombinationNV > &
	PhysicalDevice::framebufferMixedSamplesCombinations () const noexcept
	{
		return m_framebufferMixedSamplesCombinations;
	}

	VkFormatProperties
	PhysicalDevice::getFormatProperties (VkFormat format) const noexcept
	{
		VkFormatProperties formatProperties{};

		vkGetPhysicalDeviceFormatProperties(m_physicalDevice, format, &formatProperties);

		return formatProperties;
	}

	VkImageFormatProperties
	PhysicalDevice::getImageFormatProperties (VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags) const noexcept
	{
		VkImageFormatProperties imageFormatProperties{};

		auto result = vkGetPhysicalDeviceImageFormatProperties(m_physicalDevice, format, type, tiling, usage, flags, &imageFormatProperties);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to get image format properties : " << vkResultToCString(result) << " !";
		}

		return imageFormatProperties;
	}

	std::vector< VkSparseImageFormatProperties >
	PhysicalDevice::getSparseImageFormatProperties (VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkSampleCountFlagBits samples) const noexcept
	{
		uint32_t count = 0;

		vkGetPhysicalDeviceSparseImageFormatProperties(m_physicalDevice, format, type, samples, usage, tiling, &count, nullptr);

		std::vector< VkSparseImageFormatProperties > sparseImageFormatProperties{};

		if ( count > 0 )
		{
			sparseImageFormatProperties.resize(count);

			vkGetPhysicalDeviceSparseImageFormatProperties(m_physicalDevice, format, type, samples, usage, tiling, &count, sparseImageFormatProperties.data());
		}

		return sparseImageFormatProperties;
	}

	VkExternalImageFormatPropertiesNV
	PhysicalDevice::getExternalFormatProperties (VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType) const noexcept
	{
		VkExternalImageFormatPropertiesNV externalImageFormatProperties{};

		/*auto result = vkGetPhysicalDeviceExternalImageFormatPropertiesNV(m_physicalDevice, format, type, tiling, usage, flags, externalHandleType, &externalImageFormatProperties);

		if ( result != VK_SUCCESS )
			TraceError{ClassId} << "Unable to get external image format properties : " << vkResultToCString(result) << " !");*/

		return externalImageFormatProperties;
	}

	VkExternalBufferProperties
	PhysicalDevice::getExternalBufferProperties (const VkPhysicalDeviceExternalBufferInfo * pExternalBufferInfo) const noexcept
	{
		VkExternalBufferProperties externalBufferProperties{};

		vkGetPhysicalDeviceExternalBufferProperties(m_physicalDevice, pExternalBufferInfo, &externalBufferProperties);

		return externalBufferProperties;
	}

	VkExternalFenceProperties
	PhysicalDevice::getExternalFenceProperties (const VkPhysicalDeviceExternalFenceInfo * pExternalFenceInfo) const noexcept
	{
		VkExternalFenceProperties externalFenceProperties{};

		vkGetPhysicalDeviceExternalFenceProperties(m_physicalDevice, pExternalFenceInfo, &externalFenceProperties);

		return externalFenceProperties;
	}

	VkExternalSemaphoreProperties
	PhysicalDevice::getExternalSemaphoreProperties (const VkPhysicalDeviceExternalSemaphoreInfo * pExternalSemaphoreInfo) const noexcept
	{
		VkExternalSemaphoreProperties externalSemaphoreProperties{};

		vkGetPhysicalDeviceExternalSemaphoreProperties(m_physicalDevice, pExternalSemaphoreInfo, &externalSemaphoreProperties);

		return externalSemaphoreProperties;
	}

	bool
	PhysicalDevice::getSurfaceSupport (VkSurfaceKHR surface, uint32_t queueFamilyIndex) const noexcept
	{
		VkBool32 supported = VK_FALSE;

		auto result = vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice, queueFamilyIndex, surface, &supported);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to get surface support : " << vkResultToCString(result) << " !";
		}

		return supported != 0;
	}

	VkSurfaceCapabilitiesKHR
	PhysicalDevice::getSurfaceCapabilities (VkSurfaceKHR surface) const noexcept
	{
		VkSurfaceCapabilitiesKHR surfaceCapabilities{};

		auto result = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(m_physicalDevice, surface, &surfaceCapabilities);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to get surface capabilities : " << vkResultToCString(result) << " !";
		}

		return surfaceCapabilities;
	}

	std::vector< VkSurfaceFormatKHR >
	PhysicalDevice::getSurfaceFormats (VkSurfaceKHR surface) const noexcept
	{
		std::vector< VkSurfaceFormatKHR > surfaceFormats{};

		uint32_t count = 0;

		auto result = vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, surface, &count, nullptr);

		if ( result == VK_SUCCESS )
		{
			if ( count > 0 )
			{
				surfaceFormats.resize(count);

				result = vkGetPhysicalDeviceSurfaceFormatsKHR(m_physicalDevice, surface, &count, surfaceFormats.data());

				if ( result != VK_SUCCESS )
					TraceError{ClassId} << "Unable to get surface formats : " << vkResultToCString(result) << " !";
			}
		}
		else
		{
			TraceError{ClassId} << "Unable to get surface format count : " << vkResultToCString(result) << " !";
		}

		return surfaceFormats;
	}

	std::vector< VkPresentModeKHR >
	PhysicalDevice::getSurfacePresentModes (VkSurfaceKHR surface) const noexcept
	{
		std::vector< VkPresentModeKHR > presentModes{};

		uint32_t count = 0;

		auto result = vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, surface, &count, nullptr);

		if ( result == VK_SUCCESS )
		{
			if ( count > 0 )
			{
				presentModes.resize(count);

				result = vkGetPhysicalDeviceSurfacePresentModesKHR(m_physicalDevice, surface, &count, presentModes.data());

				if ( result != VK_SUCCESS )
					TraceError{ClassId} << "Unable to get present modes : " << vkResultToCString(result) << " !";
			}
		}
		else
		{
			TraceError{ClassId} << "Unable to get present mode count : " << vkResultToCString(result) << " !";
		}

		return presentModes;
	}

	std::vector< VkRect2D >
	PhysicalDevice::getPresentRectangles (VkSurfaceKHR surface) const noexcept
	{
		std::vector< VkRect2D > presentRectangles{};

		uint32_t count = 0;

		auto result = vkGetPhysicalDevicePresentRectanglesKHR(m_physicalDevice, surface, &count, nullptr);

		if ( result == VK_SUCCESS )
		{
			if ( count > 0 )
			{
				presentRectangles.resize(count);

				result = vkGetPhysicalDevicePresentRectanglesKHR(m_physicalDevice, surface, &count, presentRectangles.data());

				if ( result != VK_SUCCESS )
					TraceError{ClassId} << "Unable to get present rectangles : " << vkResultToCString(result) << " !";
			}
		}
		else
		{
			TraceError{ClassId} << "Unable to get present rectangle count : " << vkResultToCString(result) << " !";
		}

		return presentRectangles;
	}

	uint32_t
	PhysicalDevice::getQueueFamilyPerformanceQueryPasses (const VkQueryPoolPerformanceCreateInfoKHR * pPerformanceQueryCreateInfos) const noexcept
	{
		uint32_t numPasses = 0;

		//vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(m_physicalDevice, pPerformanceQueryCreateInfos, &numPasses);

		return numPasses;
	}

	VkMultisamplePropertiesEXT
	PhysicalDevice::getMultisampleProperties (VkSampleCountFlagBits samples) const noexcept
	{
		VkMultisamplePropertiesEXT multisampleProperties{};

		//vkGetPhysicalDeviceMultisamplePropertiesEXT(m_physicalDevice, samples, &multisampleProperties);

		return multisampleProperties;
	}

	std::vector< VkLayerProperties >
	PhysicalDevice::getValidationLayers () const noexcept
	{
		std::vector< VkLayerProperties > validationLayers{};

		uint32_t count = 0;

		auto result = vkEnumerateDeviceLayerProperties(m_physicalDevice, &count, nullptr);

		if ( result == VK_SUCCESS )
		{
			if ( count > 0 )
			{
				validationLayers.resize(count);

				result = vkEnumerateDeviceLayerProperties(m_physicalDevice, &count, validationLayers.data());

				if ( result != VK_SUCCESS )
					TraceError{ClassId} << "Unable to get device validation layers : " << vkResultToCString(result) << " !";
			}
		}
		else
		{
			TraceError{ClassId} << "Unable to get device validation layer count : " << vkResultToCString(result) << " !";
		}

		return validationLayers;
	}

	std::vector< VkExtensionProperties >
	PhysicalDevice::getExtensions (const char * pLayerName) const noexcept
	{
		std::vector< VkExtensionProperties > extensions{};

		uint32_t count = 0;

		auto result = vkEnumerateDeviceExtensionProperties(m_physicalDevice, pLayerName, &count, nullptr);

		if ( result == VK_SUCCESS )
		{
			if ( count > 0 )
			{
				extensions.resize(count);

				result = vkEnumerateDeviceExtensionProperties(m_physicalDevice, pLayerName, &count, extensions.data());

				if ( result != VK_SUCCESS )
					TraceError{ClassId} << "Unable to get device extensions : " << vkResultToCString(result) << " !";
			}
		}
		else
		{
			TraceError{ClassId} << "Unable to get device extension count : " << vkResultToCString(result) << " !";
		}

		return extensions;
	}

	std::string
	PhysicalDevice::getPhysicalDeviceInformation () const noexcept
	{
		std::stringstream ss{};

		ss <<
			this->deviceType() << " '" << this->deviceName() << "' : \n"
			" - API driver : " << this->APIDriverString() << "\n"
			" - Driver version : " << this->DriverVersionString() << "\n"
			" - Vendor ID : " << this->vendorId() << "\n"
			" - Device ID : " << this->deviceId() << "\n"
			" - Pipeline cache UUID : " << this->pipelineCacheUUID() << "\n";

		/* Checks queue family properties. */
		if ( !m_queueFamilyProperties.empty() )
		{
			ss << " - Queue family count : " << m_queueFamilyProperties.size() << "\n";

			for ( size_t index = 0; index < m_queueFamilyProperties.size(); index++ )
			{
				const auto & familyQueue = m_queueFamilyProperties[index];

				std::vector< std::string > flags{};

				if ( familyQueue.queueFlags & VK_QUEUE_GRAPHICS_BIT )
					flags.emplace_back("Graphics");

				if ( familyQueue.queueFlags & VK_QUEUE_COMPUTE_BIT )
					flags.emplace_back("Compute");

				if ( familyQueue.queueFlags & VK_QUEUE_TRANSFER_BIT )
					flags.emplace_back("Transfer");

				if ( familyQueue.queueFlags & VK_QUEUE_SPARSE_BINDING_BIT )
					flags.emplace_back("SparseBinding");

				if ( familyQueue.queueFlags & VK_QUEUE_PROTECTED_BIT )
					flags.emplace_back("Protected");

				if ( familyQueue.queueFlags & VK_QUEUE_VIDEO_DECODE_BIT_KHR )
					flags.emplace_back("VideoDecode");

#ifdef VK_ENABLE_BETA_EXTENSIONS
				if ( familyQueue.queueFlags & VK_QUEUE_VIDEO_ENCODE_BIT_KHR )
					flags.emplace_back("VideoEncode");
#endif

				/* Optical flow are fundamental algorithms in computer vision (CV) area.
				 * This extension allows applications to estimate 2D displacement of pixels between two frames.
				 * For use with : NVIDIA Optical Flow SDK Version 5 */
				if ( familyQueue.queueFlags & VK_QUEUE_OPTICAL_FLOW_BIT_NV )
					flags.emplace_back("OpticalFlow");

				ss << "\t#" << index << " supports " << familyQueue.queueCount << "x {" << String::implode(flags, " | ") << "}";

				/* Additional info */
				ss << " timestampValidBits: " << familyQueue.timestampValidBits << ", minImageTransferGranularity(" << familyQueue.minImageTransferGranularity.width << ", " << familyQueue.minImageTransferGranularity.height << ", " << familyQueue.minImageTransferGranularity.depth << ")" "\n";
			}
		}
		else
		{
			ss << " - Queue family count : None !" "\n";
		}

		return ss.str();
	}

	size_t
	PhysicalDevice::getTotalQueueCount () const noexcept
	{
		if ( m_queueFamilyProperties.empty() )
			return 0;

		size_t queueCount = 0;

		for ( size_t index = 0; index < m_queueFamilyProperties.size(); index++ )
			queueCount += m_queueFamilyProperties[index].queueCount;

		return queueCount;
	}

	std::string
	PhysicalDevice::UUIDToString (const uint8_t uuid[]) noexcept
	{
		std::stringstream ss;

		for ( size_t index = 0; index < VK_UUID_SIZE; ++index )
		{
			ss << std::setfill('0') << std::setw(2) << std::hex << static_cast< uint32_t >(uuid[index]);

			switch ( index )
			{
				case 3 :
				case 7 :
				case 11 :
					ss << '-';
					break;
			}
		}

		return ss.str();
	}
}
