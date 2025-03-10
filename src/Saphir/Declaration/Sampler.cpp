/*
 * src/Saphir/Declaration/Sampler.cpp
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

#include "Sampler.hpp"

/* STL inclusions. */
#include <sstream>

namespace Emeraude::Saphir::Declaration
{
	using namespace Keys;

	Sampler::Sampler (uint32_t set, uint32_t binding, Key type, Key name, size_t arraySize) noexcept
		: m_set(set), m_binding(binding), m_type(type), m_name(name), m_arraySize(arraySize)
	{

	}

	bool
	Sampler::isValid () const noexcept
	{
		if ( m_type == nullptr || m_name == nullptr )
			return false;

		return true;
	}

	std::string
	Sampler::sourceCode () const noexcept
	{
		std::stringstream code{};

		code <<
			GLSL::Layout << "(" << GLSL::Set << " = " << m_set << ", " << GLSL::Binding << " = " << m_binding << ") " <<
			GLSL::Uniform << ' ' << m_type << ' ' << m_name;

		if ( m_arraySize > 0 )
		{
			code << '[' << m_arraySize << ']';
		}

		code << ";" "\n";

		return code.str();
	}

	Key
	Sampler::name () const noexcept
	{
		return m_name;
	}

	size_t
	Sampler::bytes () const noexcept
	{
		return 0;
	}

	Key
	Sampler::type () const noexcept
	{
		return m_type;
	}

	size_t
	Sampler::arraySize () const noexcept
	{
		return m_arraySize;
	}

	uint32_t
	Sampler::set () const noexcept
	{
		return m_set;
	}

	uint32_t
	Sampler::binding () const noexcept
	{
		return m_binding;
	}
}
