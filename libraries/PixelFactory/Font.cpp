/*
 * Libraries/PixelFactory/Font.cpp
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

#include "Font.hpp"

/* C/C++ standard libraries. */
#include <iostream>
#include <sstream>

/* Local inclusions */
#include "FileIO.hpp"
#include "Processor.hpp"
#include "Utility.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/freetype.hpp"

namespace Libraries::PixelFactory
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay, readability-identifier-length)

	Font::FontType
	Font::findFileType (const std::string & filepath) noexcept
	{
		if ( filepath.find(".ttf") != std::string::npos || filepath.find(".TTF") != std::string::npos )
		{
			return FontType::TrueTypeFont;
		}

		if ( filepath.find(".bmp") != std::string::npos || filepath.find(".BMP") != std::string::npos )
		{
			return FontType::PixmapFont;
		}

		if ( filepath.find(".tga") != std::string::npos || filepath.find(".TGA") != std::string::npos )
		{
			return FontType::PixmapFont;
		}

		if ( filepath.find(".png") != std::string::npos || filepath.find(".PNG") != std::string::npos )
		{
			return FontType::PixmapFont;
		}

		if ( filepath.find(".jpg") != std::string::npos || filepath.find(".JPG") != std::string::npos || filepath.find(".jpeg") != std::string::npos || filepath.find(".JPEG") != std::string::npos )
		{
			return FontType::PixmapFont;
		}

		return FontType::None;
	}

	bool
	Font::readPixmapFile (const std::string & filepath) noexcept
	{
		using namespace PixelFactory;

		Pixmap< uint8_t > charsMap{};

		if ( !FileIO::read(Path::File{filepath}, charsMap) )
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
			const auto x = charNum % FontMapDivisor;
			const auto y = 15 - ( (charNum - x) / FontMapDivisor );

			clipping.setOffsetX(x * charWidth);
			clipping.setOffsetY(y * charHeight);

			/* Crop the targeted char out of the bitmap and
			 * resize it as the desired size to the char storage. */
			m_glyphs.at(charNum) = Processor< uint8_t >::resize(Processor< uint8_t >::crop(charsMap, clipping), m_maxWidth, m_maxHeight);
		}

		return true;
	}

	bool
	Font::readTrueTypeFile (const std::string & filepath) noexcept
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
		if ( FT_New_Face(library, filepath.c_str(), 0, &face) > 0 )
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
			auto glyphIndex = FT_Get_Char_Index(face, charNum);

			/* Gets the glyph loaded. NOTE : Only one font can be loaded at a time. */
			if ( FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER) > 0 )
			{
				std::cerr << "[ERROR] " << __PRETTY_FUNCTION__ << ", Glyph " << glyphIndex << " failed to load !" "\n";

				break;
			}

			auto glyphWidth = face->glyph->bitmap.width;
			auto glyphHeight = face->glyph->bitmap.rows;

			auto size = glyphWidth * glyphHeight;

			if ( size > 0 )
			{
				auto newWidth = glyphWidth + 2;

				/* Checks for overflow */
				if ( newWidth > size )
				{
					newWidth = size;
				}

				Pixmap glyph{};

				if ( glyph.initialize(glyphWidth, glyphHeight, ChannelMode::Grayscale) )
				{
					auto bufferSize = static_cast< size_t >(face->glyph->bitmap.width * face->glyph->bitmap.rows) * sizeof(uint8_t);

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

				auto offsetY = (m_maxHeight - face->glyph->bitmap_top) - (m_maxHeight / 4);

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
				if ( newWidth > m_maxWidth )
				{
					m_maxWidth = newWidth;
				}
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
		std::cerr << "[DEBUG] " << __PRETTY_FUNCTION__ << ", LibFreeType is not available ! Unable to save image to " << filepath << std::endl;

		return false;
#endif
	}

	size_t
	Font::size () const noexcept
	{
		return m_size;
	}

	size_t
	Font::maxWidth () const noexcept
	{
		return m_maxWidth;
	}

	size_t
	Font::maxHeight () const noexcept
	{
		return m_maxHeight;
	}

	const Pixmap< uint8_t > &
	Font::character (unsigned int charSym) const noexcept
	{
		return m_glyphs.at(charSym);
	}

	bool
	Font::readFile (const std::string & filepath, size_t size) noexcept
	{
		m_size = size;

		switch ( this->findFileType(filepath) )
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

	std::ostream &
	operator<< (std::ostream & out, const Font & obj)
	{
		out <<
			"Font data :\n"
			"Size : " << obj.m_size << "\n"
			"Widest character : " << obj.m_maxWidth << "\n"
			"Highest character : " << obj.m_maxHeight << "\n"
			"Glyphs :\n";

		for ( const auto & glyph : obj.m_glyphs )
		{
			out << glyph;
		}

		return out;
	}

	std::string
	to_string (const Font & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}

	// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay, readability-identifier-length)
}
