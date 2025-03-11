/*
 * src/TracerLogger.cpp
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

#include "TracerLogger.hpp"

/* STL inclusions. */
#include <fstream>
#include <thread>
#include <utility>

namespace EmEn
{
	TracerLogger::TracerLogger (std::string filepath) noexcept
	 : m_filepath(std::move(filepath))
	{

	}

	void
	TracerLogger::task () noexcept
	{
		std::ofstream log{m_filepath, std::ios_base::trunc};

		if ( !log.is_open() )
		{
			std::cerr << "TracerLogger::task() : Unable to open log file !" "\n";

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
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

			/* Clean up the entries queue. */
			while ( !m_entries.empty() )
			{
				/* NOTE : Lock between the writing logs task in a file and the push/pop method. */
				const std::lock_guard< std::mutex > lockGuard{m_entriesAccessMutex};

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
