/*
 * src/PlatformSpecific/Desktop/Dialog/Message.linux.cpp
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

#include "Message.hpp"

#if IS_LINUX

/* Third-party inclusions. */
#ifdef GTK3_ENABLED
	#include <gtk/gtk.h>
#endif

/* Local inclusions. */
#include "Window.hpp"

namespace EmEn::PlatformSpecific::Desktop::Dialog
{
#ifdef GTK3_ENABLED
	GtkMessageType
	getMessageType (MessageType messageType) noexcept
	{
		switch ( messageType )
		{
			case MessageType::Info:
				return GTK_MESSAGE_INFO;

			case MessageType::Warning:
				return GTK_MESSAGE_WARNING;

			case MessageType::Error:
				return GTK_MESSAGE_ERROR;

			case MessageType::Question:
				return GTK_MESSAGE_QUESTION;

			default:
				return GTK_MESSAGE_OTHER;
		}
	}

	GtkButtonsType
	getButtonLayout (ButtonLayout buttonLayout) noexcept
	{
		switch ( buttonLayout )
		{
			case ButtonLayout::OK :
				return GTK_BUTTONS_OK;

			case ButtonLayout::OKCancel :
				return GTK_BUTTONS_OK_CANCEL;

			case ButtonLayout::YesNo :
				return GTK_BUTTONS_YES_NO;

			case ButtonLayout::Quit :
				return GTK_BUTTONS_CLOSE;

			case ButtonLayout::NoButton :
				return GTK_BUTTONS_NONE;

			default:
				return GTK_BUTTONS_OK;
		}
	}

	bool
	Message::execute (Window * window) noexcept
	{
		GtkWidget * dialog = gtk_message_dialog_new(
			window ? window->getGtkWindow() : nullptr,
			GTK_DIALOG_MODAL,
			getMessageType(m_messageType),
			getButtonLayout(m_buttonLayout),
			"%s",
			m_message.data()
		);

		if ( dialog == nullptr )
		{
			return false;
		}

		gtk_window_set_title(GTK_WINDOW(dialog), this->title().data());

		switch ( gtk_dialog_run(GTK_DIALOG(dialog)) )
		{
			case GTK_RESPONSE_OK:
				m_userAnswer = Answer::OK;
				break;

			case GTK_RESPONSE_CANCEL:
				m_userAnswer = Answer::Cancel;
				break;

				case GTK_RESPONSE_YES:
				m_userAnswer = Answer::Yes;
				break;

			case GTK_RESPONSE_NO:
				m_userAnswer = Answer::No;
				break;

			default:
				break;
		}

		gtk_widget_destroy(GTK_WIDGET(dialog));

		return true;
	}
#else
	bool
	Message::execute (Window * /*window*/) noexcept
	{
		std::cerr << "Native GUI disabled !" "\n";

		return false;
	}
#endif
}

#endif
