/*
 * src/Graphics/RenderTarget/Texture/Texture2D.hpp
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
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"

/* Local inclusions for usages. */
#include "Graphics/ViewMatrices2DUBO.hpp"
#include "MasterControl/AbstractVirtualVideoDevice.hpp"
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Vector.hpp"
#include "Resources/Container.hpp"

namespace Emeraude::Graphics::RenderTarget::Texture
{
	/**
	 * @brief The render to 2D texture class.
	 * @extends Emeraude::Graphics::RenderTarget::Texture::Abstract This is a render to texture
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

			/**
			 * @brief Destroys the render to 2D texture.
			 */
			~Texture2D () override;

			/** @copydoc Libraries::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t
			classUID () const noexcept override
			{
				return ClassUID;
			}

			/** @copydoc Libraries::ObservableTrait::is() const */
			[[nodiscard]]
			bool
			is (size_t classUID) const noexcept override
			{
				return classUID == ClassUID;
			}

			/** @copydoc Emeraude::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char *
			classLabel () const noexcept override
			{
				return ClassId;
			}

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::isCubemap() */
			[[nodiscard]]
			bool
			isCubemap () const noexcept override
			{
				return false;
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

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::type() */
			[[nodiscard]]
			TextureResource::Type
			type () const noexcept override
			{
				return TextureResource::Type::Texture2D;
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::request3DTextureCoordinates() */
			[[nodiscard]]
			bool
			request3DTextureCoordinates () const noexcept override
			{
				return false;
			}

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

		private:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::updateProperties() */
			void updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onSourceConnected() */
			void onSourceConnected (AbstractVirtualVideoDevice * sourceDevice) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onSourceDisconnected() */
			void onSourceDisconnected (AbstractVirtualVideoDevice * sourceDevice) noexcept override;

			ViewMatrices2DUBO m_viewMatrices;
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using RenderToTexture2Ds = Container< Graphics::RenderTarget::Texture::Texture2D >;
}
