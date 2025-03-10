/*
 * src/Libraries/PixelFactory/TextProcessor.hpp
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

/* STL inclusions. */
#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>

/* Local inclusions for usages. */
#include "Pixmap.hpp"
#include "Font.hpp"

namespace Libraries::PixelFactory
{
	struct TextMetrics
	{
		size_t lineHeight{0};
		size_t lineSpace{0};
		size_t maxColumns{0};
		size_t maxRows{0};
	};

	/**
	 * @brief The text processor is used to write on the targeted pixmap.
	 * @tparam precision_t A numeric type to define the depth precision of pixel.
	 */
	template< typename precision_t = uint8_t >
	requires (std::is_arithmetic_v< precision_t >)
	class TextProcessor final
	{
		public:

			/**
			 * @brief Constructs a processor on a pixmap.
			 */
			TextProcessor () noexcept = default;

			/**
			 * @brief Constructs a processor on a pixmap.
			 * @param pixmap A reference to a target pixmap.
			 */
			explicit
			TextProcessor (Pixmap< precision_t > & pixmap) noexcept
				: m_pixmap(&pixmap), m_area(pixmap.area())
			{

			}

			/**
			 * @brief Sets the target pixmap to write on.
			 * @param pixmap A reference to a pixmap.
			 * @return bool
			 */
			bool
			setPixmap (Pixmap< precision_t > & pixmap) noexcept
			{
				if ( !pixmap.isValid() )
				{
					return false;
				}

				m_pixmap = &pixmap;
				m_area = pixmap.area();

				return true;
			}

			void
			setArea (const Area< size_t > & area) noexcept
			{
				m_area = area;

				this->updateMetrics();
			}

			[[nodiscard]]
			const Area< size_t > &
			area () const noexcept
			{
				return m_area;
			}

			/**
			 * @brief Sets a font to write on the pixmap.
			 * @param font A reference to a font smart point.
			 * @return void
			 */
			void
			setFont (const std::shared_ptr< Font< precision_t > > & font) noexcept
			{
				m_font = font;

				this->updateMetrics();
			}

			/**
			 * @brief Returns the font smart pointer.
			 * @return const std::shared_ptr< Font< precision_t > > &
			 */
			[[nodiscard]]
			const std::shared_ptr< Font< precision_t > > &
			font () const noexcept
			{
				return m_font;
			}

			/**
			 * @brief Sets the font color.
			 * @param color A reference to a color.
			 * @return void
			 */
			void
			setFontColor (const Color< float > & color) noexcept
			{
				m_fontColor = color;
			}

			/**
			 * @brief Returns the font color.
			 * @return const Color< float > &
			 */
			[[nodiscard]]
			const Color< float > &
			fontColor () const noexcept
			{
				return m_fontColor;
			}

			/**
			 * @brief Set the mode to print characters on the pixmap.
			 * @param mode The draw pixel mode.
			 * @return void
			 */
			void
			setDrawMode (DrawPixelMode mode) noexcept
			{
				m_mode = mode;
			}

			/**
			 * @brief Returns the mode to prind characters on the pixmap.
			 * @return DrawPixelMode
			 */
			[[nodiscard]]
			DrawPixelMode
			setDrawMode () const noexcept
			{
				return m_mode;
			}

			/**
			 * @brief Set space between lines.
			 * @param lineSpace The space.
			 * @return void
			 */
			void
			setLineSpace (size_t lineSpace) noexcept
			{
				m_textMetrics.lineSpace = lineSpace;

				this->updateMetrics();
			}

			/**
			 * @brief Returns the current lince space.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			lineSpace () const noexcept
			{
				return m_textMetrics.lineSpace;
			}

			/**
			 * @brief Writes a text on the pixmap with the font and color setup.
			 * @param text A reference to a string.
			 * @return bool
			 */
			bool
			write (const std::string & text) noexcept
			{
				if ( m_pixmap == nullptr || !m_area.isValid() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", the area is not valid !" "\n";

					return false;
				}

				if ( m_font == nullptr )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", there is no font !" "\n";

					return false;
				}

				/* Text buffer position. */
				size_t currentChar = 0;

				for ( size_t currentRow = 0; currentRow < m_textMetrics.maxRows; currentRow++ )
				{
					size_t currentColumn = 0;

					for ( ; currentChar < text.size(); currentChar++ )
					{
						auto chr = text.at(currentChar);

						/* NOTE: Check for a new line feed. */
						if ( chr == '\n' )
						{
							currentColumn = 0;

							currentChar++;

							break;
						}

						/* NOTE: Check for spaces special cases. */
						if ( chr == ' ' )
						{
							/* NOTE: Do not print a space at a begining of a line. */
							if ( currentColumn == 0 )
							{
								continue;
							}

							/* NOTE: Check if the next word can fit in the row. */
							const auto nextSeparator = text.find_first_of(' ', currentChar + 1);

							if ( nextSeparator != std::string::npos )
							{
								const auto nextWordLength = nextSeparator - currentChar;
								const auto spaceLeft = m_textMetrics.maxColumns - currentColumn;

								if ( nextWordLength < m_textMetrics.maxColumns && spaceLeft < nextWordLength )
								{
									break;
								}
							}
						}

						this->printCharacter(chr, currentColumn, currentRow);

						currentColumn++;

						if ( currentColumn >= m_textMetrics.maxColumns )
						{
							currentColumn = 0;
							currentChar++;

							break;
						}
					}

					/* NOTE: No more text to print. */
					if ( currentChar >= text.size() )
					{
						break;
					}
				}

				return true;
			}

		private:

			/**
			 * @brief Prints a character on the pixmap.
			 * @param chr The ASCII code.
			 * @param column The column inside the area.
			 * @param row The row inside the area.
			 * @return bool
			 */
			bool
			printCharacter (char chr, size_t column, size_t row) noexcept
			{
				const auto & glyph = m_font->glyph(chr);

				const Area< size_t > glyphArea = glyph.area(
					m_area.offsetX() + (column * m_font->maxWidth()),
					m_area.offsetY() + (row * m_textMetrics.lineHeight)
				);

				for ( size_t coordX = 0; coordX < glyphArea.width(); coordX++ )
				{
					for ( size_t coordY = 0; coordY < glyphArea.height(); coordY++ )
					{
						if constexpr ( std::is_floating_point_v< precision_t > )
						{
							m_pixmap->blendPixel(
								glyphArea.offsetX() + coordX,
								glyphArea.offsetY() + coordY,
								m_fontColor,
								m_mode,
								glyph.pixelElement(coordX, coordY, Channel::Red)
							);
						}
						else
						{
							const auto value = static_cast< float >(glyph.pixelElement(coordX, coordY, Channel::Red)) / static_cast< float >(std::numeric_limits< precision_t >::max());

							m_pixmap->blendPixel(
								glyphArea.offsetX() + coordX,
								glyphArea.offsetY() + coordY,
								m_fontColor,
								m_mode,
								value
							);
						}
					}
				}

				return true;
			}

			/**
			 * @brief Computes line heigt and line available on the pixmap.
			 * @return void
			 */
			void
			updateMetrics () noexcept
			{
				if ( !m_area.isValid() || m_font == nullptr )
				{
					return;
				}

				m_textMetrics.lineHeight = m_font->maxHeight() + m_textMetrics.lineSpace;

				m_textMetrics.maxColumns = std::floor(m_area.width() / m_font->maxWidth());
				m_textMetrics.maxRows = std::floor(m_area.height() / m_textMetrics.lineHeight);
			}

			Pixmap< precision_t > * m_pixmap{nullptr};
			Area< size_t > m_area;
			std::shared_ptr< Font< precision_t > > m_font;
			Color< float > m_fontColor = White;
			DrawPixelMode m_mode{DrawPixelMode::Normal};
			TextMetrics m_textMetrics;
	};
}
