/*
 * Emeraude/Graphics/TextWriter.hpp
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
#include <string>
#include <sstream>

/* Local inclusions */
#include "FontResource.hpp"
#include "PixelFactory/Margin.hpp"

namespace Emeraude::Graphics
{
	class TextWriter final : public Libraries::PixelFactory::Margin< size_t >
	{
		public:

			enum class Alignment
			{
				TopLeft,
				TopCenter,
				TopRight,
				CenterLeft,
				Center,
				CenterRight,
				BottomLeft,
				BottomCenter,
				BottomRight,
				AtCursor
			};

			enum class SpaceAvailability
			{
				Yes,
				RequestNewLine,
				No
			};

			/** @brief Class identifier. */
			static constexpr auto ClassId{"TextWriter"};

			static constexpr auto LoremIpsum =
				"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Sed non risus. Suspendisse lectus tortor, dignissim sit amet, adipiscing nec, ultricies sed, dolor. Cras elementum ultrices diam. Maecenas ligula massa, varius a, semper congue, euismod non, mi. Proin porttitor, orci nec nonummy molestie, enim est eleifend mi, non fermentum diam nisl sit amet erat. Duis semper. Duis arcu massa, scelerisque vitae, consequat in, pretium a, enim. Pellentesque congue. Ut in risus volutpat libero pharetra tempor. Cras vestibulum bibendum augue. Praesent egestas leo in pede. Praesent blandit odio eu enim. Pellentesque sed dui ut augue blandit sodales. Vestibulum ante ipsum primis in faucibus orci luctus et ultrices posuere cubilia Curae; Aliquam nibh. Mauris ac mauris sed pede pellentesque fermentum. Maecenas adipiscing ante non diam sodales hendrerit.\n"
				"Ut velit mauris, egestas sed, gravida nec, ornare ut, mi. Aenean ut orci vel massa suscipit pulvinar. Nulla sollicitudin. Fusce varius, ligula non tempus aliquam, nunc turpis ullamcorper nibh, in tempus sapien eros vitae ligula. Pellentesque rhoncus nunc et augue. Integer id felis. Curabitur aliquet pellentesque diam. Integer quis metus vitae elit lobortis egestas. Lorem ipsum dolor sit amet, consectetuer adipiscing elit. Morbi vel erat non mauris convallis vehicula. Nulla et sapien. Integer tortor tellus, aliquam faucibus, convallis id, congue eu, quam. Mauris ullamcorper felis vitae erat. Proin feugiat, augue non elementum posuere, metus purus iaculis lectus, et tristique ligula justo vitae magna.\n"
				"Aliquam convallis sollicitudin purus. Praesent aliquam, enim at fermentum mollis, ligula massa adipiscing nisl, ac euismod nibh nisl eu lectus. Fusce vulputate sem at sapien. Vivamus leo. Aliquam euismod libero eu enim. Nulla nec felis sed leo placerat imperdiet. Aenean suscipit nulla in justo. Suspendisse cursus rutrum augue. Nulla tincidunt tincidunt mi. Curabitur iaculis, lorem vel rhoncus faucibus, felis magna fermentum augue, et ultricies lacus lorem varius purus. Curabitur eu amet.\n";

			/** Default constructor. */
			TextWriter (Libraries::PixelFactory::Pixmap< uint8_t > * target = nullptr) noexcept;

			/** Copy constructor. */
			TextWriter (const TextWriter & copy) = delete;

			/** Move constructor. */
			TextWriter (TextWriter && copy) = delete;

			/** Assignment operator. */
			TextWriter & operator= (const TextWriter & other) = delete;

			/** Move assignment operator. */
			TextWriter & operator= (TextWriter && other) = delete;

			[[nodiscard]]
			bool isReady () const noexcept;

			void enableWrapping (bool state) noexcept;

			[[nodiscard]]
			bool isWrappingEnabled () const noexcept;

			void enableAutoLineFeed (bool state) noexcept;

			[[nodiscard]]
			bool autoLineFeedEnabled () const noexcept;

			void enableScrollUp (bool state) noexcept;

			[[nodiscard]]
			bool isScrollUpEnabled () const noexcept;

			void enableAllCharacters (bool state) noexcept;

			[[nodiscard]]
			bool isAllCharactersEnabled () const noexcept;

			void setTarget (Libraries::PixelFactory::Pixmap< uint8_t > * target) noexcept;

			[[nodiscard]]
			Libraries::PixelFactory::Pixmap< uint8_t > * target () const noexcept;

			void setFont (const std::shared_ptr< FontResource > & font) noexcept;

			[[nodiscard]]
			std::shared_ptr< FontResource > font () const noexcept;

			void setColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & color () const noexcept;

			void setClearColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & clearColor () const noexcept;

			template< typename type_t >
			void
			setCursor (type_t x, type_t y) noexcept
			{
				auto _x = static_cast< int >(x);
				auto _y = static_cast< int >(y);

				m_originCursor[Libraries::Math::X] = _x;
				m_originCursor[Libraries::Math::Y] = _y;

				m_currentCursor[Libraries::Math::X] = _x;
				m_currentCursor[Libraries::Math::Y] = _y;
			}

			template< typename type_t >
			void
			setCursorX (type_t x) noexcept
			{
				auto _x = static_cast< int >(x);

				m_originCursor[Libraries::Math::X] = _x;

				m_currentCursor[Libraries::Math::X] = _x;
			}

			template< typename type_t >
			void
			setCursorY (type_t y) noexcept
			{
				auto _y = static_cast< int >(y);

				m_originCursor[Libraries::Math::Y] = _y;

				m_currentCursor[Libraries::Math::Y] = _y;
			}

			template< typename type_t >
			void
			moveCursor (type_t x, type_t y) noexcept
			{
				m_currentCursor[Libraries::Math::X] += static_cast< int >(x);
				m_currentCursor[Libraries::Math::Y] += static_cast< int >(y);
			}

			template< typename type_t >
			void
			moveCursorX (type_t x) noexcept
			{
				m_currentCursor[Libraries::Math::X] += static_cast< int >(x);
			}

			template< typename type_t >
			void
			moveCursorY (type_t y) noexcept
			{
				m_currentCursor[Libraries::Math::Y] += static_cast< int >(y);
			}

			void resetCursorToOrigin () noexcept;

			[[nodiscard]]
			const Libraries::Math::Vector< 2, int > & originCursor () const noexcept;

			[[nodiscard]]
			const Libraries::Math::Vector< 2, int > & currentCursor () const noexcept;

			void setSpacing (int spacing) noexcept;

			void lineFeed (size_t count = 1UL) noexcept;

			size_t write (const std::string & text, Alignment alignment = Alignment::AtCursor) noexcept;

			[[nodiscard]]
			size_t widthRequest (const std::string & text) const noexcept;

			/**
			 * STL streams printable object.
			 *
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const TextWriter & obj);

			/**
			 * Stringify the object.
			 *
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend std::string to_string (const TextWriter & obj) noexcept;

			static std::string ASCIITable () noexcept;

		private:

			/* Flag names. */
			static constexpr auto WrappingEnabled = 0UL;
			static constexpr auto AutoLineFeedEnabled = 1UL;
			static constexpr auto ScrollUpEnabled = 2UL;
			static constexpr auto AllCharactersEnabled = 3UL;

			[[nodiscard]]
			inline
			size_t
			OpenGLCursorY (size_t height) const noexcept
			{
				return (m_target->height() - (static_cast< size_t >(m_currentCursor[Libraries::Math::Y]) + 1)) - (height - 1);
			}

			[[nodiscard]]
			inline
			Libraries::PixelFactory::Area< size_t >
			getArea (const Libraries::PixelFactory::Pixmap< uint8_t > & glyph) const noexcept
			{
				return {static_cast< size_t >(m_currentCursor[Libraries::Math::X]), this->OpenGLCursorY(glyph.height()), glyph.width(), glyph.height()};
			}

			[[nodiscard]]
			SpaceAvailability isSpaceLeftFor (size_t glyphWidth, size_t glyphHeight) const noexcept;

			[[nodiscard]]
			std::pair< size_t, size_t > computeSpaceRequired (const std::string & text) const noexcept;

			bool executeCharacter (uint8_t ASCIICode) noexcept;

			bool renderGlyph (const Libraries::PixelFactory::Pixmap< uint8_t > & glyph) noexcept;

			bool autoAlignCursor (Alignment alignment, const std::pair< size_t, size_t > & requestedSizes) noexcept;

			bool moveUp (size_t distance, const Libraries::PixelFactory::Color< float > & color) noexcept;

			Libraries::PixelFactory::Pixmap< uint8_t > * m_target = nullptr;
			std::shared_ptr< FontResource > m_font{};
			Libraries::PixelFactory::Color< float > m_color{};
			Libraries::PixelFactory::Color< float > m_clearColor = Libraries::PixelFactory::Transparent;
			Libraries::Math::Vector< 2, int > m_originCursor{};
			Libraries::Math::Vector< 2, int > m_currentCursor{};
			int m_spacing = 0;
			std::array< bool, 8 > m_flags{
				false,/*WrappingEnabled*/
				false,/*AutoLineFeedEnabled*/
				false,/*ScrollUpEnabled*/
				false,/*AllCharactersEnabled*/
				false,/*UNUSED*/
				false,/*UNUSED*/
				false,/*UNUSED*/
				false/*Debug*/
			};
	};
}
