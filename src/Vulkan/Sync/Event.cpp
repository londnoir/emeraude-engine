/*
 * Emeraude/Vulkan/Sync/Event.cpp
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

#include "Event.hpp"

/* Local inclusions. */
#include "../Device.hpp"
#include "../Utility.hpp"
#include "Tracer.hpp"

namespace Emeraude::Vulkan::Sync
{
	const char *
	to_cstring (EventStatus value) noexcept
	{
		switch ( value )
		{
			case EventStatus::Set :
				return SetString;

			case EventStatus::Reset :
				return ResetString;

			case EventStatus::Error :
				return ErrorString;

			default:
				return "Unknown";
		}
	}

	Event::Event (const std::shared_ptr< Device > & device, VkEventCreateFlags createFlags) noexcept
		: AbstractDeviceDependentObject(device)
	{
		m_createInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = createFlags;
	}

	Event::Event (const std::shared_ptr< Device > & device, const VkEventCreateInfo & createInfo) noexcept
		: AbstractDeviceDependentObject(device), m_createInfo(createInfo)
	{

	}

	Event::~Event ()
	{
		this->destroyFromHardware();
	}

	bool
	Event::createOnHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create this event !");

			return false;
		}

		const auto result = vkCreateEvent(this->device()->handle(), &m_createInfo, nullptr, &m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to create an event : " << vkResultToCString(result) << " !";

			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The event " << m_handle << " (" << this->identifier() << ") is successfully created !";

		return true;
	}

	bool
	Event::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the event " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		if (  m_handle != VK_NULL_HANDLE )
		{
			this->device()->waitIdle();

			vkDestroyEvent(this->device()->handle(), m_handle, nullptr);

			TraceSuccess{ClassId} << "The event " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}

		this->setDestroyed();

		return true;
	}

	VkEvent
	Event::handle () const noexcept
	{
		return m_handle;
	}

	VkEventCreateInfo
	Event::createInfo () const noexcept
	{
		return m_createInfo;
	}

	EventStatus
	Event::getStatus () const noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to get status from this fence !");

			return EventStatus::Error;
		}

		const auto result = vkGetEventStatus(this->device()->handle(), m_handle);

		switch ( result )
		{
			case VK_EVENT_SET :
				return EventStatus::Set;

			case VK_EVENT_RESET :
				return EventStatus::Reset;

			default :
				return EventStatus::Error;
		}
	}

	bool
	Event::set () const noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to set this event !");

			return false;
		}

		const auto result = vkSetEvent(this->device()->handle(), m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to set an event : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}

	bool
	Event::reset () const noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to reset this event !");

			return false;
		}

		const auto result = vkResetEvent(this->device()->handle(), m_handle);

		if ( result != VK_SUCCESS )
		{
			TraceError{ClassId} << "Unable to reset an event : " << vkResultToCString(result) << " !";

			return false;
		}

		return true;
	}
}
