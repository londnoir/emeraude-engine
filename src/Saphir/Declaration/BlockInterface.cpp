/*
 * Emeraude/Saphir/Declaration/BlockInterface.cpp
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

#include "BlockInterface.hpp"

/* Local inclusions. */
#include "Tracer.hpp"

namespace Emeraude::Saphir::Declaration
{
	using namespace Keys;

	BlockInterface::BlockInterface (Key name, Key instanceName, size_t arraySize) noexcept
		: m_name(name), m_instanceName(instanceName), m_arraySize(arraySize)
	{

	}

	Key
	BlockInterface::name () const noexcept
	{
		return m_name;
	}

	const std::string &
	BlockInterface::instanceName () const noexcept
	{
		return m_instanceName;
	}

	size_t
	BlockInterface::arraySize () const noexcept
	{
		return m_arraySize;
	}

	const std::unordered_map< Key, Structure > &
	BlockInterface::structures () const noexcept
	{
		return m_structures;
	}

	bool
	BlockInterface::addStructure (Key name, const Structure & structure) noexcept
	{
		if ( m_structures.contains(name) )
		{
			TraceError{"BlockInterface"} << "This block interface has already declared a structure named '" << name << "' !";

			return false;
		}

		m_structures.emplace(name, structure);

		return true;
	}
}
