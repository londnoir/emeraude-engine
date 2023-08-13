/*
 * Libraries/Time/AbstractStatistics.cpp
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

#include "AbstractStatistics.hpp"

/* C/C++ standard libraries. */
#include <iostream>
#include <numeric>

namespace Libraries::Time
{
	AbstractStatistics::AbstractStatistics (size_t range) noexcept
		: m_range(std::max< size_t >(range, 1)), m_durations(m_range, 0.0), m_executionsPerSeconds(m_range, 0UL)
	{

	}

	void
	AbstractStatistics::incrementIndex (size_t & index) const noexcept
	{
		index++;

		if ( index >= m_range )
		{
			index = 0;
		}
	}

	size_t
	AbstractStatistics::getPreviousIndex (size_t index) const noexcept
	{
		if ( index == 0 )
		{
			return m_range - 1;
		}

		return index - 1;
	}

	void
	AbstractStatistics::insertDuration (unsigned long int duration) noexcept
	{
		m_durations[m_durationIndex] = duration;

		this->incrementIndex(m_durationIndex);

		/* NOTE: this method is called every stop(); */
		m_topCount++;
	}

	void
	AbstractStatistics::insertEPS (unsigned int count) noexcept
	{
		m_executionsPerSeconds[m_EPSIndex] = count;

		this->incrementIndex(m_EPSIndex);
	}

	unsigned long int
	AbstractStatistics::duration () const noexcept
	{
		return m_durations[this->getPreviousIndex(m_durationIndex)];
	}

	double
	AbstractStatistics::averageDuration () const noexcept
	{
		return std::accumulate(m_durations.cbegin(), m_durations.cend(), 0.0) / static_cast< double >(m_range);
	}

	unsigned int
	AbstractStatistics::executionsPerSecond () const noexcept
	{
		return m_executionsPerSeconds[this->getPreviousIndex(m_EPSIndex)];
	}

	double
	AbstractStatistics::averageExecutionsPerSecond () const noexcept
	{
		return std::accumulate(m_executionsPerSeconds.cbegin(), m_executionsPerSeconds.cend(), 0.0) / static_cast< double >(m_range);
	}

	size_t
	AbstractStatistics::range () const noexcept
	{
		return m_range;
	}

	size_t
	AbstractStatistics::topCount () const noexcept
	{
		return m_topCount;
	}

	void
	AbstractStatistics::print () const noexcept
	{
		if ( m_range > 1 )
		{
			const auto * warning = ( m_topCount < m_range ? " [IRRELEVANT]" : " " );

			std::cout <<
				"Time statistics (Top count: " << m_topCount << ", range: " << m_range << ")" "\n" <<
				"Duration : " << this->duration() << " ms" "\n" <<
				"Average duration : " << this->averageDuration() << " ms" << warning << '\n' <<
				"Executions per second : " << this->executionsPerSecond() << " times" "\n" <<
				"Average executions per second : " << this->averageExecutionsPerSecond() << " times" << warning << "\n\n";
		}
		else
		{
			std::cout <<
				"Time statistics" "\n" <<
				"Duration : " << this->averageDuration() << " ms" "\n\n";
		}
	}
}
