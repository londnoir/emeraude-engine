/*
 * Emeraude/Overlay/Elements/Range.cpp
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

#include "Range.hpp"

/* Local inclusions. */
#include "Graphics/Geometry/IndexedVertexResource.hpp"
#include "PixelFactory/Processor.hpp"

namespace Emeraude::Overlay::Elements
{
	using namespace Libraries;
	using namespace Libraries::PixelFactory;

	Range::Range () noexcept
		: m_textWriter(&this->pixmap())
	{

	}

	Graphics::TextWriter &
	Range::textWriter () noexcept
	{
		return m_textWriter;
	}

	void
	Range::setValue (float value) noexcept
	{
		m_value = Math::clampToUnit(value);

		this->drawFinished();
	}

	float
	Range::value () const noexcept
	{
		return m_value;
	}

	bool
	Range::onResize (const Pixmap< uint8_t > & /*pixmap*/) noexcept
	{
		return true;
	}

	bool
	Range::onDrawFinished (Pixmap< uint8_t > & pixmap) noexcept
	{
		pixmap.zeroFill();

		Processor proc{pixmap};
		proc.drawSquare(pixmap.area(), White);

		const auto width = static_cast< size_t >((pixmap.width() - 6) * m_value);

		if ( width > 0 )
		{
			if ( !proc.copy(Green, {3UL, 3UL, width, pixmap.height() - 6UL}) )
			{
				return false;
			}
		}

		if ( m_value < 1.0F )
		{
			if ( !proc.copy(TranslucentBlack, {3UL + width, 3UL, (pixmap.width() - 6) - width, pixmap.height() - 6UL}) )
			{
				return false;
			}
		}

		m_textWriter.write(std::to_string(100 * m_value) + " %", Graphics::TextWriter::Alignment::Center);

		return true;
	}
}
