/*
 * Libraries/Utility.cpp
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

#include "Utility.hpp"

/* C/C++ standard libraries. */
#include <chrono>
#include <sstream>

/* Third-party libraries */
#include "Third-Party-Inclusion/zlib.hpp"

namespace Libraries::Utility
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
	bool
	fileGetContents (const Path::File & filepath, std::string & content) noexcept
	{
		std::ifstream file{to_string(filepath), std::ios::ate};

		if ( !file.is_open() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to read '" << filepath << "' file." "\n";

			return false;
		}

		/* NOTE: Read the file size. */
		const auto size = file.tellg();
		file.seekg(0);

		content.resize(size);

		file.read(content.data(), static_cast< std::streamsize >(content.size()));
		file.close();

		return true;
	}

	bool
	filePutContents (const Path::File & filepath, const std::string & content) noexcept
	{
		std::ofstream file{to_string(filepath), std::ios::trunc};

		if ( !file.is_open() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to write into '" << filepath << "' file." "\n";

			return false;
		}

		file << content;
		file.close();

		return true;
	}

	// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
	bool
	uncompressStream (std::istream & sourceStream, std::ostream & targetStream) noexcept
	{
#ifdef ZLIB_ENABLED
		/* Compressed source stream will go here. */
		std::string source;
		/* Uncompressed buffer will go here
		 * and read back to target stream. */
		std::string destination;

		while ( sourceStream.good() )
		{
			/* Read to size_t variable the uncompressed size. */
			size_t baseSize = 0;

			sourceStream.read(reinterpret_cast< char * >(&baseSize), sizeof(size_t));

			/* If the chunk header says nothing,
			 * we are at the end of the stream. */
			if ( baseSize == 0 )
			{
				return true;
			}

			/* Read to size_t variable the compressed size. */
			size_t compressedSize = 0;

			sourceStream.read(reinterpret_cast< char * >(&compressedSize), sizeof(size_t));

			/* Resize both of buffer before writing into. */
			source.resize(compressedSize);
			destination.resize(baseSize);

			/* Read some bytes of compressed data. */
			auto readSize = static_cast< std::streamsize >(compressedSize * sizeof(char));

			if ( sourceStream.read(source.data(), readSize) )
			{
				auto * dest = reinterpret_cast< Bytef * >(destination.data());
				const auto * src = reinterpret_cast< const Bytef * >(source.c_str());

				if ( uncompress(dest, &baseSize, src, compressedSize) > 0 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", unable to uncompress stream." "\n";

					return false;
				}

				/* Write uncompressed data to destination string. */
				auto writeSize = static_cast< std::streamsize >(baseSize * sizeof(char));

				targetStream.write(destination.c_str(), writeSize);
			}
			else
			{
				std::cerr << __PRETTY_FUNCTION__ << ", unable to read compressed stream." "\n";

				return false;
			}
		}

		std::cerr << __PRETTY_FUNCTION__ << ", stream seems broken." "\n";

		return false;
#else
		std::cerr << "[DEBUG] " << __PRETTY_FUNCTION__ << ", ZLib not available !" "\n";

		return false;
#endif
	}
	// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

	// NOLINTBEGIN(cppcoreguidelines-pro-type-reinterpret-cast)
	size_t
	compressStream (std::istream & sourceStream, std::ostream & targetStream, size_t chunkSize, int level) noexcept
	{
#ifdef ZLIB_ENABLED
		sourceStream.seekg(0, std::istream::end);
		const std::streamoff finalPosition = sourceStream.tellg();
		sourceStream.seekg(0, std::istream::beg);

		if ( finalPosition <= 0 )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", nothing to compress !" "\n";

			return 0;
		}

		/* Gets length of stream. */
		auto streamSize = static_cast< size_t >(finalPosition);

		size_t steppes = 0;

		if ( streamSize < chunkSize )
		{
			chunkSize = streamSize;

			steppes = 1;
		}
		else
		{
			steppes = streamSize / chunkSize;

			if ( streamSize % chunkSize > 0 )
			{
				steppes++;
			}
		}

		/* Compression result size. */
		size_t compressedSize = 0;

		/* Uncompressed source stream will go here. */
		std::string source{};
		source.resize(chunkSize);

		/* Compressed buffer will go here and read back to target stream. */
		std::string destination{};

		for ( size_t step = 0; step < steppes; step++ )
		{
			/* Read chunk size byte of uncompressed data. */
			auto readSize = static_cast< std::streamsize >(chunkSize * sizeof(char));

			sourceStream.read(source.data(), readSize);

			/* Prepare the size of the destination buffer by estimate it. */
			auto destinationSize = compressBound(chunkSize);

			destination.resize(destinationSize);

			/* Compression and retrieve the real size of the destination buffer. */
			auto * dest = reinterpret_cast< Bytef * >(destination.data());
			const auto * src = reinterpret_cast< const Bytef * >(source.c_str());

			auto error = compress2(dest, &destinationSize, src, chunkSize, level);

			if ( error > 0 )
			{
				std::cerr << __PRETTY_FUNCTION__ << ", " << zError(error) << "\n";

				return 0;
			}

			/* Write the base size and the compressed size. */
			targetStream.write(reinterpret_cast< const char * >(&chunkSize), sizeof(size_t));
			targetStream.write(reinterpret_cast< const char * >(&destinationSize), sizeof(size_t));

			/* Write compressed data. */
			auto writeSize = static_cast< std::streamsize >(destinationSize * sizeof(char));

			targetStream.write(destination.c_str(), writeSize);

			/* Adding compressed data chunk size to the total. */
			compressedSize += destinationSize;

			/* Compute data left to compress and reduce
			 * the chunk size if we are at the end of the stream. */
			if ( streamSize > chunkSize )
			{
				streamSize -= chunkSize;
			}

			if ( streamSize < chunkSize )
			{
				chunkSize = streamSize;
				source.resize(chunkSize);
			}
		}

		return compressedSize;
#else
		std::cerr << "[DEBUG] " << __PRETTY_FUNCTION__ << ", ZLib not available !" << std::endl;

		return 0;
#endif
	}
	// NOLINTEND(cppcoreguidelines-pro-type-reinterpret-cast)

	unsigned int
	timeBasedSeed () noexcept
	{
		/* FIXME : Check the error message. */
		//return static_cast< unsigned int >(std::time(nullptr));
		return static_cast< unsigned int >(std::chrono::system_clock::now().time_since_epoch().count());
	}
	// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
}
