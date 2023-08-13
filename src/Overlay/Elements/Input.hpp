/*
 * Emeraude/Overlay/Elements/Input.hpp
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
#include "Interface.hpp"
#include "Graphics/TextWriter.hpp"

namespace Emeraude::Overlay::Elements
{
	/**
	 * @brief The input form element.
	 * @extends Emeraude::Overlay::Surface This a visible element.
	 * @extends Emeraude::Overlay::Elements::UIInputInterface The is an user input element.
	 */
	class Input final : public Surface, public UIInputInterface
	{
		public:

			/**
			 * @brief Default constructor.
			 */
			Input () noexcept;

			void onKeyPress (int key, int scanCode, int modifiers, bool repeat) noexcept override;

			void onKeyRelease (int key, int scanCode, int modifiers) noexcept override;

			void onCharacterType (unsigned int unicode, int modifiers) noexcept override;

			/**
			 * Gives acces to the TextWriter for configuration.
			 *
			 * @warning  Don't use it to write on the surface.
			 * @return TextWriter &
			 */
			Graphics::TextWriter & textWriter () noexcept;

			/**
			 * Sets the default color of the background of the surface.
			 *
			 * @param color A reference to the color.
			 */
			void setClearColor (const Libraries::PixelFactory::Color< float > & color) noexcept;

			/**
			 * Returns the clear color.
			 *
			 * @return const Color< float > &
			 */
			[[nodiscard]]
			const Libraries::PixelFactory::Color< float > & clearColor () const noexcept;

			/** Sets the initial content of the input box. */
			void write (const std::string & text) noexcept;

			/** Cleat the content of the input box. */
			void clear () noexcept;

			/** Returns the text currently held by the surface. */
			[[nodiscard]]
			const std::string & text () const noexcept;

		private:

			bool onDrawFinished (Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept final;

			Libraries::PixelFactory::Color< float > m_clearColor = Libraries::PixelFactory::Transparent;
			std::string m_text{};
			Graphics::TextWriter m_textWriter{};
	};
}
