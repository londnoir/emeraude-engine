/*
 * src/PlatformSpecific/SystemInfo.windows.cpp
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

#if IS_WINDOWS

/* STL inclusions. */
#include <iostream>
#include <string>

/* Third-party inclusions. */
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <Windows.h>
#include <psapi.h>

/* Local inclusions. */
#include "Helpers.hpp"

namespace EmEn::PlatformSpecific
{
	bool
	SystemInfo::fetchOSInformation () noexcept
	{
		try
		{
			const std::wstring systemName = getStringValueFromHKLM(L"SOFTWARE\\MICROSOFT\\windows nt\\currentversion", L"ProductName");
			const std::wstring systemVersion = getStringValueFromHKLM(L"SOFTWARE\\MICROSOFT\\windows nt\\currentversion", L"CurrentBuildNumber");

			m_OSInformation.systemName = convertWideToUTF8(systemName);
			m_OSInformation.systemVersion = convertWideToUTF8(systemVersion);
		}
		catch ( std::exception & e )
		{
			std::cerr << e.what();

			return false;
		}

		// TODO: Not required for now
		m_OSInformation.computerName = "MyComputer";

		return true;
	}

	size_t
	SystemInfo::getTotalMemory () noexcept
	{
		/* Doc: https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-globalmemorystatusex */
		MEMORYSTATUSEX status{};
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);

		return status.ullTotalPhys;
	}

	size_t
	SystemInfo::getFreeMemory () noexcept
	{
		MEMORYSTATUSEX status{};
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);

		return status.ullAvailPhys;
	}

	size_t
	SystemInfo::getPeakRSS () noexcept
	{
		PROCESS_MEMORY_COUNTERS info{};

		GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));

		return info.PeakWorkingSetSize;
	}

	size_t
	SystemInfo::getCurrentRSS () noexcept
	{
		PROCESS_MEMORY_COUNTERS info{};

		GetProcessMemoryInfo(GetCurrentProcess(), &info, sizeof(info));

		return info.WorkingSetSize;
	}

	std::filesystem::path
	SystemInfo::getRealApplicationDir () noexcept
	{
		std::string realPath(1024, '\0');

		GetModuleFileNameA(
			nullptr,
			realPath.data(),
			static_cast< DWORD >(realPath.size())
		);

		const auto position = realPath.find_last_of('\\');

		return
			position == std::string::npos ?
			realPath :
			realPath.substr(0, position);
	}
}

#endif
