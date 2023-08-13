/*
 * Libraries/Math/BezierCurve.hpp
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

/* C/C++ standard libraries. */
#include <cmath>
#include <functional>
#include <vector>

/* Local inclusions */
#include "Vector.hpp"

namespace Libraries::Math
{
	/**
	 * @brief Bezier curve.
	 * @tparam type_t The data type.
	 * @tparam dim_t The dimension of the point.
	 */
	template<
		typename type_t,
		std::size_t dim_t,
		std::enable_if_t< std::is_arithmetic_v< type_t >, bool > = false,
		std::enable_if_t< dim_t == 2 || dim_t == 3 || dim_t == 4, bool > = false
	>
	class BezierCurve final
	{
		public:

			using Callback = std::function< bool (float time, const Vector< dim_t, type_t > & position) >;

			/**
			 * @brief Constructs a bezier curve.
			 */
			BezierCurve () noexcept = default;

			/**
			 * @brief Adds a control point.
			 * @param position The absolute position of the control point.
			 * @return Vector< dim_t, type_t > &
			 */
			inline
			Vector< dim_t, type_t > &
			addPoint (const Vector< dim_t, type_t > & position) noexcept
			{
				return m_points.emplace_back(position);
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
					std::cerr << __PRETTY_FUNCTION__ << ", the curve needs at least 3 points !" << std::endl;

					return false;
				}

				if ( segments < 1 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", segment parameter must be at least 2 !" << std::endl;

					return false;
				}

				const auto factorStep = 1.0F / static_cast< float >(segments);

				auto factor = 0.0F;

				for ( size_t index = 0; index <= segments; index++ )
				{
					if ( !callback(factor, BezierCurve::synthesizePoint(m_points, factor)) )
					{
						return false;
					}

					factor += factorStep;
				}

				return true;
			}

		private:

			/**
			 * @brief Gets a point on the synthesized line at a time.
			 * @note This method is recursive.
			 * @param points The number of points left at this iteration.
			 * @param factor A time from 0 to 1.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector< dim_t, type_t >
			synthesizePoint (const std::vector< Vector< dim_t, type_t > > & points, float factor) noexcept
			{
				if ( points.size() == 3 )
				{
					return Vector< dim_t, type_t >::quadraticBezierInterpolation(points[0], points[1], points[2], factor);
				}

				std::vector< Vector< dim_t, type_t > > newPoints{};

				for ( auto pointIndex = 2UL; pointIndex < points.size(); pointIndex++ )
				{
					newPoints.emplace_back(Vector< dim_t, type_t >::quadraticBezierInterpolation(points[pointIndex-2], points[pointIndex-1], points[pointIndex], factor));
				}

				return BezierCurve::synthesizePoint(newPoints, factor);
			}

			std::vector< Vector< dim_t, type_t > > m_points{};
	};
}
