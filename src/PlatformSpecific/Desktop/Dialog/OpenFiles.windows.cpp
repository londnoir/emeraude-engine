/*
 * src/UserDialogs/OpenFiles.windows.cpp
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

#include "OpenFiles.hpp"

#if IS_WINDOWS

/* STL inclusions. */
#include <vector>
#include <map>
#include <sstream>

/* Third-party inclusions. */
#include <shobjidl.h>
#include <commdlg.h>

/* Local inclusions. */
#include "PlatformSpecific/Helpers.hpp"
#include "Window.hpp"

namespace Emeraude::PlatformSpecific::Desktop::Dialog
{
	std::map< std::wstring, std::wstring >
	getExtensionFiltersAsWString (const std::map< std::string, std::vector< std::string > > & extensionFilters)
	{
		std::map< std::wstring, std::wstring > output{};

		for ( const auto & extensionFilter : extensionFilters )
		{
			std::stringstream extensionsRule{};

			for ( const auto & extension : extensionFilter.second )
			{
				extensionsRule << "*." << extension << ";";
			}

			const std::string extensionsRuleStr = extensionsRule.str();

			output.emplace(
				std::wstring{extensionFilter.first.cbegin(), extensionFilter.first.cend()},
				std::wstring{extensionsRuleStr.begin(), extensionsRuleStr.end()}
			);
		}

		return output;
	}

	bool
	OpenFiles::execute (Window * window) noexcept
	{
		/* Create the FileOpenDialog object. */
		IFileOpenDialog * fileDialog = nullptr;

		if ( CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast< void * * >(&fileDialog)) < 0 )
		{
			return false;
		}

		/* Create the file types allowed in the dialog. */
		const auto & extensionFilters = getExtensionFiltersAsWString(m_extensionFilters);

		std::vector< COMDLG_FILTERSPEC > fileTypes{};
		fileTypes.reserve(extensionFilters.size());

		for ( const auto & extensionFilter : extensionFilters )
		{
			COMDLG_FILTERSPEC type{extensionFilter.first.data(), extensionFilter.second.data()};

			fileTypes.emplace_back(type);
		}

		fileDialog->SetFileTypes(fileTypes.size(), fileTypes.data());
		fileDialog->SetOptions(OFN_ALLOWMULTISELECT);

		const auto & title = this->title();
		std::wstring wsTitle(title.cbegin(), title.cend());

		fileDialog->SetTitle(wsTitle.data());

		/* Show the Open dialog box. */
		HWND parentWindow = window != nullptr ? window->getWin32Window() : nullptr;

		if ( fileDialog->Show(parentWindow) < 0 )
		{
			return false;
		}

		IShellItemArray * pItems = nullptr;

		if ( fileDialog->GetResults(&pItems) >= 0 )
		{
			DWORD fileCount{0};
			pItems->GetCount(&fileCount);

			for ( DWORD index = 0; index < fileCount; index++ )
			{
				IShellItem * pItem = nullptr;
				pItems->GetItemAt(index, &pItem);

				{
					PWSTR pszFilePath = nullptr;
					pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

					m_filePaths.emplace_back(convertWideToANSI({pszFilePath}));

					CoTaskMemFree(pszFilePath);
				}

				pItem->Release();
			}

			pItems->Release();
		}

		fileDialog->Release();

		return true;
	}
}

#endif
