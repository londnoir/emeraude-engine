/*
 * Emeraude/Vulkan/AbstractObject.cpp
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

#include "AbstractObject.hpp"

/* C/C++ standard libraries. */
#ifdef VK_TRACKING
#include <iostream>
#endif

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
#ifdef VK_TRACKING

	std::map< void *, std::string > AbstractObject::s_tracking{}; // NOLINT(cppcoreguidelines-avoid-non-const-global-variables) NOTE : Debug purpose

	AbstractObject::AbstractObject () noexcept
	{
		s_tracking[this] = "";

		std::cout << "[VK_TRACKING] Object @" << this << " constructed !" "\n";
	}

	AbstractObject::~AbstractObject ()
	{
		if ( !m_flags[Created] )
		{
			TraceError{"VulkanObject"} << "A Vulkan object (" << m_identifier << ") was not correctly constructed !";
		}

		if ( !m_flags[Destroyed] )
		{
			TraceError{"VulkanObject"} << "A Vulkan object (" << m_identifier << ") is not correctly destroyed !";
		}

		if ( m_identifier.empty() )
		{
			std::cout << "[VK_TRACKING] Object @" << this << " UNIDENTIFIED destructed !" "\n";
		}
		else
		{
			std::cout << "[VK_TRACKING] Object @" << this << " '" << m_identifier << "' destructed !" "\n";
		}

		s_tracking.erase(this);
	}

	void
	AbstractObject::setIdentifier (const std::string & identifier) noexcept
	{
		m_identifier = identifier;

		s_tracking[this] = m_identifier;

		std::cout << "[VK_TRACKING] Object @" << this << " identified as '" << m_identifier << "' !" "\n";
	}

#else

	AbstractObject::~AbstractObject ()
	{
		if ( !m_flags[Created] )
		{
			TraceError{"VulkanObject"} << "A Vulkan object (" << m_identifier << ") was not correctly constructed !";
		}

		if ( !m_flags[Destroyed] )
		{
			TraceError{"VulkanObject"} << "A Vulkan object (" << m_identifier << ") is not correctly destroyed !";
		}
	}

	void
	AbstractObject::setIdentifier (const std::string & identifier) noexcept
	{
		m_identifier = identifier;
	}

#endif

	const std::string &
	AbstractObject::identifier () const noexcept
	{
		return m_identifier;
	}

	bool
	AbstractObject::isCreated () const noexcept
	{
		return m_flags[Created];
	}

	void
	AbstractObject::setCreated () noexcept
	{
		m_flags[Created] = true;
	}

	void
	AbstractObject::setDestroyed () noexcept
	{
		m_flags[Destroyed] = true;
	}
}
