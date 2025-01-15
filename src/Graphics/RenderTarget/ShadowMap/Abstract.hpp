/*
 * src/Graphics/RenderTarget/ShadowMap/Abstract.hpp
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
#include <cstdint>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Graphics/RenderTarget/Abstract.hpp"

/* Local inclusions for usages. */
#include "Graphics/FramebufferPrecisions.hpp"
#include "Graphics/TextureResource/Abstract.hpp"
#include "Graphics/Types.hpp"
#include "MasterControl/Types.hpp"

namespace Emeraude::Graphics::RenderTarget::ShadowMap
{
	/**
	 * @brief The base class for shadow maps.
	 * @extends Emeraude::Graphics::RenderTarget::Abstract This is a render target.
	 */
	class Abstract : public RenderTarget::Abstract
	{
		public:

			static constexpr auto Bias{0.5F};
			static constexpr Libraries::Math::Matrix< 4, float > ScaleBiasMatrix{{
				Bias, 0.0F, 0.0F, 0.0F,
				0.0F, Bias, 0.0F, 0.0F,
				0.0F, 0.0F, Bias, 0.0F,
				Bias, Bias, Bias, 1.0F
			}};

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::videoType() */
			[[nodiscard]]
			MasterControl::VideoType
			videoType () const noexcept override
			{
				return MasterControl::VideoType::ShadowMap;
			}

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::framebuffer() */
			[[nodiscard]]
			const Vulkan::Framebuffer *
			framebuffer () const noexcept final
			{
				return m_framebuffer.get();
			}

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::image() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::Image >
			image () const noexcept final
			{
				return m_depthImage;
			}

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::imageView() */
			[[nodiscard]]
			std::shared_ptr< Vulkan::ImageView >
			imageView () const noexcept final
			{
				return m_depthImageView;
			}

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::isValid() */
			[[nodiscard]]
			bool isValid () const noexcept final;

			/**
			 * @brief Returns the shadow map resolution from settings.
			 * @return uint32_t
			 */
			[[nodiscard]]
			static uint32_t getBaseResolution () noexcept;

		protected:

			/**
			 * @brief Constructs an abstract render to shadow map.
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
			std::shared_ptr< Vulkan::Image > m_depthImage;
			std::shared_ptr< Vulkan::ImageView > m_depthImageView;
	};
}
