/*
 * Emeraude/Graphics/TextureResource/Abstract.hpp
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
#include "Resources/ResourceTrait.hpp"
#include "PixelFactory/Pixmap.hpp"

/* Third-party inclusions. */
#include "Third-Party-Inclusion/vulkan.hpp"

/* Forward declarations. */
namespace Emeraude::Vulkan
{
	class Framebuffer;
	class RenderPass;
	class Image;
	class ImageView;
	class Sampler;
}

namespace Emeraude::Graphics::TextureResource
{
	/**
	 * @brief This is the base class for every vulkan image resource.
	 * @extends Emeraude::Resources::ResourceTrait This is a loadable resource.
	 */
	class Abstract : public Resources::ResourceTrait
	{
		public:

			/**
			 * @brief Destructs the abstract texture resource.
			 */
			~Abstract () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Abstract (const Abstract & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Abstract (Abstract && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Abstract & operator= (const Abstract & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Abstract & operator= (Abstract && copy) noexcept = delete;

			/**
			 * @brief Returns the descriptor image info.
			 * @return VkDescriptorBufferInfo
			 */
			[[nodiscard]]
			virtual VkDescriptorImageInfo getDescriptorInfo () const noexcept final;

			/**
			 * @brief Returns whether the image is ready.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isCreated () const noexcept = 0;

			/**
			 * @brief Creates the image buffer from local data to video memory.
			 * @return bool
			 */
			virtual bool createOnHardware () noexcept = 0;

			/**
			 * @brief Destroys the image from video memory.
			 */
			virtual bool destroyFromHardware () noexcept = 0;

			/**
			 * @brief Returns whether the texture is grayscale or not.
			 * @note This should be done by a local data analysis.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isGrayScale () const noexcept = 0;

			/**
			 * @brief Returns the average color of the texture.
			 * @note This should be done by a local data analysis.
			 * @return Color< float >
			 */
			[[nodiscard]]
			virtual Libraries::PixelFactory::Color< float > averageColor () const noexcept = 0;

			/**
			 * @brief Returns the dimensions for use with texture coordinates. Should be 1, 2 or 3.
			 * @return uint32_t
			 */
			[[nodiscard]]
			virtual uint32_t dimensions () const noexcept = 0;

			/**
			 * @brief Returns whether the texture is a cubemap.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isCubemapTexture () const noexcept = 0;

			/**
			 * @brief Returns the number frame.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t frameCount () const noexcept = 0;

			/**
			 * @brief Returns the duration.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t duration () const noexcept = 0;

			/**
			 * @brief Returns the image of the texture.
			 * @return const std::shared_ptr< Vulkan::Image > &
			 */
			[[nodiscard]]
			virtual const std::shared_ptr< Vulkan::Image > & image () const noexcept = 0;

			/**
			 * @brief Returns the image view of the texture.
			 * @return const std::shared_ptr< Vulkan::ImageView > &
			 */
			[[nodiscard]]
			virtual const std::shared_ptr< Vulkan::ImageView > & imageView () const noexcept = 0;

			/**
			 * @brief Returns the sampler used by of the texture.
			 * @return const std::shared_ptr< Vulkan::Sampler > &
			 */
			[[nodiscard]]
			virtual const std::shared_ptr< Vulkan::Sampler > & sampler () const noexcept = 0;

			/**
			 * @brief Validates a pixmap for Vulkan requirements.
			 * @param classId A pointer to the class id validating the pixmap.
			 * @param pixmap A reference to a pixmap.
			 * @param disablePowerOfTwoCheck Disable the check for size pixmap check. Default false.
			 * @return bool
			 */
			[[nodiscard]]
			static bool validatePixmap (const char * classId, Libraries::PixelFactory::Pixmap< uint8_t > & pixmap, bool disablePowerOfTwoCheck = false) noexcept;

		protected:

			/**
			 * @brief Constructs an abstract texture resource.
			 * @param name The name of the resource.
			 * @param resourceFlagBits The resource flag bits.
			 */
			Abstract (const std::string & name, uint32_t resourceFlagBits) noexcept;

		private:

			/** @copydoc Emeraude::Resources::ResourceTrait::onDependenciesLoaded() */
			[[nodiscard]]
			bool onDependenciesLoaded () noexcept override;
	};
}
