/*
 * src/Vulkan/ImageView.hpp
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

#pragma once

/* STL inclusions. */
#include <memory>

/* Local inclusions for inheritances. */
#include "AbstractDeviceDependentObject.hpp"

/* Forward declarations. */
namespace Emeraude::Vulkan
{
	class Image;
}

namespace Emeraude::Vulkan
{
	/**
	 * @brief The image view class
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This object needs a device.
	 */
	class ImageView final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanImageView"};

			/**
			 * @brief Constructs an image view.
			 * @param image A reference to an image smart pointer.
			 * @param viewType
			 * @param subresourceRange
			 * @param components Default unchanged.
			 * @param createFlags The create info flags. Default none.
			 */
			ImageView (const std::shared_ptr< Image > & image, VkImageViewType viewType, VkImageSubresourceRange subresourceRange, VkComponentMapping components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY}, VkImageViewCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs an image view with a create info.
			 * @param image A reference to an image smart pointer.
			 * @param createInfo A reference to a create info.
			 */
			ImageView (const std::shared_ptr< Image > & image, const VkImageViewCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ImageView (const ImageView & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ImageView (ImageView && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			ImageView & operator= (const ImageView & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			ImageView & operator= (ImageView && copy) noexcept = default;

			/**
			 * @brief Destructs the image view.
			 */
			~ImageView () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Returns the image view vulkan handle.
			 * @return VkImageView
			 */
			[[nodiscard]]
			VkImageView
			handle () const noexcept
			{
				return m_handle;
			}

			/**
			 * @brief Returns the image view create info.
			 * @return const VkImageViewCreateInfo &
			 */
			[[nodiscard]]
			const VkImageViewCreateInfo &
			createInfo () const noexcept
			{
				return m_createInfo;
			}

			/**
			 * @brief Returns the associated image smart pointer.
			 * @return std::shared_ptr< Image >
			 */
			[[nodiscard]]
			std::shared_ptr< Image >
			image () const noexcept
			{
				return m_image;
			}

		private:

			VkImageView m_handle{VK_NULL_HANDLE};
			VkImageViewCreateInfo m_createInfo{};
			std::shared_ptr< Image > m_image;
	};
}
