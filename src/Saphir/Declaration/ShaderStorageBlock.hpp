/*
 * Emeraude/Saphir/Declaration/ShaderStorageBlock.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractBufferBackedBlock.hpp"

namespace Emeraude::Saphir::Declaration
{
	/**
	 * @brief Shader Storage Block. This is the GLSL counter-part of Shader Storage Buffer Object.
	 * @extends Emeraude::Saphir::AbstractBufferBackedBlock
	 */
	class ShaderStorageBlock final : public AbstractBufferBackedBlock
	{
		public:

			/**
			 * @brief Constructs a shader storage block.
			 * @param set An integer to define in which set the buffer is.
			 * @param binding An integer to define at which point the buffer is bound.
			 * @param memoryLayout The type of video memory layout.
			 * @param name A C-string to set the name of the block.
			 * @param instanceName A C-string to set the name of the instance of the block. Default nullptr.
			 * @param arraySize Set the block as an array. Default 0.
			 */
			ShaderStorageBlock (uint32_t set, uint32_t binding, MemoryLayout memoryLayout, Key name, Key instanceName = nullptr, size_t arraySize = 0) noexcept;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::sourceCode() */
			[[nodiscard]]
			std::string sourceCode () const noexcept override;
	};
}
