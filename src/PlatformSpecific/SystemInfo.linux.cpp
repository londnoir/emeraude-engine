/*
 * src/PlatformSpecific/SystemInfo.linux.cpp
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

#include "SystemInfo.hpp"

#if IS_LINUX

/* STL inclusions. */
#include <fstream>
#include <string>
#include <filesystem>

/* Third-party inclusions. */
#include <unistd.h>
#include <sys/resource.h>
#include <sys/utsname.h>

/* Local inclusions. */
#include "Libraries/String.hpp"

namespace Emeraude::PlatformSpecific
{
	bool
	SystemInfo::fetchOSInformation () noexcept
	{
		{
			std::ifstream osReleaseFile{"/etc/os-release"};

			if ( osReleaseFile.is_open() )
			{
				std::string line;

				while ( std::getline(osReleaseFile, line) )
				{
					if ( line.starts_with("PRETTY_NAME") )
					{
						auto & name = m_OSInformation.systemName;
						name = Libraries::String::right(line, "=");
						std::erase(name, '"');
					}
				}
			}
		}

		{
			std::stringstream rawInformation;

			utsname info{};

			if ( uname(&info) != 0 )
			{
				return {};
			}

			rawInformation <<
				"System name : " << info.sysname << "\n"
				"Node name : " << info.nodename << "\n"
				"Release : " << info.release << "\n"
				"Version : " << info.version << "\n"
				"Machine : " << info.machine << "\n";

#ifdef _GNU_SOURCE
			rawInformation << "Domain name : " << info.domainname << "\n";
#endif

			m_OSInformation.systemVersion = info.version;
			m_OSInformation.computerName = info.nodename;
			m_OSInformation.rawInformation = rawInformation.str();
		}

		return true;
	}

	size_t
	SystemInfo::getTotalMemory () noexcept
	{
		return sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGE_SIZE);
	}

	size_t
	SystemInfo::getFreeMemory () noexcept
	{
		return sysconf(_SC_AVPHYS_PAGES) * sysconf(_SC_PAGESIZE);
	}

	size_t
	SystemInfo::getPeakRSS () noexcept
	{
		rusage rusage{};
		getrusage( RUSAGE_SELF, &rusage);

		return rusage.ru_maxrss * 1024UL;
	}

	size_t
	SystemInfo::getCurrentRSS () noexcept
	{
		std::ifstream statFile{"/proc/self/statm"};

		if ( !statFile.is_open() )
		{
			return 0;
		}

		/* ie: "92957 20466 16854 854 0 1627 0" */
		std::string line;
		std::getline(statFile, line);

		/* NOTE: We need the second number. */
		const auto position = line.find_first_of(' ');

		if ( position == std::string::npos )
		{
			return 0;
		}

		const auto bytes = std::strtol(&line.at(position), nullptr, 10);

		return static_cast< size_t >(bytes * sysconf( _SC_PAGESIZE));
	}

	std::filesystem::path
	SystemInfo::getRealApplicationDir () noexcept
	{
		const std::string realPath = std::filesystem::canonical("/proc/self/exe");

		const auto position = realPath.find_last_of('/');

		return
			position == std::string::npos ?
			realPath :
			realPath.substr(0, position);
	}
}

#endif
