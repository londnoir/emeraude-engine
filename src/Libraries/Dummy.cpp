/*
 * src/Libraries/Dummy.cpp
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

#include "Dummy.hpp"

/* STL inclusions. */
#include <iostream>

namespace Libraries
{
	Dummy::Dummy () noexcept
	{
		std::cout << "Default constructor" "\n";
	}

	Dummy::Dummy (int value) noexcept
		: m_value(value)
	{
		std::cout << "Parametric constructor" "\n";
	}

	Dummy::Dummy (const Dummy & copy) noexcept
		: m_value(copy.m_value)
	{
		std::cout << "Copy constructor" "\n";
	}

	Dummy::Dummy (Dummy && copy) noexcept
	{
		std::cout << "Move constructor" "\n";

		*this = std::move(copy);
	}

	Dummy &
	Dummy::operator= (const Dummy & copy) noexcept
	{
		std::cout << "Copy assignment" "\n";

		if ( this != &copy )
		{
			m_value = copy.m_value;
		}

		return *this;
	}

	Dummy::~Dummy ()
	{
		std::cout << "Destructor" "\n";
	}

	Dummy &
	Dummy::operator= (Dummy && copy) noexcept
	{
		std::cout << "Move assignment" "\n";

		if ( this != &copy )
		{
			m_value = copy.m_value;
		}

		return *this;
	}
}
