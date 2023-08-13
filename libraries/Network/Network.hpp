/*
 * Libraries/Network/Network.hpp
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

/* Local inclusions for usages. */
#include "Path/File.hpp"
#include "URI.hpp"

/* Third party inclusions. */
#include "Third-Party-Inclusion/asio.hpp"

namespace Libraries::Network
{
	class HTTPResponse;

	/**
	 * @brief Checks whether a connexion is available.
	 * @return bool
	 */
	[[nodiscard]]
	bool hasInternetConnexion () noexcept;

	/**
	 * @brief Downloads a file from an URI.
	 * @param uri A reference to an URI.
	 * @param filepath A reference to a file path.
	 * @param verbose Show transaction informations.
	 * @return bool
	 */
	bool download (const URI & uri, const Path::File & filepath, bool verbose = false) noexcept;

#ifdef ASIO_ENABLED
	/**
	 * @brief Gets a list of endpoints from an URL.
	 * @param uri A reference to an URI.
	 * @return basic_resolver_results< tcp >
	 */
	[[nodiscard]]
	asio::ip::basic_resolver_results< asio::ip::tcp > getEndpointsFromUrl (const URI & uri) noexcept;

	/**
	 * @brief Creates a GET request header in the string format from an URI.
	 * @param uri A reference to an URI.
	 * @return string
	 */
	[[nodiscard]]
	std::string getGETHeaderRequest (const URI & uri) noexcept;

	/**
	 * @brief extractHeaders
	 * @param buffer
	 * @param delimiter
	 * @return HTTPResponse
	 */
	[[nodiscard]]
	HTTPResponse extractHeaders (asio::streambuf & buffer, const std::string & delimiter) noexcept;
#endif
}
