/*
 * Emeraude/Graphics/RenderTarget/View/Cubemap.hpp
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

#pragma once

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

/* Local inclusions for usages. */
#include "Graphics/ViewMatrices3DUBO.hpp"
#include "Saphir/Declaration/UniformBlock.hpp"

namespace Emeraude::Graphics::RenderTarget::View
{
	/**
	 * @brief The cubic view class.
	 * @extends Emeraude::Graphics::View::Abstract This is a view.
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

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::getAspectRatio() */
			[[nodiscard]]
			float aspectRatio () const noexcept override;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::isCubemap() */
			[[nodiscard]]
			bool isCubemap () const noexcept override;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::viewMatrices() const */
			[[nodiscard]]
			const ViewMatricesInterface & viewMatrices () const noexcept override;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::viewMatrices() */
			[[nodiscard]]
			ViewMatricesInterface & viewMatrices () noexcept override;

			/**
			 * @brief Gets a cubic view uniform block.
			 * @param set The set number used in the descriptor set.
			 * @param binding The binding used number the in descriptor set. Default 0.
			 * @return Saphir::Declaration::UniformBlock
			 */
			[[nodiscard]]
			static Saphir::Declaration::UniformBlock getViewUniformBlock (uint32_t set, uint32_t binding = 0) noexcept;

		private:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libraries::Math::Coordinates< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::updateProperties() */
			void updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onSourceConnected() */
			void onSourceConnected (AbstractVirtualVideoDevice * sourceDevice) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onSourceDisconnected() */
			void onSourceDisconnected (AbstractVirtualVideoDevice * sourceDevice) noexcept override;

			ViewMatrices3DUBO m_viewMatrices{};
			size_t m_currentLayer = 0;
	};
}
