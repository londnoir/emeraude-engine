/*
 * src/UserDialogs/OpenFiles.linux.cpp
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

#if IS_LINUX

/* STL inclusions. */
#include <iostream>

/* Third-party inclusions. */
#ifdef GTK3_ENABLED
	#include <gtk/gtk.h>
#endif

/* Local inclusions. */
#include "Window.hpp"

namespace Emeraude::PlatformSpecific::Desktop::Dialog
{
#ifdef GTK3_ENABLED
	bool
	OpenFiles::execute (Window * window) noexcept
	{
		GtkWidget * dialog = gtk_file_chooser_dialog_new(
			this->title().c_str(),
			window ? window->getGtkWindow() : nullptr,
			GTK_FILE_CHOOSER_ACTION_OPEN,
			"Cancel",
			GTK_RESPONSE_CANCEL,
			"Open",
			GTK_RESPONSE_ACCEPT,
			nullptr
		);

		if ( dialog == nullptr )
		{
			return false;
		}

		for ( const auto & [filterName, extensions] : m_extensionFilters )
		{
			GtkFileFilter * filter = gtk_file_filter_new();
			gtk_file_filter_set_name(filter, filterName.c_str());

			for ( const auto & extension : extensions )
			{
				const auto fileType = "*." + extension;

				gtk_file_filter_add_pattern(filter, fileType.c_str());
			}

			gtk_file_chooser_add_filter(reinterpret_cast< GtkFileChooser * >(dialog), filter);
		}

		gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(dialog), TRUE);

		if ( gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT )
		{
			GSList * files = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(dialog));

			for ( const GSList * iterator = files; iterator; iterator = iterator->next )
			{
				m_filePaths.emplace_back(static_cast< char * >(iterator->data));
			}

			g_free(files);
		}

		gtk_widget_destroy(dialog);

		return true;
	}
#else
	bool
	OpenFiles::execute (Window * /*window*/) noexcept
	{
		std::cerr << "Native GUI disabled !" "\n";

		return false;
	}
#endif
}

#endif
