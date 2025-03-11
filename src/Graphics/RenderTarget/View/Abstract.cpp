/*
 * src/Graphics/RenderTarget/View/Abstract.cpp
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

#include "Abstract.hpp"

/* Local inclusions. */
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Instance.hpp"
#include "Vulkan/RenderPass.hpp"
#include "Vulkan/Framebuffer.hpp"
#include "Vulkan/RenderSubPass.hpp"
#include "Graphics/Renderer.hpp"
#include "Window.hpp"
#include "Settings.hpp"
#include "Tracer.hpp"

namespace EmEn::Graphics::RenderTarget::View
{
	using namespace EmEn::Libs;
	using namespace Vulkan;
	using namespace Saphir;

	static constexpr auto TracerTag{"AbstractView"};

	Abstract::Abstract (const std::string & name, const FramebufferPrecisions & precisions, const VkExtent3D & extent, RenderTargetType renderType) noexcept
		: RenderTarget::Abstract(name, precisions, extent, renderType, AVConsole::ConnexionType::Both, true)
	{

	}

	bool
	Abstract::createImages (const std::shared_ptr< Device > & device) noexcept
	{
		/* Color buffer. */
		if ( this->precisions().colorBits() > 0 )
		{
			/* Create the image for color buffer in video memory. */
			m_colorImage = std::make_shared< Image >(
				device,
				VK_IMAGE_TYPE_2D,
				Instance::findColorFormat(device, this->precisions()),
				this->extent(),
				VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
				VK_IMAGE_LAYOUT_UNDEFINED,
				0,
				1,
				1,
				Instance::findSampleCount(this->precisions().samples())
			);
			m_colorImage->setIdentifier(this->id() + "-Color-Image");

			if ( !m_colorImage->createOnHardware() )
			{
				TraceError{TracerTag} << "Unable to create an image (Color buffer) for view '" << this->id() << "' !";

				return false;
			}

			/* Create a view to exploit the image. */
			m_colorImageView = std::make_shared< ImageView >(
				m_colorImage,
				VK_IMAGE_VIEW_TYPE_2D,
				VkImageSubresourceRange{
					.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
					.baseMipLevel = 0,
					.levelCount = m_colorImage->createInfo().mipLevels,
					.baseArrayLayer = 0,
					.layerCount = m_colorImage->createInfo().arrayLayers
				}
			);
			m_colorImageView->setIdentifier(this->id() + "-Color-ImageView");

			if ( !m_colorImageView->createOnHardware() )
			{
				TraceError{TracerTag} << "Unable to create an image view (Color buffer) for view '" << this->id() << "' !";

				return false;
			}
		}

		/* Depth/Stencil buffer. */
		if ( this->precisions().depthBits() > 0 || this->precisions().stencilBits() > 0 )
		{
			/* Create the image for depth/stencil buffer in video memory. */
			m_depthStencilImage = std::make_shared< Image >(
				device,
				VK_IMAGE_TYPE_2D,
				Instance::findDepthStencilFormat(device, this->precisions()),
				this->extent(),
				VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
				VK_IMAGE_LAYOUT_UNDEFINED
			);
			m_depthStencilImage->setIdentifier(this->id() + "-DepthStencil-Image");

			if ( !m_depthStencilImage->createOnHardware() )
			{
				TraceError{TracerTag} << "Unable to create an image (Depth/stencil buffer) for view '" << this->id() << "' !";

				return false;
			}

			/* Create a view to exploit the depth part of the image. */
			if ( this->precisions().depthBits() > 0 )
			{
				m_depthImageView = std::make_shared< ImageView >(
					m_depthStencilImage,
					VK_IMAGE_VIEW_TYPE_2D,
					VkImageSubresourceRange{
						.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
						.baseMipLevel = 0,
						.levelCount = m_depthStencilImage->createInfo().mipLevels,
						.baseArrayLayer = 0,
						.layerCount = m_depthStencilImage->createInfo().arrayLayers
					}
				);
				m_depthImageView->setIdentifier(this->id() + "-Depth-ImageView");

				if ( !m_depthImageView->createOnHardware() )
				{
					TraceError{TracerTag} << "Unable to create an image view (Depth buffer) for view '" << this->id() << "' !";

					return false;
				}
			}

			/* Create a view to exploit the stencil part of the image. */
			if ( this->precisions().stencilBits() > 0 )
			{
				m_stencilImageView = std::make_shared< ImageView >(
					m_depthStencilImage,
					VK_IMAGE_VIEW_TYPE_2D,
					VkImageSubresourceRange{
						.aspectMask = VK_IMAGE_ASPECT_STENCIL_BIT,
						.baseMipLevel = 0,
						.levelCount = m_depthStencilImage->createInfo().mipLevels,
						.baseArrayLayer = 0,
						.layerCount = m_depthStencilImage->createInfo().arrayLayers
					}
				);
				m_stencilImageView->setIdentifier(this->id() + "-Stencil-ImageView");

				if ( !m_stencilImageView->createOnHardware() )
				{
					TraceError{TracerTag} << "Unable to create an image view (Stencil buffer) for view '" << this->id() << "' !";

					return false;
				}
			}
		}

		return true;
	}

	std::shared_ptr< RenderPass >
	Abstract::createRenderPass (Renderer & renderer) const noexcept
	{
		/* FIXME: The identifier must reflect the enabled attachments !!! */
		auto renderPass = renderer.getRenderPass(ViewRender, 0);

		if ( !renderPass->isCreated() )
		{
			/* Prepare a sub-pass for the render pass. */
			RenderSubPass subPass{VK_PIPELINE_BIND_POINT_GRAPHICS, 0};

			/* Color buffer. */
			if ( this->precisions().colorBits() > 0 )
			{
				renderPass->addAttachmentDescription(VkAttachmentDescription{
					.flags = 0,
					.format = m_colorImage->createInfo().format,
					.samples = VK_SAMPLE_COUNT_1_BIT,
					.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
					.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
					.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
					.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
					.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR
				});

				subPass.addColorAttachment(0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);
			}

			/* Depth/Stencil buffer. */
			if ( this->precisions().depthBits() > 0 || this->precisions().stencilBits() > 0 )
			{
				renderPass->addAttachmentDescription(VkAttachmentDescription{
					.flags = 0,
					.format = m_depthStencilImage->createInfo().format,
					.samples = VK_SAMPLE_COUNT_1_BIT,
					.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
					.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
					.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
					.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
					.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL
				});

				subPass.setDepthStencilAttachment(1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
			}

			renderPass->addSubPass(subPass);

			//VkSubpassDependency subpassDependency{};
			//subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
			//subpassDependency.dstSubpass = 0;
			//subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			//subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
			//subpassDependency.srcAccessMask = 0;
			//subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
			//subpassDependency.dependencyFlags = 0;

			//renderPass->addSubpassDependency(subpassDependency);

			if ( !renderPass->createOnHardware() )
			{
				TraceError{TracerTag} << "Unable to create the render pass for view '" << this->id() << "' !";

				return nullptr;
			}
		}

		return renderPass;
	}

	bool
	Abstract::createFramebuffer (const std::shared_ptr< RenderPass > & renderPass) noexcept
	{
		m_framebuffer = std::make_shared< Framebuffer >(renderPass, this->extent());
		m_framebuffer->setIdentifier(this->id() + "-Main-Framebuffer");

		/* Color buffer. */
		if ( this->precisions().colorBits() > 0 )
		{
			m_framebuffer->addAttachment(m_colorImageView->handle());
		}

		/* Depth buffer. */
		if ( this->precisions().depthBits() > 0 )
		{
			m_framebuffer->addAttachment(m_depthImageView->handle());
		}

		/* Stencil buffer. */
		if ( this->precisions().stencilBits() > 0 )
		{
			m_framebuffer->addAttachment(m_stencilImageView->handle());
		}

		if ( !m_framebuffer->createOnHardware() )
		{
			TraceError{TracerTag} << "Unable to create the framebuffer for view '" << this->id() << "' !";

			return false;
		}

		return true;
	}

	bool
	Abstract::onCreate (Renderer & renderer) noexcept
	{
		if ( !this->createImages(renderer.device()) )
		{
			TraceError{TracerTag} << "Unable to create image buffers for view '" << this->id() << "' !";

			return false;
		}

		const auto renderPass = this->createRenderPass(renderer);

		if ( renderPass == nullptr )
		{
			return false;
		}

		return this->createFramebuffer(renderPass);
	}

	void
	Abstract::onDestroy () noexcept
	{
		/* Depth stencil buffer. */
		m_stencilImageView.reset();
		m_depthImageView.reset();
		m_depthStencilImage.reset();

		/* Color buffer */
		m_colorImageView.reset();
		m_colorImage.reset();

		/* Framebuffer */
		m_framebuffer.reset();
	}

	bool
	Abstract::isValid () const noexcept
	{
		if ( m_framebuffer == nullptr || !m_framebuffer->isCreated() )
		{
			TraceError{TracerTag} << "The render target '" << this->id() << "' (View) framebuffer is missing or not created !";

			return false;
		}

		if ( m_colorImage == nullptr || !m_colorImage->isCreated() )
		{
			TraceError{TracerTag} << "The render target '" << this->id() << "' (View) color image is missing or not created !";

			return false;
		}

		if ( m_colorImageView == nullptr || !m_colorImageView->isCreated() )
		{
			TraceError{TracerTag} << "The render target '" << this->id() << "' (View) color image view is missing or not created !";

			return false;
		}

		if ( m_depthStencilImage == nullptr || !m_depthStencilImage->isCreated() )
		{
			TraceError{TracerTag} << "The render target '" << this->id() << "' (View) depth/stencil image is missing or not created !";

			return false;
		}

		if ( m_depthImageView == nullptr || !m_depthImageView->isCreated() )
		{
			TraceError{TracerTag} << "The render target '" << this->id() << "' (View) depth image view is missing or not created !";

			return false;
		}

		if ( m_stencilImageView == nullptr || !m_stencilImageView->isCreated() )
		{
			TraceError{TracerTag} << "The render target '" << this->id() << "' (View) stencil image view is missing or not created !";

			return false;
		}

		return true;
	}

	uint32_t
	Abstract::getWidth () noexcept
	{
		auto * settings = Settings::instance();

		if ( settings->get< bool >(VideoFullscreenEnabledKey, false) )
		{
			return settings->get< uint32_t >(VideoFullscreenWidthKey, DefaultVideoFullscreenWidth);
		}

		return settings->get< uint32_t >(VideoWindowWidthKey, DefaultVideoWindowWidth);
	}

	uint32_t
	Abstract::getHeight () noexcept
	{
		auto * settings = Settings::instance();

		if ( settings->get< bool >(VideoFullscreenEnabledKey, false) )
		{
			return settings->get< uint32_t >(VideoFullscreenHeightKey, DefaultVideoFullscreenHeight);
		}

		return Settings::instance()->get< uint32_t >(VideoWindowHeightKey, DefaultVideoWindowHeight);
	}
}
