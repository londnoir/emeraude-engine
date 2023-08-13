/*
 * Emeraude/Saphir/Declaration/Member/ShaderBlock.cpp
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

#include "ShaderBlock.hpp"

/* C/C++ standard libraries. */
#include <sstream>

namespace Emeraude::Saphir::Declaration::Member
{
	ShaderBlock::ShaderBlock (VariableType type, Key name, Key interpolation, size_t arraySize) noexcept
		: m_type(type), m_name(name), m_interpolation(interpolation), m_arraySize(arraySize)
	{

	}

	VariableType
	ShaderBlock::type () const noexcept
	{
		return m_type;
	}

	Key
	ShaderBlock::name () const noexcept
	{
		return m_name;
	}

	size_t
	ShaderBlock::bytes () const noexcept
	{
		/* FIXME : Check alignement with array size. */
		if ( m_arraySize > 1 )
		{
			return size_bytes(m_type) * m_arraySize;
		}

		return size_bytes(m_type);
	}

	const Key &
	ShaderBlock::interpolation () const noexcept
	{
		return m_interpolation;
	}

	size_t
	ShaderBlock::arraySize () const noexcept
	{
		return m_arraySize;
	}

	std::string
	ShaderBlock::sourceCode () const noexcept
	{
		std::stringstream code{};

		if ( m_interpolation != nullptr )
		{
			code << m_interpolation << ' ';
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
