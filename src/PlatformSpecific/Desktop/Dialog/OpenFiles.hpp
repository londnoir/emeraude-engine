/*
 * src/UserDialogs/OpenFiles.hpp
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
#include <map>
#include <vector>
#include <string>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

namespace Emeraude::PlatformSpecific::Desktop::Dialog
{
	/**
	 * @brief The file box class.
	 * @extends Emeraude::PlatformSpecific::Desktop::Dialog::Abstract
	 */
	class OpenFiles final : public Abstract
	{
		public:

			static constexpr auto ClassId{"OpenFiles"};

			/** 
			 * @brief Constructs an open files dialog.
			 * @param title A reference to a string.
			 */
			explicit OpenFiles (const std::string & title);

			/** @copydoc Emeraude::PlatformSpecific::Desktop::Dialog::Abstract::execute() */
			bool execute (Window * window) noexcept override;

			/**
			 * @brief Sets multiple file extensions filters.
			 * @param extensionFilters A reference to a dictionary of file extensions.
			 * @return void
			 */
			void setExtensionFilters (const std::map< std::string, std::vector< std::string > > & extensionFilters);

			/**
			 * @brief Adds a single file extensions filter.
			 * @param filterName A reference to a string.
			 * @param extensionFilter A reference to a vector of extension.
			 * @return void
			 */
			void addExtensionFilter (const std::string & filterName, const std::vector< std::string > & extensionFilter);

			/**
			 * @brief Returns the extensions filters.
			 * @return const std::map< std::string, std::vector< std::string > > &
			 */
			[[nodiscard]]
			const std::map< std::string, std::vector< std::string > > & getExtensionFilters () const;

			/**
			 * @brief Returns the selected files.
			 * @return const std::vector< std::string > &
			 */
			[[nodiscard]]
			const std::vector< std::string > & getFilePaths () const;

			/**
			 * @brief Creates and opens an open files window [Shortcut].
			 * @param title A reference to a string.
			 * @param extensionFilters A reference to a dictionary of file extensions. Default none.
			 * @param window A pointer to the main window for parenting. Default no parent.
			 * @return std::vector< std::string >
			 */
			static
			std::vector< std::string >
			create (const std::string & title, const std::map< std::string, std::vector< std::string > > & extensionFilters = {}, Window * window = nullptr)
			{
				OpenFiles dialog{title};
				dialog.setExtensionFilters(extensionFilters);
				dialog.execute(window);

				return dialog.getFilePaths();
			}

		private:

			std::map< std::string, std::vector< std::string > > m_extensionFilters{};
			std::vector< std::string > m_filePaths{};
	};
}
