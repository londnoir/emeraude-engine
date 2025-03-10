/*
 * src/PlatformSpecific/Desktop/Dialog/OpenFile.linux.cpp
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

#include "OpenFile.hpp"

#if IS_LINUX

/* Third-party inclusions. */
#include <gtk/gtk.h>

/* Local inclusions. */
#include "Window.hpp"

namespace Emeraude::PlatformSpecific::Desktop::Dialog
{
	bool
	OpenFile::execute (Window * window) noexcept
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

		if ( m_flags[MultiSelect] )
		{
			gtk_file_chooser_set_select_multiple(GTK_FILE_CHOOSER(dialog), TRUE);

			if ( gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT )
			{
				const GSList * files = gtk_file_chooser_get_filenames(GTK_FILE_CHOOSER(dialog));

				for ( const GSList * iterator = files; iterator; iterator = iterator->next )
				{
					m_filepaths.emplace_back(static_cast< char * >(iterator->data));
				}
			}
		}
		else
		{
			if ( gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT )
			{
				const auto * filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

				m_filepaths.emplace_back(filepath);
			}
		}

		gtk_widget_destroy(dialog);

		return true;
	}
}

#endif
