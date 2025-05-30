/*
 * src/Graphics/RenderTarget/View/Texture2D.cpp
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

#include "Texture2D.hpp"

/* Local inclusions. */
#include "Graphics/Renderer.hpp"

namespace EmEn::Graphics::RenderTarget::View
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::Math;
	using namespace Vulkan;

	Texture2D::Texture2D (const std::string & name, uint32_t width, uint32_t height, const FramebufferPrecisions & precisions) noexcept
		: Abstract(name, precisions, {width, height, 1}, RenderTargetType::View)
	{

	}

	Texture2D::~Texture2D ()
	{
		this->destroy();
	}

	void
	Texture2D::updateDeviceFromCoordinates (const CartesianFrame< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
	{
		m_viewMatrices.updateViewCoordinates(worldCoordinates, worldVelocity);
	}

	void
	Texture2D::updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept
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
	Texture2D::onSourceConnected (AbstractVirtualDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.create(*Graphics::Renderer::instance(), this->id());
	}

	void
	Texture2D::onSourceDisconnected (AbstractVirtualDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.destroy();
	}
}
