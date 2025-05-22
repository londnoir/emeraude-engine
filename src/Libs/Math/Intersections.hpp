/*
* src/Libs/Math/Intersections.hpp
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
#include <limits>
#include <vector>

/* Local inclusions. */
#include "Segment.hpp"
#include "Triangle.hpp"
#include "Circle.hpp"
#include "Sphere.hpp"

namespace EmEn::Libs::Math
{
	/**
	 * @brief Checks if a 2D triangle contains a 2D point.
	 * @tparam precision_t The data precision. Default float.
	 * @param point A reference to vector.
	 * @param triangle A reference to triangle.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	contains (const Vector< 2, precision_t > & point, const Triangle< 2, precision_t > & triangle) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		const auto & pA = triangle.pointA();
		const auto & pB = triangle.pointB();
		const auto & pC = triangle.pointC();

		/* NOTE: This method checks if the point is on the same side of each edge. The side is determined by the sign of the 2D cross product. */
		const precision_t crossAB = Vector<2, precision_t>::crossProduct(pB - pA, point - pA);
		const precision_t crossBC = Vector<2, precision_t>::crossProduct(pC - pB, point - pB);
		const precision_t crossCA = Vector<2, precision_t>::crossProduct(pA - pC, point - pC);

		/* NOTE: If the point is inside, the three cross products will have the same sign (or will be zero if the point is on an edge).
		 * We check both directions (clockwise and counterclockwise) to be robust. */
		const bool allNonNegative = (crossAB >= 0) && (crossBC >= 0) && (crossCA >= 0);
		const bool allNonPositive = (crossAB <= 0) && (crossBC <= 0) && (crossCA <= 0);

		return allNonNegative || allNonPositive;
	}

	/**
	 * @brief Finds the intersection between two 2D lines using the "Cramer" method.
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
	findIntersection (precision_t ax, precision_t ay, precision_t bx, precision_t by, precision_t cx, precision_t cy, precision_t dx, precision_t dy, Vector< 2, precision_t > & intersection) noexcept
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
	 * @brief Checks if 2D segments are intersecting and gives the intersection point.
	 * @tparam precision_t The data precision. Default float.
	 * @param segmentAStart A reference to a vector for the first segment starting point.
	 * @param segmentAEnd A reference to a vector for the first segment ending point.
	 * @param segmentBStart A reference to a vector for the second segment starting point.
	 * @param segmentBEnd A reference to a vector for the second segment ending point.
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	findIntersection (const Vector< 2, precision_t > & segmentAStart, const Vector< 2, precision_t > & segmentAEnd, const Vector< 2, precision_t > & segmentBStart, const Vector< 2, precision_t > & segmentBEnd, Vector< 2, precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		/* NOTE: Direction vectors for each segment. */
		const Vector< 2, precision_t > dirA = segmentAEnd - segmentAStart;
		const Vector< 2, precision_t > dirB = segmentBEnd - segmentBStart;

		/* NOTE: The denominator is the 2D cross-product of the direction vectors. If it is zero, the lines are parallel or collinear. */
		const precision_t denominator = Vector< 2, precision_t >::crossProduct(dirA, dirB);

		/* NOTE: Check for parallel lines (denominator close to zero). */
		if ( std::abs(denominator) < std::numeric_limits< precision_t >::epsilon() )
		{
			/* NOTE: No unique intersection possible.
			 * TODO: An overlap check for collinear segments could be added here. */
			return false;
		}

		/* NOTE: The vector between the starting points of the two segments. */
		const Vector< 2, precision_t > startDiff = segmentBStart - segmentAStart;

		/* NOTE: Computes the parameters t and u. 't' is the parameter for segment A, 'u' for segment B.
		 * The intersection occurs at `segmentAStart + t * dirA` and also at `segmentBStart + u * dirB`. */
		const precision_t t = Vector< 2, precision_t >::crossProduct(startDiff, dirB) / denominator;
		const precision_t u = Vector< 2, precision_t >::crossProduct(startDiff, dirA) / denominator;

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
	 * @brief Checks if 2D segments are intersecting and gives the intersection point.
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
	findIntersection (const Segment< 2, precision_t > & segmentA, const Segment< 2, precision_t > & segmentB, Vector< 2, precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		return findIntersection(segmentA.start(), segmentA.end(), segmentB.start(), segmentB.end(), intersection);
	}

	/**
	 * @brief Checks if a 2D segment is intersecting a 2D triangle and gives the intersection point.
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
	findIntersection (const Segment< 2, precision_t > & segment, const Triangle< 2, precision_t > & triangle, Vector< 2, precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		std::vector< Vector< 2, precision_t > > intersections;
		Vector< 2, precision_t > currentIntersection;

		/* NOTE: Test the intersection with each edge and store the results. */
		if ( findIntersection(segment.start(), segment.end(), triangle.pointA(), triangle.pointB(), currentIntersection) )
		{
			intersections.emplace_back(currentIntersection);
		}

		if ( findIntersection(segment.start(), segment.end(), triangle.pointB(), triangle.pointC(), currentIntersection) )
		{
			intersections.emplace_back(currentIntersection);
		}

		if ( findIntersection(segment.start(), segment.end(), triangle.pointC(), triangle.pointA(), currentIntersection) )
		{
			intersections.emplace_back(currentIntersection);
		}

		if ( !intersections.empty() )
		{
			/* NOTE: The segment crosses one or more edges. Find the closest point. */
			precision_t minDistSq = std::numeric_limits< precision_t >::max();
			Vector< 2, precision_t > closestIntersection;

			for ( const auto & point : intersections )
			{
				const precision_t distSq = Vector< 2, precision_t >::distanceSquared(segment.start(), point);

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
	 * @brief Checks if a 2D segment is intersecting a 2D circle and gives the intersection point.
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
	findIntersection (const Segment< 2, precision_t > & segment, const Circle< precision_t > & circle, Vector< 2, precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		const Vector< 2, precision_t > segmentStart = segment.start();
		const Vector< 2, precision_t > segmentDirection = segment.end() - segmentStart;
		const Vector< 2, precision_t > centerToStart = segmentStart - circle.position();

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

	/**
	 * @brief Checks if a 3D segment intersects a 3D triangle using the "Möller-Trumbore" algorithm.
	 * @note The intersection is valid for both faces of the triangle (no backface culling).
	 * @tparam precision_t The data precision. Default float.
	 * @param segmentStart A reference to a vector for segment starting point.
	 * @param segmentEnd A reference to a vector for segment ending point.
	 * @param trianglePointA A reference to a vector for the first triangle point.
	 * @param trianglePointB A reference to a vector for the second triangle point.
	 * @param trianglePointC A reference to a vector for the third triangle point.
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	findIntersection (const Vector< 3, precision_t > & segmentStart, const Vector< 3, precision_t > & segmentEnd, const Vector< 3, precision_t > & trianglePointA, const Vector< 3, precision_t > & trianglePointB, const Vector< 3, precision_t > & trianglePointC, Vector< 3, precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		/* 1. Define the vectors for the segment and edges of the triangle. */
		const Vector< 3, precision_t > segmentDirection = segmentEnd - segmentStart;
		const Vector< 3, precision_t > edge1 = trianglePointB - trianglePointA;
		const Vector< 3, precision_t > edge2 = trianglePointC - trianglePointA;

		/* 2. Calculate the determinant. If close to zero, the segment is parallel to the plane of the triangle. */
		const Vector< 3, precision_t > h = Vector< 3, precision_t >::crossProduct(segmentDirection, edge2);
		const auto det = Vector< 3, precision_t >::dotProduct(edge1, h);

		if ( det > -std::numeric_limits< precision_t >::epsilon() && det < std::numeric_limits< precision_t >::epsilon() )
		{
			/* NOTE: Segment parallel to the triangle. */
			return false;
		}

		const auto invDet = static_cast< precision_t >(1) / det;

		/* 3. Calculate the barycentric coordinate 'u' */
		const Vector< 3, precision_t > s = segmentStart - trianglePointA;
		const precision_t u = invDet * Vector< 3, precision_t >::dotProduct(s, h);

		if ( u < static_cast< precision_t >(0) || u > static_cast< precision_t >(1) )
		{
			/* NOTE: The point of intersection is outside the triangle. */
			return false;
		}

		/* 4. Calculate the barycentric coordinate 'v' */
		const Vector< 3, precision_t > q = Vector< 3, precision_t >::crossProduct(s, edge1);
		const precision_t v = invDet * Vector< 3, precision_t >::dotProduct(segmentDirection, q);

		if ( v < static_cast< precision_t >(0) || u + v > static_cast< precision_t >(1) )
		{
			/* NOTE: The point of intersection is outside the triangle. */
			return false;
		}

		/* 5. Calculate 't', the distance along the segment where the intersection occurs. */
		const precision_t t = invDet * Vector< 3, precision_t >::dotProduct(edge2, q);

		/* NOTE: We check that the intersection is located ON the segment (t between 0 and 1) */
		if ( t >= static_cast< precision_t >(0) && t <= static_cast< precision_t >(1) )
		{
			/* NOTE: The intersection is valid and lies on the segment. */
			intersection = segmentStart + segmentDirection * t;

			return true;
		}

		/* NOTE: The intersection is outside the segment. */
		return false;
	}

	/**
	 * @brief Checks if a 3D segment intersects a 3D triangle using the "Möller-Trumbore" algorithm.
	 * @note The intersection is valid for both faces of the triangle (no backface culling).
	 * @tparam precision_t The data precision. Default float.
	 * @param segment A reference to a 3D segment.
	 * @param trianglePointA A reference to a vector for the first triangle point.
	 * @param trianglePointB A reference to a vector for the second triangle point.
	 * @param trianglePointC A reference to a vector for the third triangle point.
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	findIntersection (const Segment< 3, precision_t > & segment, const Vector< 3, precision_t > & trianglePointA, const Vector< 3, precision_t > & trianglePointB, const Vector< 3, precision_t > & trianglePointC, Vector< 3, precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		return findIntersection(
			segment.start(), segment.end(),
			trianglePointA, trianglePointB, trianglePointC,
			intersection
		);
	}

	/**
	 * @brief Checks if a 3D segment intersects a 3D triangle using the "Möller-Trumbore" algorithm.
	 * @note The intersection is valid for both faces of the triangle (no backface culling).
	 * @tparam precision_t The data precision. Default float.
	 * @param segment A reference to a 3D segment.
	 * @param triangle A reference to a triangle.
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	findIntersection (const Segment< 3, precision_t > & segment, const Triangle< 3, precision_t > & triangle, Vector< 3, precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		return findIntersection(
			segment.start(), segment.end(),
			triangle.pointA(), triangle.pointB(), triangle.pointC(),
			intersection
		);
	}

	/**
	 * @brief Checks if a 3D segment intersects a 3D sphere.
	 * @tparam precision_t The data precision. Default float.
	 * @param segment A reference to a 3D segment.
	 * @param sphere A reference to a sphere.
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	findIntersection (const Segment< 3, precision_t > & segment, const Sphere< precision_t > & sphere, Vector< 3, precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		const auto & segmentStart = segment.start();
		const auto & segmentEnd = segment.end();
		const auto & center = sphere.position();
		const auto radius = sphere.radius();

		const Vector< 3, precision_t > segmentDirection = segmentEnd - segmentStart;
		/* NOTE: Vector from the center of the sphere to the start of the segment. */
		const Vector< 3, precision_t > oc = segmentStart - center;

		const precision_t a = Vector< 3, precision_t >::dotProduct(segmentDirection, segmentDirection);
		const precision_t b = static_cast< precision_t >(2) * Vector< 3, precision_t >::dotProduct(segmentDirection, oc);
		const precision_t c = Vector< 3, precision_t >::dotProduct(oc, oc) - radius * radius;

		/* NOTE: Calculation of the discriminant of the quadratic equation. */
		const precision_t discriminant = b * b - 4 * a * c;

		/* NOTE: If the discriminant is negative, the line never intersects the sphere. */
		if ( discriminant < 0 )
		{
		    return false;
		}

		/* NOTE: Solving the equation to find the intersection points t1 and t2. */
		const precision_t sqrtDiscriminant = std::sqrt(discriminant);
		const precision_t t1 = (-b - sqrtDiscriminant) / (static_cast< precision_t >(2) * a);
		const precision_t t2 = (-b + sqrtDiscriminant) / (static_cast< precision_t >(2) * a);

		/* NOTE: We look for the smallest positive t in the interval [0, 1] to find
		 * the intersection point closest to the start of the segment. */

		/* NOTE: Case 1: The first intersection point (t1) is on the segment. */
		if ( t1 >= 0 && t1 <= 1 )
		{
		    intersection = segmentStart + segmentDirection * t1;

		    return true;
		}

		/* NOTE: Case 2: The second intersection point (t2) is on the segment. This happens if the segment starts inside the sphere. */
		if ( t2 >= 0 && t2 <= 1 )
		{
		    intersection = segmentStart + segmentDirection * t2;

		    return true;
		}

		/* NOTE: Case 3: The segment is entirely contained within the sphere (t1 < 0 and t2 > 1).
		 * In this case, there is indeed an intersection (the entire volume of the segment is within the sphere).
		 * We can consider the starting point as a valid intersection point. */
		if ( t1 < 0 && t2 > 1 )
		{
		    intersection = segmentStart;

		    return true;
		}

		/* NOTE: No intersection point was found on the segment. */
		return false;
	}
}