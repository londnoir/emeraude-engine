/*
 * src/Libs/Math/Segment.hpp
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
#include <sstream>
#include <string>

/* Local inclusions. */
#include "Vector.hpp"

namespace EmEn::Libs::Math
{
	/**
	 * @brief Class for a segment.
	 * @tparam dimension_t Specify is the segment is 2D or 3D.
	 * @tparam precision_t The data precision. Default float.
	 */
	template< size_t dimension_t, typename precision_t = float >
	requires (dimension_t == 2 || dimension_t == 3) && std::is_floating_point_v< precision_t >
	class Segment final
	{
		public:

			/**
			 * @brief Constructs a segment.
			 */
			Segment () noexcept = default;

			/**
			 * @brief Constructs a segment from origin to a point.
			 * @param end A reference to a vector.
			 */
			explicit
			Segment (const Vector< dimension_t, precision_t > & end) noexcept
				: m_end(end)
			{

			}

			/**
			 * @brief Constructs a segment from two points.
			 * @param start A reference to a vector.
			 * @param end A reference to a vector.
			 */
			Segment (const Vector< dimension_t, precision_t > & start, const Vector< dimension_t, precision_t > & end) noexcept
				: m_start(start), m_end(end)
			{

			}

			/**
			 * @brief Sets the starting point of the segment.
			 * @param vector A reference to a vector.
			 * @return void
			 */
			void
			setStart (const Vector< dimension_t, precision_t > & vector) noexcept
			{
				m_start = vector;
			}

			/**
			 * @brief Sets the ending point of the segment.
			 * @param vector A reference to a vector.
			 * @return void
			 */
			void
			setEnd (const Vector< dimension_t, precision_t > & vector) noexcept
			{
				m_end = vector;
			}

			/**
			 * @brief Returns the starting point of the segment.
			 * @return const Vector< dimension_t, precision_t > &
			 */
			[[nodiscard]]
			const Vector< dimension_t, precision_t > &
			start () const noexcept
			{
				return m_start;
			}

			/**
			 * @brief Returns the starting point X value of the segment.
			 * @return precision_t
			 */
			[[nodiscard]]
			precision_t
			startX () const noexcept
			{
				return m_start[X];
			}

			/**
			 * @brief Returns the starting point Y value of the segment.
			 * @return precision_t
			 */
			[[nodiscard]]
			precision_t
			startY () const noexcept
			{
				return m_start[Y];
			}

			/**
			 * @brief Returns the starting point Z value of the segment.
			 * @return precision_t
			 */
			[[nodiscard]]
			precision_t
			startZ () const noexcept requires (dimension_t == 3)
			{
				return m_start[Z];
			}

			/**
			 * @brief Returns the ending point of the segment.
			 * @return const Vector< dimension_t, precision_t > &
			 */
			[[nodiscard]]
			const Vector< dimension_t, precision_t > &
			end () const noexcept
			{
				return m_end;
			}

			/**
			 * @brief Returns the ending point X value of the segment.
			 * @return precision_t
			 */
			[[nodiscard]]
			precision_t
			endX () const noexcept
			{
				return m_end[X];
			}

			/**
			 * @brief Returns the ending point Y value of the segment.
			 * @return precision_t
			 */
			[[nodiscard]]
			precision_t
			endY () const noexcept
			{
				return m_end[Y];
			}

			/**
			 * @brief Returns the ending point Z value of the segment.
			 * @return precision_t
			 */
			[[nodiscard]]
			precision_t
			endZ () const noexcept requires (dimension_t == 3)
			{
				return m_end[Z];
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

		private:

			Vector< dimension_t, precision_t > m_start;
			Vector< dimension_t, precision_t > m_end;
	};
}
