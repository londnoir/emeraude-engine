/*
 * src/Overlay/Elements/Switch.hpp
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
#include <array>
#include <cstdint>
#include <memory>

/* Local inclusions for inheritances. */
#include "Overlay/ComposedSurface.hpp"
#include "Interface.hpp"

namespace Emeraude::Overlay::Elements
{
	/**
	 * @brief The switch form element.
	 * @extends Emeraude::Overlay::ComposedSurface This a visible element.
	 * @extends Emeraude::Overlay::Elements::UIInputInterface this is a user input element.
	 */
	class Switch final : public ComposedSurface, public UIInputInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Switch"};

			/**
			 * @brief Constructs a switch.
			 * @param framebufferProperties A reference to the overlay framebuffer properties.
			 * @param name A reference to a string.
			 * @param geometry A reference to a rectangle for the surface geometry on screen. Default the whole screen.
			 * @param depth A depth value to order surface on the screen. Default 0.0.
			 */
			Switch (const FramebufferProperties & framebufferProperties, const std::string & name, const Libraries::Math::Rectangle< float > & geometry = {}, float depth = 0.0F) noexcept;

			/** @copydoc Emeraude::Overlay::AbstractSurface::onPointerEnter() */
			void onPointerEnter (float positionX, float positionY) noexcept override;

			/** @copydoc Emeraude::Overlay::AbstractSurface::onPointerLeave() */
			void onPointerLeave (float positionX, float positionY) noexcept override;

			/** @copydoc Emeraude::Overlay::AbstractSurface::onButtonPress() */
			bool onButtonPress (float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept override;

			/** @copydoc Emeraude::Overlay::AbstractSurface::onButtonRelease() */
			bool onButtonRelease (float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept override;

			/**
			 * @brief Sets the background image of the switch.
			 * @param image A reference to an image resource smart pointer.
			 * @return void
			 */
			void
			setImage (const std::shared_ptr< Graphics::ImageResource > & image) noexcept
			{
				m_image = image;
			}

			/**
			 * @brief Returns the background image of the switch.
			 * @return std::shared_ptr< Graphics::ImageResource >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::ImageResource >
			image () const noexcept
			{
				return m_image;
			}

			/**
			 * @brief Toggles the switch state.
			 * @return void
			 */
			void toggle () noexcept;

			/**
			 * @brief Set the stage of the switch.
			 * @param state The state.
			 * @return void
			 */
			void setState (bool state) noexcept;

			/**
			 * @brief Returns the state of the switch.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			state () const noexcept
			{
				return m_state;
			}

		private:

			/**
			 * @brief Declares the draw finished on the surface.
			 * @param pixmap A reference to a pixmap.
			 * @return bool
			 */
			bool onDrawFinished (Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept override;

			std::shared_ptr< Graphics::ImageResource > m_image{};
			Status m_status = Status::Normal;
			bool m_state = false;
	};
}
