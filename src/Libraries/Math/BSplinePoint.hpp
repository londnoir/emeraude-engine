/*
 * src/Libraries/Math/BSplinePoint.hpp
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
#include <cstdint>
#include <iostream>
#include <type_traits>

/* Local inclusions. */
#include "Vector.hpp"

namespace Libraries::Math
{
	/**
	 * @brief The CurveType enum
	 */
	enum class CurveType : uint8_t
	{
		None,
		BezierQuadratic,
		BezierCubic
	};

	/**
	 * @brief The B-Spline point class.
	 * @tparam dim_t The dimension of the vector. This can be 2, 3 or 4.
	 * @tparam number_t The type of number. Default float.
	 */
	template< size_t dim_t, typename number_t = float >
	requires (dim_t == 2 || dim_t == 3 || dim_t == 4) && std::is_arithmetic_v< number_t >
	class BSplinePoint final
	{
		public:

			/**
			 * @brief Constructs a B-Spline point.
			 * @param position A reference to a vector.
			 * @param curveType The curve type.
			 * @param segments The number of segment.
			 */
			BSplinePoint (const Vector< dim_t, number_t > & position, CurveType curveType, size_t segments) noexcept
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
			BSplinePoint (const Vector< dim_t, number_t > & position, const Vector< dim_t, number_t > & handle, CurveType curveType, size_t segments) noexcept
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
			BSplinePoint (const Vector< dim_t, number_t > & position, const Vector< dim_t, number_t > & handleIn, const Vector< dim_t, number_t > & handleOut, CurveType curveType, size_t segments) noexcept
				: m_position(position), m_handleIn(handleIn), m_handleOut(handleOut), m_curveType(curveType), m_segments(segments)
			{

			}

			/**
			 * @brief Sets the curve type.
			 * @param curveType The curve type.
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
					std::cerr << __PRETTY_FUNCTION__ << ", segment should at least be 1 !" "\n";
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
			const Vector< dim_t, number_t > &
			position () const noexcept
			{
				return m_position;
			}

			/**
			 * @brief Returns the "in" handle.
			 * @return const Vector< dim_t, type_t > &
			 */
			[[nodiscard]]
			const Vector< dim_t, number_t > &
			handleIn () const noexcept
			{
				return m_handleIn;
			}

			/**
			 * @brief Returns the "out" handle.
			 * @return const Vector< dim_t, type_t > &
			 */
			[[nodiscard]]
			const Vector< dim_t, number_t > &
			handleOut () const noexcept
			{
				return m_handleOut;
			}

		private:

			Vector< dim_t, number_t > m_position;
			Vector< dim_t, number_t > m_handleIn{};
			Vector< dim_t, number_t > m_handleOut{};
			CurveType m_curveType{CurveType::None};
			size_t m_segments{1};
	};
}
