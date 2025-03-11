/*
 * src/Graphics/TextureResource/Texture2D.hpp
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

/* Local inclusions. */
#include "Libs/PixelFactory/Color.hpp"
#include "Resources/Container.hpp"
#include "Resources/ResourceTrait.hpp"

/* Forward declarations. */
namespace EmEn
{
	namespace Graphics
	{
		class ImageResource;
	}

	namespace Vulkan
	{
		class Image;
	}
}

namespace EmEn::Graphics::TextureResource
{
	/**
	 * @brief The texture 2D resource class.
	 * @extends EmEn::Graphics::TextureResource::Abstract This is a loadable texture resource.
	 */
	class Texture2D final : public Abstract
	{
		friend class Resources::Container< Texture2D >;

		using ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Texture2DResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a texture 2D resource.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits. Default none. (Unused yet)
			 */
			explicit Texture2D (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Texture2D (const Texture2D & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Texture2D (Texture2D && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Texture2D &
			 */
			Texture2D & operator= (const Texture2D & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Texture2D &
			 */
			Texture2D & operator= (Texture2D && copy) noexcept = delete;

			/**
			 * @brief Constructs the texture 2D resource.
			 */
			~Texture2D () override;

			/** @copydoc EmEn::Libs::ObservableTrait::classUID() const */
			[[nodiscard]]
			size_t classUID () const noexcept override;

			/** @copydoc EmEn::Libs::ObservableTrait::is() const */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::createOnHardware() */
			bool createOnHardware (Renderer & renderer) noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::type() */
			[[nodiscard]]
			Type type () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::isGrayScale() */
			[[nodiscard]]
			bool isGrayScale () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::averageColor() */
			[[nodiscard]]
			Libs::PixelFactory::Color< float > averageColor () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::dimensions() */
			[[nodiscard]]
			uint32_t dimensions () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::isCubemapTexture() */
			[[nodiscard]]
			bool isCubemapTexture () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::frameCount() */
			[[nodiscard]]
			uint32_t frameCount () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::duration() */
			[[nodiscard]]
			uint32_t duration () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::frameIndexAt() */
			[[nodiscard]]
			size_t frameIndexAt (uint32_t sceneTime) const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::image() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::Image > image () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::imageView() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::ImageView > imageView () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::sampler() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::Sampler > sampler () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::request3DTextureCoordinates() */
			[[nodiscard]]
			bool request3DTextureCoordinates () const noexcept override;

			/** @copydoc EmEn::Resources::ResourceTrait::classLabel() const */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::load() */
			bool load () noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::load (const std::filesystem::path &) */
			bool load (const std::filesystem::path & filepath) noexcept override;

			/** @copydoc EmEn::Graphics::TextureResource::Abstract::load (const Json::Value &) */
			bool load (const Json::Value & data) noexcept override;

			/**
			 * @brief Loads from an image resource.
			 * @param imageResource A reference to an image resource smart pointer.
			 * @return bool
			 */
			bool load (const std::shared_ptr< ImageResource > & imageResource) noexcept;

			/**
			 * @brief Returns the image resource smart pointer.
			 * @return std::shared_ptr< ImageResource >
			 */
			[[nodiscard]]
			std::shared_ptr< ImageResource > localData () noexcept;

			/**
			 * @brief Returns a texture 2D resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< TextureResource >
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

			std::shared_ptr< ImageResource > m_localData;
			std::shared_ptr< Vulkan::Image > m_image;
			std::shared_ptr< Vulkan::ImageView > m_imageView;
			std::shared_ptr< Vulkan::Sampler > m_sampler;
	};
}

/* Expose the resource manager as a convenient type. */
namespace EmEn::Resources
{
	using Texture2Ds = Container< Graphics::TextureResource::Texture2D >;
}
