/*
 * src/Libs/Time/TimedEvent.hpp
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

/* STL inclusions. */
#include <array>
#include <chrono>
#include <functional>
#include <ratio>
#include <thread>
#include <type_traits>
#include <cstdint>

/* Local Inclusions. */
#include "Types.hpp"

namespace EmEn::Libs::Time
{
	/**
	 * @brief The timed event class.
	 * @tparam rep_t The time thick precision. Default unsigned int.
	 * @tparam period_t The unity of time expressed with std::ratio<>. Default std::milli.
	 */
	template< typename rep_t = uint32_t, typename period_t = std::milli >
	requires (std::is_arithmetic_v< rep_t >)
	class TimedEvent final
	{
		public:

			/**
			 * @brief Constructs a default timed event.
			 */
			TimedEvent () noexcept = default;

			/**
			 * @brief Constructs a timed event.
			 * @param function A function object to fire after each interval.
			 * @param granularity The interval duration respecting the period_t.
			 * @param once Declare to stop after one interval elapsed. Default false.
			 */
			TimedEvent (std::function< bool (TimerID) > function, rep_t granularity, bool once = false) noexcept
				: m_granularity(granularity), m_function(std::move(function))
			{
				m_flags[OnlyOnce] = once;
			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			TimedEvent (const TimedEvent & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			TimedEvent (TimedEvent && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			TimedEvent & operator= (const TimedEvent & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			TimedEvent & operator= (TimedEvent && copy) noexcept = default;

			/**
			 * @brief Destructs the timed event.
			 * @note Waits for thread to quit properly.
			 */
			~TimedEvent ()
			{
				/* NOTE: This will causes the while() loop to stop in the thread. */
				m_flags[IsProcessCreated] = false;
				m_flags[IsProcessActive] = false;
				m_flags[IsProcessPaused] = false;

				/* If thread is launched, wait for the end. */
				if ( m_thread.joinable() )
				{
					m_thread.join();
				}
			}

			/**
			 * @brief Modifies the interval duration.
			 * @param granularity The interval duration respecting the period_t template argument.
			 * @return void
			 */
			void
			setGranularity (rep_t granularity) noexcept
			{
				m_granularity = std::chrono::duration< rep_t, period_t >{granularity};
				m_previousTime = std::chrono::steady_clock::now();
			}

			/**
			 * @brief Returns the interval duration respecting the period_t (time unit) template argument.
			 * @return rep_t
			 */
			[[nodiscard]]
			rep_t
			granularity () const noexcept
			{
				return m_granularity.count();
			}

			/**
			 * @brief Sets the timer ID to identify on callback.
			 * @param timerID A unsigned integer.
			 * @return void
			 */
			void
			setTimerID (TimerID timerID) noexcept
			{
				m_timerId = timerID;
			}

			/**
			 * @brief Returns the timer ID associated.
			 * @note This can be zero.
			 * @return TimerID
			 */
			[[nodiscard]]
			TimerID
			timerID () const noexcept
			{
				return m_timerId;
			}

			/**
			 * @brief Returns the elapsed time respecting the period_t (time unit) template argument.
			 * @return rep_t
			 */
			[[nodiscard]]
			rep_t
			elapsed () noexcept
			{
				const auto top = std::chrono::steady_clock::now();

				return std::chrono::duration_cast< std::chrono::duration< rep_t, period_t > >(top - m_previousTime).count();
			}

			/**
			 * @brief Returns whether the interval expressed by the granularity parameter is elapsed and returns the duration overflow.
			 * @return time A reference to a value to express if interval is elapsed, the time overflow, if not the remaining time (all using period_t, the time unit).
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isIntervalElapsed (rep_t & time) noexcept
			{
				const auto top = std::chrono::steady_clock::now();

				const auto delta = std::chrono::duration_cast< std::chrono::duration< rep_t, period_t > >(top - m_previousTime).count();
				const auto intervalDuration = m_granularity.count();

				if ( delta < intervalDuration )
				{
					/* Report the remaining time. */
					time = intervalDuration - delta;

					return false;
				}

				/* Report the time overflow */
				time = delta - intervalDuration;

				m_previousTime = top - std::chrono::duration< rep_t, period_t >{time};

				return true;
			}

			/**
			 * @brief Resets the previous top.
			 * @return void
			 */
			void
			resetTop () noexcept
			{
				m_previousTime = std::chrono::steady_clock::now();
			}

			/**
			 * @brief Starts the timer of the event.
			 * @return void
			 */
			void
			start () noexcept
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

			/**
			 * @brief Stops the timer of the event.
			 * @return void
			 */
			void
			stop () noexcept
			{
				m_flags[IsProcessActive] = false;
			}

			/**
			 * @brief Pauses the timer of the event.
			 * @return void
			 */
			void
			pause () noexcept
			{
				if ( !m_flags[IsProcessCreated] || !m_flags[IsProcessActive] )
				{
					return;
				}

				m_flags[IsProcessActive] = false;
				m_flags[IsProcessPaused] = true;
			}

			/**
			 * @brief Resumes the timer of the event.
			 * @return void
			 */
			void
			resume () noexcept
			{
				if ( !m_flags[IsProcessPaused] )
				{
					return;
				}

				m_flags[IsProcessActive] = true;
				m_flags[IsProcessPaused] = false;
			}

			/**
			 * @brief Returns whether the event is running.
			 * @return bool.
			 */
			[[nodiscard]]
			bool
			isStarted () const noexcept
			{
				return m_flags[IsProcessActive];
			}

			/**
			 * @brief Returns whether the event is on pause.
			 * @return bool.
			 */
			[[nodiscard]]
			bool
			isPaused () const noexcept
			{
				return m_flags[IsProcessPaused];
			}

			/**
			 * @brief Returns whether the event is fired only once.
			 * @return bool.
			 */
			[[nodiscard]]
			bool
			once () const noexcept
			{
				return m_flags[OnlyOnce];
			}

		private:

			/**
			 * @brief Thread task.
			 * @param event A pointer to the timed event.
			 * @return void
			 */
			static
			void
			process (TimedEvent * event) noexcept
			{
				while ( event->m_flags[IsProcessCreated] )
				{
					if ( event->m_flags[IsProcessActive] )
					{
						rep_t time;

						/* If the delay is elapsed we fire the event. */
						if ( event->isIntervalElapsed(time) )
						{
							if ( event->m_function(event->m_timerId) || event->once() )
							{
								event->stop();
							}
						}
						else
						{
							/* NOTE: Balance CPU work to avoid burning it.
							 * We put the thread on standby for the remaining time. */
							std::this_thread::sleep_for(std::chrono::duration< rep_t, period_t >{time});
						}

						continue;
					}

					/* NOTE: Balance CPU work to avoid burning it.
					 * We put the thread to sleep while waiting for the timer to resume. */
					std::this_thread::sleep_for(std::chrono::milliseconds{SleepTimeForUnactiveProcess});
				}
			}

			/* Flag names. */
			static constexpr auto OnlyOnce{0UL};
			static constexpr auto IsProcessCreated{1UL};
			static constexpr auto IsProcessActive{2UL};
			static constexpr auto IsProcessPaused{3UL};

			static constexpr rep_t SleepTimeForUnactiveProcess{300};

			std::chrono::duration< rep_t, period_t > m_granularity{std::chrono::seconds{1}};
			std::chrono::time_point< std::chrono::steady_clock > m_previousTime{std::chrono::steady_clock::now()};
			std::function< bool (TimerID) > m_function;
			std::thread m_thread;
			TimerID m_timerId{0};
			std::array< bool, 8 > m_flags{
				false/*OnlyOnce*/,
				false/*IsProcessCreated*/,
				false/*IsProcessActive*/,
				false/*IsProcessPaused*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
