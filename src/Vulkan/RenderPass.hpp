/*
 * src/Vulkan/RenderPass.hpp
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
#include <memory>
#include <vector>

/* Local inclusions for inheritances. */
#include "AbstractDeviceDependentObject.hpp"

/* Local inclusions for usages. */
#include "RenderSubPass.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The render-pass class
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This object needs a device.
	 */
	class RenderPass final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanRenderPass"};

			/**
			 * @brief Constructs a render pass.
			 * @param device A reference to a smart pointer to device where the render pass will be performed.
			 * @param createFlags The create info flags. Default none.
			 */
			explicit RenderPass (const std::shared_ptr< Device > & device, VkRenderPassCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a render pass with create info.
			 * @param device A reference to a smart pointer to device where the render pass will be performed.
			 * @param createInfo A reference to a create info.
			 */
			RenderPass (const std::shared_ptr< Device > & device, const VkRenderPassCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			RenderPass (const RenderPass & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			RenderPass (RenderPass && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			RenderPass & operator= (const RenderPass & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			RenderPass & operator= (RenderPass && copy) noexcept = default;

			/**
			 * @brief Destructs the render pass.
			 */
			~RenderPass () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Adds an attachment description.
			 * @param attachmentDescription A reference to an attachment description.
			 * @return void
			 */
			void
			addAttachmentDescription (const VkAttachmentDescription & attachmentDescription) noexcept
			{
				m_attachmentDescriptions.emplace_back(attachmentDescription);
			}

			/**
			 * @brief Adds a render sub-pass description.
			 * @param subPass A reference to a render sub-pass structure.
			 * @return void
			 */
			void
			addSubPass (const RenderSubPass & subPass) noexcept
			{
				m_renderSubPasses.emplace_back(subPass);
			}

			/**
			 * @brief Adds a sub-pass dependency.
			 * @param dependency A reference to a sub-pass dependency.
			 * @return void
			 */
			void
			addSubPassDependency (const VkSubpassDependency & dependency) noexcept
			{
				m_subPassDependencies.emplace_back(dependency);
			}

			/**
			 * @brief Returns the render-pass vulkan handle.
			 * @return VkRenderPass
			 */
			[[nodiscard]]
			VkRenderPass
			handle () const noexcept
			{
				return m_handle;
			}

			/**
			 * @brief Returns the render-pass create info.
			 * @return VkRenderPassCreateInfo
			 */
			[[nodiscard]]
			const VkRenderPassCreateInfo &
			createInfo () const noexcept
			{
				return m_createInfo;
			}

		private:

			/**
			 * @brief Pack sub-pass descriptions.
			 * @return std::vector< VkSubpassDescription >
			 */
			[[nodiscard]]
			std::vector< VkSubpassDescription > getSubPassDescriptions () const noexcept;

			VkRenderPass m_handle{VK_NULL_HANDLE};
			VkRenderPassCreateInfo m_createInfo{};
			std::vector< VkAttachmentDescription > m_attachmentDescriptions;
			std::vector< RenderSubPass > m_renderSubPasses;
			std::vector< VkSubpassDependency > m_subPassDependencies;
	};
}
