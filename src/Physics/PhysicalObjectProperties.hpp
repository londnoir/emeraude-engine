/*
 * src/Physics/PhysicalObjectProperties.hpp
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

#pragma once

/* STL inclusions. */
#include <cstddef>
#include <ostream>
#include <string>

/* Third-party inclusions. */
#ifndef JSON_USE_EXCEPTION
#define JSON_USE_EXCEPTION 0
#endif
#include "json/json.h"

/* Local inclusions for inheritances. */
#include "Libraries/ObservableTrait.hpp"

/* Local inclusions for usages. */
#include "Physics.hpp"

namespace Emeraude::Physics
{
	/**
	 * @brief Class defining physical properties of an object.
	 * Libraries::ObservableTrait This notifies each physical property changes.
	 */
	class PhysicalObjectProperties final : public Libraries::ObservableTrait
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PhysicalObjectProperties"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* JSON keys */
			static constexpr auto MassKey{"Mass"};
			static constexpr auto SurfaceKey{"Surface"};
			static constexpr auto DragCoefficientKey{"DragCoefficient"};
			static constexpr auto BouncinessKey{"Bounciness"};
			static constexpr auto StickinessKey{"Stickiness"};

			/* Variables defaults. */
			static constexpr auto DefaultMass{0.0F};
			static constexpr auto DefaultSurface{0.0F};
			static constexpr auto DefaultDragCoefficient{DragCoefficient::Sphere< float >};
			static constexpr auto DefaultBounciness{0.5F};
			static constexpr auto DefaultStickiness{0.5F};

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				MassChanged,
				SurfaceChanged,
				DragCoefficientChanged,
				BouncinessChanged,
				StickinessChanged,
				PropertiesChanged,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Constructs a default physical properties collection.
			 */
			PhysicalObjectProperties () noexcept = default;

			/**
			 * @brief Constructs a physical property collection.
			 * @param mass The mass in kilograms.
			 * @param surface The average surface in square meters.
			 * @param dragCoefficient The drag coefficient.
			 * @param bounciness A scalar of the bounciness of the object when hitting something. Default 50%.
			 * @param stickiness A scalar of the stickiness of the object when hitting something. Default 50%.
			 */
			explicit PhysicalObjectProperties (float mass, float surface, float dragCoefficient, float bounciness = DefaultBounciness, float stickiness = DefaultStickiness) noexcept;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t classUID () const noexcept override;

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/**
			 * @brief Sets the mass of the object.
			 * @param value The mass in kilograms.
			 * @param fireEvents Controls whether event are fired or not when setting the property. Default true.
			 * @return bool
			 */
			bool setMass (float value, bool fireEvents = true) noexcept;

			/**
			 * @brief Returns the mass of the object in kilograms.
			 * @return float
			 */
			[[nodiscard]]
			float
			mass () const noexcept
			{
				return m_mass;
			}

			/**
			 * @brief Returns the inverse of the mass of the object.
			 * @note This value is precomputed from mass.
			 * @return float
			 */
			[[nodiscard]]
			float
			inverseMass () const noexcept
			{
				return m_inverseMass;
			}

			/**
			 * @brief Returns whether the mass is null.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isMassNull () const noexcept
			{
				return m_mass <= 0.0F;
			}

			/**
			 * @brief Sets the surface of the object in square meters.
			 * @note This should be an approximation of average surface.
			 * @param value The surface in square meters.
			 * @param fireEvents Controls whether event are fired or not when setting the property. Default true.
			 * @return bool
			 */
			bool setSurface (float value, bool fireEvents = true) noexcept;

			/**
			 * @brief Returns the surface of the object in square meters.
			 * @return float
			 */
			[[nodiscard]]
			float
			surface () const noexcept
			{
				return m_surface;
			}

			/**
			 * @brief Sets the drag coefficient of the object.
			 * @note Use constants from Emeraude::Physics::DragCoefficient namespace.
			 * @param value The coefficient.
			 * @param fireEvents Controls whether event are fired or not when setting the property. Default true.
			 * @return bool
			 */
			bool setDragCoefficient (float value, bool fireEvents = true) noexcept;

			/**
			 * @brief Returns the drag coefficient of the object.
			 * @return float
			 */
			[[nodiscard]]
			float
			dragCoefficient () const noexcept
			{
				return m_dragCoefficient;
			}

			/**
			 * @brief Sets the bounciness of the object when hitting something.
			 * @param value A scalar clamped from 0.0 to 1.0.
			 * @param fireEvents Controls whether event are fired or not when setting the property. Default true.
			 * @return bool
			 */
			bool setBounciness (float value, bool fireEvents = true) noexcept;

			/**
			 * @brief Returns the bounciness of the object.
			 * @return float
			 */
			[[nodiscard]]
			float
			bounciness () const noexcept
			{
				return m_bounciness;
			}

			/**
			 * @brief Sets the stickiness of the object when hitting something.
			 * @param value A scalar clamped from 0.0 to 1.0.
			 * @param fireEvents Controls whether event are fired or not when setting the property. Default true.
			 * @return bool
			 */
			bool setStickiness (float value, bool fireEvents = true) noexcept;

			/**
			 * @brief Returns the stickiness of the object.
			 * @return float
			 */
			[[nodiscard]]
			float
			stickiness () const noexcept
			{
				return m_stickiness;
			}

			/**
			 * @brief Sets physical properties at once.
			 * @param mass The mass in kilograms.
			 * @param surface The average surface in square meters.
			 * @param dragCoefficient The drag coefficient.
			 * @param bounciness A scalar of the bounciness of the object when hitting something.
			 * @param stickiness A scalar of the stickiness of the object when hitting something.
			 * @return bool
			 */
			bool setProperties (float mass, float surface, float dragCoefficient, float bounciness, float stickiness) noexcept;

			/**
			 * @brief Sets physical properties at once from JSON data.
			 * @param data A reference to a JSON value.
			 * @return bool
			 */
			bool setProperties (const Json::Value & data) noexcept;

			/**
			 * @brief Sets physical properties at once from another one.
			 * @param other A reference to another properties.
			 * @return bool
			 */
			bool
			setProperties (const PhysicalObjectProperties & other) noexcept
			{
				return this->setProperties(other.m_mass, other.m_surface, other.m_dragCoefficient, other.m_bounciness, other.m_stickiness);
			}

			/**
			 * @brief Merges physical properties. Mass will be summed, the bigger surface will be kept and the drag coefficient, bounciness and stickiness will be averaged.
			 * @warning  This is an approximation method.
			 * @note This method do not trigger any notification.
			 * @param other A reference to PhysicalProperties.
			 */
			void merge (const PhysicalObjectProperties & other) noexcept;

			/** @brief Resets properties to zero. */
			void reset () noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const PhysicalObjectProperties & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const PhysicalObjectProperties & obj) noexcept;

		private:

			float m_mass{DefaultMass};
			float m_inverseMass{0.0F};
			float m_surface{DefaultSurface};
			float m_dragCoefficient{DefaultDragCoefficient};
			float m_bounciness{DefaultBounciness};
			float m_stickiness{DefaultStickiness};
	};
}
