/*
 * src/Saphir/Declaration/OutputFragment.cpp
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

#include "OutputFragment.hpp"

/* Local inclusions. */
#include <sstream>

namespace Emeraude::Saphir::Declaration
{
	using namespace Keys;

	OutputFragment::OutputFragment (uint32_t location, Key type, Key name) noexcept
		: m_location(location), m_type(type), m_name(name)
	{

	}

	bool
	OutputFragment::isValid () const noexcept
	{
		if ( m_type == nullptr || m_name == nullptr )
			return false;

		return true;
	}

	std::string
	OutputFragment::sourceCode () const noexcept
	{
		return (std::stringstream{} <<
			GLSL::Layout << " (" << GLSL::Location << " = " << std::to_string(m_location) << ") " <<
			GLSL::Out << ' ' << m_type << ' ' << m_name << ";" "\n"
		).str();
	}

	Key
	OutputFragment::name () const noexcept
	{
		return m_name;
	}

	size_t
	OutputFragment::bytes () const noexcept
	{
		return 0;
	}

	uint32_t
	OutputFragment::location () const noexcept
	{
		return m_location;
	}

	Key
	OutputFragment::type () const noexcept
	{
		return m_type;
	}
}
