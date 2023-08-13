/*
 * Libraries/GameTools/Dice.cpp
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

#include "Dice.hpp"

/* C/C++ standard libraries. */
#include <random>

/* Local inclusions */
#include "Utility.hpp"

namespace Libraries::GameTools
{
	Dice::Dice (size_t faceCount) noexcept
		: m_faceCount(std::max(2UL, faceCount))
	{
		this->reset();
	}

	size_t
	Dice::roll () noexcept
	{
		return std::uniform_int_distribution{1UL, m_faceCount}(m_randomEngine);
	}

	void
	Dice::reset () noexcept
	{
		const auto seed = std::random_device{}();

		m_randomEngine.seed(seed);
	}
}
