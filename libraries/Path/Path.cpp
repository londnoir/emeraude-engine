/*
 * Libraries/Path/Path.cpp
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

#include "Path.hpp"

/* C/C++ standard libraries. */
#include <utility>

/* Local inclusions */
#include "String.hpp"

namespace Libraries::Path
{
	const std::array< std::string, 3 > Path::PathBases{{
		{"./"},
		{"../"},
		{"/"},
	}};

	Path::Path (const std::vector< std::string > & segments, std::string filename, std::string pathBase) noexcept
		: m_base(std::move(pathBase)), m_segments(segments), m_filename(std::move(filename))
	{

	}

	Path::Path (std::string rawString) noexcept
	{
		if ( rawString.empty() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", empty string !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		for ( const auto & base : PathBases )
		{
			if ( rawString.starts_with(base) )
			{
				this->setPathBase(base);

				rawString = String::replace(base, String::Empty, rawString, 1);

				break;
			}
		}

		m_segments = String::explode(rawString, Separator);

		if ( rawString.back() != Separator )
		{
			m_filename = m_segments.back();

			m_segments.pop_back();
		}
	}

	void
	Path::append (const std::string & name) noexcept
	{
		m_segments.emplace_back(name);
	}

	void
	Path::setPathBase (const std::string & pathBase) noexcept
	{
		m_base = pathBase;
	}

	void
	Path::setFilename (const std::string & name) noexcept
	{
		m_filename = String::removeChars(name, Separator);
	}

	const std::string &
	Path::pathBase () const noexcept
	{
		return m_base;
	}

	std::string
	Path::directory () const noexcept
	{
		if ( m_segments.empty() )
		{
			return m_base;
		}

		return m_base + String::implode(m_segments, Separator) + Separator;
	}

	const std::string &
	Path::filename () const noexcept
	{
		return m_filename;
	}

	std::ostream &
	operator<< (std::ostream & out, const Path & obj)
	{
		return out << obj.directory() << obj.m_filename;
	}

	std::string
	to_string (const Path & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
