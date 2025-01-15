/*
 * src/Libraries/PixelFactory/FileIO.hpp
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
#include <cstdint>
#include <filesystem>
#include <iostream>
#include <type_traits>

/* Local inclusions for usages. */
#include "Libraries/IO.hpp"
#include "FileFormatJpeg.hpp"
#include "FileFormatPNG.hpp"
#include "FileFormatTarga.hpp"
#include "Pixmap.hpp"

namespace Libraries::PixelFactory::FileIO
{
	/**
	 * @brief Reads a file into a pixmap structure.
	 * @tparam data_t The pixmap data precision. Default 'uint8_t' (8bits per chanel).
	 * @param filepath A reference to a filesystem path.
	 * @param pixmap A reference to the destination pixmap.
	 * @return bool
	 */
	template< typename data_t = uint8_t >
	[[nodiscard]]
	bool
	read (const std::filesystem::path & filepath, Pixmap< data_t > & pixmap) requires (std::is_arithmetic_v< data_t >)
	{
		if ( !IO::fileExists(filepath) )
		{
			std::cerr << "PixelFactory::FileIO::read(), the file '" << filepath << "' doesn't exist !" "\n";

			return false;
		}

		const auto extension = IO::getFileExtension(filepath, true);

		if ( extension == "jpg" || extension == "jpeg" )
		{
			FileFormatJpeg< data_t > fileFormat;

			return fileFormat.readFile(filepath, pixmap);
		}

		if ( extension == "png" )
		{
			FileFormatPNG< data_t > fileFormat;

			return fileFormat.readFile(filepath, pixmap);
		}

		if ( extension == "tga" )
		{
			FileFormatTarga< data_t > fileFormat;

			return fileFormat.readFile(filepath, pixmap);
		}

		std::cerr << "PixelFactory::FileIO::read(), the file '" << filepath << "' format is not handled !" "\n";

		return false;
	}

	/**
	 * @briew Writes a pixmap into a file.
	 * @tparam data_t The pixmap data precision. Default 'uint8_t' (8bits per chanel).
	 * @param pixmap A reference to the source pixmap.
	 * @param filepath A reference to a filesystem path.
	 * @param overwrite Overwrite existing file. Default false.
	 * @return bool
	 */
	template< typename data_t = uint8_t >
	[[nodiscard]]
	bool
	write (const Pixmap< data_t > & pixmap, const std::filesystem::path & filepath, bool overwrite = false) requires (std::is_arithmetic_v< data_t >)
	{
		if ( IO::fileExists(filepath) && !overwrite )
		{
			std::cerr << "PixelFactory::FileIO::write(), the file '" << filepath << "' already exists !" "\n";

			return false;
		}

		const auto extension = IO::getFileExtension(filepath, true);

		if ( extension == "jpg" || extension == "jpeg" )
		{
			FileFormatJpeg< data_t > fileFormat;

			return fileFormat.writeFile(filepath, pixmap);
		}

		if ( extension == "png" )
		{
			FileFormatPNG< data_t > fileFormat;

			return fileFormat.writeFile(filepath, pixmap);
		}

		if ( extension == "tga" )
		{
			FileFormatTarga< data_t > fileFormat;

			return fileFormat.writeFile(filepath, pixmap);
		}

		std::cerr << "PixelFactory::FileIO::write(), the file '" << filepath << "' format is not handled !" "\n";

		return false;
	}
}
