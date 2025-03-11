/*
 * src/TracerLogger.hpp
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

#pragma once

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <mutex>
#include <queue>
#include <string>
#include <iostream>

/* Local inclusions for usages. */
#include "TracerEntry.hpp"
#include "Types.hpp"

namespace EmEn
{
	/**
	 * @brief The tracer logger class.
	 */
	class TracerLogger final
	{
		public:

			/**
			 * @brief Constructs the trace logger.
			 * @param filepath The path of the log file [std::move].
			 */
			explicit TracerLogger (std::string filepath) noexcept;

			/**
			 * @brief Returns whether the logger can write to the log file.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			usable () const noexcept
			{
				return !m_filepath.empty();
			}

			/**
			 * @brief Creates a log.
			 * @param severity The type of log.
			 * @param tag A pointer to a C-string to describe a tag. This help for sorting logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location.
			 * @return void
			 */
			void
			push (Severity severity, const char * tag, const std::string & message, const std::source_location & location) noexcept
			{
				/* NOTE : Lock between the writing logs task in a file and the push/pop method. */
				const std::lock_guard< std::mutex > lockGuard{m_entriesAccessMutex};

				m_entries.emplace(severity, tag, message, location, std::this_thread::get_id());
			}

			/**
			 * @brief Stops nicely the writing task for shutting down the tracer service.
			 * @return void
			 */
			void stop () noexcept
			{
				m_isRunning = false;

				if ( !m_entries.empty() )
				{
					std::cout << "TracerLogger::stop() : Still " << m_entries.size() << " entries to write down in the log file !" "\n";
				}
			}

			/**
			 * @brief Clears pending entries.
			 * @return void
			 */
			void
			clear () noexcept
			{
				/* NOTE : Lock between the writing logs task in a file and the push/pop method. */
				const std::lock_guard< std::mutex > lockGuard{m_entriesAccessMutex};

				while ( !m_entries.empty() )
				{
					m_entries.pop();
				}
			}

			/**
			 * @brief Runs the task of writing entries to the log file.
			 * @return void
			 */
			void task () noexcept;

		private:

			std::string m_filepath;
			std::queue< TracerEntry > m_entries;
			std::mutex m_entriesAccessMutex;
			bool m_isRunning{true};
	};
}
