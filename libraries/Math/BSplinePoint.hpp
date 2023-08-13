/*
 * Libraries/Math/BSplinePoint.hpp
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
#include <type_traits>

/* Local inclusions */
#include "Vector.hpp"

namespace Libraries::Math
{
	/**
	 * @brief The CurveType enum
	 */
	enum class CurveType
	{
		None,
		BezierQuadratic,
		BezierCubic
	};

	/**
	 * @brief The B-Spline point class.
	 * @tparam type_t The data type.
	 * @tparam dim_t The dimension of the point.
	 */
	template<
		typename type_t,
		std::size_t dim_t,
		std::enable_if_t< std::is_arithmetic_v< type_t >, bool > = false,
		std::enable_if_t< dim_t == 2 || dim_t == 3 || dim_t == 4, bool > = false
	>
	class BSplinePoint final
	{
		public:

			/**
			 * @brief Constructs a B-Spline point.
			 * @param position A reference to a vector.
			 * @param curveType The curve type.
			 * @param segments The number of segment.
			 */
			BSplinePoint (const Vector< dim_t, type_t > & position, CurveType curveType, size_t segments) noexcept
				: m_position(position), m_curveType(curveType), m_segments(segments)
			{

			}

			/**
			 * @brief Constructs a B-Spline point.
			 * @param position A reference to a vector.
			 * @param handle A reference to a vector.
			 * @param curveType The curve type.
			 * @param segments The number of segment.
			 */
			BSplinePoint (const Vector< dim_t, type_t > & position, const Vector< dim_t, type_t > & handle, CurveType curveType, size_t segments) noexcept
				: m_position(position), m_handleIn(-handle), m_handleOut(handle), m_curveType(curveType), m_segments(segments)
			{

			}

			/**
			 * @brief Constructs a B-Spline point.
			 * @param position A reference to a vector.
			 * @param handleIn A reference to a vector.
			 * @param handleOut A reference to a vector.
			 * @param curveType The curve type.
			 * @param segments The number of segment.
			 */
			BSplinePoint (const Vector< dim_t, type_t > & position, const Vector< dim_t, type_t > & handleIn, const Vector< dim_t, type_t > & handleOut, CurveType curveType, size_t segments) noexcept
				: m_position(position), m_handleIn(handleIn), m_handleOut(handleOut), m_curveType(curveType), m_segments(segments)
			{

			}

			/**
			 * @brief Sets the curve type.
			 * @param bezierType The curve type.
			 * @return BSplinePoint &
			 */
			BSplinePoint &
			setCurveType (CurveType curveType) noexcept
			{
				m_curveType = curveType;

				return *this;
			}

			/**
			 * @brief Returns the curve type.
			 * @return CurveType
			 */
			[[nodiscard]]
			CurveType
			curveType () const noexcept
			{
				return m_curveType;
			}

			/**
			 * @brief Sets the number of segments.
			 * @param segments The number of segments.
			 * @return BSplinePoint &
			 */
			BSplinePoint &
			setSegments (size_t segments) noexcept
			{
				if ( segments < 1 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", segment should at least be 1 !" << std::endl;
				}
				else
				{
					m_segments = segments;
				}

				return *this;
			}

			/**
			 * @brief Returns the number of segments.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			segments () const noexcept
			{
				return m_segments;
			}

			/**
			 * @brief Returns the position.
			 * @return const Vector< dim_t, type_t > &
			 */
			[[nodiscard]]
			const Vector< dim_t, type_t > &
			position () const noexcept
			{
				return m_position;
			}

			/**
			 * @brief Returns the "in" handle.
			 * @return const Vector< dim_t, type_t > &
			 */
			[[nodiscard]]
			const Vector< dim_t, type_t > &
			handleIn () const noexcept
			{
				return m_handleIn;
			}

			/**
			 * @brief Returns the "out" handle.
			 * @return const Vector< dim_t, type_t > &
			 */
			[[nodiscard]]
			const Vector< dim_t, type_t > &
			handleOut () const noexcept
			{
				return m_handleOut;
			}

		private:

			Vector< dim_t, type_t > m_position;
			Vector< dim_t, type_t > m_handleIn{};
			Vector< dim_t, type_t > m_handleOut{};
			CurveType m_curveType{CurveType::None};
			size_t m_segments{1};
	};
}
