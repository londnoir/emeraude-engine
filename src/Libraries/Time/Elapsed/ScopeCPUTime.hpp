/*
 * src/Libraries/Time/Elapsed/ScopeCPUTime.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <cstdint>
#include <ctime>

namespace Libraries::Time::Elapsed
{
	/**
	 * @brief Gets the duration in CPU time of a specific scope.
	 * @note The internal precision is set to nanoseconds.
	 */
	class ScopeCPUTime final
	{
		public:

			/**
			 * @brief Construct a scope timer in nanoseconds.
			 * @param duration A reference where the duration will be accumulated in nanoseconds.
			 */
			explicit ScopeCPUTime (uint64_t & duration) noexcept;

			/** @brief Deleted copy constructor. */
			ScopeCPUTime (const ScopeCPUTime &) = delete;

			/** @brief Deleted move constructor. */
			ScopeCPUTime (ScopeCPUTime &&) = delete;

			/** @brief Deleted assignment operator. */
			ScopeCPUTime & operator= (const ScopeCPUTime &) = delete;

			/** @brief Deleted move assignment operator. */
			ScopeCPUTime & operator= (const ScopeCPUTime &&) = delete;

			/** @brief Destructor. */
			~ScopeCPUTime ();

		private:

			uint64_t & m_duration;
			std::clock_t m_start{std::clock()};
	};
}
