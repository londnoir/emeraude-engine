/*
 * src/Graphics/RenderTarget/ShadowMap/Texture2D.hpp
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

#pragma once

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

/* Local inclusions for usages. */
#include "Graphics/ViewMatrices2DUBO.hpp"

namespace EmEn::Graphics::RenderTarget::ShadowMap
{
	/**
	 * @brief Render target specialization for 2D shadow mapping (directional lights and spotlights).
	 * @extends EmEn::Graphics::RenderTarget::ShadowMap::Abstract This is a shadow map.
	 */
	class Texture2D final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ShadowTexture2D"};

			/**
			 * @brief Constructs a render to shadow map.
			 * @param name The name to identify the shadow map.
			 * @param resolution The definition of the shadow map.
			 */
			Texture2D (const std::string & name, uint32_t resolution) noexcept;

			/**
			 * @brief Destroys the render to shadow map.
			 */
			~Texture2D () override;

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::isCubemap() */
			[[nodiscard]]
			bool
			isCubemap () const noexcept override
			{
				return false;
			}

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::viewMatrices() const */
			[[nodiscard]]
			const ViewMatricesInterface &
			viewMatrices () const noexcept override
			{
				return m_viewMatrices;
			}

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::viewMatrices() */
			[[nodiscard]]
			ViewMatricesInterface &
			viewMatrices () noexcept override
			{
				return m_viewMatrices;
			}

		private:

			/** @copydoc EmEn::AVConsole::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libs::Math::CartesianFrame< float > & worldCoordinates, const Libs::Math::Vector< 3, float > & worldVelocity) noexcept override;

			/** @copydoc EmEn::AVConsole::AbstractVirtualDevice::updateProperties() */
			void updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept override;

			/** @copydoc EmEn::AVConsole::AbstractVirtualDevice::onSourceConnected() */
			void onSourceConnected (AbstractVirtualDevice * sourceDevice) noexcept override;

			/** @copydoc EmEn::AVConsole::AbstractVirtualDevice::onSourceDisconnected() */
			void onSourceDisconnected (AbstractVirtualDevice * sourceDevice) noexcept override;

			ViewMatrices2DUBO m_viewMatrices;
	};
}
