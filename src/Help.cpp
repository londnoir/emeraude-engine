/*
 * Emeraude/Help.cpp
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

#include "Help.hpp"

/* C/C++ standard libraries */
#include <sstream>

/* Local inclusions */
#include "Tracer.hpp"

namespace Emeraude
{
	const size_t Help::ClassUID{Observable::getClassUID()};

	Help::Help (const char * serviceInstanceName) noexcept
		: ServiceInterface(serviceInstanceName)
	{

	}

	bool
	Help::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	Help::usable () const noexcept
	{
		return true;
	}

	bool
	Help::onInitialize () noexcept
	{
		return true;
	}

	bool
	Help::onTerminate () noexcept
	{
		return true;
	}

	void
	Help::registerArgument (const ArgumentDoc & argumentDoc) noexcept
	{
		m_argumentDocs.emplace_back(argumentDoc);
	}

	void
	Help::registerArgument (const std::string & description, const std::string & longName, char shortName, const std::vector< std::string > & options) noexcept
	{
		m_argumentDocs.emplace_back(description, longName, shortName, options);
	}

	void
	Help::registerShortcut (const ShortcutDoc & shortcutDoc) noexcept
	{
		m_shortcutDocs.emplace_back(shortcutDoc);
	}

	void
	Help::registerShortcut (const std::string & description, Emeraude::Input::Key key, int modifiers) noexcept
	{
		m_shortcutDocs.emplace_back(description, key, modifiers);
	}

	const std::vector< ArgumentDoc > &
	Help::argumentDocs () const noexcept
	{
		return m_argumentDocs;
	}

	const std::vector< ShortcutDoc > &
	Help::shortcutDocs () const noexcept
	{
		return m_shortcutDocs;
	}

	std::string
	Help::argumentDocsString () const noexcept
	{
		std::stringstream output{};

		output << this->name() << " arguments : " "\n";

		for ( const auto & argumentDoc : m_argumentDocs )
		{
			output << '\t' << argumentDoc << '\n';
		}

		return output.str();
	}

	std::string
	Help::shortcutDocsString () const noexcept
	{
		std::stringstream output{};

		output << this->name() << " shortcuts : " "\n";

		for ( const auto & shortcutDoc : m_shortcutDocs )
		{
			output << '\t' << shortcutDoc << '\n';
		}

		return output.str();
	}
}
