/*
 * src/Saphir/Declaration/Structure.cpp
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

#include "Structure.hpp"

/* STL inclusions. */
#include <sstream>

/* Local inclusions. */
#include "Libraries/Utility.hpp"
#include "Tracer.hpp"

namespace Emeraude::Saphir::Declaration
{
	using namespace Libraries;
	using namespace Keys;

	Structure::Structure (Key name, Key instanceName) noexcept
		: m_name(name), m_instanceName(instanceName)
	{

	}

	bool
	Structure::isValid () const noexcept
	{
		if ( m_name == nullptr )
			return false;

		if ( m_members.empty() )
			return false;

		return true;
	}

	Key
	Structure::name () const noexcept
	{
		return m_name;
	}

	size_t
	Structure::bytes () const noexcept
	{
		return 0;
	}

	const std::string &
	Structure::instanceName () const noexcept
	{
		return m_instanceName;
	}

	const std::vector< std::pair< Key, Member::Structure > > &
	Structure::members () const noexcept
	{
		return m_members;
	}

	bool
	Structure::addMember (VariableType type, Key name) noexcept
	{
		if ( Utility::contains(m_members, name) )
		{
			TraceError{ClassId} << "This structure has already a member named '" << name << "' !";

			return false;
		}

		m_members.emplace_back(
			std::piecewise_construct,
			std::forward_as_tuple(name),
			std::forward_as_tuple(type, name)
		);

		return true;
	}

	std::string
	Structure::sourceCode () const noexcept
	{
		std::stringstream code{};

		code << GLSL::Struct << ' ' << m_name << "\n" "{" "\n";

		for ( const auto & variable : m_members )
		{
			code << '\t' << variable.second.sourceCode() << '\n';
		}

		code << '}';

		if ( !m_instanceName.empty() )
		{
			code << ' ' << m_instanceName;
		}

		code << ";" "\n";

		return code.str();
	}
}
