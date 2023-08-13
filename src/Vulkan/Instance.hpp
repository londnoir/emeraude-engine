/*
 * Emeraude/Vulkan/Instance.hpp
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
#include <string>
#include <vector>
#include <array>
#include <memory>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "Graphics/FramebufferPrecisions.hpp"
#include "DebugMessenger.hpp"
#include "PhysicalDevice.hpp"
#include "Device.hpp"

/* Forward declarations */
namespace Emeraude
{
	class Arguments;
	class Settings;
	class Window;
}

namespace Emeraude::Vulkan
{
	/**
	 * @brief The Vulkan instance service class.
	 * @extends Emeraude::ServiceInterface This is a service
	 */
	class Instance final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanInstanceService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* Settings keys */
			static constexpr auto EnableInstanceDebugKey = "Video/Vulkan/EnableInstanceDebug";
			static constexpr auto ValidationLayersEnabledKey = "Video/Vulkan/ValidationLayers/Enabled";
			static constexpr auto ValidationLayersRequestedKey = "Video/Vulkan/ValidationLayers/RequestedLayers";
			static constexpr auto UseDebugMessengerKey = "Video/Vulkan/ValidationLayers/UseDebugMessenger";
			static constexpr auto ShowAvailableValidationLayersKey = "Video/Vulkan/ValidationLayers/ShowAvailable";
			static constexpr auto ShowAvailableInstanceExtensionsKey = "Video/Vulkan/Extensions/ShowAvailableForInstance";

			/**
			 * @brief Constructs the Vulkan instance.
			 * @param arguments A reference to Arguments.
			 * @param coreSettings A reference to the core settings.
			 */
			Instance (const Arguments & arguments, Settings & coreSettings) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Engine::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Returns the Vulkan instance handle wrapped in a smart pointer.
			 * @return VkInstance
			 */
			[[nodiscard]]
			VkInstance handle () const noexcept;

			/**
			 * @brief Returns a reference to the physical device smart pointer list.
			 * @return const std::vector< std::shared_ptr< PhysicalDevice > > &
			 */
			[[nodiscard]]
			const std::vector< std::shared_ptr< PhysicalDevice > > & physicalDevices () const noexcept;

			/**
			 * @brief Returns a reference to the device smart pointer list.
			 * @return const std::vector< std::shared_ptr< Device > > &
			 */
			[[nodiscard]]
			const std::vector< std::shared_ptr< Device > > & devices () const noexcept;

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
			 * @brief Returns a logical device with graphics capabilities.
			 * @param window A reference to a Window to check the device with presentation. Default Off-screen rendering.
			 * @return std::shared_ptr< Device >
			 */
			[[nodiscard]]
			std::shared_ptr< Device > getGraphicsDevice (Window & window) noexcept;

			/**
			 * @brief Returns a logical device with compute capabilities.
			 * @return std::shared_ptr< Device >
			 */
			[[nodiscard]]
			std::shared_ptr< Device > getComputeDevice () noexcept;

			/**
			 * @brief Returns a list of validation layers available from Vulkan.
			 * @note This method follow the vkEnumerateDeviceLayerProperties() deprecation.
			 * @return std::vector< VkLayerProperties >
			 */
			[[nodiscard]]
			static std::vector< VkLayerProperties > getValidationLayers () noexcept;

			/**
			 * @brief Returns a list of extensions available from Vulkan.
			 * @param pLayerName Default nullptr.
			 * @return std::vector< VkExtensionProperties >
			 */
			[[nodiscard]]
			static std::vector< VkExtensionProperties > getExtensions (const char * pLayerName = nullptr) noexcept;

			/**
			 * @brief Finds a suitable color buffer format.
			 * @param device A reference to a device smart pointer.
			 * @param redBits The bit depth for red component.
			 * @param greenBits The bit depth for green component.
			 * @param blueBits The bit depth for blue component.
			 * @param alphaBits The bit depth for alpha component.
			 * @return VkFormat
			 */
			[[nodiscard]]
			static VkFormat findColorFormat (const std::shared_ptr< Vulkan::Device > & device, uint32_t redBits, uint32_t greenBits, uint32_t blueBits, uint32_t alphaBits) noexcept;

			/**
			 * @brief Finds a suitable color buffer format.
			 * @param device A reference to a device smart pointer.
			 * @param precision A reference to a framebuffer prceisions structure.
			 * @return VkFormat
			 */
			[[nodiscard]]
			inline
			static
			VkFormat
			findColorFormat (const std::shared_ptr< Vulkan::Device > & device, const Graphics::FramebufferPrecisions & precision) noexcept
			{
				return Instance::findColorFormat(device, precision.redBits(), precision.greenBits(), precision.blueBits(), precision.alphaBits());
			}

			/**
			 * @brief Finds a suitable depth/stencil buffer format.
			 * @param device A reference to a device smart pointer.
			 * @param depthBits The bit depth for depth buffer.
			 * @param stencilBits The bit depth for stencil buffer.
			 * @return VkFormat
			 */
			[[nodiscard]]
			static VkFormat findDepthStencilFormat (const std::shared_ptr< Vulkan::Device > & device, uint32_t depthBits, uint32_t stencilBits) noexcept;

			/**
			 * @brief Finds a suitable depth/stencil buffer format.
			 * @param device A reference to a device smart pointer.
			 * @param precision A reference to a framebuffer prceisions structure.
			 * @return VkFormat
			 */
			[[nodiscard]]
			inline
			static
			VkFormat
			findDepthStencilFormat (const std::shared_ptr< Vulkan::Device > & device, const Graphics::FramebufferPrecisions & precision) noexcept
			{
				return Instance::findDepthStencilFormat(device, precision.depthBits(), precision.stencilBits());
			}

			/**
			 * @brief Finds the right Vulkan token for multisampling.
			 * @param device A reference to a device smart pointer.
			 * @param samples The number of samples desired.
			 * @return VkSampleCountFlagBits
			 */
			[[nodiscard]]
			static VkSampleCountFlagBits findSampleCount (uint32_t samples) noexcept;

			/**
			 * @brief Returns a list of supported validations layers with the current system from a requested list.
			 * @param requestedValidationLayers A reference to a vector of requested validation layer names.
			 * @param availableValidationlayers A reference to a vector of available validation layer properties.
			 * @return std::vector< const char * >
			 */
			[[nodiscard]]
			static std::vector< const char * > getSupportedValidationLayers (const std::vector< std::string > & requestedValidationLayers, const std::vector< VkLayerProperties > & availableValidationLayers = Instance::getValidationLayers()) noexcept;

		private:

			/* Flag names. */
			static constexpr auto DebugMode = 0UL;
			static constexpr auto ValidationLayersEnabled = 1UL;
			static constexpr auto UseDebugMessenger = 2UL;

			/** @copydoc Emeraude::Engine::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::Engine::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Read settings.
			 * @return void
			 */
			void readSettings () noexcept;

			/**
			 * @brief Returns a list of available devices.
			 * @return std::vector< VkPhysicalDevice >
			 */
			[[nodiscard]]
			std::vector< VkPhysicalDevice > getPhysicalDevices () const noexcept;

			/**
			 * @brief Configures the list of required validation layers.
			 * @note This method follow the vkEnumerateDeviceLayerProperties() deprecation.
			 * @return void
			 */
			void setRequiredValidationLayers () noexcept;

			/**
			 * @brief Configures the list of required extensions.
			 * @return void
			 */
			void setRequiredExtensions () noexcept;

			/**
			 * @brief Modulates the device score against a running strategy.
			 * @param deviceProperties A vulkan struct for the device properties.
			 * @param runningMode The desired running mode.
			 * @param score A reference to the score.
			 */
			void modulateDeviceScoring (const VkPhysicalDeviceProperties & deviceProperties, RunningMode runningMode, size_t & score) const noexcept;

			/**
			 * @brief Checks the physical device type for use as a specific purpose
			 * @param physicalDevice A reference to the physical device smart pointer.
			 * @param runningMode The desired running mode.
			 * @param type The desired queue type.
			 * @param score A reference to a score to sort preferred device.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkDeviceCompatibility (const std::shared_ptr< PhysicalDevice > & physicalDevice, RunningMode runningMode, VkQueueFlagBits type, size_t & score) const noexcept;

			/**
			 * @brief Checks the physical device type for use as a graphics device with presentation supported.
			 * @param physicalDevice A reference to the physical device smart pointer.
			 * @param runningMode The desired running mode.
			 * @param window A reference to the handle where the graphics device will draw to.
			 * @param score A reference to a score to sort preferred device.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkDeviceCompatibility (const std::shared_ptr< PhysicalDevice > & physicalDevice, RunningMode runningMode, const Window & window, size_t & score) const noexcept;

			/**
			 * @brief Checks the device features presence for a specialized device selector.
			 * @param physicalDevice A reference to the physical device smart pointer.
			 * @param score A reference to a score to sort preferred device.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkDevicesFeaturesForGraphics (const std::shared_ptr< PhysicalDevice > & physicalDevice, size_t & score) const noexcept;

			/**
			 * @brief Checks the device features presence for a specialized device selector.
			 * @param physicalDevice A reference to the physical device smart pointer.
			 * @param score A reference to a score to sort preferred device.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkDevicesFeaturesForCompute (const std::shared_ptr< PhysicalDevice > & physicalDevice, size_t & score) const noexcept;

			/**
			 * @brief Checks the device extensions presence for a specialized device selector.
			 * @param physicalDevice A reference to the physical device smart pointer.
			 * @param requiredExtensions A reference to a list of required extensions.
			 * @param score A reference to a score to sort preferred device.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkDeviceForRequiredExtensions (const std::shared_ptr< PhysicalDevice > & physicalDevice, const std::vector< const char * > & requiredExtensions, size_t & score) const noexcept;

			const Arguments & m_arguments;
			Settings & m_coreSettings;
			VkInstance m_instance = VK_NULL_HANDLE;
			VkApplicationInfo m_applicationInfo{};
			VkInstanceCreateInfo m_createInfo{};
			VkDebugUtilsMessengerCreateInfoEXT m_debugCreateInfo{};
			std::unique_ptr< DebugMessenger > m_debugMessenger{};
			std::vector< std::shared_ptr< PhysicalDevice > > m_physicalDevices{};
			std::vector< std::shared_ptr< Device > > m_devices{};
			std::vector< std::string > m_requestedValidationLayers{};
			std::vector< const char * > m_requiredValidationLayers{};
			std::vector< const char * > m_requiredExtensions{};
			std::array< bool, 8 > m_flags{
				false/*DebugMode*/,
				false/*ValidationLayersEnabled*/,
				false/*UseDebugMessenger*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
