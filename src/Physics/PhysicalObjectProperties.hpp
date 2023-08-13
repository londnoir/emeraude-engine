/*
 * Emeraude/Physics/PhysicalObjectProperties.hpp
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

#pragma once

/* C/C++ standard libraries */
#include <string>
#include <sstream>
#include <iostream>

/* Local inclusions for inheritances. */
#include "Observable.hpp"

/* Local inclusions for usages. */
#include "Math/Base.hpp"
#include "Physics.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/json.hpp"

namespace Emeraude::Physics
{
	/**
	 * @brief Class defining physical properties of an object.
	 * @extends Libraries::Observable This notifies each physical property changes.
	 */
	class PhysicalObjectProperties final : public Libraries::Observable
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PhysicalObjectProperties"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/* JSON keys */
			static constexpr auto MassKey = "Mass";
			static constexpr auto SurfaceKey = "Surface";
			static constexpr auto DragCoefficientKey = "DragCoefficient";
			static constexpr auto BouncinessKey = "Bounciness";
			static constexpr auto StickinessKey = "Stickiness";

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
			 * @brief Constructs a physical properties collection.
			 * @param mass The mass in kilograms. Default: 0.
			 * @param surface The average surface in squared meters. Default: 0.
			 * @param dragCoefficient The drag coefficient. Default: 0.
			 * @param bounciness A scalar of the bounciness of the object when hitting something. Default:  0.5.
			 * @param stickiness A scalar of the stickiness of the object when hitting something. Default: 0.5.
			 */
			explicit PhysicalObjectProperties (float mass = 0.0F, float surface = 0.0F, float dragCoefficient = 0.0F, float bounciness = 0.5F, float stickiness = 0.5F) noexcept; // NOLINT(*-magic-numbers)

			/** @copydoc Libraries::Observable::is() */
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
			float mass () const noexcept;

			/**
			 * @brief Returns the inverse of the mass of the object.
			 * @note This value is precomputed from mass.
			 * @return float
			 */
			[[nodiscard]]
			float inverseMass () const noexcept;

			/**
			 * @brief Returns whether the mass is null.
			 * @return bool
			 */
			[[nodiscard]]
			bool isMassNull () const noexcept;

			/**
			 * @brief Sets the surface of the object in squared meters.
			 * @note This should be an approximation of average surface.
			 * @param value The surface in squared meters.
			 * @param fireEvents Controls whether event are fired or not when setting the property. Default true.
			 * @return bool
			 */
			bool setSurface (float value, bool fireEvents = true) noexcept;

			/**
			 * @brief Returns the surface of the object in squared meters.
			 * @return float
			 */
			[[nodiscard]]
			float surface () const noexcept;

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
			float dragCoefficient () const noexcept;

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
			float bounciness () const noexcept;

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
			float stickiness () const noexcept;

			/**
			 * @brief Sets physical properties at once.
			 * @param mass The mass in kilograms.
			 * @param surface The average surface in squared meters.
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
			 * @param data A reference to an other properties.
			 * @return bool
			 */
			inline
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
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const PhysicalObjectProperties & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const PhysicalObjectProperties & obj) noexcept;

		private:

			float m_mass;
			float m_inverseMass;
			float m_surface;
			float m_dragCoefficient;
			float m_bounciness;
			float m_stickiness;
	};
}
