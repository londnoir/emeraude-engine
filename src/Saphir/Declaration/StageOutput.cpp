/*
 * src/Saphir/Declaration/StageOutput.cpp
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

#include "StageOutput.hpp"

/* STL inclusions. */
#include <sstream>

namespace Emeraude::Saphir::Declaration
{
	using namespace Keys;

	StageOutput::StageOutput (uint32_t location, Key type, Key name, Key interpolation, int32_t arraySize) noexcept
		: m_location(location),
		  m_type(type),
		  m_name(name),
		  m_interpolation(interpolation),
		  m_arraySize(arraySize)
	{

	}

	bool
	StageOutput::isValid () const noexcept
	{
		return m_type != nullptr && m_name != nullptr;
	}

	std::string
	StageOutput::sourceCode () const noexcept
	{
		std::stringstream code{};

		code << GLSL::Layout << " (" << GLSL::Location << " = " << m_location << ") ";

		if ( m_interpolation != nullptr )
		{
			code << m_interpolation << ' ';
		}

		code << GLSL::Out << ' ' << m_type << ' ' << m_name;

		if ( m_arraySize == -1 )
		{
			code << "[]";
		}
		else if ( m_arraySize > 0 )
		{
			code << '[' << m_arraySize << ']';
		}

		code << ";" "\n";

		return code.str();
	}

	Key
	StageOutput::name () const noexcept
	{
		return m_name;
	}

	size_t
	StageOutput::bytes () const noexcept
	{
		return 0;
	}

	uint32_t
	StageOutput::location () const noexcept
	{
		return m_location;
	}

	Key
	StageOutput::type () const noexcept
	{
		return m_type;
	}

	Key
	StageOutput::interpolation () const noexcept
	{
		return m_interpolation;
	}

	int32_t
	StageOutput::arraySize () const noexcept
	{
		return m_arraySize;
	}

	bool
	StageOutput::isArray () const noexcept
	{
		return m_arraySize > 0;
	}

	bool
	StageOutput::isNonFixedArraySize () const noexcept
	{
		return m_arraySize == -1;
	}
}
