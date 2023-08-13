/*
 * Emeraude/Overlay/Elements/Picture.hpp
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

namespace Emeraude::Overlay::Elements
{
	class Picture final : public Surface
	{
		public:

			enum class Alignment
			{
				FitToSurface
			};

			/** Default constructor. */
			Picture () noexcept = default;

			/** Sets an image and an alignment as the background of this surface. */
			void setImage (const std::shared_ptr< Graphics::ImageResource > & image, Alignment alignment = Alignment::FitToSurface) noexcept;

			[[nodiscard]]
			std::shared_ptr< Graphics::ImageResource > image () const noexcept;

			void setOpacity (float value) noexcept;

			[[nodiscard]]
			float opacity () const noexcept;

		private:

			bool onDrawFinished (Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept final;

			std::shared_ptr< Graphics::ImageResource > m_image{};
			float m_opacity = 1.0F;
			Alignment m_alignment = Alignment::FitToSurface;
	};
}
