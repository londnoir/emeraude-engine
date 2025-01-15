/*
 * src/Libraries/Math/Segment.hpp
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
#include <iostream>
#include <sstream>
#include <string>

/* Local inclusions. */
#include "Vector.hpp"

namespace Libraries::Math
{
	/**
	 * @brief Defining a 2D segment.
	 * @tparam data_t The data precision.
	 */
	template< typename data_t = float >
	requires (std::is_arithmetic_v< data_t >)
	class Segment final
	{
		public:

			/**
			 * @brief Constructs a segment.
			 */
			Segment () noexcept = default;

			/**
			 * @brief Constructs a segment.
			 * @param end A reference to a vector.
			 */
			explicit
			Segment (const Vector< 2, data_t > & end) noexcept
				: m_start(end)
			{

			}

			/**
			 * @brief Constructs a segment.
			 * @param start A reference to a vector.
			 * @param end A reference to a vector.
			 */
			Segment (const Vector< 2, data_t > & start, const Vector< 2, data_t > & end) noexcept
				: m_start(start), m_end(end)
			{

			}

			/**
			 * @brief Sets the starting point of the segment.
			 * @param vector A reference to a vector.
			 */
			void
			setStart (const Vector< 2, data_t > & vector) noexcept
			{
				m_start = vector;
			}

			/**
			 * @brief Sets the ending point of the segment.
			 * @param vector A reference to a vector.
			 */
			void
			setEnd (const Vector< 2, data_t > & vector) noexcept
			{
				m_end = vector;
			}

			/**
			 * @brief Returns the starting point of the segment.
			 * @return const Vector< 2, data_t > &
			 */
			[[nodiscard]]
			const Vector< 2, data_t > &
			start () const noexcept
			{
				return m_start;
			}

			/**
			 * @brief Returns the starting point X value of the segment.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			startX () const noexcept
			{
				return m_start[X];
			}

			/**
			 * @brief Returns the starting point Y value of the segment.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			startY () const noexcept
			{
				return m_start[Y];
			}

			/**
			 * @brief Returns the ending point of the segment.
			 * @return const Vector< 2, data_t > &
			 */
			[[nodiscard]]
			const Vector< 2, data_t > &
			end () const noexcept
			{
				return m_end;
			}

			/**
			 * @brief Returns the ending point X value of the segment.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			endX () const noexcept
			{
				return m_end[X];
			}

			/**
			 * @brief Returns the ending point Y value of the segment.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			endY () const noexcept
			{
				return m_end[Y];
			}

			/**
			 * @brief Returns whether the segment is valid.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				return m_start != m_end;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Segment & obj) noexcept
			{
				return out << "Segment data :\n"
					"Start : " << obj.m_start << "\n"
					"End : " << obj.m_end << '\n';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Segment & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

			[[nodiscard]]
			static
			bool
			intersect (const Segment & segmentA, const Segment & segmentB)
			{
				const auto d1x = segmentA.endX() - segmentA.startX(); // ad.x
				const auto d1y = segmentA.endY() - segmentA.startY(); // ad.y
				const auto d2x = segmentB.endX() - segmentB.startX(); // bd.x
				const auto d2y = segmentB.endY() - segmentB.startY(); // bd.y
				const auto det = d2y * d1x - d2x * d1y;

				/* NOTE: Lines are parallel or collinear */
				if ( det < 0.0001 && det > -0.0001 )
				{
					return false;
				}

				auto a = segmentA.startY() - segmentB.startY(); // origin dy
				auto b = segmentA.startX() - segmentB.startX(); // origin dx
				const auto n1 = d2x * a - d2y * b;
				const auto n2 = d1x * a - d1y * b;

				/* NOTE: roughly distance from l1 origin to l2 intersection. */
				a = n1 / det;
				/* NOTE: roughly distance from l2 origin to l1 intersection. */
				b = n2 / det;

				const bool ia = a >= -0.0001 && a <= 1.0001;
				const bool ib = b >= -0.0001 && b <= 1.0001;

				return ia && ib;
			}

		private:

			Vector< 2, data_t > m_start{};
			Vector< 2, data_t > m_end{};
	};
}
