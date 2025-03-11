/*
 * src/PlatformSpecific/Desktop/Dialog/OpenFile.hpp
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

#pragma once

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <utility>
#include <vector>
#include <string>
#include <array>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

namespace EmEn::PlatformSpecific::Desktop::Dialog
{
	/**
	 * @brief User dialog to select multiple files.
	 * @extends EmEn::PlatformSpecific::Desktop::Dialog::Abstract
	 */
	class OpenFile final : public Abstract
	{
		public:

			static constexpr auto ClassId{"OpenFile"};

			/** 
			 * @brief Constructs a file box.
			 * @param title A reference to a string.
			 * @param selectFolder Select folders instead of files. Default false.
			 * @param multiSelect Allow multiple selection. Default false.
			 */
			explicit OpenFile (const std::string & title, bool selectFolder = false, bool multiSelect = false);

			/** @copydoc EmEn::PlatformSpecific::Desktop::Dialog::Abstract::execute() */
			bool execute (Window * window) noexcept override;

			/**
			 * @brief Sets file extensions filters.
			 * @param filters A reference to a vector.
			 * @return void
			 */
			void
			setExtensionFilters (const std::vector< std::pair< std::string, std::vector< std::string > > > & filters)
			{
				m_extensionFilters = filters;
			}

			/**
			 * @brief Sets file extensions filters.
			 * @param filterName A reference to a string.
			 * @param extensions A reference to a vector.
			 * @return void
			 */
			void
			setExtensionFilters (const std::string & filterName, const std::vector< std::string > & extensions)
			{
				m_extensionFilters.emplace_back(filterName, extensions);
			}

			/**
			 * @brief Returns the selected files.
			 * @return const std::vector< std::string > &
			 */
			[[nodiscard]]
			const std::vector< std::pair< std::string, std::vector< std::string > > > &
			extensionFilters () const
			{
				return m_extensionFilters;
			}

			/**
			 * @brief Returns the selected files.
			 * @return const std::vector< std::string > &
			 */
			[[nodiscard]]
			const std::vector< std::string > &
			filepaths () const
			{
				return m_filepaths;
			}

			/**
			 * @brief Helper function to create a file box to choose file(s) [Shortcut].
			 * @param title Title of the opened modal.
			 * @param filters vector of the names of the filters paired to the associated file extension.
			 * @param selectFolder Enable folder selection instead of files. Default false.
			 * @param multiSelect Enable multi selection. Default false.
			 * @param window (optional) Handler of the parent window, if left out or nullptr the created window will be orphaned
			 * @return std::vector< std::string >
			 */
			[[nodiscard]]
			static
			std::vector< std::string >
			create (const std::string & title, const std::vector< std::pair< std::string, std::vector< std::string > > > & filters, bool selectFolder = false, bool multiSelect = false, Window * window = nullptr)
			{
				OpenFile dialog{title, selectFolder, multiSelect};
				dialog.setExtensionFilters(filters);
				dialog.execute(window);

				return dialog.filepaths();
			}

			/**
			 * @brief Helper function to create a file box to choose file(s), with just one filter name [Shortcut].
			 * @param title Title of the opened modal.
			 * @param filterName Name of the filter.
			 * @param extensions Vector of the selectable extensions.
			 * @param window (optional) Handler of the parent window, if left out or nullptr the created window will be orphaned
			 * @return std::vector< std::string >
			 */
			[[nodiscard]]
			static
			std::vector< std::string >
			create (const std::string & title, const std::string & filterName, const std::vector< std::string > & extensions, Window * window = nullptr)
			{
				OpenFile dialog{title};
				dialog.setExtensionFilters(filterName, extensions);
				dialog.execute(window);

				return dialog.filepaths();
			}

		private:

			static constexpr auto SelectFolder{0UL};
			static constexpr auto MultiSelect{1UL};

			std::vector< std::pair< std::string, std::vector< std::string > > > m_extensionFilters; //Maybe change to std::map
			std::vector< std::string > m_filepaths;
			std::array< bool, 8 > m_flags{
				false/*SelectFolder*/,
				false/*MultiSelect*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
