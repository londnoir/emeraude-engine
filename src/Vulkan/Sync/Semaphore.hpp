/*
 * Emeraude/Vulkan/Sync/Semaphore.hpp
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
#include <memory>

/* Local inclusions for inheritances. */
#include "../AbstractDeviceDependentObject.hpp"

namespace Emeraude::Vulkan::Sync
{
	/**
	 * @brief The synchronization semaphore class. Semaphores are designed for GPU tasks synchronization.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This object needs a device.
	 */
	class Semaphore final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanSemaphore"};

			/**
			 * @brief Constructs a semaphore.
			 * @param device A reference to a smart pointer of the device.
			 * @param createFlags The create info flags. Default none.
			 */
			explicit Semaphore (const std::shared_ptr< Device > & device, VkSemaphoreCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a semaphore with a create info.
			 * @param device A reference to a smart pointer of the device.
			 * @param createInfo A reference to the create info.
			 */
			Semaphore (const std::shared_ptr< Device > & device, const VkSemaphoreCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Semaphore (const Semaphore & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Semaphore (Semaphore && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Semaphore & operator= (const Semaphore & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Semaphore & operator= (Semaphore && copy) noexcept = default;

			/**
			 * @brief Destructs the semaphore.
			 */
			~Semaphore () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Returns the semaphore vulkan handle.
			 * @return VkSemaphore
			 */
			[[nodiscard]]
			VkSemaphore handle () const noexcept;

			/**
			 * @brief Returns the semaphore create info.
			 * @return VkSemaphoreCreateInfo
			 */
			[[nodiscard]]
			VkSemaphoreCreateInfo createInfo () const noexcept;

		private:

			VkSemaphore m_handle{VK_NULL_HANDLE};
			VkSemaphoreCreateInfo m_createInfo{};
	};
}
