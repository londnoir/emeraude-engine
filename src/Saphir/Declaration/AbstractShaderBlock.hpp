/*
 * src/Saphir/Declaration/AbstractShaderBlock.hpp
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
#include <map>
#include <cstdint>

/* Local inclusions for inheritances. */
#include "BlockInterface.hpp"
#include "Member/ShaderBlock.hpp"

namespace Emeraude::Saphir::Declaration
{
	/**
	 * @brief Base class for every GLSL shader blocks.
	 * @extends Emeraude::Saphir::BlockInterface
	 */
	class AbstractShaderBlock : public BlockInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractShaderBlock (const AbstractShaderBlock & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			AbstractShaderBlock (AbstractShaderBlock && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractShaderBlock &
			 */
			AbstractShaderBlock & operator= (const AbstractShaderBlock & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return AbstractShaderBlock &
			 */
			AbstractShaderBlock & operator= (AbstractShaderBlock && copy) noexcept = default;

			/**
			 * @brief Destructs the shader block.
			 */
			~AbstractShaderBlock () override = default;

			/** @copydoc Emeraude::Saphir::Declaration::Interface::isValid() */
			[[nodiscard]]
			bool isValid () const noexcept override;

			/** @copydoc Emeraude::Saphir::Declaration::Interface::bytes() */
			[[nodiscard]]
			size_t bytes () const noexcept final;

			/**
			 * @brienf returns the location for this block.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t location () const noexcept;

			/**
			 * @brief Adds a member to the block.
			 * @param type A C-string to set the type of the member. Use one of Keys::GLSL::* keyword.
			 * @param name A C-string to set the name of the member.
			 * @param interpolation The interpolation used by the member between stages. Use one of Keys::GLSL::* keyword. Default nullptr.
			 */
			bool addMember (VariableType type, Key name, Key interpolation = nullptr) noexcept;

			/**
			 * @brief Adds a member to the block.
			 * @param structure A reference to a structure.
			 * @param interpolation The interpolation used by the member between stages. Use one of Keys::GLSL::* keyword. Default nullptr.
			 */
			bool addMember (const Structure & structure, Key interpolation = nullptr) noexcept;

			/**
			 * @brief Adds an array member to the block.
			 * @param type A C-string to set the type of the member. Use one of Keys::GLSL::* keyword.
			 * @param name A C-string to set the name of the member.
			 * @param arraySize The size of the array.
			 * @param interpolation The interpolation used by the member between stages. Use one of Keys::GLSL::* keyword. Default nullptr.
			 */
			bool addArrayMember (VariableType type, Key name, size_t arraySize, Key interpolation = nullptr) noexcept;

			/**
			 * @brief Adds an array member to the block.
			 * @param structure A reference to a structure.
			 * @param arraySize The size of the array.
			 * @param interpolation The interpolation used by the member between stages. Use one of Keys::GLSL::* keyword. Default nullptr.
			 */
			bool addArrayMember (const Structure & structure, size_t arraySize, Key interpolation = nullptr) noexcept;

			/**
			 * @brief Returns the list of members.
			 * @return const std::vector< std::pair< Key, Member::ShaderBlock > > &
			 */
			[[nodiscard]]
			const std::vector< std::pair< Key, Member::ShaderBlock > > & members () const noexcept;

		protected:

			/**
			 * @brief Constructs a shader block.
			 * @param name A C-string to set the name of the block.
			 * @param location A integer to set a location between shaders.
			 * @param instanceName A C-string to set the name of the instance of the block. Default nullptr.
			 * @param arraySize Set the block as an array. Default 0.
			 */
			AbstractShaderBlock (Key name, uint32_t location, Key instanceName = nullptr, size_t arraySize = 0) noexcept;

		private:

			uint32_t m_location;
			std::vector< std::pair< Key, Member::ShaderBlock > > m_members{};
	};
}
