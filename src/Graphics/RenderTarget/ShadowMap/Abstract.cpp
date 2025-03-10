/*
 * src/Graphics/RenderTarget/ShadowMap/Abstract.cpp
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
#include "Vulkan/Framebuffer.hpp"
#include "Vulkan/Image.hpp"
#include "Vulkan/ImageView.hpp"
#include "Vulkan/Instance.hpp"
#include "Vulkan/RenderPass.hpp"
#include "Vulkan/RenderSubPass.hpp"
#include "Graphics/Renderer.hpp"
#include "Settings.hpp"
#include "SettingKeys.hpp"
#include "Tracer.hpp"

namespace Emeraude::Graphics::RenderTarget::ShadowMap
{
	using namespace Libraries;
	using namespace Vulkan;
	using namespace Saphir;

	static constexpr auto TracerTag{"AbstractShadowMap"};

	Abstract::Abstract (const std::string & name, const FramebufferPrecisions & precisions, const VkExtent3D & extent, RenderTargetType renderType) noexcept
		: RenderTarget::Abstract(name, precisions, extent, renderType, MasterControl::ConnexionType::Input, true)
	{

	}

	bool
	Abstract::createImages (const std::shared_ptr< Device > & device) noexcept
	{
		/* Color buffer. */
		if ( this->precisions().colorBits() > 0 )
		{
			TraceWarning{TracerTag} << "Color bits requested for shadow map '" << this->id() << "' !";
		}

		/* Depth/Stencil buffer. */
		if ( this->precisions().depthBits() > 0 || this->precisions().stencilBits() > 0 )
		{
			m_depthImage = std::make_shared< Image >(
				device,
				VK_IMAGE_TYPE_2D,
				Instance::findDepthStencilFormat(device, this->precisions()),
				this->extent(),
				VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT,
				VK_IMAGE_LAYOUT_UNDEFINED
			);
			m_depthImage->setIdentifier(this->id() + "-Depth-Image");

			if ( !m_depthImage->createOnHardware() )
			{
				TraceError{TracerTag} << "Unable to create an image (Depth/Stencil buffer) for shadow map '" << this->id() << "' !";

				return false;
			}

			/* Create a view to exploit the depth part of the image. */
			if ( this->precisions().depthBits() > 0 )
			{
				m_depthImageView = std::make_shared< ImageView >(
					m_depthImage,
					VK_IMAGE_VIEW_TYPE_2D,
					VkImageSubresourceRange{
						.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT,
						.baseMipLevel = 0,
						.levelCount = m_depthImage->createInfo().mipLevels,
						.baseArrayLayer = 0,
						.layerCount = m_depthImage->createInfo().arrayLayers
					}
				);
				m_depthImage->setIdentifier(this->id() + "-Depth-ImageView");

				if ( !m_depthImageView->createOnHardware() )
				{
					TraceError{TracerTag} << "Unable to create an image view (Depth buffer) for shadow map '" << this->id() << "' !";

					return false;
				}
			}

			/* Create a view to exploit the stencil part of the image. */
			if ( this->precisions().stencilBits() > 0 )
			{
				TraceWarning{TracerTag} << "Stencil bits requested for shadow map '" << this->id() << "' !";
			}
		}

		return true;
	}

	std::shared_ptr< RenderPass >
	Abstract::createRenderPass (Renderer & renderer) const noexcept
	{
		/* FIXME: The identifier must reflect the enabled attachments !!! */
		auto renderPass = renderer.getRenderPass(ShadowRender, 0);

		if ( !renderPass->isCreated() )
		{
			/* Prepare a sub-pass for the render pass. */
			RenderSubPass subPass{VK_PIPELINE_BIND_POINT_GRAPHICS, 0};

			/* Color buffer. */
			if ( this->precisions().colorBits() > 0 )
			{
				TraceWarning{TracerTag} << "Color bits requested for shadow map '" << this->id() << "' !";
			}

			/* Depth/Stencil buffer. */
			if ( this->precisions().depthBits() > 0 || this->precisions().stencilBits() > 0 )
			{
				renderPass->addAttachmentDescription(VkAttachmentDescription{
					.flags = 0,
					.format = m_depthImage->createInfo().format,
					.samples = VK_SAMPLE_COUNT_1_BIT,
					.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,
					.storeOp = VK_ATTACHMENT_STORE_OP_STORE,
					.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,
					.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,
					.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,
					.finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_READ_ONLY_OPTIMAL
				});

				subPass.setDepthStencilAttachment(0, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
			}

			renderPass->addSubPass(subPass);

			renderPass->addSubPassDependency({
				.srcSubpass = VK_SUBPASS_EXTERNAL,
				.dstSubpass = 0,
				.srcStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
				.dstStageMask = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
				.srcAccessMask = VK_ACCESS_SHADER_READ_BIT,
				.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
				.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
			});

			renderPass->addSubPassDependency({
				.srcSubpass = 0,
				.dstSubpass = VK_SUBPASS_EXTERNAL,
				.srcStageMask = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
				.dstStageMask = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
				.srcAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
				.dstAccessMask = VK_ACCESS_SHADER_READ_BIT,
				.dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT
			});

			if ( !renderPass->createOnHardware() )
			{
				TraceError{TracerTag} << "Unable to create the render pass for shadow map '" << this->id() << "' !";

				return nullptr;
			}
		}

		return renderPass;
	}

	bool
	Abstract::createFramebuffer (const std::shared_ptr< RenderPass > & renderPass) noexcept
	{
		/* Prepare the framebuffer. */
		m_framebuffer = std::make_shared< Framebuffer >(renderPass, this->extent());
		m_framebuffer->setIdentifier(this->id() + "-Main-Framebuffer");

		/* Color buffer. */
		if ( this->precisions().colorBits() > 0 )
		{
			TraceWarning{TracerTag} << "Color bits requested for shadow map '" << this->id() << "' !";
		}

		/* Depth buffer. */
		if ( this->precisions().depthBits() > 0 )
		{
			m_framebuffer->addAttachment(m_depthImageView->handle());
		}

		/* Stencil buffer. */
		if ( this->precisions().stencilBits() > 0 )
		{
			TraceWarning{TracerTag} << "Stencil bits requested for shadow map '" << this->id() << "' !";
		}

		if ( !m_framebuffer->createOnHardware() )
		{
			TraceError{TracerTag} << "Unable to create the framebuffer for shadow map '" << this->id() << "' !";

			return false;
		}

		return true;
	}

	bool
	Abstract::onCreate (Renderer & renderer) noexcept
	{
		if ( !this->createImages(renderer.device()) )
		{
			TraceError{TracerTag} << "Unable to create image buffers for shadow map '" << this->id() << "' !";

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
		/* Depth buffer. */
		m_depthImageView.reset();
		m_depthImage.reset();

		/* Framebuffer. */
		m_framebuffer.reset();
	}

	bool
	Abstract::isValid () const noexcept
	{
		if ( m_framebuffer == nullptr || !m_framebuffer->isCreated() )
		{
			TraceError{TracerTag} << "The render target '" << this->id() << "' (Shadow) framebuffer is missing or not created !";

			return false;
		}

		if ( m_depthImage == nullptr || !m_depthImage->isCreated() )
		{
			TraceError{TracerTag} << "The render target '" << this->id() << "' (Shadow) depth image is missing or not created !";

			return false;
		}

		if ( m_depthImageView == nullptr || !m_depthImageView->isCreated() )
		{
			TraceError{TracerTag} << "The render target '" << this->id() << "' (Shadow) depth image view is missing or not created !";

			return false;
		}

		return true;
	}

	uint32_t
	Abstract::getBaseResolution () noexcept
	{
		return Settings::instance()->get< uint32_t >(GraphicsShadowMappingBaseResolutionKey, DefaultGraphicsShadowMappingBaseResolution);
	}
}
