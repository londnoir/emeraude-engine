/*
 * Emeraude/Graphics/RenderTarget/Abstract.hpp
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
#include <array>
#include <memory>
#include <string>

/* Local inclusions for inheritances. */
#include "MasterControl/AbstractVirtualVideoDevice.hpp"

/* Local inclusions for usages. */
#include "Graphics/FramebufferPrecisions.hpp"
#include "Graphics/Types.hpp"

/* Third-party inclusions. */
#include "Third-Party-Inclusion/vulkan.hpp"

/* Forward declarations. */
namespace Emeraude
{
	namespace Graphics
	{
		class ViewMatricesInterface;
	}

	namespace Vulkan
	{
		class Device;
		class Framebuffer;
		class RenderPass;
		class Image;
		class ImageView;
	}
}

namespace Emeraude::Graphics::RenderTarget
{
	/**
	 * @brief The base class for all render targets.
	 * @extends Emeraude::MasterControl::AbstractVirtualVideoDevice This is a virtual video device.
	 */
	class Abstract : public MasterControl::AbstractVirtualVideoDevice
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
			 * @brief Destructs an abstract render target.
			 */
			~Abstract () override = default;

			/**
			 * @brief Returns whether the render target is out of date.
			 * @note Always return true with automatic rendering ON.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isRenderOutOfDate () const noexcept final;

			/**
			 * @brief Returns whether the render target is made every frame.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isAutomaticRendering () const noexcept final;

			/**
			 * @brief Sets the automatic rendering state.
			 * @param state The state.
			 */
			virtual void setAutomaticRenderingState (bool state) noexcept final;

			/**
			 * @brief Discard the render.
			 * @note Ineffective with automatic rendering ON.
			 */
			virtual void setRenderOutOfDate () noexcept final;

			/**
			 * @brief Sets the render is finished.
			 * @note Ineffective with automatic rendering ON.
			 */
			virtual void setRenderFinished () noexcept final;

			/**
			 * @brief Returns the precisions of the framebuffer.
			 * @return const FramebufferPrecisions &
			 */
			[[nodiscard]]
			virtual const FramebufferPrecisions & precisions () const noexcept final;

			/**
			 * @brief Returns the dimensions of the framebuffer.
			 * @return const VkExtent3D &
			 */
			[[nodiscard]]
			virtual const VkExtent3D & extent () const noexcept final;

			/**
			 * @brief Returns the render type.
			 * @return RenderType
			 */
			[[nodiscard]]
			virtual RenderType renderType () const noexcept final;

			/**
			 * @brief Returns the aspect ratio of the render target.
			 * @return float
			 */
			[[nodiscard]]
			virtual float aspectRatio () const noexcept;

			/**
			 * @brief Creates the render target in the video memory.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool createOnHardware () noexcept = 0;

			/**
			 * @brief Destroys the render target from the video memory.
			 * @return bool
			 */
			virtual bool destroyFromHardware () noexcept = 0;

			/**
			 * @brief Returns whether the render target is a cubemap.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isCubemap () const noexcept = 0;

			/**
			 * @brief Returns the render-pass.
			 * @return const Vulkan::RenderPass *
			 */
			[[nodiscard]]
			virtual const Vulkan::RenderPass * renderPass () const noexcept = 0;

			/**
			 * @brief Returns the framebuffer.
			 * @return const Vulkan::Framebuffer *
			 */
			[[nodiscard]]
			virtual const Vulkan::Framebuffer * framebuffer () const noexcept = 0;

			/**
			 * @brief Gives access to the main hardware image object of the render target.
			 * @deprecated
			 * @return const std::shared_ptr< Vulkan::Image > &
			 */
			[[nodiscard]]
			virtual const std::shared_ptr< Vulkan::Image > & image () const noexcept = 0;

			/**
			 * @brief Gives access to the main hardware image view object of the render target.
			 * @deprecated
			 * @return const std::shared_ptr< Vulkan::ImageView > &
			 */
			[[nodiscard]]
			virtual const std::shared_ptr< Vulkan::ImageView > & imageView () const noexcept = 0;

			/**
			 * @brief Returns the const access to view matrices object.
			 * @return const ViewMatricesInterface &
			 */
			[[nodiscard]]
			virtual const ViewMatricesInterface & viewMatrices () const noexcept = 0;

			/**
			 * @brief Returns the access to view matrices object.
			 * @return ViewMatricesInterface &
			 */
			[[nodiscard]]
			virtual ViewMatricesInterface & viewMatrices () noexcept = 0;

			/**
			 * @brief Returns whether the render target is valid.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isValid () const noexcept = 0;

		protected:

			/**
			 * @brief Constructs an abstract render target.
			 * @param name A reference to a string for the name of the video device.
			 * @param precisions The framebuffer precisions.
			 * @param extent The framebuffer dimensions.
			 * @param renderType The type of render.
			 * @param allowedConnexionType The type of connexion this virtual device allows.
			 */
			Abstract (const std::string & name, const FramebufferPrecisions & precisions, const VkExtent3D & extent, RenderType renderType, MasterControl::ConnexionType allowedConnexionType) noexcept;

			/**
			 * @brief Sets extents of the render target.
			 * @param extent A reference to the extent.
			 */
			void setExtent (const VkExtent3D & extent) noexcept;

			/**
			 * @brief Creates a color buffer.
			 * @param device A reference to a graphics device smart pointer.
			 * @param image A reference to an image smart pointer.
			 * @param imageView A reference to an image view smart pointer.
			 * @param purposeId A reference to a string to identify buffers.
			 * @return bool
			 */
			[[nodiscard]]
			bool createColorBuffer (const std::shared_ptr< Vulkan::Device > & device, std::shared_ptr< Vulkan::Image > & image, std::shared_ptr< Vulkan::ImageView > & imageView, const std::string & purposeId) const noexcept;

			/**
			 * @brief Creates a depth buffer.
			 * @param device A reference to a graphics device smart pointer.
			 * @param image A reference to an image smart pointer.
			 * @param imageView A reference to an image view smart pointer.
			 * @param purposeId A reference to a string to identify buffers.
			 * @return bool
			 */
			[[nodiscard]]
			bool createDepthBuffer (const std::shared_ptr< Vulkan::Device > & device, std::shared_ptr< Vulkan::Image > & image, std::shared_ptr< Vulkan::ImageView > & imageView, const std::string & purposeId) const noexcept;

			/**
			 * @brief Creates a depth+stencil buffer.
			 * @param device A reference to a graphics device smart pointer.
			 * @param image A reference to an image smart pointer.
			 * @param depthImageView A reference to an image view smart pointer.
			 * @param stencilImageView A reference to an image view smart pointer.
			 * @param purposeId A reference to a string to identify buffers.
			 * @return bool
			 */
			[[nodiscard]]
			bool createDepthStencilBuffer (const std::shared_ptr< Vulkan::Device > & device, std::shared_ptr< Vulkan::Image > & image, std::shared_ptr< Vulkan::ImageView > & depthImageView, std::shared_ptr< Vulkan::ImageView > & stencilImageView, const std::string & purposeId) noexcept;

		private:

			/* Flag names. */
			static constexpr auto RenderOutOfDate = 0UL;
			static constexpr auto AutomaticRendering = 1UL;

			FramebufferPrecisions m_precisions{};
			VkExtent3D m_extent{};
			RenderType m_renderType;
			std::array< bool, 8 > m_flags{ // NOLINT
				true/*RenderOutOfDate*/,
				false/*AutomaticRendering*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
