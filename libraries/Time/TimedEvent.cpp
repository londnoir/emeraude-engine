/*
 * Libraries/Time/TimedEvent.cpp
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

#include "TimedEvent.hpp"

/* C/C++ standard libraries. */
#include <utility>

namespace Libraries::Time
{
	TimedEvent::TimedEvent (Function function, double granularity, bool once, bool precise) noexcept
		: Interval(granularity, precise), m_function(std::move(function))
	{
		m_flags[OnlyOnce] = once;
	}

	TimedEvent::~TimedEvent ()
	{
		/* This causes the while() loop to stop in the thread. */
		m_flags[IsProcessCreated] = false;
		m_flags[IsProcessActive] = false;
		m_flags[IsProcessPaused] = false;

		/* If thread is launched, wait for the end. */
		if ( m_thread.joinable() )
		{
			m_thread.join();
		}
	}

	void
	TimedEvent::start () noexcept
	{
		/* If the process is already active, we do nothing. */
		if ( m_flags[IsProcessActive] )
		{
			return;
		}

		m_flags[IsProcessActive] = true;

		this->resetTop();

		/* Creates the process thread only once. */
		if ( m_flags[IsProcessCreated] )
		{
			return;
		}

		m_flags[IsProcessCreated] = true;

		/* This will be called only for the first execute(). */
		m_thread = std::thread(&TimedEvent::process, this);
	}

	void
	TimedEvent::stop () noexcept
	{
		m_flags[IsProcessActive] = false;
	}

	void
	TimedEvent::pause () noexcept
	{
		if ( !m_flags[IsProcessCreated] || !m_flags[IsProcessActive] )
		{
			return;
		}

		m_flags[IsProcessActive] = false;
		m_flags[IsProcessPaused] = true;
	}

	void
	TimedEvent::resume () noexcept
	{
		if ( !m_flags[IsProcessPaused] )
		{
			return;
		}

		m_flags[IsProcessActive] = true;
		m_flags[IsProcessPaused] = false;
	}

	void
	TimedEvent::process (TimedEvent * event) noexcept
	{
		while ( event->m_flags[IsProcessCreated] )
		{
#ifdef POWER_SAVING_ENABLED
			auto execute = std::chrono::steady_clock::now();
#endif

			if ( event->m_flags[IsProcessActive] )
			{
				auto elapsedTime = event->elapsed();

				/* If the delay is elapsed we fire the event. */
				if ( elapsedTime > 0.0 )
				{
					event->m_function(elapsedTime);

					/* If the event was unique, we stop the process. */
					if ( event->once() )
					{
						event->stop();
					}
				}
			}
			else if ( event->m_flags[IsProcessPaused] )
			{
				event->skipTime();
			}

#ifdef POWER_SAVING_ENABLED
			/* Ideal waiting time for this event. */
			auto waitingTime = static_cast< int64_t >(std::floor(event->granularity() * 0.9));

			/* The time spent in this loop. */
			auto elapsedTime = std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::steady_clock::now() - execute).count();

			/* We let sleep the process during the smallest
			 * event granularity minus loop elapsed time. */
			if ( elapsedTime < waitingTime )
			{
				auto remainingTime = waitingTime - elapsedTime;

				std::this_thread::sleep_for(std::chrono::milliseconds(remainingTime));
			}
#endif
		}
	}

	bool
	TimedEvent::isStarted () const noexcept
	{
		return m_flags[IsProcessActive];
	}

	bool
	TimedEvent::isPaused () const noexcept
	{
		return m_flags[IsProcessPaused];
	}

	bool
	TimedEvent::once () const noexcept
	{
		return m_flags[OnlyOnce];
	}
}
