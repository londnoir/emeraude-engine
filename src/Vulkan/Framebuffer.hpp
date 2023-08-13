/*
 * Emeraude/Vulkan/Framebuffer.hpp
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
#include "RenderPass.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The framebuffer class
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This object needs a device.
	 */
	class Framebuffer final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanFramebuffer"};

			/**
			 * @brief Constructs a framebuffer.
			 * @param renderPass A reference to a RenderPass smart pointer.
			 * @param extent A reference to an VkExtent2D.
			 * @param layerCount The number of framebuffer layers. Default 1.
			 * @param createFlags The create info flags. Default none.
			 */
			Framebuffer (const std::shared_ptr< const RenderPass > & renderPass, const VkExtent2D & extent, uint32_t layerCount = 1, VkFramebufferCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a framebuffer.
			 * @param renderPass A reference to a RenderPass smart pointer.
			 * @param extent A reference to an VkExtent3D.
			 * @param createFlags The create info flags. Default none.
			 */
			Framebuffer (const std::shared_ptr< const RenderPass > & renderPass, const VkExtent3D & extent, VkFramebufferCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a framebuffer with create info.
			 * @param renderPass A reference to a RenderPass smart pointer.
			 * @param createInfo A reference to a create info.
			 */
			Framebuffer (const std::shared_ptr< const RenderPass > & renderPass, const VkFramebufferCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Framebuffer (const Framebuffer & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Framebuffer (Framebuffer && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Framebuffer & operator= (const Framebuffer & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Framebuffer & operator= (Framebuffer && copy) noexcept = default;

			/**
			 * @brief Destructs the framebuffer.
			 */
			~Framebuffer () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Adds an image view to the framebuffer.
			 * @return void
			 */
			void addAttachment (VkImageView imageViewHandle) noexcept;

			/**
			 * @brief Returns the framebuffer vulkan handle.
			 * @return VkFramebuffer
			 */
			[[nodiscard]]
			VkFramebuffer handle () const noexcept;

			/**
			 * @brief Returns the framebuffer create info.
			 * @return VkFramebuffer
			 */
			[[nodiscard]]
			VkFramebufferCreateInfo createInfo () const noexcept;

			/**
			 * @brief Returns the render pass associated to this framebuffer.
			 * @return const shared_ptr< const RenderPass > &
			 */
			[[nodiscard]]
			std::shared_ptr< const RenderPass > renderPass () const noexcept;

		private:

			VkFramebuffer m_handle{VK_NULL_HANDLE};
			VkFramebufferCreateInfo m_createInfo{};
			std::shared_ptr< const RenderPass > m_renderPass;
			std::vector< VkImageView > m_attachments;
	};
}
