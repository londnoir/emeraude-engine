/*
 * src/Graphics/RenderTarget/View/Cubemap.hpp
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
#include <cstdint>
#include <string>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

/* Local inclusions for usages. */
#include "Graphics/FramebufferPrecisions.hpp"
#include "Graphics/ViewMatrices3DUBO.hpp"
#include "Graphics/ViewMatricesInterface.hpp"
#include "MasterControl/AbstractVirtualVideoDevice.hpp"
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Vector.hpp"

namespace Emeraude::Graphics::RenderTarget::View
{
	/**
	 * @brief The cubic view class.
	 * @extends Emeraude::Graphics::RenderTarget::View::Abstract This is a view.
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

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::aspectRatio() */
			[[nodiscard]]
			float
			aspectRatio () const noexcept override
			{
				return 1.0F;
			}

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::isCubemap() */
			[[nodiscard]]
			bool
			isCubemap () const noexcept override
			{
				return true;
			}

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::viewMatrices() const */
			[[nodiscard]]
			const ViewMatricesInterface &
			viewMatrices () const noexcept override
			{
				return m_viewMatrices;
			}

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::viewMatrices() */
			[[nodiscard]]
			ViewMatricesInterface &
			viewMatrices () noexcept override
			{
				return m_viewMatrices;
			}

		private:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::updateProperties() */
			void updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onSourceConnected() */
			void onSourceConnected (AbstractVirtualVideoDevice * sourceDevice) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onSourceDisconnected() */
			void onSourceDisconnected (AbstractVirtualVideoDevice * sourceDevice) noexcept override;

			ViewMatrices3DUBO m_viewMatrices;
			//size_t m_currentLayer{0};
	};
}
