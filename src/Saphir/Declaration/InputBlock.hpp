/*
 * src/Saphir/Declaration/InputBlock.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractShaderBlock.hpp"

namespace Emeraude::Saphir::Declaration
{
	/**
	 * @brief The InputBlock class
	 * @extends Emeraude::Saphir::AbstractShaderBlock
	 */
	class InputBlock final : public AbstractShaderBlock
	{
		public:

			/**
			 * @brief Constructs an input block declaration.
			 * @param name A C-string to set the name of the block.
			 * @param location An integer for the location of this block within the shader.
			 * @param instanceName A C-string to set the name of the instance of the block. Default nullptr.
			 * @param arraySize Set the block as an array. Default 0.
			 */
			InputBlock (Key name, uint32_t location, Key instanceName = nullptr, size_t arraySize = 0) noexcept;

			/**
			 * @brief Constructs an input block declaration from an output block declaration.
			 * @param outputBlock A reference to an output block.
			 */
			explicit InputBlock (const AbstractShaderBlock & outputBlock) noexcept;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::sourceCode() */
			[[nodiscard]]
			std::string sourceCode () const noexcept override;
	};
}
