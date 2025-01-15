/*
 * src/Libraries/Math/BezierCurve.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <cstddef>
#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

/* Local inclusions for usages. */
#include "Vector.hpp"

namespace Libraries::Math
{
	/**
	 * @brief Bezier curve.
	 * @tparam dim_t The dimension of the point.
	 * @tparam number_t The type of number. Default float.
	 */
	template< size_t dim_t, typename number_t = float >
	requires (dim_t == 2 || dim_t == 3 || dim_t == 4) && std::is_arithmetic_v< number_t >
	class BezierCurve final
	{
		public:

			using Callback = std::function< bool (float time, const Vector< dim_t, number_t > & position) >;

			/**
			 * @brief Constructs a bezier curve.
			 */
			BezierCurve () noexcept = default;

			/**
			 * @brief Adds a control point.
			 * @param position The absolute position of the control point.
			 * @return Vector< dim_t, type_t > &
			 */
			Vector< dim_t, number_t > &
			addPoint (const Vector< dim_t, number_t > & position) noexcept
			{
				return m_points.emplace_back(position);
			}

			/**
			 * @brief Close the curve by reusing the first point.
			 * @return void
			 */
			void
			close () noexcept
			{
				m_closed = true;
			}

			/**
			 * @brief Creates a line from the control point.
			 * @param segments The number of segment to synthesize the line.
			 * @param callback A function which receive the point and the interval on the line.
			 * @return bool
			 */
			bool
			synthesize (size_t segments, const Callback & callback) const noexcept
			{
				if ( m_points.size() < 3 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the curve needs at least 3 points !" "\n";

					return false;
				}

				if ( segments < 2 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the segment parameter must be at least 2 !" "\n";

					return false;
				}

				const auto timeStep = 1.0F / static_cast< float >(segments);

				auto timePoint = 0.0F;

				/* NOTE: we use the segment count + 1 here. */
				for ( size_t index = 0; index <= segments; index++ )
				{
					const auto interpolatedPoint = this->synthesizePoint(timePoint);

					if ( !callback(timePoint, interpolatedPoint) )
					{
						return false;
					}

					timePoint += timeStep;
				}

				return true;
			}

		private:

			/**
			 * @brief Gets a point on the synthesized line at a time.
			 * @param globalTimePoint A time from 0.0 to 1.0
			 * @return Vector
			 */
			[[nodiscard]]
			Vector< dim_t, number_t >
			synthesizePoint (float globalTimePoint) const noexcept
			{
				if ( !m_closed )
				{
					if ( globalTimePoint <= 0.0F )
					{
						return *m_points.cbegin();
					}

					if ( globalTimePoint >= 1.0F )
					{
						return *m_points.crbegin();
					}
				}

				if ( m_points.size() == 3 )
				{
					return Vector< dim_t, number_t >::quadraticBezierInterpolation(m_points[0], m_points[1], m_points[2], globalTimePoint);
				}

				const auto pointCount = m_closed ? m_points.size() : m_points.size() - 1;
				const auto segmentSize = 1.0F / pointCount;

				const auto pointIndex = static_cast< size_t >(std::round(globalTimePoint / segmentSize));

				Vector< dim_t, number_t > pointA;
				Vector< dim_t, number_t > pointB;
				Vector< dim_t, number_t > pointC;

				float sizeA;
				float sizeB;

				if ( pointIndex == 0 )
				{
					if ( m_closed )
					{
						pointA = m_points[m_points.size() - 1];
						pointB = m_points[pointIndex];
						pointC = m_points[pointIndex+1];

						sizeA = (m_points.size() - 1) * segmentSize;
						sizeB = (pointIndex + 1) * segmentSize;
					}
					else
					{
						pointA = m_points[pointIndex];
						pointB = m_points[pointIndex+1];
						pointC = m_points[pointIndex+2];

						sizeA = 0.0F;
						sizeB = (pointIndex + 2) * segmentSize;
					}
				}
				else if ( pointIndex == pointCount )
				{
					if ( m_closed )
					{
						pointA = m_points[pointIndex-1];
						pointB = m_points[pointIndex];
						pointC = m_points[0];

						sizeA = (pointIndex + 1) * segmentSize;
						sizeB = 0.0F;
					}
					else
					{
						pointA = m_points[pointIndex-2];
						pointB = m_points[pointIndex-1];
						pointC = m_points[pointIndex];

						sizeA = (pointIndex - 2) * segmentSize;
						sizeB = pointIndex * segmentSize;
					}
				}
				else
				{
					pointA = m_points[pointIndex-1];
					pointB = m_points[pointIndex];
					pointC = m_points[pointIndex+1];

					sizeA = (pointIndex - 1) * segmentSize;
					sizeB = (pointIndex + 1) * segmentSize;
				}

				const auto normalizedStart = globalTimePoint - sizeA;
				const auto normalizedEnd = sizeB - sizeA;
				const auto localTimePoint = clampToUnit(normalizedStart / normalizedEnd);

				return Vector< dim_t, number_t >::quadraticBezierInterpolation(pointA, pointB, pointC, localTimePoint);
			}

			std::vector< Vector< dim_t, number_t > > m_points;
			bool m_closed{false};
	};
}
