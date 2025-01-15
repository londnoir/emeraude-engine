/*
 * src/Libraries/Math/BSpline.hpp
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

/* Local inclusions. */
#include "BSplinePoint.hpp"
#include "Vector.hpp"

namespace Libraries::Math
{
	/**
	 * @brief The BSpline class.
	 * @tparam dim_t The dimension of the vector. This can be 2, 3 or 4.
	 * @tparam number_t The type of number. Default float.
	 */
	template< size_t dim_t, typename number_t = float >
	requires (dim_t == 2 || dim_t == 3 || dim_t == 4) && std::is_arithmetic_v< number_t >
	class BSpline final
	{
		public:

			using Callback = std::function< bool (float time, const Vector< dim_t, number_t > & position) >;

			/**
			 * @brief Default constructor.
			 */
			BSpline () noexcept = default;

			/**
			 * @brief BSpline
			 * @param defaultSegments
			 * @param defaultCurveType
			 */
			explicit
			BSpline (size_t defaultSegments, CurveType defaultCurveType = CurveType::BezierQuadratic) noexcept
				: m_defaultSegments(defaultSegments), m_defaultCurveType(defaultCurveType)
			{

			}

			/**
			 * @brief Sets the default number of segments.
			 * @param defaultSegments The number of segments.
			 * @return void
			 */
			void
			setDefaultSegments (size_t defaultSegments) noexcept
			{
				if ( defaultSegments < 1 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", default segment should at least be 1 !" "\n";

					return;
				}

				m_defaultSegments = defaultSegments;
			}

			/**
			 * @brief Returns the default number of segments.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			defaultSegments () const noexcept
			{
				return m_defaultSegments;
			}

			/**
			 * @brief Sets the default curve type.
			 * @param defaultCurveType The curve type.
			 * @return void
			 */
			void
			setDefaultCurveType (CurveType defaultCurveType) noexcept
			{
				m_defaultCurveType = defaultCurveType;
			}

			/**
			 * @brief Returns the default curve type.
			 * @return CurveType
			 */
			[[nodiscard]]
			CurveType
			defaultCurveType () const noexcept
			{
				return m_defaultCurveType;
			}

			/**
			 * @brief Adds a point.
			 * @param position A reference to a vector.
			 * @return BSplinePoint< dim_t, number_t > &
			 */
			BSplinePoint< dim_t, number_t > &
			addPoint (const Vector< dim_t, number_t > & position) noexcept
			{
				return m_points.emplace_back(position, m_defaultCurveType, m_defaultSegments);
			}

			/**
			 * @brief Adds a point.
			 * @param position A reference to a vector.
			 * @param handle A reference to a vector.
			 * @return BSplinePoint< dim_t, number_t > &
			 */
			BSplinePoint< dim_t, number_t > &
			addPoint (const Vector< dim_t, number_t > & position, const Vector< dim_t, number_t > & handle) noexcept
			{
				return m_points.emplace_back(position, handle, m_defaultCurveType, m_defaultSegments);
			}

			/**
			 * @brief Adds a point.
			 * @param position A reference to a vector.
			 * @param handleIn A reference to a vector.
			 * @param handleOut A reference to a vector.
			 * @return BSplinePoint< dim_t, number_t > &
			 */
			BSplinePoint< dim_t, number_t > &
			addPoint (const Vector< dim_t, number_t > & position, const Vector< dim_t, number_t > & handleIn, const Vector< dim_t, number_t > & handleOut) noexcept
			{
				return m_points.emplace_back(position, handleIn, handleOut, m_defaultCurveType, m_defaultSegments);
			}

			/**
			 * @brief Synthesize the curve.
			 * @param callback
			 * @param constant Default false.
			 * @return bool
			 */
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
					size_t segments = 0;

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
						/* Simple point. */
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

			/**
			 * @brief synthesizeLinear
			 * @param callback
			 * @param currentPoint
			 * @param nextPoint
			 * @param currentTime
			 * @param timeStep
			 * @return bool
			 */
			bool
			synthesizeLinear (const Callback & callback, const BSplinePoint< dim_t, number_t > & currentPoint, const BSplinePoint< dim_t, number_t > & nextPoint, float & currentTime, float timeStep) const noexcept
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

			/**
			 * @brief synthesizeQuadratic
			 * @param callback
			 * @param currentPoint
			 * @param nextPoint
			 * @param currentTime
			 * @param timeStep
			 * @return bool
			 */
			bool
			synthesizeQuadratic (const Callback & callback, const BSplinePoint< dim_t, number_t > & currentPoint, const BSplinePoint< dim_t, number_t > & nextPoint, float & currentTime, float timeStep) const noexcept
			{
				/* Time step along a segment. */
				const auto factorStep = 1.0F / currentPoint.segments();

				auto factor = 0.0F;

				for ( size_t segment = 0; segment < currentPoint.segments(); segment++ )
				{
					/* Gets the handle in absolute position. */
					const auto handleOut = currentPoint.position() + currentPoint.handleOut();

					if ( !callback(currentTime, Vector< dim_t, number_t >::quadraticBezierInterpolation(currentPoint.position(), handleOut, nextPoint.position(), factor)) )
					{
						return false;
					}

					factor += factorStep;

					currentTime += timeStep;
				}

				return true;
			}

			/**
			 * @brief synthesizeCubic
			 * @param callback
			 * @param currentPoint
			 * @param nextPoint
			 * @param currentTime
			 * @param timeStep
			 * @return bool
			 */
			bool
			synthesizeCubic (const Callback & callback, const BSplinePoint< dim_t, number_t > & currentPoint, const BSplinePoint< dim_t, number_t > & nextPoint, float & currentTime, float timeStep) const noexcept
			{
				/* Time step along a segment. */
				const auto factorStep = 1.0F / currentPoint.segments();

				auto factor = 0.0F;

				for ( size_t segment = 0; segment < currentPoint.segments(); segment++ )
				{
					/* Gets the handle in absolute position. */
					const auto handleOut = currentPoint.position() + currentPoint.handleOut();
					const auto handleIn = nextPoint.position() + nextPoint.handleIn();

					if ( !callback(currentTime, Vector< dim_t, number_t >::cubicBezierInterpolation(currentPoint.position(), handleOut, handleIn, nextPoint.position(), factor)) )
					{
						return false;
					}

					factor += factorStep;

					currentTime += timeStep;
				}

				return true;
			}

			std::vector< BSplinePoint< dim_t, number_t > > m_points{};
			size_t m_defaultSegments{1};
			CurveType m_defaultCurveType{CurveType::None};
	};
}
