/*
 * src/Libs/Math/Space3D/Sphere.hpp
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
#include <sstream>
#include <string>

/* Local inclusions for usages. */
#include "Libs/Math/Base.hpp"
#include "Point.hpp"

namespace EmEn::Libs::Math::Space3D
{
	/**
	 * @brief Class for a sphere in 3D space.
	 * @tparam precision_t The precision type. Default float.
	 */
	template< typename precision_t = float >
	requires (std::is_floating_point_v< precision_t >)
	class Sphere final
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
			Sphere (precision_t radius) noexcept
				: m_radius(radius)
			{

			}

			/**
			 * @brief Constructs a sphere volume at a location.
			 * @param radius The radius of the sphere.
			 * @param position A reference to a position vector.
			 */
			constexpr
			Sphere (precision_t radius, const Vector< 3, precision_t > & position) noexcept
				: m_position(position), m_radius(radius)
			{

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
			 * @brief Sets a position.
			 * @param position A reference to a position vector.
			 * @return void
			 */
			void
			setPosition (const Vector< 3, precision_t > & position) noexcept
			{
				m_position = position;
			}

			/**
			 * @brief Returns the position.
			 * @return const Vector< 3, data_t > &
			 */
			[[nodiscard]]
			const Vector< 3, precision_t > &
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
			setRadius (precision_t radius) noexcept
			{
				m_radius = std::abs(radius);
			}

			/**
			 * @brief Returns the radius of the sphere.
			 * @return data_t
			 */
			[[nodiscard]]
			precision_t
			radius () const noexcept
			{
				return m_radius;
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
			 * @brief Checks if a point is inside or on the edge of the sphere.
			 * @param point A reference to a point.
			 * @return bool
			 */
			[[nodiscard]]
			constexpr
			bool
			contains (const Point< precision_t > & point) const noexcept
			{
				const Point< precision_t > distance = point - m_position;

				return distance.lengthSquared() <= m_radius * m_radius;
			}

			/**
			 * @brief Returns the sphere perimeter.
			 * @return precision_t
			 */
			[[nodiscard]]
			constexpr
			precision_t
			getPerimeter () const noexcept
			{
				return circleCircumference(m_radius);
			}

			/**
			 * @brief Returns the sphere area (2D).
			 * @return precision_t
			 */
			[[nodiscard]]
			constexpr
			precision_t
			getArea () const noexcept
			{
				return circleArea(m_radius);
			}

			/**
			 * @return Returns the sphere volume.
			 * @return precision_t
			 */
			[[nodiscard]]
			precision_t
			getVolume () const noexcept
			{
				return sphereVolume(m_radius);
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
			isOverlapping (precision_t D, precision_t R2)
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
			precision_t
			overlap (precision_t D, precision_t R2)
			{
				return D < R2 ? R2 - D : 0;
			}

			Vector< 3, precision_t > m_position{};
			precision_t m_radius{0};
	};
}
