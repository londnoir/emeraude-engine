/*
 * Emeraude/TracerLogger.cpp
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

#include "TracerLogger.hpp"

/* C/C++ standard libraries. */
#include <fstream>
#include <iostream>

/* Local inclusions. */
#include "Types.hpp"
#include "emeraude_config.hpp"

namespace Emeraude
{
	TracerLogger::TracerLogger (std::string filepath) noexcept
	 : m_filepath(std::move(filepath))
	{

	}

	bool
	TracerLogger::usable () const noexcept
	{
		/* FIXME: Empty function */
		return true;
	}

	void
	TracerLogger::push (Severity severity, const char * tag, const std::string & message, const std_glue::source_location & location) noexcept
	{
		const std::lock_guard< std::mutex > lock{m_mutex};

		m_entries.emplace(severity, tag, message, location, std::this_thread::get_id());
	}

	void
	TracerLogger::stop () noexcept
	{
		m_isRunning = false;

		if ( !m_entries.empty() )
		{
			std::cout << __PRETTY_FUNCTION__ << ", still " << m_entries.size() << " entries to write down in the log file !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
		}
	}

	void
	TracerLogger::clear () noexcept
	{
		const std::lock_guard< std::mutex > lock{m_mutex};

		while ( !m_entries.empty() )
		{
			m_entries.pop();
		}
	}

	void
	TracerLogger::task () noexcept
	{
		std::ofstream log{m_filepath, std::ios_base::trunc};

		if ( !log.is_open() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to open log file !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return;
		}

		log <<
			   "<!DOCTYPE html>" "\n"
			   "<html>" "\n"
			   "\t" "<head>" "\n"
			   "\t\t" "<title>" ENGINE_NAME " " ENGINE_VERSION_STRING " execution</title>" "\n"
			   "\t" "</head>" "\n"
			   "\t" "<body>" "\n"

			   "\t\t" "<h1>" ENGINE_NAME " " ENGINE_VERSION_STRING " execution</h1>" "\n"
			   "\t\t" "<p>Beginning at " << std::chrono::steady_clock::now().time_since_epoch().count() << "</p>" "\n";

		while ( m_isRunning )
		{
			/* NOTE: Calm down this low priority process. We will write down logs every 100ms. */
			std::this_thread::sleep_for(std::chrono::milliseconds(100)); // NOLINT(*-magic-numbers)

			/* Clean up the entries queue. */
			while ( !m_entries.empty() )
			{
				const std::lock_guard< std::mutex > lock{m_mutex};

				const auto & entry = m_entries.front();

				log <<
					"\t\t" "<div>" "\n"
					"\t\t\t" "<h2 class=\"entry-tag\">" << entry.tag() << " @ <small><i>" << entry.location().file_name() << ':' << entry.location().line() << ':' << entry.location().column() << " `" << entry.location().function_name() << '`' << "</i></small></h2>" "\n"
					"\t\t\t" "<p class=\"entry-time\">Time: " << entry.time().time_since_epoch().count() << "</p>" "\n"
					"\t\t\t" "<p class=\"entry-thread\">Thread: " << entry.threadId() << "</p>" "\n"
					"\t\t\t" "<p class=\"entry-severity\">Severity: " << to_string(entry.severity()) << "<p/>" "\n"
					"\t\t\t" "<pre class=\"entry-message\">" "\n"
					<< entry.message() << "\n"
					"\t\t\t" "</pre>" "\n"
					"\t\t" "</div>" "\n";

				m_entries.pop();
			}
		}

		log <<
			   "\t\t" "<p>Ending at " << std::chrono::steady_clock::now().time_since_epoch().count() << "</p>" "\n"
			   "\t" "</body>" "\n"
			   "</html>" "\n";
	}
}
