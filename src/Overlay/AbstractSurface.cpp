/*
 * src/Overlay/AbstractSurface.cpp
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

#include "AbstractSurface.hpp"

/* C/C++ standard libraries. */
#include <iostream>
#include <string>

/* Local inclusions. */
#include "Libraries/NameableTrait.hpp"
#include "Libraries/Math/Matrix.hpp"
#include "Libraries/Math/Rectangle.hpp"
#include "Graphics/Renderer.hpp"
#include "FramebufferProperties.hpp"
#include "Tracer.hpp"

namespace Emeraude::Overlay
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Graphics;

	static constexpr auto TracerTag{"OverlaySurface"};

	AbstractSurface::AbstractSurface (const std::string & name, const Rectangle< float > & geometry, float depth) noexcept
		: NameableTrait(name), m_rectangle(geometry), m_depth(depth)
	{
		this->setTransformationMatrix();
	}

	bool
	AbstractSurface::isBelowPoint (const FramebufferProperties & framebufferProperties, float positionX, float positionY) const noexcept
	{
		{
			const auto screenWidth = static_cast< float >(framebufferProperties.width());

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
			const auto screenHeight = static_cast< float >(framebufferProperties.height());

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

	void
	AbstractSurface::setTransformationMatrix () noexcept
	{
		const auto xPosition = (-1.0F + m_rectangle.width()) + (m_rectangle.offsetX() * 2.0F);
		const auto yPosition = (-1.0F + m_rectangle.height()) + (m_rectangle.offsetY() * 2.0F);

		m_transformationMatrix.reset();
		m_transformationMatrix *= Matrix< 4, float >::translation(xPosition, yPosition, m_depth);
		m_transformationMatrix *= Matrix< 4, float >::scaling(m_rectangle.width(), m_rectangle.height(), 1.0F);
	}

	bool
	AbstractSurface::updatePhysicalRepresentation (Renderer & renderer, const FramebufferProperties & framebufferProperties) noexcept
	{
		if ( !this->onPhysicalRepresentationUpdate(renderer, framebufferProperties) )
		{
			TraceError{TracerTag} << "Unable to update the physical representation of surface '" << this->name() << " !";

			return false;
		}

		this->setTransformationMatrix();

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
