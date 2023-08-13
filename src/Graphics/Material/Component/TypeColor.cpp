/*
 * Emeraude/Graphics/Material/Component/TypeColor.cpp
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

#include "TypeColor.hpp"

/* Local inclusions. */
#include "Tracer.hpp"

namespace Emeraude::Graphics::Material::Component
{
	using namespace Libraries;
	using namespace Libraries::PixelFactory;

	TypeColor::TypeColor (const std::string & variableName, const Color< float > & color) noexcept
		: m_variableName(variableName), m_color(color)
	{

	}

	TypeColor::TypeColor (const std::string & variableName, const Json::Value & data) noexcept
		: m_variableName(variableName)
	{
		if ( !data.isArray() || data.size() < 3 )
		{
			Tracer::error(ClassId, "Json value is not an array or invalid !");

			return;
		}

		std::array< float, 4 > colorData{0.0F, 0.0F, 0.0F, 1.0F};

		for ( uint32_t index = 0; index < std::min(4U, data.size()); index++ )
		{
			auto & colorComponent = data[index];

			if ( !colorComponent.isNumeric() )
			{
				TraceError{ClassId} << "Json array #" << index << " value is not numeric !";

				break;
			}

			colorData[index] = colorComponent.asFloat();
		}

		m_color = Color{colorData};
	}

	bool
	TypeColor::create () noexcept
	{
		return true;
	}

	bool
	TypeColor::isCreated () const noexcept
	{
		return true;
	}

	const std::string &
	TypeColor::variableName () const noexcept
	{
		return m_variableName;
	}

	Type
	TypeColor::type () const noexcept
	{
		return Type::Color;
	}

	bool
	TypeColor::isOpaque () const noexcept
	{
		return m_color.alpha() >= 1.0F;
	}

	void
	TypeColor::setColor (const Color< float > & color) noexcept
	{
		m_color = color;
	}

	const Color< float > &
	TypeColor::color () const noexcept
	{
		return m_color;
	}

	Color< float > &
	TypeColor::color () noexcept
	{
		return m_color;
	}

	void
	TypeColor::setOpacity (float value) noexcept
	{
		m_color.setAlpha(value);
	}

	float
	TypeColor::opacity () const noexcept
	{
		return m_color.alpha();
	}

	std::ostream &
	operator<< (std::ostream & out, const TypeColor & obj)
	{
		return out << obj.ClassId << "." "\n"
			"Variable name: " << obj.m_variableName << "\n"
			"Color: " << obj.m_color;
	}

	std::string
	to_string (const TypeColor & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
