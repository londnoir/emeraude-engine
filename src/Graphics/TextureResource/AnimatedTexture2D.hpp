/*
 * Emeraude/Graphics/TextureResource/AnimatedTexture2D.hpp
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
#include <vector>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"
#include "Resources/Container.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Graphics
	{
		class MovieResource;
	}

	namespace Vulkan
	{
		class Image;
	}
}

namespace Emeraude::Graphics::TextureResource
{
	/**
	 * @brief The animated texture 2D resource class.
	 * @extends Emeraude::Graphics::TextureResource::Abstract This is a loadable texture resource.
	 */
	class AnimatedTexture2D final : public Abstract
	{
		friend class Resources::Container< AnimatedTexture2D >;

		using Resources::ResourceTrait::load;

		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"AnimatedTexture2DResource"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs an animated texture 2D resource.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits. Default none. (Unused yet)
			 */
			explicit AnimatedTexture2D (const std::string & name, uint32_t resourceFlagBits = 0) noexcept;

			/** @brief Cleans video memory. */
			~AnimatedTexture2D () override;

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
			 * @brief Loads from a movie resource.
			 * @param image A reference to a movie resource smart pointer.
			 * @return bool
			 */
			bool load (const std::shared_ptr< MovieResource > & movieResource) noexcept;

			/**
			 * @brief Returns an animated texture 2D resource by its name.
			 * @param resourceName A reference to a string.
			 * @param directLoad Use the direct loading mode. Default false.
			 * @return std::shared_ptr< AnimatedTexture2D >
			 */
			[[nodiscard]]
			static std::shared_ptr< AnimatedTexture2D > get (const std::string & resourceName, bool directLoad = false) noexcept;

			/**
			 * @brief Returns the default animated texture 2D resource.
			 * @return std::shared_ptr< AnimatedTexture2D >
			 */
			[[nodiscard]]
			static std::shared_ptr< AnimatedTexture2D > getDefault () noexcept;

		private:

			/**
			 * @brief extractCountWidth
			 * @param basename
			 * @param replaceKey
			 * @return size_t
			 */
			static size_t extractCountWidth (const std::string & basename, std::string & replaceKey) noexcept;

			std::shared_ptr< Vulkan::Image > m_image{};
			std::shared_ptr< Vulkan::ImageView > m_imageView{};
			std::shared_ptr< Vulkan::Sampler > m_sampler{};
			std::shared_ptr< MovieResource > m_localData{};
	};
}

/* Expose the resource manager as a convenient type. */
namespace Emeraude::Resources
{
	using AnimatedTexture2Ds = Container< Graphics::TextureResource::AnimatedTexture2D >;
}
