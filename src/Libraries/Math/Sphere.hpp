/*
 * src/Libraries/Math/Sphere.hpp
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
#include <cmath>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

/* Local inclusions for inheritances. */
#include "Shape3DInterface.hpp"

/* Local inclusions for usages. */
#include "Base.hpp"
#include "Vector.hpp"

namespace Libraries::Math
{
	/**
	 * @brief Defines a sphere.
	 * @tparam data_t The type used for geometric distance and dimensions. Default float.
	 * @extends Libraries::Math::Shape3DInterface This is a 3D shape.
	 */
	template< typename data_t = float >
	requires (std::is_arithmetic_v< data_t >)
	class Sphere final : public Shape3DInterface< data_t >
	{
		public:

			/**
			 * @brief Constructs a default sphere.
			 */
			constexpr
			Sphere () noexcept = default;

			/**
			 * @brief Constructs a sphere volume.
			 * @param radius The radius of the sphere.
			 */
			explicit
			constexpr
			Sphere (data_t radius) noexcept
				: m_radius(radius)
			{

			}

			/**
			 * @brief Constructs a sphere volume at a location.
			 * @param radius The radius of the sphere.
			 * @param position A reference to a position vector.
			 */
			constexpr
			Sphere (data_t radius, const Vector< 3, data_t > & position) noexcept
				: m_position(position), m_radius(radius)
			{

			}

			/** @copydoc Libraries::Math::Shape3DInterface::getVolume() */
			[[nodiscard]]
			data_t
			getVolume () const noexcept override
			{
				return sphereVolume(m_radius);
			}

			/**
			 * @brief Sets a position.
			 * @param position A reference to a position vector.
			 * @return void
			 */
			void
			setPosition (const Vector< 3, data_t > & position) noexcept
			{
				m_position = position;
			}

			/**
			 * @brief Returns the position.
			 * @return const Vector< 3, data_t > &
			 */
			[[nodiscard]]
			const Vector< 3, data_t > &
			position () const noexcept
			{
				return m_position;
			}

			/**
			 * @brief Sets the radius of the sphere.
			 * @param radius The radius of the sphere.
			 * @return void
			 */
			void
			setRadius (data_t radius) noexcept
			{
				m_radius = std::abs(radius);
			}

			/**
			 * @brief Returns the radius of the sphere.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			radius () const noexcept
			{
				return m_radius;
			}

			/**
			 * @brief Checks if the sphere volume consistency.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				return m_radius > 0;
			}

			/**
			 * @brief Extends the volume of this sphere with another one.
			 * @param other A reference to a sphere.
			 * @return void
			 */
			void
			merge (const Sphere< data_t > & other) noexcept
			{
				/* If the other sphere is the same or is invalid, we skip it. */
				if ( this == &other || !other.isValid() )
				{
					return;
				}

				/* If THIS sphere is invalid, we simply
				 * copy the other over it. */
				if ( !this->isValid() )
				{
					m_position = other.m_position;
					m_radius = other.m_radius;

					return;
				}

				/* FIXME: Check this algorithm ! */
				const auto delta = Vector< 3, data_t >::distance(m_position, other.m_position) - m_radius - other.m_radius;

				m_position = Vector< 3, data_t >::midPoint(m_position, other.m_position);
				m_radius = (m_radius + other.m_radius) + delta;
			}

			/**
			 * @brief Returns the overlap distance from the intersection with another sphere.
			 * @param other A reference to another sphere.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isCollidingWith (const Sphere & other) const noexcept
			{
				if ( this == &other || !this->isValid() || !other.isValid() )
				{
					return false;
				}

				const auto D = Vector< 3, data_t >::distanceSquared(m_position, other.m_position);
				const auto R2 = std::pow(m_radius + other.m_radius, 2);

				return Sphere::isOverlapping(D, R2);
			}

			/**
			 * @brief Returns the overlap distance from the intersection with a point.
			 * @param point A reference to a vector.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isCollidingWith (const Vector< 3, data_t > & point) const noexcept
			{
				const auto D = Vector< 3, data_t >::distanceSquared(m_position, point);
				const auto R2 = m_radius * m_radius;

				return Sphere::isOverlapping(D, R2);
			}

			/**
			 * @brief Returns the overlap distance from the intersection with a point.
			 * @param point A reference to a vector.
			 * @param useFourthValueAsRadius Set the fourth value of the vector as the radius. Default false.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isCollidingWith (const Vector< 4, data_t > & point, bool useFourthValueAsRadius = false) const noexcept
			{
				if ( useFourthValueAsRadius )
				{
					return this->isCollidingWith(Vector<3, data_t>(point), point[Vector<3, data_t>::W]);
				}

				return this->isCollidingWith(Vector< 3, data_t >(point));
			}

			/**
			 * @brief Returns the overlap distance from the intersection with a point.
			 * @param point A reference to a vector.
			 * @param radius A value for the radius around the point.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isCollidingWith (const Vector< 3, data_t > & point, float radius) const noexcept
			{
				const auto D = Vector< 3, data_t >::distanceSquared(m_position, point);
				const auto R2 = std::pow(m_radius + radius, 2);

				return Sphere::isOverlapping(D, R2);
			}

			/**
			 * @brief Returns whether a point is intersecting this volume.
			 * @param point A reference to a vector.
			 * @param radius A value for the radius around the point.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isCollidingWith (const Vector< 4, data_t > & point, float radius) const noexcept
			{
				return this->isCollidingWith(Vector< 3, data_t >(point), radius);
			}

			/**
			 * @brief Returns the overlap distance from the intersection with another sphere.
			 * @param lhs A reference to a sphere.
			 * @param rhs A reference to a sphere.
			 * @return data_t
			 */
			[[nodiscard]]
			static
			data_t
			getIntersectionOverlap (const Sphere & lhs, const Sphere & rhs) noexcept
			{
				if ( &lhs == &rhs || !lhs.isValid() || !rhs.isValid() )
				{
					return 0;
				}

				const auto distance = Vector< 3, data_t >::distance(lhs.m_position, rhs.m_position);
				const auto radius = lhs.m_radius + rhs.m_radius;

				return Sphere::overlap(distance, radius);
			}

			/**
			 * @brief Returns the overlap distance from the intersection with a point.
			 * @param lhs A reference to a sphere.
			 * @param point A reference to a vector.
			 * @return data_t
			 */
			[[nodiscard]]
			static
			data_t
			getIntersectionOverlap (const Sphere & lhs, const Vector< 3, data_t > & point) noexcept
			{
				const auto distance = Vector< 3, data_t >::distance(lhs.m_position, point);

				return Sphere::overlap(distance, lhs.m_radius);
			}

			/**
			 * @brief Returns the overlap distance from the intersection with a point.
			 * @param lhs A reference to a sphere.
			 * @param point A reference to a vector.
			 * @param radius A value for the radius around the point.
			 * @return data_t
			 */
			[[nodiscard]]
			static
			data_t
			getIntersectionOverlap (const Sphere & lhs, const Vector< 3, data_t > & point, float radius) noexcept
			{
				const auto distance = Vector< 3, data_t >::distance(lhs.m_position, point);
				const auto totalRadius = lhs.m_radius + radius;

				return Sphere::overlap(distance, totalRadius);
			}

			/**
			 * @brief Returns the overlap distance from the intersection with a point.
			 * @param lhs A reference to a sphere.
			 * @param point A reference to a vector.
			 * @param useFourthValueAsRadius Set the fourth value of the vector as the radius. Default false.
			 * @return data_t
			 */
			[[nodiscard]]
			static
			data_t
			getIntersectionOverlap (const Sphere & lhs, const Vector< 4, data_t > & point, bool useFourthValueAsRadius = false) noexcept
			{
				if ( useFourthValueAsRadius )
				{
					return Sphere::getIntersectionOverlap(lhs, Vector<3, data_t>(point), point[Vector<3, data_t>::W]);
				}

				return Sphere::getIntersectionOverlap(lhs, Vector< 3, data_t >(point));
			}

			/**
			 * @brief Returns whether a point is intersecting this volume.
			 * @param lhs A reference to a sphere.
			 * @param point A reference to a vector.
			 * @param radius A value for the radius around the point.
			 * @return data_t
			 */
			[[nodiscard]]
			static
			data_t
			getIntersectionOverlap (const Sphere & lhs, const Vector< 4, data_t > & point, float radius) noexcept
			{
				return Sphere::getIntersectionOverlap(lhs, Vector< 3, data_t >(point), radius);
			}

			/**
			 * @brief Reset the sphere to null value.
			 * @return void
			 */
			void
			reset () noexcept
			{
				m_position.reset();
				m_radius = 0;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Sphere & obj) noexcept
			{
				return out <<
					"Sphere volume data :\n"
					"Position : " << obj.m_position << "\n"
					"Radius : " << obj.m_radius << '\n';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Sphere & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			/**
			 * @brief isOverlapping
			 * @param D
			 * @param R2
			 * @return bool
			 */
			static
			bool
			isOverlapping (data_t D, data_t R2)
			{
				return D < R2;
			}

			/**
			 * @brief overlap
			 * @param D
			 * @param R2
			 * @return data_t
			 */
			static
			data_t
			overlap (data_t D, data_t R2)
			{
				return D < R2 ? R2 - D : 0;
			}

			Vector< 3, data_t > m_position{};
			data_t m_radius{0};
	};
}
