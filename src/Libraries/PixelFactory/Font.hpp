/*
 * src/Libraries/PixelFactory/Font.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

/* Third-party inclusions. */
#ifdef FREETYPE_ENABLED
#include "ft2build.h"
#include FT_FREETYPE_H
#include FT_GLYPH_H
#endif

/* Local inclusions. */
#include "Pixmap.hpp"
#include "Area.hpp"
#include "Color.hpp"
#include "FileIO.hpp"
#include "Processor.hpp"
#include "Types.hpp"

namespace Libraries::PixelFactory
{
	/**
	 * @brief The font class.
	* @tparam precision_t The type of number for pixmap precision. Default uint8_t.
	 */
	template< typename precision_t = uint8_t >
	requires (std::is_arithmetic_v< precision_t >)
	class Font final
	{
		public:

			enum class FontType : uint8_t
			{
				None,
				PixmapFont,
				TrueTypeFont
			};

			/**
			 * @brief Constructs a default font.
			 */
			Font () noexcept = default;

			/**
			 * @brief Returns the font size.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			size () const noexcept
			{
				return m_size;
			}

			/**
			 * @brief Returns the real size of the widest char in the font.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			maxWidth () const noexcept
			{
				return m_maxWidth;
			}

			/**
			 * @brief Returns the real size of the highest char in the font.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			maxHeight () const noexcept
			{
				return m_maxHeight;
			}

			/**
			 * @brief Returns the pixmap for the character.
			 * @param ASCIICode ASCII code for the character.
			 * @return const Pixmap< precision_t > &
			 */
			[[nodiscard]]
			const Pixmap< precision_t > &
			glyph (uint8_t ASCIICode) const noexcept
			{
				return m_glyphs.at(ASCIICode);
			}

			/**
			 * @brief Reads a font file.
			 * @param filepath A reference to a filesystem path.
			 * @param size The font size. Default 24.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			readFile (const std::filesystem::path & filepath, size_t size = DefaultFontSize) noexcept
			{
				m_size = size;

				switch ( findFileType(filepath) )
				{
					case FontType::PixmapFont :
						return this->readPixmapFile(filepath);

					case FontType::TrueTypeFont :
						return this->readTrueTypeFile(filepath);

					case FontType::None :
						std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", the font file " << filepath << " is not handled !" "\n";

					return false;
				}

				return false;
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Font & obj)
			{
				out <<
					"Font data :" "\n"
					"Size : " << obj.m_size << "\n"
					"Widest character : " << obj.m_maxWidth << "\n"
					"Highest character : " << obj.m_maxHeight << "\n"
					"Glyphs :" "\n";

				for ( const auto & glyph : obj.m_glyphs )
				{
					out << glyph;
				}

				return out;
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Font & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

			/**
			 * @brief Converts a char to an integer.
			 * @tparam integer_t The type of integer to return the ASCII code.
			 * @param ASCII ASCII code for the character.
			 * @return integer_t
			 */
			template< typename integer_t = int32_t >
			static
			integer_t
			charToInt (char ASCII) noexcept
			{
				/* NOTE: First convert to an unsigned char. */
				return static_cast< integer_t >(static_cast< uint8_t >(ASCII));
			}

		private:

			/**
			 * @brief Reads a font map.
			 * @param filepath A reference to a filesystem path.
			 * @return bool
			 */
			bool
			readPixmapFile (const std::filesystem::path & filepath) noexcept
			{
				Pixmap< precision_t > charsMap;

				if ( !FileIO::read(filepath, charsMap) )
				{
					std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", can't load pixel data from " << filepath << " file !" "\n";

					return false;
				}

				if ( charsMap.bytes() == 0 )
				{
					std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", the pixmap " << filepath << " is empty !" "\n";

					return false;
				}

				if ( charsMap.width() % FontMapDivisor > 0 || charsMap.height() % FontMapDivisor > 0 )
				{
					std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", invalid chars map dimensions !" "\n";

					return false;
				}

				/* The available size in the font map */
				const auto charWidth = charsMap.width() / FontMapDivisor;
				const auto charHeight = charsMap.height() / FontMapDivisor;

				Area< size_t > clipping(0, 0, charWidth, charHeight);

				const auto ratio = static_cast< float >(charWidth) / static_cast< float >(charHeight);
				const auto rounded = std::round(static_cast< float >(m_size) * ratio);

				m_maxWidth = static_cast< size_t >(rounded);
				m_maxHeight = m_size;

				for ( size_t charNum = 0; charNum < ASCIICount; charNum++ )
				{
					const auto coordX = charNum % FontMapDivisor;
					//const auto coordY = 15 - ((charNum - coordX) / FontMapDivisor); // OpenGL
					const auto coordY = std::floor(charNum / FontMapDivisor); // Vulkan

					clipping.setOffsetX(coordX * charWidth);
					clipping.setOffsetY(coordY * charHeight);

					/* Crop the targeted char out of the bitmap and
					 * resize it as the desired size to the char storage. */
					m_glyphs.at(charNum) = Processor< precision_t >::resize(Processor< precision_t >::crop(charsMap, clipping), m_maxWidth, m_maxHeight);
				}

				return true;
			}

			/**
			 * @brief Reads a TrueType font file.
			 * @param filepath A reference to a filesystem path.
			 * @return bool
			 */
			bool
			readTrueTypeFile (const std::filesystem::path & filepath) noexcept
			{
#ifdef FREETYPE_ENABLED
				FT_Library library{};
				FT_Face face{};

				/* Try to init FreeType 2. */
				if ( FT_Init_FreeType(&library) > 0 )
				{
					std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", FreeType 2 init failed !" "\n";

					return false;
				}

				/* Load the font face. Face index 0 (always available). */
				if ( FT_New_Face(library, filepath.string().c_str(), 0, &face) > 0 )
				{
					std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", Font file " << filepath << " cannot be open !" "\n";

					return false;
				}

				/* Prepare output sizes. NOTE: 0 means square. */
				if ( FT_Set_Pixel_Sizes(face, 0, static_cast< FT_UInt >(m_size)) > 0 )
				{
					std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", the size request with this font is not available !" "\n";

					return false;
				}

				/* MaxWidth will be determined inside the loop. */
				m_maxWidth = 0;
				m_maxHeight = m_size;

				for ( size_t charNum = 0; charNum < ASCIICount; charNum++ )
				{
					/* Gets the correct glyph index inside the font for the iso code. */
					const auto glyphIndex = FT_Get_Char_Index(face, charNum);

					/* Gets the glyph loaded. NOTE : Only one font can be loaded at a time. */
					if ( FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER) > 0 )
					{
						std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", Glyph " << glyphIndex << " failed to load !" "\n";

						break;
					}

					const auto glyphWidth = face->glyph->bitmap.width;
					const auto glyphHeight = face->glyph->bitmap.rows;
					const auto size = glyphWidth * glyphHeight;

					if ( size > 0 )
					{
						auto newWidth = glyphWidth + 2;

						/* Checks for overflow */
						newWidth = std::min(newWidth, size);

						Pixmap glyph{};

						if ( glyph.initialize(glyphWidth, glyphHeight, ChannelMode::Grayscale) )
						{
							const auto bufferSize = static_cast< size_t >(face->glyph->bitmap.width * face->glyph->bitmap.rows) * sizeof(uint8_t);

							glyph.fill(face->glyph->bitmap.buffer, bufferSize);
						}
						else
						{
							continue;
						}

						/* Three cases :
							1. simple char as "m" 109
							2. low char as "p" (NOTE : bitmap_top <> bitmap.rows) 112
							3. high char as "f" 102
						*/

						/*
						switch ( charNum )
						{
							case 109 :
								std::cout << " m = rows:" << face->glyph->bitmap.rows << ", top:" << face->glyph->bitmap_top << " [" << glyph.getHeight() << "]" "\n";
								break;

							case 112 :
								std::cout << " p = rows:" << face->glyph->bitmap.rows << ", top:" << face->glyph->bitmap_top << " [" << glyph.getHeight() << "]" "\n";
								break;

							case 102 :
								std::cout << " f = rows:" << face->glyph->bitmap.rows << ", top:" << face->glyph->bitmap_top << " [" << glyph.getHeight() << "]" "\n";
								break;
						}
						*/

						const auto offsetY = (m_maxHeight - face->glyph->bitmap_top) - (m_maxHeight / 4);

						if ( offsetY > m_maxHeight )
						{
							continue;
						}

						/*
						int32_t offsetY = 0;
						if ( face->glyph->bitmap_top != face->glyph->bitmap.rows )
							offsetY = (m_maxHeight - face->glyph->bitmap_top) / 2;
						else
							offsetY = m_maxHeight - face->glyph->bitmap.rows;*/

						auto & currentGlyph = m_glyphs.at(charNum);

						currentGlyph.initialize(newWidth, m_maxHeight, ChannelMode::Grayscale);

						const Processor proc{currentGlyph};
						proc.blit(glyph, {1UL, static_cast< size_t >(offsetY), glyph.width(), glyph.height()});

						/* Sets the highest width of a char. */
						m_maxWidth = std::max< size_t >(newWidth, m_maxWidth);
					}
					else
					{
						auto currentGlyph = m_glyphs.at(charNum);

						/* Empty char. */
						currentGlyph.initialize(m_maxWidth / 2, m_maxHeight, ChannelMode::Grayscale);
						currentGlyph.fill(Color(0.0F, 0.0F, 0.0F));
					}
				}

				FT_Done_Face(face);
				FT_Done_FreeType(library);

				return true;
#else
				std::cerr << "[DEBUG] " << __PRETTY_FUNCTION__ << ", LibFreeType is not available ! Unable to save image to " << filepath << '\n';

				return false;
#endif
			}

			/**
			 * @brief Determines the type of the font file.
			 * @param filepath A reference to a filesystem path.
			 * @return FontType
			 */
			static
			FontType
			findFileType (const std::filesystem::path & filepath) noexcept
			{
				const auto extension = IO::getFileExtension(filepath, true);

				if ( extension == "ttf" )
				{
					return FontType::TrueTypeFont;
				}

				if ( extension == "bmp" )
				{
					return FontType::PixmapFont;
				}

				if ( extension == "tga" )
				{
					return FontType::PixmapFont;
				}

				if ( extension == "png" )
				{
					return FontType::PixmapFont;
				}

				if ( extension == "jpg" || extension == "jpeg" )
				{
					return FontType::PixmapFont;
				}

				return FontType::None;
			}

			static constexpr auto DefaultFontSize{24};
			static constexpr auto ASCIICount{256};
			static constexpr auto FontMapDivisor{16};

			size_t m_size{DefaultFontSize};
			size_t m_maxWidth{0};
			size_t m_maxHeight{0};
			std::array< Pixmap< precision_t >, ASCIICount > m_glyphs;
	};
}
