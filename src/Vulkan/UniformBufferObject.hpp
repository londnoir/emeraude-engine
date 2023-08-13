/*
 * Emeraude/Vulkan/UniformBufferObject.hpp
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

/* C/C++ standard libraries */
#include <memory>

/* Local inclusions for inheritances. */
#include "AbstractHostBuffer.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief Defines a convenient way to build a uniform buffer object (UBO).
	 * @note OpenGL guaranteed a minimum size of 16Kb.
	 * @extends Emeraude::Vulkan::AbstractHostBuffer This is a host-side buffer.
	 */
	class UniformBufferObject final : public AbstractHostBuffer
	{
		public:

			static constexpr auto Vector2Room = 4UL;
			static constexpr auto Vector2iSize = Vector2Room * sizeof(int);
			static constexpr auto Vector2fSize = Vector2Room * sizeof(float);
			static constexpr auto Vector2dSize = Vector2Room * sizeof(double);
			static constexpr auto Vector3Room = 4UL;
			static constexpr auto Vector3iSize = Vector3Room * sizeof(int);
			static constexpr auto Vector3fSize = Vector3Room * sizeof(float);
			static constexpr auto Vector3dSize = Vector3Room * sizeof(double);
			static constexpr auto Vector4Room = 4UL;
			static constexpr auto Vector4iSize = Vector4Room * sizeof(int);
			static constexpr auto Vector4fSize = Vector4Room * sizeof(float);
			static constexpr auto Vector4dSize = Vector4Room * sizeof(double);
			static constexpr auto Matrix2Room = 4UL;
			static constexpr auto Matrix2fSize = Matrix2Room * sizeof(float);
			static constexpr auto Matrix2dSize = Matrix2Room * sizeof(double);
			static constexpr auto Matrix3Room = 12UL;
			static constexpr auto Matrix3fSize = Matrix3Room * sizeof(float);
			static constexpr auto Matrix3dSize = Matrix3Room * sizeof(double);
			static constexpr auto Matrix4Room = 16UL;
			static constexpr auto Matrix4fSize = Matrix4Room * sizeof(float);
			static constexpr auto Matrix4dSize = Matrix4Room * sizeof(double);

			/**
			 * @brief Constructs an uniform buffer object (UBO).
			 * @param device A reference to a smart pointer to the device where the buffer will be created.
			 * @param size The size of the buffer.
			 */
			UniformBufferObject (const std::shared_ptr< Device > & device, VkDeviceSize size) noexcept;
	};
}
