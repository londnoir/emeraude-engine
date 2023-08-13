/*
 * Emeraude/Graphics/Material/Component/TypeValue.cpp
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

#include "TypeValue.hpp"

/* Local inclusions. */
#include "Tracer.hpp"

namespace Emeraude::Graphics::Material::Component
{
	TypeValue::TypeValue (const std::string & variableName, float value) noexcept
		: m_variableName(variableName), m_value(value)
	{

	}

	TypeValue::TypeValue (const std::string & variableName, const Json::Value & data) noexcept
		: m_variableName(variableName)
	{
		if ( !data.isNumeric() )
		{
			Tracer::error(ClassId, "Json value is not numeric !");

			return;
		}

		m_value = data.asFloat();
	}

	bool
	TypeValue::create () noexcept
	{
		return true;
	}

	bool
	TypeValue::isCreated () const noexcept
	{
		return true;
	}

	const std::string &
	TypeValue::variableName () const noexcept
	{
		return m_variableName;
	}

	Type
	TypeValue::type () const noexcept
	{
		return Type::Value;
	}

	bool
	TypeValue::isOpaque () const noexcept
	{
		return true;
	}

	void
	TypeValue::setValue (float value) noexcept
	{
		m_value = value;
	}

	float
	TypeValue::value () const noexcept
	{
		return m_value;
	}

	std::ostream &
	operator<< (std::ostream & out, const TypeValue & obj)
	{
		return out << obj.ClassId << "." "\n"
			"Variable name: " << obj.m_variableName << "\n"
			"Value: " << obj.m_value;
	}

	std::string
	to_string (const TypeValue & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
