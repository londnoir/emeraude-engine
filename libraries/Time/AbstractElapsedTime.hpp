/*
 * Libraries/Time/AbstractElapsedTime.hpp
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

namespace Libraries::Time
{
	/**
	 * @brief The AbstractElapsedTime class
	 */
	class AbstractElapsedTime
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractElapsedTime (const AbstractElapsedTime & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractElapsedTime (AbstractElapsedTime && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractElapsedTime &
			 */
			AbstractElapsedTime & operator= (const AbstractElapsedTime & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractElapsedTime &
			 */
			AbstractElapsedTime & operator= (AbstractElapsedTime && copy) noexcept = default;

			/**
			 * @brief Destructs the elapsed time structure.
			 */
			virtual ~AbstractElapsedTime () = default;

			/**
			 * @brief Returns the duration in nanoseconds.
			 * @return unsigned long int
			 */
			[[nodiscard]]
			virtual unsigned long int duration () const noexcept final;

			/**
			 * @brief Returns the duration in seconds.
			 * @return double
			 */
			[[nodiscard]]
			virtual double seconds () const noexcept final;

			/**
			 * @brief Returns the duration in milliseconds.
			 * @return double
			 */
			[[nodiscard]]
			virtual double milliseconds () const noexcept final;

			/**
			 * @brief Returns the duration in microseconds.
			 * @return double
			 */
			[[nodiscard]]
			virtual double microseconds () const noexcept final;

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
			 * @brief Constructs an elapsed time structure.
			 */
			AbstractElapsedTime () noexcept = default;

			/**
			 * @brief Set duration in nanoseconds.
			 * @param duration The duration in nanoseconds.
			 * @return void
			 */
			void setDuration (unsigned long int duration) noexcept;

		private:

			unsigned long int m_duration{0};
	};
}
