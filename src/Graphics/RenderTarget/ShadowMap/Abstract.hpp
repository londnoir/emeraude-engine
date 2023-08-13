/*
 * Emeraude/Graphics/RenderTarget/ShadowMap/Abstract.hpp
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

/* C/C++ standards libraries */
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "Graphics/RenderTarget/Abstract.hpp"

namespace Emeraude::Vulkan
{
	class Device;
}

namespace Emeraude::Graphics::RenderTarget::ShadowMap
{
	/**
	 * @brief The base class for shadow maps.
	 * @extends Emeraude::Graphics::RenderTarget::Abstract This is a render target.
	 */
	class Abstract : public RenderTarget::Abstract
	{
		public:

			/* Settings keys */
			static constexpr auto MaxViewableDistanceKey = "Video/ShadowMaps/MaxViewableDistance";
			static constexpr auto DefaultMaxViewableDistance = 500U;
			static constexpr auto BaseResolutionKey = "Video/ShadowMaps/BaseResolution";
			static constexpr auto DefaultBaseResolution = 512U;
			static constexpr auto EnabledKey = "Video/ShadowMaps/Enabled";
			static constexpr auto DefaultEnabled = true;
			/*static constexpr auto DirectionalLightResolutionKey = "Video/ShadowMaps/DirectionalLightResolution";
			static constexpr auto DefaultDirectionalLightResolution = 1024U;
			static constexpr auto PointLightResolutionKey = "Video/ShadowMaps/PointLightResolution";
			static constexpr auto DefaultPointLightResolution = 256U;
			static constexpr auto SpotLightResolutionKey = "Video/ShadowMaps/SpotLightResolution";
			static constexpr auto DefaultSpotLightResolution = 512U;*/
			static constexpr auto PCFSampleKey = "Video/ShadowMaps/PCFSample";
			static constexpr auto DefaultPCFSample = 0U;
			static constexpr auto PCFRadiusKey = "Video/ShadowMaps/PCFRadius";
			static constexpr auto DefaultPCFRadius = 1.0F;

			static constexpr auto Bias{0.5F};
			static constexpr Libraries::Math::Matrix< 4, float > ScaleBiasMatrix{{
				Bias, 0.0F, 0.0F, 0.0F,
				0.0F, Bias, 0.0F, 0.0F,
				0.0F, 0.0F, Bias, 0.0F,
				Bias, Bias, Bias, 1.0F
			}};

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
			 * @brief Destructs the abstract render to shadow map.
			 */
			~Abstract () override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::videoType() */
			[[nodiscard]]
			MasterControl::VideoType videoType () const noexcept override;

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

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::image() */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::Image > & image () const noexcept final;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::imageView() */
			[[nodiscard]]
			const std::shared_ptr< Vulkan::ImageView > & imageView () const noexcept final;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::isValid() */
			[[nodiscard]]
			bool isValid () const noexcept final;

			/**
			 * @brief Returns the max viewable distance from settings.
			 * @return float
			 */
			[[nodiscard]]
			static float getMaxViewableDistance () noexcept;

			/**
			 * @brief Returns the shadow map resolution from settings.
			 * @return uint32_t
			 */
			[[nodiscard]]
			static uint32_t getBaseResolution () noexcept;

		protected:

			/**
			 * @brief Constructs an abstract render to shadow map.
			 * @param precisions The framebuffer precisions.
			 * @param extent The framebuffer dimensions.
			 * @param renderType The type of render.
			 */
			Abstract (const std::string & name, const FramebufferPrecisions & precisions, const VkExtent3D & extent, RenderType renderType) noexcept;

		private:

			/**
			 * @brief Returns shader create infos for graphics pipeline.
			 * @param modelMatricesType The type of model matrices.
			 * @param outputAsColor Say how shadow output will be.
			 */
			[[deprecated("Bad design, loss of createInfo data")]]
			[[nodiscard]]
			virtual std::vector< VkPipelineShaderStageCreateInfo > getShaderStageCreateInfos (const std::shared_ptr< Vulkan::Device > & device, ModelMatrixType modelMatricesType, bool outputAsColor) const noexcept = 0;

			std::shared_ptr< Vulkan::RenderPass > m_renderPass{};
			std::shared_ptr< Vulkan::Framebuffer > m_framebuffer{};
			std::shared_ptr< Vulkan::Image > m_depthImage{};
			std::shared_ptr< Vulkan::ImageView > m_depthImageView{};
	};
}
