/*
 * src/Overlay/Elements/Input.cpp
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

#include "Input.hpp"

/* Local inclusions. */
#include "Libraries/PixelFactory/Processor.hpp"
#include "Input/Types.hpp"

namespace Emeraude::Overlay::Elements
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;

	Input::Input (const FramebufferProperties & framebufferProperties, const std::string & name, const Math::Rectangle< float > & geometry, float depth) noexcept
		: ComposedSurface(framebufferProperties, name, geometry, depth)//, m_textWriter(this->pixmap())
	{
		m_textWriter.enableWrapping(true);

		this->enablePointerListening(true);
		this->enableKeyboardListening(true);
	}

	bool
	Input::onKeyRelease (int key, int /*scancode*/, int /*modifiers*/) noexcept
	{
		switch ( key )
		{
			/* Process the current command. */
			case Emeraude::Input::KeyEnter :
			case Emeraude::Input::KeyPadEnter :
			case Emeraude::Input::KeyEscape :
				this->setFocusedState(false);

				return true;

			case Emeraude::Input::KeyBackspace :
				if ( !m_text.empty() )
				{
					m_text.pop_back();

					this->drawFinished();
				}

				return true;

			default:
				return false;
		}
	}

	bool
	Input::onCharacterType (uint32_t unicode) noexcept
	{
		if ( unicode >= 127 )
		{
			/* Out of range. */
			return false;
		}

		m_text += static_cast< char >(unicode);

		this->drawFinished();

		return true;
	}

	Graphics::TextWriter &
	Input::textWriter () noexcept
	{
		return m_textWriter;
	}

	void
	Input::setClearColor (const Color< float > & color) noexcept
	{
		m_clearColor = color;
		m_textWriter.setClearColor(color);
	}

	const Color< float > &
	Input::clearColor () const noexcept
	{
		return m_clearColor;
	}

	void
	Input::write (const std::string & text) noexcept
	{
		m_text = text;
	}

	void
	Input::clear () noexcept
	{
		m_text.clear();
	}

	const std::string &
	Input::text () const noexcept
	{
		return m_text;
	}

	bool
	Input::onDrawFinished (Pixmap< uint8_t > & pixmap) noexcept
	{
		/* Clean the background. */
		pixmap.fill(m_clearColor);

		/* Creates a border to identify the input box. */
		Processor proc{pixmap};
		proc.drawSquare(pixmap.area(), White);

		/* Rewrite the content. */
		if ( !m_text.empty() )
		{
			m_textWriter.resetCursorToOrigin();
			m_textWriter.write(m_text, Graphics::TextWriter::Alignment::AtCursor);
		}

		return true;
	}
}
