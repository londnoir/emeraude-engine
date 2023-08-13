/*
 * Emeraude/Graphics/FontResource.hpp
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
#include <string>

/* Local inclusions */
#include "PixelFactory/Pixmap.hpp"
#include "Resources/Container.hpp"
#include "Resources/ResourceTrait.hpp"

namespace Emeraude::Graphics
{
	/**
	 * @brief The font resource class.
	 * @extends Emeraude::Resources::ResourceTrait This is a loadable resource.
	 */
	class FontResource final : public Resources::ResourceTrait
	{
		friend class Resources::Container< FontResource >;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"FontResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a font resource.
			 * @param name A reference to a string for resource name.
			 * @param resourceFlagBits The resource flag bits. Default none. (Unused yet)
			 */
			explicit FontResource (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Libraries::Path::File &) */
			bool load (const Libraries::Path::File & filepath) noexcept override;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Returns a pixmap of the glyph.
			 * @param ASCIICode The ascii code of the character.
			 * @return const Libraries::PixelFactory::Pixmap< uint8_t > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Pixmap< uint8_t > & glyph (uint8_t ASCIICode) const noexcept;

			/**
			 * @brief Returns the spacing in pixel.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t spacing () const noexcept;

			/**
			 * @brief Returns the line height in pixel.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t lineHeight () const noexcept;

			/**
			 * @brief debug
			 * @param debugPath
			 */
			void debug (const char * debugPath) const noexcept;

			/**
			 * @brief Returns a font resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< FontResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< FontResource > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default font resource.
			 * @return std::shared_ptr< FontResource >
			 */
			[[nodiscard]]
			static std::shared_ptr< FontResource > getDefault () noexcept;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;

			/**
			 * @brief getUsableWidth
			 * @param glyph
			 * @return Libraries::PixelFactory::Area< size_t >
			 */
			[[nodiscard]]
			Libraries::PixelFactory::Area< size_t > getUsableWidth (const Libraries::PixelFactory::Pixmap< uint8_t > & glyph) const noexcept;

			/**
			 * @brief Parses a bitmap to create the font.
			 * @param filepath A reference to file.
			 * @param desiredHeight The height of the font.
			 * @return bool
			 */
			bool parseBitmap (const Libraries::Path::File & filepath, size_t desiredHeight) noexcept;

			/**
			 * @brief Parses a bitmap to create the font.
			 * @param map A reference to a pixmap.
			 * @param desiredHeight The height of the font.
			 * @return bool
			 */
			bool parseBitmap (const Libraries::PixelFactory::Pixmap< uint8_t > & map, size_t desiredHeight) noexcept;

			/**
			 * @brief Parses a font file to create the font.
			 * @param filepath A reference to a file.
			 * @param desiredHeight The height of the font.
			 * @return bool
			 */
			bool parseFontFile (const Libraries::Path::File & filepath, size_t desiredHeight) noexcept;

			std::array< Libraries::PixelFactory::Pixmap< uint8_t >, 256 > m_glyphs;
			size_t m_lineHeight = 0UL;
			size_t m_spacing = 0UL;
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Fonts = Container< Graphics::FontResource >;
}
