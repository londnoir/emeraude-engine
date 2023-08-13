/*
 * Libraries/Dummy.cpp
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

#include "Dummy.hpp"

/* C/C++ standard libraries. */
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

	void
	Dummy::setValue (int value)
	{
		m_value = value;
	}

	int
	Dummy::value () const
	{
		return m_value;
	}
}
