/*
 * src/Graphics/TextWriter.hpp
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
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

/* Local inclusions. */
#include "FontResource.hpp"
#include "Libs/Math/Vector.hpp"
#include "Libs/PixelFactory/Area.hpp"
#include "Libs/PixelFactory/Color.hpp"
#include "Libs/PixelFactory/Margin.hpp"
#include "Libs/PixelFactory/Pixmap.hpp"

namespace EmEn::Graphics
{
	/**
	 * @brief
	 * @extends EmEn::Libs::PixelFactory::Margin
	 */
	class TextWriter final : public Libs::PixelFactory::Margin< size_t >
	{
		public:

			enum class Alignment : uint8_t
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

			enum class SpaceAvailability : uint8_t
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

			TextWriter () noexcept = default;

			explicit TextWriter (Libs::PixelFactory::Pixmap< uint8_t > & target) noexcept;

			TextWriter (const TextWriter & copy) = delete;

			TextWriter (TextWriter && copy) = delete;

			TextWriter & operator= (const TextWriter & other) = delete;

			TextWriter & operator= (TextWriter && other) = delete;

			~TextWriter () override = default;

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

			void setTarget (Libs::PixelFactory::Pixmap< uint8_t > * target) noexcept;

			[[nodiscard]]
			Libs::PixelFactory::Pixmap< uint8_t > * target () const noexcept;

			void setFont (const std::shared_ptr< FontResource > & font) noexcept;

			[[nodiscard]]
			std::shared_ptr< FontResource > font () const noexcept;

			void setColor (const Libs::PixelFactory::Color< float > & color) noexcept;

			[[nodiscard]]
			const Libs::PixelFactory::Color< float > & color () const noexcept;

			void setClearColor (const Libs::PixelFactory::Color< float > & color) noexcept;

			[[nodiscard]]
			const Libs::PixelFactory::Color< float > & clearColor () const noexcept;

			template< typename number_t >
			void
			setCursorX (number_t coordX) noexcept requires (std::is_arithmetic_v< number_t >)
			{
				if constexpr ( std::is_integral_v< number_t > )
				{
					const auto _coordX = static_cast< int >(coordX);

					m_originCursor[Libs::Math::X] = _coordX;
					m_currentCursor[Libs::Math::X] = _coordX;
				}

				if constexpr ( std::is_floating_point_v< number_t > )
				{
					const auto _coordX = static_cast< int >(std::round(coordX));

					m_originCursor[Libs::Math::X] = _coordX;
					m_currentCursor[Libs::Math::X] = _coordX;
				}
			}

			template< typename number_t >
			void
			setCursorY (number_t coordY) noexcept requires (std::is_arithmetic_v< number_t >)
			{
				if constexpr ( std::is_integral_v< number_t > )
				{
					const auto _coordY = static_cast< int >(coordY);

					m_originCursor[Libs::Math::Y] = _coordY;
					m_currentCursor[Libs::Math::Y] = _coordY;
				}

				if constexpr ( std::is_floating_point_v< number_t > )
				{
					const auto _coordY = static_cast< int >(std::round(coordY));

					m_originCursor[Libs::Math::Y] = _coordY;
					m_currentCursor[Libs::Math::Y] = _coordY;
				}
			}

			template< typename number_t >
			void
			setCursor (number_t coordX, number_t coordY) noexcept requires (std::is_arithmetic_v< number_t >)
			{
				this->setCursorX(coordX);
				this->setCursorY(coordY);
			}

			template< typename number_t >
			void
			moveCursorX (number_t coordX) noexcept requires (std::is_arithmetic_v< number_t >)
			{
				if constexpr ( std::is_integral_v< number_t > )
				{
					m_currentCursor[Libs::Math::X] += static_cast< int >(coordX);
				}

				if constexpr ( std::is_floating_point_v< number_t > )
				{
					m_currentCursor[Libs::Math::X] += static_cast< int >(std::round(coordX));
				}
			}

			template< typename number_t >
			void
			moveCursorY (number_t coordY) noexcept requires (std::is_arithmetic_v< number_t >)
			{
				if constexpr ( std::is_integral_v< number_t > )
				{
					m_currentCursor[Libs::Math::Y] += static_cast< int >(coordY);
				}

				if constexpr ( std::is_floating_point_v< number_t > )
				{
					m_currentCursor[Libs::Math::Y] += static_cast< int >(std::round(coordY));
				}
			}

			template< typename number_t >
			void
			moveCursor (number_t coordX, number_t coordY) noexcept requires (std::is_arithmetic_v< number_t >)
			{
				this->moveCursorX(coordX);
				this->moveCursorY(coordY);
			}

			void resetCursorToOrigin () noexcept;

			[[nodiscard]]
			const Libs::Math::Vector< 2, int > & originCursor () const noexcept;

			[[nodiscard]]
			const Libs::Math::Vector< 2, int > & currentCursor () const noexcept;

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
			 * @return std::ostream &
			 */
			friend std::ostream & operator<< (std::ostream & out, const TextWriter & obj);

			/**
			 * Stringify the object.
			 *
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend std::string to_string (const TextWriter & obj) noexcept;

			static std::string ASCIITable () noexcept;

		private:

			[[nodiscard]]
			size_t
			OpenGLCursorY (size_t height) const noexcept
			{
				if ( m_target == nullptr )
				{
					return 0;
				}

				return (m_target->height() - (static_cast< size_t >(m_currentCursor[Libs::Math::Y]) + 1)) - (height - 1);
			}

			[[nodiscard]]
			Libs::PixelFactory::Area< size_t >
			getArea (const Libs::PixelFactory::Pixmap< uint8_t > & glyph) const noexcept
			{
				return {static_cast< size_t >(m_currentCursor[Libs::Math::X]), this->OpenGLCursorY(glyph.height()), glyph.width(), glyph.height()};
			}

			[[nodiscard]]
			SpaceAvailability isSpaceLeftFor (size_t glyphWidth, size_t glyphHeight) const noexcept;

			[[nodiscard]]
			std::pair< size_t, size_t > computeSpaceRequired (const std::string & text) const noexcept;

			bool executeCharacter (uint8_t ASCIICode) noexcept;

			bool renderGlyph (const Libs::PixelFactory::Pixmap< uint8_t > & glyph) noexcept;

			bool autoAlignCursor (Alignment alignment, const std::pair< size_t, size_t > & requestedSizes) noexcept;

			bool moveUp (size_t distance, const Libs::PixelFactory::Color< float > & color) noexcept;

			/* Flag names. */
			static constexpr auto WrappingEnabled{0UL};
			static constexpr auto AutoLineFeedEnabled{1UL};
			static constexpr auto ScrollUpEnabled{2UL};
			static constexpr auto AllCharactersEnabled{3UL};

			Libs::PixelFactory::Pixmap< uint8_t > * m_target{nullptr};
			std::shared_ptr< FontResource > m_font{};
			Libs::PixelFactory::Color< float > m_color{};
			Libs::PixelFactory::Color< float > m_clearColor{Libs::PixelFactory::Transparent};
			Libs::Math::Vector< 2, int > m_originCursor{};
			Libs::Math::Vector< 2, int > m_currentCursor{};
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
