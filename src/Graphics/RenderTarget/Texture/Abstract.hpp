/*
 * Emeraude/Graphics/RenderTarget/Texture/Abstract.hpp
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

/* C/C++ standard libraries */
#include <string>

/* Local inclusions for inheritances. */
#include "Graphics/RenderTarget/Abstract.hpp"
#include "Graphics/Light/LightableRenderTargetTrait.hpp"
#include "Graphics/TextureResource/Abstract.hpp"

namespace Emeraude::Graphics::RenderTarget::Texture
{
	/**
	 * @brief Base class for rendering to texture2Ds.
	 * @extends Emeraude::Graphics::RenderTarget::Abstract This is a render target.
	 * @extends Emeraude::Graphics::Light::LightableRenderTargetTrait This render target use lighting.
	 * @extends Emeraude::Graphics::TextureResource::Abstract This is a usable texture.
	 */
	class Abstract : public RenderTarget::Abstract, public Light::LightableRenderTargetTrait, public TextureResource::Abstract
	{
		public:

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
			 * @return Abstract &
			 */
			Abstract & operator= (const Abstract & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Abstract &
			 */
			Abstract & operator= (Abstract && copy) noexcept = delete;

			/**
			 * @brief Destructs the abstract render to texture.
			 */
			~Abstract () override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::videoType() */
			[[nodiscard]]
			MasterControl::VideoType videoType () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept override;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::createOnHardware() */
			[[nodiscard]]
			bool createOnHardware () noexcept final;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::destroyFromHardware() */
			bool destroyFromHardware () noexcept final;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::renderPass() */
			[[nodiscard]]
			const Vulkan::RenderPass * renderPass () const noexcept final;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::framebuffer() */
			[[nodiscard]]
			const Vulkan::Framebuffer * framebuffer () const noexcept final;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::image() */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::Image > & image () const noexcept final;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::imageView() */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::ImageView > & imageView () const noexcept final;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::sampler() */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::Sampler > & sampler () const noexcept final;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::isValid() */
			[[nodiscard]]
			bool isValid () const noexcept final;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept final;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Libraries::Path::File &) */
			bool load (const Libraries::Path::File & filepath) noexcept final;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept final;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::isGrayScale() */
			[[nodiscard]]
			bool isGrayScale () const noexcept final;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::averageColor() */
			[[nodiscard]]
			Libraries::PixelFactory::Color< float > averageColor () const noexcept final;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::dimensions() */
			[[nodiscard]]
			uint32_t dimensions () const noexcept final;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::isCubemapTexture() */
			[[nodiscard]]
			bool isCubemapTexture () const noexcept final;

			/**
			 * @brief Returns the number frame.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t frameCount () const noexcept final;

			/**
			 * @brief Returns the duration.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t duration () const noexcept final;

			/**
			 * @brief Gives access to the main hardware depth stencil image of the render target.
			 * @return const std::shared_ptr< Vulkan::Image > &
			 */
			[[nodiscard]]
			virtual const std::shared_ptr< Vulkan::Image > & depthStencilImage () const noexcept final;

			/**
			 * @brief Gives access to the main hardware depth image view object of the render target.
			 * @return const std::shared_ptr< Vulkan::ImageView > &
			 */
			[[nodiscard]]
			virtual const std::shared_ptr< Vulkan::ImageView > & depthImageView () const noexcept final;

			/**
			 * @brief Gives access to the main hardware stencil image view object of the render target.
			 * @return const std::shared_ptr< Vulkan::ImageView > &
			 */
			[[nodiscard]]
			virtual const std::shared_ptr< Vulkan::ImageView > & stencilImageView () const noexcept final;

		protected:

			/**
			 * @brief Constructs an abstract render to texture.
			 * @param precisions The framebuffer precisions.
			 * @param extent The framebuffer dimensions.
			 * @param renderType The type of render.
			 */
			Abstract (const std::string & name, const FramebufferPrecisions & precisions, const VkExtent3D & extent, RenderType renderType) noexcept;

		private:

			std::shared_ptr< Vulkan::RenderPass > m_renderPass{};
			std::shared_ptr< Vulkan::Framebuffer > m_framebuffer{};
			std::shared_ptr< Vulkan::Image > m_colorImage{};
			std::shared_ptr< Vulkan::ImageView > m_colorImageView{};
			std::shared_ptr< Vulkan::Image > m_depthStencilImage{};
			std::shared_ptr< Vulkan::ImageView > m_depthImageView{};
			std::shared_ptr< Vulkan::ImageView > m_stencilImageView{};
			std::shared_ptr< Vulkan::Sampler > m_sampler{};
	};
}
