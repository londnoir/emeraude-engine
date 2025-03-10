/*
 * src/Libraries/KVParser/Section.cpp
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

#include "Section.hpp"

/* STL inclusions. */
#include <fstream>
#include <iostream>

namespace Libraries::KVParser
{
	void
	Section::write (std::ofstream & file) const noexcept
	{
		for ( const auto & variable : m_variables )
		{
			file << variable.first << " = " << variable.second.asString() << "\n";
		}
	}

	void
	Section::addVariable (const std::string & key, const Variable & variable) noexcept
	{
		m_variables[key] = variable;
	}

	size_t
	Section::getVariableCount () const noexcept
	{
		return m_variables.size();
	}

	Variable
	Section::variable (const std::string & key) const noexcept
	{
		const auto variableIt = m_variables.find(key);

		if ( variableIt != m_variables.cend() )
		{
			return variableIt->second;
		}

		return {};
	}
}
