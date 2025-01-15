/*
 * src/Libraries/Compression/LZMA.hpp
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
#include <string>

namespace Libraries::Compression::LZMA
{
	/**
	 * @brief Compresses a string with LZMA algorithm.
	 * @param input A reference to a string.
	 * @param output A writable reference to a string.
	 * @param level The compression level from 0 to 9. Default 9 (high).
	 * @return bool
	 */
	bool compressString (const std::string & input, std::string & output, int level = 9) noexcept;

	/**
	 * @brief Decompresses a string with LZMA algorithm.
	 * @param input A reference to a string.
	 * @param output A writable reference to a string.
	 * @return bool
	 */
	bool decompressString (const std::string & input, std::string & output) noexcept;
}
