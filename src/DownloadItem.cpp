/*
 * src/DownloadItem.cpp
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

#include "DownloadItem.hpp"

/* Local inclusions. */
#include "Tracer.hpp"

namespace Emeraude
{
	using namespace Libraries;

	DownloadItem::DownloadItem (Network::URL url, std::filesystem::path output, bool replaceExistingFile) noexcept
		: m_url(std::move(url)), m_output(std::move(output)), m_replaceExistingFile(replaceExistingFile)
	{

	}

	void
	DownloadItem::setStatus (Status status) noexcept
	{
		switch ( status )
		{
			case Status::Pending :
				Tracer::error(ClassId, "Cannot reset a download process to 'Pending' status, use 'OnHold' instead !");
				break;

			case Status::Transferring :
			case Status::OnHold :
			case Status::Error :
			case Status::Done :
				m_status = status;
				break;
		}
	}

	void
	DownloadItem::setProgression (size_t total, size_t received) noexcept
	{
		m_bytesTotal = total;
		m_bytesReceived = received;

		if ( m_bytesReceived >= m_bytesTotal )
		{
			m_status = Status::Done;
		}
	}
}
