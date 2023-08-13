/*
 * Libraries/Math/Segment.hpp
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
#include <iostream>
#include <sstream>
#include <string>

/* Local inclusions */
#include "Vector.hpp"

namespace Libraries::Math
{
	/**
	 * @brief Defining a segment.
	 * @tparam data_t The data precision.
	 */
	template< typename data_t = float, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
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
			 * @return ostream &
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
			 * @return string
			 */
			friend
			std::string
			to_string (const Segment & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			Vector< 2, data_t > m_start{};
			Vector< 2, data_t > m_end{};
	};
}
