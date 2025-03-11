/*
 * src/Saphir/StaticLighting.cpp
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

#include "StaticLighting.hpp"

/* STL inclusions. */
#include <sstream>

namespace EmEn::Saphir
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::Math;
	using namespace EmEn::Libs::PixelFactory;

	std::string
	StaticLighting::positionVec3 () const noexcept
	{
		std::stringstream output;
		output << "vec3(" << m_position[X] << ", " << m_position[Y] << ", " << m_position[Z] << ")";

		return output.str();
	}

	std::string
	StaticLighting::positionVec4 () const noexcept
	{
		std::stringstream output;
		output << "vec4(" << m_position[X] << ", " << m_position[Y] << ", " << m_position[Z] << ", 1.0)";
		
		return output.str();
	}

	std::string
	StaticLighting::directionVec3 () const noexcept
	{
		std::stringstream output;
		output << "vec3(" << m_direction[X] << ", " << m_direction[Y] << ", " << m_direction[Z] << ")";
		
		return output.str();
	}

	std::string
	StaticLighting::directionVec4 () const noexcept
	{
		std::stringstream output;
		output << "vec4(" << m_direction[X] << ", " << m_direction[Y] << ", " << m_direction[Z] << ", 0.0)";
		
		return output.str();
	}

	std::string
	StaticLighting::ambientColorVec4 () const noexcept
	{
		std::stringstream output;
		output << "vec4(" << m_ambientColor.red() << ", " << m_ambientColor.green() << ", " << m_ambientColor.blue() << ", 1.0)";
		
		return output.str();
	}

	std::string
	StaticLighting::colorVec4 () const noexcept
	{
		std::stringstream output;
		output << "vec4(" << m_color.red() << ", " << m_color.green() << ", " << m_color.blue() << ", 1.0)";
		
		return output.str();
	}

	std::ostream &
	operator<< (std::ostream & out, const StaticLighting & obj)
	{
		return out <<
			"Static lighting data:" "\n"
			"Type: " << to_string(obj.m_type) << "\n"
			"Position (Spot & Point): " << obj.m_position << "\n"
			"Direction (Directional & Spot): " << obj.m_direction << "\n"
			"Ambient color: " << obj.m_ambientColor << "\n"
			"Light color: " << obj.m_color << "\n"
			"Ambient intensity: " << obj.m_ambientIntensity << "\n"
			"Light intensity: " << obj.m_intensity << "\n"
			"Radius (Spot & Point): " << obj.m_radius << "\n"
			"Inner cosine angle (Spot): " << obj.m_innerCosAngle << "\n"
			"Outer cosine angler (Spot): " << obj.m_outerCosAngle << "\n";
	}

	std::string
	to_string (const StaticLighting & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
