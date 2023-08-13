/*
 * Emeraude/Overlay/Elements/Switch.cpp
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

#include "Switch.hpp"

/* Local inclusions */
#include "PixelFactory/Processor.hpp"
#include "Graphics/ImageResource.hpp"
#include "Graphics/Geometry/IndexedVertexResource.hpp"

namespace Emeraude::Overlay::Elements
{
	using namespace Libraries;
	using namespace PixelFactory;
	using namespace Graphics;

	Switch::Switch () noexcept
		: Surface(0.5F, 0.33333F)
	{
		this->setCapturePointerEventsState(true);
	}

	void
	Switch::onPointerEnter (float, float) noexcept
	{
		if ( m_status == Status::Disabled )
			return;

		m_status = Status::Over;

		this->setTextureOffsetY(0.33333F);
	}

	void
	Switch::onPointerLeave (float, float) noexcept
	{
		if ( m_status == Status::Disabled )
			return;

		m_status = Status::Normal;

		this->setTextureOffsetY(0.0F);
	}

	void
	Switch::onButtonPress (float, float, int, int) noexcept
	{
		if ( m_status == Status::Disabled )
			return;

		m_status = Status::Active;
	}

	void
	Switch::onButtonRelease (float, float, int, int) noexcept
	{
		if ( m_status == Status::Disabled )
			return;

		m_status = Status::Over;

		this->toggle();
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
			return;

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
