/*
 * Emeraude/Vulkan/Sampler.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractDeviceDependentObject.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief The sampler class.
	 * @extends Emeraude::Vulkan::AbstractDeviceDependentObject This object needs a device.
	 */
	class Sampler  final : public AbstractDeviceDependentObject
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"VulkanSampler"};

			/**
			 * @brief Constructs a sampler.
			 * @param device A reference to a smart pointer of the device.
			 * @param createFlags The create info flags. Default none.
			 */
			explicit Sampler (const std::shared_ptr< Device > & device, VkSamplerCreateFlags createFlags = 0) noexcept;

			/**
			 * @brief Constructs a sampler with create info.
			 * @param device A reference to a smart pointer of the device.
			 * @param createInfo A reference to a create info.
			 */
			Sampler (const std::shared_ptr< Device > & device, const VkSamplerCreateInfo & createInfo) noexcept;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Sampler (const Sampler & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Sampler (Sampler && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			Sampler & operator= (const Sampler & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			Sampler & operator= (Sampler && copy) noexcept = default;

			/**
			 * @brief Destructs the sampler.
			 */
			~Sampler () override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::createOnHardware() */
			bool createOnHardware () noexcept override;

			/** @copydoc Emeraude::Vulkan::AbstractDeviceDependentObject::destroyFromHardware() */
			bool destroyFromHardware () noexcept override;

			/**
			 * @brief Returns the sampler vulkan handle.
			 * @param VkSampler
			 */
			[[nodiscard]]
			VkSampler handle () const noexcept;

			/**
			 * @brief Returns the sampler create info.
			 * @param VkSamplerCreateInfo
			 */
			[[nodiscard]]
			VkSamplerCreateInfo createInfo () const noexcept;

		private:

			VkSampler m_handle{VK_NULL_HANDLE};
			VkSamplerCreateInfo m_createInfo{};
	};
}
