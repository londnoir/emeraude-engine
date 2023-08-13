/*
 * Libraries/Time/AbstractStatistics.hpp
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
#include <cstddef>
#include <vector>

namespace Libraries::Time
{
	/**
	 * @brief The AbstractStatistics class
	 */
	class AbstractStatistics
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractStatistics (const AbstractStatistics & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractStatistics (AbstractStatistics && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractStatistics &
			 */
			AbstractStatistics & operator= (const AbstractStatistics & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractStatistics &
			 */
			AbstractStatistics & operator= (AbstractStatistics && copy) noexcept = default;

			/**
			 * @brief Destructs the statistics.
			 */
			virtual ~AbstractStatistics () = default;

			/**
			 * @brief Returns the last duration in milliseconds.
			 * @return unsigned long int
			 */
			[[nodiscard]]
			virtual unsigned long int duration () const noexcept final;

			/**
			 * @brief Returns the average duration in milliseconds.
			 * @return double
			 */
			[[nodiscard]]
			virtual double averageDuration () const noexcept final;

			/**
			 * @brief Returns the last executions count per second registered.
			 * @return unsigned int
			 */
			[[nodiscard]]
			virtual unsigned int executionsPerSecond () const noexcept final;

			/**
			 * @brief Returns the average executions count per second registered.
			 * @return double
			 */
			[[nodiscard]]
			virtual double averageExecutionsPerSecond () const noexcept final;

			/**
			 * @brief Returns the range of samples for averaging.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t range () const noexcept final;

			/**
			 * @brief Returns the number of stat taken.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t topCount () const noexcept final;

			/**
			 * @brief Prints statistics in console.
			 * @return void
			 */
			virtual void print () const noexcept final;

			/**
			 * @brief Starts a measurement.
			 * @return void
			 */
			virtual void start () noexcept = 0;

			/**
			 * @brief Stops the measurement.
			 * @return void
			 */
			virtual void stop () noexcept = 0;

		protected:

			/**
			 * @brief Constructs a statistics.
			 * @param range The range. Default 1.
			 */
			explicit AbstractStatistics (size_t range = 1) noexcept;

			/**
			 * @brief Increments the index.
			 * @param index A reference to an index.
			 * @return void
			 */
			void incrementIndex (size_t & index) const noexcept;

			/**
			 * @brief Returns the previous index.
			 * @param index The index.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t getPreviousIndex (size_t index) const noexcept;

			/**
			 * @brief Inserts a duration.
			 * @param duration The duration in milliseconds.
			 * @return void
			 */
			void insertDuration (unsigned long int duration) noexcept;

			/**
			 * @brief Inserts an execution count per seconds.
			 * @param count The number of execution.
			 * @return void
			 */
			void insertEPS (unsigned int count) noexcept;

		private:

			size_t m_range{1};
			std::vector< unsigned long int > m_durations{};
			std::vector< unsigned int > m_executionsPerSeconds{};
			size_t m_topCount{0};
			size_t m_durationIndex{0};
			size_t m_EPSIndex{0};
	};
}
