/*
 * src/Vulkan/AbstractObject.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "AbstractObject.hpp"

/* STL inclusions. */
#ifdef VK_TRACKING_ENABLED
#include <iostream>
#endif

/* Local inclusions. */
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
#ifdef VK_TRACKING_ENABLED

	std::map< void *, std::string > AbstractObject::s_tracking{};

	AbstractObject::AbstractObject () noexcept
		: m_identifier()
	{
		s_tracking[this] = "";

		std::cout << "[DEBUG:VK_TRACKING] A Vulkan object (@" << this << ") constructed !" "\n";
	}

	AbstractObject::~AbstractObject ()
	{
		const auto * identifier = m_identifier.empty() ? "***UNIDENTIFIED***" : m_identifier.data();

		if ( !m_flags[Created] )
		{
			TraceError{"VulkanObject"} << "A Vulkan object ('" << identifier << "' " << this << ") was not correctly constructed !";
		}

		if ( !m_flags[Destroyed] )
		{
			TraceError{"VulkanObject"} << "A Vulkan object ('" << identifier << "' " << this << ") is not correctly destroyed !";
		}

		std::cout << "[DEBUG:VK_TRACKING] A Vulkan object ('" << identifier << "' @" << this << ") destructed !" "\n";

		s_tracking.erase(this);
	}

	void
	AbstractObject::setIdentifier (const std::string & identifier) noexcept
	{
		m_identifier = identifier;

		s_tracking[this] = m_identifier;

		std::cout << "[DEBUG:VK_TRACKING] A Vulkan object ('" << m_identifier << "', @" << this << ") is marked !" "\n";
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

#endif
}
