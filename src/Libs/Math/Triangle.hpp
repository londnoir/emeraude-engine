/*
 * src/Libs/Math/Triangle.hpp
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
#include <algorithm>

/* Local inclusions for inheritances. */
#include "Shape2DInterface.hpp"

/* Local inclusions. */
#include "Vector.hpp"

namespace EmEn::Libs::Math
{
	/**
	 * @brief Class for a triangle.
	 * @tparam dimension_t Specify is the segment is 2D or 3D.
	 * @tparam precision_t The data precision. Default float.
	 * @extends EmEn::Libs::Math::Shape2DInterface This is a 2D shape.
	 * @deprecated Use Space2D::Triangle or Space3D::triangle
	 */
	template< size_t dimension_t, typename precision_t = float >
	requires (dimension_t == 2 || dimension_t == 3) && std::is_floating_point_v< precision_t >
	class Triangle final : public Shape2DInterface< precision_t >
	{
		public:

			/**
			 * @brief Constructs a default triangle.
			 */
			Triangle () noexcept = default;

			/**
			 * @brief Constructs a triangle.
			 * @param pointA A reference to vector.
			 * @param pointB A reference to vector.
			 * @param pointC A reference to vector.
			 */
			Triangle (Vector< dimension_t, precision_t > pointA, Vector< dimension_t, precision_t > pointB, Vector< dimension_t, precision_t > pointC) noexcept
				: m_points({std::move(pointA), std::move(pointB), std::move(pointC)})
			{

			}

			/** @copydoc EmEn::Libs::Math::Shape2DInterface::getPerimeter() */
			[[nodiscard]]
			constexpr
			precision_t
			getPerimeter () const noexcept override
			{
				return
					Vector< dimension_t, precision_t >::distance(m_points[0], m_points[1]) +
					Vector< dimension_t, precision_t >::distance(m_points[1], m_points[2]) +
					Vector< dimension_t, precision_t >::distance(m_points[2], m_points[0]);
			}

			/** @copydoc EmEn::Libs::Math::Shape2DInterface::getArea() */
			[[nodiscard]]
			constexpr
			precision_t
			getArea () const noexcept override
			{
				if constexpr ( dimension_t == 2 )
				{
					const auto x1 = m_points[0][X];
					const auto y1 = m_points[0][Y];
					const auto x2 = m_points[1][X];
					const auto y2 = m_points[1][Y];
					const auto x3 = m_points[2][X];
					const auto y3 = m_points[2][Y];

					/* NOTE: Application of the Shoelace formula. */
					return static_cast< precision_t >(0.5) * std::abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
				}
				else if constexpr ( dimension_t == 3 )
				{
					/* NOTE: Create two vectors representing two edges of the triangle. */
					const auto vectorAB = m_points[1] - m_points[0];
					const auto vectorAC = m_points[2] - m_points[0];

					/* NOTE: Calculate the vector product of these two vectors. */
					const auto crossProduct = Vector<3, float>::crossProduct(vectorAB, vectorAC);

					/* NOTE: The area is half the length of the resulting vector. */
					return crossProduct.length() * static_cast< precision_t >(0.5);
				}
				else
				{
					return static_cast< precision_t >(0);
				}
			}

			/**
			 * @brief Returns the point array.
			 * @return std::array< Vector< dimension_t, precision_t >, 3 > &
			 */
			[[nodiscard]]
			std::array< Vector< dimension_t, precision_t >, 3 > &
			points () noexcept
			{
				return m_points;
			}

			/**
			 * @brief Returns the point array.
			 * @return std::array< Vector< dimension_t, precision_t >, 3 > &
			 */
			[[nodiscard]]
			const std::array< Vector< dimension_t, precision_t >, 3 > &
			points () const noexcept
			{
				return m_points;
			}

			/**
			 * @brief Returns the first point of the triangle.
			 * @return const Vector< dimension_t, precision_t > &
			 */
			const Vector< dimension_t, precision_t > &
			pointA () const noexcept
			{
				return m_points[0];
			}

			/**
			 * @brief Returns the second point of the triangle.
			 * @return const Vector< dimension_t, precision_t > &
			 */
			const Vector< dimension_t, precision_t > &
			pointB () const noexcept
			{
				return m_points[1];
			}

			/**
			 * @brief Returns the third point of the triangle.
			 * @return const Vector< dimension_t, precision_t > &
			 */
			const Vector< dimension_t, precision_t > &
			pointC () const noexcept
			{
				return m_points[2];
			}

			/**
			 * @brief Flips the triangle by swapping the first and the second points.
			 * @return void
			 */
			void
			flip () noexcept
			{
				std::swap(m_points[0], m_points[1]);
			}

			/**
			 * @brief Cycles the point in the triangle.
			 * @note Point A becomes the B, old B becomes the C, old C becomes the A.
			 * @return void
			 */
			void
			cycle () noexcept
			{
				std::rotate(m_points.begin(), m_points.begin() + 1, m_points.end());
			}

			/**
			 * @brief Returns whether the triangle is valid.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				if ( m_points[0] == m_points[1] )
				{
					return false;
				}

				if ( m_points[0] == m_points[2] )
				{
					return false;
				}

				if ( m_points[1] == m_points[2] )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Triangle & obj) noexcept
			{
				return out << "Triangle data :\n"
					"Point A : " << obj.pointA() << "\n"
					"Point B : " << obj.pointB() << "\n"
					"Point C : " << obj.pointC() << '\n';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Triangle & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			std::array< Vector< dimension_t, precision_t >, 3 > m_points{};
	};
}
