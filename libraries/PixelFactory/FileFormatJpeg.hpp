/*
 * Libraries/PixelFactory/FileFormatJpeg.hpp
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
#include <cstring>
#include <iostream>

/* Local inclusions for inheritances. */
#include "FileFormatInterface.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/jpeg.hpp"

namespace Libraries::PixelFactory
{
	/**
	 * @brief Class for read and write JPEG format.
	 * @tparam data_t Precision of data.
	 * @extends Libraries::PixelFactory::FileFormatInterface The base IO class.
	 */
	template< typename data_t = uint8_t, std::enable_if_t< std::is_integral_v< data_t >, bool > = false >
	class FileFormatJpeg final : public FileFormatInterface< data_t >
	{
		public:

			/**
			 * @brief Constructs a JPEG format IO.
			 */
			FileFormatJpeg () noexcept = default;

			/** @copydoc Libraries::PixelFactory::FileFormatInterface::readFile() */
			[[nodiscard]]
			bool
			readFile (const Path::File & filepath, Pixmap< data_t > & pixmap) noexcept override
			{
				pixmap.clear();

#ifdef JPEG_ENABLED
				auto loaded = false;

				/* FIXME: Use C++ stream. */
				auto * file = fopen(to_string(filepath).c_str(), "rb");

				if ( file != nullptr )
				{
					struct jpeg_decompress_struct info{};
					struct jpeg_error_mgr error{};

					info.err = jpeg_std_error(&error);

					jpeg_create_decompress(&info);

					jpeg_stdio_src(&info, file);

					/* This does not really read header. */
					jpeg_read_header(&info, 1);
					jpeg_start_decompress(&info);

#ifdef DEBUG_PIXEL_FACTORY
					std::cout <<
						"[Jpeg_DEBUG] Reading header." << '\n' <<
						"\tWidth : " << info.output_width << '\n' <<
						"\tHeight : " << info.output_height << '\n' <<
						"\tComponents : " << info.output_components << '\n' <<
					std::endl;
#endif

					auto pixmapAllocated = false;

					switch ( info.output_components )
					{
						case 1:
							pixmapAllocated = pixmap.initialize(info.output_width, info.output_height, ChannelMode::Grayscale);
							break;

						case 2:
							pixmapAllocated = pixmap.initialize(info.output_width, info.output_height, ChannelMode::GrayscaleAlpha);
							break;

						case 3:
							pixmapAllocated = pixmap.initialize(info.output_width, info.output_height, ChannelMode::RGB);
							break;

						case 4:
							pixmapAllocated = pixmap.initialize(info.output_width, info.output_height, ChannelMode::RGBA);
							break;

						default:
							/* Badness */
							break;
					}

					if ( pixmapAllocated )
					{
						if ( this->invertYAxis() )
						{
							auto rowIndex = static_cast< size_t >(info.output_height - 1);

							while (info.output_scanline < info.output_height )
							{
								auto rowData = pixmap.rowPointer(rowIndex);

								jpeg_read_scanlines(&info, &rowData, 1);

								rowIndex--;
							}
						}
						else
						{
							size_t rowIndex = 0;

							while (info.output_scanline < info.output_height )
							{
								auto rowData = pixmap.rowPointer(rowIndex);

								jpeg_read_scanlines(&info, &rowData, 1);

								rowIndex++;
							}
						}

						loaded = true;
					}

					jpeg_finish_decompress(&info);
					jpeg_destroy_decompress(&info);

					fclose(file);
				}

				return loaded;
#else
				std::cerr << "[DEBUG] " << __PRETTY_FUNCTION__ << ", LibJPEG not available !" "\n";

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

#ifdef JPEG_ENABLED

				if ( pixmap.colorCount() != 3 && pixmap.colorCount() != 1 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", only rgb and grayscale format is supported for now !" "\n";

					return false;
				}

				/* FIXME: Use C++ stream. */
				auto * file = fopen(to_string(filepath).c_str(), "wb");

				if ( file != nullptr )
				{
					struct jpeg_compress_struct info{};
					struct jpeg_error_mgr error{};

					info.err = jpeg_std_error(&error);
					jpeg_create_compress(&info);
					jpeg_stdio_dest(&info, file);

					info.image_width = static_cast< JDIMENSION >(pixmap.width());
					info.image_height = static_cast< JDIMENSION >(pixmap.height());

					switch ( pixmap.channelMode() )
					{
						case ChannelMode::RGB :
						case ChannelMode::RGBA :
							info.input_components = 3;
							info.in_color_space = JCS_RGB;
							break;

						case ChannelMode::Grayscale :
						case ChannelMode::GrayscaleAlpha :
							info.input_components = 1;
							info.in_color_space = JCS_GRAYSCALE;
							break;
					}

#ifdef DEBUG_PIXEL_FACTORY
					std::cout <<
						"[Jpeg_DEBUG] Writing header." << '\n' <<
						"\tWidth : " << info.image_width << '\n' <<
						"\tHeight : " << info.image_height << '\n' <<
						"\tComponents : " << info.input_components << '\n' <<
					std::endl;
#endif

					jpeg_set_defaults(&info);

					jpeg_set_quality(&info, m_quality > 100 ? 100 : m_quality, 1); // NOLINT(*-magic-numbers)
					jpeg_start_compress(&info, 1);

					if ( this->invertYAxis() )
					{
						auto rowIndex = static_cast< size_t >(pixmap.height() - 1);

						while (info.next_scanline < info.image_height )
						{
							auto * rowData = (JSAMPROW)pixmap.rowPointer(rowIndex);

							jpeg_write_scanlines(&info, &rowData, 1);

							rowIndex--;
						}
					}
					else
					{
						size_t rowIndex = 0;

						while (info.next_scanline < info.image_height )
						{
							auto * rowData = (JSAMPROW)pixmap.rowPointer(rowIndex);

							jpeg_write_scanlines(&info, &rowData, 1);

							rowIndex++;
						}
					}

					jpeg_finish_compress(&info);
					jpeg_destroy_compress(&info);

					fclose(file);

					return true;
				}

				return false;
#else
				std::cerr << "[DEBUG] " << __PRETTY_FUNCTION__ << ", LibJPEG not available !" "\n";

				return false;
#endif
			}

			/**
			 * @brief Sets the JPEG compression quality.
			 * @param value A value from 0 to 100.
			 * @return void
			 */
			void
			setQuality (int value) noexcept
			{
				// NOLINTBEGIN(*-magic-numbers)
				if ( value > 100 )
				{ 
					m_quality = 100;
				}
				else if ( value < 0 )
				{ 
					m_quality = 0; 
				}
				else
				{ 
					m_quality = value; 
				}
				// NOLINTEND(*-magic-numbers)
			}

			/**
			 * @brief Returns the JPEG compression quality.
			 * @return int
			 */
			[[nodiscard]]
			int
			getQuality () const noexcept
			{
				return m_quality;
			}

		private:

			int m_quality{75}; // NOLINT(*-magic-numbers)
	};
}
