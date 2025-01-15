/*
 * src/Saphir/Declaration/SpecializationConstant.cpp
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

#include "SpecializationConstant.hpp"

/* STL inclusions. */
#include <sstream>

namespace Emeraude::Saphir::Declaration
{
	using namespace Keys;

	SpecializationConstant::SpecializationConstant (Key type, Key name, uint32_t constantId, std::string defaultValue) noexcept
		: m_type(type), m_name(name), m_constantId(constantId), m_defaultValue(std::move(defaultValue))
	{

	}

	bool
	SpecializationConstant::isValid () const noexcept
	{
		if ( m_type == nullptr || m_name == nullptr )
			return false;

		return true;
	}

	Key
	SpecializationConstant::name () const noexcept
	{
		return m_name;
	}

	size_t
	SpecializationConstant::bytes () const noexcept
	{
		return 0;
	}

	Key
	SpecializationConstant::type () const noexcept
	{
		return m_type;
	}

	uint32_t
	SpecializationConstant::constantId () const noexcept
	{
		return m_constantId;
	}

	const std::string &
	SpecializationConstant::defaultValue () const noexcept
	{
		return m_defaultValue;
	}

	std::string
	SpecializationConstant::sourceCode () const noexcept
	{
		std::stringstream code{};

		code <<
			GLSL::Layout << "(" << GLSL::ConstantId << " = " << m_constantId << ")" << ' ' <<
			GLSL::Const << ' ' << m_type << ' ' << m_name << " = " << m_defaultValue << ";" "\n";

		return code.str();
	}
}
