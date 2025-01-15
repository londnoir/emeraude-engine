/*
 * src/Graphics/Material/Component/Value.cpp
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

#include "Value.hpp"

namespace Emeraude::Graphics::Material::Component
{
	Value::Value (std::string variableName) noexcept
		: m_variableName(std::move(variableName))
	{

	}

	std::ostream &
	operator<< (std::ostream & out, const Value & obj)
	{
		return out << Value::ClassId << "." "\n"
			"Variable name: " << obj.m_variableName;
	}

	std::string
	to_string (const Value & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
