/*
 * src/ShortcutDoc.hpp
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

/* STL inclusions. */
#include <ostream>
#include <string>

/* Local inclusions for inheritances. */
#include "AbstractDoc.hpp"

/* Local inclusions for usages. */
#include "Input/Types.hpp"

namespace Emeraude
{
	/**
 	 * @brief Class for shortcut documentation.
	 * @extends Emeraude::AbstractDoc The base documentation class.
	 */
	class ShortcutDoc final : public AbstractDoc
	{
		public:

			/**
			 * @brief Constructs a shortcut documentation.
			 * @param description A reference to a string.
			 * @param key The main key for the shortcut.
			 * @param modifiers The additional modifiers. Default none.
			 */
			ShortcutDoc (const std::string & description, Input::Key key, int modifiers = 0) noexcept;

			/**
			 * @brief Returns the main key of the shortcut.
			 * @return Emeraude::Input::Key
			 */
			[[nodiscard]]
			Input::Key
			key () const noexcept
			{
				return m_key;
			}

			/**
			 * @brief Returns the mask of modifier for shortcut.
			 * @note 0 means no modifier needed.
			 * @return int
			 */
			[[nodiscard]]
			int
			modifiers () const noexcept
			{
				return m_modifiers;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const ShortcutDoc & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const ShortcutDoc & obj) noexcept;

		private:

			Input::Key m_key;
			int m_modifiers;
	};
}
