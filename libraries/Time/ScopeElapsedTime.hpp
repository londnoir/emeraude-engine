/*
 * Libraries/Time/ScopeElapsedTime.hpp
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

namespace Libraries::Time
{
	/**
	 * @brief Gets the duration in wall clock time of a specific scope.
	 * @note The internal precision is set to nanoseconds.
	 * @tparam clockType The type of clock used. Default std::chrono::high_resolution_clock.
	 */
	template< typename clockType = std::chrono::high_resolution_clock >
	class [[maybe_unused]] ScopeElapsedTime final
	{
		public:

			/**
			 * @brief Construct a scope timer in nanoseconds.
			 * @param duration A reference where the duration will be accumulated in nanoseconds.
			 */
			explicit
			ScopeElapsedTime (unsigned long int & duration) noexcept
				: m_duration(duration)
			{

			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ScopeElapsedTime (const ScopeElapsedTime & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ScopeElapsedTime (ScopeElapsedTime && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			ScopeElapsedTime & operator= (const ScopeElapsedTime & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			ScopeElapsedTime & operator= (ScopeElapsedTime && copy) noexcept = delete;

			/**
			 * @brief Destructs the scope timer
			 */
			~ScopeElapsedTime ()
			{
				m_duration += std::chrono::duration_cast< std::chrono::nanoseconds >(clockType::now() - m_startTime).count();
			}

		private:

			unsigned long int & m_duration; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
			std::chrono::time_point< clockType > m_startTime{clockType::now()};
	};
}
