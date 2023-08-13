/*
 * Libraries/Time/Interval.hpp
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
#include <chrono>

namespace Libraries::Time
{
	/**
	 * @brief Class defining an interval of time in milliseconds.
	 */
	class Interval
	{
		public:

			/**
			 * @brief Constructs a default interval.
			 */
			Interval () noexcept = default;

			/**
			 * @brief Constructs an interval.
			 * @param granularity The interval granularity in milliseconds.
			 * @param precise Use a precise timer. Default false.
			 */
			explicit Interval (double granularity, bool precise = false) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Interval (const Interval & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Interval (Interval && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Interval &
			 */
			Interval & operator= (const Interval & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Interval &
			 */
			Interval & operator= (Interval && copy) noexcept = default;

			/**
			 * @brief Destructs the interval.
			 */
			virtual ~Interval () = default;

			/**
			 * @brief Modifies the interval.
			 * @param granularity A floating number for milliseconds.
			 */
			virtual void setGranularity (double granularity) noexcept final;

			/**
			 * @brief Returns the delay in milliseconds.
			 * @return double
			 */
			[[nodiscard]]
			virtual double granularity () const noexcept final;

			/**
			 * @brief Returns whether the delay is elapsed.
			 * @return double. 0 if time is not elapsed or the number of milliseconds.
			 */
			virtual double elapsed () noexcept final;

			/**
			 * @brief  ???
			 * @todo FIXME: Add a time delay to reduce call to event system.
			 * @return void
			 */
			virtual void skipTime () noexcept final;

			/**
			 * @brief Resets the previous top.
			 * @return void
			 */
			virtual void resetTop () noexcept final;

			std::array< bool, 8 > m_flags{ // NOLINT
					false/*Precise*/,
					false/*UNUSED*/,
					false/*UNUSED*/,
					false/*UNUSED*/,
					false/*RESERVED FOR CHILD*/,
					false/*RESERVED FOR CHILD*/,
					false/*RESERVED FOR CHILD*/,
					false/*RESERVED FOR CHILD*/
			};

		private:

			/* Flag names. */
			static constexpr auto Precise = 0UL;

			double m_granularity{1000.0}; // NOLINT(*-magic-numbers)
			std::chrono::time_point< std::chrono::steady_clock > m_previousTime{std::chrono::steady_clock::now()};
	};
}
