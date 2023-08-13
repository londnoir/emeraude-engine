/*
 * Libraries/VertexFactory/FileIO.hpp
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
#include <iostream>
#include <type_traits>

/* Local inclusions for usages. */
#include "Types.hpp"
#include "FileFormatFBX.hpp"
#include "FileFormatMD2.hpp"
#include "FileFormatMD3.hpp"
#include "FileFormatMD5.hpp"
#include "FileFormatMDL.hpp"
#include "FileFormatNative.hpp"
#include "FileFormatOBJ.hpp"

namespace Libraries::VertexFactory::FileIO
{
	/** @brief Enumerates shape file type handled. */
	enum class FileType
	{
		Unhandled,
		Native,
		WavefrontOBJ,
		IDSoftwareMDL,
		IDSoftwareMD2,
		IDSoftwareMD3,
		IDSoftwareMD5,
		AutodeskFBX
	};

	/**
	 * @brief Returns the type of format from filepath.
	 * @param filepath A reference to the file path.
	 * @return FileType
	 */
	[[nodiscard]]
	FileType getFileType (const Path::File & filepath) noexcept;

	/**
	 * @brief Reads a file into a shape structure.
	 * @tparam data_t The pixmap data precision. Default 'uint8_t' (8bits per chanel).
	 * @param filepath filepath A reference to a file path.
	 * @param shape A reference to the destination shape.
	 * @return bool
	 */
	template< typename data_t = uint8_t, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
	[[nodiscard]]
	bool
	read (const Path::File & filepath, Shape< data_t > & shape)
	{
		if ( !filepath.exists() )
		{
			std::cerr << "VertexFactory::FileIO::read(), the file '" << filepath << "' doesn't exist !" "\n";

			return false;
		}

		switch ( FileIO::getFileType(filepath) )
		{
			case FileType::Unhandled :
				std::cerr << "VertexFactory::FileIO::read(), the file '" << filepath << "' format is not handled !" "\n";

				return false;

			case FileType::Native :
			{
				FileFormatNative< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::WavefrontOBJ :
			{
				FileFormatOBJ< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::IDSoftwareMDL :
			{
				FileFormatMDL< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::IDSoftwareMD2 :
			{
				FileFormatMD2< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::IDSoftwareMD3 :
			{
				FileFormatMD3< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::IDSoftwareMD5 :
			{
				FileFormatMD5< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::AutodeskFBX :
			{
				FileFormatFBX< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}
		}

		return false;
	}

	/**
	 * @briew Writes a shape into a file.
	 * @tparam data_t The pixmap data precision. Default 'uint8_t' (8bits per chanel).
	 * @param shape A reference to the source shape.
	 * @param filepath filepath A reference to a file path.
	 * @param overwrite Overwrite existing file. Default false.
	 * @return bool
	 */
	template< typename data_t = uint8_t, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
	[[nodiscard]]
	bool
	write (const Shape< data_t > & shape, const Path::File & filepath, bool overwrite = false)
	{
		if ( filepath.exists() && !overwrite )
		{
			std::cerr << "VertexFactory::FileIO::write(), the file '" << filepath << "' already exists !" "\n";

			return false;
		}

		switch ( getFileType(filepath) )
		{
			case FileType::Unhandled :
				std::cerr << "VertexFactory::FileIO::write(), the file '" << filepath << "' format is not handled !" "\n";

				return false;

			case FileType::Native :
			{
				FileFormatNative< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::WavefrontOBJ :
			{
				FileFormatOBJ< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::IDSoftwareMDL :
			{
				FileFormatMDL< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::IDSoftwareMD2 :
			{
				FileFormatMD2< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::IDSoftwareMD3 :
			{
				FileFormatMD3< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::IDSoftwareMD5 :
			{
				FileFormatMD5< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}

			case FileType::AutodeskFBX :
			{
				FileFormatFBX< data_t > fileFormat{};

				return fileFormat.readFile(filepath, shape);
			}
		}

		return false;
	}
}
