/*
 * Emeraude/Vulkan/Surface.hpp
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

/* C/C++ standard libraries */
#include <memory>
#include <vector>

/* Third-party libraries */
#include "Third-Party-Inclusion/vulkan.hpp"

namespace Emeraude::Vulkan
{
	class Instance;
	class PhysicalDevice;
	class Device;

	/**
	 * @brief The Surface class
	 */
	class Surface final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanSurface"};

			/**
			 * @brief Constructs a surface info.
			 * @param instance A reference to a vulkan instance.
			 * @param surface A vulkan surface handle.
			 */
			Surface (const Instance & instance, const VkSurfaceKHR & surface) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Surface (const Surface & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Surface (Surface && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Surface & operator= (const Surface & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Surface & operator= (Surface && copy) noexcept = delete;

			/**
			 * @brief Destructs the surface.
			 */
			~Surface ();

			/**
			 * @brief Updates surface informations with a physical device.
			 * @param physicalDevice A reference to the physical device smart pointer.
			 * @return bool
			 */
			bool update (const std::shared_ptr< PhysicalDevice > & physicalDevice) noexcept;

			/**
			 * @brief Updates surface informations with a physical device.
			 * @param device A reference to the device smart pointer.
			 * @return bool
			 */
			bool update (const std::shared_ptr< Device > & device) noexcept;

			/**
			 * @brief Returns the surface handle.
			 * @return VkSurfaceKHR
			 */
			[[nodiscard]]
			VkSurfaceKHR handle () const noexcept;

			/**
			 * @brief Returns the surface capabilities.
			 * @return const VkSurfaceCapabilitiesKHR &
			 */
			[[nodiscard]]
			const VkSurfaceCapabilitiesKHR & capabilities () const noexcept;

			/**
			 * @brief Returns the surface formats.
			 * @return const std::vector< VkSurfaceFormatKHR > &
			 */
			[[nodiscard]]
			const std::vector< VkSurfaceFormatKHR > & formats () const noexcept;

			/**
			 * @brief Returns the surface present modes.
			 * @return const std::vector< VkPresentModeKHR > &
			 */
			[[nodiscard]]
			const std::vector< VkPresentModeKHR > & presentModes () const noexcept;

			/**
			 * @brief Returns the surface present rectangles.
			 * @return const std::vector< VkRect2D > &
			 */
			[[nodiscard]]
			const std::vector< VkRect2D > & presentRectangles () const noexcept;

			/**
			 * @brief Returns whether the presentation is supported by this surface.
			 * @return bool
			 */
			[[nodiscard]]
			bool presentationSupported () const noexcept;

			/**
			 * @brief Returns a string of surface capabilities.
			 * @param capabilities A reference to a surface capabilities structure.
			 * @return std::string
			 */
			[[nodiscard]]
			static std::string getCapabilitiesString (const VkSurfaceCapabilitiesKHR & capabilities) noexcept;

		private:

			const Instance & m_instance; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
			VkSurfaceKHR m_handle{VK_NULL_HANDLE};
			VkSurfaceCapabilitiesKHR m_capabilities{};
			std::vector< VkSurfaceFormatKHR > m_formats{};
			std::vector< VkPresentModeKHR > m_presentModes{};
			std::vector< VkRect2D > m_presentRectangles{};
			bool m_supported{false};
	};
}
