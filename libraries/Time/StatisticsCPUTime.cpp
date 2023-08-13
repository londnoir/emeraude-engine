/*
 * Libraries/Time/StatisticsCPUTime.cpp
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

#include "StatisticsCPUTime.hpp"

namespace Libraries::Time
{
	StatisticsCPUTime::StatisticsCPUTime (size_t range) noexcept
		: AbstractStatistics(range)
	{

	}

	void
	StatisticsCPUTime::start () noexcept
	{
		m_startTime = std::clock();
	}

	// NOLINTBEGIN(*-magic-numbers)
	void
	StatisticsCPUTime::stop () noexcept
	{
		/* Increment executions count. */
		m_currentExecutionsPerSecond++;

		/* Gets the duration. */
		auto duration = std::clock() - m_startTime;

		/* Insert duration for average statistics. */
		if constexpr ( CLOCKS_PER_SEC == 1000 )
		{
			/* Duration is expressed in milliseconds. */
			this->insertDuration(duration);
		}

		if constexpr ( CLOCKS_PER_SEC == 1000000 )
		{
			/* Duration is expressed in microseconds. */
			this->insertDuration(duration / 1000);
		}

		if constexpr ( CLOCKS_PER_SEC == 1000000000 )
		{
			/* Duration is expressed in nanoseconds. */
			this->insertDuration(duration / 1000000);
		}

		/* Keep track of time elapsed. */
		m_delta += duration;

		/* Checks if a second passed. */
		if ( m_delta >= CLOCKS_PER_SEC )
		{
			/* Insert EPS for average statistics. */
			this->insertEPS(m_currentExecutionsPerSecond);

			/* Reset statistics variables. */
			m_delta -= CLOCKS_PER_SEC;
			m_currentExecutionsPerSecond = 0;
		}
	}
	// NOLINTEND(*-magic-numbers)
}
