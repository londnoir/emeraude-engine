/*
 * src/Graphics/RenderTarget/View/Cubemap.hpp
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

/* STL inclusions. */
#include <cstdint>
#include <string>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

/* Local inclusions for usages. */
#include "AVConsole/AbstractVirtualVideoDevice.hpp"
#include "Graphics/FramebufferPrecisions.hpp"
#include "Graphics/ViewMatrices3DUBO.hpp"
#include "Graphics/ViewMatricesInterface.hpp"
#include "Libs/Math/CartesianFrame.hpp"
#include "Libs/Math/Vector.hpp"

namespace EmEn::Graphics::RenderTarget::View
{
	/**
	 * @brief The cubic view class.
	 * @extends EmEn::Graphics::RenderTarget::View::Abstract This is a view.
	 */
	class Cubemap final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"ViewCubemap"};

			/**
			 * @brief Constructs a render to cubic view.
			 * @param name A reference to a string for the name of the video device.
			 * @param size The size of the cubemap.
			 * @param precisions A structure to describe framebuffer precisions. Default R:8,G:8,B:8,A:8,depth:8,stencil:0,samples:1.
			 */
			Cubemap (const std::string & name, uint32_t size, const FramebufferPrecisions & precisions = {}) noexcept;

			/**
			 * @brief Destroys the render to cubic view.
			 */
			~Cubemap () override;

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::aspectRatio() */
			[[nodiscard]]
			float
			aspectRatio () const noexcept override
			{
				return 1.0F;
			}

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::isCubemap() */
			[[nodiscard]]
			bool
			isCubemap () const noexcept override
			{
				return true;
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

			/** @copydoc EmEn::AVConsole::AbstractVirtualVideoDevice::updateProperties() */
			void updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept override;

			/** @copydoc EmEn::AVConsole::AbstractVirtualVideoDevice::onSourceConnected() */
			void onSourceConnected (AbstractVirtualVideoDevice * sourceDevice) noexcept override;

			/** @copydoc EmEn::AVConsole::AbstractVirtualVideoDevice::onSourceDisconnected() */
			void onSourceDisconnected (AbstractVirtualVideoDevice * sourceDevice) noexcept override;

			ViewMatrices3DUBO m_viewMatrices;
			//size_t m_currentLayer{0};
	};
}
