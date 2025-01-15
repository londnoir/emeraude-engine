/*
 * src/Help.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "Help.hpp"

namespace Emeraude
{
	using namespace Libraries;
	
	Help::Help (const std::string & name) noexcept
		: NameableTrait(name)
	{

	}

	std::string
	Help::argumentDocsString () const noexcept
	{
		std::stringstream output;

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
		std::stringstream output;

		output << this->name() << " shortcuts : " "\n";

		for ( const auto & shortcutDoc : m_shortcutDocs )
		{
			output << '\t' << shortcutDoc << '\n';
		}

		return output.str();
	}

	std::string
	Help::getHelp () const noexcept
	{
		std::stringstream output;

		output <<
				"\n\n" << this->name() << " help." "\n" <<
				this->argumentDocsString() << '\n' <<
				this->shortcutDocsString() << '\n';

		return output.str();
	}
}
