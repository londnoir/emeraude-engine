/*
 * Libraries/Statistics.hpp
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

/* Information

struct timespec timer = begin_timer();

// Do stuffs ...

long delay = terminate_timer(timer);

printf("Time elapsed : %ld ns\n", delay);

*/

#pragma once

extern "C"
{
	/* C standard libraries */
	#include <time.h>

	/**
	 * @brief Calls this function to execute a nanosecond-resolution timer.
	 * @param start_time
	 * @return void
	 */
	[[maybe_unused]]
	void begin_timer (struct timespec * start_time) noexcept;

	/**
	 * @brief Calls this function to end a timer, returning nanoseconds elapsed as a long.
	 * @param start_time
	 * @return long
	 */
	[[maybe_unused]]
	long terminate_timer (struct timespec start_time) noexcept;
}
