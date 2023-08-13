/*
 * Emeraude/NetworkManager.hpp
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
#include <array>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "ServiceInterface.hpp"
#include "ParallelizableProcess.hpp"

/* Local inclusions for usages. */
#include "CachedDownloadItem.hpp"
#include "DownloadItem.hpp"

namespace Emeraude
{
	class Arguments;
	class FileSystem;
	class Settings;

	/**
	 * @brief The network manager service class.
	 * @extends Emeraude::ServiceInterface This is a service.
	 * @extends Libraries::ParallelizableProcess This needs to parallelize download processes.
	 */
	class NetworkManager final : public ServiceInterface, public Libraries::ParallelizableProcess< size_t >
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"NetworkManagerService"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/** @brief Observable notification codes. */
			enum NotificationCode
			{
				Unknown,
				DownloadingStarted,
				FileDownloaded,
				DownloadingFinished,
				Progress,
				/* Enumeration boundary. */
				MaxEnum
			};

			/**
			 * @brief Constructs the network manager.
			 * @param arguments A reference to Arguments.
			 * @param fileSystem A reference to the file system service.
			 * @param coreSettings A reference to the core settings service.
			 */
			NetworkManager (const Arguments & arguments, const FileSystem & fileSystem, Settings & coreSettings) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::ServiceInterface::usable() */
			[[nodiscard]]
			bool usable () const noexcept override;

			/**
			 * @brief Adds a download request and returns a ticket.
			 * @param url A reference to the item url to download.
			 * @param output A reference to a path to set where to save the file.
			 * @param replaceExistingFile A switch to replace on exists file.
			 * @return int
			 */
			int download (const Libraries::Network::URL & url, const Libraries::Path::File & output, bool replaceExistingFile = true) noexcept;

			/**
			 * @brief Gets the download status using a ticket got from NetworkManager::newDownloadRequest().
			 * @param ticket The download ticket.
			 * @return Status
			 */
			[[nodiscard]]
			DownloadItem::Status downloadStatus (int ticket) const noexcept;

			/**
			 * @brief Returns the total number of files.
			 * @param ticket The download ticket.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t fileCount () const noexcept;

			/**
			 * @brief Returns the total number of files with a filter.
			 * @param filter The status of the file.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t fileCount (DownloadItem::Status filter) const noexcept;

			/**
			 * @brief Returns the total number of files currently in downloading.
			 * @param ticket The download ticket.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t fileRemainingCount () const noexcept;

			/**
			 * @brief totalBytesTotal
			 * @return size_t
			 */
			[[nodiscard]]
			size_t totalBytesTotal () const noexcept;

			/**
			 * @brief totalBytesReceived
			 * @return size_t
			 */
			[[nodiscard]]
			size_t totalBytesReceived () const noexcept;

			/**
			 * @brief Controls download informations output from NetworkManager in console.
			 * @param state The state of the option.
			 * @return void
			 */
			void showProgressionInConsole (bool state) noexcept;

			/**
			 * @brief Returns whether the NetworkManager is printing download informations in console.
			 * @return bool
			 */
			[[nodiscard]]
			bool showProgressionInConsole () const noexcept;

		private:

			/** @copydoc Emeraude::ServiceInterface::onInitialize() */
			bool onInitialize () noexcept override;

			/** @copydoc Emeraude::ServiceInterface::onTerminate() */
			bool onTerminate () noexcept override;

			/** @copydoc Libraries::ParallelizableProcess::task() */
			bool task (const size_t & data) noexcept override;

			/**
			 * @brief Returns the download cache db filepath.
			 * @return Libraries::Path::File
			 */
			[[nodiscard]]
			Libraries::Path::File getDownloadCacheDBFilepath () const noexcept;

			/**
			 * @brief Returns the downloaded item filepath.
			 * @param cacheId The downloaded item ID.
			 * @return Libraries::Path::File
			 */
			[[nodiscard]]
			Libraries::Path::File getDownloadedCacheFilepath (size_t cacheId) const noexcept;

			/**
			 * @brief Updates the download cache db file.
			 * @return bool
			 */
			[[nodiscard]]
			bool updateDownloadCacheDBFile () const noexcept;

			/**
			 * @brief Checks the download cache.
			 * @return bool
			 */
			 [[nodiscard]]
			bool checkDownloadCacheDBFile () noexcept;

			/**
			 * @brief Removes downloaded files from the cache directory.
			 * @return bool
			 */
			bool clearDownloadCache () noexcept;

			/* Flag names. */
			static constexpr auto DownloadEnabled = 0UL;
			static constexpr auto ShowProgression = 1UL;

			static constexpr auto DownloadCacheDirectory = "downloads";
			static constexpr auto DownloadCacheDBFilename = "downloads_db.json";

			static constexpr auto FileDataBaseKey = "FileDataBase";
			static constexpr auto FileURLKey = "FileURL";
			static constexpr auto CacheIdKey = "CacheId";
			static constexpr auto FilenameKey = "Filename";
			static constexpr auto FilesizeKey = "Filesize";

			// NOLINTBEGIN(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			const Arguments & m_arguments;
			const FileSystem & m_fileSystem;
			Settings & m_coreSettings;
			// NOLINTEND(cppcoreguidelines-avoid-const-or-ref-data-members) NOTE: Services inter-connexions.
			Libraries::Path::Directory m_downloadCacheDirectory{};
			std::map< std::string, CachedDownloadItem > m_downloadCache{};
			size_t m_nextCacheItemId{1};
			std::vector< DownloadItem > m_downloadItems{};
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*DownloadEnabled*/,
				false/*ShowProgression*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
