/*
 * Libraries/Time/StatisticsCPUTime.hpp
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
#include <ctime>

/* Local inclusions */
#include "AbstractStatistics.hpp"

namespace Libraries::Time
{
	/**
	 * @brief A chrono to get the duration in CPU time between two tops.
	 * @extends Libraries::Time::AbstractStatistics The interface for statistics.
	 */
	class [[maybe_unused]] StatisticsCPUTime final : public AbstractStatistics
	{
		public:

			/**
			 * @brief Constructs a stat counter in CPU time.
			 * @param range range The range of ???. Default 1.
			 */
			explicit StatisticsCPUTime (size_t range = 1) noexcept;

			/**
			 * @brief Starts a measurement.
			 * @return void
			 */
			void start () noexcept override;

			/**
			 * @brief Stops the measurement.
			 * @return void
			 */
			void stop () noexcept override;

		private:

			std::clock_t m_startTime = 0;
			unsigned long int m_delta = 0;
			unsigned int m_currentExecutionsPerSecond = 0;
	};
}
