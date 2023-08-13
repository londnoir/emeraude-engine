/*
 * Emeraude/TracerEntry.hpp
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
#include <chrono>
#include <string>
#include <thread>
#if defined(__clang__) && __clang_major__ < 16
#include <experimental/source_location>

namespace std_glue = std::experimental;
#else
#include <source_location>

namespace std_glue = std;
#endif

/* Local inclusions for usages. */
#include "Types.hpp"

namespace Emeraude
{
	/**
	 * @brief The TracerEntry class
	 */
	class TracerEntry final
	{
		public:

			/**
			 * @brief Constructs a tracer entry.
			 * @param severity The severity of the message.
			 * @param tag The tag to sort and/or filter entries.
			 * @param message The content of the entry [std::move].
			 * @param location The location of the message in the code source.
			 * @param threadId The thread ID.
			 */
			TracerEntry (Severity severity, const char * tag, std::string message, const std_glue::source_location & location, const std::thread::id & threadId) noexcept;

			/**
			 * @brief Returns the time of the message.
			 * @return const time_point< steady_clock > &
			 */
			[[nodiscard]]
			const std::chrono::time_point< std::chrono::steady_clock > & time () const noexcept;

			/**
			 * @brief Returns the severity of the message.
			 * @return Severity
			 */
			[[nodiscard]]
			Severity severity () const noexcept;

			/**
			 * @brief Returns the tag of the entry.
			 * @param const char *
			 */
			[[nodiscard]]
			const char * tag () const noexcept;

			/**
			 * @brief Returns the message.
			 * @param std::string
			 */
			[[nodiscard]]
			const std::string & message () const noexcept;

			/**
			 * @brief Returns the location where the entry comes from.
			 * @param const std_glue::source_location &
			 */
			[[nodiscard]]
			const std_glue::source_location & location () const noexcept;

			/**
			 * @brief Returns the thread ID where the entry was generated.
			 * @param thread::id
			 */
			[[nodiscard]]
			const std::thread::id & threadId () const noexcept;

		private:

			std::chrono::time_point< std::chrono::steady_clock > m_time{std::chrono::steady_clock::now()};
			Severity m_severity{Severity::Info};
			const char * m_tag{nullptr};
			std::string m_message;
			std_glue::source_location m_location;
			std::thread::id m_threadId;
	};
}
