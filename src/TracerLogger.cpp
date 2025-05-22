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

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <fstream>
#include <thread>
#include <utility>

/* Local inclusions. */
#include "Libs/IO/IO.hpp"

namespace EmEn
{
	TracerLogger::TracerLogger (std::filesystem::path filepath, LogFormat logFormat) noexcept
		: m_filepath(std::move(filepath)),
		m_logFormat(logFormat)
	{
		std::fstream file{m_filepath, std::ios::out | std::ios::trunc};

		m_flags[IsUsable] = file.is_open();

		file.close();

		if constexpr ( IsDebug )
		{
			if ( m_flags[IsUsable] )
			{
				std::cout << "TracerLogger::TracerLogger() : Log file " << m_filepath << " opened !" "\n";
			}
			else
			{
				std::cerr << "TracerLogger::TracerLogger() : Unable to open the log file " << m_filepath << " !" "\n";
			}
		}
	}

	void
	TracerLogger::task () noexcept
	{
		if ( !m_flags[IsUsable] )
		{
			return;
		}

		m_flags[IsRunning] = true;

		switch ( m_logFormat )
		{
			case LogFormat::Text :
				this->taskText();
				break;

			case LogFormat::JSON :
				this->taskJSON();
				break;

			case LogFormat::HTML :
				this->taskHTML();
				break;
		}
	}

	void
	TracerLogger::taskText () noexcept
	{
		/* NOTE: Write the file start. */
		{
			std::fstream file{m_filepath, std::ios::out | std::ios::app};

			file << "====== " << EngineName << " " << VersionString << " execution. Beginning at " << std::chrono::steady_clock::now().time_since_epoch().count() << " ======" "\n";

			file.close();
		}

		while ( m_flags[IsRunning] )
		{
			if ( !m_entries.empty() )
			{
				std::fstream file{m_filepath, std::ios::out | std::ios::app};

				while ( !m_entries.empty() )
				{
					const std::lock_guard< std::mutex > lock{m_entriesAccess};

					const auto & entry = m_entries.front();

					file <<
						"[" << entry.time().time_since_epoch().count() << "]"
						"[" << entry.tag() << "]"
						"[" << to_string(entry.severity()) << "]"
						"[" << entry.location().file_name() << ':' << entry.location().line() << ':' << entry.location().column() << " `" << entry.location().function_name() << "`]" "\n"
						<< entry.message() << '\n';

					m_entries.pop();
				}

				file.close();
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		/* NOTE: Write the file end. */
		{
			std::fstream file{m_filepath, std::ios::out | std::ios::app};

			file << "====== Log file closed properly ======" "\n";

			file.close();
		}
	}

	void
	TracerLogger::taskJSON () noexcept
	{
		/* NOTE: Write the file start. */
		{
			std::fstream file{m_filepath, std::ios::out | std::ios::app};

			file << "{" "\n";

			file.close();
		}

		while ( m_flags[IsRunning] )
		{
			if ( !m_entries.empty() )
			{
				std::fstream file{m_filepath, std::ios::out | std::ios::app};

				while ( !m_entries.empty() )
				{
					const std::lock_guard< std::mutex > lock{m_entriesAccess};

					const auto & entry = m_entries.front();

					file <<
						"\t" "{" "\n"
						"\t\t" "\"tag\" : " << entry.tag() << " @ <small><i>" << entry.location().file_name() << ':' << entry.location().line() << ':' << entry.location().column() << " `" << entry.location().function_name() << '`' << "</i></small></h2>" "\n"
						"\t\t" "\"filename\" : " << entry.location().file_name() << ':' << entry.location().line() << ':' << entry.location().column() << " `" << entry.location().function_name() << '`' << "</i></small></h2>" "\n"
						"\t\t" "\"line\" : " <<  entry.location().line() << ':' << entry.location().column() << " `" << entry.location().function_name() << '`' << "</i></small></h2>" "\n"
						"\t\t" "\"column\" :" << entry.location().column() << " `" << entry.location().function_name() << '`' << "</i></small></h2>" "\n"
						"\t\t" "\"function\" : " << entry.location().function_name() << '`' << "</i></small></h2>" "\n"
						"\t\t" "<p class=\"entry-time\">Time: " << entry.time().time_since_epoch().count() << "</p>" "\n"
						"\t\t" "<p class=\"entry-thread\">Thread: " << entry.threadId() << "</p>" "\n"
						"\t\t" "<p class=\"entry-severity\">Severity: " << to_string(entry.severity()) << "<p/>" "\n"
						"\t\t" "<pre class=\"entry-message\">" "\n"
						<< entry.message() << "\n"
						"\t\t" "</pre>" "\n"
						"\t" "}" "\n";

					m_entries.pop();
				}

				file.close();
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		/* NOTE: Write the file end. */
		{
			std::fstream file{m_filepath, std::ios::out | std::ios::app};

			file << "}" "\n";

			file.close();
		}
	}

	void
	TracerLogger::taskHTML () noexcept
	{
		/* NOTE: Write the file start. */
		{
			std::fstream file{m_filepath, std::ios::out | std::ios::app};

			file <<
					"<!DOCTYPE html>" "\n"
					"<html>" "\n"
					"\t" "<head>" "\n"
					"\t\t" "<title>" << EngineName << " " << VersionString << " execution</title>" "\n"
					"\t" "</head>" "\n"
					"\t" "<body>" "\n"

					"\t\t" "<h1>" << EngineName << " " << VersionString << " execution</h1>" "\n"
					"\t\t" "<p>Beginning at " << std::chrono::steady_clock::now().time_since_epoch().count() << "</p>" "\n";

			file.close();
		}

		while ( m_flags[IsRunning] )
		{
			if ( !m_entries.empty() )
			{
				std::fstream file{m_filepath, std::ios::out | std::ios::app};

				while ( !m_entries.empty() )
				{
					const std::lock_guard< std::mutex > lock{m_entriesAccess};

					const auto & entry = m_entries.front();

					file <<
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

				file.close();
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}

		/* NOTE: Write the file end. */
		{
			std::fstream file{m_filepath, std::ios::out | std::ios::app};

			file <<
			   "\t\t" "<p>Ending at " << std::chrono::steady_clock::now().time_since_epoch().count() << "</p>" "\n"
			   "\t" "</body>" "\n"
			   "</html>" "\n";

			file.close();
		}
	}
}
