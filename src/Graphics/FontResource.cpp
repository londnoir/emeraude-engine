/*
 * src/Graphics/FontResource.cpp
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

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <cstddef>
#include <cstdint>
#include <iterator>
#include <memory>
#include <string>

/* Third-party inclusions. */
#ifdef FREETYPE_ENABLED
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H
#endif

/* Local inclusions. */
#include "Libraries/PixelFactory/Area.hpp"
#include "Libraries/PixelFactory/FileIO.hpp"
#include "Libraries/PixelFactory/Pixmap.hpp"
#include "Libraries/PixelFactory/Processor.hpp"
#include "Libraries/PixelFactory/Types.hpp"
#include "FontResource.hpp"
#include "Resources/Container.hpp"
#include "Resources/Manager.hpp"
#include "Resources/ResourceTrait.hpp"
#include "Tracer.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::FontResource >::ClassId{"FontContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::FontResource >::ClassUID{getClassUID(ClassId)};

namespace Emeraude::Graphics
{
	using namespace Libraries;
	using namespace Libraries::PixelFactory;

	const size_t FontResource::ClassUID{getClassUID(ClassId)};

	FontResource::FontResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	size_t
	FontResource::classUID () const noexcept
	{
		return ClassUID;
	}

	bool
	FontResource::is (size_t classUID) const noexcept
	{
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
		{
			return false;
		}

		Pixmap font{};

		if ( !font.initialize(DefaultSize, DefaultSize, ChannelMode::RGBA) )
		{
			return false;
		}

		font.noise();

		return this->setLoadSuccess(this->parseBitmap(font, DefaultSize));
	}

	bool
	FontResource::load (const std::filesystem::path & filepath) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		const auto extension = IO::getFileExtension(filepath, true);

		if ( extension == "ttf" )
		{
			return this->setLoadSuccess(this->parseFontFile(filepath, DefaultSize));
		}

		if ( extension == "bmp" )
		{
			return this->setLoadSuccess(this->parseBitmap(filepath, DefaultSize));
		}

		if ( extension == "tga" )
		{
			return this->setLoadSuccess(this->parseBitmap(filepath, DefaultSize));
		}

		if ( extension == "png" )
		{
			return this->setLoadSuccess(this->parseBitmap(filepath, DefaultSize));
		}

		if ( extension == "jpg"  || extension == "jpeg" )
		{
			return this->setLoadSuccess(this->parseBitmap(filepath, DefaultSize));
		}

		return this->setLoadSuccess(false);
	}

	bool
	FontResource::load (const Json::Value & /*data*/) noexcept
	{
		if ( !this->beginLoading() )
		{
			return false;
		}

		Tracer::warning(ClassId, "FIXME: This function is not available yet !");

		return this->setLoadSuccess(false);
	}

	const
	Pixmap< uint8_t > &
	FontResource::glyph (uint8_t ASCIICode) const noexcept
	{
		return m_glyphs.at(ASCIICode);
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
			std::stringstream filename;
			filename << glyphPixmap << '-' << code << ".png";

			std::filesystem::path filepath{debugPath};
			filepath.append(filename.str());

			if ( !FileIO::write(glyphPixmap, filepath) )
			{
				return;
			}

			code++;
		}
	}

	Area< size_t >
	FontResource::getUsableWidth (const Pixmap< uint8_t > & glyph) noexcept
	{
		Area clip{};

		clip.setHeight(glyph.height());

		/* Gets the first column of pixels where a color changes. */
		for ( size_t coordX = 0; coordX < glyph.width(); coordX++ )
		{
			auto goOn = true;

			for ( size_t coordY = 0; coordY < glyph.height(); coordY++ )
			{
				const auto * pixels = glyph.pixelPointer(coordX, coordY);

				if ( pixels[0] > 0 )
				{
					clip.setOffsetX(coordX);
					//clip.setWidth(glyph.width() - x);

					goOn = false;

					break;
				}
			}

			if ( !goOn )
			{
				break;
			}
		}

		/* Gets the last column of pixels where a color is present. */
		for ( size_t coordX = glyph.width() - 1; coordX > 0UL; coordX-- )
		{
			auto goOn = true;

			for ( size_t coordY = 0; coordY < glyph.height(); coordY++ )
			{
				const auto * pixels = glyph.pixelPointer(coordX, coordY);

				if ( pixels[0] > 0 )
				{
					clip.setWidth(coordX - clip.offsetX() + 1);

					goOn = false;

					break;
				}
			}

			if ( !goOn )
			{
				break;
			}
		}

		if ( !clip.isValid() )
		{
			return {clip.width(), clip.height()};
		}

		return clip;
	}

	bool
	FontResource::parseBitmap (const std::filesystem::path & filepath, size_t desiredHeight) noexcept
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
	FontResource::parseBitmap (const Pixmap< uint8_t > & map, size_t /*desiredHeight*/) noexcept
	{
		using namespace PixelFactory;

		auto fixedFont = true;

		if ( map.bytes() == 0 )
		{
			Tracer::error(ClassId, BlobTrait() << "The Pixmap is empty !");

			return false;
		}

		if ( map.width() % BitmapSection != 0 || map.height() % BitmapSection != 0 )
		{
			Tracer::error(ClassId, BlobTrait() << "Invalid glyphs map dimensions !");

			return false;
		}

		/* The available size in the chars map */
		const auto width = map.width() / BitmapSection;
		const auto height = map.height() / BitmapSection;

		Area clipping{width, height};

		Pixmap rawGlyph{};

		for ( auto glyphIt = m_glyphs.begin(); glyphIt != m_glyphs.end(); ++glyphIt )
		{
			const auto ASCIICode = std::distance(m_glyphs.begin(), glyphIt);

			const auto coordX = ASCIICode % BitmapSection;

			clipping.setOffsetX(coordX * width);
			clipping.setOffsetY((BitmapSection - 1 - (ASCIICode - coordX) / BitmapSection) * height);

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
	FontResource::parseFontFile (const std::filesystem::path & filepath, size_t desiredHeight) noexcept
	{
		using namespace PixelFactory;

#ifdef FREETYPE_ENABLED
		FT_Library library;
		FT_Face face;

		/* Try to init FreeType 2. */
		if ( FT_Init_FreeType(&library) > 0 )
		{
			Tracer::error(ClassId, BlobTrait() << "FreeType 2 initialization failed !");

			return false;
		}

		/* Load the font face. Face index 0 (always available). */
		if ( FT_New_Face(library, filepath.string().c_str(), 0, &face) > 0 )
		{
			Tracer::error(ClassId, BlobTrait() << "Can't load '" << filepath << "' font file !");

			return false;
		}

		/* Prepare output sizes. */
		if ( FT_Set_Pixel_Sizes(face, 0, static_cast< FT_UInt >(desiredHeight)) > 0 )
		{
			Tracer::error(ClassId, BlobTrait() << "The size " << desiredHeight << " with this font is not available !");

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
				Tracer::error(ClassId, BlobTrait() << "Glyph " << glyphIndex << " failed to load !");

				break;
			}

			/* Gets the font glyph size. */
			const auto width = face->glyph->bitmap.width;
			const auto height = face->glyph->bitmap.rows;

			Pixmap rawGlyph;

			if ( !rawGlyph.initialize(width, height, ChannelMode::Grayscale) )
			{
				Tracer::error(ClassId, "Unable to prepare a temporary Pixmap !");

				continue;
			}

			/* Copy the buffer. */
			rawGlyph.fill(face->glyph->bitmap.buffer, width * height * sizeof(uint8_t));

			if ( glyphIt->initialize(width, desiredHeight, ChannelMode::Grayscale) )
			{
				const auto coordY = desiredHeight - static_cast< size_t >(face->glyph->bitmap_top) - desiredHeight / 4;

				Processor proc{*glyphIt};
				proc.blit(rawGlyph, {0UL, coordY, width, height});
				proc.mirror(MirrorMode::X);
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
		return Resources::Manager::instance()->fonts().getResource(resourceName, !directLoad);
	}

	std::shared_ptr< FontResource >
	FontResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->fonts().getDefaultResource();
	}
}
