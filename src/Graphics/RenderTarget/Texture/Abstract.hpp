/*
 * src/Graphics/RenderTarget/Texture/Abstract.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2024 - "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Emeraude-Engine; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor,
 * Boston, MA  02110-1301  USA
 *
 * Complete project and additional information can be found at :
 * https://bitbucket.org/londnoir/emeraude-engine
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
#include "Graphics/RenderTarget/Abstract.hpp"
#include "Graphics/TextureResource/Abstract.hpp"

/* Local inclusions for usages. */
#include "Libraries/PixelFactory/Color.hpp"
#include "Graphics/FramebufferPrecisions.hpp"
#include "Graphics/Types.hpp"
#include "MasterControl/Types.hpp"

namespace Emeraude::Graphics::RenderTarget::Texture
{
	/**
	 * @brief Base class for rendering to texture2Ds.
	 * @extends Emeraude::Graphics::RenderTarget::Abstract This is a render target.
	 * @extends Emeraude::Graphics::TextureResource::Abstract This is a usable texture.
	 */
	class Abstract : public RenderTarget::Abstract, public TextureResource::Abstract
	{
		public:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::videoType() */
			[[nodiscard]]
			MasterControl::VideoType
			videoType () const noexcept override
			{
				return MasterControl::VideoType::Texture;
			}

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::framebuffer() */
			[[nodiscard]]
			const Vulkan::Framebuffer *
			framebuffer () const noexcept final
			{
				return m_framebuffer.get();
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::image() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::Image >
			image () const noexcept final
			{
				return m_colorImage;
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::imageView() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::ImageView >
			imageView () const noexcept final
			{
				return m_colorImageView;
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::sampler() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::Sampler >
			sampler () const noexcept final
			{
				return m_sampler;
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::isCreated() */
			[[nodiscard]]
			bool isCreated () const noexcept override;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::createOnHardware() */
			[[nodiscard]]
			bool
			createOnHardware (Renderer & renderer) noexcept final
			{
				return this->create(renderer);
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::destroyFromHardware() */
			bool
			destroyFromHardware () noexcept final
			{
				return this->destroy();
			}

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::isValid() */
			[[nodiscard]]
			bool isValid () const noexcept final;

			/** @copydoc Emeraude::Resources::ResourceTrait::load() */
			bool load () noexcept final;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const std::filesystem::path &) */
			bool load (const std::filesystem::path & filepath) noexcept final;

			/** @copydoc Emeraude::Resources::ResourceTrait::load(const Json::Value &) */
			bool load (const Json::Value & data) noexcept final;

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::isGrayScale() */
			[[nodiscard]]
			bool
			isGrayScale () const noexcept final
			{
				/* FIXME: Scan the create info */
				return false;
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::averageColor() */
			[[nodiscard]]
			Libraries::PixelFactory::Color< float >
			averageColor () const noexcept final
			{
				/* FIXME: Compute average color from video memory texture2Ds. */
				return Libraries::PixelFactory::Grey;
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::dimensions() */
			[[nodiscard]]
			uint32_t
			dimensions () const noexcept final
			{
				return this->isCubemap() ? 3 : 2;
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::isCubemapTexture() */
			[[nodiscard]]
			bool
			isCubemapTexture () const noexcept final
			{
				return this->isCubemap();
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::frameCount() */
			[[nodiscard]]
			uint32_t
			frameCount () const noexcept final
			{
				return 1;
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::duration() */
			[[nodiscard]]
			uint32_t
			duration () const noexcept final
			{
				return 0;
			}

			/** @copydoc Emeraude::Graphics::TextureResource::Abstract::frameIndexAt() */
			[[nodiscard]]
			size_t
			frameIndexAt (uint32_t /*sceneTime*/) const noexcept override
			{
				return 0;
			}

			/**
			 * @brief Gives access to the main hardware depth stencil image of the render target.
			 * @return std::shared_ptr< Vulkan::Image >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::Image >
			depthStencilImage () const noexcept
			{
				return m_depthStencilImage;
			}

			/**
			 * @brief Gives access to the main hardware depth image view object of the render target.
			 * @return std::shared_ptr< Vulkan::ImageView >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::ImageView >
			depthImageView () const noexcept
			{
				return m_depthImageView;
			}

			/**
			 * @brief Gives access to the main hardware stencil image view object of the render target.
			 * @return std::shared_ptr< Vulkan::ImageView >
			 */
			[[nodiscard]]
			std::shared_ptr< Vulkan::ImageView >
			stencilImageView () const noexcept
			{
				return m_stencilImageView;
			}

		protected:

			/**
			 * @brief Constructs an abstract render to texture.
			 * @param name A reference to a string.
			 * @param precisions The framebuffer precisions.
			 * @param extent The framebuffer dimensions.
			 * @param renderType The type of render.
			 */
			Abstract (const std::string & name, const FramebufferPrecisions & precisions, const VkExtent3D & extent, RenderTargetType renderType) noexcept;

		private:

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::onCreate() */
			[[nodiscard]]
			bool onCreate (Renderer & renderer) noexcept final;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::onDestroy() */
			void onDestroy () noexcept final;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::createRenderPass() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::RenderPass > createRenderPass (Renderer & renderer) const noexcept override;

			/**
			 * @brief Creates the images and the image views for each swap chain frame.
			 * @param device A reference to the graphics device smart pointer.
			 * @return bool
			 */
			[[nodiscard]]
			bool createImages (const std::shared_ptr< Vulkan::Device > & device) noexcept;

			/**
			 * @brief Creates the framebuffer.
			 * @param renderPass A reference to the render pass smart pointer.
			 * @return bool
			 */
			[[nodiscard]]
			bool createFramebuffer (const std::shared_ptr< Vulkan::RenderPass > & renderPass) noexcept;

			std::shared_ptr< Vulkan::Framebuffer > m_framebuffer;
			std::shared_ptr< Vulkan::Image > m_colorImage;
			std::shared_ptr< Vulkan::ImageView > m_colorImageView;
			std::shared_ptr< Vulkan::Image > m_depthStencilImage;
			std::shared_ptr< Vulkan::ImageView > m_depthImageView;
			std::shared_ptr< Vulkan::ImageView > m_stencilImageView;
			std::shared_ptr< Vulkan::Sampler > m_sampler;
	};
}
