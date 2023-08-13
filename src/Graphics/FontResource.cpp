/*
 * Emeraude/Graphics/FontResource.cpp
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

#include "FontResource.hpp"

/* Local inclusions */
#include "PixelFactory/FileIO.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/freetype.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::FontResource >::ClassId{"FontContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::FontResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics
{
	using namespace Libraries;
	using namespace Libraries::PixelFactory;

	const size_t FontResource::ClassUID{Observable::getClassUID()};

	FontResource::FontResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	bool
	FontResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	const char *
	FontResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	FontResource::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		Pixmap font;

		const auto defaultSize = 32UL;

		if ( !font.initialize(defaultSize, defaultSize, ChannelMode::RGBA) )
			return false;

		font.noise();

		return this->setLoadSuccess(this->parseBitmap(font, defaultSize));
	}

	bool
	FontResource::load (const Path::File & filepath) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		const auto defaultSize = 32UL;

		if ( filepath.hasExtension("ttf") || filepath.hasExtension("TTF") )
			return this->setLoadSuccess(this->parseFontFile(filepath, defaultSize));

		if ( filepath.hasExtension(".bmp") || filepath.hasExtension(".BMP") )
			return this->setLoadSuccess(this->parseBitmap(filepath, defaultSize));

		if ( filepath.hasExtension(".tga") || filepath.hasExtension(".TGA") )
			return this->setLoadSuccess(this->parseBitmap(filepath, defaultSize));

		if ( filepath.hasExtension(".png") || filepath.hasExtension(".PNG") )
			return this->setLoadSuccess(this->parseBitmap(filepath, defaultSize));

		if ( filepath.hasExtension(".jpg") || filepath.hasExtension(".JPG") || filepath.hasExtension(".jpeg") || filepath.hasExtension(".JPEG") )
			return this->setLoadSuccess(this->parseBitmap(filepath, defaultSize));

		return this->setLoadSuccess(false);
	}

	bool
	FontResource::load (const Json::Value &) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		Tracer::warning(ClassId, "FIXME: This function is not available yet !");

		return this->setLoadSuccess(false);
	}

	const
	Pixmap< uint8_t > &
	FontResource::glyph (uint8_t ASCIICode) const noexcept
	{
		return m_glyphs[ASCIICode];
	}

	size_t
	FontResource::spacing () const noexcept
	{
		return m_spacing;
	}

	size_t
	FontResource::lineHeight () const noexcept
	{
		return m_lineHeight;
	}

	void
	FontResource::debug (const char * debugPath) const noexcept
	{
		auto code = 0UL;

		for ( const auto & glyphPixmap : m_glyphs  )
		{
			const Path::File filepath{(std::stringstream{} << debugPath << glyphPixmap << '-' << code << ".png").str()};

			if ( !FileIO::write(glyphPixmap, filepath) )
				return;

			code++;
		}
	}

	Area< size_t >
	FontResource::getUsableWidth (const Pixmap< uint8_t > & glyph) const noexcept
	{
		Area clip;

		clip.setHeight(glyph.height());

		/* Gets the first column of pixels where a color changes. */
		for ( size_t x = 0; x < glyph.width(); x++ )
		{
			auto goOn = true;

			for ( size_t y = 0; y < glyph.height(); y++ )
			{
				if ( glyph.pixelPointer(x, y)[0] > 0 )
				{
					clip.setOffsetX(x);
					//clip.setWidth(glyph.width() - x);

					goOn = false;

					break;
				}
			}

			if ( !goOn )
				break;
		}

		/* Gets the last column of pixels where a color is present. */
		for ( auto x = glyph.width() - 1; x > 0UL; x-- )
		{
			auto goOn = true;

			for ( size_t y = 0; y < glyph.height(); y++ )
			{
				if ( glyph.pixelPointer(x, y)[0] > 0 )
				{
					clip.setWidth(x - clip.offsetX() + 1);

					goOn = false;

					break;
				}
			}

			if ( !goOn )
				break;
		}

		if ( !clip.isValid() )
			return {clip.width(), clip.height()};

		return clip;
	}

	bool
	FontResource::parseBitmap (const Path::File & filepath, size_t desiredHeight) noexcept
	{
		using namespace PixelFactory;

		Pixmap map{};

		if ( !FileIO::read(filepath, map) )
		{
			TraceError{ClassId} << "Can't load pixel data from '" << filepath << "' file !";

			return false;
		}

		return this->parseBitmap(map, desiredHeight);
	}

	bool
	FontResource::parseBitmap (const Pixmap< uint8_t > & map, size_t) noexcept
	{
		using namespace PixelFactory;

		auto fixedFont = true;

		if ( map.bytes() == 0 )
		{
			Tracer::error(ClassId, Blob() << "The Pixmap is empty !");

			return false;
		}

		if ( map.width() % 16 || map.height() % 16 )
		{
			Tracer::error(ClassId, Blob() << "Invalid glyphs map dimensions !");

			return false;
		}

		/* The available size in the chars map */
		const auto width = map.width() / 16UL;
		const auto height = map.height() / 16UL;

		Area clipping{width, height};

		Pixmap rawGlyph{};

		for ( auto glyphIt = m_glyphs.begin(); glyphIt != m_glyphs.end(); ++glyphIt )
		{
			auto ASCIICode = std::distance(m_glyphs.begin(), glyphIt);

			auto x = ASCIICode % 16;

			clipping.setOffsetX(static_cast< size_t >(x) * width);
			clipping.setOffsetY(static_cast< size_t >(15 - ((ASCIICode - x) / 16)) * height);

			if ( fixedFont )
			{
				*glyphIt = Processor< uint8_t >::crop(map, clipping);
			}
			else
			{
				rawGlyph = Processor< uint8_t >::crop(map, clipping);

				*glyphIt = Processor< uint8_t >::crop(rawGlyph, FontResource::getUsableWidth(rawGlyph));
			}
		}

		m_lineHeight = height;
		m_spacing = fixedFont ? m_lineHeight : m_lineHeight / 2;

		return true;
	}

	bool
	FontResource::parseFontFile (const Path::File & filepath, size_t desiredHeight) noexcept
	{
		using namespace PixelFactory;

#ifdef FREETYPE_ENABLED
		FT_Library library;
		FT_Face face;

		/* Try to init FreeType 2. */
		if ( FT_Init_FreeType(&library) > 0 )
		{
			Tracer::error(ClassId, Blob() << "FreeType 2 initialization failed !");

			return false;
		}

		/* Load the font face. Face index 0 (always available). */
		if ( FT_New_Face(library, to_string(filepath).c_str(), 0, &face) > 0 )
		{
			Tracer::error(ClassId, Blob() << "Can't load '" << filepath << "' font file !");

			return false;
		}

		/* Prepare output sizes. */
		if ( FT_Set_Pixel_Sizes(face, 0, static_cast< FT_UInt >(desiredHeight)) > 0 )
		{
			Tracer::error(ClassId, Blob() << "The size " << desiredHeight << " with this font is not available !");

			return false;
		}

		for ( auto glyphIt = m_glyphs.begin(); glyphIt != m_glyphs.end(); ++glyphIt )
		{
			const auto ASCIICode = static_cast< size_t >(std::distance(m_glyphs.begin(), glyphIt));

			/* Gets the correct glyph index inside the font for the ascii code. */
			const auto glyphIndex = FT_Get_Char_Index(face, ASCIICode);

			/* Gets the glyph loaded.
			 * NOTE : Only one glyph can be loaded at a time. FT_LOAD_RENDER */
			if ( FT_Load_Glyph(face, glyphIndex, FT_LOAD_RENDER) > 0 )
			{
				Tracer::error(ClassId, Blob() << "Glyph " << glyphIndex << " failed to load !");

				break;
			}

			/* Gets the font glyph size. */
			const auto width = face->glyph->bitmap.width;
			const auto height = face->glyph->bitmap.rows;

			Pixmap rawGlyph;

			if ( rawGlyph.initialize(width, height, ChannelMode::Grayscale) )
			{
				/* Copy the buffer. */
				rawGlyph.fill(face->glyph->bitmap.buffer, width * height * sizeof(uint8_t));

				if ( glyphIt->initialize(width, desiredHeight, ChannelMode::Grayscale) )
				{
					const size_t y = desiredHeight - static_cast< size_t >(face->glyph->bitmap_top) - (desiredHeight / 4);

					Processor proc{*glyphIt};
					proc.blit(rawGlyph, {0UL, y, width, height});
					proc.mirror(MirrorMode::X);
				}
			}
			else
			{
				Tracer::error(ClassId, "Unable to prepare a temporary Pixmap !");

				continue;
			}
		}

		FT_Done_Face(face);

		FT_Done_FreeType(library);

		m_lineHeight = desiredHeight;
		m_spacing = m_lineHeight / 2;

		return true;
#else
		Tracer::debug(ClassId, "LibFreeType is not available !");

		return false;
#endif
	}

	bool
	FontResource::onDependenciesLoaded () noexcept
	{
		return true;
	}

	std::shared_ptr< FontResource >
	FontResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->fonts().getResource(resourceName, directLoad);
	}

	std::shared_ptr< FontResource >
	FontResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->fonts().getDefaultResource();
	}
}
