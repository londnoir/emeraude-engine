/*
 * Emeraude/Saphir/Declaration/TexelBuffer.cpp
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

#include "TexelBuffer.hpp"

/* C/C++ standard libraries. */
#include <sstream>

namespace Emeraude::Saphir::Declaration
{
	using namespace Keys;

	TexelBuffer::TexelBuffer (uint32_t set, uint32_t binding, Key type, Key name) noexcept
		: m_type(type), m_name(name), m_set(set), m_binding(binding)
	{

	}

	bool
	TexelBuffer::isValid () const noexcept
	{
		if ( m_type == nullptr || m_name == nullptr )
			return false;

		return true;
	}

	std::string
	TexelBuffer::sourceCode () const noexcept
	{
		return (std::stringstream{} <<
			GLSL::Layout << " (" << GLSL::Set << " = " << m_set << ", " << GLSL::Binding << " = " << m_binding << ") " <<
			GLSL::Uniform << ' ' << m_type << ' ' << m_name << ";" "\n"
		).str();
	}

	Key
	TexelBuffer::name () const noexcept
	{
		return m_name;
	}

	size_t
	TexelBuffer::bytes () const noexcept
	{
		return 0;
	}

	Key
	TexelBuffer::type () const noexcept
	{
		return m_type;
	}

	uint32_t
	TexelBuffer::set () const noexcept
	{
		return m_set;
	}

	uint32_t
	TexelBuffer::binding () const noexcept
	{
		return m_binding;
	}
}
