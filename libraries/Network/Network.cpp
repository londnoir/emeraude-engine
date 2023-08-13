/*
 * Libraries/Network/Network.cpp
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

#include "Network.hpp"

/* C/C++ standard libraries. */
#include <iostream>

/* Third party inclusions. */
#ifdef ASIO_ENABLED
#include "asio/completion_condition.hpp"
#include "asio/io_service.hpp"
#include "asio/read.hpp"
#include "asio/read_until.hpp"
#endif

/* Local inclusions. */
#include "HTTPRequest.hpp"
#include "HTTPResponse.hpp"
#include "String.hpp"
#include "Utility.hpp"
#include "libraries_config.hpp"
#include "platform.hpp"

namespace Libraries::Network
{
	// NOLINTBEGIN(*-magic-numbers)

	bool
	hasInternetConnexion () noexcept
	{
#ifdef ASIO_ENABLED
		asio::io_service ioService{};
		asio::ip::tcp::resolver resolver{ioService};

		/* NOTE: Send a request to the most known service through internet */
		const asio::ip::tcp::resolver::query query{INTERNET_CHECK_DOMAIN, "80"};

		auto endpoints = resolver.resolve(query);

		return !endpoints.empty();
#else
		return false;
#endif
	}

	bool
	download (const URI & uri, const Path::File & filepath, bool verbose) noexcept
	{
#ifdef ASIO_ENABLED
		/* Gets a list of endpoints to reach the resource. */
		const auto endpoints = getEndpointsFromUrl(uri);

		if ( endpoints.empty() )
		{
			return false;
		}

		/* Build a basic GET request. */
		auto GETRequest = getGETHeaderRequest(uri);

		if ( verbose )
		{
			std::cout << "Request :" "\n" << GETRequest << "\n";
		}

		/* Creates the downloading context. */
		asio::io_context context{};

		asio::ip::tcp::socket socket{context};

		for ( const auto & endpoint : endpoints )
		{
			asio::error_code errorCode{};

			/* Connexion */
			socket.connect(endpoint, errorCode); // NOLINT(bugprone-unused-return-value)

			if ( errorCode )
			{
				std::cerr <<
					"Unable to connect to " << endpoint.endpoint().address() << ".\n"
					"Error : " << errorCode.message() << "\n";

				continue;
			}

			if ( verbose )
			{
				std::cout << "Connected to socket : " << endpoint.endpoint().address() << "\n";
			}

			/* Send the GET request. */
			socket.write_some(asio::buffer(GETRequest.data(), GETRequest.size()), errorCode);

			socket.wait(asio::basic_stream_socket< asio::ip::tcp >::wait_read);

			if ( errorCode )
			{
				std::cerr <<
					"Unable send the GET request." "\n"
					"Error : " << errorCode.message() << "\n";

				continue;
			}

			if ( socket.available() == 0 )
			{
				std::cerr << "ZERO bytes to read from the response !" "\n";

				return false;
			}

			/* Read the response. */
			asio::streambuf buffer{};

			auto readBytes = asio::read_until(socket, buffer, HTTPHeaders::HeaderSeparator, errorCode);

			if ( errorCode )
			{
				std::cerr <<
					"Unable to read response header !" "\n"
					"Error : " << errorCode.message() << "\n";

				return false;
			}

			const auto HTTPResponse = extractHeaders(buffer, HTTPHeaders::HeaderSeparator);

			/* Analyse the response type. */
			switch ( HTTPResponse.codeResponse() )
			{
				case 200 :
					/* NOTE: Everything is fine ! */
					if ( verbose )
					{
						std::cout <<
							"Server response :" "\n" <<
							HTTPResponse.toString() << "\n";
					}
					break;

				/* Redirection code. */
				case 301 :
				case 302 :
				case 307 :
				case 308 :
					std::cerr <<
						"Unhandled redirection" "\n"
						"Server response : " "\n" <<
						HTTPResponse.toString() << "\n";

					continue;

				default:
					std::cerr <<
						"Request failed :\n" << GETRequest <<
						"Server response :\n" << HTTPResponse.toString() << "\n";

					return false;
			}

			/* Read the final content. */
			const auto expectedContentBytes = String::toNumber< unsigned int >(HTTPResponse.value(HTTPResponse::ContentLength));

			if ( verbose )
			{
				std::cout << "Expected content size : " << expectedContentBytes << " bytes (" << expectedContentBytes / 1024 << " Kib)" "\n";
			}

			buffer.prepare(expectedContentBytes);

			readBytes += asio::read(socket, buffer, asio::transfer_all(), errorCode);

			if ( errorCode != asio::error::eof )
			{
				std::cerr <<
					"Unable to read response content !" "\n"
					"Error : " << errorCode.message() << "\n";

				return false;
			}

			if ( buffer.size() != expectedContentBytes )
			{
				std::cerr << "Only " << buffer.size() << " bytes read of the expecting " << expectedContentBytes << " bytes !" "\n";

				return false;
			}

			if ( verbose )
			{
				std::cout << readBytes << " total bytes (" << readBytes / 1024 << " Kib) read." "\n";
			}

			if ( !Utility::filePutContents({filepath}, {asio::buffers_begin(buffer.data()), asio::buffers_end(buffer.data())}) )
			{
				std::cerr << "Unable to write data in file '" << filepath << "' !" "\n";

				return false;
			}

			if ( verbose )
			{
				std::cout << "File written in '" << filepath << "' !" "\n";
			}

			return true;
		}

		return false;
#else
		return false;
#endif
	}

#ifdef ASIO_ENABLED
	asio::ip::basic_resolver_results< asio::ip::tcp >
	getEndpointsFromUrl (const URI & uri) noexcept
	{
		asio::io_service ioService{};

		asio::ip::tcp::resolver resolver{ioService};

		const asio::ip::tcp::resolver::query resolverQuery{uri.uriDomain().hostname().name(), uri.scheme()};

		return resolver.resolve(resolverQuery);
	}

	std::string
	getGETHeaderRequest (const URI & uri) noexcept
	{
		HTTPRequest request{HTTPRequest::Method::GET, uri};
		request.add(HTTPRequest::Accept, "*/*");
		request.add(HTTPRequest::AcceptLanguage, "*");
		request.add(HTTPRequest::AcceptEncoding, "gzip, deflate");
		request.add(HTTPRequest::Connection, "close");
		request.add(HTTPRequest::UserAgent, LIBRARIES_NAME "/" LIBRARIES_VERSION_STRING " (" WEB_BROWSER_PLATFORM ")");

		/*
			BASE : User-Agent: Mozilla/5.0 (<system-information>) <platform> (<platform-details>) <extensions>
			Mozilla/5.0 (Windows NT 6.1; Win64; x64; rv:47.0) Gecko/20100101 Firefox/47.0
			Mozilla/5.0 (Macintosh; Intel Mac OS X x.y; rv:42.0) Gecko/20100101 Firefox/42.0
			Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36
			Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.106 Safari/537.36 OPR/38.0.2220.41
			Opera/9.80 (Macintosh; Intel Mac OS X; U; en) Presto/2.2.15 Version/10.00
			Opera/9.60 (Windows NT 6.0; U; en) Presto/2.1.1
			Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36 Edg/91.0.864.59
			Mozilla/5.0 (iPhone; CPU iPhone OS 13_5_1 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Version/13.1.1 Mobile/15E148 Safari/604.1
			Mozilla/5.0 (compatible; Googlebot/2.1; +http://www.google.com/bot.html)
			Mozilla/5.0 (compatible; YandexAccessibilityBot/3.0; +http://yandex.com/bots)
			curl/7.64.1
			PostmanRuntime/7.26.5
		*/

		return request.toString();
	}

	HTTPResponse
	extractHeaders (asio::streambuf & buffer, const std::string & delimiter) noexcept
	{
		const auto rawHeader = std::string{asio::buffers_begin(buffer.data()), asio::buffers_end(buffer.data())};

		const auto offset = rawHeader.find(delimiter);

		if ( offset == std::string::npos )
		{
			return {};
		}

		const auto rawResponseHeaders = rawHeader.substr(0, offset + delimiter.size());

		buffer.consume(rawResponseHeaders.size());

		return HTTPResponse{rawResponseHeaders};
	}
#endif

	// NOLINTEND(*-magic-numbers)
}
