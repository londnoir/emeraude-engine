/*
 * src/Overlay/Elements/Picture.hpp
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
#include "Overlay/ComposedSurface.hpp"

namespace Emeraude::Overlay::Elements
{
	/**
	 * @brief The picture element.
	 * @extends Emeraude::Overlay::ComposedSurface This a visible element.
	 */
	class Picture final : public ComposedSurface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Picture"};

			enum class Alignment
			{
				FitToSurface
			};

			/**
			 * @brief Constructs a picture.
			 * @param framebufferProperties A reference to the overlay framebuffer properties.
			 * @param name A reference to a string.
			 * @param geometry A reference to a rectangle for the surface geometry on screen. Default the whole screen.
			 * @param depth A depth value to order surface on the screen. Default 0.0.
			 */
			Picture (const FramebufferProperties & framebufferProperties, const std::string & name, const Libraries::Math::Rectangle< float > & geometry = {}, float depth = 0.0F) noexcept;

			/** Sets an image and an alignment as the background of this surface. */
			void setImage (const std::shared_ptr< Graphics::ImageResource > & image, Alignment alignment = Alignment::FitToSurface) noexcept;

			[[nodiscard]]
			std::shared_ptr< Graphics::ImageResource > image () const noexcept;

			void setOpacity (float value) noexcept;

			[[nodiscard]]
			float opacity () const noexcept;

		private:

			bool onDrawFinished (Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept override;

			std::shared_ptr< Graphics::ImageResource > m_image{};
			float m_opacity = 1.0F;
			Alignment m_alignment = Alignment::FitToSurface;
	};
}
