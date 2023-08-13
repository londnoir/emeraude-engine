/*
 * Emeraude/Graphics/RenderTarget/Texture/Cubemap.hpp
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

/* C/C++ standard libraries. */
#include <array>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

/* Local inclusions for usages. */
#include "Graphics/ViewMatrices3DUBO.hpp"
#include "Resources/Container.hpp"
#include "Saphir/Declaration/UniformBlock.hpp"

namespace Emeraude::Graphics::RenderTarget::Texture
{
	/**
	 * @brief The render to cubemap class.
	 * @extends Emeraude::Graphics::Texture::Abstract This is a render to texture
	 */
	class Cubemap final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"RTTCubemapResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a render to cubemap.
			 * @param name A reference to a string for the name of the video device.
			 * @param size The size of the cubemap.
			 * @param colorCount The number of color channel desired for the texture2Ds. Default 4.
			 */
			Cubemap (const std::string & name, uint32_t size, uint32_t colorCount = 4) noexcept;

			/**
			 * @brief Constructor version for resource manager.
			 * @param name A reference to a string for the resource name.
			 */
			explicit Cubemap (const std::string & name) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

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
			 * @brief Returns a texture cubemap resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< Cubemap >
			 */
			[[nodiscard]]
			static std::shared_ptr< Cubemap > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default texture cubemap resource.
			 * @return std::shared_ptr< Cubemap >
			 */
			[[nodiscard]]
			static std::shared_ptr< Cubemap > getDefault () noexcept;

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

			/**
			 * @brief isSinglePass
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			isSinglePass () const noexcept
			{
				return m_currentLayer > 5;
			}

			ViewMatrices3DUBO m_viewMatrices{};
			size_t m_currentLayer = 0;
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using RenderToCubemaps = Container< Graphics::RenderTarget::Texture::Cubemap >;
}
