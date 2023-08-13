/*
 * Libraries/Time/PrintScopeTime.hpp
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
#include <iostream>
#include <string>

namespace Libraries::Time
{
	/**
	 * @brief Print in the console the duration in wall clock time of a specific scope.
	 * @note The internal precision is set to nanoseconds.
	 * @tparam clockType The type of clock used. Default std::chrono::high_resolution_clock.
	 */
	template< typename clockType = std::chrono::high_resolution_clock >
	class [[maybe_unused]] PrintScopeTime
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
			PrintScopeTime () noexcept = default;

			/**
			 * @brief Starts a nano timer.
			 * @param label A reference to a string for the output [std::move].
			 * @param precision The rounded precision desired for the output. Default milliseconds.
			 */
			explicit
			PrintScopeTime (std::string label, Precision precision = Precision::Milliseconds) noexcept
				: m_label(std::move(label)), m_precision(precision)
			{

			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			PrintScopeTime (const PrintScopeTime & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			PrintScopeTime (PrintScopeTime && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			PrintScopeTime & operator= (const PrintScopeTime & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			PrintScopeTime & operator= (PrintScopeTime && copy) noexcept = delete;

			/**
			 * @brief The destructor will print out the result.
			 */
			// NOLINTBEGIN(*-magic-numbers)
			~PrintScopeTime ()
			{
				const auto nanoseconds = std::chrono::duration_cast< std::chrono::nanoseconds >(clockType::now() - m_start).count();

				switch ( m_precision )
				{
					case Precision::Seconds:
						std::cout << m_label << " : " << static_cast< double >(nanoseconds) / 1000000000.0 << " s" "\n";
						break;

					case Precision::Milliseconds:
						std::cout << m_label << " : " << static_cast< double >(nanoseconds) / 1000000.0 << " ms" "\n";
						break;

					case Precision::Microseconds:
						std::cout << m_label << " : " << static_cast< double >(nanoseconds) / 1000.0 << " μs" "\n";
						break;

					case Precision::Nanoseconds:
						std::cout << m_label << " : " << nanoseconds << " ms" "\n" << std::endl;
						break;
				}
			}
			// NOLINTEND(*-magic-numbers)

		private:

			std::chrono::time_point< clockType > m_start{clockType::now()};
			std::string m_label{"Time"};
			Precision m_precision{Precision::Milliseconds};
	};
}
