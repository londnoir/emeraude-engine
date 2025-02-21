/*
 * src/Overlay/Elements/Range.cpp
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

#include "Range.hpp"

/* Local inclusions. */
#include "Libraries/PixelFactory/Processor.hpp"

namespace Emeraude::Overlay::Elements
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;

	Range::Range (const FramebufferProperties & framebufferProperties, const std::string & name, const Math::Rectangle< float > & geometry, float depth) noexcept
		: ComposedSurface(framebufferProperties, name, geometry, depth)//, m_textWriter(this->pixmap())
	{

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

		const auto width = static_cast< size_t >(static_cast< float >(pixmap.width() - 6UL) * m_value);

		if ( width > 0 )
		{
			if ( !proc.copy(Green, {3UL, 3UL, width, pixmap.height() - 6UL}) )
			{
				return false;
			}
		}

		if ( m_value < 1.0F )
		{
			if ( !proc.copy(TranslucentBlack, {3UL + width, 3UL, (pixmap.width() - 6UL) - width, pixmap.height() - 6UL}) )
			{
				return false;
			}
		}

		m_textWriter.write(std::to_string(100 * m_value) + " %", Graphics::TextWriter::Alignment::Center);

		return true;
	}
}
