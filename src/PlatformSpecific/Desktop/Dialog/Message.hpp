/*
 * src/UserDialogs/Message.hpp
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

#pragma once

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <string>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

/* Local inclusions for usages. */
#include "Types.hpp"

namespace Emeraude::PlatformSpecific::Desktop::Dialog
{
	/**
	 * @brief The user dialog message class.
	 * @extends Emeraude::PlatformSpecific::Desktop::Dialog::Abstract This is an user dialog box.
	 */
	class Message final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Message"};

			/** 
			 * @brief Constructs a message dialog.
			 * @param title A reference to a string for the dialog title.
			 * @param message A string for the message content to display [std::move].
			 * @param buttonLayout The buttons layout type. Default "OK".
			 * @param messageType The type of message. Default "Info".
			 */
			Message (const std::string & title, std::string message, ButtonLayout buttonLayout = ButtonLayout::OK, MessageType messageType = MessageType::Info) noexcept;

			/** @copydoc Emeraude::PlatformSpecific::Desktop::Dialog::Abstract::execute() */
			bool execute (Window * window) noexcept override;

			/**
			 * @brief Returns the user answer.
			 * @return Answer
			 */
			[[nodiscard]]
			Answer getUserAnswer () const noexcept;

			/**
			 * @brief Creates and opens a message window [Shortcut].
			 * @param title A reference to a string.
			 * @param message A reference to a string.
			 * @param buttonLayout The button layout. Default "ok".
			 * @param messageType The message type. Default "info".
			 * @param window A pointer to the main window for parenting. Default no parent.
			 * @return Answer
			 */
			static
			Answer
			create (const std::string & title, const std::string & message, ButtonLayout buttonLayout = ButtonLayout::OK, MessageType messageType = MessageType::Info, Window * window = nullptr)
			{
				Message dialog{title, message, buttonLayout, messageType};
				dialog.execute(window);
				return dialog.getUserAnswer();
			}

			/**
			 * @brief Creates and opens a confirmation window [Shortcut].
			 * @param title A reference to a string.
			 * @param message A reference to a string.
			 * @param window A pointer to the main window for parenting. Default no parent.
			 * @return Answer
			 */
			static
			Answer
			createConfirmation (const std::string & title, const std::string & message, Window * window = nullptr)
			{
				Message dialog{title, message, ButtonLayout::YesNo, MessageType::Question};
				dialog.execute(window);
				return dialog.getUserAnswer();
			}

		private:

			std::string m_message;
			ButtonLayout m_buttonLayout;
			MessageType m_messageType;
			Answer m_userAnswer{Answer::None};
	};
}
