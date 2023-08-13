/*
 * Emeraude/DownloadItem.hpp
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
#include <string>

/* Local inclusions for usages. */
#include "Network/URL.hpp"
#include "Path/File.hpp"

namespace Emeraude
{
	/**
	 * @brief The DownloadItem class
	 */
	class DownloadItem final
	{
		public:

			enum class Status
			{
				Pending,
				Transferring,
				OnHold,
				Error,
				Done
			};

			/**
			 * @brief Constructs an item to download.
			 * @param url The download URL [std::move].
			 * @param output The output file path [std::move].
			 * @param replaceExistingFile Erase file on exists if true.
			 */
			DownloadItem (Libraries::Network::URL url, Libraries::Path::File output, bool replaceExistingFile = true) noexcept;

			/**
			 * @brief setStatus
			 * @param status
			 */
			void setStatus (Status status) noexcept;

			/**
			 * @brief setProgression
			 * @param total
			 * @param received
			 */
			void setProgression (size_t total, size_t received) noexcept;

			/**
			 * @brief url
			 * @return const Libraries::Network::URL &
			 */
			[[nodiscard]]
			const Libraries::Network::URL & url () const noexcept;

			/**
			 * @brief output
			 * @return const Libraries::Path::File &
			 */
			[[nodiscard]]
			const Libraries::Path::File & output () const noexcept;

			/**
			 * @brief header
			 * @return std::string &
			 */
			std::string & header () noexcept;

			/**
			 * @brief bytesTotal
			 * @return size_t
			 */
			[[nodiscard]]
			size_t bytesTotal () const noexcept;

			/**
			 * @brief bytesReceived
			 * @return size_t
			 */
			[[nodiscard]]
			size_t bytesReceived () const noexcept;

			/**
			 * @brief status
			 * @return Status
			 */
			[[nodiscard]]
			Status status () const noexcept;

			/**
			 * @brief replaceExistingFile
			 * @return bool
			 */
			[[nodiscard]]
			bool replaceExistingFile () const noexcept;

		private:

			Libraries::Network::URL m_url;
			Libraries::Path::File m_output;
			std::string m_header{};
			size_t m_bytesTotal{0};
			size_t m_bytesReceived{0};
			Status m_status{Status::Pending};
			bool m_replaceExistingFile;
	};
}
