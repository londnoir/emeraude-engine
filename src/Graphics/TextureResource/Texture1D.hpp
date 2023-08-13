/*
 * Emeraude/Graphics/TextureResource/Texture1D.hpp
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
#include <memory>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"
#include "Resources/Container.hpp"

/* Forward declarations. */
namespace Emeraude
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

namespace Emeraude::Graphics::TextureResource
{
	/**
	 * @brief The texture 1D resource class.
	 * @extends Emeraude::Graphics::TextureResource::Abstract This is a loadable texture resource.
	 */
	class Texture1D final : public Abstract
	{
		friend class Resources::Container< Texture1D >;

		using Resources::ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Texture1DResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a texture 1D resource.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits. Default none. (Unused yet)
			 */
			explicit Texture1D (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @brief Cleans video memory. */
			~Texture1D () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::isGrayScale() */
			[[nodiscard]]
			bool isGrayScale () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::averageColor() */
			[[nodiscard]]
			Libraries::PixelFactory::Color< float > averageColor () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::dimensions() */
			[[nodiscard]]
			uint32_t dimensions () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::isCubemapTexture() */
			[[nodiscard]]
			bool isCubemapTexture () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::frameCount() */
			[[nodiscard]]
			size_t frameCount () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::duration() */
			[[nodiscard]]
			size_t duration () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::image() */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::Image > & image () const noexcept final;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::imageView() */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::ImageView > & imageView () const noexcept final;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::sampler() */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::Sampler > & sampler () const noexcept final;

			/** @copydoc Libraries::Resources::ResourceTrait::classLabel() */
			[[nodiscard]]
			const char * classLabel () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::load() */
			bool load () noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::load (const Libraries::Path::File &) */
			bool load (const Libraries::Path::File & filepath) noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::load (const Json::Value &) */
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
			 * @brief Returns a texture 1D resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< Texture1D >
			 */
			[[nodiscard]]
			static std::shared_ptr< Texture1D > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default texture 1D resource.
			 * @return std::shared_ptr< Texture1D >
			 */
			[[nodiscard]]
			static std::shared_ptr< Texture1D > getDefault () noexcept;

		private:

			std::shared_ptr< Vulkan::Image > m_image{};
			std::shared_ptr< Vulkan::ImageView > m_imageView{};
			std::shared_ptr< Vulkan::Sampler > m_sampler{};
			std::shared_ptr< ImageResource > m_localData{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using Texture1Ds = Container< Graphics::TextureResource::Texture1D >;
}
