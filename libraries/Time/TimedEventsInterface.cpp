/*
 * Libraries/Time/TimedEventsInterface.cpp
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

#include "TimedEventsInterface.hpp"

/* C/C++ standard libraries. */
#include <cmath>
#include <iostream> // Debug

namespace Libraries::Time
{
	TimerID
	TimedEventsInterface::createTimer (const Time::Function & callable, double granularity, bool once, bool autostart, bool precise) noexcept
	{
		const auto timerID = m_lastTimerID++;

		auto result = m_events.emplace(std::piecewise_construct, std::forward_as_tuple(timerID), std::forward_as_tuple(callable, granularity, once, precise));

		if ( !result.second )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to create a timer !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return 0;
		}

		if ( autostart )
		{
			result.first->second.start();
		}

		return timerID;
	}

	bool
	TimedEventsInterface::setTimerGranularity (TimerID timerID, double granularity) noexcept
	{
		/* Gets the right timer. */
		auto * timer = this->getTimer(timerID);

		if ( timer == nullptr )
		{
			return false;
		}

		timer->setGranularity(granularity);

		return true;
	}

	bool
	TimedEventsInterface::addTimerGranularity (TimerID timerID, double granularity) noexcept
	{
		/* Gets the right timer. */
		auto * timer = this->getTimer(timerID);

		if ( timer == nullptr )
		{
			return false;
		}

		timer->setGranularity(timer->granularity() + granularity);

		return true;
	}

	bool
	TimedEventsInterface::startTimer (TimerID timerID) noexcept
	{
		auto * timer = this->getTimer(timerID);

		if ( timer == nullptr )
		{
			return false;
		}

		timer->start();

		return true;
	}

	bool
	TimedEventsInterface::stopTimer (TimerID timerID) noexcept
	{
		/* Gets the right timer. */
		auto * timer = this->getTimer(timerID);

		if ( timer == nullptr )
		{
			return false;
		}

		timer->stop();

		return true;
	}

	void
	TimedEventsInterface::startTimers () noexcept
	{
		for ( auto & event : m_events )
		{
			event.second.start();
		}
	}

	void
	TimedEventsInterface::stopTimers () noexcept
	{
		for ( auto & event : m_events )
		{
			event.second.stop();
		}
	}

	bool
	TimedEventsInterface::isTimerStarted (TimerID timerID) noexcept
	{
		auto * timer = this->getTimer(timerID);

		if ( timer == nullptr )
		{
			return false;
		}

		return timer->isStarted();
	}

	bool
	TimedEventsInterface::pauseTimer (TimerID timerID) noexcept
	{
		auto * timer = this->getTimer(timerID);

		if ( timer == nullptr )
		{
			return false;
		}

		timer->pause();

		return true;
	}

	bool
	TimedEventsInterface::resumeTimer (TimerID timerID) noexcept
	{
		auto * timer = this->getTimer(timerID);

		if ( timer == nullptr )
		{
			return false;
		}

		timer->resume();

		return true;
	}

	void
	TimedEventsInterface::pauseTimers () noexcept
	{
		for ( auto & event : m_events )
		{
			event.second.pause();
		}
	}

	void
	TimedEventsInterface::resumeTimers () noexcept
	{
		for ( auto & event : m_events )
		{
			event.second.resume();
		}
	}

	bool
	TimedEventsInterface::isTimerPaused (TimerID timerID) noexcept
	{
		auto * timer = this->getTimer(timerID);

		if ( timer == nullptr )
		{
			return false;
		}

		return timer->isPaused();
	}

	void
	TimedEventsInterface::destroyTimer (TimerID timerID) noexcept
	{
		m_events.erase(timerID);
	}

	void
	TimedEventsInterface::destroyTimers () noexcept
	{
		m_events.clear();
	}

	TimedEvent *
	TimedEventsInterface::getTimer (TimerID timerID) noexcept
	{
		auto timerIt = m_events.find(timerID);

		if ( timerIt == m_events.end() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to find timer #" << timerID << " !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return nullptr;
		}

		return &timerIt->second;
	}
}
