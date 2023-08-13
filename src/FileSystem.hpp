/*
 * Emeraude/FileSystem.hpp
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
#include <sstream>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"

/* Local inclusions for usages. */
#include "Path/Directory.hpp"

namespace Emeraude
{
	/* Forward declarations. */
	class Arguments;

	/**
	 * @brief The file system service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 */
	class FileSystem final : public ServiceInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"FileSystemService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs the file system.
			 * @param arguments An access to the command arguments.
			 * @param applicationName A string for the application name [std::move].
			 */
			FileSystem (const Arguments & arguments, std::string applicationName) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			FileSystem (const FileSystem & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			FileSystem (FileSystem && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			FileSystem & operator= (const FileSystem & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			FileSystem & operator= (FileSystem && copy) noexcept = delete;

			/**
			 * @brief Destructs the file system.
			 */
			~FileSystem () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Returns the home directory of the current user.
			 * @return Directory
			 */
			[[nodiscard]]
			const Libraries::Path::Directory & userDirectory () const noexcept;

			/**
			 * @brief Returns the user data directory for the application of the current user.
			 * @return Directory
			 */
			[[nodiscard]]
			Libraries::Path::Directory userDataDirectory (const std::string & append = {}) const noexcept;

			/**
			 * @brief Returns the parent directory of the binary.
			 * @return Directory
			 */
			[[nodiscard]]
			const Libraries::Path::Directory & binaryDirectory () const noexcept;

			/**
			 * @brief Returns the application binary file name.
			 * @return string
			 */
			[[nodiscard]]
			const std::string & binaryName () const noexcept;

			/**
			 * @brief Returns a list of available config directories for this application.
			 * @return vector< Directory >
			 */
			[[nodiscard]]
			const std::vector< Libraries::Path::Directory > & configDirectoriesList () const noexcept;

			/**
			 * @brief Returns a list of available data directories for this application.
			 * @return vector< Directory >
			 */
			[[nodiscard]]
			const std::vector< Libraries::Path::Directory > & dataDirectoriesList () const noexcept;

			/**
			 * @brief Returns a list of available cache directories for this application.
			 * @return vector< Directory >
			 */
			[[nodiscard]]
			const std::vector< Libraries::Path::Directory > & cacheDirectoriesList () const noexcept;

			/**
			 * @brief Returns the first config directory of this application.
			 * @param append A directory to append at the end of the directory. Default none.
			 * @return Directory
			 */
			[[nodiscard]]
			Libraries::Path::Directory configDirectory (const std::string & append = {}) const noexcept;

			/**
			 * @brief Returns the first data directory of this application.
			 * @param append A directory to append at the end of the directory. Default none.
			 * @return Directory
			 */
			[[nodiscard]]
			Libraries::Path::Directory dataDirectory (const std::string & append = {}) const noexcept;

			/**
			 * @brief Returns the first cache directory of this application.
			 * @param append A directory to append at the end of the directory. Default none.
			 * @return Directory
			 */
			[[nodiscard]]
			Libraries::Path::Directory cacheDirectory (const std::string & append = {}) const noexcept;

			/**
			 * @brief Returns the instance of the file system.
			 * @return FileSystem *
			 */
			[[nodiscard]]
			static
			FileSystem * instance () noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const FileSystem & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const FileSystem & obj) noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/**
			 * @brief Checks the user directory.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkUserDirectory () noexcept;

			/**
			 * @brief Tries to find valid config directories.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkConfigDirectories () noexcept;

			/**
			 * @brief Tries to find valid data directories.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkDataDirectories () noexcept;

			/**
			 * @brief Tries to find valid cache directories.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkCacheDirectories () noexcept;

			/**
			 * @brief Tests and registers selected directories.
			 * @param directoryStrings Directories to test.
			 * @param createLastDirectory If no directory was found, we try create the last one from the list.
			 * @param writableRequested Is directory need to be writable.
			 * @param directories Where to save directory.
			 * @return bool
			 */
			static bool registerDirectories (const std::vector< std::string > & directoryStrings, bool createLastDirectory, bool writableRequested, std::vector< Libraries::Path::Directory > & directories) noexcept;

			static FileSystem * s_instance; // NOLINT NOTE: Singleton behavior

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			std::string m_applicationName;
			Libraries::Path::Directory m_userDirectory{};
			Libraries::Path::Directory m_binaryDirectory{};
			std::string m_binaryName{};
			std::vector< Libraries::Path::Directory > m_configDirectories{};
			std::vector< Libraries::Path::Directory > m_dataDirectories{};
			std::vector< Libraries::Path::Directory > m_cacheDirectories{};
			bool m_usable{false};
	};
}
