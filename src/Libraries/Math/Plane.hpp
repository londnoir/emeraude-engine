/*
 * src/Libraries/Math/Plane.hpp
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
#include <iostream>
#include <sstream>
#include <string>

/* Local inclusions. */
#include "Vector.hpp"

namespace Libraries::Math
{
	/**
	 * @brief
	 * @note Plan equation "ax + by + cy + d = 0"
	 */
	template< typename data_t = float >
	requires (std::is_arithmetic_v< data_t >)
	class Plane final
	{
		public:

			/**
			 * @brief Constructs a default plane.
			 */
			Plane () noexcept = default;

			/**
			 * @brief Constructs a plane.
			 * @param normal A reference to a vector.
			 * @param point A reference to a vector.
			 */
			Plane (const Vector< 3, data_t > & normal, const Vector< 3, data_t > & point) noexcept
				: m_data(normal, Plane::computeDComponent(normal, point))
			{

			}

			/**
			 * @brief Constructs a plane.
			 * @param pointA A reference to a vector.
			 * @param pointB A reference to a vector.
			 * @param pointC A reference to a vector.
			 */
			Plane (const Vector< 3, data_t > & pointA, const Vector< 3, data_t > & pointB, const Vector< 3, data_t > & pointC) noexcept
				: m_data(Vector< 3, data_t >::normal(pointA, pointB, pointC), Plane::computeDComponent(Vector< 3, data_t >::normal(pointA, pointB, pointC), pointA))
			{

			}

			/**
			 * @brief Constructs a plane.
			 * @param vector A reference to a vector.
			 */
			explicit
			Plane (const Vector< 4, data_t > & vector) noexcept
				: m_data(vector)
			{

			}

			/**
			 * @brief Sets the normal and the point of the plane.
			 * @param normal A reference to a vector.
			 * @param point A reference to a vector.
			 * @return void
			 */
			void
			setNormalAndPoint (const Vector< 3, data_t > & normal, const Vector< 3, data_t > & point) noexcept
			{
				m_data.set(normal, Plane::computeDComponent(normal, point));
			}

			/**
			 * @brief Sets vectors of the place.
			 * @param pointA A reference to a vector.
			 * @param pointB A reference to a vector.
			 * @param pointC A reference to a vector.
			 * @return void
			 */
			void
			setVectors (const Vector< 3, data_t > & pointA, const Vector< 3, data_t > & pointB, const Vector< 3, data_t > & pointC) noexcept
			{
				auto normal = Vector< 3, data_t >::normal(pointA, pointB, pointC);

				m_data.set(normal, Plane::computeDComponent(normal, pointA));
			}

			/**
			 * @brief Returns the distance between a point and the plane.
			 * @param point A reference to a vector.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			getDistanceBetween (const Vector< 3, data_t > & point) const noexcept
			{
				/*		 a.x+b.y+c.z+d
				 * dist = ----------------
				 *		 sqrt(a²+b²+c²)
				 */

				const auto sqX = m_data[X] * m_data[X];
				const auto sqY = m_data[Y] * m_data[Y];
				const auto sqZ = m_data[Z] * m_data[Z];

				const auto tmp = (m_data[X] * point[X]) + (m_data[Y] * point[Y]) + (m_data[Z] * point[Z]) + m_data[W];

				return tmp / std::sqrt(sqX + sqY + sqZ);
			}

			/**
			 * @brief Sets the plane raw data.
			 * @param vector A reference to a vector.
			 * @return void
			 */
			void
			setData (const Vector< 4, data_t > & vector) noexcept
			{
				m_data = vector;
			}

			/**
			 * @brief Returns the plane raw data.
			 * @return const Vector< 4, data_t > &
			 */
			[[nodiscard]]
			const Vector< 4, data_t > &
			data () const noexcept
			{
				return m_data;
			}

			/**
			 * @brief Returns the distance.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			distance () const noexcept
			{
				return m_data[W];
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Plane & obj) noexcept
			{
				out << "Plane data :\n"
					"Normal " << obj.m_data.toVector3() << "\n"
					"D : " << obj.m_data[W] << '\n';

				return out;
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Plane & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			/**
			 * @brief Computes the distance.
			 * @param surfaceNormal A reference to vector.
			 * @param point A reference to vector.
			 * @return data_t
			 */
			static
			data_t
			computeDComponent (const Vector< 3, data_t > & surfaceNormal, const Vector< 3, data_t > & point) noexcept
			{
				/* d = -ax -by -bz; */
				return -(surfaceNormal[X] * point[X]) -(surfaceNormal[Y] * point[Y]) -(surfaceNormal[Z] * point[Z]);
			}

			Vector< 4, data_t > m_data{};
	};
}
