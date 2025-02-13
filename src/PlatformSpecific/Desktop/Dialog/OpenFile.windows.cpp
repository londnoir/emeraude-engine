#include "OpenFile.hpp"

#if IS_WINDOWS

/* STL inclusions. */
#include <vector>
#include <map>

/* Third-party inclusions. */
#include <shobjidl.h>
#include <commdlg.h>

/* Local inclusions. */
#include "PlatformSpecific/Helpers.hpp"
#include "Window.hpp"
#include "Tracer.hpp"

namespace Emeraude::PlatformSpecific::Desktop::Dialog
{
	bool
	OpenFile::execute (Window * window) noexcept
	{
		IFileOpenDialog * dialogHandle = nullptr;

		HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast< void * * >(&dialogHandle));
		if ( FAILED(hr) )
		{
			Tracer::error(ClassId, "Unable to create the dialog instance !");

			return false;
		}

		/* NOTE: Create an automatic dialog release. */
		std::unique_ptr< IFileOpenDialog, void (*)(IFileOpenDialog *) > autoRelease(dialogHandle, [] (IFileOpenDialog * p) {
			p->Release();
		});

		/* NOTE: Set the dialog title. */
		const auto title = convertUTF8ToWide(this->title());

		hr = dialogHandle->SetTitle(title.data());
		if ( FAILED(hr) )
		{
			Tracer::error(ClassId, "Unable to set the title of the dialog instance !");

			return false;
		}

		/* NOTE: Set dialog options. */
		if ( m_flags[SelectFolder] || m_flags[MultiSelect] )
		{
			FILEOPENDIALOGOPTIONS options = 0;

			hr = dialogHandle->GetOptions(&options);
			if ( FAILED(hr) )
			{
				Tracer::error(ClassId, "Unable to get initial options from the dialog instance !");

				return false;
			}

			if ( m_flags[SelectFolder] )
			{
				options |= FOS_PICKFOLDERS;
			}

			if ( m_flags[MultiSelect] )
			{
				options |= FOS_ALLOWMULTISELECT;
			}

			hr = dialogHandle->SetOptions(options);
			if ( FAILED(hr) )
			{
				Tracer::error(ClassId, "Unable to set an option to the dialog instance !");

				return false;
			}
		}

		/* NOTE: Set the dialog file extension filter. */
		std::map< std::wstring, std::wstring > dataHolder;

		if ( m_extensionFilters.empty() )
		{
			COMDLG_FILTERSPEC save_filter[1];
			save_filter[0].pszName = L"All files";
			save_filter[0].pszSpec = L"*.*";

			hr = dialogHandle->SetFileTypes(1, save_filter);
			if ( FAILED(hr) )
			{
				Tracer::error(ClassId, "Unable to set file types to the dialog instance !");

				return false;
			}

			hr = dialogHandle->SetFileTypeIndex(1);
			if ( FAILED(hr) )
			{
				Tracer::error(ClassId, "Unable to set file type index to the dialog instance !");

				return false;
			}
		}
		else
		{
			const auto fileTypes = createExtensionFilter(m_extensionFilters, dataHolder);

			hr = dialogHandle->SetFileTypes(static_cast< uint32_t >(fileTypes.size()), fileTypes.data());
			if ( FAILED(hr) )
			{
				Tracer::error(ClassId, "Unable to set file types to the dialog instance !");

				return false;
			}

			hr = dialogHandle->SetFileTypeIndex(1);
			if ( FAILED(hr) )
			{
				Tracer::error(ClassId, "Unable to set file type index to the dialog instance !");

				return false;
			}
		}

		/* NOTE: Open the dialog box. */
		hr = dialogHandle->Show(window != nullptr ? window->getWin32Window() : nullptr);
		if ( hr == HRESULT_FROM_WIN32(ERROR_CANCELLED) ) // No item was selected.
		{
			return true;
		}
		else if ( FAILED(hr) )
		{
			Tracer::error(ClassId, "Unable to show the dialog instance !");

			return false;
		}

		/* Get the filepaths selected. */
		{
			IShellItemArray * items = nullptr;
			
			hr = dialogHandle->GetResults(&items);
			if ( FAILED(hr) )
			{
				Tracer::error(ClassId, "Unable to get the items selected !");

				return false;
			}
			
			DWORD filepathCount = 0;
			
			hr = items->GetCount(&filepathCount);
			if ( FAILED(hr) )
			{
				Tracer::error(ClassId, "Unable to get the number of file selected !");

				return false;
			}

			for ( int filepathIndex = 0; filepathIndex < static_cast< int >(filepathCount); ++filepathIndex )
			{
				IShellItem * item = nullptr;

				items->GetItemAt(filepathIndex, &item);
				if ( SUCCEEDED(hr) )
				{
					PWSTR path;

					hr = item->GetDisplayName(SIGDN_FILESYSPATH, &path);
					if ( SUCCEEDED(hr) )
					{
						const std::wstring filepathW{path};

						m_filepaths.emplace_back(convertWideToUTF8(filepathW));

						CoTaskMemFree(path);
					}

					item->Release();
				}
			}

			items->Release();
		}

		return true;
	}
}

#endif
