/*
 * Libraries/VertexFactory/FileFormatInterface.hpp
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
#include <array>
#include <iostream>

/* Local inclusions for usages. */
#include "Path/File.hpp"
#include "Shape.hpp"

namespace Libraries::VertexFactory
{
	/**
	 * @brief File format interface for reading and writing a geometry.
	 * @tparam data_t The data precision.
	 */
	template< typename data_t, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	class FileFormatInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			FileFormatInterface (const FileFormatInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			FileFormatInterface (FileFormatInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return FileFormatInterface &
			 */
			FileFormatInterface & operator= (const FileFormatInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return FileFormatInterface &
			 */
			FileFormatInterface & operator= (FileFormatInterface && copy) noexcept = default;

			/**
			 * @brief Destructs the pixmap format.
			 */
			virtual ~FileFormatInterface () = default;

			/**
			 * @brief Reads the geometry from a file.
			 * @param filepath The file path.
			 * @param geometry A reference to the Geometry.
			 * @return bool
			 */
			virtual bool readFile (const Path::File & filepath, Shape< data_t > & geometry) noexcept = 0;

			/**
			 * @brief Writes the geometry to a file.
			 * @param filepath The file path. Should be accessible.
			 * @param geometry A read-only reference to the Geometry.
			 * @return bool
			 */
			virtual bool writeFile (const Path::File & filepath, const Shape< data_t > & geometry) const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a pixmap format.
			 */
			FileFormatInterface () noexcept = default;

		private:

			/* Flag names. */
			std::array< bool, 8 > m_flags{ // NOLINT(*-magic-numbers)
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
