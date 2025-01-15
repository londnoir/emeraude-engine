/*
 * src/Graphics/RenderTarget/ShadowMap/Cubemap.cpp
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

#include "Cubemap.hpp"

/* Local inclusions. */
#include "Graphics/Renderer.hpp"

namespace Emeraude::Graphics::RenderTarget::ShadowMap
{
	using namespace Libraries;
	using namespace Libraries::Math;

	Cubemap::Cubemap (const std::string & name, uint32_t resolution) noexcept
		: Abstract(name, {}, {resolution, resolution, 1}, RenderTargetType::ShadowCubemap)
	{

	}

	Cubemap::~Cubemap ()
	{
		this->destroy();
	}

	void
	Cubemap::updateDeviceFromCoordinates (const CartesianFrame< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
	{
		m_viewMatrices.updateViewCoordinates(worldCoordinates, worldVelocity);
	}

	void
	Cubemap::updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept
	{
		const auto & extent = this->extent();

		if ( isPerspectiveProjection )
		{
			m_viewMatrices.updatePerspectiveViewProperties(static_cast< float >(extent.width), static_cast< float >(extent.height), distance, fovOrNear);
		}
		else
		{
			m_viewMatrices.updateOrthographicViewProperties(static_cast< float >(extent.width), static_cast< float >(extent.height), distance, fovOrNear);
		}
	}

	void
	Cubemap::onSourceConnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.create(*Graphics::Renderer::instance(), this->id());
	}

	void
	Cubemap::onSourceDisconnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.destroy();
	}
}
