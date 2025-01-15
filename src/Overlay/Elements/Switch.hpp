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
#include "../ComposedSurface.hpp"
#include "Interface.hpp"
#include "Libraries/Math/Rectangle.hpp"

namespace Emeraude::Overlay::Elements
{
	/**
	 * @brief The switch form element.
	 * @extends Emeraude::Overlay::ComposedSurface This a visible element.
	 * @extends Emeraude::Overlay::Elements::UIInputInterface The is an user input element.
	 */
	class Switch final : public ComposedSurface, public UIInputInterface
	{
		public:

			/**
			 * @brief Constructs a switch.
			 * @param name A reference to a string.
			 * @param geometry A reference to a rectangle for the surface geometry on screen. Default the whole screen.
			 * @param depth A depth value to order surface on the screen. Default 0.0.
			 */
			explicit Switch (const std::string & name, const Libraries::Math::Rectangle< float > & geometry = {}, float depth = 0.0F) noexcept;

			/** @copydoc Emeraude::Overlay::AbstractSurface::onPointerEnter() */
			void onPointerEnter (const FramebufferProperties & framebufferProperties, float positionX, float positionY) noexcept override;

			/** @copydoc Emeraude::Overlay::AbstractSurface::onPointerLeave() */
			void onPointerLeave (const FramebufferProperties & framebufferProperties, float positionX, float positionY) noexcept override;

			/** @copydoc Emeraude::Overlay::AbstractSurface::onButtonPress() */
			bool onButtonPress (const FramebufferProperties & framebufferProperties, float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept override;

			/** @copydoc Emeraude::Overlay::AbstractSurface::onButtonRelease() */
			bool onButtonRelease (const FramebufferProperties & framebufferProperties, float positionX, float positionY, int32_t buttonNumber, int32_t modifiers) noexcept override;

			/**
			 * @brief Sets the background image of the switch.
			 * @param image A reference to an image resource smart pointer.
			 * @return void
			 */
			void setImage (const std::shared_ptr< Graphics::ImageResource > & image) noexcept;

			/**
			 * @brief Returns the background image of the switch.
			 * @return std::shared_ptr< Graphics::ImageResource >
			 */
			[[nodiscard]]
			std::shared_ptr< Graphics::ImageResource > image () const noexcept;

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
			 * @brief Returs the state of the switch.
			 * @return bool
			 */
			[[nodiscard]]
			bool state () const noexcept;

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
