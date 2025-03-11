/*
 * src/Physics/PhysicalEnvironmentProperties.cpp
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

#include "PhysicalEnvironmentProperties.hpp"

namespace EmEn::Physics
{
	PhysicalEnvironmentProperties::PhysicalEnvironmentProperties (float surfaceGravity, float atmosphericDensity, float planetRadius) noexcept
		: m_surfaceGravity(surfaceGravity),
		m_steppedSurfaceGravity(surfaceGravity * EngineUpdateCycleDurationS< float >),
		m_atmosphericDensity(atmosphericDensity),
		m_planetRadius(planetRadius)
	{

	}

	std::ostream &
	operator<< (std::ostream & out, const PhysicalEnvironmentProperties & obj)
	{
		return out <<
			"Physical environment properties :" "\n"
			"Surface gravity : " << obj.m_surfaceGravity << " m/s² (" << obj.m_steppedSurfaceGravity << " m/s² per update)" "\n"
			"Atmospheric density : " << obj.m_atmosphericDensity << " kg/m³" "\n"
			"Planet radius : " << obj.m_planetRadius << " m" "\n";
	}

	std::string
	to_string (const PhysicalEnvironmentProperties & obj) noexcept
	{
		std::stringstream output;

		output << obj;

		return output.str();
	}
}
