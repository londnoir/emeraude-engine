/*
 * Emeraude/Graphics/RenderTarget/Texture/Abstract.cpp
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

#include "Abstract.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Graphics/Renderer.hpp"
#include "Vulkan/Instance.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Sampler.hpp"

namespace Emeraude::Graphics::RenderTarget::Texture
{
	using namespace Libraries;
	using namespace Libraries::PixelFactory;
	using namespace Vulkan;
	using namespace Saphir;

	constexpr auto TracerTag{"AbstractTexture"};

	Abstract::Abstract (const std::string & name, const FramebufferPrecisions & precisions, const VkExtent3D & extent, RenderType renderType) noexcept
		: RenderTarget::Abstract(name, precisions, extent, renderType, MasterControl::ConnexionType::Both), TextureResource::Abstract(name, 0)
	{

	}

	Abstract::~Abstract ()
	{
		this->destroyFromHardware();
	}

	MasterControl::VideoType
	Abstract::videoType () const noexcept
	{
		return MasterControl::VideoType::Texture;
	}

	bool
	Abstract::isCreated () const noexcept
	{
		if ( m_colorImage == nullptr || !m_colorImage->isCreated() )
		{
			return false;
		}

		if ( m_colorImageView == nullptr || !m_colorImageView->isCreated() )
		{
			return false;
		}

		if ( m_sampler == nullptr || !m_sampler->isCreated() )
		{
			return false;
		}

		return true;
	}

	bool
	Abstract::createOnHardware () noexcept
	{
		auto * renderer = Renderer::instance();

		const auto & device = renderer->device();

		/* Prepare the render pass. */
		m_renderPass = std::make_shared< Vulkan::RenderPass >(device);
		m_renderPass->setIdentifier(this->name() + "-Main-RenderPass");

		/* Prepare a subpass for the render pass. */
		RenderSubpass subpass{VK_PIPELINE_BIND_POINT_GRAPHICS, 0};

		/* Prepare the framebuffer. */
		m_framebuffer = std::make_shared< Vulkan::Framebuffer >(m_renderPass, this->extent());
		m_framebuffer->setIdentifier(this->name() + "-Main-Framebuffer");

		{
			/* Create the color buffer. */
			if ( this->precisions().colorBits() > 0 )
			{
				/* Create the image for color buffer in video memory. */
				m_colorImage = std::make_shared< Image >(
					device,
					VK_IMAGE_TYPE_2D,
					Instance::findColorFormat(device, this->precisions()),
					this->extent(),
					VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
					VK_IMAGE_LAYOUT_UNDEFINED
				);
				m_colorImage->setIdentifier(this->name() + "-Color-Image");

				if ( !m_colorImage->createOnHardware() )
				{
					Tracer::error(TracerTag, "Unable to create a color buffer !");

					return false;
				}

				/* Declare the color attachment to the render pass. */
				m_renderPass->addAttachmentDescription(VkAttachmentDescription{
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

				/* Declare the color attachment to the subpass. */
				subpass.addColorAttachment(0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL);

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
				m_colorImageView->setIdentifier(this->name() + "-Color-ImageView");

				if ( !m_colorImageView->createOnHardware() )
				{
					Tracer::error(TracerTag, "Unable to create a color buffer view !");

					return false;
				}

				/* Add the image view (attachment) to the framebuffer. */
				m_framebuffer->addAttachment(m_colorImageView->handle());
			}

			/* Create the depth/stencil buffer. */
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
				m_depthStencilImage->setIdentifier(this->name() + "-DepthStencil-Image");

				if ( !m_depthStencilImage->createOnHardware() )
				{
					Tracer::error(TracerTag, "Unable to create a depth/stencil buffer !");

					return false;
				}

				/* Declare the depth/stencil attachment to the render pass. */
				m_renderPass->addAttachmentDescription(VkAttachmentDescription{
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

				/* Declare the depth/stencil attachment to the subpass. */
				subpass.setDepthStencilAttachment(1, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

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
					m_depthImageView->setIdentifier(this->name() + "-Depth-ImageView");

					if ( !m_depthImageView->createOnHardware() )
					{
						Tracer::error(TracerTag, "Unable to create a depth buffer view !");

						return false;
					}

					/* Add the image view (attachment) to the framebuffer. */
					m_framebuffer->addAttachment(m_depthImageView->handle());
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
					m_depthImageView->setIdentifier(this->name() + "-Stencil-ImageView");

					if ( !m_stencilImageView->createOnHardware() )
					{
						Tracer::error(TracerTag, "Unable to create a stencil buffer view !");

						return false;
					}

					/* Add the image view (attachment) to the framebuffer. */
					m_framebuffer->addAttachment(m_stencilImageView->handle());
				}
			}
		}

		m_renderPass->addSubpass(subpass);

		/*VkSubpassDependency subpassDependency{};
		subpassDependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		subpassDependency.dstSubpass = 0;
		subpassDependency.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		subpassDependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT | VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
		subpassDependency.srcAccessMask = 0;
		subpassDependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
		subpassDependency.dependencyFlags = 0;

		m_renderPass->addSubpassDependency(subpassDependency);*/

		if ( !m_renderPass->createOnHardware() )
		{
			Tracer::error(TracerTag, "Unable to create a render pass !");

			return false;
		}

		if ( !m_framebuffer->createOnHardware() )
		{
			Tracer::error(TracerTag, "Unable to create a framebuffer !");

			return false;
		}

		return true;
	}

	bool
	Abstract::destroyFromHardware () noexcept
	{
		/* FIXME: Check the coherence of each call to destroy ! */

		/* Depth stencil buffer. */
		{
			if ( m_stencilImageView != nullptr )
			{
				m_stencilImageView->destroyFromHardware();
				m_stencilImageView.reset();
			}

			if ( m_depthImageView != nullptr )
			{
				m_depthImageView->destroyFromHardware();
				m_depthImageView.reset();
			}

			if ( m_depthStencilImage != nullptr )
			{
				m_depthStencilImage->destroyFromHardware();
				m_depthStencilImage.reset();
			}
		}

		/* Color buffer */
		{
			if ( m_colorImageView != nullptr )
			{
				m_colorImageView->destroyFromHardware();
				m_colorImageView.reset();
			}

			if ( m_colorImage != nullptr )
			{
				m_colorImage->destroyFromHardware();
				m_colorImage.reset();
			}
		}

		/* FIXME: The sampler must be shared ! */
		if ( m_sampler != nullptr )
		{
			m_sampler->destroyFromHardware();
			m_sampler.reset();
		}

		/* Framebuffer */
		if ( m_framebuffer != nullptr )
		{
			m_framebuffer->destroyFromHardware();
			m_framebuffer.reset();
		}

		/* Render-pass */
		if ( m_renderPass != nullptr )
		{
			m_renderPass->destroyFromHardware();
			m_renderPass.reset();
		}

		return true;
	}

	const Vulkan::RenderPass *
	Abstract::renderPass () const noexcept
	{
		return m_renderPass.get();
	}

	const Vulkan::Framebuffer *
	Abstract::framebuffer () const noexcept
	{
		return m_framebuffer.get();
	}

	const std::shared_ptr< Image > &
	Abstract::image () const noexcept
	{
		return m_colorImage;
	}

	const std::shared_ptr< ImageView > &
	Abstract::imageView () const noexcept
	{
		return m_colorImageView;
	}

	const std::shared_ptr< Sampler > &
	Abstract::sampler () const noexcept
	{
		return m_sampler;
	}

	const std::shared_ptr< Image > &
	Abstract::depthStencilImage () const noexcept
	{
		return m_depthStencilImage;
	}

	const std::shared_ptr< ImageView > &
	Abstract::depthImageView () const noexcept
	{
		return m_depthImageView;
	}

	const std::shared_ptr< ImageView > &
	Abstract::stencilImageView () const noexcept
	{
		return m_stencilImageView;
	}

	bool
	Abstract::isValid () const noexcept
	{
		if ( m_renderPass == nullptr || !m_renderPass->isCreated() )
		{
			return false;
		}

		if ( m_framebuffer == nullptr || !m_framebuffer->isCreated() )
		{
			return false;
		}

		if ( m_colorImage == nullptr || !m_colorImage->isCreated() )
		{
			return false;
		}

		if ( m_colorImageView == nullptr || !m_colorImageView->isCreated() )
		{
			return false;
		}

		if ( m_depthStencilImage == nullptr || !m_depthStencilImage->isCreated() )
		{
			return false;
		}

		if ( m_depthImageView == nullptr || !m_depthImageView->isCreated() )
		{
			return false;
		}

		if ( m_stencilImageView == nullptr || !m_stencilImageView->isCreated() )
		{
			return false;
		}

		if ( m_sampler == nullptr ||  !m_sampler->isCreated() )
		{
			return false;
		}

		return true;
	}

	bool
	Abstract::load () noexcept
	{
		Tracer::warning(TracerTag, "This resource cannot be loaded !");

		return false;
	}

	bool
	Abstract::load (const Libraries::Path::File &) noexcept
	{
		return this->load();
	}

	bool
	Abstract::load (const Json::Value &) noexcept
	{
		return this->load();
	}

	bool
	Abstract::isGrayScale () const noexcept
	{
		/* FIXME: Scan the create info */
		return false;
	}

	Color< float >
	Abstract::averageColor () const noexcept
	{
		/* FIXME: Compute average color from video memory texture2Ds. */
		return Grey;
	}

	size_t
	Abstract::frameCount () const noexcept
	{
		return 1;
	}

	size_t
	Abstract::duration () const noexcept
	{
		return 0;
	}

	uint32_t
	Abstract::dimensions () const noexcept
	{
		return this->isCubemap() ? 3 : 2;
	}

	bool
	Abstract::isCubemapTexture () const noexcept
	{
		return this->isCubemap();
	}
}
