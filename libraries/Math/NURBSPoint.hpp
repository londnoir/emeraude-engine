/*
 * Libraries/Math/NURBSPoint.hpp
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
#include "Base.hpp"
#include "BSplinePoint.hpp"
#include "Vector.hpp"

namespace Libraries::Math
{
	template<
		typename type_t,
		std::size_t dim_t,
		std::enable_if_t< std::is_arithmetic_v< type_t >, bool > = false,
		std::enable_if_t< dim_t == 3 || dim_t == 4, bool > = false
	>
	class NURBSPoint final
	{
		public:

			NURBSPoint (const Vector< dim_t, type_t > & position, CurveType curveType, size_t segments) noexcept
				: m_position(position), m_curveType(curveType), m_segments(segments)
			{

			}

			NURBSPoint (const Vector< dim_t, type_t > & position, const Vector< dim_t, type_t > & handleX, const Vector< dim_t, type_t > & handleY, CurveType curveType, size_t segments) noexcept
				: m_position(position), m_handleXIn(-handleX), m_handleXOut(handleX), m_handleYIn(-handleY), m_handleYOut(handleY), m_curveType(curveType), m_segments(segments)
			{

			}

			NURBSPoint (const Vector< dim_t, type_t > & position, const Vector< dim_t, type_t > & handleXIn, const Vector< dim_t, type_t > & handleXOut, const Vector< dim_t, type_t > & handleYIn, const Vector< dim_t, type_t > & handleYOut, CurveType curveType, size_t segments) noexcept
				: m_position(position), m_handleXIn(handleXIn), m_handleXOut(handleXOut), m_handleYIn(handleYIn), m_handleYOut(handleYOut), m_curveType(curveType), m_segments(segments)
			{

			}

			NURBSPoint &
			setCurveType (CurveType bezierType) noexcept
			{
				m_curveType = bezierType;

				return *this;
			}

			[[nodiscard]]
			CurveType
			curveType () const noexcept
			{
				return m_curveType;
			}

			NURBSPoint &
			setSegments (size_t segments) noexcept
			{
				m_segments = segments;

				return *this;
			}

			[[nodiscard]]
			size_t
			segments () const noexcept
			{
				return m_segments;
			}

			[[nodiscard]]
			const Vector< dim_t, type_t > &
			position () const noexcept
			{
				return m_position;
			}

			[[nodiscard]]
			const Vector< dim_t, type_t > &
			handleXIn () const noexcept
			{
				return m_handleXIn;
			}

			[[nodiscard]]
			const Vector< dim_t, type_t > &
			handleXOut () const noexcept
			{
				return m_handleXOut;
			}

			[[nodiscard]]
			const Vector< dim_t, type_t > &
			handleYIn () const noexcept
			{
				return m_handleYIn;
			}

			[[nodiscard]]
			const Vector< dim_t, type_t > &
			handleYOut () const noexcept
			{
				return m_handleYOut;
			}

		private:

			Vector< dim_t, type_t > m_position;
			Vector< dim_t, type_t > m_handleXIn;
			Vector< dim_t, type_t > m_handleXOut;
			Vector< dim_t, type_t > m_handleYIn;
			Vector< dim_t, type_t > m_handleYOut;
			CurveType m_curveType = CurveType::None;
			size_t m_segments = 1;
	};
}
