/*
 * Emeraude/TracerLogger.hpp
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
#include <mutex>
#include <queue>
#include <thread>

/* Local inclusions for usages. */
#include "TracerEntry.hpp"

namespace Emeraude
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
			explicit  TracerLogger (std::string filepath) noexcept;

			/**
			 * @brief Returns whether the logger can write to the log file.
			 * @return bool
			 */
			[[nodiscard]]
			bool usable () const noexcept;

			/**
			 * @brief Creates a log.
			 * @param severity The type of log.
			 * @param tag A pointer to a C-string to describe a tag. This help for sorting logs.
			 * @param message A reference to a string for the log content.
			 * @param location A reference to a source_location.
			 * @return void
			 */
			void push (Severity severity, const char * tag, const std::string & message, const std_glue::source_location & location) noexcept;

			/**
			 * @brief Stops nicely the writing task for shutting down the tracer service.
			 * @return void
			 */
			void stop () noexcept;

			/**
			 * @brief Clears pending entries.
			 * @return void
			 */
			void clear () noexcept;

			/**
			 * @brief Runs the task of writing entries to the log file.
			 * @return void
			 */
			void task () noexcept;

		private:

			std::string m_filepath;
			std::queue< TracerEntry > m_entries{};
			std::mutex m_mutex{};
			bool m_isRunning{true};
	};
}
