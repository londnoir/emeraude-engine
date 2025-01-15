/*
 * src/Overlay/Elements/Range.hpp
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
#include <cstdint>
#include <string>

/* Local inclusions for inheritances. */
#include "../ComposedSurface.hpp"
#include "Graphics/TextWriter.hpp"
#include "Libraries/Math/Rectangle.hpp"

namespace Emeraude::Overlay::Elements
{
	/**
	 * @brief The range element.
	 * @extends Emeraude::Overlay::ComposedSurface This a visible element.
	 */
	class Range final : public ComposedSurface
	{
		public:

			/**
			 * @brief Constructs a range.
			 * @param name A reference to a string.
			 * @param geometry A reference to a rectangle for the sufarce geometry on screen. Default the whole screen.
			 * @param depth A depth value to order surface on the screen. Default 0.0.
			 */
			explicit Range (const std::string & name, const Libraries::Math::Rectangle< float > & geometry = {}, float depth = 0.0F) noexcept;

			/**
			 * @brief Gives acces to the TextWriter for configuration.
			 * @warning  Don't use it to write on the surface.
			 * @return Graphics::TextWriter &
			 */
			Graphics::TextWriter & textWriter () noexcept;

			/**
			 * @brief Sets the range value.
			 * @param value A float from 0.0 to 1.0
			 * @return void
			 */
			void setValue (float value) noexcept;

			/**
			 * @brief Returns the range value between 0.0 and 1.0.
			 * @return float
			 */
			[[nodiscard]]
			float value () const noexcept;

		private:
		
			/**
			 * @brief 
			 * @param pixmap A reference to a pixmap.
			 * @return bool
			 */
			bool onResize (const Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept override;

			/**
			 * @brief 
			 * @param pixmap A reference to a pixmap.
			 * @return bool
			 */
			bool onDrawFinished (Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept override;

			Graphics::TextWriter m_textWriter;
			float m_value{0.0F};
	};
}
