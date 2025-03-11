/*
 * src/Saphir/Declaration/Member/BufferBackedBlock.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "BufferBackedBlock.hpp"

/* STL inclusions. */
#include <sstream>

namespace EmEn::Saphir::Declaration::Member
{
	using namespace Keys;

	BufferBackedBlock::BufferBackedBlock (VariableType type, Key name, Key layout, size_t arraySize) noexcept
		: m_type(type), m_name(name), m_layout(layout), m_arraySize(arraySize)
	{

	}

	VariableType
	BufferBackedBlock::type () const noexcept
	{
		return m_type;
	}

	Key
	BufferBackedBlock::name () const noexcept
	{
		return m_name;
	}

	size_t
	BufferBackedBlock::bytes () const noexcept
	{
		/* FIXME : Check alignment with array size. */
		if ( m_arraySize > 1 )
		{
			return size_bytes(m_type) * m_arraySize;
		}

		return size_bytes(m_type);
	}

	const Key &
	BufferBackedBlock::layout () const noexcept
	{
		return m_layout;
	}

	size_t
	BufferBackedBlock::arraySize () const noexcept
	{
		return m_arraySize;
	}

	std::string
	BufferBackedBlock::sourceCode () const noexcept
	{
		std::stringstream code{};

		if ( m_layout != nullptr )
		{
			code << GLSL::Layout << " (" << m_layout << ") ";
		}

		code << to_cstring(m_type) << ' ' << m_name;

		if ( m_arraySize > 0 )
		{
			code << '[' << m_arraySize << ']';
		}

		code << ";" "\n";

		return code.str();
	}
}
