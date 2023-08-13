/*
 * Libraries/Time/ElapsedTime.hpp
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
#include <chrono>

/* Local inclusions */
#include "AbstractElapsedTime.hpp"

namespace Libraries::Time
{
	/**
	 * @brief Gets the duration in wall clock time between two point in milliseconds.
	 * @note The internal precision is set to nanoseconds.
	 * @extends Libraries::Time::AbstractElapsedTime
	 * @tparam clockType The type of clock used. Default std::chrono::high_resolution_clock.
	 */
	template< typename clockType = std::chrono::high_resolution_clock >
	class [[maybe_unused]] ElapsedTime final : public AbstractElapsedTime
	{
		public:

			/**
			 * @brief Constructs an elapsed time structure.
			 */
			ElapsedTime () noexcept = default;

			/** @copydoc Libraries::Time::AbstractElapsedTime::start() */
			void
			start () noexcept override
			{
				m_startTime = clockType::now();
			}

			/** @copydoc Libraries::Time::AbstractElapsedTime::stop() */
			void
			stop () noexcept override
			{
				this->setDuration(std::chrono::duration_cast< std::chrono::nanoseconds >(clockType::now() - m_startTime).count());
			}

		private:

			std::chrono::time_point< clockType > m_startTime{};
	};

	/**
	 * @brief Gets the duration in CPU time between two point in milliseconds.
	 * @note The internal precision is set to nanoseconds.
	 * @extends Libraries::Time::AbstractElapsedTime
	 */
	class [[maybe_unused]] ElapsedCPUTime final : public AbstractElapsedTime
	{
		public:

			/**
			 * @brief Constructs an elapsed CPU time structure.
			 */
			ElapsedCPUTime () noexcept = default;

			/** @copydoc Libraries::Time::AbstractElapsedTime::start() */
			void start () noexcept override
			{
				m_startTime = std::clock();
			}

			/** @copydoc Libraries::Time::AbstractElapsedTime::stop() */
			void stop () noexcept override
			{
				this->setDuration(std::clock() - m_startTime);
			}

		private:

			std::clock_t m_startTime{};
	};
}
