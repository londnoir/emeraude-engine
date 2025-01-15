/*
 * src/PlatformSpecific/Helpers.windows.cpp
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

#include "Helpers.hpp"

#if IS_WINDOWS

/* STL inclusions. */
#include <iostream>
#include <stdexcept>

/* Third-party inclusions. */
#include <psapi.h>
#include <tlhelp32.h>

namespace Emeraude::PlatformSpecific
{
	std::wstring
	getStringValueFromHKLM (const std::wstring & regSubKey, const std::wstring & regValue)
	{
		size_t bufferSize = 0xFFF; // If too small, will be resized down below.
		std::wstring valueBuf;
		valueBuf.resize(bufferSize);

		auto cbData = static_cast< DWORD >(bufferSize * sizeof(wchar_t));
		auto rc = RegGetValueW(
			HKEY_LOCAL_MACHINE,
			regSubKey.c_str(),
			regValue.c_str(),
			RRF_RT_REG_SZ,
			nullptr,
			valueBuf.data(),
			&cbData
		);

		while ( rc == ERROR_MORE_DATA )
		{
			// Get a buffer that is big enough.
			cbData /= sizeof(wchar_t);

			if ( cbData > static_cast< DWORD >(bufferSize) )
			{
				bufferSize = static_cast<size_t>(cbData);
			}
			else
			{
				bufferSize *= 2;
				cbData = static_cast< DWORD >(bufferSize * sizeof(wchar_t));
			}

			valueBuf.resize(bufferSize);

			rc = RegGetValueW(
				HKEY_LOCAL_MACHINE,
				regSubKey.c_str(),
				regValue.c_str(),
				RRF_RT_REG_SZ,
				nullptr,
				static_cast<void*>(valueBuf.data()),
				&cbData
			);
		}

		if ( rc != ERROR_SUCCESS )
		{
			throw std::runtime_error("Windows system error code: " + std::to_string(rc));
		}

		cbData /= sizeof(wchar_t);
		valueBuf.resize(static_cast< size_t >(cbData - 1)); // remove end null character

		return valueBuf;
	}

	std::string
	convertWideToANSI (const std::wstring & input)
	{
		const int count = WideCharToMultiByte(
			CP_ACP,
			0,
			input.data(),
			static_cast< int >(input.length()),
			nullptr,
			0,
			nullptr,
			nullptr
		);

		std::string output{};
		output.resize(count);

		WideCharToMultiByte(
			CP_ACP,
			0,
			input.data(),
			-1,
			output.data(),
			count,
			nullptr,
			nullptr
		);

		return output;
	}

	std::wstring
	convertANSIToWide (const std::string & input)
	{
		const int count = MultiByteToWideChar(
			CP_ACP,
			0,
			input.data(),
			static_cast< int >(input.length()),
			nullptr,
			0
		);

		std::wstring output{};
		output.resize(count);

		MultiByteToWideChar(
			CP_ACP,
			0,
			input.data(),
			static_cast< int >(input.length()),
			output.data(),
			count
		);

		return output;
	}

	std::string
	convertWideToUTF8 (const std::wstring & input)
	{
		const int count = WideCharToMultiByte(
			CP_UTF8,
			0,
			input.data(),
			static_cast< int >(input.length()),
			nullptr,
			0,
			nullptr,
			nullptr
		);

		std::string output{};
		output.resize(count);

		WideCharToMultiByte(
			CP_UTF8,
			0,
			input.data(),
			-1,
			output.data(),
			count,
			nullptr,
			nullptr
		);

		return output;
	}

	std::wstring
	convertUTF8ToWide (const std::string & input)
	{
		const int count = MultiByteToWideChar(
			CP_UTF8,
			0,
			input.data(),
			static_cast< int >(input.length()),
			nullptr,
			0
		);

		std::wstring output{};
		output.resize(count);

		MultiByteToWideChar(
			CP_UTF8,
			0,
			input.data(),
			static_cast< int >(input.length()),
			output.data(),
			count
		);

		return output;
	}

	bool
	createConsole (const std::string & title)
	{
		if ( !AllocConsole() )
		{
			return false;
		}

		SetConsoleTitleA(title.c_str());

		// std::cout, std::clog, std::cerr, std::cin
		FILE * fDummy = nullptr;
		freopen_s(&fDummy, "CONOUT$", "w", stdout);
		freopen_s(&fDummy, "CONOUT$", "w", stderr);
		freopen_s(&fDummy, "CONIN$", "r", stdin);
		std::cout.clear();
		std::clog.clear();
		std::cerr.clear();
		std::cin.clear();

		auto hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleMode(hOutput, ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

		return true;
	}

	int
	getParentProcessId (DWORD pid) noexcept
	{
		DWORD ppid = 0;

		HANDLE h = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

		PROCESSENTRY32 pe{0};
		pe.dwSize = sizeof(PROCESSENTRY32);

		if ( Process32First(h, &pe) )
		{
			do
			{
				if ( pe.th32ProcessID == pid )
				{
					ppid = pe.th32ParentProcessID;
					break;
				}

			} while ( Process32Next(h, &pe) );
		}

		CloseHandle(h);

		return static_cast< int >(ppid);
	}
}

#endif
