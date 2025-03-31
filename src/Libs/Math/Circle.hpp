/*
 * src/Libs/Math/Circle.hpp
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
#include <sstream>
#include <string>
#include <type_traits>
#include <limits>
#include <algorithm>

/* Local inclusions for inheritances. */
#include "Shape2DInterface.hpp"

/* Local inclusions for usages. */
#include "Base.hpp"
#include "Vector.hpp"
#include "Rectangle.hpp"

namespace EmEn::Libs::Math
{
	/**
	 * @brief Defines a geometric circle.
	 * @tparam data_t The type used for geometric distance and dimensions. Default float.
	 * @extends EmEn::Libs::Math::Shape2DInterface This is a 2D shape.
	 */
	template< typename data_t = float > requires (std::is_floating_point_v< data_t >)
	class Circle final : public Shape2DInterface< data_t >
	{
		public:

			/**
			 * @brief Constructs a circle.
			 * @param radius The initial radius. Default 0.
			 * @param position A reference to a vector. Default origin.
			 */
			explicit
			constexpr
			Circle (data_t radius = 0, const Vector< 2, data_t > & position = {}) noexcept
				: m_position(position), m_radius(radius < 0 ? -radius : radius)
			{

			}

			/**
			 * @brief Returns whether another circle is different.
			 * @param operand A reference to a circle.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator== (const Circle & operand) const noexcept
			{
				if ( m_position != operand.m_position )
				{
					return false;
				}

				return std::abs(m_radius - operand.m_radius) <= std::numeric_limits< data_t >::epsilon() * std::max(data_t(1.0), std::max(std::abs(m_radius), std::abs(operand.m_radius)));
			}

			/**
			 * @brief Returns whether another circle is different.
			 * @param operand A reference to a circle.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator!= (const Circle & operand) const noexcept
			{
				return !(*this == operand);
			}

			/** @copydoc EmEn::Libs::Math::Shape2DInterface::getPerimeter() */
			[[nodiscard]]
			constexpr
			data_t
			getPerimeter () const noexcept override
			{
				return circleCircumference(m_radius);
			}

			/** @copydoc EmEn::Libs::Math::Shape2DInterface::getArea() */
			[[nodiscard]]
			constexpr
			data_t
			getArea () const noexcept override
			{
				return circleArea(m_radius);
			}

			/**
			 * @brief Sets the position of the circle in space.
			 * @param position A reference to a vector.
			 */
			void
			setPosition (const Vector< 2, data_t > & position) noexcept
			{
				m_position = position;
			}

			/**
			 * @brief Sets the radius of the circle.
			 * @param radius The radius in engine metrics.
			 */
			void
			setRadius (data_t radius) noexcept
			{
				m_radius = std::abs(radius);
			}

			/**
			 * @brief Returns whether the circle is a coherent surface.
			 * @return bool
			 */
			[[nodiscard]]
			constexpr
			bool
			isValid () const noexcept
			{
				return m_radius > static_cast< data_t >(0);
			}

			/**
			 * @brief Returns the position of the circle in space.
			 * @return const Vector< 2, data_t > &
			 */
			[[nodiscard]]
			const Vector< 2, data_t > &
			position () const noexcept
			{
				return m_position;
			}

			/**
			 * @brief Returns the radius of the circle in engine metrics.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			radius () const noexcept
			{
				return m_radius;
			}

			/**
			* @brief Checks if this circle intersects with another circle.
			* @details Intersection includes touching edges (tangent).
			* @param other The other circle.
			* @return true if the circles intersect or touch.
			*/
			[[nodiscard]]
			constexpr
			bool
			intersects (const Circle & other) const noexcept
			{
				const data_t radiiSum = m_radius + other.m_radius;
				const Vector< 2, data_t > distance = m_position - other.m_position;

				return distance.lengthSquared() <= radiiSum * radiiSum;
			}

			/**
			 * @brief Checks if a point is inside or on the edge of the circle.
			 * @param point The point to check.
			 * @return true if the point is contained within the circle.
			 */
			[[nodiscard]]
			constexpr
			bool
			contains (const Vector< 2, data_t > & point) const noexcept
			{
				const Vector< 2, data_t > distance = point - m_position;

				return distance.lengthSquared() <= m_radius * m_radius;
			}

			/**
			* @brief Checks if this circle completely contains another circle.
			* @details Containment includes the case where the inner circle touches the edge from the inside.
			* @param other The circle to check for containment.
			* @return true if the other circle is fully inside or touching the edge of this circle.
			*/
			[[nodiscard]]
			constexpr
			bool
			contains (const Circle & other) const noexcept
			{
				if ( other.m_radius > m_radius )
				{
					return false;
				}

				const Vector< 2, data_t > distance = m_position - other.m_position;
				const data_t radiiDiff = m_radius - other.m_radius;

				return distance.lengthSquared() <= radiiDiff * radiiDiff;
			}

			/**
			* @brief Calculates the smallest Axis-Aligned Bounding Box (AABB) containing the circle.
			* @return A Rectangle object representing the bounding box.
			*/
			[[nodiscard]]
			constexpr
			Rectangle< data_t >
			getBoundingBox() const noexcept
			{
				if ( !this->isValid() )
				{
					return {m_position.x(), m_position.y(), 0, 0};
				}

				const data_t diameter = static_cast< data_t >(2) * m_radius;

				return {
					m_position.x() - m_radius,
					m_position.y() - m_radius,
					diameter,
					diameter
				};
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Circle & obj)
			{
				return out << "Circle data :\n"
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
			to_string (const Circle & obj)
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			Vector< 2, data_t > m_position;
			data_t m_radius;
	};
}
