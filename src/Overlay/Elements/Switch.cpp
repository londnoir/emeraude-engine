/*
 * src/Overlay/Elements/Switch.cpp
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

#include "Switch.hpp"

/* STL inclusions. */
#include <array>
#include <cstdint>

/* Local inclusions. */
#include "Libraries/PixelFactory/Processor.hpp"
#include "Graphics/ImageResource.hpp"

namespace Emeraude::Overlay::Elements
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace PixelFactory;
	using namespace Graphics;

	Switch::Switch (const std::string & name, const Math::Rectangle< float > & geometry, float depth) noexcept
		: ComposedSurface(name, geometry, depth)
	{
		this->enablePointerListening(true);
	}

	void
	Switch::onPointerEnter (const FramebufferProperties & /*framebufferProperties*/, float /*positionX*/, float /*positionY*/) noexcept
	{
		if ( m_status == Status::Disabled )
		{
			return;
		}

		m_status = Status::Over;

		this->setTextureOffsetY(0.33333F);
	}

	void
	Switch::onPointerLeave (const FramebufferProperties & /*framebufferProperties*/, float /*positionX*/, float /*positionY*/) noexcept
	{
		if ( m_status == Status::Disabled )
		{
			return;
		}

		m_status = Status::Normal;

		this->setTextureOffsetY(0.0F);
	}

	bool
	Switch::onButtonPress (const FramebufferProperties & /*framebufferProperties*/, float /*positionX*/, float /*positionY*/, int32_t /*buttonNumber*/, int32_t /*modifiers*/) noexcept
	{
		if ( m_status == Status::Disabled )
		{
			return false;
		}

		m_status = Status::Active;

		return true;
	}

	bool
	Switch::onButtonRelease (const FramebufferProperties & /*framebufferProperties*/, float /*positionX*/, float /*positionY*/, int /*buttonNumber*/, int /*modifiers*/) noexcept
	{
		if ( m_status == Status::Disabled )
		{
			return false;
		}

		m_status = Status::Over;

		this->toggle();

		return true;
	}

	void
	Switch::setImage (const std::shared_ptr< ImageResource > & image) noexcept
	{
		m_image = image;
	}

	std::shared_ptr< ImageResource >
	Switch::image () const noexcept
	{
		return m_image;
	}

	void
	Switch::toggle () noexcept
	{
		m_state = !m_state;

		this->setTextureOffsetX(m_state ? 0.5F : 0.0F);
	}

	void
	Switch::setState (bool state) noexcept
	{
		if ( m_state == state )
		{
			return;
		}

		m_state = state;

		this->setTextureOffsetX(m_state ? 0.5F : 0.0F);
	}

	bool
	Switch::state () const noexcept
	{
		return m_state;
	}

	bool
	Switch::onDrawFinished (Libraries::PixelFactory::Pixmap< uint8_t > & pixmap) noexcept
	{
		/* Applies the current background. */
		pixmap = Processor< uint8_t >::resize(m_image->data(), pixmap.width(), pixmap.height());

		return true;
	}
}
