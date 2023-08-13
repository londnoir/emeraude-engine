/*
 * Emeraude/Vulkan/MemoryRegion.cpp
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

#include "MemoryRegion.hpp"

/* C/C++ standard libraries */
#include <sstream>

namespace Emeraude::Vulkan
{
	MemoryRegion::MemoryRegion (const void * source, size_t bytes, size_t offset) noexcept
		: m_source(source), m_offset(offset), m_bytes(bytes)
	{

	}

	const void *
	MemoryRegion::source () const noexcept
	{
		return m_source;
	}

	size_t
	MemoryRegion::bytes () const noexcept
	{
		return m_bytes;
	}

	size_t
	MemoryRegion::offset () const noexcept
	{
		return m_offset;
	}

	std::ostream &
	operator<< (std::ostream & out, const MemoryRegion & obj)
	{
		return out << "Region of " << obj.m_bytes << " bytes from @" << obj.m_source << " to destination offset : " << obj.m_offset;
	}

	std::string
	to_string (const MemoryRegion & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
