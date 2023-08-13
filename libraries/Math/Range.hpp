/*
 * Libraries/Math/Range.hpp
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
#include "Utility.hpp"

namespace Libraries::Math
{
	/**
	 * @brief The range class.
	 * @tparam data_t The data precision.
	 */
	template< typename data_t = float, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
	class Range
	{
		public:

			/**
			 * @brief Constructs a range.
			 */
			Range () noexcept = default;

			/**
			 * @brief Constructs a range.
			 * @param minimum A value for the maximum.
			 * @param maximum A value for the minimum.
			 */
			Range (data_t minimum, data_t maximum) noexcept
				: m_minimum(std::min(minimum, maximum)), m_maximum(std::max(minimum, maximum))
			{

			}

			/**
			 * @brief Returns whether the range is valid.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				return Utility::different(m_maximum, m_minimum);
			}

			/**
			 * @brief Returns the minimum value of the range.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			minimum () const noexcept
			{
				return m_minimum;
			}

			/**
			 * @brief Returns the maximum value of the range.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			maximum () const noexcept
			{
				return m_maximum;
			}

			/**
			 * @brief Updates the range with a new value.
			 * @param value A value to add to the range.
			 * @return void
			 */
			void
			update (data_t value) noexcept
			{
				if ( value < m_minimum )
				{
					m_minimum = value;
				}

				if ( value > m_maximum )
				{
					m_maximum = value;
				}
			}

			/**
			 * @brief Checks the overlap with an other range.
			 * @param otherRange A reference to a range.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			overlaps (const Range & otherRange) const noexcept
			{
				return !( m_minimum > otherRange.m_maximum || otherRange.m_minimum > m_maximum );
			}

			/**
			 * @brief Returns the overlapping distance with an other range.
			 * @param otherRange A reference to a range.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			getOverlap (const Range & otherRange) const noexcept
			{
				if ( !this->overlaps(otherRange) )
				{
					return 0;
				}

				if ( m_maximum > otherRange.m_minimum )
				{
					return m_maximum - otherRange.m_minimum;
				}

				return otherRange.m_maximum - m_minimum;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Range & obj) noexcept
			{
				return out << "Range(" << obj.m_minimum << " -> " << obj.m_maximum << ')';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend
			std::string
			to_string (const Range & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			data_t m_minimum{std::numeric_limits< data_t >::max()};
			data_t m_maximum{std::numeric_limits< data_t >::lowest()};
	};
}
