/*
 * src/Overlay/AbstractSurface.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "AbstractSurface.hpp"

/* Local inclusions. */
#include "Tracer.hpp"

namespace EmEn::Overlay
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::Math;
	using namespace Graphics;

	static constexpr auto TracerTag{"OverlaySurface"};

	AbstractSurface::AbstractSurface (const FramebufferProperties & framebufferProperties, const std::string & name, const Rectangle< float > & geometry, float depth) noexcept
		: NameableTrait(name),
		m_framebufferProperties(framebufferProperties),
		m_rectangle(geometry),
		m_depth(depth)
	{
		this->updateModelMatrix();
	}

	void
	AbstractSurface::setGeometry (const Rectangle< float > & rectangle) noexcept
	{
		m_rectangle = rectangle;
	}

	void
	AbstractSurface::setPosition (float xPosition, float yPosition) noexcept
	{
		m_rectangle.setOffsetX(xPosition);
		m_rectangle.setOffsetY(yPosition);
	}

	void
	AbstractSurface::setSize (float width, float height) noexcept
	{
		m_rectangle.setWidth(width);
		m_rectangle.setHeight(height);
	}

	void
	AbstractSurface::setDepth (float depth) noexcept
	{
		m_depth = depth;
	}

	void
	AbstractSurface::move (float deltaX, float deltaY) noexcept
	{
		m_rectangle.move(deltaX, deltaY);
	}

	bool
	AbstractSurface::isBelowPoint (float positionX, float positionY) const noexcept
	{
		{
			const auto screenWidth = static_cast< float >(m_framebufferProperties.width());

			const auto positionXa = screenWidth * m_rectangle.offsetX();

			if ( positionX < positionXa )
			{
				return false;
			}

			const auto positionXb = screenWidth * m_rectangle.offsetXb();

			if ( positionX > positionXb )
			{
				return false;
			}
		}

		{
			const auto screenHeight = static_cast< float >(m_framebufferProperties.height());

			const auto positionYa = screenHeight * m_rectangle.offsetY();

			if ( positionY < positionYa )
			{
				return false;
			}

			const auto positionYb = screenHeight * m_rectangle.offsetYb();

			if ( positionY > positionYb )
			{
				return false;
			}
		}

		return true;
	}

	bool
	AbstractSurface::isEventBlocked (float positionX, float positionY) const noexcept
	{
		/* The test is disabled. */
		if ( !m_flags[IsOpaque] )
		{
			return false;
		}

		/* The alpha test is not required, so the position is blocked. */
		if ( !m_flags[IsAlphaTestEnabled] )
		{
			return true;
		}

		return this->isEventBlockedWithAlpha(positionX, positionY, m_alphaThreshold);
	}

	void
	AbstractSurface::updateModelMatrix () noexcept
	{
		const auto xPosition = (-1.0F + m_rectangle.width()) + (m_rectangle.offsetX() * 2.0F);
		const auto yPosition = (-1.0F + m_rectangle.height()) + (m_rectangle.offsetY() * 2.0F);

		m_modelMatrix.reset();
		m_modelMatrix *= Matrix< 4, float >::translation(xPosition, yPosition, m_depth);
		m_modelMatrix *= Matrix< 4, float >::scaling(m_rectangle.width(), m_rectangle.height(), 1.0F);
	}

	bool
	AbstractSurface::updatePhysicalRepresentation (Renderer & renderer) noexcept
	{
		if ( !this->onPhysicalRepresentationUpdate(renderer) )
		{
			TraceError{TracerTag} << "Unable to update the physical representation of surface '" << this->name() << " !";

			return false;
		}

		this->updateModelMatrix();

		return true;
	}

	bool
	AbstractSurface::updateVideoMemory (Renderer & renderer) noexcept
	{
		if ( !m_flags[VideoMemoryUpdateRequested] )
		{
			return true;
		}

		if ( !this->onVideoMemoryUpdate(renderer) )
		{
			return false;
		}

		m_flags[VideoMemoryUpdateRequested] = false;

		return true;
	}
}
