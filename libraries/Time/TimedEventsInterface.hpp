/*
 * Libraries/Time/TimedEventsInterface.hpp
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

/* C/C++ standards libraries */
#include <cstdint>
#include <map>

/* Local Inclusion */
#include "TimedEvent.hpp"

namespace Libraries::Time
{
	using TimerID = unsigned long;

	/**
	 * @brief Interface that adds timed events to a class.
	 */
	class TimedEventsInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			TimedEventsInterface (const TimedEventsInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			TimedEventsInterface (TimedEventsInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return TimedEventsInterface &
			 */
			TimedEventsInterface & operator= (const TimedEventsInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return TimedEventsInterface &
			 */
			TimedEventsInterface & operator= (TimedEventsInterface && copy) noexcept = default;

			/**
			 * @brief Destructs the timed events interface.
			 */
			virtual ~TimedEventsInterface () = default;

			/**
			 * @brief Starts a timer. This will register a cyclic (or a unique) call to timeEvent() with an ID given by this function.
			 * @param callable The function triggered after the timeout.
			 * @param granularity This is the interval, or the timeout in milliseconds. 1000.0 = 1 second.
			 * @param once If set to true, you timer will fire only once and will be killed automatically.
			 * @param autostart If set to true, the timer will execute automatically.
			 * @param precise If set to true, when checking if the time is elapsed, the next time point will be corrected to reduce imprecision over time.
			 * @return TimerID
			 */
			virtual TimerID createTimer (const Time::Function & callable, double granularity, bool once = false, bool autostart = false, bool precise = false) noexcept final;

			/**
			 * @brief Executes a single event using TimedEventsInterface::createTimer().
			 * @param callable The function triggered after the timeout.
			 * @param timeout The delay before firing the event.
			 * @param precise If set to true, when checking if the time is elapsed, the next time point will be corrected to reduce imprecision over time.
			 * @return TimerID
			 */
			inline
			virtual
			TimerID
			fire (const Time::Function & callable, double timeout, bool precise = false) noexcept final
			{
				return this->createTimer(callable, timeout, true, true, precise);
			}

			/**
			 * @brief Sets a new granularity to the timer.
			 * @param timerID The ID of your timer.
			 * @param granularity Time in milliseconds.
			 * @return bool
			 */
			virtual bool setTimerGranularity (TimerID timerID, double granularity) noexcept final;

			/**
			 * @brief Sets a new granularity to the timer.
			 * @param timerID The ID of your timer.
			 * @param granularity Time in milliseconds.
			 * @return bool
			 */
			virtual bool addTimerGranularity (TimerID timerID, double granularity) noexcept final;

			/**
			 * @brief Starts an existing timer.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			virtual bool startTimer (TimerID timerID) noexcept final;

			/**
			 * @brief Pauses a timer without destroy it.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			virtual bool stopTimer (TimerID timerID) noexcept final;

			/**
			 * @brief Restarts all previously active timers.
			 * @return void
			 */
			virtual void startTimers () noexcept final;

			/**
			 * @brief Pauses every active timers.
			 * @return void
			 */
			virtual void stopTimers () noexcept final;

			/**
			 * @brief Returns whether the timer is started.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			virtual bool isTimerStarted (TimerID timerID) noexcept final;

			/**
			 * @brief Pauses a timer without destroy it.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			virtual bool pauseTimer (TimerID timerID) noexcept final;

			/**
			 * @brief Starts an existing timer.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			virtual bool resumeTimer (TimerID timerID) noexcept final;

			/**
			 * @brief Pauses every active timers.
			 * @return void
			 */
			virtual void pauseTimers () noexcept final;

			/**
			 * @brief Restarts all previously active timers.
			 * @return void
			 */
			virtual void resumeTimers () noexcept final;

			/**
			 * @brief Returns whether the timer is paused.
			 * @param timerID The ID of your timer.
			 * @return bool
			 */
			virtual bool isTimerPaused (TimerID timerID) noexcept final;

			/**
			 * @brief This function is used to kill a cyclic timer, or a timeout before it fire.
			 * @param timerID The ID of your timer.
			 * @return void
			 */
			virtual void destroyTimer (TimerID timerID) noexcept final;

			/**
			 * @brief This function kill every timer.
			 * @return void
			 */
			virtual void destroyTimers () noexcept final;

		protected:

			/**
			 * @brief Constructs a timed events interface.
			 */
			TimedEventsInterface () noexcept = default;

			/**
			 * @brief Returns a timer.
			 * @param timerID The timer ID.
			 * @return TimedEvent *
			 */
			virtual TimedEvent * getTimer (TimerID timerID) noexcept final;

		private:

			TimerID m_lastTimerID{1};
			std::map< TimerID, TimedEvent > m_events{};
	};
}
