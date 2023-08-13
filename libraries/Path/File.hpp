/*
 * Libraries/Path/File.hpp
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

/* Local inclusions */
#include "Path/Directory.hpp"

namespace Libraries::Path
{
	class File final
	{
		public:

			/**
			 * @brief Constructs a default file.
			 */
			File () noexcept = default;

			/**
			 * @brief Constructs a file from a Directory and a filename.
			 * @param directory The directory [std::move].
			 * @param filename A string for the filename [std::move].
			 */
			File (Directory directory, std::string filename) noexcept;

			/**
			 * @brief Constructs a File from a full filepath.
			 * @param path A reference to a string.
			 */
			explicit File (const std::string & path) noexcept;

			/**
			 * @brief Returns whether the path is empty.
			 * @return bool
			 */
			[[nodiscard]]
			bool empty () const noexcept;

			/**
			 * @brief Returns the length of the path.
			 * @return size_T
			 */
			[[nodiscard]]
			size_t length () const noexcept;

			/**
			 * @brief Sets a new path.
			 * @param directory A reference to a directory.
			 * @param filename A reference to a string.
			 * @return void
			 */
			void set (const Directory & directory, const std::string & filename) noexcept;

			/**
			 * @brief Sets a new path.
			 * @param path A reference to a string.
			 * @return void
			 */
			void set (const std::string & path) noexcept;

			/**
			 * @brief Returns whether the filename has the extension.
			 * @param extension A reference to a string.
			 * @return bool
			 */
			[[nodiscard]]
			bool hasExtension (const std::string & extension) const noexcept;

			/**
			 * @brief Returns whether the filename has one of extensions.
			 * @param extensions A reference to a list of extensions.
			 * @return bool
			 */
			[[nodiscard]]
			bool hasExtensions (const std::vector< std::string > & extensions) const noexcept;

			/**
			 * @brief Returns whether the filename has one of extensions.
			 * @param extensions A reference to a list of extensions.
			 * @return bool
			 */
			[[nodiscard]]
			bool hasExtensions (const std::vector< const char * > & extensions) const noexcept;

			/**
			 * @brief Returns whether the filename has one of extensions.
			 * @param extensions A pointer to an array of c-string.
			 * @param size The size of the array.
			 * @return bool
			 */
			[[nodiscard]]
			bool hasExtensions (const char * const * extensions, size_t size) const noexcept;

			/**
			 * @brief Returns the filename without the directory.
			 * @return const string &
			 */
			[[nodiscard]]
			const std::string & getFilename () const noexcept;

			/**
			 * @brief Checks if the file exists at pointed location.
			 * @return bool
			 */
			[[nodiscard]]
			bool exists () const noexcept;

			/**
			 * @brief Checks if the file exists at pointed location.
			 * @param path A reference to a string.
			 * @return bool
			 */
			static bool exists (const std::string & path) noexcept;

			/**
			 * @brief Creates an empty file at pointed location.
			 * @return bool
			 */
			[[nodiscard]]
			bool create () const noexcept;

			/**
			 * @brief Creates an empty file at pointed location.
			 * @param path A reference to a string.
			 * @return bool
			 */
			static bool create (const std::string & path) noexcept;

			/**
			 * @brief Erases the file at pointed location.
			 * @warning This is a destructive function.
			 * @return bool
			 */
			[[nodiscard]]
			bool erase () const noexcept;

			/**
			 * @brief Erases the file at pointed location.
			 * @warning This is a destructive function.
			 * @param path A reference to a string.
			 * @return bool
			 */
			static bool erase (const std::string & path) noexcept;

			/**
			 * @brief Cleans the file path.
			 * @param fullPath A point to a C-string.
			 * @return string
			 */
			[[nodiscard]]
			static std::string cleanFilepath (const char * fullPath) noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const File & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const File & obj) noexcept;

		private:

			Directory m_directory;
			std::string m_filename;
	};
}
