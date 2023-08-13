/*
 * Emeraude/Overlay/Elements/Text.cpp
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

#include "Text.hpp"

/* Local inclusions. */
#include "Graphics/Geometry/IndexedVertexResource.hpp"

namespace Emeraude::Overlay::Elements
{
	using namespace Libraries;

	Text::Text () noexcept
		: m_textWriter(&this->pixmap())
	{
		m_textWriter.enableWrapping(true);
		m_textWriter.enableAutoLineFeed(true);
		m_textWriter.enableScrollUp(true);
	}

	Graphics::TextWriter &
	Text::textWriter () noexcept
	{
		return m_textWriter;
	}

	void
	Text::setClearColor (const PixelFactory::Color< float > & color) noexcept
	{
		m_clearColor = color;
		m_textWriter.setClearColor(color);
	}

	const PixelFactory::Color< float > &
	Text::clearColor () const noexcept
	{
		return m_clearColor;
	}

	void
	Text::write (const std::string & text, bool clear) noexcept
	{
		/* Clear the text. */
		if ( clear )
			this->clear();

		/* Write the new one. */
		if ( m_textWriter.write(text, Graphics::TextWriter::Alignment::AtCursor) )
		{
			m_text += text;

			if ( m_textWriter.autoLineFeedEnabled() )
				m_text += "\n";
		}
		else
		{
			Tracer::error(ClassId, "Unable to write text !");
		}

		/* Tell the Renderer there is new data to upload to video memory. */
		this->drawFinished();
	}

	void
	Text::clear () noexcept
	{
		m_text.clear();

		this->pixmap().fill(m_clearColor);

		m_textWriter.resetCursorToOrigin();

		/* Tell Renderer there is new data to upload to video memory. */
		this->drawFinished();
	}

	const std::string &
	Text::text () const noexcept
	{
		return m_text;
	}
}
