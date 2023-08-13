/*
 * Emeraude/Vulkan/SwapChain.cpp
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

#include "SwapChain.hpp"

/* Local inclusions */
#include "Device.hpp"
#include "Framebuffer.hpp"
#include "Image.hpp"
#include "ImageView.hpp"
#include "Instance.hpp"
#include "Queue.hpp"
#include "RenderPass.hpp"
#include "Sync/Fence.hpp"
#include "Sync/Semaphore.hpp"
#include "Tracer.hpp"
#include "Utility.hpp"
#include "Graphics/Renderer.hpp"
#include "Graphics/RenderTarget/View/Abstract.hpp"

namespace Emeraude::Vulkan
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Graphics;

	SwapChain::SwapChain (const std::shared_ptr< Device > & device, Window & window) noexcept
		: AbstractDeviceDependentObject(device), Abstract(ClassId, {}, {}, RenderType::View, MasterControl::ConnexionType::Input),
		  m_window(&window)
	{
		m_window->surface()->update(device);
	}

	SwapChain::~SwapChain ()
	{
		this->destroyFromHardware();
	}

	void
	SwapChain::onSourceConnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.create(*this);
	}

	void
	SwapChain::onSourceDisconnected (AbstractVirtualVideoDevice * /*sourceDevice*/) noexcept
	{
		m_viewMatrices.destroy();
	}

	MasterControl::VideoType
	SwapChain::videoType () const noexcept
	{
		return MasterControl::VideoType::View;
	}

	bool
	SwapChain::isCubemap () const noexcept
	{
		return false;
	}

	const RenderPass *
	SwapChain::renderPass () const noexcept
	{
		return m_renderPass.get();
	}

	const Framebuffer *
	SwapChain::framebuffer () const noexcept
	{
		return m_framebuffers.at(m_currentFrame).get();
	}

	const std::shared_ptr< Vulkan::Image > &
	SwapChain::image () const noexcept
	{
		return m_images[m_currentFrame];
	}

	const std::shared_ptr< Vulkan::ImageView > &
	SwapChain::imageView () const noexcept
	{
		return m_imageViews[m_currentFrame];
	}

	const ViewMatricesInterface &
	SwapChain::viewMatrices () const noexcept
	{
		return m_viewMatrices;
	}

	ViewMatricesInterface &
	SwapChain::viewMatrices () noexcept
	{
		return m_viewMatrices;
	}

	bool
	SwapChain::isValid () const noexcept
	{
		if ( !this->isCreated() )
		{
			return false;
		}

		return m_flags[Ready];
	}

	VkSwapchainKHR
	SwapChain::handle () const noexcept
	{
		return m_handle;
	}

	VkSwapchainCreateInfoKHR
	SwapChain::createInfo () const noexcept
	{
		return m_createInfo;
	}

	uint32_t
	SwapChain::imageCount () const noexcept
	{
		return m_imageCount;
	}

	bool
	SwapChain::isDegraded () const noexcept
	{
		return m_flags[SwapChainRecreationRequested];
	}

	bool
	SwapChain::createOnHardware () noexcept
	{
		if ( !this->checkPrerequisites() )
		{
			Tracer::error(ClassId, "Prerequisites are not met to build the swap chain !");

			return false;
		}

		if ( !this->createBaseSwapChain() )
		{
			Tracer::error(ClassId, "Unable to create the base of the swap chain !");

			return false;
		}

		if ( !this->prepareFrameData() )
		{
			Tracer::error(ClassId, "Unable to prepare data to complete the swap chain !");

			return false;
		}

		if ( !this->createFramebuffer() )
		{
			Tracer::error(ClassId, "Unable to complete the framebuffer !");

			return false;
		}

		if ( !this->createSynchronizationPrimitives() )
		{
			Tracer::error(ClassId, "Unable to create synchronization primitives !");

			return false;
		}

		this->setCreated();

		TraceSuccess{ClassId} << "The swap chain " << m_handle << " (" << this->identifier() << ") is successfully created !";

		m_flags[Ready] = true;

		return true;
	}

	bool
	SwapChain::recreate () noexcept
	{
		this->resetFramebuffer();

		if ( !this->createBaseSwapChain(m_handle) )
		{
			Tracer::error(ClassId, "Unable to recreate the base of the swap chain !");

			return false;
		}

		if ( !this->createFramebuffer() )
		{
			Tracer::error(ClassId, "Unable to complete the framebuffer !");

			return false;
		}

		TraceSuccess{ClassId} << "The swap chain " << m_handle << " (" << this->identifier() << ") is successfully recreated !";

		m_flags[Ready] = true;
		m_flags[SwapChainRecreationRequested] = false;

		return true;
	}

	bool
	SwapChain::destroyFromHardware () noexcept
	{
		if ( !this->hasDevice() )
		{
			TraceError{ClassId} << "No device to destroy the swap chain " << m_handle << " (" << this->identifier() << ") !";

			return false;
		}

		this->device()->waitIdle();

		this->destroySynchronizationPrimitives();

		this->destroyFramebuffer();

		this->destroyBaseSwapChain();

		this->setDestroyed();

		return true;
	}

	void
	SwapChain::resetFramebuffer () noexcept
	{
		m_flags[Ready] = false;

		/* Clear the render-pass. */
		m_renderPass->destroyFromHardware();

		for ( size_t imageIndex = 0; imageIndex < m_imageCount; imageIndex++ )
		{
			/* Clear the framebuffer. */
			m_framebuffers[imageIndex]->destroyFromHardware();

			/* Clear the color buffer. */
			m_imageViews[imageIndex]->destroyFromHardware();
			m_images[imageIndex]->destroyFromHardware();

			/* Clear the depth+stencil buffer. */
			m_depthImageViews[imageIndex]->destroyFromHardware();
			m_depthStencilImages[imageIndex]->destroyFromHardware();

			/* Reset the image fence. */
			m_inFlightFences[imageIndex]->recreate();
		}

		m_currentFrame = 0;
	}

	void
	SwapChain::destroyFramebuffer () noexcept
	{
		m_flags[Ready] = false;

		m_renderPass.reset();

		m_framebuffers.clear();

		m_depthImageViews.clear();
		m_depthStencilImages.clear();

		m_imageViews.clear();
		m_images.clear();
	}

	bool
	SwapChain::checkPrerequisites () noexcept
	{
		if ( !this->hasDevice() )
		{
			Tracer::error(ClassId, "No device to create the swap chain !");

			return false;
		}

		if ( m_window == nullptr )
		{
			Tracer::error(ClassId, "No handle to create the swap chain !");

			return false;
		}

		if ( m_window->surface() == nullptr )
		{
			Tracer::error(ClassId, "The surface pointer of the handle is null !");

			return false;
		}

		return true;
	}

	bool
	SwapChain::createBaseSwapChain (VkSwapchainKHR oldSwapChain) noexcept
	{
		const auto surfaceFormat = this->chooseSurfaceFormat();
		const auto & capabilities = m_window->surface()->capabilities();

#ifdef DEBUG
		TraceDebug{ClassId} << "\n" << Surface::getCapabilitiesString(capabilities);
#endif

		m_createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		m_createInfo.pNext = nullptr;
		m_createInfo.flags = 0;
		m_createInfo.surface = m_window->surface()->handle();
		m_createInfo.minImageCount = this->chooseMinimumImageCount();
		m_createInfo.imageFormat = surfaceFormat.format;
		m_createInfo.imageColorSpace = surfaceFormat.colorSpace;
		m_createInfo.imageExtent = this->chooseSwapExtent();
		m_createInfo.imageArrayLayers = 1;
		m_createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
		//auto index = device->getFamilyQueueIndex(VK_QUEUE_GRAPHICS_BIT);

		/*QueueFamilyIndices indices = this->findQueueFamilies(m_device->physicalDeviceHandle());

			uint32_t queueFamilyIndices[] = {indices.graphicsFamily.value(), indices.presentFamily.value()};

			if ( indices.graphicsFamily != indices.presentFamily )
			{
				m_createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
				m_createInfo.queueFamilyIndexCount = 2;
				m_createInfo.pQueueFamilyIndices = queueFamilyIndices;
			}
			else*/
		{
			m_createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE; /* Performance ! */
			m_createInfo.queueFamilyIndexCount = 0; /* Optional */
			m_createInfo.pQueueFamilyIndices = nullptr; /* Optional */
		}
		m_createInfo.preTransform = capabilities.currentTransform; /* NOTE: No transformation. Check "supportedTransforms" in "capabilities" */
		m_createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
		m_createInfo.presentMode = VK_PRESENT_MODE_FIFO_KHR;//this->choosePresentMode();
		m_createInfo.clipped = VK_TRUE;
		m_createInfo.oldSwapchain = oldSwapChain;

		const auto result = vkCreateSwapchainKHR(
			this->device()->handle(),
			&m_createInfo,
			nullptr,
			&m_handle
		);

		/* NOTE: Destroy the previous swap chain if exists. */
		if ( m_createInfo.oldSwapchain != VK_NULL_HANDLE )
		{
			vkDestroySwapchainKHR(
				this->device()->handle(),
				m_createInfo.oldSwapchain,
				nullptr
			);
		}

		if ( result != VK_SUCCESS )
		{
			TraceFatal{ClassId} << "Unable to create the swap chain : " << vkResultToCString(result) << " !";

			return false;
		}

		this->setExtent({m_createInfo.imageExtent.width, m_createInfo.imageExtent.height, 1});

		return true;
	}

	void
	SwapChain::destroyBaseSwapChain () noexcept
	{
		m_flags[Ready] = false;

		if ( m_handle != VK_NULL_HANDLE )
		{
			vkDestroySwapchainKHR(this->device()->handle(), m_handle, nullptr);

			TraceSuccess{ClassId} << "The swap chain " << m_handle << " (" << this->identifier() << ") is gracefully destroyed !";

			m_handle = VK_NULL_HANDLE;
		}
	}

	bool
	SwapChain::prepareFrameData () noexcept
	{
		/* NOTE: Will set the image count for the swap chain. */
		const auto result = vkGetSwapchainImagesKHR(this->device()->handle(), m_handle, &m_imageCount, nullptr);

		if ( result != VK_SUCCESS )
		{
			TraceFatal{ClassId} << "Unable to get image count from the swap chain : " << vkResultToCString(result) << " !";

			return false;
		}

		if ( m_imageCount == 0 )
		{
			Tracer::fatal(ClassId, "Unable to get the image count from the swap chain !");

			return {};
		}

		/* Framebuffer */
		m_framebuffers.resize(m_imageCount);

		/* Color buffer */
		m_images.resize(m_imageCount);
		m_imageViews.resize(m_imageCount);

		/* Depth+Stencil buffer */
		m_depthStencilImages.resize(m_imageCount);
		m_depthImageViews.resize(m_imageCount);
		m_stencilImageViews.resize(m_imageCount);

		/* Synchronization primitives */
		m_imageAvailableSemaphores.resize(m_imageCount);
		m_renderFinishedSemaphores.resize(m_imageCount);
		m_inFlightFences.resize(m_imageCount);

		return true;
	}

	std::vector< VkImage >
	SwapChain::retrieveSwapChainImages () noexcept
	{
		std::vector< VkImage > imageHandles{m_imageCount, VK_NULL_HANDLE};

		const auto result = vkGetSwapchainImagesKHR(
			this->device()->handle(),
			m_handle,
			&m_imageCount, imageHandles.data()
		);

		if ( result != VK_SUCCESS )
		{
			TraceFatal{ClassId} << "Unable to get images from the swap chain : " << vkResultToCString(result) << " !";

			return {};
		}

		return imageHandles;
	}

	bool
	SwapChain::createFramebuffer () noexcept
	{
		if ( m_imageCount == 0 )
		{
			Tracer::error(ClassId, "Unable to create the swap chain without image !");

			return false;
		}

		const auto swapChainImages = this->retrieveSwapChainImages();

		if ( swapChainImages.empty() )
		{
			return false;
		}

		/* Prepare the render pass for attachments. */
		m_renderPass = std::make_shared< RenderPass >(this->device());
		m_renderPass->setIdentifier("SwapChain-Main-RenderPass");

		/* Prepare a subpass for the render pass. */
		RenderSubpass subpass{VK_PIPELINE_BIND_POINT_GRAPHICS, 0};

		for ( size_t imageIndex = 0; imageIndex < m_imageCount; ++imageIndex )
		{
			/* Prepare the framebuffer for attachments. */
			m_framebuffers[imageIndex] = std::make_unique< Framebuffer >(m_renderPass, this->extent());
			m_framebuffers[imageIndex]->setIdentifier((std::stringstream{} << "SwapChain-Frame" << imageIndex << "-Framebuffer").str());

			/* Color buffer. */
			{
				const auto purposeId = (std::stringstream{} << "SwapChain-ColorBuffer" << imageIndex).str();

				if ( !this->createColorBuffer(swapChainImages[imageIndex], m_images[imageIndex], m_imageViews[imageIndex], purposeId) )
				{
					TraceFatal{ClassId} << "Unable to create the color buffer #" << imageIndex << " !";

					return false;
				}

				if ( imageIndex == 0 )
				{
					m_renderPass->addAttachmentDescription(VkAttachmentDescription{
						.flags = 0,
						.format = m_images[imageIndex]->createInfo().format,
						.samples = m_images[imageIndex]->createInfo().samples,
						.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
						.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
						.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
						.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
						.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
						.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
					});

					subpass.addColorAttachment(0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

					TraceInfo{ClassId} << "Image (color) #" << imageIndex << " attached to the render pass !";
				}

				m_framebuffers[imageIndex]->addAttachment(m_imageViews[imageIndex]->handle());

				TraceInfo{ClassId} << "Image view (color) #" << imageIndex << " attached to the framebuffer #" << imageIndex << " !";
			}

			/* Depth/Stencil buffer. */
			{
				const auto purposeId = (std::stringstream{} << "SwapChain-DepthBuffer" << imageIndex).str();

				if ( !this->createDepthBuffer(this->device(), m_depthStencilImages[imageIndex], m_depthImageViews[imageIndex], purposeId) )
				{
					TraceFatal{ClassId} << "Unable to create the depth buffer #" << imageIndex << " !";

					return false;
				}

				if ( imageIndex == 0 )
				{
					m_renderPass->addAttachmentDescription(VkAttachmentDescription{
						.flags = 0,
						.format = m_depthStencilImages[imageIndex]->createInfo().format,
						.samples = m_depthStencilImages[imageIndex]->createInfo().samples,
						.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
						.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
						.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
						.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
						.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
						.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
					});

					subpass.setDepthStencilAttachment(1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

					TraceInfo{ClassId} << "Image (depth/stencil) #" << imageIndex << " attached to the render pass !";
				}

				m_framebuffers[imageIndex]->addAttachment(m_depthImageViews[imageIndex]->handle());

				TraceInfo{ClassId} << "Image view (depth/stencil) #" << imageIndex << " attached to the framebuffer #" << imageIndex << " !";
			}

			if ( imageIndex == 0 )
			{
				m_renderPass->addSubpass(subpass);

				//VkSubpassDependency subpassDependency{};
				//subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
				//subpassDependency.dstSubpass = 0;
				//subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
				//subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
				//subpassDependency.srcAccessMask = 0;
				//subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
				//subpassDependency.dependencyFlags = 0;

				//m_renderPass->addSubpassDependency(subpassDependency);

				if ( m_renderPass->createOnHardware() )
				{
					Tracer::success(ClassId, "Render pass is successfully created !");
				}
				else
				{
					Tracer::error(ClassId, "Unable to create a render pass !");

					return false;
				}
			}

			if ( m_framebuffers[imageIndex]->createOnHardware() )
			{
				TraceSuccess{ClassId} << "Framebuffer #" << imageIndex << " is successfully created !";
			}
			else
			{
				TraceError{ClassId} << "Unable to create a framebuffer #" << imageIndex << " !";

				return false;
			}
		}

		return true;
	}

	bool
	SwapChain::createColorBuffer (const VkImage & swapChainImage, std::shared_ptr< Vulkan::Image > & image, std::shared_ptr< Vulkan::ImageView > & imageView, const std::string & purposeId) noexcept
	{
		/* NOTE: Create an image from existing data from the swap chain. */
		image = Image::createFromSwapChain(this->device(), swapChainImage, m_createInfo);
		image->setIdentifier(purposeId + "-Image");

		if ( swapChainImage != image->handle() )
		{
			TraceFatal{ClassId} << "Unable to create image '" << purposeId << "' !";

			return false;
		}

		const auto & imageCreateInfo = image->createInfo();

		imageView = std::make_shared< ImageView >(
			image,
			VK_IMAGE_VIEW_TYPE_2D,
			VkImageSubresourceRange{
				.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
				.baseMipLevel = 0,
				.levelCount = imageCreateInfo.mipLevels,
				.baseArrayLayer = 0,
				.layerCount = imageCreateInfo.arrayLayers
			}
		);
		imageView->setIdentifier(purposeId + "-ImageView");

		if ( !imageView->createOnHardware() )
		{
			TraceFatal{ClassId} << "Unable to create image view '" << purposeId << "' !";

			return false;
		}

		return true;
	}

	bool
	SwapChain::createSynchronizationPrimitives () noexcept
	{
		for ( size_t imageIndex = 0; imageIndex < m_imageCount; ++imageIndex )
		{
			m_imageAvailableSemaphores[imageIndex] = std::make_unique< Sync::Semaphore >(this->device());
			m_imageAvailableSemaphores[imageIndex]->setIdentifier((std::stringstream{} << "SwapChain-ImageAvailable" << imageIndex << "-Semaphore").str());

			if ( !m_imageAvailableSemaphores[imageIndex]->createOnHardware() )
			{
				TraceError{ClassId} << "Unable to create a semaphore #" << imageIndex << " for image available !";

				return false;
			}

			m_renderFinishedSemaphores[imageIndex] = std::make_unique< Sync::Semaphore >(this->device());
			m_renderFinishedSemaphores[imageIndex]->setIdentifier((std::stringstream{} << "SwapChain-RenderFinished" << imageIndex << "-Semaphore").str());

			if ( !m_renderFinishedSemaphores[imageIndex]->createOnHardware() )
			{
				TraceError{ClassId} << "Unable to create a semaphore #" << imageIndex << " for image finished !";

				return false;
			}

			m_inFlightFences[imageIndex] = std::make_unique< Sync::Fence >(this->device());
			m_inFlightFences[imageIndex]->setIdentifier((std::stringstream{} << "SwapChain-ImageInFlight" << imageIndex << "-Fence").str());

			if ( !m_inFlightFences[imageIndex]->createOnHardware() )
			{
				TraceError{ClassId} << "Unable to create a fence #" << imageIndex << " for in-flight !";

				return false;
			}
		}

		return true;
	}

	void
	SwapChain::destroySynchronizationPrimitives () noexcept
	{
		m_flags[Ready] = false;

		m_inFlightFences.clear();
		m_renderFinishedSemaphores.clear();
		m_imageAvailableSemaphores.clear();
	}

	bool
	SwapChain::acquireNextImage (uint32_t & imageIndex) noexcept
	{
		if ( !m_flags[Ready] )
		{
			return false;
		}

		if ( !m_inFlightFences[m_currentFrame]->wait() )
		{
			Tracer::error(ClassId, "Something wrong happens while waiting the fence !");

			return false;
		}

		const auto result = vkAcquireNextImageKHR(
			this->device()->handle(),
			m_handle,
			std::numeric_limits< uint64_t >::max(),
			m_imageAvailableSemaphores[m_currentFrame]->handle(),
			VK_NULL_HANDLE,
			&imageIndex
		);

		switch ( result )
		{
			case VK_SUCCESS :
				return true;

			case VK_TIMEOUT :
				TraceWarning{ClassId} << "VK_TIMEOUT @ acquisition for image #" << imageIndex << " !";

				return false;

			case VK_ERROR_OUT_OF_DATE_KHR :
			case VK_SUBOPTIMAL_KHR :
				TraceError{ClassId} << vkResultToCString(result) << " @ acquisition for image #" << imageIndex << " !";

				m_flags[SwapChainRecreationRequested] = true;

				return false;

			default:
				TraceError{ClassId} << "Error from the swap chain : " << vkResultToCString(result) << " !";

				return false;
		}
	}

	bool
	SwapChain::submitCommandBuffer (const std::shared_ptr< CommandBuffer > & commandBuffer, const uint32_t & imageIndex) noexcept
	{
		if ( !m_flags[Ready] )
		{
			return false;
		}

		if ( !m_inFlightFences[imageIndex]->wait() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", Something wrong happens while waiting the fence !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return false;
		}

		if ( !m_inFlightFences[m_currentFrame]->reset() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", Unable to reset in-flight fence for image " << m_currentFrame << " !" "\n"; // NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

			return false;
		}

		auto * graphicsQueue = this->device()->getQueue(QueueJob::Presentation, QueuePriority::High);

		if ( !graphicsQueue->submit(commandBuffer, *m_imageAvailableSemaphores[m_currentFrame], VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, *m_renderFinishedSemaphores[m_currentFrame], *m_inFlightFences[m_currentFrame]) )
		{
			return false;
		}

		auto * waitSemaphoreHandle = m_renderFinishedSemaphores[m_currentFrame]->handle();

		VkPresentInfoKHR presentInfo{};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		presentInfo.pNext = nullptr;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = &waitSemaphoreHandle;

		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = &m_handle;

		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = nullptr;

		auto * presentationQueue = this->device()->getQueue(QueueJob::Presentation, QueuePriority::High);

		if ( !presentationQueue->present(&presentInfo, m_flags[SwapChainRecreationRequested]) )
		{
			return false;
		}

		m_currentFrame = (m_currentFrame + 1) % m_imageCount;

		return true;
	}

	uint32_t
	SwapChain::chooseMinimumImageCount () const noexcept
	{
		const auto & capabilities = m_window->surface()->capabilities();

		/* NOTE: minimal images + 1. */
		/*auto imageCount = capabilities.minImageCount + 1;

		if ( capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount )
			imageCount = capabilities.maxImageCount;*/

		/* NOTE: We only use minimum image from capabilities for now. */
		return capabilities.minImageCount;
	}

	VkSurfaceFormatKHR
	SwapChain::chooseSurfaceFormat () const noexcept
	{
		const auto & formats = m_window->surface()->formats();

		/* NOTE: Check for 24bits sRGB */
		const auto formatIt = std::ranges::find_if(formats, [] (auto item) {
			return item.format == VK_FORMAT_B8G8R8A8_SRGB && item.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		});

		return formatIt != formats.cend() ? *formatIt : formats.at(0);
	}

	VkPresentModeKHR
	SwapChain::choosePresentMode () const noexcept
	{
		const auto & presentModes = m_window->surface()->presentModes();

		/*
		 * VK_PRESENT_MODE_IMMEDIATE_KHR (tearing problem)
		 * VK_PRESENT_MODE_MAILBOX_KHR (best, can implement triple-buffering)
		 * VK_PRESENT_MODE_FIFO_KHR (always present)
		 * VK_PRESENT_MODE_FIFO_RELAXED_KHR
		 * VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR
		 * VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR
		 */
		const auto modeIt = std::ranges::find_if(presentModes, [] (auto mode) {
			return mode == VK_PRESENT_MODE_MAILBOX_KHR;
		});

		return modeIt != presentModes.cend() ? *modeIt : VK_PRESENT_MODE_FIFO_KHR;
	}

	VkExtent2D
	SwapChain::chooseSwapExtent () const noexcept
	{
		const auto & capabilities = m_window->surface()->capabilities();

		if ( capabilities.currentExtent.width <= std::numeric_limits< uint32_t >::max() )
		{
			return capabilities.currentExtent;
		}

		const auto & min = capabilities.minImageExtent;
		const auto & max = capabilities.maxImageExtent;

		/* NOTE: Get the current framebuffer dimensions from GLFW. */
		int width = 0;
		int height = 0;

		glfwGetFramebufferSize(m_window->handle(), &width, &height);

		return {
			std::max(min.width, std::min(max.width, static_cast< uint32_t >(width))),
			std::max(min.height, std::min(max.height, static_cast< uint32_t >(height)))
		};
	}

	void
	SwapChain::updateDeviceFromCoordinates (const Coordinates< float > & worldCoordinates, const Vector< 3, float > & worldVelocity) noexcept
	{
		m_viewMatrices.updateViewCoordinates(worldCoordinates, worldVelocity);
	}

	void
	SwapChain::updateProperties (bool isPerspectiveProjection, float distance, float fovOrNear) noexcept
	{
		const auto & extent = this->extent();

		const auto width = static_cast< float >(extent.width);
		const auto height = static_cast< float >(extent.height);

		if ( isPerspectiveProjection )
		{
			m_viewMatrices.updatePerspectiveViewProperties(width, height, distance, fovOrNear);
		}
		else
		{
			m_viewMatrices.updateOrthographicViewProperties(width, height, distance, fovOrNear);
		}
	}
}
