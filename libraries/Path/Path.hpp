/*
 * Libraries/Path/Path.hpp
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
#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Libraries::Path
{
	constexpr auto Separator = '/';

	/**
	 * A class describing a path as simple tokens between slashes.
	 * It can be used in URL, directory, file path, and wherever a path is needed.
	 */
	class Path final
	{
		public:

			const static std::array< std::string, 3 > PathBases;

			/**
			 * @brief Constructs a default path.
			 */
			Path () noexcept = default;

			/**
			 * @brief Constructs a path.
			 * @warning There is no check with this version.
			 * @param segments List of segment of the path.
			 * @param filename A name to append to the path [std::move]. Default empty.
			 * @param pathBase The beginning of the path [std::move]. Default "/".
			 */
			explicit Path (const std::vector< std::string > & segments, std::string filename = {}, std::string pathBase = PathBases[2]) noexcept;

			/**
			 * @brief Constructs a path from a raw string.
			 * @param rawString A raw string of path.
			 */
			explicit Path (std::string rawString) noexcept;

			/**
			 * @brief Adds a chunk at the end of the path. But before the filename if exists.
			 * @param name The name of the file or segment to append to the current path.
			 * @return void
			 */
			void append (const std::string & name) noexcept;

			/**
			 * @brief Sets the beginning of the path. This could be "/", "./" or "../".
			 * @param pathBase A reference to a string.
			 * @return void
			 */
			void setPathBase (const std::string & pathBase) noexcept;

			/**
			 * @brief Sets a file name at the end of the path. This won't be treated as a path segment.
			 * @param name A reference to a string.
			 * @return void
			 */
			void setFilename (const std::string & name) noexcept;

			/**
			 * @brief Returns the optional path base.
			 * @return const string &
			 */
			[[nodiscard]]
			const std::string & pathBase () const noexcept;

			/**
			 * @brief Returns the path as a string without the filename if defined.
			 * @return string
			 */
			[[nodiscard]]
			std::string directory () const noexcept;

			/**
			 * @brief Returns the optional filename.
			 * @return const string &
			 */
			[[nodiscard]]
			const std::string & filename () const noexcept;

			/**
			 * @brief Returns whether the path is empty.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			empty () const noexcept
			{
				return m_segments.empty() && m_filename.empty();
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Path & obj);

			/**
			 * @brief Stringify the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const Path & obj) noexcept;

		private:

			std::string m_base{};
			std::vector< std::string > m_segments{};
			std::string m_filename{};
	};
}
