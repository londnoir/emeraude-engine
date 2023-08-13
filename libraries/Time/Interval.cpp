/*
 * Libraries/Time/Interval.cpp
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

#include "Interval.hpp"

namespace Libraries::Time
{
	Interval::Interval (double granularity, bool precise) noexcept
		: m_granularity(granularity), m_previousTime(std::chrono::steady_clock::now())
	{
		m_flags[Precise] = precise;
	}

	void
	Interval::setGranularity (double granularity) noexcept
	{
		/* example for 60 Hertz = 1.0 / 60 */
		m_granularity = granularity;

		m_previousTime = std::chrono::steady_clock::now();
	}

	double
	Interval::granularity () const noexcept
	{
		return m_granularity;
	}

	// NOLINTBEGIN(*-magic-numbers)
	double
	Interval::elapsed () noexcept
	{
		using namespace std::chrono;

		auto top = steady_clock::now();

		if ( m_flags[Precise] )
		{
			/* Microseconds to milliseconds. */
			auto delta = static_cast< double >(duration_cast< microseconds >(top - m_previousTime).count()) / 1000.0;

			if ( delta >= m_granularity )
			{
				/* NOTE: Milliseconds. */
				auto overlap = delta - m_granularity;

				m_previousTime = top - microseconds(static_cast< long >(overlap / 1000));

				return delta;
			}
		}
		else
		{
			auto delta = static_cast< double >(duration_cast< milliseconds >(top - m_previousTime).count());

			if ( delta >= m_granularity )
			{
				m_previousTime = top;

				return delta;
			}
		}

		return 0.0;
	}
	// NOLINTEND(*-magic-numbers)

	void
	Interval::skipTime () noexcept
	{

	}

	void
	Interval::resetTop() noexcept
	{
		m_previousTime = std::chrono::steady_clock::now();
	}
}
