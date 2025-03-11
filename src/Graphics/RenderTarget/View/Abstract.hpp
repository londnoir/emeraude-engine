/*
 * src/Graphics/RenderTarget/View/Abstract.hpp
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
#include <memory>
#include <cstdint>
#include <string>

/* Local inclusions for inheritances. */
#include "Graphics/RenderTarget/Abstract.hpp"

/* Local inclusions for usages. */
#include "AVConsole/Types.hpp"
#include "Graphics/FramebufferPrecisions.hpp"
#include "Graphics/Types.hpp"

namespace EmEn::Graphics::RenderTarget::View
{
	/**
	 * @brief The base class of every view.
	 * @extends EmEn::Graphics::RenderTarget::Abstract This is a render target.
	 */
	class Abstract : public RenderTarget::Abstract
	{
		public:

			/** @copydoc EmEn::AVConsole::AbstractVirtualVideoDevice::videoType() */
			[[nodiscard]]
			AVConsole::VideoType
			videoType () const noexcept override
			{
				return AVConsole::VideoType::View;
			}

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::framebuffer() */
			[[nodiscard]]
			const Vulkan::Framebuffer *
			framebuffer () const noexcept final
			{
				return m_framebuffer.get();
			}

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::image() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::Image >
			image () const noexcept final
			{
				return m_colorImage;
			}

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::imageView() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::ImageView >
			imageView () const noexcept final
			{
				return m_colorImageView;
			}

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::isValid() */
			[[nodiscard]]
			bool isValid () const noexcept final;

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

			/**
			 * @brief Returns the view width from settings.
			 * @return uint32_t
			 */
			[[nodiscard]]
			static uint32_t getWidth () noexcept;

			/**
			 * @brief Returns the view height from settings.
			 * @return uint32_t
			 */
			[[nodiscard]]
			static uint32_t getHeight () noexcept;

		protected:

			/**
			 * @brief Constructs an abstract render to view.
			 * @param name A reference to a string.
			 * @param precisions The framebuffer precisions.
			 * @param extent The framebuffer dimensions.
			 * @param renderType The type of render.
			 */
			Abstract (const std::string & name, const FramebufferPrecisions & precisions, const VkExtent3D & extent, RenderTargetType renderType) noexcept;

		private:

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::onCreate() */
			[[nodiscard]]
			bool onCreate (Renderer & renderer) noexcept final;

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::onDestroy() */
			void onDestroy () noexcept final;

			/** @copydoc EmEn::Graphics::RenderTarget::Abstract::createRenderPass() */
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
	};
}
