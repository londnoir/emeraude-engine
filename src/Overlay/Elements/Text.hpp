/*
 * src/Overlay/Elements/Text.hpp
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

#pragma once

/* STL inclusions. */
#include <string>

/* Local inclusions for inheritances. */
#include "../ComposedSurface.hpp"

/* Local inclusions for usages. */
#include "Graphics/TextWriter.hpp"
#include "Libraries/PixelFactory/Color.hpp"
#include "Libraries/Math/Rectangle.hpp"

namespace Emeraude::Overlay::Elements
{
	/**
	 * @brief The text element.
	 * @extends Emeraude::Overlay::ComposedSurface This a visible element.
	 */
	class Text final : public ComposedSurface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"UIText"};

			/**
			 * @brief Constructs a text.
			 * @param name A reference to a string.
			 * @param geometry A reference to a rectangle for the sufarce geometry on screen. Default the whole screen.
			 * @param depth A depth value to order surface on the screen. Default 0.0.
			 */
			explicit Text (const std::string & name, const Libraries::Math::Rectangle< float > & geometry = {}, float depth = 0.0F) noexcept;

			/**
			 * @brief Gives acces to the TextWriter for configuration.
			 * @warning  Don't use it to write on the surface.
			 * @return TextWriter &
			 */
			[[nodiscard]]
			Graphics::TextWriter & textWriter () noexcept;

			/**
			 * @brief Sets the default color of the background of the surface.
			 * @param color A reference to a color.
			 */
			void setClearColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * @brief Returns the clear color.
			 * @return const Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & clearColor () const noexcept;

			/**
			 * @brief Write a new text on the surface.
			 * @param text A reference to a string.
			 * @param clear Clear before writting. Default false.
			 * @return void
			 */
			void write (const std::string & text, bool clear = false) noexcept;

			/**
			 * @brief Replaces the whole surface pixmap with the clear color. And clear the text value equivalent.
			 * @return void
			 */
			void clear () noexcept;

			/**
			 * @brief Returns the text currently held by the surface.
			 * @return const std::string &
			 */
			[[nodiscard]]
			const std::string & text () const noexcept;

		private:

			Libraries::PixelFactory::Color< float > m_clearColor{Libraries::PixelFactory::Transparent};
			std::string m_text{};
			Graphics::TextWriter m_textWriter{};
	};
}
