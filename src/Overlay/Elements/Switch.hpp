/*
 * Emeraude/Overlay/Elements/Switch.hpp
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

namespace Emeraude::Overlay::Elements
{
	/**
	 * @brief The switch form element.
	 * @extends Emeraude::Overlay::Surface This a visible element.
	 * @extends Emeraude::Overlay::Elements::UIInputInterface The is an user input element.
	 */
	class Switch final : public Surface, public UIInputInterface
	{
		public:

			/** Default constructor. */
			Switch () noexcept;

			void onPointerEnter (float x, float y) noexcept override;

			void onPointerLeave (float x, float y) noexcept override;

			void onButtonPress (float x, float y, int buttonNumber, int mods) noexcept override;

			void onButtonRelease (float x, float y, int buttonNumber, int mods) noexcept override;

			void setImage (const std::shared_ptr< Graphics::ImageResource > & image) noexcept;

			[[nodiscard]]
			std::shared_ptr< Graphics::ImageResource > image () const noexcept;

			void toggle () noexcept;

			void setState (bool state) noexcept;

			[[nodiscard]]
			bool state () const noexcept;

		private:

			bool onDrawFinished (Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept final;

			std::shared_ptr< Graphics::ImageResource > m_image{};
			Status m_status = Status::Normal;
			bool m_state = false;
	};
}
