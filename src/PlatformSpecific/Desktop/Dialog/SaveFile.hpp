#pragma once

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <utility>
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
	class SaveFile final : public Abstract
	{
		public:

			static constexpr auto ClassId{"SaveFile"};

			/** 
			 * @brief Constructs a file box.
			 * @param title A reference to a string.
			 */
			explicit SaveFile (const std::string & title);

			/** @copydoc Emeraude::PlatformSpecific::Desktop::Dialog::Abstract::execute() */
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
			 * @brief Returns the selected file.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string &
			filepath () const
			{
				return m_filepath;
			}

			/**
			 * @brief Helper function to create a file box to choose file(s) [Shortcut].
			 * @param title Title of the opened modal.
			 * @param filters vector of the names of the filters paired to the associated file extension.
			 * @param window (optional) Handler of the parent window, if left out or nullptr the created window will be orphaned
			 * @return std::string
			 */
			[[nodiscard]]
			static
			std::string
			create (const std::string & title, const std::vector< std::pair< std::string, std::vector< std::string > > > & filters, Window * window = nullptr)
			{
				SaveFile dialog{title};
				dialog.setExtensionFilters(filters);
				dialog.execute(window);

				return dialog.filepath();
			}

			/**
			 * @brief Helper function to create a file box to choose file(s), with just one filter name [Shortcut].
			 * @param title Title of the opened modal.
			 * @param filterName Name of the filter.
			 * @param extensions Vector of the selectable extensions.
			 * @param window (optional) Handler of the parent window, if left out or nullptr the created window will be orphaned
			 * @return std::string
			 */
			[[nodiscard]]
			static
			std::string
			create (const std::string & title, const std::string & filterName, const std::vector< std::string > & extensions, Window * window = nullptr)
			{
				SaveFile dialog{title};
				dialog.setExtensionFilters(filterName, extensions);
				dialog.execute(window);

				return dialog.filepath();
			}

		private:

			std::vector< std::pair< std::string, std::vector< std::string > > > m_extensionFilters{}; //Maybe change to std::map
			std::string m_filepath;
			std::string m_defaultFilename{"untitled"};
	};
}
