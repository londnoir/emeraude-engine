/*
 * Libraries/Time/Time.hpp
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
#include <cstdint>
#include <string>

namespace Libraries::Time
{
	/** @brief Returns the time point when the program has started. */
	static const std::chrono::time_point< std::chrono::steady_clock > ProgramStaringTime{std::chrono::steady_clock::now()};

	/**
	 * @brief Returns the elapsed time in seconds since the start of th program.
	 * @return long
	 */
	inline
	long
	elapsedSeconds () noexcept
	{
		return std::chrono::duration_cast< std::chrono::seconds >(std::chrono::steady_clock::now() - ProgramStaringTime).count();
	}

	/**
	 * @brief Returns the elapsed time in milliseconds since the start of th program.
	 * @return long
	 */
	inline
	long
	elapsedMilliseconds () noexcept
	{
		return std::chrono::duration_cast< std::chrono::milliseconds >(std::chrono::steady_clock::now() - ProgramStaringTime).count();
	}

	/**
	 * @brief Returns the elapsed time in nanoseconds since the start of th program.
	 * @return long
	 */
	inline
	long
	elapsedMicroseconds () noexcept
	{
		return std::chrono::duration_cast< std::chrono::microseconds >(std::chrono::steady_clock::now() - ProgramStaringTime).count();
	}

	/**
	 * @brief Returns UNIX timestamp as a simple integer.
	 * @return unsigned int
	 */
	inline
	unsigned int
	UNIXTimestamp () noexcept
	{
		return static_cast< unsigned int >(std::time(nullptr));
	}

	/**
	 * @brief Returns UNIX timestamp as a string.
	 * @return std::string
	 */
	inline
	std::string
	UNIXTimestampString () noexcept
	{
		return (std::stringstream{} << UNIXTimestamp()).str();
	}
}
