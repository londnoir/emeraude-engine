/*
 * Emeraude/Physics/PhysicalObjectProperties.cpp
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

#include "PhysicalObjectProperties.hpp"

/* C/C++ standard libraries. */
#include <sstream>

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude::Physics
{
	using namespace Libraries;
	using namespace Libraries::Math;

	const size_t PhysicalObjectProperties::ClassUID{Observable::getClassUID()};

	PhysicalObjectProperties::PhysicalObjectProperties (float mass, float surface, float dragCoefficient, float bounciness, float stickiness) noexcept
		: m_mass(mass), m_inverseMass(1.0F / m_mass), m_surface(surface), m_dragCoefficient(dragCoefficient), m_bounciness(bounciness), m_stickiness(stickiness)
	{

	}

	bool
	PhysicalObjectProperties::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	PhysicalObjectProperties::setMass (float value, bool fireEvents) noexcept
	{
		if ( value < 0.0F )
		{
			Tracer::warning(ClassId, "Mass can't be negative !");

			return false;
		}

		if ( value == m_mass )
		{
			return false;
		}

		m_mass = value;
		m_inverseMass = 1.0F / m_mass;

		if ( fireEvents )
		{
			this->notify(MassChanged, m_mass);
			this->notify(PropertiesChanged);
		}

		return true;
	}

	float
	PhysicalObjectProperties::mass () const noexcept
	{
		return m_mass;
	}

	float
	PhysicalObjectProperties::inverseMass () const noexcept
	{
		return m_inverseMass;
	}

	bool
	PhysicalObjectProperties::isMassNull () const noexcept
	{
		return m_mass <= 0.0F;
	}

	bool
	PhysicalObjectProperties::setSurface (float value, bool fireEvents) noexcept
	{
		if ( value < 0.0F )
		{
			Tracer::warning(ClassId, "Surface can't be negative !");

			return false;
		}

		if ( value == m_surface )
		{
			return false;
		}

		m_surface = value;

		if ( fireEvents )
		{
			this->notify(SurfaceChanged, m_surface);
			this->notify(PropertiesChanged);
		}

		return true;
	}

	float
	PhysicalObjectProperties::surface () const noexcept
	{
		return m_surface;
	}

	bool
	PhysicalObjectProperties::setDragCoefficient (float value, bool fireEvents) noexcept
	{
		if ( value < 0.0F )
		{
			Tracer::warning(ClassId, "Drag coefficient can't be negative.");

			return false;
		}

		if ( value == m_dragCoefficient )
		{
			return false;
		}

		m_dragCoefficient = value;

		if ( fireEvents )
		{
			this->notify(DragCoefficientChanged, m_dragCoefficient);
			this->notify(PropertiesChanged);
		}

		return true;
	}

	float
	PhysicalObjectProperties::dragCoefficient () const noexcept
	{
		return m_dragCoefficient;
	}

	bool
	PhysicalObjectProperties::setBounciness (float value, bool fireEvents) noexcept
	{
		if ( value < 0.0F || value > 1.0F )
		{
			Tracer::warning(ClassId, "Bounciness must be a scalar value [0.0 -> 1.0].");

			return false;
		}

		if ( value == m_bounciness )
		{
			return false;
		}

		m_bounciness = clampToUnit(value);

		if ( fireEvents )
		{
			this->notify(BouncinessChanged, m_bounciness);
			this->notify(PropertiesChanged);
		}

		return true;
	}

	float
	PhysicalObjectProperties::bounciness () const noexcept
	{
		return m_bounciness;
	}

	bool
	PhysicalObjectProperties::setStickiness (float value, bool fireEvents) noexcept
	{
		if ( value < 0.0F || value > 1.0F )
		{
			Tracer::warning(ClassId, "Stickiness must be a scalar value [0.0 -> 1.0].");

			return false;
		}

		if ( value == m_stickiness )
		{
			return false;
		}

		m_stickiness = value;

		if ( fireEvents )
		{
			this->notify(StickinessChanged, m_stickiness);
			this->notify(PropertiesChanged);
		}

		return true;
	}

	float
	PhysicalObjectProperties::stickiness () const noexcept
	{
		return m_stickiness;
	}

	bool
	PhysicalObjectProperties::setProperties (float mass, float surface, float dragCoefficient, float bounciness, float stickiness) noexcept
	{
		auto changes = false;

		if ( this->setMass(mass, false) )
		{
			this->notify(MassChanged, m_mass);

			changes = true;
		}

		if ( this->setSurface(surface, false) )
		{
			this->notify(SurfaceChanged, m_surface);

			changes = true;
		}

		if ( this->setDragCoefficient(dragCoefficient, false) )
		{
			this->notify(DragCoefficientChanged, m_dragCoefficient);

			changes = true;
		}

		if ( this->setBounciness(bounciness, false) )
		{
			this->notify(BouncinessChanged, m_bounciness);

			changes = true;
		}

		if ( this->setStickiness(stickiness, false) )
		{
			this->notify(StickinessChanged, m_stickiness);

			changes = true;
		}

		if ( changes )
		{
			this->notify(PropertiesChanged);
		}

		return changes;
	}

	bool
	PhysicalObjectProperties::setProperties (const Json::Value & data) noexcept
	{
		struct property {
			const char * jsonKey = nullptr;
			bool (PhysicalObjectProperties::* method)(float, bool) = nullptr;
			int notificationCode = std::numeric_limits< int >::max();
		};

		const std::array< property, 5 > properties{{
			{MassKey, &PhysicalObjectProperties::setMass, MassChanged},
			{SurfaceKey, &PhysicalObjectProperties::setSurface, SurfaceChanged},
			{DragCoefficientKey, &PhysicalObjectProperties::setDragCoefficient, DragCoefficientChanged},
			{BouncinessKey, &PhysicalObjectProperties::setBounciness, BouncinessChanged},
			{StickinessKey, &PhysicalObjectProperties::setStickiness, StickinessChanged}
		}};

		auto changes = false;

		for ( const auto & property : properties )
		{
			/* Not present in the JSON. */
			if ( !data.isMember(property.jsonKey) )
			{
				continue;
			}

			/* Checking the value type and pop an error on bad one. */
			if ( !data[property.jsonKey].isNumeric() )
			{
				Tracer::error(ClassId, Blob() << '\'' << property.jsonKey << "' key must be a floating number !");

				continue;
			}

			/* Set the value, if changes prepares to declaring it as event. */
			const auto value = data[property.jsonKey].asFloat();

			if ( !(this->*property.method)(value, false) )
			{
				continue;
			}

			this->notify(property.notificationCode, value);

			changes = true;
		}

		if ( changes )
		{
			this->notify(PropertiesChanged);
		}

		return changes;
	}

	void
	PhysicalObjectProperties::merge (const PhysicalObjectProperties & other) noexcept
	{
		m_mass += other.m_mass;
		m_inverseMass = 1.0F / m_mass;
		if ( other.m_surface > m_surface )
		{
			m_surface = other.m_surface;
		}
		m_dragCoefficient = (m_dragCoefficient + other.m_dragCoefficient) * 0.5F;
		m_bounciness = (m_bounciness + other.m_bounciness) * 0.5F;
		m_stickiness = (m_stickiness + other.m_stickiness) * 0.5F;
	}

	void
	PhysicalObjectProperties::reset () noexcept
	{
		m_mass = 0.0F;
		m_inverseMass = 0.0F;
		m_surface = 0.0F;
		m_dragCoefficient = DragCoefficient::Sphere< float >;
		m_bounciness = 0.5F;
		m_stickiness = 0.5F;
	}

	std::ostream &
	operator<< (std::ostream & out, const PhysicalObjectProperties & obj)
	{
		return out <<
			"Mass : " << obj.m_mass << " Kg (Inverse: " << obj.m_inverseMass << ")" << '\n' <<
			"Surface : " << obj.m_surface << " m²" << '\n' <<
			"Drag Coefficient : " << obj.m_dragCoefficient << '\n' <<
			"Bounciness : " << obj.m_bounciness << '\n' <<
			"Stickiness : " << obj.m_stickiness << '\n';
	}

	std::string
	to_string (const PhysicalObjectProperties & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
