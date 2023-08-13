/*
 * Libraries/PixelFactory/FileFormatTarga.hpp
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
#include <sstream>

/* Local inclusions for inheritances. */
#include "FileFormatInterface.hpp"

/* Local inclusions for usages. */
#include "Processor.hpp"

namespace Libraries::PixelFactory
{
	// NOLINTBEGIN(*-magic-numbers)

	/**
	 * @brief Class for read and write Targa format.
	 * @tparam data_t Precision of data.
	 * @extends Libraries::PixelFactory::FileFormatInterface The base IO class.
	 */
	template< typename data_t = uint8_t, std::enable_if_t< std::is_integral_v< data_t >, bool > = false >
	class FileFormatTarga final : public FileFormatInterface< data_t >
	{
		public:

			/**
			 * @brief Constructs a Targa format IO.
			 */
			FileFormatTarga () noexcept = default;

			/** @copydoc Libraries::PixelFactory::FileFormatInterface::readFile() */
			[[nodiscard]]
			bool
			readFile (const Path::File & filepath, Pixmap< data_t > & pixmap) noexcept override
			{
				pixmap.clear();

				/* FIXME: Use C++ stream. */
				auto * file = fopen(to_string(filepath).c_str(), "rb");

				if ( file != nullptr )
				{
					auto RLE = false;

					Header fileHeader{};

					std::array< void *, 12 > ptr = {
						&fileHeader.idCharCount,
						&fileHeader.colorMapType,
						&fileHeader.imageTypeCode,
						&fileHeader.colorMapOrigin,
						&fileHeader.colorMapLength,
						&fileHeader.colorMapEntrySize,
						&fileHeader.xOrigin,
						&fileHeader.yOrigin,
						&fileHeader.width,
						&fileHeader.height,
						&fileHeader.imagePixelSize,
						&fileHeader.imageDescriptorByte
					};

					std::array< size_t, 12 > size = {1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 1, 1};

					/* Read out the TARGA header, byte to byte */
					for ( auto i = 0U; i < 12; i++ )
					{
						if ( fread(ptr.at(i), size.at(i), 1, file) != 1 )
						{
							fclose(file);

							std::cerr << "[TARGA_ERROR] " << __PRETTY_FUNCTION__ << ", reading header #" << i << " (size:" << size.at(i) << ") from " << filepath << " file failed !" "\n";

							return false;
						}
					}

#ifdef DEBUG_PIXEL_FACTORY
					std::cout <<
						"[TARGA_DEBUG] Reading header.\n" <<
						"\tidCharCount : " << static_cast< int >(fileHeader.idCharCount) << '\n' <<
						"\tcolorMapType : " << static_cast< int >(fileHeader.colorMapType) << '\n' <<
						"\timageTypeCode : " << static_cast< int >(fileHeader.imageTypeCode) << '\n' <<
						"\tcolorMapOrigin : " << static_cast< int >(fileHeader.colorMapOrigin) << '\n' <<
						"\tcolorMapLength : " << static_cast< int >(fileHeader.colorMapLength) << '\n' <<
						"\tcolorMapEntrySize : " << static_cast< int >(fileHeader.colorMapEntrySize) << '\n' <<
						"\txOrigin : " << static_cast< int >(fileHeader.xOrigin) << '\n' <<
						"\tyOrigin : " << static_cast< int >(fileHeader.yOrigin) << '\n' <<
						"\twidth : " << static_cast< int >(fileHeader.width) << '\n' <<
						"\theight : " << static_cast< int >(fileHeader.height) << '\n' <<
						"\timagePixelSize : " << static_cast< int >(fileHeader.imagePixelSize) << '\n' <<
						"\timageDescriptorByte : " << fileHeader.imageDescriptorByte  << '\n' <<
					std::endl;
#endif

					auto pixmapAllocated = false;

					switch ( fileHeader.imageTypeCode )
					{
						case 0 : /* No image data included. */
							fclose(file);

							std::cerr << "[TARGA_ERROR] " << __PRETTY_FUNCTION__ << ", no pixel data !" "\n";

							return false;

					/* 256 colors index */
						case 9 : /* 8bits (RLE) */
							RLE = true;

							[[fallthrough]];

						case 1 : /* 8bits */
							pixmapAllocated = pixmap.initialize(fileHeader.width, fileHeader.height, ChannelMode::RGB);
							break;

					/* Composite */
						case 10 : /* 16bits, 24bits, 32bits BGR(RLE) */
							RLE = true;

							[[fallthrough]];

						case 2 : /* 16bits, 24bits, 32bits BGR */
							pixmapAllocated = pixmap.initialize(fileHeader.width, fileHeader.height, ( fileHeader.imagePixelSize == 32 ) ? ChannelMode::RGBA : ChannelMode::RGB);
							break;

					/* Grayscale targa file */
						case 11 : /* 8bits, 16bits Grayscale(RLE) */
							RLE = true;

							[[fallthrough]];

						case 3 : /* 8bits, 16bits Grayscale */
							pixmapAllocated = pixmap.initialize(fileHeader.width, fileHeader.height, ChannelMode::Grayscale);
							break;

						case 32 : /* Compressed color-mapped data, using Huffman, Delta, and run-length encoding. */
						case 33 : /* Compressed color-mapped data, using Huffman, Delta, and run-length encoding.  4-pass quadtree-type process.*/
							std::cerr << "[TARGA_ERROR] " << __PRETTY_FUNCTION__ << ", unhandled type of targa file !" "\n";
							break;
					}

					/* Memory allocation. */
					if ( !pixmapAllocated )
					{
						fclose(file);

						return false;
					}

					/* Store identification. */
					if ( fileHeader.idCharCount > 0 )
					{
						auto * identification = new char[fileHeader.idCharCount + 1]();

						fread(&identification, sizeof(char), static_cast< size_t >(fileHeader.idCharCount), file);
						identification[fileHeader.idCharCount] = '\0';

						delete[] identification;
						identification = nullptr;
					}

					/* Load data. */
					if ( RLE )
					{
						/* FIXME: Complete the method ... */

						std::cerr << "[TARGA_WARNING] " << __PRETTY_FUNCTION__ << ", RLE compression not handled for now !" "\n";
					}
					else
					{
						fread(pixmap.data().data(), sizeof(uint8_t), pixmap.bytes(), file);

						/* Checks the Y-Axis orientation. */
						if ( this->invertYAxis() )
						{
							/* NOTE: Origin is top-left in TGA file. */
							if ( fileHeader.yOrigin > 0 )
							{ 
								pixmap = Processor<data_t>::mirror(pixmap, MirrorMode::X); 
							}
						}
						else
						{
							/* NOTE: Origin is bottom-left in TGA file. */
							if ( fileHeader.yOrigin == 0 )
							{ 
								pixmap = Processor<data_t>::mirror(pixmap, MirrorMode::X); 
							}
						}

						/* Convert BGR to RGB format. */
						if ( pixmap.colorCount() > 1 )
						{
							Processor proc{pixmap};
							pixmap = proc.swapChannels();
						}
					}

					fclose(file);

					return true;
				}

				return false;
			}

			/** @copydoc Libraries::PixelFactory::FileFormatInterface::writeFile() */
			[[nodiscard]]
			bool
			writeFile (const Path::File & filepath, const Pixmap< data_t > & pixmap) const noexcept override
			{
				if ( !pixmap.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", pixmap parameter is invalid !" "\n";

					return false;
				}

				/* FIXME: Use C++ stream. */
				auto * file = fopen(to_string(filepath).c_str(), "wb");

				if ( file != nullptr )
				{
					/* Identification string */
					const std::string identification("Emeraude-Engine libPixelFactory");

					Header fileHeader{};

					/* FIXME: Check identification. */
					fileHeader.idCharCount = 0;//identification.size();
					/* NOTE: We use the default TGA bottom-left origin image. */
					fileHeader.yOrigin = static_cast< uint16_t >(pixmap.height());
					fileHeader.width = static_cast< uint16_t >(pixmap.width());
					fileHeader.height = static_cast< uint16_t >(pixmap.height());
					fileHeader.imagePixelSize = static_cast< uint8_t >(pixmap.bitPerPixel());

					switch ( pixmap.channelMode() )
					{
						/* Grayscale targa file */
						case ChannelMode::Grayscale :
							fileHeader.imageTypeCode = 3; // RLE = 10
							break;

						/* Composite */
						case ChannelMode::RGB :
						case ChannelMode::RGBA :
							fileHeader.imageTypeCode = 2; // RLE = 11
							break;

						case ChannelMode::GrayscaleAlpha :
							std::cerr << "[TARGA_ERROR] " << __PRETTY_FUNCTION__ << ", unhandled color channel format to write a Targa image." "\n";

							return false;
					}

					std::array< void *, 12 > ptr = {
						&fileHeader.idCharCount,
						&fileHeader.colorMapType,
						&fileHeader.imageTypeCode,
						&fileHeader.colorMapOrigin,
						&fileHeader.colorMapLength,
						&fileHeader.colorMapEntrySize,
						&fileHeader.xOrigin,
						&fileHeader.yOrigin,
						&fileHeader.width,
						&fileHeader.height,
						&fileHeader.imagePixelSize,
						&fileHeader.imageDescriptorByte
					};

					std::array< size_t, 12 > size = {1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 1, 1};

#ifdef DEBUG_PIXEL_FACTORY
					std::cout <<
						"[TARGA_DEBUG] Writing header.\n" <<
						"\tidCharCount : " << static_cast< int >(fileHeader.idCharCount) << '\n' <<
						"\tcolorMapType : " << static_cast< int >(fileHeader.colorMapType) << '\n' <<
						"\timageTypeCode : " << static_cast< int >(fileHeader.imageTypeCode) << '\n' <<
						"\tcolorMapOrigin : " << static_cast< int >(fileHeader.colorMapOrigin) << '\n' <<
						"\tcolorMapLength : " << static_cast< int >(fileHeader.colorMapLength) << '\n' <<
						"\tcolorMapEntrySize : " << static_cast< int >(fileHeader.colorMapEntrySize) << '\n' <<
						"\txOrigin : " << static_cast< int >(fileHeader.xOrigin) << '\n' <<
						"\tyOrigin : " << static_cast< int >(fileHeader.yOrigin) << '\n' <<
						"\twidth : " << static_cast< int >(fileHeader.width) << '\n' <<
						"\theight : " << static_cast< int >(fileHeader.height) << '\n' <<
						"\timagePixelSize : " << static_cast< int >(fileHeader.imagePixelSize) << '\n' <<
						"\timageDescriptorByte : " << fileHeader.imageDescriptorByte  << '\n' <<
					std::endl;
#endif

					/* Write in the TARGA header, byte to byte */
					for ( auto i = 0U; i < 12; i++ )
					{
						if ( fwrite(ptr.at(i), size.at(i), 1, file) != 1 )
						{
							fclose(file);

							std::cerr << "[TARGA_ERROR] " << __PRETTY_FUNCTION__ << ", writing header #" << i << " (size:" << size.at(i) << ") from " << filepath << " file failed !" "\n";

							return false;
						}
					}

					/* Writing identification field. */
					if ( fileHeader.idCharCount > 0 )
					{ 
						fwrite(identification.c_str(), sizeof(char), fileHeader.idCharCount, file); 
					}

					/* NOTE: We use the default TGA bottom-left origin image. */
					if ( pixmap.colorCount() > 1 )
					{
						Pixmap copy{pixmap};

						/* RGB -> BGR */
						Processor< uint8_t > proc{copy};
						copy = proc.swapChannels();

						if ( !this->invertYAxis() )
						{ 
							copy = Processor<data_t>::mirror(copy, MirrorMode::X); 
						}

						fwrite(copy.data().data(), sizeof(uint8_t), copy.bytes(), file);
					}
					else
					{
						if ( this->invertYAxis() )
						{
							fwrite(pixmap.data().data(), sizeof(uint8_t), pixmap.bytes(), file);
						}
						else
						{
							auto copy = Processor< data_t >::mirror(pixmap, MirrorMode::X);

							fwrite(copy.data().data(), sizeof(uint8_t), copy.bytes(), file);
						}
					}

					fclose(file);

					return true;
				}

				return false;
			}

		private:

			struct Header
			{
				/* Number of Characters in Identification Field. */
				uint8_t idCharCount = 0; /* 0:1 (0, 255) */
				/* Color Map Type. */
				uint8_t colorMapType = 0; /* 1:1 */
				/* Image Type Code. */
				uint8_t imageTypeCode = 0; /* 2:1 */
				/* Color Map Specification. */
				uint16_t colorMapOrigin = 0; /* 3:2 */
				uint16_t colorMapLength = 0; /* 5:2 */
				uint8_t colorMapEntrySize = 0;  /* 7:1 (16, 24, 32) */
				/* Image Specification. */
				uint16_t xOrigin = 0; /* 8:2 */
				uint16_t yOrigin = 0; /* 10:2 */
				uint16_t width = 0; /* 12:2 */
				uint16_t height = 0; /* 14:2 */
				uint8_t imagePixelSize = 0; /* 16:1 (16, 24, 32) */
				uint8_t imageDescriptorByte = 0; /* 17:1 */
			};
	};

	// NOLINTEND(*-magic-numbers)
}
