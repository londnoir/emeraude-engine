/*
 * Emeraude/Graphics/RenderTarget/Texture/Texture2D.hpp
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
#include "Graphics/ViewMatrices2DUBO.hpp"
#include "Resources/Container.hpp"
#include "Saphir/Declaration/UniformBlock.hpp"

namespace Emeraude::Graphics::RenderTarget::Texture
{
	/**
	 * @brief The render to 2D texture class.
	 * @extends Emeraude::Graphics::Texture::Abstract This is a render to texture
	 */
	class Texture2D final : public Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"RTTTexture2DResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a render to 2D texture.
			 * @param name The name of the texture for debugging.
			 * @param width The width of the texture.
			 * @param width The height of the texture.
			 * @param colorCount The number of color channel desired for the texture2Ds. Default 4.
			 */
			Texture2D (const std::string & name, uint32_t width, uint32_t height, uint32_t colorCount = 4) noexcept;

			/**
			 * @brief Constructor version for resource manager.
			 * @param name A reference to a string for the resource name.
			 */
			explicit Texture2D (const std::string & name) noexcept;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

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
			 * @brief Returns a texture 2D resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< Texture2D >
			 */
			[[nodiscard]]
			static std::shared_ptr< Texture2D > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default texture 2D resource.
			 * @return std::shared_ptr< Texture2D >
			 */
			[[nodiscard]]
			static std::shared_ptr< Texture2D > getDefault () noexcept;

			/**
			 * @brief Gets a view uniform block.
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

			ViewMatrices2DUBO m_viewMatrices{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using RenderToTexture2Ds = Container< Graphics::RenderTarget::Texture::Texture2D >;
}
