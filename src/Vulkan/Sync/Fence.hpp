/*
 * Emeraude/Vulkan/Sync/Fence.hpp
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
#include <numeric>
#include <vector>

/* Local inclusions for inheritances. */
#include "../AbstractDeviceDependentObject.hpp"

namespace Emeraude::Vulkan::Sync
{
	/**
	 * @brief The fence status.
	 */
	enum class FenceStatus
	{
		Ready,
		Busy,
		Error
	};

	static constexpr auto ReadyString = "Ready";
	static constexpr auto BusyString = "Busy";
	//static constexpr auto ErrorString = "Error";

	/**
	 * @brief Returns a C-String version of the enum value.
	 * @param value The enum value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (FenceStatus value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (FenceStatus value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief The synchronization fence class. Fences are designed for GPU-to-CPU synchronization.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This object needs a device.
	 */
	class Fence final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanFence"};

			/**
			 * @brief Constructs a fence.
			 * @param device A reference to a smart pointer of the device.
			 * @param createFlags The create info flags. Default VK_FENCE_CREATE_SIGNALED_BIT.
			 */
			explicit Fence (const std::shared_ptr< Device > & device, VkFenceCreateFlags createFlags = VK_FENCE_CREATE_SIGNALED_BIT) noexcept;

			/**
			 * @brief Constructs an fence with a create info.
			 * @param device A reference to a smart pointer of the device.
			 * @param createInfo A reference to the create info.
			 */
			Fence (const std::shared_ptr< Device > & device, const VkFenceCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Fence (const Fence & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Fence (Fence && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Fence & operator= (const Fence & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Fence & operator= (Fence && copy) noexcept = default;

			/**
			 * @brief Destructs the fence.
			 */
			~Fence () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Returns the fence vulkan handle.
			 * @return VkFence
			 */
			[[nodiscard]]
			VkFence handle () const noexcept;

			/**
			 * @brief Returns the fence create info.
			 * @return VkFenceCreateInfo
			 */
			[[nodiscard]]
			VkFenceCreateInfo createInfo () const noexcept;

			/**
			 * @brief Sets the fence as unsignaled.
			 * @return bool
			 */
			[[nodiscard]]
			bool reset () const noexcept;

			/**
			 * @brief Sets the fence as signaled.
			 * @return bool
			 */
			[[nodiscard]]
			bool signal () const noexcept;

			/**
			 * @brief Returns the fence status.
			 * @return Status
			 */
			[[nodiscard]]
			FenceStatus getStatus () const noexcept;

			/**
			 * @brief Waits for fence to be signaled.
			 * @param timeout A duration in nanoseconds for timeout. Default close to infinity (584 years).
			 * @return bool
			 */
			[[nodiscard]]
			bool wait (uint64_t timeout = std::numeric_limits< uint64_t >::max()) const noexcept;

			/**
			 * @brief Waits for all fences to be signaled.
			 * @warning All the fences must be created by the device passed in parameters.
			 * @param device A reference to the device smart pointer.
			 * @param fences A reference to a vector of fences.
			 * @param timeout A duration in nanoseconds for timeout. Default close to infinity (584 years).
			 * @return bool
			 */
			static bool waitForAll (const std::shared_ptr< Device > & device, const std::vector< VkFence > & fences, uint64_t timeout = std::numeric_limits< uint64_t >::max()) noexcept;

			/**
			 * @brief Waits for any of fences to be signaled and returns it.
			 * @param device A reference to the device smart pointer.
			 * @param fences A reference to a vector of fences.
			 * @param timeout A duration in nanoseconds for timeout. Default close to infinity (584 years).
			 * @return bool
			 */
			static VkFence waitForAnyOf (const std::shared_ptr< Device > & device, const std::vector< VkFence > & fences, uint64_t timeout = std::numeric_limits< uint64_t >::max()) noexcept;

		private:

			VkFence m_handle{VK_NULL_HANDLE};
			VkFenceCreateInfo m_createInfo{};
	};
}
