/*
 * Emeraude/Vulkan/StagingBuffer.hpp
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
#include "LockableTrait.hpp"
#include "AbstractHostBuffer.hpp"

namespace Emeraude::Vulkan
{
	/**
	 * @brief This buffer is intended to push data all-purposes buffer from CPU to GPU specific buffer.
	 * @extends Emeraude::Vulkan::AbstractHostBuffer This is a host-side buffer.
	 */
	class StagingBuffer final : public Libraries::LockableTrait, public AbstractHostBuffer
	{
		public:

			/**
			 * @brief Construct a staging buffer.
			 * @param device A reference to a device smart pointer.
			 * @param size The size in bytes. Default empty.
			 */
			explicit StagingBuffer (const std::shared_ptr< Device > & device, size_t size = 0) noexcept;
	};
}
