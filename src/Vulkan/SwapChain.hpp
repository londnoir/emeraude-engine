/*
 * Emeraude/Vulkan/SwapChain.hpp
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
#include "AbstractDeviceDependentObject.hpp"
#include "Graphics/RenderTarget/Abstract.hpp"

/* Local inclusions for usages. */
#include "Graphics/ViewMatrices2DUBO.hpp"
#include "Window.hpp"

/* Forward declarations. */
namespace Emeraude::Vulkan
{
	namespace Sync
	{
		class Semaphore;
		class Fence;
	}

	class RenderPass;
	class Framebuffer;
	class CommandBuffer;
}

namespace Emeraude::Vulkan
{
	/**
	 * @brief The vulkan swap chain class.
	 * @extends Emeraude::AbstractDeviceDependentObject This object needs a device.
	 * @extends Emeraude::Graphics::RenderTarget::Abstract This is a render
	 */
	class SwapChain final : public AbstractDeviceDependentObject, public Graphics::RenderTarget::Abstract
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanSwapChain"};

			/**
			 * @brief Constructs a swap chain.
			 * @param device A reference to a smart pointer of the device in use with the swap chain.
			 */
			SwapChain (const std::shared_ptr< Device > & device, Window & window) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			SwapChain (const SwapChain & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			SwapChain (SwapChain && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			SwapChain & operator= (const SwapChain & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			SwapChain & operator= (SwapChain && copy) noexcept = delete;

			/**
			 * @brief Destructs the swap chain.
			 */
			~SwapChain () override;

			/** @copydoc Emeraude::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::AbstractDeviceDependentObject::recreate() */
			[[nodiscard]]
			bool recreate () noexcept override;

			/** @copydoc Emeraude::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::videoType() */
			[[nodiscard]]
			MasterControl::VideoType videoType () const noexcept override;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::isCubemap() */
			[[nodiscard]]
			bool isCubemap () const noexcept override;

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

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::viewMatrices() const */
			[[nodiscard]]
			const Graphics::ViewMatricesInterface & viewMatrices () const noexcept override;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::viewMatrices() */
			[[nodiscard]]
			Graphics::ViewMatricesInterface & viewMatrices () noexcept override;

			/** @copydoc Emeraude::Graphics::RenderTarget::Abstract::viewMatrices() */
			[[nodiscard]]
			bool isValid () const noexcept override;

			/**
			 * @brief Returns the swap chain vulkan handle.
			 * @return VkSwapchainKHR
			 */
			[[nodiscard]]
			VkSwapchainKHR handle () const noexcept;

			/**
			 * @brief Returns the swap chain create info.
			 * @return VkSwapchainCreateInfoKHR
			 */
			[[nodiscard]]
			VkSwapchainCreateInfoKHR createInfo () const noexcept;

			/**
			 * @brief Returns the number of images in the swap chain.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t imageCount () const noexcept;

			/**
			 * @brief Acquires the next image index available in the swap chain.
			 * @param imageIndex A reference to an unsigned int to store the index.
			 * @return bool
			 */
			bool acquireNextImage (uint32_t & imageIndex) noexcept;

			/**
			 * @brief Submits command buffer to the current rendering image.
			 * @param commandBuffer A reference to a command buffer smart pointer.
			 * @param imageIndex The current rendering image index.
			 * @return bool
			 */
			bool submitCommandBuffer (const std::shared_ptr< CommandBuffer > & commandBuffer, const uint32_t & imageIndex) noexcept;

			/**
			 * @brief Returns whether the swap chain is still valid or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool isDegraded () const noexcept;

		private:

			/** @copydoc Emeraude::MasterControl::AbstractVirtualDevice::updateDeviceFromCoordinates() */
			void updateDeviceFromCoordinates (const Libraries::Math::Coordinates< float > & worldCoordinates, const Libraries::Math::Vector< 3, float > & worldVelocity) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::updateProperties() */
			void updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onSourceConnected() */
			void onSourceConnected (AbstractVirtualVideoDevice * sourceDevice) noexcept override;

			/** @copydoc Emeraude::MasterControl::AbstractVirtualVideoDevice::onSourceDisconnected() */
			void onSourceDisconnected (AbstractVirtualVideoDevice * sourceDevice) noexcept override;

			/**
			 * @brief Returns the minimum image count desired in the swap chain.
			 * @param surface A reference to the surface.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t chooseMinimumImageCount () const noexcept;

			/**
			 * @brief Returns the best surface format.
			 * @return VkSurfaceFormatKHR
			 */
			[[nodiscard]]
			VkSurfaceFormatKHR chooseSurfaceFormat () const noexcept;

			/**
			 * @brief Returns the best present mode.
			 * @return VkPresentModeKHR
			 */
			[[nodiscard]]
			VkPresentModeKHR choosePresentMode () const noexcept;

			/**
			 * @brief Returns the dimensions of the swap chain.
			 * @return VkExtent2D
			 */
			[[nodiscard]]
			VkExtent2D chooseSwapExtent () const noexcept;

			/**
			 * @brief Checks the prerequisites to create a swap chain.
			 * @return bool
			 */
			[[nodiscard]]
			bool checkPrerequisites () noexcept;

			/**
			 * @brief Creates the base swap chain object.
			 * @param oldSwapChain An handle to the previous swap chain. Default none.
			 * @return bool
			 */
			[[nodiscard]]
			bool createBaseSwapChain (VkSwapchainKHR oldSwapChain = VK_NULL_HANDLE) noexcept;

			/**
			 * @brief Destroys the base swap chain object.
			 * @return void
			 */
			void destroyBaseSwapChain () noexcept;

			/**
			 * @brief Prepares data to complete the swap chain framebuffer.
			 * @return bool
			 */
			[[nodiscard]]
			bool prepareFrameData () noexcept;

			/**
			 * @brief Returns images created by the swap chain.
			 * @return std::vector< VkImage >
			 */
			[[nodiscard]]
			std::vector< VkImage > retrieveSwapChainImages () noexcept;

			/**
			 * @brief Creates the global framebuffer metaphor.
			 * @return bool
			 */
			bool createFramebuffer () noexcept;

			/**
			 * @brief Resets the global framebuffer metaphor.
			 * @return void
			 */
			void resetFramebuffer () noexcept;

			/**
			 * @brief Destroys the global framebuffer metaphor.
			 * @return void
			 */
			void destroyFramebuffer () noexcept;

			/**
			 * @brief Creates a color buffer.
			 * @param swapChainImage A reference to swap chain image.
			 * @param image A reference to an image smart pointer.
			 * @param imageView A reference to an image view smart pointer.
			 * @param purposeId A reference to a string to identify buffers.
			 * @return bool
			 */
			[[nodiscard]]
			bool createColorBuffer (const VkImage & swapChainImage, std::shared_ptr< Vulkan::Image > & image, std::shared_ptr< Vulkan::ImageView > & imageView, const std::string & purposeId) noexcept;

			/**
			 * @brief Creates the synchronization primitives.
			 * @return bool
			 */
			[[nodiscard]]
			bool createSynchronizationPrimitives () noexcept;

			/**
			 * @brief Destroys the synchronization primitives.
			 * @return void
			 */
			void destroySynchronizationPrimitives () noexcept;

			/* Flag names. */
			static constexpr auto Ready = 0UL;
			static constexpr auto SwapChainRecreationRequested = 1UL;

			Window * m_window;
			VkSwapchainKHR m_handle{VK_NULL_HANDLE};
			VkSwapchainCreateInfoKHR m_createInfo{};
			uint32_t m_imageCount{0};
			uint32_t m_currentFrame{0};
			std::shared_ptr< RenderPass > m_renderPass{};
			std::vector< std::unique_ptr< Framebuffer > > m_framebuffers{};
			std::vector< std::shared_ptr< Image > > m_images{};
			std::vector< std::shared_ptr< ImageView > > m_imageViews{};
			std::vector< std::shared_ptr< Image > > m_depthStencilImages{};
			std::vector< std::shared_ptr< ImageView > > m_depthImageViews{};
			std::vector< std::shared_ptr< ImageView > > m_stencilImageViews{};
			std::vector< std::unique_ptr< Sync::Semaphore > > m_imageAvailableSemaphores{};
			std::vector< std::unique_ptr< Sync::Semaphore > > m_renderFinishedSemaphores{};
			std::vector< std::unique_ptr< Sync::Fence > > m_inFlightFences{};
			Graphics::ViewMatrices2DUBO m_viewMatrices{};
			std::array< bool, 8 > m_flags{ /* NOLINT(*-magic-numbers) */
				false/*Ready*/,
				false/*SwapChainRecreationRequested*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
