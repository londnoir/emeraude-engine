/*
 * Emeraude/Vulkan/Instance.cpp
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

#include "Instance.hpp"

/* C/C++ standard libraries */
#include <algorithm>
#include <map>
#include <sstream>

/* Local inclusions */
#include "Core.hpp" // FIXME: Remove this (Access to engine info)
#include "Arguments.hpp"
#include "Settings.hpp"
#include "Window.hpp"
#include "Utility.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;

	const size_t Instance::ClassUID{Observable::getClassUID()};

	Instance::Instance (const Arguments & arguments, Settings & coreSettings) noexcept
		: ServiceInterface(ClassId), m_arguments(arguments), m_coreSettings(coreSettings)
	{

	}

	bool
	Instance::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Instance::usable () const noexcept
	{
		return m_instance != nullptr;
	}

	VkInstance
	Instance::handle () const noexcept
	{
		return m_instance;
	}

	const std::vector< std::shared_ptr< PhysicalDevice > > &
	Instance::physicalDevices () const noexcept
	{
		return m_physicalDevices;
	}

	const std::vector< std::shared_ptr< Device > > &
	Instance::devices () const noexcept
	{
		return m_devices;
	}

	bool
	Instance::isDebugModeEnabled () const noexcept
	{
		return m_flags[DebugMode];
	}

	void
	Instance::enableDebugMode (bool state) noexcept
	{
		m_flags[DebugMode] = state;
	}

	void
	Instance::readSettings () noexcept
	{
		/* Instance verbose mode */
		m_flags[DebugMode] = m_coreSettings.getAs< bool >(EnableInstanceDebugKey, BOOLEAN_FOLLOWING_DEBUG);

		/* Enable the vulkan validation layer system. */
		m_flags[ValidationLayersEnabled] = m_coreSettings.getAs< bool >(ValidationLayersEnabledKey, BOOLEAN_FOLLOWING_DEBUG);

		/* NOTE: Only if the validation layer is enabled. */
		if ( m_flags[ValidationLayersEnabled] )
		{
			/* Enable the vulkan debug messenger. */
			m_flags[UseDebugMessenger] = m_coreSettings.getAs< bool >(UseDebugMessengerKey, true);

			if ( m_flags[UseDebugMessenger] )
				m_debugCreateInfo = DebugMessenger::getCreateInfo();
		}
	}

	bool
	Instance::onInitialize () noexcept
	{
		const auto core = Core::instance();

		this->readSettings();

		this->setRequiredValidationLayers();

		this->setRequiredExtensions();

		/* Vulkan instance creation */
		{
			m_applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
			m_applicationInfo.pNext = nullptr;
			m_applicationInfo.pApplicationName = core->applicationFullIdentification().c_str();
			m_applicationInfo.applicationVersion = VK_MAKE_VERSION(core->applicationVersion().major(), core->applicationVersion().minor(), core->applicationVersion().revision());
			m_applicationInfo.pEngineName = Core::LibraryName;
			m_applicationInfo.engineVersion = VK_MAKE_VERSION(Core::LibraryVersion.major(), Core::LibraryVersion.minor(), Core::LibraryVersion.revision());
			m_applicationInfo.apiVersion = VK_API_VERSION_1_3;

			m_createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
			m_createInfo.pNext = m_flags[UseDebugMessenger] ? &m_debugCreateInfo : nullptr;
			m_createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
			m_createInfo.pApplicationInfo = &m_applicationInfo;
			m_createInfo.enabledLayerCount = static_cast< uint32_t >(m_requiredValidationLayers.size());
			m_createInfo.ppEnabledLayerNames = m_requiredValidationLayers.data();
			m_createInfo.enabledExtensionCount = static_cast< uint32_t >(m_requiredExtensions.size());
			m_createInfo.ppEnabledExtensionNames = m_requiredExtensions.data();

			/* At this point, we create the vulkan instance.
			 * Beyond this point Vulkan is in the pipe and usable. */
			const auto result = vkCreateInstance(&m_createInfo, nullptr, &m_instance);

			if ( result != VK_SUCCESS )
			{
				TraceFatal{ClassId} << "Unable to create a Vulkan instance : " << vkResultToCString(result) << " !";

				return false;
			}
		}

		/* NOTE: When debugging, we want to re-route the validation layer messages to the engine tracer. */
		if ( m_flags[UseDebugMessenger] )
		{
			m_debugMessenger = std::make_unique< DebugMessenger >(*this);
			m_debugMessenger->setIdentifier("VulkanInstance-Main-DebugMessenger");

			if ( !m_debugMessenger->isCreated() )
				Tracer::warning(ClassId, "Unable to activate the validation layers debug messenger !");
		}

		/* Probe all usable physical devices. */
		{
			const auto & physicalDeviceList = this->getPhysicalDevices();

			if ( physicalDeviceList.empty() )
			{
				TraceFatal{ClassId} << "No physical device available !";

				return false;
			}

			m_physicalDevices.reserve(physicalDeviceList.size());

			std::transform(physicalDeviceList.cbegin(), physicalDeviceList.cend(), std::back_inserter(m_physicalDevices), [] (const auto & physicalDevice) {
				return std::make_shared< PhysicalDevice >(physicalDevice);
			});
		}

		return true;
	}

	bool
	Instance::onTerminate () noexcept
	{
		/* Checking device usage to print out some closing resources bugs. */
		for ( const auto & device : m_devices )
		{
			device->destroy();

			size_t useCount = device.use_count();

			if ( useCount > 1 )
				TraceError{ClassId} << "The Vulkan device '" << device->identifier() << "' smart pointer still have " << useCount << " uses !";
		}

		m_devices.clear();
		m_physicalDevices.clear();
		m_debugMessenger.reset();

		if ( m_instance != VK_NULL_HANDLE )
		{
			vkDestroyInstance(m_instance, nullptr);

			m_instance = VK_NULL_HANDLE;
		}

		m_requestedValidationLayers.clear();
		m_requiredValidationLayers.clear();
		m_requiredExtensions.clear();

		return true;
	}

	std::vector< VkPhysicalDevice >
	Instance::getPhysicalDevices () const noexcept
	{
		std::vector< VkPhysicalDevice > output{};

		uint32_t count = 0;

		auto result = vkEnumeratePhysicalDevices(m_instance, &count, nullptr);

		if ( result == VK_SUCCESS )
		{
			if ( count > 0 )
			{
				output.resize(count);

				result = vkEnumeratePhysicalDevices(m_instance, &count, output.data());

				if ( result != VK_SUCCESS )
					TraceError{ClassId} << "Unable to get physical devices : " << vkResultToCString(result) << " !";
			}
		}
		else
		{
			TraceError{ClassId} << "Unable to get physical device count : " << vkResultToCString(result) << " !";
		}

		return output;
	}

	void
	Instance::setRequiredValidationLayers () noexcept
	{
		if ( !m_flags[ValidationLayersEnabled] )
			return;

		const auto availableValidationLayers = Instance::getValidationLayers();

		/* NOTE: Show available validation layers on the current system. */
		if ( m_coreSettings.getAs< bool >(ShowAvailableValidationLayersKey, BOOLEAN_FOLLOWING_DEBUG) )
			printItemList(availableValidationLayers);

		/* Read the settings to get a dynamic list of validation layers. */
		if ( m_coreSettings.isArrayEmpty(ValidationLayersRequestedKey) )
		{
			TraceInfo{ClassId} <<
				"No validation layer requested in core settings ! Setting all validation layers available..." "\n"
				"NOTE: You can change the validation layers selected in core settings at the key : '" << ValidationLayersRequestedKey << "'.";

			for ( const auto & availableValidationLayer : availableValidationLayers )
			{
				m_coreSettings.setInArray(ValidationLayersRequestedKey, availableValidationLayer.layerName);
				m_requestedValidationLayers.emplace_back(availableValidationLayer.layerName);
			}
		}
		else
		{
			m_requestedValidationLayers = m_coreSettings.asStringList(ValidationLayersRequestedKey);

			if ( m_flags[DebugMode] )
			{
				TraceInfo trace{ClassId};

				trace << "Requested validation layers from settings :" "\n";

				for ( const auto & requestedValidationLayer : m_requestedValidationLayers )
					trace << "\t" << requestedValidationLayer << "\n";
			}
		}

		m_requiredValidationLayers = Instance::getSupportedValidationLayers(m_requestedValidationLayers, availableValidationLayers);

		if ( m_flags[DebugMode] )
		{
			if ( m_requiredValidationLayers.empty() )
			{
				Tracer::warning(ClassId, "None of the validation layers requested are available on this system ! Check your Vulkan setup.");
			}
			else
			{
				TraceInfo trace{ClassId};

				trace << "Final validation layers selection :" "\n";

				for ( const auto & requiredValidationLayer : m_requiredValidationLayers )
					trace << "\t" << requiredValidationLayer << "\n";
			}
		}
	}

	void
	Instance::setRequiredExtensions () noexcept
	{
		/* NOTE: Show available extensions on the current system. */
		if ( m_coreSettings.getAs< bool >(ShowAvailableInstanceExtensionsKey, BOOLEAN_FOLLOWING_DEBUG) )
			printItemList("Instance", Instance::getExtensions(nullptr));

		uint32_t glfwExtensionCount = 0;

		const auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		for ( uint32_t index = 0; index < glfwExtensionCount; index++ )
			m_requiredExtensions.emplace_back(glfwExtensions[index]);

		/* If debug mode enabled, push back debug utilities. */
		if ( m_flags[ValidationLayersEnabled] )
		{
			if ( m_flags[UseDebugMessenger] )
			{
				m_requiredExtensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
			}
			else
			{
				/* These are supersede by the debug utils extension.
				 * NOTE: This causes crashes when enabled with debug utils. */
				m_requiredExtensions.emplace_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
				m_requiredExtensions.emplace_back(VK_EXT_DEBUG_MARKER_EXTENSION_NAME);
			}
		}

		/* NOTE: This extension allows applications to control whether devices
		 * that expose the VK_KHR_portability_subset extension are included in
		 * the results of physical device enumeration. */
		m_requiredExtensions.emplace_back(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);

		/* NOTE: Video decoding extensions. (To test one day ...) */
		//m_requiredExtensions.emplace_back(VK_KHR_VIDEO_QUEUE_EXTENSION_NAME);
		//m_requiredExtensions.emplace_back(VK_KHR_VIDEO_DECODE_QUEUE_EXTENSION_NAME);
		//m_requiredExtensions.emplace_back(VK_KHR_VIDEO_DECODE_H265_EXTENSION_NAME);

		if ( m_flags[DebugMode] )
		{
			if ( m_requiredExtensions.empty() )
			{
				Tracer::info(ClassId, "No extension required !");
			}
			else
			{
				TraceInfo trace{ClassId};

				trace << "Required extensions :" "\n";

				for ( const auto & requiredExtension : m_requiredExtensions )
					trace << "\t" << requiredExtension << "\n";
			}
		}
	}

	std::vector< VkLayerProperties >
	Instance::getValidationLayers () noexcept
	{
		std::vector< VkLayerProperties > validationLayers{};

		uint32_t count = 0;

		auto result = vkEnumerateInstanceLayerProperties(&count, nullptr);

		if ( result == VK_SUCCESS )
		{
			if ( count > 0 )
			{
				validationLayers.resize(count);

				result = vkEnumerateInstanceLayerProperties(&count, validationLayers.data());

				if ( result != VK_SUCCESS )
					TraceError{ClassId} << "Unable to get instance validation layers : " << vkResultToCString(result) << " !";
			}
		}
		else
		{
			TraceError{ClassId} << "Unable to get instance validation layer count : " << vkResultToCString(result) << " !";
		}

		return validationLayers;
	}

	std::vector< VkExtensionProperties >
	Instance::getExtensions (const char * pLayerName) noexcept
	{
		std::vector< VkExtensionProperties > extensions{};

		uint32_t count = 0;

		auto result = vkEnumerateInstanceExtensionProperties(pLayerName, &count, nullptr);

		if ( result == VK_SUCCESS )
		{
			if ( count > 0 )
			{
				extensions.resize(count);

				result = vkEnumerateInstanceExtensionProperties(pLayerName, &count, extensions.data());

				if ( result != VK_SUCCESS )
					TraceError{ClassId} << "Unable to get instance extensions : " << vkResultToCString(result) << " !";
			}
		}
		else
		{
			TraceError{ClassId} << "Unable to get instance extension count : " << vkResultToCString(result) << " !";
		}

		return extensions;
	}

	VkFormat
	Instance::findColorFormat (const std::shared_ptr< Vulkan::Device > & device, uint32_t redBits, uint32_t greenBits, uint32_t blueBits, uint32_t alphaBits) noexcept
	{
		return device->findSupportedFormat(
			{
				VK_FORMAT_R8G8B8A8_SRGB
			},
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BIT
		);
	}

	VkFormat
	Instance::findDepthStencilFormat (const std::shared_ptr< Vulkan::Device > & device, uint32_t depthBits, uint32_t stencilBits) noexcept
	{
		std::vector< VkFormat > formats{};

		switch ( depthBits )
		{
			case 32U :
				if ( stencilBits == 0 )
					formats.emplace_back(VK_FORMAT_D32_SFLOAT);
				else
					formats.emplace_back(VK_FORMAT_D32_SFLOAT_S8_UINT);

				[[fallthrough]];

			case 24U :
				if ( stencilBits == 0 )
					formats.emplace_back(VK_FORMAT_X8_D24_UNORM_PACK32);
				else
					formats.emplace_back(VK_FORMAT_D24_UNORM_S8_UINT);

				[[fallthrough]];

			case 16U :
				if ( stencilBits == 0 )
					formats.emplace_back(VK_FORMAT_D16_UNORM);
				else
					formats.emplace_back(VK_FORMAT_D16_UNORM_S8_UINT);

				[[fallthrough]];

			case 0U :
				if ( stencilBits > 0 )
					formats.emplace_back(VK_FORMAT_S8_UINT);
				break;

			default:
				TraceError{ClassId} << "Unable to get a " << depthBits << "bits depth buffer !";

				return VK_FORMAT_UNDEFINED;
		}

		return device->findSupportedFormat(
			formats,
			VK_IMAGE_TILING_OPTIMAL,
			VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT
		);
	}

	VkSampleCountFlagBits
	Instance::findSampleCount (uint32_t samples) noexcept
	{
		switch ( samples )
		{
			case 1 :
				return VK_SAMPLE_COUNT_1_BIT;

			case 2 :
				return VK_SAMPLE_COUNT_2_BIT;

			case 4 :
				return VK_SAMPLE_COUNT_4_BIT;

			case 8 :
				return VK_SAMPLE_COUNT_8_BIT;

			case 16 :
				return VK_SAMPLE_COUNT_16_BIT;

			case 32 :
				return VK_SAMPLE_COUNT_32_BIT;

			case 64 :
				return VK_SAMPLE_COUNT_64_BIT;

			default :
				return VK_SAMPLE_COUNT_FLAG_BITS_MAX_ENUM;
		}
	}

	std::shared_ptr< Device >
	Instance::getGraphicsDevice (Window & window) noexcept
	{
		std::vector< const char * > requiredExtensions{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME/*,
			VK_KHR_SHARED_PRESENTABLE_IMAGE_EXTENSION_NAME*/
		};

		std::map< size_t, std::shared_ptr< PhysicalDevice > > scoredDevices{};

		for ( const auto & physicalDevice : m_physicalDevices )
		{
			size_t score = 0;

			TraceInfo{ClassId} << physicalDevice->getPhysicalDeviceInformation();

			if ( window.usable() )
			{
				window.surface()->update(physicalDevice);

				if ( !this->checkDeviceCompatibility(physicalDevice, RunningMode::Performance, window, score) )
					continue;
			}
			else
			{
				if ( !this->checkDeviceCompatibility(physicalDevice, RunningMode::Performance, VK_QUEUE_GRAPHICS_BIT, score) )
					continue;
			}

			if ( !this->checkDevicesFeaturesForGraphics(physicalDevice, score) )
				continue;

			if ( !this->checkDeviceForRequiredExtensions(physicalDevice, requiredExtensions, score) )
				continue;

			score += physicalDevice->getTotalQueueCount() * 100;

			TraceInfo(ClassId) << "Physical device '" << physicalDevice->properties().deviceName << "' reached a score of " << score << " !";

			scoredDevices.emplace(score, physicalDevice);
		}

		/* NOTE: Returns the device with the highest score. */
		if ( scoredDevices.empty() )
		{
			Tracer::error(ClassId, "There is no physical device compatible with Vulkan.");

			return {};
		}

		const auto & selectedPhysicalDevice = scoredDevices.rbegin()->second;

		/* NOTE: Logical device creation for graphics rendering and presentation. */
		TraceSuccess{ClassId} <<
			"Graphics capable physical device '" << selectedPhysicalDevice->properties().deviceName << "' selected ! "
			"Creating the logical graphics device ...";

		auto device = std::make_shared< Device >(selectedPhysicalDevice);
		device->setIdentifier((std::stringstream{} << "VulkanInstance-" << selectedPhysicalDevice->properties().deviceName << "(Graphics)-Device").str());

		/* Be sure the selected device is the one that update the surface. */
		window.surface()->update(device);

		DeviceRequirements requirements{DeviceJobHint::Graphics};
		requirements.features().fillModeNonSolid = VK_TRUE; // Required for wireframe mode !
		requirements.requireGraphicsQueues({1.0F}, {0.5F});
		requirements.requireTransferQueues({1.0F});
		requirements.requirePresentationQueues({1.0F}, window.surface()->handle(), false);

		if ( !device->create(requirements, requiredExtensions) )
			return {};

		m_devices.emplace_back(device);

		return device;
	}

	std::shared_ptr< Device >
	Instance::getComputeDevice () noexcept
	{
		std::vector< const char * > requiredExtensions{};

		std::map< size_t, std::shared_ptr< PhysicalDevice > > scoredDevices{};

		for ( const auto & physicalDevice : m_physicalDevices )
		{
			size_t score = 0;

			if ( !this->checkDeviceCompatibility(physicalDevice, RunningMode::Performance, VK_QUEUE_COMPUTE_BIT, score) )
				continue;

			if ( !this->checkDevicesFeaturesForCompute(physicalDevice, score) )
				continue;

			if ( !this->checkDeviceForRequiredExtensions(physicalDevice, requiredExtensions, score) )
				continue;

			TraceInfo{ClassId} << "Physical device '" << physicalDevice->properties().deviceName << "' reached score of " << score;

			scoredDevices.emplace(score, physicalDevice);
		}

		/* NOTE: Returns the device with the highest score. */
		if ( scoredDevices.empty() )
		{
			Tracer::fatal(ClassId, "There is no physical device compatible with Vulkan.");

			return {};
		}

		const auto & selectedPhysicalDevice = scoredDevices.rbegin()->second;

		TraceSuccess{ClassId} <<
			"Compute capable physical device '" << selectedPhysicalDevice->properties().deviceName << "' selected ! "
			"Creating the logical compute device ...";

		/* NOTE: Logical device creation for computing. */
		auto logicalDevice = std::make_shared< Device >(selectedPhysicalDevice);
		logicalDevice->setIdentifier((std::stringstream{} << "VulkanInstance-" << selectedPhysicalDevice->properties().deviceName << "(Physics)-Device").str());

		DeviceRequirements requirements{DeviceJobHint::Compute};
		requirements.requireComputeQueues({1.0F}, {0.5F});
		requirements.requireTransferQueues({1.0F});

		if ( !logicalDevice->create(requirements, requiredExtensions) )
			return {};

		m_devices.emplace_back(logicalDevice);

		return logicalDevice;
	}

	std::vector< const char * >
	Instance::getSupportedValidationLayers (const std::vector< std::string > & requestedValidationLayers, const std::vector< VkLayerProperties > & availableValidationLayers) noexcept
	{
		std::vector< const char * > supportedValidationLayers{};

		if ( !availableValidationLayers.empty() )
		{
			for ( const auto & requestedValidationLayer : requestedValidationLayers )
			{
				auto layerFound = false;

				for ( const auto & availableValidationLayer : availableValidationLayers )
				{
					if ( std::strcmp(requestedValidationLayer.c_str(), availableValidationLayer.layerName ) == 0 )
					{
						supportedValidationLayers.emplace_back(requestedValidationLayer.c_str());

						layerFound = true;

						break;
					}
				}

				if ( !layerFound )
					TraceWarning{ClassId} << "The requested '" << requestedValidationLayer << "' validation layer is unavailable !";
			}
		}
		else
		{
			TraceError{ClassId} << "There is no validation layer available !";
		}

		return supportedValidationLayers;
	}

	void
	Instance::modulateDeviceScoring (const VkPhysicalDeviceProperties & deviceProperties, RunningMode runningMode, size_t & score) const noexcept
	{
		switch ( runningMode )
		{
			case RunningMode::Performance :
				switch ( deviceProperties.deviceType )
				{
					case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU :
						score *= 3;
						break;

					case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU :
						score *= 5;
						break;

					case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU :
						score *= 2;
						break;

					default:
						break;
				}
				break;

			case RunningMode::PowerSaving :
				switch ( deviceProperties.deviceType )
				{
					case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU :
						score *= 5;
						break;

					case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU :
						score *= 1;
						break;

					case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU :
						score *= 2;
						break;

					case VK_PHYSICAL_DEVICE_TYPE_CPU :
						score *= 3;
						break;

					default:
						break;
				}
				break;

			case RunningMode::DontCare :
				switch ( deviceProperties.deviceType )
				{
					case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU :
						score *= 3;
						break;

					case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU :
						score *= 2;
						break;

					default :
						break;
				}
				break;
		}
	}

	bool
	Instance::checkDeviceCompatibility (const std::shared_ptr< PhysicalDevice > & physicalDevice, RunningMode runningMode, VkQueueFlagBits type, size_t & score) const noexcept
	{
		for ( const auto & queueFamilyProperty : physicalDevice->queueFamilyProperties() )
		{
			if ( !(queueFamilyProperty.queueFlags & type) )
				continue;

			this->modulateDeviceScoring(physicalDevice->properties(), runningMode, score);

			return true;
		}

		return false;
	}

	bool
	Instance::checkDeviceCompatibility (const std::shared_ptr< PhysicalDevice > & physicalDevice, RunningMode runningMode, const Window & window, size_t & score) const noexcept
	{
		for ( const auto & queueFamilyProperty : physicalDevice->queueFamilyProperties() )
		{
			/* Must be a graphics family queue. */
			if ( !(queueFamilyProperty.queueFlags & VK_QUEUE_GRAPHICS_BIT) )
				continue;

			/* Must support the presentation, have valid presents modes and surface formats. */
			if ( !window.surface()->presentationSupported() || window.surface()->presentModes().empty() || window.surface()->formats().empty() )
				continue;

			score += window.surface()->formats().size();
			score += window.surface()->presentModes().size();

			this->modulateDeviceScoring(physicalDevice->properties(), runningMode, score);

			return true;
		}

		return false;
	}

	bool
	Instance::checkDevicesFeaturesForGraphics (const std::shared_ptr< PhysicalDevice > & physicalDevice, size_t &) const noexcept
	{
		const auto & properties = physicalDevice->properties();
		const auto & features = physicalDevice->features();

		if ( !features.robustBufferAccess )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'robustBufferAccess' feature !";

			//return false;
		}

		if ( !features.fullDrawIndexUint32 )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'fullDrawIndexUint32' feature !";

			//return false;
		}

		if ( !features.imageCubeArray )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'imageCubeArray' feature !";

			//return false;
		}

		if ( !features.independentBlend )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'independentBlend' feature !";

			//return false;
		}

		if ( !features.geometryShader )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'geometryShader' feature !";

			//return false;
		}

		if ( !features.tessellationShader )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'tessellationShader' feature !";

			//return false;
		}

		if ( !features.sampleRateShading )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'sampleRateShading' feature !";

			//return false;
		}

		if ( !features.dualSrcBlend )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'dualSrcBlend' feature !";

			//return false;
		}

		if ( !features.logicOp )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'logicOp' feature !";

			//return false;
		}

		if ( !features.multiDrawIndirect )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'multiDrawIndirect' feature !";

			//return false;
		}

		if ( !features.drawIndirectFirstInstance )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'drawIndirectFirstInstance' feature !";

			//return false;
		}

		if ( !features.depthClamp )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'depthClamp' feature !";

			//return false;
		}

		if ( !features.depthBiasClamp )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'depthBiasClamp' feature !";

			//return false;
		}

		if ( !features.fillModeNonSolid )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'fillModeNonSolid' feature !";

			//return false;
		}

		if ( !features.depthBounds )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'depthBounds' feature !";

			//return false;
		}

		if ( !features.wideLines )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'wideLines' feature !";

			//return false;
		}

		if ( !features.largePoints )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'largePoints' feature !";

			//return false;
		}

		if ( !features.alphaToOne )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'alphaToOne' feature !";

			//return false;
		}

		if ( !features.multiViewport )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'multiViewport' feature !";

			//return false;
		}

		if ( !features.samplerAnisotropy )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'samplerAnisotropy' feature !";

			//return false;
		}

		if ( !features.textureCompressionETC2 )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'textureCompressionETC2' feature !";

			//return false;
		}

		if ( !features.textureCompressionASTC_LDR )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'textureCompressionASTC_LDR' feature !";

			//return false;
		}

		if ( !features.textureCompressionBC )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'textureCompressionBC' feature !";

			//return false;
		}

		if ( !features.occlusionQueryPrecise )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'occlusionQueryPrecise' feature !";

			//return false;
		}

		if ( !features.pipelineStatisticsQuery )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'pipelineStatisticsQuery' feature !";

			//return false;
		}

		if ( !features.vertexPipelineStoresAndAtomics )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'vertexPipelineStoresAndAtomics' feature !";

			//return false;
		}

		if ( !features.fragmentStoresAndAtomics )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'fragmentStoresAndAtomics' feature !";

			//return false;
		}

		if ( !features.shaderTessellationAndGeometryPointSize )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderTessellationAndGeometryPointSize' feature !";

			//return false;
		}

		if ( !features.shaderImageGatherExtended )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderImageGatherExtended' feature !";

			//return false;
		}

		if ( !features.shaderStorageImageExtendedFormats )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderStorageImageExtendedFormats' feature !";

			//return false;
		}

		if ( !features.shaderStorageImageMultisample )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderStorageImageMultisample' feature !";

			//return false;
		}

		if ( !features.shaderStorageImageReadWithoutFormat )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderStorageImageReadWithoutFormat' feature !";

			//return false;
		}

		if ( !features.shaderStorageImageWriteWithoutFormat )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderStorageImageWriteWithoutFormat' feature !";

			//return false;
		}

		if ( !features.shaderUniformBufferArrayDynamicIndexing )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderUniformBufferArrayDynamicIndexing' feature !";

			//return false;
		}

		if ( !features.shaderSampledImageArrayDynamicIndexing )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderSampledImageArrayDynamicIndexing' feature !";

			//return false;
		}

		if ( !features.shaderStorageBufferArrayDynamicIndexing )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderStorageBufferArrayDynamicIndexing' feature !";

			//return false;
		}

		if ( !features.shaderStorageImageArrayDynamicIndexing )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderStorageImageArrayDynamicIndexing' feature !";

			//return false;
		}

		if ( !features.shaderClipDistance )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderClipDistance' feature !";

			//return false;
		}

		if ( !features.shaderCullDistance )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderCullDistance' feature !";

			//return false;
		}

		if ( !features.shaderFloat64 )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderFloat64' feature !";

			//return false;
		}

		if ( !features.shaderInt64 )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderInt64' feature !";

			//return false;
		}

		if ( !features.shaderInt16 )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderInt16' feature !";

			//return false;
		}

		if ( !features.shaderResourceResidency )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderResourceResidency' feature !";

			//return false;
		}

		if ( !features.shaderResourceMinLod )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'shaderResourceMinLod' feature !";

			//return false;
		}

		if ( !features.sparseBinding )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'sparseBinding' feature !";

			//return false;
		}

		if ( !features.sparseResidencyBuffer )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'sparseResidencyBuffer' feature !";

			//return false;
		}

		if ( !features.sparseResidencyImage2D )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'sparseResidencyImage2D' feature !";

			//return false;
		}

		if ( !features.sparseResidencyImage3D )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'sparseResidencyImage3D' feature !";

			//return false;
		}

		if ( !features.sparseResidency2Samples )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'sparseResidency2Samples' feature !";

			//return false;
		}

		if ( !features.sparseResidency4Samples )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'sparseResidency4Samples' feature !";

			//return false;
		}

		if ( !features.sparseResidency8Samples )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'sparseResidency8Samples' feature !";

			//return false;
		}

		if ( !features.sparseResidency16Samples )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'sparseResidency16Samples' feature !";

			//return false;
		}

		if ( !features.sparseResidencyAliased )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'sparseResidencyAliased' feature !";

			//return false;
		}

		if ( !features.variableMultisampleRate )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'variableMultisampleRate' feature !";

			//return false;
		}

		if ( !features.inheritedQueries )
		{
			TraceWarning{ClassId} << "The physical device '" << properties.deviceName << "' is missing 'inheritedQueries' feature !";

			//return false;
		}

		return true;
	}

	bool
	Instance::checkDevicesFeaturesForCompute (const std::shared_ptr< PhysicalDevice > & physicalDevice, size_t & score) const noexcept
	{
		//const auto & properties = physicalDevice->properties();
		//const auto & features = physicalDevice->features();

		return true;
	}

	bool
	Instance::checkDeviceForRequiredExtensions (const std::shared_ptr< PhysicalDevice > & physicalDevice, const std::vector< const char * > & requiredExtensions, size_t & score) const noexcept
	{
		const auto & properties = physicalDevice->properties();
		const auto & extensions = physicalDevice->getExtensions();

		score += extensions.size();

		/* NOTE: If no requirements, we can stop here. */
		if ( requiredExtensions.empty() )
			return true;

		if ( extensions.empty() )
			return false;

		for ( const auto & requiredExtenion : requiredExtensions )
		{
			auto found = std::any_of(extensions.cbegin(), extensions.cend(), [requiredExtenion] (const auto & extension) {
				return std::strcmp(requiredExtenion, extension.extensionName) == 0;
			});

			/* NOTE: Missing required extension. */
			if ( !found )
			{
				TraceError{ClassId} << "The physical device '" << properties.deviceName << "' is missing the required '" << requiredExtenion << "' extension !";

				return false;
			}
		}

		return true;
	}
}
