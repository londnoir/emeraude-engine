/*
 * Emeraude/Help.hpp
 * This file is part of Emeraude
 *
 * Copyright (C) 2012-2023 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude
 * 
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* C/C++ standard libraries. */
#include <ostream>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "ArgumentDoc.hpp"
#include "ShortcutDoc.hpp"

namespace Emeraude
{
	/**
	 * @brief The help service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class Help final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"HelpService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs the Help service.
			 * @param serviceInstanceName The name of the service to differentiate the help.
			 */
			explicit Help (const char * serviceInstanceName = ClassId) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Adds a new argument to the help.
			 * @param argumentDoc A reference to a ArgumentDoc instance.
			 * @return void
			 */
			void registerArgument (const ArgumentDoc & argumentDoc) noexcept;

			/**
			 * @brief Adds a new argument to the help.
			 * @param description A reference to a string.
			 * @param longName A reference to as string for the long name.
			 * @param shortName A char for the short name. Default none.
			 * @param options A reference to a string vector as options for the argument. Default none.
			 * @return void
			 */
			void registerArgument (const std::string & description, const std::string & longName, char shortName = 0, const std::vector< std::string > & options = {}) noexcept;

			/**
			 * @brief Adds a new shortcut to the help.
			 * @param shortcutDoc A reference to a ShortcutDoc instance.
			 * @return void
			 */
			void registerShortcut (const ShortcutDoc & shortcutDoc) noexcept;

			/**
			 * @brief Adds a new shortcut to the help.
			 * @param description A reference to a string.
			 * @param key The main key for the shortcut.
			 * @param modifiers The additional modifiers. Default none.
			 * @return void
			 */
			void registerShortcut (const std::string & description, Emeraude::Input::Key key, int modifiers = 0) noexcept;

			/**
			 * @brief Returns the argument documentation list.
			 * @return const std::vector< ArgumentDoc > &
			 */
			[[nodiscard]]
			const std::vector< ArgumentDoc > & argumentDocs () const noexcept;

			/**
			 * @brief Returns the shortcut documentation list.
			 * @return const std::vector< ShortcutDoc > &
			 */
			[[nodiscard]]
			const std::vector< ShortcutDoc > & shortcutDocs () const noexcept;

			/**
			 * @brief Returns the argument documentation as a string.
			 * @return const std::vector< ArgumentDoc > &
			 */
			[[nodiscard]]
			std::string argumentDocsString () const noexcept;

			/**
			 * @brief Returns the shortcut documentation as a string.
			 * @return const std::vector< ShortcutDoc > &
			 */
			[[nodiscard]]
			std::string shortcutDocsString () const noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			std::vector< ArgumentDoc > m_argumentDocs{};
			std::vector< ShortcutDoc > m_shortcutDocs{};
	};
}
