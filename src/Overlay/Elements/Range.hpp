/*
 * Emeraude/Overlay/Elements/Range.hpp
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
	class Range final : public Surface
	{
		public:

			/** Default constructor. */
			Range () noexcept;

			/**
			 * Gives acces to the TextWriter for configuration.
			 *
			 * @warning  Don't use it to write on the surface.
			 * @return TextWriter &
			 */
			Graphics::TextWriter & textWriter () noexcept;

			void setValue (float value) noexcept;

			[[nodiscard]]
			float value () const noexcept;

		private:

			bool onResize (const Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept final;

			bool onDrawFinished (Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept final;

			Graphics::TextWriter m_textWriter;
			float m_value = 0.1F;
	};
}
