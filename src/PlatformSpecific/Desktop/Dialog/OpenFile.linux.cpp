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
