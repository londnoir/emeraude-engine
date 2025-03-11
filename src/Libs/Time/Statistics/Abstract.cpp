/*
 * src/Libs/Time/Statistics/Abstract.cpp
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

#include "Abstract.hpp"

/* STL inclusions. */
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <numeric>

namespace EmEn::Libs::Time::Statistics
{
	Abstract::Abstract (size_t range) noexcept
		: m_range(std::max< size_t >(range, 1)), m_durations(m_range, 0.0), m_executionsPerSeconds(m_range, 0UL)
	{

	}

	void
	Abstract::incrementIndex (size_t & index) const noexcept
	{
		index++;

		if ( index >= m_range )
		{
			index = 0;
		}
	}

	size_t
	Abstract::getPreviousIndex (size_t index) const noexcept
	{
		if ( index == 0 )
		{
			return m_range - 1;
		}

		return index - 1;
	}

	void
	Abstract::insertDuration (uint64_t duration) noexcept
	{
		m_durations[m_durationIndex] = duration;

		this->incrementIndex(m_durationIndex);

		/* NOTE: this method is called every stop(); */
		m_topCount++;
	}

	void
	Abstract::insertEPS (uint32_t count) noexcept
	{
		m_executionsPerSeconds[m_EPSIndex] = count;

		this->incrementIndex(m_EPSIndex);
	}

	uint64_t
	Abstract::duration () const noexcept
	{
		return m_durations[this->getPreviousIndex(m_durationIndex)];
	}

	double
	Abstract::averageDuration () const noexcept
	{
		return std::accumulate(m_durations.cbegin(), m_durations.cend(), 0.0) / static_cast< double >(m_range);
	}

	uint32_t
	Abstract::executionsPerSecond () const noexcept
	{
		return m_executionsPerSeconds[this->getPreviousIndex(m_EPSIndex)];
	}

	double
	Abstract::averageExecutionsPerSecond () const noexcept
	{
		return std::accumulate(m_executionsPerSeconds.cbegin(), m_executionsPerSeconds.cend(), 0.0) / static_cast< double >(m_range);
	}

	size_t
	Abstract::range () const noexcept
	{
		return m_range;
	}

	size_t
	Abstract::topCount () const noexcept
	{
		return m_topCount;
	}

	void
	Abstract::print () const noexcept
	{
		if ( m_range > 1 )
		{
			const auto * warning = m_topCount < m_range ? " [IRRELEVANT]" : " ";

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
