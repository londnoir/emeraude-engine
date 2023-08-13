/*
 * Emeraude/Resources/LoadingRequest.hpp
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
#include <utility>

/* Local inclusions for usages. */
#include "Tracer.hpp"
#include "BaseInformation.hpp"
#include "FileSystem.hpp"
#include "Network/URL.hpp"
#include "ResourceTrait.hpp"

namespace Emeraude::Resources
{
	/**
	 * @brief The resource loading request within the manager.
	 * @tparam resource_t The final resource type.
	 */
	template< typename resource_t, std::enable_if_t< std::is_base_of_v< ResourceTrait, resource_t >, bool > = false >
	class LoadingRequest final
	{
		public:

			/**
			 * @brief Constructs a loading request.
			 * @param baseInformation A reference to the base information of the resource [std::move].
			 * @param resource A reference to the final resource smart pointer.
			 */
			LoadingRequest (BaseInformation baseInformation, const std::shared_ptr< resource_t > & resource) noexcept
				: m_baseInformation(std::move(baseInformation)), m_resource(resource)
			{
				using namespace Libraries;

				switch ( m_baseInformation.sourceType() )
				{
					case SourceType::Undefined :
						Tracer::error("LoadingRequest", "Undefined type for resource request !");
						break;

					case SourceType::LocalData :
						break;

					case SourceType::ExternalData :
					{
						Network::URL resourceUrl{m_baseInformation.data().asString()};

						if ( resourceUrl.isValid() )
						{
							m_downloadTicket = DownloadPending;
						}
						else
						{
							TraceError{"LoadingRequest"} << "'" << resourceUrl << "' is not a valid URL ! Download cancelled ...";

							m_downloadTicket = DownloadError;
						}
					}
						break;

					case SourceType::DirectData :
						break;
				}
			}

			/**
			 * @brief Returns the cache file path.
			 * @param fileSystem A reference to the file system.
			 * @return Libraries::Path::File
			 */
			[[nodiscard]]
			Libraries::Path::File
			cacheFilepath (const FileSystem & fileSystem) const noexcept
			{
				return {
					fileSystem.cacheDirectory("data").append(resource_t::ClassId),
					Libraries::String::extractFilename(m_baseInformation.data().asString())
				};
			}

			/**
			 * @brief Returns the information of the request.
			 * @return const BaseInformation &
			 */
			[[nodiscard]]
			const BaseInformation &
			baseInformation () const noexcept
			{
				return m_baseInformation;
			}

			/**
			 * @brief Returns the resource smart pointer.
			 * @return std::shared_ptr< resource_t >
			 */
			[[nodiscard]]
			std::shared_ptr< resource_t >
			resource () const noexcept
			{
				return m_resource;
			}

			/**
			 * @brief Returns the download ticket.
			 * @note 0 means there is no download for this request.
			 * @return int
			 */
			[[nodiscard]]
			int
			downloadTicket () const noexcept
			{
				if ( m_downloadTicket < 0 )
				{
					return 0;
				}

				return m_downloadTicket;
			}

			/**
			 * @brief Returns whether the request is downloadable
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isDownloadable () const noexcept
			{
				if ( m_baseInformation.sourceType() != SourceType::ExternalData )
				{
					Tracer::error("LoadingRequest", "This request is not external !");

					return false;
				}

				return m_downloadTicket == DownloadPending;
			}

			/**
			 * @brief Returns whether the request download url.
			 * @return Libraries::Network::URL
			 */
			[[nodiscard]]
			Libraries::Network::URL
			url () const noexcept
			{
				if ( m_baseInformation.sourceType() != SourceType::ExternalData )
				{
					return {};
				}

				return Libraries::Network::URL{m_baseInformation.data().asString()};
			}

			/**
			 * @brief Returns the downloading status of the request.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isDownloading () const noexcept
			{
				if ( m_baseInformation.sourceType() != SourceType::ExternalData )
				{
					Tracer::error("LoadingRequest", "This request is not external !");

					return false;
				}

				/* NOTE: Check the networkManager ticket.
				 * If it's still present, the download
				 * is not yet finished. */
				if ( m_downloadTicket >= 0 )
				{
					return false;
				}

				return true;
			}

			/**
			 * @brief Sets the download ticket to the request.
			 * @note The request must have the 'DownloadPending' status.
			 * @param ticket The ticket number from the download manager.
			 */
			void
			setDownloadTicket (int ticket) noexcept
			{
				if ( m_baseInformation.sourceType() != SourceType::ExternalData )
				{
					Tracer::error("LoadingRequest", "This request is not external !");

					return;
				}

				if ( m_downloadTicket != DownloadPending )
				{
					Tracer::error("LoadingRequest", "Cannot set a ticket to a request which is not in 'DownloadPending' status !");

					return;
				}

				m_downloadTicket = ticket;
			}

			/**
			 * @brief Sets the download finish status. Downloaded of failed.
			 * @param fileSystem A reference to the file system to use cache.
			 * @param success Whether the download succeed or not.
			 */
			void
			setDownloadProcessed (const FileSystem & fileSystem, bool success) noexcept
			{
				if ( m_baseInformation.sourceType() != SourceType::ExternalData )
				{
					Tracer::error("LoadingRequest", "This request is not external !");

					return;
				}

				/* Invalidate the networkManager ticket. */
				if ( success )
				{
					m_downloadTicket = DownloadSuccess;

					m_baseInformation.updateFromDownload(this->cacheFilepath(fileSystem));
				}
				else
				{
					m_downloadTicket = DownloadError;
				}
			}

		private:

			/* Special ticket flags. */
			static constexpr auto DownloadNotRequested = -4;
			static constexpr auto DownloadError = -3;
			static constexpr auto DownloadSuccess = -2;
			static constexpr auto DownloadPending = -1;

			BaseInformation m_baseInformation;
			std::shared_ptr< resource_t > m_resource;
			int m_downloadTicket = DownloadNotRequested;
	};
}
