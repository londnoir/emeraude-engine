/*
 * Emeraude/Overlay/Elements/Text.hpp
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

/* Local inclusions for inheritances. */
#include "../Surface.hpp"
#include "Graphics/TextWriter.hpp"

namespace Emeraude::Overlay::Elements
{
	class Text final : public Surface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"UIText"};

			/** Default constructor. */
			Text () noexcept;

			/**
			 * Gives acces to the TextWriter for configuration.
			 *
			 * @warning  Don't use it to write on the surface.
			 * @return TextWriter &
			 */
			[[nodiscard]]
			Graphics::TextWriter & textWriter () noexcept;

			/**
			 * Sets the default color of the background of the surface.
			 *
			 * @param color A reference to a color.
			 */
			void setClearColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * Returns the clear color.
			 *
			 * @return const Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & clearColor () const noexcept;

			/**
			 * Write a new text on the surface.
			 *
			 * @param text A reference to a string.
			 * @param bool Clear before writting. Default false.
			 */
			void write (const std::string & text, bool clear = false) noexcept;

			/** Replace the whole surface pixmap with the clear color. And clear the text value equivalent. */
			void clear () noexcept;

			/**
			 * Returns the text currently held by the surface.
			 *
			 * @return const string &
			 */
			[[nodiscard]]
			const std::string & text () const noexcept;

		private:

			Libraries::PixelFactory::Color< float > m_clearColor = Libraries::PixelFactory::Transparent;
			std::string m_text{};
			Graphics::TextWriter m_textWriter{};
	};
}
