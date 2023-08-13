/*
 * Libraries/PixelFactory/Font.hpp
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

/* C/C++ standard libraries */
#include <iostream>
#include <map>
#include <memory>
#include <sstream>
#include <string>

#include "Pixmap.hpp"

namespace Libraries::PixelFactory
{
	/**
	 * @brief The font class.
	 */
	class Font final
	{
		public:

			enum class FontType
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
			size_t size () const noexcept;

			/**
			 * @brief Returns the real size of the widest char in the font.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t maxWidth () const noexcept;

			/**
			 * @brief Returns the real size of the highest char in the font.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t maxHeight () const noexcept;

			/**
			 * @brief Returns the pixmap for the character.
			 * @param charSym
			 * @return const Pixmap< uint8_t > &
			 */
			[[nodiscard]]
			const Pixmap< uint8_t > & character (unsigned int charSym) const noexcept;

			/**
			 * @brief Reads a font file.
			 * @param filepath A reference to a string.
			 * @param size The font size.
			 * @return bool
			 */
			bool readFile (const std::string & filepath, size_t size = DefaultFontSize) noexcept;

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const Font & obj);

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const Font & obj) noexcept;

			/**
			 * @brief Converts a char to an integer.
			 * @param chr
			 * @return int
			 */
			static inline int charToInt (char chr) noexcept
			{
				auto character = static_cast< int >(chr);

				/* "char" is -127 to 127 */
				if ( character < 0 )
				{
					character += ASCIICount;
				}

				return character;
			}

		private:

			static constexpr auto DefaultFontSize{24};
			static constexpr auto ASCIICount{256};
			static constexpr auto FontMapDivisor{16};

			/**
			 * @brief Reads a font map.
			 * @param filepath A reference to a string.
			 * @return bool
			 */
			bool readPixmapFile (const std::string & filepath) noexcept;

			/**
			 * @brief Reads a TrueType font file.
			 * @param filepath A reference to a string.
			 * @return bool
			 */
			bool readTrueTypeFile (const std::string & filepath) noexcept;

			/**
			 * @brief Determines the type of a font file.
			 * @param filepath A reference to a string.
			 * @return FontType
			 */
			static FontType findFileType (const std::string & filepath) noexcept;

			size_t m_size{DefaultFontSize}; // NOLINT(*-magic-numbers)
			size_t m_maxWidth{0};
			size_t m_maxHeight{};
			std::array< Pixmap< uint8_t >, ASCIICount > m_glyphs{};
	};
}
