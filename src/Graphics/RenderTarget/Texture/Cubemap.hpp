/*
 * src/Graphics/RenderTarget/Texture/Cubemap.hpp
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
#include "Graphics/ViewMatrices3DUBO.hpp"
#include "MasterControl/AbstractVirtualVideoDevice.hpp"
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Vector.hpp"
#include "Resources/Container.hpp"

namespace Emeraude::Graphics::RenderTarget::Texture
{
	/**
	 * @brief The render to cubemap class.
	 * @extends Emeraude::Graphics::RenderTarget::Texture::Abstract This is a render to texture
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

			/**
			 * @brief Destroys the render to cubemap.
			 */
			~Cubemap () override;

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

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::type() */
			[[nodiscard]]
			TextureResource::Type
			type () const noexcept override
			{
				return TextureResource::Type::TextureCube;
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::request3DTextureCoordinates() */
			[[nodiscard]]
			bool
			request3DTextureCoordinates () const noexcept override
			{
				return true;
			}

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

		private:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libraries::Math::CartesianFrame< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept override;

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
			bool
			isSinglePass () const noexcept
			{
				return m_currentLayer >= CubemapFaceCount;
			}

			ViewMatrices3DUBO m_viewMatrices;
			size_t m_currentLayer{0};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using RenderToCubemaps = Container< Graphics::RenderTarget::Texture::Cubemap >;
}
