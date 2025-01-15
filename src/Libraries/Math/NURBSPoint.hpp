/*
 * src/Libraries/Math/NURBSPoint.hpp
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
#include <cmath>
#include <cstddef>
#include <type_traits>

/* Local inclusions. */
#include "BSplinePoint.hpp"
#include "Vector.hpp"

namespace Libraries::Math
{
	template< size_t dim_t, typename number_t = float >
	requires (dim_t == 2 || dim_t == 3 || dim_t == 4) && std::is_arithmetic_v< number_t >
	class NURBSPoint final
	{
		public:

			NURBSPoint (const Vector< dim_t, number_t > & position, CurveType curveType, size_t segments) noexcept
				: m_position(position), m_curveType(curveType), m_segments(segments)
			{

			}

			NURBSPoint (const Vector< dim_t, number_t > & position, const Vector< dim_t, number_t > & handleX, const Vector< dim_t, number_t > & handleY, CurveType curveType, size_t segments) noexcept
				: m_position(position), m_handleXIn(-handleX), m_handleXOut(handleX), m_handleYIn(-handleY), m_handleYOut(handleY), m_curveType(curveType), m_segments(segments)
			{

			}

			NURBSPoint (const Vector< dim_t, number_t > & position, const Vector< dim_t, number_t > & handleXIn, const Vector< dim_t, number_t > & handleXOut, const Vector< dim_t, number_t > & handleYIn, const Vector< dim_t, number_t > & handleYOut, CurveType curveType, size_t segments) noexcept
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
			const Vector< dim_t, number_t > &
			position () const noexcept
			{
				return m_position;
			}

			[[nodiscard]]
			const Vector< dim_t, number_t > &
			handleXIn () const noexcept
			{
				return m_handleXIn;
			}

			[[nodiscard]]
			const Vector< dim_t, number_t > &
			handleXOut () const noexcept
			{
				return m_handleXOut;
			}

			[[nodiscard]]
			const Vector< dim_t, number_t > &
			handleYIn () const noexcept
			{
				return m_handleYIn;
			}

			[[nodiscard]]
			const Vector< dim_t, number_t > &
			handleYOut () const noexcept
			{
				return m_handleYOut;
			}

		private:

			Vector< dim_t, number_t > m_position;
			Vector< dim_t, number_t > m_handleXIn;
			Vector< dim_t, number_t > m_handleXOut;
			Vector< dim_t, number_t > m_handleYIn;
			Vector< dim_t, number_t > m_handleYOut;
			CurveType m_curveType{CurveType::None};
			size_t m_segments{1};
	};
}
