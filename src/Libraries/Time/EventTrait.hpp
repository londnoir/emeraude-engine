/*
 * src/Libraries/Time/EventTrait.hpp
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

/* Project configuration. */
#include "platform.hpp"

/* STL inclusions. */
#include <functional>
#include <iostream>
#include <ratio>
#include <tuple>
#include <utility>
#include <map>
#include <ranges>
#include <cstdint>

/* Local Inclusions. */
#include "Types.hpp"
#include "TimedEvent.hpp"

namespace Libraries::Time
{
	/**
	 * @brief Adds the ability to fire timed events to a class.
	 * @tparam rep_t The time thick precision. Default unsigned int.
	 * @tparam period_t The unity of time. Default microseconds.
	 */
	template< typename rep_t = uint32_t, typename period_t = std::milli >
	requires (std::is_arithmetic_v< rep_t >)
	class EventTrait
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			EventTrait (const EventTrait & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			EventTrait (EventTrait && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return EventTrait &
			 */
			EventTrait & operator= (const EventTrait & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return EventTrait &
			 */
			EventTrait & operator= (EventTrait && copy) noexcept = default;

			/**
			 * @brief Destructs the timed events interface.
			 */
			virtual ~EventTrait () = default;

			/**
			 * @brief Starts a timer. This will register a cyclic (or a unique) call to timeEvent() with an ID given by this function.
			 * @note If the function return true, the event will be stopped.
			 * @param callable The function triggered after the timeout.
			 * @param granularity This is the interval, or the timeout respecting period_t (Time unit).
			 * @param once If set to true, your timer will fire only once and will be killed automatically.
			 * @param autostart If set to true, the timer will execute automatically.
			 * @return TimerID
			 */
			TimerID
			createTimer (const std::function< bool (TimerID) > & callable, rep_t granularity, bool once = false, bool autostart = false) noexcept
			{
				const auto timerID = m_lastTimerID++;

				const auto result = m_events.emplace(
					std::piecewise_construct,
					std::forward_as_tuple(timerID),
					std::forward_as_tuple(callable, granularity, once)
				);

				if ( !result.second )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", unable to create a timer !" "\n";

					return 0;
				}

				auto & timer = result.first->second;
				timer.setTimerID(timerID);

				if ( autostart )
				{
					timer.start();
				}

				return timerID;
			}

			/**
			 * @brief Executes a single event using EventTrait::createTimer().
			 * @param callable The function triggered after the timeout.
			 * @param timeout The delay before firing the event respecting the period_t (Time unit).
			 * @return TimerID
			 */
			TimerID
			fire (const std::function< bool (TimerID) > & callable, rep_t timeout) noexcept
			{
				return this->createTimer(callable, timeout, true, true);
			}

			/**
			 * @brief Sets a new granularity to the timer.
			 * @param timerID The ID of your timer.
			 * @param granularity The interval duration respecting period_t (Time unit).
			 * @return bool
			 */
			bool
			setTimerGranularity (TimerID timerID, rep_t granularity) noexcept
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

			/**
			 * @brief Starts an existing timer.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			bool
			startTimer (TimerID timerID) noexcept
			{
				auto * timer = this->getTimer(timerID);

				if ( timer == nullptr )
				{
					return false;
				}

				timer->start();

				return true;
			}

			/**
			 * @brief Pauses a timer without destroy it.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			bool
			stopTimer (TimerID timerID) noexcept
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

			/**
			 * @brief Returns whether the timer is started.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			bool
			isTimerStarted (TimerID timerID) noexcept
			{
				const auto * timer = this->getTimer(timerID);

				if ( timer == nullptr )
				{
					return false;
				}

				return timer->isStarted();
			}

			/**
			 * @brief Pauses a timer without destroy it.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			bool
			pauseTimer (TimerID timerID) noexcept
			{
				auto * timer = this->getTimer(timerID);

				if ( timer == nullptr )
				{
					return false;
				}

				timer->pause();

				return true;
			}

			/**
			 * @brief Starts an existing timer.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			bool
			resumeTimer (TimerID timerID) noexcept
			{
				auto * timer = this->getTimer(timerID);

				if ( timer == nullptr )
				{
					return false;
				}

				timer->resume();

				return true;
			}

			/**
			 * @brief Restarts all previously active timers.
			 * @return void
			 */
			void
			startTimers () noexcept
			{
				for ( auto & event : std::ranges::views::values(m_events) )
				{
					event.start();
				}
			}

			/**
			 * @brief Pauses every active timers.
			 * @return void
			 */
			void
			stopTimers () noexcept
			{
				for ( auto & event : std::ranges::views::values(m_events) )
				{
					event.stop();
				}
			}

			/**
			 * @brief Pauses every active timers.
			 * @return void
			 */
			void
			pauseTimers () noexcept
			{
				for ( auto & event : std::ranges::views::values(m_events) )
				{
					event.pause();
				}
			}

			/**
			 * @brief Restarts all previously active timers.
			 * @return void
			 */
			void
			resumeTimers () noexcept
			{
				for ( auto & event : std::ranges::views::values(m_events) )
				{
					event.resume();
				}
			}

			/**
			 * @brief Returns whether the timer is paused.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			bool
			isTimerPaused (TimerID timerID) noexcept
			{
				const auto * timer = this->getTimer(timerID);

				if ( timer == nullptr )
				{
					return false;
				}

				return timer->isPaused();
			}

			/**
			 * @brief This function is used to kill a cyclic timer, or a timeout before it fire.
			 * @param timerID The ID of your timer.
			 * @return void
			 */
			void
			destroyTimer (TimerID timerID) noexcept
			{
				m_events.erase(timerID);
			}

			/**
			 * @brief This function kill every timer.
			 * @return void
			 */
			void
			destroyTimers () noexcept
			{
				m_events.clear();
			}

		protected:

			/**
			 * @brief Constructs a timed events interface.
			 */
			EventTrait () noexcept = default;

			/**
			 * @brief Returns a timer.
			 * @param timerID The timer ID.
			 * @return TimedEvent< rep_t, period_t > *
			 */
			TimedEvent< rep_t, period_t > *
			getTimer (TimerID timerID) noexcept
			{
				const auto timerIt = m_events.find(timerID);

				if ( timerIt == m_events.cend() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", unable to find timer #" << timerID << " !" "\n";

					return nullptr;
				}

				return &timerIt->second;
			}

			void
			resetTimer (TimerID timerID) noexcept
			{
				const auto timerIt = m_events.find(timerID);

				if ( timerIt != m_events.cend() )
				{
					timerIt->second.resetTop();
				}
			}

		private:

			TimerID m_lastTimerID{1};
			std::map< TimerID, TimedEvent< rep_t, period_t > > m_events{};
	};
}
