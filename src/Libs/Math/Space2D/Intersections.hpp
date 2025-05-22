/*
* src/Libs/Math/Space2D/Intersections.hpp
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

/* Local inclusions. */
#include "Segment.hpp"
#include "Line.hpp"
#include "Triangle.hpp"
#include "Circle.hpp"
//#include "Rectangle.hpp"

namespace EmEn::Libs::Math::Space2D
{
	/**
	 * @brief Finds the intersection between two lines using the "Cramer" method.
	 * @tparam precision_t The data precision. Default float.
	 * @param ax
	 * @param ay
	 * @param bx
	 * @param by
	 * @param cx
	 * @param cy
	 * @param dx
	 * @param dy
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	isIntersecting (precision_t ax, precision_t ay, precision_t bx, precision_t by, precision_t cx, precision_t cy, precision_t dx, precision_t dy, Point< precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		/* NOTE: Direction vectors of the lines */
		const precision_t dir_ab_x = ax - bx;
		const precision_t dir_ab_y = ay - by;
		const precision_t dir_cd_x = cx - dx;
		const precision_t dir_cd_y = cy - dy;

		/* NOTE: Determinant of the system. If zero, the lines are parallel. */
		const precision_t det = (dir_ab_x * dir_cd_y) - (dir_ab_y * dir_cd_x);

		if ( std::abs(det) < std::numeric_limits< precision_t >::epsilon() )
		{
			/* NOTE: Parallel lines, no single intersection. */
			return false;
		}

		/* NOTE: Constant terms of line equations (form Ax + By = C). */
		const precision_t c1 = (ax * by) - (ay * bx);
		const precision_t c2 = (cx * dy) - (cy * dx);

		/* NOTE: Application of Cramer's method to find the point of intersection. */
		intersection[X] = (c1 * dir_cd_x - dir_ab_x * c2) / det;
		intersection[Y] = (c1 * dir_cd_y - dir_ab_y * c2) / det;

		return true;
	}

	/**
	 * @brief Checks if segments are intersecting and gives the intersection point.
	 * @tparam precision_t The data precision. Default float.
	 * @param segmentAStart A reference to a point for the first segment starting point.
	 * @param segmentAEnd A reference to a point for the first segment ending point.
	 * @param segmentBStart A reference to a point for the second segment starting point.
	 * @param segmentBEnd A reference to a point for the second segment ending point.
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	isIntersecting (const Point< precision_t > & segmentAStart, const Point< precision_t > & segmentAEnd, const Point< precision_t > & segmentBStart, const Point< precision_t > & segmentBEnd, Point< precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		/* NOTE: Direction vectors for each segment. */
		const Point< precision_t > dirA = segmentAEnd - segmentAStart;
		const Point< precision_t > dirB = segmentBEnd - segmentBStart;

		/* NOTE: The denominator is the 2D cross-product of the direction vectors. If it is zero, the lines are parallel or collinear. */
		const precision_t denominator = Point< precision_t >::crossProduct(dirA, dirB);

		/* NOTE: Check for parallel lines (denominator close to zero). */
		if ( std::abs(denominator) < std::numeric_limits< precision_t >::epsilon() )
		{
			/* NOTE: No unique intersection possible.
			 * TODO: An overlap check for collinear segments could be added here. */
			return false;
		}

		/* NOTE: The vector between the starting points of the two segments. */
		const Point< precision_t > startDiff = segmentBStart - segmentAStart;

		/* NOTE: Computes the parameters t and u. 't' is the parameter for segment A, 'u' for segment B.
		 * The intersection occurs at `segmentAStart + t * dirA` and also at `segmentBStart + u * dirB`. */
		const precision_t t = Point< precision_t >::crossProduct(startDiff, dirB) / denominator;
		const precision_t u = Point< precision_t >::crossProduct(startDiff, dirA) / denominator;

		/* NOTE: The intersection is only valid if it lies ON both segments.
		 * For this, the parameters t and u must be in the interval [0, 1]. */
		if ( t >= 0 && t <= 1 && u >= 0 && u <= 1 )
		{
			/* NOTE: Calculates the intersection point and stores it in the output parameter. */
			intersection = segmentAStart + dirA * t;

			return true;
		}

		/* NOTE: The lines intersect, but outside the segments. */
		return false;
	}

	/**
	 * @brief Checks if segments are intersecting and gives the intersection point.
	 * @tparam precision_t The data precision. Default float.
	 * @param segmentA A reference to a segment.
	 * @param segmentB A reference to a segment.
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	isIntersecting (const Segment< precision_t > & segmentA, const Segment< precision_t > & segmentB, Point< precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		return isIntersecting(segmentA.start(), segmentA.end(), segmentB.start(), segmentB.end(), intersection);
	}

	/**
	 * @brief Checks if a segment is intersecting a triangle and gives the intersection point.
	 * @tparam precision_t The data precision. Default float.
	 * @param segment A reference to a segment.
	 * @param triangle A reference to a triangle.
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	isIntersecting (const Segment< precision_t > & segment, const Triangle< precision_t > & triangle, Point< precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		std::vector< Point< precision_t > > intersections;
		Point< precision_t > currentIntersection;

		/* NOTE: Test the intersection with each edge and store the results. */
		if ( isIntersecting(segment.start(), segment.end(), triangle.pointA(), triangle.pointB(), currentIntersection) )
		{
			intersections.emplace_back(currentIntersection);
		}

		if ( isIntersecting(segment.start(), segment.end(), triangle.pointB(), triangle.pointC(), currentIntersection) )
		{
			intersections.emplace_back(currentIntersection);
		}

		if ( isIntersecting(segment.start(), segment.end(), triangle.pointC(), triangle.pointA(), currentIntersection) )
		{
			intersections.emplace_back(currentIntersection);
		}

		if ( !intersections.empty() )
		{
			/* NOTE: The segment crosses one or more edges. Find the closest point. */
			precision_t minDistSq = std::numeric_limits< precision_t >::max();
			Point< precision_t > closestIntersection;

			for ( const auto & point : intersections )
			{
				const precision_t distSq = Point< precision_t >::distanceSquared(segment.start(), point);

				if ( distSq < minDistSq )
				{
					minDistSq = distSq;
					closestIntersection = point;
				}
			}

			intersection = closestIntersection;

			return true;
		}

		/* NOTE: If no edge is cut, check if the segment is inside. */
		if ( contains(segment.start(), triangle) )
		{
			/* NOTE: The segment starts inside the triangle. */
			intersection = segment.start();

			return true;
		}

		/* NOTE: No intersection. */
		return false;
	}

	/**
	 * @brief Checks if a segment is intersecting a circle and gives the intersection point.
	 * @tparam precision_t The data precision. Default float.
	 * @param segment A reference to a segment.
	 * @param circle A reference to a circle.
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	isIntersecting (const Segment< precision_t > & segment, const Circle< precision_t > & circle, Point< precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		const Point< precision_t > segmentStart = segment.start();
		const Point< precision_t > segmentDirection = segment.end() - segmentStart;
		const Point< precision_t > centerToStart = segmentStart - circle.position();

		const precision_t a = segmentDirection.lengthSquared();
		const precision_t b = 2 * Vector<2, precision_t>::dotProduct(segmentDirection, centerToStart);
		const precision_t c = centerToStart.lengthSquared() - (circle.radius() * circle.radius());

		if ( std::abs(a) < std::numeric_limits< precision_t >::epsilon() )
		{
			/* NOTE: The segment is a point, it cannot intersect a circumference. */
			return false;
		}

		const precision_t discriminant = b * b - 4 * a * c;

		if ( discriminant < 0 )
		{
			/* NOTE: No real solution, the line never intersects the circle. */
			return false;
		}

		const precision_t sqrtDiscriminant = std::sqrt(discriminant);
		const precision_t inv2a = static_cast< precision_t >(1) / (2 * a);

		/* NOTE: The two potential intersection points of the infinite line with the circle. */
		const precision_t t1 = (-b - sqrtDiscriminant) * inv2a;
		const precision_t t2 = (-b + sqrtDiscriminant) * inv2a;

		precision_t t_final = std::numeric_limits< precision_t >::max();
		bool intersectionFound = false;

		/* NOTE: We are looking for the smallest valid value of 't' (between 0 and 1). */
		if ( t1 >= 0 && t1 <= 1 )
		{
			t_final = t1;
			intersectionFound = true;
		}

		/* NOTE: t2 is necessarily greater than t1. If t1 is valid, t2 cannot be a better solution.
		 * We only check t2 if t1 is not in the interval [0,1]. */
		if ( t2 >= 0 && t2 <= 1 && t2 < t_final )
		{
			t_final = t2;
			intersectionFound = true;
		}

		if ( intersectionFound )
		{
			intersection = segmentStart + segmentDirection * t_final;

			return true;
		}

		return false;
	}
}
