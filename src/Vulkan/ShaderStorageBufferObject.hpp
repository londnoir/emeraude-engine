/*
 * src/Vulkan/ShaderStorageBufferObject.hpp
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

/* Local inclusions. */
#include "AbstractDeviceBuffer.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief Defines a convenient way to build an shader storage buffer object.
	 * @note OpenGL guaranteed a minimum size of 128MB.
	 * @extends Emeraude::Vulkan::AbstractDeviceBuffer This is a device-side buffer.
	 */
	class ShaderStorageBufferObject final : public AbstractDeviceBuffer
	{
		public:

			/**
			 * @brief Constructs a shader storage buffer object.
			 * @param device A reference to the device smart pointer.
			 * @param size The size of the buffer.
			 */
			ShaderStorageBufferObject (const std::shared_ptr< Device > & device, VkDeviceSize size) noexcept;
	};
}
