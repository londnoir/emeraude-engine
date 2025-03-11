/*
 * src/Libs/Time/Elapsed/CPUTime.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "CPUTime.hpp"

/* STL inclusions. */
#include <ctime>

namespace EmEn::Libs::Time::Elapsed
{
	void
	CPUTime::start () noexcept
	{
		m_startTime = std::clock();
	}

	void
	CPUTime::stop () noexcept
	{
		if constexpr ( CLOCKS_PER_SEC == 1000 )
		{
			/* Duration is expressed in milliseconds. */
			this->setDuration((std::clock() - m_startTime) * 1000000);
		}

		if constexpr ( CLOCKS_PER_SEC == 1000000 )
		{
			/* Duration is expressed in microseconds. */
			this->setDuration((std::clock() - m_startTime) * 1000);
		}

		if constexpr ( CLOCKS_PER_SEC == 1000000000 )
		{
			/* Duration is expressed in nanoseconds. */
			this->setDuration(std::clock() - m_startTime);
		}
	}
}
