/*
 * src/Libraries/PixelFactory/FileFormatInterface.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <array>
#include <filesystem>

/* Local inclusions for usages. */
#include "Pixmap.hpp"

namespace Libraries::PixelFactory
{
	/**
	 * @brief File format interface for reading and writing a pixmap.
	 * @tparam data_t The data precision.
	 */
	template< typename data_t >
	requires (std::is_arithmetic_v< data_t >)
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
			 * @brief Returns whether the image must inverse Y axis to read and write image.
			 * @note true means origin at bottom-left (OpenGL compliant), else top-left (Vulkan, DX compliant).
			 * @return bool
			 */
			[[nodiscard]]
			bool
			invertYAxis () const noexcept
			{
				return m_flags[InvertYAxis];
			}

			/**
			 * @brief Reads the pixmap from a file.
			 * @param filepath A reference to a filesystem path.
			 * @param pixmap A reference to the pixmap.
			 * @return bool
			 */
			virtual bool readFile (const std::filesystem::path & filepath, Pixmap< data_t > & pixmap) noexcept = 0;

			/**
			 * @brief Writes the pixmap to a file.
			 * @param filepath A reference to a filesystem path. Should be accessible.
			 * @param pixmap A read-only reference to the pixmap.
			 * @return bool
			 */
			virtual bool writeFile (const std::filesystem::path & filepath, const Pixmap< data_t > & pixmap) const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a pixmap format.
			 */
			FileFormatInterface () noexcept = default;

		private:

			/* Flag names. */
			static constexpr auto InvertYAxis{0UL};

			std::array< bool, 8 > m_flags{
				false/*InvertYAxis*/,
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
