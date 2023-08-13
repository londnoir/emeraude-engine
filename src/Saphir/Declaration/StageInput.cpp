/*
 * Emeraude/Saphir/Declaration/StageInput.cpp
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

#include "StageInput.hpp"

/* C/C++ standard libraries. */
#include <sstream>

/* Local inclusions. */
#include "Saphir/ShaderGenerator.hpp"

namespace Emeraude::Saphir::Declaration
{
	using namespace Keys;

	StageInput::StageInput (Key name, Key interpolation, int32_t arraySize) noexcept
		: m_location(ShaderGenerator::getShaderVariableLocation(name)),
		  m_type(ShaderGenerator::getShaderVariableType(name)),
		  m_name(name),
		  m_interpolation(interpolation),
		  m_arraySize(arraySize)
	{

	}

	StageInput::StageInput (uint32_t location, Key type, Key name, Key interpolation, int32_t arraySize) noexcept
		: m_location(location),
		  m_type(type),
		  m_name(name),
		  m_interpolation(interpolation),
		  m_arraySize(arraySize)
	{

	}

	bool
	StageInput::isValid () const noexcept
	{
		if ( m_type == nullptr || m_name == nullptr )
			return false;

		return true;
	}

	std::string
	StageInput::sourceCode () const noexcept
	{
		std::stringstream code{};

		code << GLSL::Layout << " (" << GLSL::Location << " = " << m_location << ") ";

		if ( m_interpolation != nullptr )
		{
			code << m_interpolation << ' ';
		}

		code << GLSL::In << ' ' << m_type << ' ' << m_name;

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
	StageInput::name () const noexcept
	{
		return m_name;
	}

	size_t
	StageInput::bytes () const noexcept
	{
		return 0;
	}

	uint32_t
	StageInput::location () const noexcept
	{
		return m_location;
	}

	Key
	StageInput::type () const noexcept
	{
		return m_type;
	}

	Key
	StageInput::interpolation () const noexcept
	{
		return m_interpolation;
	}

	int32_t
	StageInput::arraySize () const noexcept
	{
		return m_arraySize;
	}

	bool
	StageInput::isArray () const noexcept
	{
		return m_arraySize > 0;
	}

	bool
	StageInput::isNonFixedArraySize () const noexcept
	{
		return m_arraySize == -1;
	}
}
