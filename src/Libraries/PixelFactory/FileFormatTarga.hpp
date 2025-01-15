/*
 * src/Libraries/PixelFactory/FileFormatTarga.hpp
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
#include <array>
#include <iostream>
#include <fstream>

/* Local inclusions for inheritances. */
#include "FileFormatInterface.hpp"

/* Local inclusions for usages. */
#include "Processor.hpp"

namespace Libraries::PixelFactory
{
	/**
	 * @brief Class for read and write Targa format.
	 * @tparam data_t Precision of data.
	 * @extends Libraries::PixelFactory::FileFormatInterface The base IO class.
	 */
	template< typename data_t = uint8_t >
	requires (std::is_integral_v< data_t >)
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
			readFile (const std::filesystem::path & filepath, Pixmap< data_t > & pixmap) noexcept override
			{
				pixmap.clear();

				std::ifstream file{filepath, std::ios::binary};

				if ( !file.is_open() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", unable to read the Targa file " << filepath << " !" "\n";

					return false;
				}

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

				std::array< uint32_t, 12 > size = {1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 1, 1};

				/* Read out the TARGA header, byte to byte */
				for ( auto i = 0U; i < 12; i++ )
				{
					if ( !file.read(static_cast< char * >(ptr.at(i)), size.at(i)) )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", unable to read the Targa header !" "\n";

						return false;
					}
				}

#ifdef EMERAUDE_DEBUG_PIXEL_FACTORY
				std::cout <<
					"[TARGA_DEBUG] Reading header.\n" <<
					"\t" "idCharCount : " << static_cast< int >(fileHeader.idCharCount) << "\n"
					"\t" "colorMapType : " << static_cast< int >(fileHeader.colorMapType) << "\n"
					"\t" "imageTypeCode : " << static_cast< int >(fileHeader.imageTypeCode) << "\n"
					"\t" "colorMapOrigin : " << static_cast< int >(fileHeader.colorMapOrigin) << "\n"
					"\t" "colorMapLength : " << static_cast< int >(fileHeader.colorMapLength) << "\n"
					"\t" "colorMapEntrySize : " << static_cast< int >(fileHeader.colorMapEntrySize) << "\n"
					"\t" "xOrigin : " << static_cast< int >(fileHeader.xOrigin) << "\n"
					"\t" "yOrigin : " << static_cast< int >(fileHeader.yOrigin) << "\n"
					"\t" "width : " << static_cast< int >(fileHeader.width) << "\n"
					"\t" "height : " << static_cast< int >(fileHeader.height) << "\n"
					"\t" "imagePixelSize : " << static_cast< int >(fileHeader.imagePixelSize) << "\n"
					"\t" "imageDescriptorByte : " << fileHeader.imageDescriptorByte  << '\n';
#endif

				auto pixmapAllocated = false;

				switch ( fileHeader.imageTypeCode )
				{
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

					/* Grayscale Targa file */
					case 11 : /* 8bits, 16bits Grayscale(RLE) */
						RLE = true;

						[[fallthrough]];

					case 3 : /* 8bits, 16bits Grayscale */
						pixmapAllocated = pixmap.initialize(fileHeader.width, fileHeader.height, ChannelMode::Grayscale);
						break;

					case 32 : /* Compressed color-mapped data, using Huffman, Delta, and run-length encoding. */
					case 33 : /* Compressed color-mapped data, using Huffman, Delta, and run-length encoding.  4-pass quadtree-type process.*/
						std::cerr << __PRETTY_FUNCTION__ << ", unhandled type of Targa file !" "\n";
						break;

					case 0 : /* No image data included. */
					default:
						std::cerr << __PRETTY_FUNCTION__ << ", no pixel data !" "\n";

						return false;
				}

				/* Memory allocation. */
				if ( !pixmapAllocated )
				{
					return false;
				}

				/* Store identification. */
				if ( fileHeader.idCharCount > 0 )
				{
					std::string identification;
                    identification.resize(fileHeader.idCharCount + 1, '\0');

					if ( !file.read(identification.data(), fileHeader.idCharCount) )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", unable to read the Targa identification !" "\n";

						return false;
					}
				}

				/* Load data. */
				if ( RLE )
				{
					/* FIXME: Complete the method ... */

					std::cerr << __PRETTY_FUNCTION__ << ", RLE compression not handled for now !" "\n";
				}
				else
				{
					if ( !file.read(reinterpret_cast< char * >(pixmap.data().data()), pixmap.bytes()) )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", unable to read the Targa data !" "\n";

						return false;
					}

					/* Checks the Y-Axis orientation. */
					if ( this->invertYAxis() )
					{
						/* NOTE: Origin is top-left in TGA file. */
						if ( fileHeader.yOrigin > 0 )
						{
							pixmap = Processor< uint8_t >::mirror(pixmap, MirrorMode::X);
						}
					}
					else
					{
						/* NOTE: Origin is bottom-left in TGA file. */
						if ( fileHeader.yOrigin == 0 )
						{
							pixmap = Processor< uint8_t >::mirror(pixmap, MirrorMode::X);
						}
					}

					/* Convert BGR to RGB format. */
					if ( pixmap.colorCount() > 1 )
					{
						pixmap = Processor< uint8_t >::swapChannels(pixmap);
					}
				}

				return true;
			}

			/** @copydoc Libraries::PixelFactory::FileFormatInterface::writeFile() */
			[[nodiscard]]
			bool
			writeFile (const std::filesystem::path & filepath, const Pixmap< data_t > & pixmap) const noexcept override
			{
				if ( !pixmap.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", pixmap parameter is invalid !" "\n";

					return false;
				}

				std::ofstream file{filepath, std::ios::binary};

				if ( !file.is_open() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", unable to open a Targa file " << filepath << " for writing !" "\n";

					return false;
				}

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
					/* Grayscale Targa file */
					case ChannelMode::Grayscale :
						fileHeader.imageTypeCode = 3; // RLE = 10
						break;

					/* Composite */
					case ChannelMode::RGB :
					case ChannelMode::RGBA :
						fileHeader.imageTypeCode = 2; // RLE = 11
						break;

					case ChannelMode::GrayscaleAlpha :
					default:
						std::cerr << __PRETTY_FUNCTION__ << ", unhandled color channel format to write a Targa image." "\n";

						return false;;
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

				std::array< uint32_t, 12 > size = {1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 1, 1};

#ifdef EMERAUDE_DEBUG_PIXEL_FACTORY
				std::cout <<
					"[TARGA_DEBUG] Writing header.\n" <<
					"\t" "idCharCount : " << static_cast< int >(fileHeader.idCharCount) << "\n"
					"\t" "colorMapType : " << static_cast< int >(fileHeader.colorMapType) << "\n"
					"\t" "imageTypeCode : " << static_cast< int >(fileHeader.imageTypeCode) << "\n"
					"\t" "colorMapOrigin : " << static_cast< int >(fileHeader.colorMapOrigin) << "\n"
					"\t" "colorMapLength : " << static_cast< int >(fileHeader.colorMapLength) << "\n"
					"\t" "colorMapEntrySize : " << static_cast< int >(fileHeader.colorMapEntrySize) << "\n"
					"\t" "xOrigin : " << static_cast< int >(fileHeader.xOrigin) << "\n"
					"\t" "yOrigin : " << static_cast< int >(fileHeader.yOrigin) << "\n"
					"\t" "width : " << static_cast< int >(fileHeader.width) << "\n"
					"\t" "height : " << static_cast< int >(fileHeader.height) << "\n"
					"\t" "imagePixelSize : " << static_cast< int >(fileHeader.imagePixelSize) << "\n"
					"\t" "imageDescriptorByte : " << fileHeader.imageDescriptorByte  << '\n';
#endif

				/* Write in the Targa header, byte to byte */
				for ( auto i = 0U; i < 12; i++ )
				{
					if ( !file.write(static_cast< const char * >(ptr.at(i)), size.at(i)) )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", unable to write the Targa header !" "\n";

						return false;
					}
				}

				/* Writing identification field. */
				if ( fileHeader.idCharCount > 0 )
				{
					if ( !file.write(identification.data(), fileHeader.idCharCount * sizeof(char)) )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", unable to write the Targa identification !" "\n";

						return false;
					}
				}

				/* NOTE: We use the default TGA bottom-left origin image. */
				if ( pixmap.colorCount() > 1 )
				{
					/* RGB -> BGR */
					auto copy = Processor< uint8_t >::swapChannels(pixmap);

					if ( !this->invertYAxis() )
					{
						copy = Processor< uint8_t >::mirror(copy, MirrorMode::X);
					}

					if ( !file.write(reinterpret_cast< const char * >(copy.data().data()), copy.bytes()) )
					{
						std::cerr << __PRETTY_FUNCTION__ << ", unable to write the Targa data !" "\n";

						return false;
					}
				}
				else
				{
					if ( this->invertYAxis() )
					{
						if ( !file.write(reinterpret_cast< const char * >(pixmap.data().data()), pixmap.bytes()) )
						{
							std::cerr << __PRETTY_FUNCTION__ << ", unable to write the Targa data !" "\n";

							return false;
						}
					}
					else
					{
						const auto copy = Processor< uint8_t >::mirror(pixmap, MirrorMode::X);

						if ( !file.write(reinterpret_cast< const char * >(copy.data().data()), copy.bytes()) )
						{
							std::cerr << __PRETTY_FUNCTION__ << ", unable to write the Targa data !" "\n";

							return false;
						}
					}
				}

				return true;
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
}
