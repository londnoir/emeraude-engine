/*
 * Libraries/Time/TimedEvent.hpp
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
#include <array>
#include <functional>
#include <thread>

/* Local inclusions */
#include "Interval.hpp"

namespace Libraries::Time
{
	/** @brief Method signature for timed event. the parameter (double) will give the elapsed time for time correction. */
	using Function = std::function< void (double) >;

	/**
	 * @brief The TimedEvent class.
	 * @extends Libraries::Time::Interval This is an interval.
	 */
	class [[maybe_unused]] TimedEvent final : public Interval
	{
		public:

			/**
			 * @brief Constructs a timed event.
			 */
			TimedEvent () noexcept = default;

			/**
			 * @brief Constructs a timed event.
			 * @param function Lambda function to launch.
			 * @param granularity Milliseconds.
			 * @param precise Use a precise timer.
			 */
			TimedEvent (Function function, double granularity, bool once = false, bool precise = false) noexcept;

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
			~TimedEvent () override;

			/**
			 * @brief Starts the timer of the event.
			 * @return void
			 */
			void start () noexcept;

			/**
			 * @brief Stops the timer of the event.
			 * @return void
			 */
			void stop () noexcept;

			/**
			 * @brief Pauses the timer of the event.
			 * @return void
			 */
			void pause () noexcept;

			/**
			 * @brief Resumes the timer of the event.
			 * @return void
			 */
			void resume () noexcept;

			/**
			 * @brief Returns whether the event is running.
			 * @return bool.
			 */
			[[nodiscard]]
			bool isStarted () const noexcept;

			/**
			 * @brief Returns whether the event is on pause.
			 * @return bool.
			 */
			[[nodiscard]]
			bool isPaused () const noexcept;

			/**
			 * @brief Returns whether the event fires only once.
			 * @return bool.
			 */
			[[nodiscard]]
			bool once () const noexcept;

		private:

			/**
			 * @brief Thread task.
			 * @param event A pointer to the timed event.
			 * @return void
			 */
			static void process (TimedEvent * event) noexcept;

			/* Flag names shared with TimedEvent starting at 4. */
			static constexpr auto OnlyOnce = 4UL;
			static constexpr auto IsProcessCreated = 5UL;
			static constexpr auto IsProcessActive = 6UL;
			static constexpr auto IsProcessPaused = 7UL;

			Function m_function{};
			std::thread m_thread{};
	};
}
