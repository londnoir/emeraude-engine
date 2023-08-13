/*
 * Libraries/Path/Directory.hpp
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

/* C/C++ standard libraries */
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Libraries::Path
{
	class Directory final
	{
		public:

			/**
			 * @brief Constructs a directory.
			 */
			Directory () noexcept = default;

			/**
			 * @brief Constructs a directory from a path.
			 * @param path A reference to a string to define the directory.
			 */
			explicit Directory (const std::string & path) noexcept;

			/**
			 * @brief Checks if two directories is not the same.
			 * @param operand A reference to an other directory.
			 * @return bool
			 */
			[[nodiscard]]
			bool operator== (const Directory & operand) const noexcept;

			/**
			 * @brief Returns whether the path is empty.
			 * @return bool
			 */
			[[nodiscard]]
			bool empty () const noexcept;

			/**
			 * @brief Returns whether the path is empty.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t length () const noexcept;

			/**
			 * @brief Sets a new directory path.
			 * @param path A reference to a string to define the directory.
			 */
			void set (const std::string & path) noexcept;

			/**
			 * @brief Appends a sub-folder to the current one.
			 * @param part A reference to a string.
			 * @return Directory &
			 */
			Directory & append (const std::string & part) noexcept;

			/**
			 * @brief Checks the directory is ready to be used and writable.
			 * @note This is useful for cache directory.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			checkUsage () const noexcept
			{
				if ( this->exists() )
				{
					return this->writable();
				}

				return this->create();
			}

			/**
			 * @brief Checks if the directory exists on disk.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			exists () const noexcept
			{
				return Directory::exists(to_string(*this));
			}

			/**
			 * @brief Checks if the directory exists on disk.
			 * @param path A reference to a string to define a directory.
			 * @return bool
			 */
			static bool exists (const std::string & path) noexcept;

			/**
			 * @brief Checks if the directory is writable.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			writable () const noexcept
			{
				return Directory::writable(to_string(*this));
			}

			/**
			 * @brief Checks if the directory is writable.
			 * @param path A reference to a string to define a directory.
			 * @return bool
			 */
			static bool writable (const std::string & path) noexcept;

			/**
			 * @brief Creates the whole path on disk.
			 * @todo Use std::filesystem::create_directories()
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			create () const noexcept
			{
				return Directory::create(to_string(*this), false);
			}

			/**
			 * @brief Creates the whole path on disk.
			 * @todo Use std::filesystem::create_directories()
			 * @param path A reference to a string to define a directory.
			 * @param lastPartIsFile Ignore the last part of the path. Default false.
			 * @return bool
			 */
			static bool create (const std::string & path, bool lastPartIsFile = false) noexcept;

			/**
			 * @brief Removes the last folder from the path.
			 * @warning  This is a destructive function.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			remove () const noexcept
			{
				return Directory::remove(to_string(*this));
			}

			/**
			 * @brief Removes the last folder from the path.
			 * @warning  This is a destructive function.
			 * @param path A reference to a string to define a directory.
			 * @return bool
			 */
			static bool remove (const std::string & path) noexcept;

			/**
			 * @brief Returns a list of entries to this directory.
			 * @return vector< string >
			 */
			[[nodiscard]]
			std::vector< std::string > entries () const noexcept;

			/**
			 * @brief Returns the current working directory.
			 * @return Directory
			 */
			static Directory getCurrentWorkingDirectory () noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Directory & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const Directory & obj) noexcept;

		private:

			/**
			 * @brief Creates a directory.
			 * @todo Use std::filesystem::create_directories()
			 * @param path A reference to a string.
			 * @return bool
			 */
			static bool mkdir (const std::string & path) noexcept;

			std::string m_startPoint;
			std::vector< std::string > m_parts;
	};
}
