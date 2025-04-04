/*
 * src/Libs/Math/NURBS.hpp
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
#include <cstddef>
#include <functional>
#include <type_traits>
#include <vector>

/* Local inclusions. */
#include "BSplinePoint.hpp"
#include "NURBSPoint.hpp"
#include "Vector.hpp"

namespace EmEn::Libs::Math
{
	/**
	 * @brief The NURBS class.
	 * @tparam dim_t The dimension of the vector. This can be 2, 3 or 4.
	 * @tparam number_t The type of number. Default float.
	 */
	template< size_t dim_t, typename number_t = float >
	requires (dim_t == 2 || dim_t == 3 || dim_t == 4) && std::is_arithmetic_v< number_t >
	class NURBS final
	{
		public:

			using Callback = std::function< bool (float currentTime, const Vector< dim_t, number_t > & position) >;

			NURBS () noexcept = default;

			explicit NURBS (size_t segments, CurveType curveType = CurveType::BezierCubic) noexcept
				: m_defaultSegments(segments), m_defaultCurveType(curveType)
			{

			}

			void
			setDefaultSegments (size_t segments) noexcept
			{
				if ( segments > 0 )
				{
					m_defaultSegments = segments;
				}
			}

			[[nodiscard]]
			size_t
			defaultSegments () const noexcept
			{
				return m_defaultSegments;
			}

			void
			setDefaultCurveType (CurveType bezierType) noexcept
			{
				m_defaultCurveType = bezierType;
			}

			[[nodiscard]]
			CurveType
			defaultCurveType () const noexcept
			{
				return m_defaultCurveType;
			}

			NURBSPoint< dim_t, number_t > &
			addPoint (const Vector< dim_t, number_t > & position) noexcept
			{
				return m_points.emplace_back(position, m_defaultCurveType, m_defaultSegments);
			}

			NURBSPoint< dim_t, number_t > &
			addPoint (const Vector< dim_t, number_t > & position, const Vector< dim_t, number_t > & handleX, const Vector< dim_t, number_t > & handleY) noexcept
			{
				return m_points.emplace_back(position, handleX, handleY, m_defaultCurveType, m_defaultSegments);
			}

			NURBSPoint< dim_t, number_t > &
			addPoint (const Vector< dim_t, number_t > & position, const Vector< dim_t, number_t > & handleXIn, const Vector< dim_t, number_t > & handleXOut, const Vector< dim_t, number_t > & handleYIn, const Vector< dim_t, number_t > & handleYOut) noexcept
			{
				return m_points.emplace_back(position, handleXIn, handleXOut, handleYIn, handleYOut, m_defaultCurveType, m_defaultSegments);
			}

			bool
			synthesize (const Callback & callback, bool constant = false) const noexcept
			{
				if ( m_points.size() < 2 )
				{
					return false;
				}

				auto timeStep = 0.0F;

				/* In non-constant mode, the time step between
				 * each point will be equivalent. */
				if ( !constant )
				{
					auto segments = 0UL;

					for ( auto index = m_points.size() - 1; index > 0; --index )
					{
						segments += m_points[index - 1].segments();
					}

					timeStep = 1.0F / static_cast< float >(segments);
				}

				auto currentTime = 0.0F;

				for ( size_t index = 0; index < m_points.size(); index++ )
				{
					const auto & currentPoint = m_points[index];

					/* In constant mode, we rescale the time step
					 * by segment count against the whole spline. */
					if ( constant )
					{
						timeStep = 1.0F / (m_points.size() - 1);
						timeStep /= currentPoint.segments();
					}

					if ( currentPoint.segments() > 1 )
					{
						/* Curve generation. */
						switch ( m_points[index].curveType() )
						{
							case CurveType::None :
								if ( !this->synthesizeLinear(callback, currentPoint, m_points[index + 1], currentTime, timeStep) )
								{
									return false;
								}
								break;

							case CurveType::BezierQuadratic :
								if ( !this->synthesizeQuadratic(callback, currentPoint, m_points[index + 1], currentTime, timeStep) )
								{
									return false;
								}
								break;

							case CurveType::BezierCubic :
								if ( !this->synthesizeCubic(callback, currentPoint, m_points[index + 1], currentTime, timeStep) )
								{
									return false;
								}
								break;

							default:
								break;
						}
					}
					else
					{
						/* Simple point */
						if ( !callback(currentTime, currentPoint.position()) )
						{
							return false;
						}

						currentTime += timeStep;
					}
				}

				return true;
			}

		private:

			bool
			synthesizeLinear (const Callback & callback, const NURBSPoint< dim_t, number_t > & currentPoint, const NURBSPoint< dim_t, number_t > & nextPoint, float & currentTime, float timeStep) const noexcept
			{
				/* Time step along a segment. */
				const auto factorStep = 1.0F / currentPoint.segments();

				auto factor = 0.0F;

				for ( size_t segment = 0; segment < currentPoint.segments(); segment++ )
				{
					if ( !callback(currentTime, linearInterpolation(currentPoint.position(), nextPoint.position(), factor)) )
					{
						return false;
					}

					factor += factorStep;

					currentTime += timeStep;
				}

				return true;
			}

			bool
			synthesizeQuadratic (const Callback & callback, const NURBSPoint< dim_t, number_t > & currentPoint, const NURBSPoint< dim_t, number_t > & nextPoint, float & currentTime, float timeStep) const noexcept
			{
				/* Time step along a segment. */
				const auto factorStep = 1.0F / currentPoint.segments();

				auto factor = 0.0F;

				for ( size_t segment = 0; segment < currentPoint.segments(); segment++ )
				{
					/* Gets the handle-out in absolute position. */
					const auto handleOut = currentPoint.position() + currentPoint.handleOut();
					const auto interpolationA = linearInterpolation(currentPoint.position(), handleOut, factor);
					const auto interpolationB = linearInterpolation(handleOut, nextPoint.position(), factor);

					if ( !callback(currentTime, linearInterpolation(interpolationA, interpolationB, factor)) )
					{
						return false;
					}

					factor += factorStep;

					currentTime += timeStep;
				}

				return true;
			}

			bool
			synthesizeCubic (const Callback & callback, const NURBSPoint< dim_t, number_t > & currentPoint, const NURBSPoint< dim_t, number_t > & nextPoint, float & currentTime, float timeStep) const noexcept
			{
				/* Time step along a segment. */
				const auto factorStep = 1.0F / currentPoint.segments();

				auto factor = 0.0F;

				for ( size_t segment = 0; segment < currentPoint.segments(); segment++ )
				{
					/* Gets the handle-out in absolute position. */
					const auto handleOut = currentPoint.position() + currentPoint.handleOut();
					const auto interpolationA = linearInterpolation(
						linearInterpolation(currentPoint.position(), handleOut, factor),
						linearInterpolation(handleOut, nextPoint.position(), factor),
						factor
					);

					/* Gets the handle-in in absolute position. */
					const auto handleIn = nextPoint.position() + nextPoint.handleIn();
					const auto interpolationB = linearInterpolation(
						linearInterpolation(currentPoint.position(), handleIn, factor),
						linearInterpolation(handleIn, nextPoint.position(), factor),
						factor
					);

					if ( !callback(currentTime, linearInterpolation(interpolationA, interpolationB, factor)) )
					{
						return false;
					}

					factor += factorStep;

					currentTime += timeStep;
				}

				return true;
			}

			std::vector< NURBSPoint< dim_t, number_t > > m_points;
			size_t m_defaultSegments = 1;
			CurveType m_defaultCurveType = CurveType::None;
	};
}
