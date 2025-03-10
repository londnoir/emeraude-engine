/*
 * src/PlatformSpecific/Desktop/Commands.cpp
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

#include "Commands.hpp"

/* Local inclusions. */
#include "Libraries/Network/URL.hpp"
#include "Tracer.hpp"

namespace Emeraude::PlatformSpecific::Desktop
{
	using namespace Libraries::Network;

	static constexpr auto TracerTag{"DesktopCommand"};

	bool
	openURL (const std::string & url) noexcept
	{
		if ( !URL::isURL(url) )
		{
			TraceWarning{TracerTag} << "The URL '" << url << "' is invalid !";

			return false;
		}

		runDesktopApplication(url);

		return true;
	}

	bool
	openFile (const std::filesystem::path & filepath) noexcept
	{
		if ( !std::filesystem::is_regular_file(filepath) )
		{
			TraceWarning{TracerTag} << "The file '" << filepath.string() << "' does not exist !";

			return false;
		}

		runDesktopApplication(filepath.string());

		return true;
	}

	bool
	openFolder (const std::filesystem::path & filepath) noexcept
	{
		if ( !std::filesystem::is_directory(filepath) )
		{
			TraceWarning{TracerTag} << "The file '" << filepath.string() << "' does not exist !";

			return false;
		}

		runDesktopApplication(filepath.string());

		return true;
	}

	bool
	showInFolder (const std::filesystem::path & filepath) noexcept
	{
		if ( !std::filesystem::is_regular_file(filepath) )
		{
			TraceWarning{TracerTag} << "The file '" << filepath.string() << "' does not exist !";

			return false;
		}

		runDesktopApplication(filepath.parent_path().string());

		return true;
	}
}
