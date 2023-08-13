/*
 * Emeraude/Vulkan/Sync/Event.hpp
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
	enum class EventStatus
	{
		Set,
		Reset,
		Error
	};

	static constexpr auto SetString = "Set";
	static constexpr auto ResetString = "Reset";
	//static constexpr auto ErrorString = "Error";

	/**
	 * @brief Returns a C-String version of the enum value.
	 * @param value The enum value.
	 * @return const char *
	 */
	[[nodiscard]]
	const char * to_cstring (EventStatus value) noexcept;

	/**
	 * @brief Returns a string version of the enum value.
	 * @param value The enum value.
	 * @return std::string
	 */
	[[nodiscard]]
	inline
	std::string
	to_string (EventStatus value) noexcept
	{
		return {to_cstring(value)};
	}

	/**
	 * @brief The synchronization event class.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This object needs a device.
	 */
	class Event final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanEvent"};

			/**
			 * @brief Constructs an event.
			 * @param device A reference to a smart pointer of the device.
			 * @param createFlags The create info flags. Default none.
			 */
			explicit Event (const std::shared_ptr< Device > & device, VkEventCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs an event with a create info.
			 * @param device A reference to a smart pointer of the device.
			 * @param createInfo A reference to the create info.
			 */
			Event (const std::shared_ptr< Device > & device, const VkEventCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Event (const Event & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Event (Event && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Event & operator= (const Event & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Event & operator= (Event && copy) noexcept = default;

			/**
			 * @brief Destructs the event.
			 */
			~Event () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Returns the event vulkan handle.
			 * @return VkEvent
			 */
			[[nodiscard]]
			VkEvent handle () const noexcept;

			/**
			 * @brief Returns the event create info.
			 * @return VkEventCreateInfo
			 */
			[[nodiscard]]
			VkEventCreateInfo createInfo () const noexcept;

			/**
			 * @brief Returns the event status.
			 * @return Status
			 */
			[[nodiscard]]
			EventStatus getStatus () const noexcept;

			/**
			 * @brief Sets the event status.
			 * @return bool
			 */
			[[nodiscard]]
			bool set () const noexcept;

			/**
			 * @brief Reset the event status.
			 * @return bool
			 */
			[[nodiscard]]
			bool reset () const noexcept;

		private:

			VkEvent m_handle{VK_NULL_HANDLE};
			VkEventCreateInfo m_createInfo{};
	};
}
