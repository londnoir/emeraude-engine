/*
 * src/Libs/Math/Cuboid.hpp
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
#include <cstddef>
#include <limits>
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

/* Local inclusions for inheritances. */
#include "Shape3DInterface.hpp"

/* Local inclusions for usages. */
#include "Sphere.hpp"
#include "Vector.hpp"

namespace EmEn::Libs::Math
{
	/**
	 * @brief Defines a cubic volume aligned on axis.
	 * @tparam data_t The type used for geometric distance and dimensions. Default float.
	 * @extends EmEn::Libs::Math::Shape3DInterface This is a 3D shape.
	 */
	template< typename data_t = float >
	requires (std::is_arithmetic_v< data_t >)
	class Cuboid : public Shape3DInterface< data_t >
	{
		public:

			/**
			 * @brief Construct a cuboid.
			 */
			constexpr
			Cuboid () noexcept = default;

			/**
			 * @brief Constructs a uniform axis aligned bounding box.
			 * @param value The maximal value in every direction.
			 */
			explicit
			constexpr
			Cuboid (data_t value) noexcept
				: m_maximum(value, value, value), m_minimum(-value, -value, -value)
			{

			}

			/**
			 * @brief Constructs an axis aligned bounding box.
			 * @param maximum The highest positive XYZ coordinates of the box.
			 * @param minimum The lowest negative XYZ coordinates of the box.
			 */
			constexpr
			Cuboid (const Vector< 3, data_t > & maximum, const Vector< 3, data_t > & minimum) noexcept
				: m_maximum(maximum), m_minimum(minimum)
			{

			}

			/**
			 * @brief Extends the volume of this box with another one.
			 * @param other A reference to another cuboid.
			 * @return Cuboid< type_t >
			 */
			Cuboid< data_t >
			operator+ (const Cuboid< data_t > & other) const noexcept
			{
				if ( !this->isValid() )
				{
					return other;
				}

				if ( !other.isValid() )
				{
					return *this;
				}

				return {m_maximum + other.m_maximum, m_minimum + other.m_minimum};
			}

			/**
			 * @brief Extends the volume of this box with another one.
			 * @param operand A reference to a cuboid.
			 * @return Cuboid< type_t >
			 */
			Cuboid< data_t > &
			operator+= (const Cuboid< data_t > & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					if ( operand.isValid() )
					{
						if ( this->isValid() )
						{
							m_maximum += operand.m_maximum;
							m_minimum += operand.m_minimum;
						}
						else
						{
							m_maximum = operand.m_maximum;
							m_minimum = operand.m_minimum;
						}
					}
				}

				return *this;
			}

			/**
			 * @brief Reduces the volume of this box with another one.
			 * @warning  This can lead to an invalid volume.
			 * @param other A reference to another cuboid.
			 * @return Cuboid< type_t >
			 */
			Cuboid< data_t >
			operator- (const Cuboid< data_t > & other) const noexcept
			{
				if ( !this->isValid() )
				{
					return other;
				}

				if ( !other.isValid() )
				{
					return *this;
				}

				return {m_maximum - other.m_maximum, m_minimum - other.m_minimum};
			}

			/**
			 * @brief Reduces the volume of this box with another one.
			 * @warning  This can lead to an invalid volume.
			 * @param operand A reference to a cuboid.
			 * @return Cuboid< type_t > &
			 */
			Cuboid< data_t > &
			operator-= (const Cuboid< data_t > & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					if ( this->isValid() && operand.isValid() )
					{
						m_maximum -= operand.m_maximum;
						m_minimum -= operand.m_minimum;
					}
				}

				return *this;
			}

			/** @copydoc EmEn::Libs::Math::Shape3DInterface::getVolume() */
			[[nodiscard]]
			data_t
			getVolume () const noexcept override
			{
				return this->width() * this->height() * this->depth();
			}

			/**
			 * @brief Sets the absolute volume of the box from its center.
			 * @param value The maximal value in every direction.
			 * @return void
			 */
			void
			set (data_t value)
			{
				m_maximum[X] = value;
				m_maximum[Y] = value;
				m_maximum[Z] = value;

				m_minimum[X] = -value;
				m_minimum[Y] = -value;
				m_minimum[Z] = -value;
			}

			/**
			 * @brief Sets the volume of the box.
			 * @param maximum The highest positive XYZ coordinates of the box.
			 * @param minimum The lowest negative XYZ coordinates of the box.
			 * @return void
			 */
			void
			set (const Vector< 3, data_t > & maximum, const Vector< 3, data_t > & minimum) noexcept
			{
				if ( maximum[X] >= minimum[X] )
				{
					m_maximum[X] = maximum[X];
					m_minimum[X] = minimum[X];
				}
				else
				{
					m_maximum[X] = minimum[X];
					m_minimum[X] = maximum[X];
				}

				if ( maximum[Y] >= minimum[Y] )
				{
					m_maximum[Y] = maximum[Y];
					m_minimum[Y] = minimum[Y];
				}
				else
				{
					m_maximum[Y] = minimum[Y];
					m_minimum[Y] = maximum[Y];
				}

				if ( maximum[Z] >= minimum[Z] )
				{
					m_maximum[Z] = maximum[Z];
					m_minimum[Z] = minimum[Z];
				}
				else
				{
					m_maximum[Z] = minimum[Z];
					m_minimum[Z] = maximum[Z];
				}
			}

			/**
			 * @brief Checks if the box volume consistency.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				if ( m_maximum[X] <= m_minimum[X] )
				{
					return false;
				}

				if ( m_maximum[Y] <= m_minimum[Y] )
				{
					return false;
				}

				if ( m_maximum[Z] <= m_minimum[Z] )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief Returns the highest positive XYZ coordinates of the box.
			 * @return Vector3
			 */
			[[nodiscard]]
			const Vector< 3, data_t > &
			maximum () const noexcept
			{
				return m_maximum;
			}

			/**
			 * @brief Returns the highest positive coordinates of the box on one axis.
			 * @return type_t
			 */
			[[nodiscard]]
			data_t
			maximum (size_t index) const noexcept
			{
				return m_maximum[index];
			}

			/**
			 * @brief Returns the lowest negative XYZ coordinates of the box.
			 * @return Vector3
			 */
			[[nodiscard]]
			const Vector< 3, data_t > &
			minimum () const noexcept
			{
				return m_minimum;
			}

			/**
			 * @brief Returns the highest lowest negative coordinates of the box on one axis.
			 * @return type_t
			 */
			[[nodiscard]]
			data_t
			minimum (size_t index) const noexcept
			{
				return m_minimum[index];
			}

			/**
			 * @brief Returns the width of the box (X axis).
			 * @return type_t
			 */
			[[nodiscard]]
			data_t
			width () const noexcept
			{
				return m_maximum[X] - m_minimum[X];
			}

			/**
			 * @brief Returns the height of the box (Y axis).
			 * @return type_t
			 */
			[[nodiscard]]
			data_t
			height () const noexcept
			{
				return m_maximum[Y] - m_minimum[Y];
			}

			/**
			 * @brief Returns the depth of the box (Z axis).
			 * @return type_t
			 */
			[[nodiscard]]
			data_t
			depth () const noexcept
			{
				return m_maximum[Z] - m_minimum[Z];
			}

			/**
			 * @brief Returns the farthest corner from the center of the box.
			 * @return type_t
			 */
			[[nodiscard]]
			data_t
			farthestPoint () const noexcept
			{
				data_t distance = 0;

				if ( m_maximum[X] > distance )
				{
					distance = m_maximum[X];
				}

				if ( m_maximum[Y] > distance )
				{
					distance = m_maximum[Y];
				}

				if ( m_maximum[Z] > distance )
				{
					distance = m_maximum[Z];
				}

				if ( std::abs(m_minimum[X]) > distance )
				{
					distance = std::abs(m_minimum[X]);
				}

				if ( std::abs(m_minimum[Y]) > distance )
				{
					distance = std::abs(m_minimum[Y]);
				}

				if ( std::abs(m_minimum[Z]) > distance )
				{
					distance = std::abs(m_minimum[Z]);
				}

				return distance;
			}

			/**
			 * @brief Returns the highest length of every axis.
			 * @return type_t
			 */
			[[nodiscard]]
			data_t
			highestLength () const noexcept
			{
				auto length = this->width();

				const auto height = this->height();

				if ( height > length )
				{
					length = height;
				}

				const auto depth = this->depth();

				if ( depth > length )
				{
					length = depth;
				}

				return length;
			}

			/**
			 * @brief Returns the point at X+, Y- and Z+.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			Vector< 3, data_t >
			bottomSouthEast () const noexcept
			{
				return {m_maximum[X], m_maximum[Y], m_maximum[Z]};
			}

			/**
			 * @brief Returns the point at X+, Y- and Z-.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			Vector< 3, data_t >
			bottomNorthEast () const noexcept
			{
				return {m_maximum[X], m_maximum[Y], m_minimum[Z]};
			}

			/**
			 * @brief Returns the point at X-, Y- and Z+.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			Vector< 3, data_t >
			bottomSouthWest () const noexcept
			{
				return {m_minimum[X], m_maximum[Y], m_maximum[Z]};
			}

			/**
			 * @brief Returns the point at X-, Y- and Z-.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			Vector< 3, data_t >
			bottomNorthWest () const noexcept
			{
				return {m_minimum[X], m_maximum[Y], m_minimum[Z]};
			}

			/**
			 * @brief Returns the point at X+, Y+ and Z+.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			Vector< 3, data_t >
			topSouthEast () const noexcept
			{
				return {m_maximum[X], m_minimum[Y], m_maximum[Z]};
			}

			/**
			 * @brief Returns the point at X+, Y+ and Z-.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			Vector< 3, data_t >
			topNorthEast () const noexcept
			{
				return {m_maximum[X], m_minimum[Y], m_minimum[Z]};
			}

			/**
			 * @brief Returns the point at X-, Y+ and Z+.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			Vector< 3, data_t >
			topSouthWest () const noexcept
			{
				return {m_minimum[X], m_minimum[Y], m_maximum[Z]};
			}

			/**
			 * @brief Returns the point at X-, Y+ and Z-.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			Vector< 3, data_t >
			topNorthWest () const noexcept
			{
				return {m_minimum[X], m_minimum[Y], m_minimum[Z]};
			}

			/**
			 * @brief Returns the center of the bounding box.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			Vector< 3, data_t >
			centroid () const noexcept
			{
				return (m_maximum + m_minimum) * 0.5F;
			}

			/**
			 * @brief Extends the volume of this box with another one.
			 * @param other A reference to a cuboid.
			 * @return void
			 */
			void
			merge (const Cuboid< data_t > & other) noexcept
			{
				/* If the other box is the same or is invalid, we skip it. */
				if ( this == &other || !other.isValid() )
				{
					return;
				}

				/* If THIS box is invalid, we simply
				 * copy the other over it. */
				if ( !this->isValid() )
				{
					m_maximum = other.m_maximum;
					m_minimum = other.m_minimum;

					return;
				}

				/* Compare and processLogics every axis boundaries. */
				if ( other.m_maximum[X] > m_maximum[X] )
				{
					m_maximum[X] = other.m_maximum[X];
				}

				if ( other.m_minimum[X] < m_minimum[X] )
				{
					m_minimum[X] = other.m_minimum[X];
				}

				if ( other.m_maximum[Y] > m_maximum[Y] )
				{
					m_maximum[Y] = other.m_maximum[Y];
				}

				if ( other.m_minimum[Y] < m_minimum[Y] )
				{
					m_minimum[Y] = other.m_minimum[Y];
				}

				if ( other.m_maximum[Z] > m_maximum[Z] )
				{
					m_maximum[Z] = other.m_maximum[Z];
				}

				if ( other.m_minimum[Z] < m_minimum[Z] )
				{
					m_minimum[Z] = other.m_minimum[Z];
				}
			}

			/**
			 * @brief Extends the volume with a point.
			 * @param point A reference to a vector.
			 * @return void
			 */
			void
			merge (const Vector< 3, data_t > & point) noexcept
			{
				this->mergeX(point[X]);

				this->mergeY(point[Y]);

				this->mergeZ(point[Z]);
			}

			/**
			 * @brief Extends the volume with a point.
			 * @param point A reference to a vector.
			 * @return void
			 */
			void
			merge (const Vector< 4, data_t > & point) noexcept
			{
				this->mergeX(point[X]);

				this->mergeY(point[Y]);

				this->mergeZ(point[Z]);
			}

			/**
			 * @brief Merge a value on X.
			 * @param value The distance in X.
			 * @return void
			 */
			void
			mergeX (data_t value) noexcept
			{
				if ( value > m_maximum[X] )
				{
					m_maximum[X] = value;
				}

				if ( value < m_minimum[X] )
				{
					m_minimum[X] = value;
				}
			}

			/**
			 * @brief Merge a value on Y.
			 * @param value The distance in Y.
			 * @return void
			 */
			void
			mergeY (data_t value) noexcept
			{
				if ( value > m_maximum[Y] )
				{
					m_maximum[Y] = value;
				}

				if ( value < m_minimum[Y] )
				{
					m_minimum[Y] = value;
				}
			}

			/**
			 * @brief Merge a value on Z.
			 * @param value The distance in Z.
			 * @return void
			 */
			void
			mergeZ (data_t value) noexcept
			{
				if ( value > m_maximum[Z] )
				{
					m_maximum[Z] = value;
				}

				if ( value < m_minimum[Z] )
				{
					m_minimum[Z] = value;
				}
			}

			/**
			 * @brief Returns whether the volume is colliding with a cuboid.
			 * @param cuboid A reference to another cuboid.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isCollidingWith (const Cuboid< data_t > & cuboid) const noexcept
			{
				if ( this == &cuboid || !this->isValid() || !cuboid.isValid() )
				{
					return false;
				}

				if ( m_maximum[X] < cuboid.m_minimum[X] || m_minimum[X] > cuboid.m_maximum[X] )
				{
					return false;
				}

				if ( m_maximum[Y] < cuboid.m_minimum[Y] || m_minimum[Y] > cuboid.m_maximum[Y] )
				{
					return false;
				}

				if ( m_maximum[Z] < cuboid.m_minimum[Z] || m_minimum[Z] > cuboid.m_maximum[Z] )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief Returns whether the volume is colliding with a sphere.
			 * @param sphere A reference to a sphere.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isCollidingWith (const Sphere< data_t > & sphere) const noexcept
			{
				const auto & point = sphere.position();

				if ( point[X] + sphere.radius() < m_minimum[X] || point[X] - sphere.radius() > m_maximum[X] )
				{
					return false;
				}

				if ( point[Y] + sphere.radius() < m_minimum[Y] || point[Y] - sphere.radius() > m_maximum[Y] )
				{
					return false;
				}

				if ( point[Z] + sphere.radius() < m_minimum[Z] || point[Z] - sphere.radius() > m_maximum[Z] )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief Returns whether the volume is colliding with a point.
			 * @param point A reference to a vector.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isCollidingWith (const Vector< 3, data_t > & point) const noexcept
			{
				if ( point[X] < m_minimum[X] || point[X] > m_maximum[X] )
				{
					return false;
				}

				if ( point[Y] < m_minimum[Y] || point[Y] > m_maximum[Y] )
				{
					return false;
				}

				if ( point[Z] < m_minimum[Z] || point[Z] > m_maximum[Z] )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief Returns whether the volume is colliding with a point.
			 * @param point A reference to a vector.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isCollidingWith (const Vector< 4, data_t > & point) const noexcept
			{
				return this->isCollidingWith(Vector< 3, data_t >(point));
			}

			/**
			 * @brief Returns the overlap distance vector from the intersection with another cuboid.
			 * @param lhs A reference to a cuboid.
			 * @param rhs A reference to a cuboid.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			static
			Vector< 3, data_t >
			getIntersectionOverlap (const Cuboid< data_t > & lhs, const Cuboid< data_t > & rhs) noexcept
			{
				if ( &lhs == &rhs || !lhs->isValid() || !rhs.isValid() )
				{
					return {};
				}

				if ( lhs.m_maximum[X] < rhs.m_minimum[X] || lhs.m_minimum[X] > rhs.m_maximum[X] )
				{
					return {};
				}

				if ( lhs.m_maximum[Y] < rhs.m_minimum[Y] || lhs.m_minimum[Y] > rhs.m_maximum[Y] )
				{
					return {};
				}

				if ( lhs.m_maximum[Z] < rhs.m_minimum[Z] || lhs.m_minimum[Z] > rhs.m_maximum[Z] )
				{
					return {};
				}

				const auto maxX = std::min(lhs.m_maximum[X], rhs.m_maximum[X]);
				const auto minX = std::max(lhs.m_minimum[X], rhs.m_minimum[X]);

				const auto maxY = std::min(lhs.m_maximum[Y], rhs.m_maximum[Y]);
				const auto minY = std::max(lhs.m_minimum[Y], rhs.m_minimum[Y]);

				const auto maxZ = std::min(lhs.m_maximum[Z], rhs.m_maximum[Z]);
				const auto minZ = std::max(lhs.m_minimum[Z], rhs.m_minimum[Z]);

				return {maxX - minX, maxY - minY, maxZ - minZ};
			}

			/**
			 * @brief Returns the overlap distance vector from the intersection with a point.
			 * @param lhs A reference to a cuboid.
			 * @param point A reference to a vector.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			static
			Vector< 3, data_t >
			getIntersectionOverlap (const Cuboid< data_t > & lhs, const Vector< 3, data_t > & point) noexcept
			{
				if ( point[X] < lhs.m_minimum[X] || point[X] > lhs.m_maximum[X] )
				{
					return {};
				}

				if ( point[Y] < lhs.m_minimum[Y] || point[Y] > lhs.m_maximum[Y] )
				{
					return {};
				}

				if ( point[Z] < lhs.m_minimum[Z] || point[Z] > lhs.m_maximum[Z] )
				{
					return {};
				}

				const auto maxX = std::min(lhs.m_maximum[X], point[X]);
				const auto minX = std::max(lhs.m_minimum[X], point[X]);

				const auto maxY = std::min(lhs.m_maximum[Y], point[Y]);
				const auto minY = std::max(lhs.m_minimum[Y], point[Y]);

				const auto maxZ = std::min(lhs.m_maximum[Z], point[Z]);
				const auto minZ = std::max(lhs.m_minimum[Z], point[Z]);

				return {maxX - minX, maxY - minY, maxZ - minZ};
			}

			/**
			 * @brief Returns the overlap distance vector from the intersection with a point.
			 * @param lhs A reference to a cuboid.
			 * @param point A reference to a vector.
			 * @return Vector< 3, type_t >
			 */
			[[nodiscard]]
			static
			Vector< 3, data_t >
			getIntersectionOverlap (const Cuboid< data_t > & lhs, const Vector< 4, data_t > & point) noexcept
			{
				return Cuboid::getIntersectionOverlap(lhs, Vector< 3, data_t >(point));
			}

			/**
			 * @brief Returns the intersection cuboid.
			 * @param lhs A reference to a cuboid.
			 * @param rhs A reference to a cuboid.
			 * @return Cuboid< type_t >
			 */
			[[nodiscard]]
			static
			Cuboid< data_t >
			getIntersectionCuboid (const Cuboid< data_t > & lhs, const Cuboid< data_t > & rhs) noexcept
			{
				if ( &lhs == &rhs || !lhs.isValid() || !rhs.isValid())
				{
					return {};
				}

				if ( lhs.m_maximum[X] < rhs.m_minimum[X] || lhs.m_minimum[X] > rhs.m_maximum[X] )
				{
					return {};
				}

				if ( lhs.m_maximum[Y] < rhs.m_minimum[Y] || lhs.m_minimum[Y] > rhs.m_maximum[Y] )
				{
					return {};
				}

				if ( lhs.m_maximum[Z] < rhs.m_minimum[Z] || lhs.m_minimum[Z] > rhs.m_maximum[Z] )
				{
					return {};
				}

				Vector< 3, data_t > maximum{};
				Vector< 3, data_t > minimum{};

				maximum[X] = std::min(lhs.m_maximum[X], rhs.m_maximum[X]);
				minimum[X] = std::max(lhs.m_minimum[X], rhs.m_minimum[X]);

				maximum[Y] = std::min(lhs.m_maximum[Y], rhs.m_maximum[Y]);
				minimum[Y] = std::max(lhs.m_minimum[Y], rhs.m_minimum[Y]);

				maximum[Z] = std::min(lhs.m_maximum[Z], rhs.m_maximum[Z]);
				minimum[Z] = std::max(lhs.m_minimum[Z], rhs.m_minimum[Z]);

				return {maximum, minimum};
			}

			/** @brief Reset the cuboid to null value. */
			void
			reset () noexcept
			{
				m_maximum[X] = std::numeric_limits< data_t >::lowest();
				m_maximum[Y] = std::numeric_limits< data_t >::lowest();
				m_maximum[Z] = std::numeric_limits< data_t >::lowest();

				m_minimum[X] = std::numeric_limits< data_t >::max();
				m_minimum[Y] = std::numeric_limits< data_t >::max();
				m_minimum[Z] = std::numeric_limits< data_t >::max();
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Cuboid & obj) noexcept
			{
				return out <<
					"Cuboid volume data :\n"
					"Maximum : " << obj.m_maximum << "\n"
					"Minimum : " << obj.m_minimum << '\n';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Cuboid & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			Vector< 3, data_t > m_maximum{std::numeric_limits< data_t >::lowest(), std::numeric_limits< data_t >::lowest(), std::numeric_limits< data_t >::lowest()};
			Vector< 3, data_t > m_minimum{std::numeric_limits< data_t >::max(), std::numeric_limits< data_t >::max(), std::numeric_limits< data_t >::max()};
	};
}
