/*
 * Emeraude/Physics/PhysicalEnvironmentProperties.cpp
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

#include "PhysicalEnvironmentProperties.hpp"

namespace Emeraude::Physics
{
	PhysicalEnvironmentProperties::PhysicalEnvironmentProperties (float surfaceGravity, float atmosphericDensity, float planetRadius) noexcept
		: m_surfaceGravity(surfaceGravity), m_atmosphericDensity(atmosphericDensity), m_planetRadius(planetRadius)
	{

	}

	float
	PhysicalEnvironmentProperties::gravity (float /*height*/) const noexcept
	{
		// FIXME: TODO ...

		// gh = g (1 + h/R)–2
		// R is your distance from the center of the Earth
		return m_surfaceGravity;
	}

	float
	PhysicalEnvironmentProperties::atmosphericDensity (float /*height*/, float /*temperature*/) const noexcept
	{
		// FIXME: TODO ...

		return m_atmosphericDensity;
	}

	float
	PhysicalEnvironmentProperties::planetRadius () const noexcept
	{
		return m_planetRadius;
	}
}
