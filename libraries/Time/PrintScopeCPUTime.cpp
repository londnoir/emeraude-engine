/*
 * Libraries/Time/PrintScopeCPUTime.cpp
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

#include "PrintScopeCPUTime.hpp"

/* C/C++ standard libraries. */
#include <iostream>

namespace Libraries::Time
{
	PrintScopeCPUTime::PrintScopeCPUTime (std::string label, Precision precision) noexcept
		: m_label(std::move(label)), m_precision(precision)
	{

	}

	// NOLINTBEGIN(*-magic-numbers)
	PrintScopeCPUTime::~PrintScopeCPUTime ()
	{
		auto duration = 0UL;

		if constexpr ( CLOCKS_PER_SEC == 1000 )
		{
			/* Duration is expressed in milliseconds. */
			duration = (std::clock() - m_start) * 1000000;
		}

		if constexpr ( CLOCKS_PER_SEC == 1000000 )
		{
			/* Duration is expressed in microseconds. */
			duration = (std::clock() - m_start) * 1000;
		}

		if constexpr ( CLOCKS_PER_SEC == 1000000000 )
		{
			/* Duration is expressed in nanoseconds. */
			duration = std::clock() - m_start;
		}

		switch ( m_precision )
		{
			case Precision::Seconds:
				std::cout << m_label << " (CPU) : " << static_cast< double >(duration) / 1000000000.0 << " s" "\n";
				break;

			case Precision::Milliseconds:
				std::cout << m_label << " (CPU) : " << static_cast< double >(duration) / 1000000.0 << " ms" "\n";
				break;

			case Precision::Microseconds:
				std::cout << m_label << " (CPU) : " << static_cast< double >(duration) / 1000.0 << " μs" "\n";
				break;

			case Precision::Nanoseconds:
				std::cout << m_label << " (CPU) : " << duration << " ms" "\n";
				break;
		}
	}
	// NOLINTEND(*-magic-numbers)
}
