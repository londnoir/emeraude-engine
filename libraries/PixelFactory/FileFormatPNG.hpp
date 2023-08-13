/*
 * Libraries/PixelFactory/FileFormatPNG.hpp
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
#include <cstring> /* memcpy() */

/* Local inclusions for inheritances. */
#include "FileFormatInterface.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/png.hpp"

namespace Libraries::PixelFactory
{
	// NOLINTBEGIN(readability-identifier-length, *-magic-numbers)

	/**
	 * @brief Class for read and write PNG format.
	 * @tparam data_t Precision of data.
	 * @extends Libraries::PixelFactory::FileFormatInterface The base IO class.
	 */
	template< typename data_t = uint8_t, std::enable_if_t< std::is_integral_v< data_t >, bool > = false >
	class FileFormatPNG final : public FileFormatInterface< data_t >
	{
		public:

			/**
			 * @brief Constructs a PNG format IO.
			 */
			FileFormatPNG () noexcept = default;

			/** @copydoc Libraries::PixelFactory::FileFormatInterface::readFile() */
			[[nodiscard]]
			bool
			readFile (const Path::File & filepath, Pixmap< data_t > & pixmap) noexcept override
			{
				pixmap.clear();

#ifdef PNG_ENABLED
				/* NOTE: Based on PNG file read function from David HENRY. */
				auto result = false;

				/* FIXME: Use C++ stream. */
				auto * file = fopen(to_string(filepath).c_str(), "rb");

				if ( file != nullptr )
				{
					std::array< png_byte, 8 > signature{};

					/* Read signature and check it. */
					fread(signature.data(), 1, sizeof(signature), file);

					if ( png_check_sig(signature.data(), sizeof(signature)) )
					{
						/* create a png read struct. */
						auto * image = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

						if ( image != nullptr )
						{
							/* create a png info struct. */
							auto * headers = png_create_info_struct(image);

							if ( headers != nullptr )
							{
								/* setup PNG for using standard C fread() function with our FILE pointer. */
								png_init_io(image, file);

								/* tell PNG that we have already read the magic number. */
								png_set_sig_bytes(image, sizeof(signature));

								if ( setjmp(png_jmpbuf(image)) )
								{
									std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", PNG read failed !" "\n";
								}

								/* read png info */
								png_read_info(image, headers);

								auto width = png_get_image_width(image, headers);
								auto height = png_get_image_height(image, headers);
								auto bitDepth = png_get_bit_depth(image, headers);
								auto colorType = png_get_color_type(image, headers);

								/* convert index color images to RGB images */
								if ( colorType == PNG_COLOR_TYPE_PALETTE )
								{
									png_set_palette_to_rgb(image);
								}

								/* convert 1-2-4 bits grayscale images to 8 bits grayscale. */
								if ( colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8 )
								{
									png_set_expand_gray_1_2_4_to_8(image);
								}

								if ( png_get_valid(image, headers, PNG_INFO_tRNS) > 0 )
								{
									png_set_tRNS_to_alpha(image);
								}

								if ( bitDepth == 16 )
								{
									png_set_strip_16(image);
								}
								else if ( bitDepth < 8 )
								{
									png_set_packing(image);
								}

								/* update info structure to apply transformations */
								png_read_update_info(image, headers);

								auto pixmapAllocated = false;

								switch ( png_get_color_type(image, headers) )
								{
									case PNG_COLOR_TYPE_GRAY:
										pixmapAllocated = pixmap.initialize(width, height, ChannelMode::Grayscale);
										break;

									case PNG_COLOR_TYPE_GRAY_ALPHA:
										pixmapAllocated = pixmap.initialize(width, height, ChannelMode::GrayscaleAlpha);
										break;

									case PNG_COLOR_TYPE_RGB:
										pixmapAllocated = pixmap.initialize(width, height, ChannelMode::RGB);
										break;

									case PNG_COLOR_TYPE_RGB_ALPHA:
										pixmapAllocated = pixmap.initialize(width, height, ChannelMode::RGBA);
										break;

									default:
										/* Badness */
										break;
								}

								if ( pixmapAllocated )
								{
									/* Set up a pointer array. Each one points at the beginning of a row. */
									auto size = sizeof(png_bytep) * static_cast< size_t >(pixmap.height());

									/* FIXME: Use a vector */
									auto * rows = static_cast< png_bytepp >(malloc(size));

									for ( size_t y = 0; y < pixmap.height(); ++y )
									{
										const auto rowIndex = this->invertYAxis() ? static_cast< uint32_t >(pixmap.height() - 1 - y) : y;
										const auto offset = rowIndex * pixmap.width() * pixmap.colorCount();

										rows[y] = static_cast< png_bytep >(pixmap.data().data() + offset);
									}

									/* read pixel data using row pointers */
									png_read_image(image, rows);

									/* finish decompression and release memory */
									png_read_end(image, nullptr);

									/* we don't need row pointers anymore */
									free(rows);

									result = true;
								}
								else
								{
									std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", pixel data size is null !" "\n";
								}
							}

							png_destroy_read_struct(&image, &headers, nullptr);
						}
					}
					else
					{
						std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", " << filepath << " is not a PNG file !" "\n";
					}

					fclose(file);
				}
				else
				{
					std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", " << filepath << " cannot be read !" "\n";
				}

				return result;
#else
				std::cerr << "[DEBUG] " << __PRETTY_FUNCTION__ << ", LibPNG not available !" "\n";

				return false;
#endif
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

#ifdef PNG_ENABLED

				/* FIXME: Use C++ stream. */
				auto * file = fopen(to_string(filepath).c_str(), "wb");

				if ( file != nullptr )
				{
					/* WRITE HERE */
					png_structp png_ptr = nullptr;
					png_infop info_ptr = nullptr;

					png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);

					if ( png_ptr != nullptr )
					{
						info_ptr = png_create_info_struct(png_ptr);

						if ( info_ptr != nullptr )
						{
							/* Sets up error handling. */
							//if ( setjmp(png_jmpbuf(png_ptr)) )
							//	goto png_failure;
							auto colorType = 0;

							switch ( pixmap.channelMode() )
							{
								case ChannelMode::Grayscale :
									colorType = PNG_COLOR_TYPE_GRAY;
									break;

								case ChannelMode::GrayscaleAlpha :
									colorType = PNG_COLOR_TYPE_GRAY_ALPHA;
									break;

								case ChannelMode::RGB :
									colorType = PNG_COLOR_TYPE_RGB;
									break;

								case ChannelMode::RGBA :
									colorType = PNG_COLOR_TYPE_RGB_ALPHA;
									break;
							}

							png_set_IHDR(
								png_ptr,
								info_ptr,
								static_cast< png_uint_32 >(pixmap.width()),
								static_cast< png_uint_32 >(pixmap.height()),
								8,
								colorType,
								PNG_INTERLACE_NONE,
								PNG_COMPRESSION_TYPE_DEFAULT,
								PNG_FILTER_TYPE_DEFAULT
							);

							auto * row_pointers = static_cast< png_bytepp >(png_malloc(png_ptr, sizeof(png_voidp) * static_cast< size_t >(pixmap.height())));
							auto rowSize = sizeof(uint8_t) * static_cast< size_t >(pixmap.width()) * pixmap.colorCount();

							for ( size_t y = 0; y < pixmap.height(); ++y )
							{
								auto * rowData = static_cast< png_bytep >(png_malloc(png_ptr, rowSize));
								auto rowIndex = this->invertYAxis() ? static_cast< uint32_t >(pixmap.height() - 1 - y) : y;

								std::memcpy(rowData, pixmap.rowPointer(rowIndex), rowSize);

								row_pointers[y] = rowData;
							}

							png_init_io(png_ptr, file);
							png_set_rows(png_ptr, info_ptr, row_pointers);
							png_write_png(png_ptr, info_ptr, PNG_TRANSFORM_IDENTITY, nullptr);

							for ( size_t y = 0; y < pixmap.height(); y++ )
							{
								png_free(png_ptr, row_pointers[y]);
							}

							png_free(png_ptr, row_pointers);

							png_destroy_write_struct(&png_ptr, &info_ptr);
						}
					}

					fclose(file);

					return true;
				}

				return false;
#else
				std::cerr << "[DEBUG] " << __PRETTY_FUNCTION__ << ", LibPNG not available !" "\n";

				return false;
#endif
			}
	};

	// NOLINTEND(readability-identifier-length, *-magic-numbers)
}
