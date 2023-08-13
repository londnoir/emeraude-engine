/*
 * Emeraude/Vulkan/UniformBufferObject.cpp
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

#include "UniformBufferObject.hpp"

/* Local inclusions. */
#include "Device.hpp"

namespace Emeraude::Vulkan
{
	UniformBufferObject::UniformBufferObject (const std::shared_ptr< Device > & device, VkDeviceSize size) noexcept
		: AbstractHostBuffer(device, 0, size, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
	{

	}
}
