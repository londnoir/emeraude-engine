/*
 * Libraries/Version.cpp
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

#include "Version.hpp"

/* C/C++ standard libraries. */
#include <iostream>
#include <sstream>

/* Local inclusions */
#include "String.hpp"

namespace Libraries
{
	Version::Version (const std::string & raw) noexcept
	{
		if ( !this->set(raw) )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", " << raw << " is not a valid string for a version representation." << "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
		}
	}

	// NOLINTBEGIN(*-magic-numbers)
	Version::Version (uint32_t bitmask) noexcept
		: m_major(static_cast< int >(bitmask >> 22)),
		m_minor(static_cast< int >(((bitmask << 10) >> 10) >> 12)),
		m_revision(static_cast< int >((bitmask << 20) >> 20))
	{

	}
	// NOLINTEND(*-magic-numbers)

	bool
	Version::operator== (const Version & operand) const noexcept
	{
		if ( this != &operand )
		{
			if ( operand.m_major != m_major )
			{
				return false;
			}

			if ( operand.m_minor != m_minor )
			{
				return false;
			}

			if ( operand.m_revision != m_revision )
			{
				return false;
			}
		}

		return true;
	}

	bool
	Version::operator!= (const Version & operand) const noexcept
	{
		return !this->operator==(operand);
	}

	bool
	Version::operator> (const Version & operand) const noexcept
	{
		if ( m_major > operand.m_major )
		{
			return true;
		}

		if ( m_major == operand.m_major && m_minor > operand.m_minor )
		{
			return true;
		}

		if ( m_major == operand.m_major && m_minor == operand.m_minor && m_revision > operand.m_revision )
		{
			return true;
		}

		return false;
	}

	bool
	Version::operator>= (const Version & operand) const noexcept
	{
		if ( m_major > operand.m_major )
		{
			return true;
		}

		if ( m_major == operand.m_major && m_minor > operand.m_minor )
		{
			return true;
		}

		if ( m_major == operand.m_major && m_minor == operand.m_minor && m_revision >= operand.m_revision )
		{
			return true;
		}

		return false;
	}

	bool
	Version::operator< (const Version & operand) const noexcept
	{
		if ( m_major < operand.m_major )
		{
			return true;
		}

		if ( m_major == operand.m_major && m_minor < operand.m_minor )
		{
			return true;
		}

		if ( m_major == operand.m_major && m_minor == operand.m_minor && m_revision < operand.m_revision )
		{
			return true;
		}

		return false;
	}

	bool
	Version::operator<= (const Version & operand) const noexcept
	{
		if ( m_major < operand.m_major )
		{
			return true;
		}

		if ( m_major == operand.m_major && m_minor < operand.m_minor )
		{
			return true;
		}

		if ( m_major == operand.m_major && m_minor == operand.m_minor && m_revision <= operand.m_revision )
		{
			return true;
		}

		return false;
	}

	void
	Version::set (int major, int minor, int revision) noexcept
	{
		m_major = major;
		m_minor = minor;
		m_revision = revision;
	}

	bool
	Version::set (const std::string & raw) noexcept
	{
		const auto chunks = String::explode(raw, '.');

		if ( chunks.size() < 3 )
		{
			return false;
		}

		m_major = String::toNumber< int >(chunks[0]);
		m_minor = String::toNumber< int >(chunks[1]);
		m_revision = String::toNumber< int >(chunks[2]);

		return true;
	}

	void
	Version::setMajor (int value) noexcept
	{
		m_major = value;
	}

	void
	Version::setMinor (int value) noexcept
	{
		m_minor = value;
	}

	void
	Version::setRevision (int value) noexcept
	{
		m_revision = value;
	}

	int
	Version::major () const noexcept
	{
		return m_major;
	}

	int
	Version::minor () const noexcept
	{
		return m_minor;
	}

	int
	Version::revision () const noexcept
	{
		return m_revision;
	}

	std::ostream &
	operator<< (std::ostream & out, const Version & obj)
	{
		return out << obj.m_major << '.' << obj.m_minor << '.' << obj.m_revision;
	}

	std::string
	to_string (const Version & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
