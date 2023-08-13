/*
 * Emeraude/TracerEntry.cpp
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

#include "TracerEntry.hpp"

namespace Emeraude
{
	TracerEntry::TracerEntry (Severity severity, const char * tag, std::string message, const std_glue::source_location & location, const std::thread::id & threadId) noexcept
		: m_severity(severity), m_tag(tag), m_message(std::move(message)), m_location(location), m_threadId(threadId)
	{

	}

	const std::chrono::time_point< std::chrono::steady_clock > &
	TracerEntry::time () const noexcept
	{
		return m_time;
	}

	Severity
	TracerEntry::severity () const noexcept
	{
		return m_severity;
	}

	const char *
	TracerEntry::tag () const noexcept
	{
		return m_tag;
	}

	const std::string &
	TracerEntry::message () const noexcept
	{
		return m_message;
	}

	const std_glue::source_location &
	TracerEntry::location () const noexcept
	{
		return m_location;
	}

	const std::thread::id &
	TracerEntry::threadId () const noexcept
	{
		return m_threadId;
	}
}
