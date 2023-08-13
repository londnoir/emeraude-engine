/*
 * Libraries/Time/ScopeElapsedCPUTime.hpp
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

namespace Libraries::Time
{
	/**
	 * @brief Gets the duration in CPU time of a specific scope.
	 * @note The internal precision is set to nanoseconds.
	 */
	class [[maybe_unused]] ScopeElapsedCPUTime final
	{
		public:

			/**
			 * @brief Construct a scope timer in nanoseconds.
			 * @param duration A reference where the duration will be accumulated in nanoseconds.
			 */
			explicit ScopeElapsedCPUTime (unsigned long int & duration) noexcept;

			/** @brief Deleted copy constructor. */
			ScopeElapsedCPUTime (const ScopeElapsedCPUTime &) = delete;

			/** @brief Deleted move constructor. */
			ScopeElapsedCPUTime (ScopeElapsedCPUTime &&) = delete;

			/** @brief Deleted assignment operator. */
			ScopeElapsedCPUTime & operator= (const ScopeElapsedCPUTime &) = delete;

			/** @brief Deleted move assignment operator. */
			ScopeElapsedCPUTime & operator= (const ScopeElapsedCPUTime &&) = delete;

			/** @brief Destructor. */
			~ScopeElapsedCPUTime ();

		private:

			unsigned long int & m_duration; // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
			std::clock_t m_start{std::clock()};
	};
}
