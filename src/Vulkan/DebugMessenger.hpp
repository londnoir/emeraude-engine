/*
 * Emeraude/Vulkan/DebugMessenger.hpp
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
#include "AbstractObject.hpp"

namespace Emeraude::Vulkan
{
	class Instance;

	/**
	 * @brief Holds the debug messenger extension from the Vulkan API.
	 * @extends Emeraude::Vulkan::AbstractObject Do not need a device to works.
	 */
	class DebugMessenger final : public AbstractObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanDebugMessenger"};

			/**
			 * @brief Constructs the Vulkan debugger.
			 * @param instance A reference to a vulkan instance.
			 */
			explicit DebugMessenger (const Instance & instance) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			DebugMessenger (const DebugMessenger & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			DebugMessenger (DebugMessenger && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			DebugMessenger & operator= (const DebugMessenger & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			DebugMessenger & operator= (DebugMessenger && copy) noexcept = delete;

			/**
			 * @brief Destructs the Vulkan debugger.
			 */
			~DebugMessenger () override;

			/**
			 * @brief Returns a create info for debugging.
			 * @return VkDebugUtilsMessengerEXT
			 */
			[[nodiscard]]
			VkDebugUtilsMessengerEXT handle () noexcept;

			/**
			 * @brief Returns a create info for debugging.
			 * @return VkDebugUtilsMessengerCreateInfoEXT
			 */
			[[nodiscard]]
			VkDebugUtilsMessengerCreateInfoEXT createInfo () noexcept;

			/**
			 * @brief getCreateInfo
			 * @return VkDebugUtilsMessengerCreateInfoEXT
			 */
			[[nodiscard]]
			static VkDebugUtilsMessengerCreateInfoEXT getCreateInfo () noexcept;

		private:

			/**
			 * @brief Debug callback signature method for Vulkan messenger.
			 * @param messageSeverity
			 * @param messageType
			 * @param pCallbackData
			 * @param pUserData
			 * @return VkBool32
			 */
			static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback (VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData, void * pUserData) noexcept;

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Instance & m_instance;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			VkDebugUtilsMessengerEXT m_handle{VK_NULL_HANDLE};
			VkDebugUtilsMessengerCreateInfoEXT m_createInfo{};
	};
}
