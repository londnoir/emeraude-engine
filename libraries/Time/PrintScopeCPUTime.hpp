/*
 * Libraries/Time/PrintScopeCPUTime.hpp
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
#include <string>

namespace Libraries::Time
{
	/**
	 * @brief Print in the console the duration in CPU time of a specific scope.
	 * @note The internal precision is set to nanoseconds.
	 */
	class [[maybe_unused]] PrintScopeCPUTime
	{
		public:

			/** @brief The type of precision on output. */
			enum class Precision
			{
				Seconds,
				Milliseconds,
				Microseconds,
				Nanoseconds
			};

			/**
			 * @brief Constructs a default scope timer.
			 */
			PrintScopeCPUTime () noexcept = default;

			/**
			 * @brief Starts a nano timer.
			 * @param label A reference to a string for the output [std::move].
			 * @param precision The rounded precision desired for the output. Default milliseconds.
			 */
			explicit PrintScopeCPUTime (std::string label, Precision precision = Precision::Milliseconds) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			PrintScopeCPUTime (const PrintScopeCPUTime & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			PrintScopeCPUTime (PrintScopeCPUTime && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			PrintScopeCPUTime & operator= (const PrintScopeCPUTime & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			PrintScopeCPUTime & operator= (PrintScopeCPUTime && copy) noexcept = delete;

			/**
			 * @brief The destructor will print out the result.
			 */
			~PrintScopeCPUTime ();

		private:

			std::clock_t m_start{std::clock()};
			std::string m_label{"Time"};
			Precision m_precision{Precision::Milliseconds};
	};
}
