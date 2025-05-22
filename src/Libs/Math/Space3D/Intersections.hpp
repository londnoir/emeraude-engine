/*
* src/Libs/Math/Space3D/Intersections.hpp
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
#include "Sphere.hpp"
//#include "Cuboid.hpp"

namespace EmEn::Libs::Math::Space3D
{
	/**
	 * @brief Checks if a segment intersects a triangle using the "Möller-Trumbore" algorithm.
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
	isIntersecting (const Point< precision_t > & segmentStart, const Point< precision_t > & segmentEnd, const Point< precision_t > & trianglePointA, const Point< precision_t > & trianglePointB, const Point< precision_t > & trianglePointC, Point< precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		/* 1. Define the vectors for the segment and edges of the triangle. */
		const Point< precision_t > segmentDirection = segmentEnd - segmentStart;
		const Point< precision_t > edge1 = trianglePointB - trianglePointA;
		const Point< precision_t > edge2 = trianglePointC - trianglePointA;

		/* 2. Calculate the determinant. If close to zero, the segment is parallel to the plane of the triangle. */
		const Point< precision_t > h = Point< precision_t >::crossProduct(segmentDirection, edge2);
		const auto det = Point< precision_t >::dotProduct(edge1, h);

		if ( det > -std::numeric_limits< precision_t >::epsilon() && det < std::numeric_limits< precision_t >::epsilon() )
		{
			/* NOTE: Segment parallel to the triangle. */
			return false;
		}

		const auto invDet = static_cast< precision_t >(1) / det;

		/* 3. Calculate the barycentric coordinate 'u' */
		const Point< precision_t > s = segmentStart - trianglePointA;
		const precision_t u = invDet * Point< precision_t >::dotProduct(s, h);

		if ( u < static_cast< precision_t >(0) || u > static_cast< precision_t >(1) )
		{
			/* NOTE: The point of intersection is outside the triangle. */
			return false;
		}

		/* 4. Calculate the barycentric coordinate 'v' */
		const Point< precision_t > q = Point< precision_t >::crossProduct(s, edge1);
		const precision_t v = invDet * Point< precision_t >::dotProduct(segmentDirection, q);

		if ( v < static_cast< precision_t >(0) || u + v > static_cast< precision_t >(1) )
		{
			/* NOTE: The point of intersection is outside the triangle. */
			return false;
		}

		/* 5. Calculate 't', the distance along the segment where the intersection occurs. */
		const precision_t t = invDet * Point< precision_t >::dotProduct(edge2, q);

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
	 * @brief Checks if a segment intersects a triangle using the "Möller-Trumbore" algorithm.
	 * @note The intersection is valid for both faces of the triangle (no backface culling).
	 * @tparam precision_t The data precision. Default float.
	 * @param segment A reference to a segment.
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
	isIntersecting (const Segment< precision_t > & segment, const Point< precision_t > & trianglePointA, const Point< precision_t > & trianglePointB, const Point< precision_t > & trianglePointC, Point< precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		return isIntersecting(
			segment.start(), segment.end(),
			trianglePointA, trianglePointB, trianglePointC,
			intersection
		);
	}

	/**
	 * @brief Checks if a segment intersects a triangle using the "Möller-Trumbore" algorithm.
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
	isIntersecting (const Segment< precision_t > & segment, const Triangle< precision_t > & triangle, Point< precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		return isIntersecting(
			segment.start(), segment.end(),
			triangle.pointA(), triangle.pointB(), triangle.pointC(),
			intersection
		);
	}

	/**
	 * @brief Checks if a segment intersects a sphere.
	 * @tparam precision_t The data precision. Default float.
	 * @param segment A reference to a segment.
	 * @param sphere A reference to a sphere.
	 * @param intersection A writable reference to a vector for the intersection if method returns true.
	 * @return bool
	 */
	template< typename precision_t = float >
	[[nodiscard]]
	static
	bool
	isIntersecting (const Segment< precision_t > & segment, const Sphere< precision_t > & sphere, Point< precision_t > & intersection) noexcept
		requires (std::is_floating_point_v< precision_t >)
	{
		const auto & segmentStart = segment.start();
		const auto & segmentEnd = segment.end();
		const auto & center = sphere.position();
		const auto radius = sphere.radius();

		const Point< precision_t > segmentDirection = segmentEnd - segmentStart;
		/* NOTE: Vector from the center of the sphere to the start of the segment. */
		const Point< precision_t > oc = segmentStart - center;

		const precision_t a = Point< precision_t >::dotProduct(segmentDirection, segmentDirection);
		const precision_t b = static_cast< precision_t >(2) * Point< precision_t >::dotProduct(segmentDirection, oc);
		const precision_t c = Point< precision_t >::dotProduct(oc, oc) - radius * radius;

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
