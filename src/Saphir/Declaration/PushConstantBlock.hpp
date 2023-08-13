/*
 * Emeraude/Saphir/Declaration/PushConstantBlock.hpp
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
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "BlockInterface.hpp"
#include "Member/PushConstant.hpp"

namespace Emeraude::Saphir::Declaration
{
	/**
	 * @brief The PushConstant class
	 * @extends Emeraude::Saphir::BlockInterface
	 */
	class PushConstantBlock final : public BlockInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PushConstantBlock"};

			/**
			 * @brief Constructs a push constant (Vulkan) block.
			 * @param name A C-string to set the name of the block.
			 * @param instanceName A C-string to set the name of the instance of the block. Default nullptr.
			 */
			explicit PushConstantBlock (Key name, Key instanceName = nullptr) noexcept;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::isValid() */
			[[nodiscard]]
			bool isValid () const noexcept override;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::bytes() */
			[[nodiscard]]
			size_t bytes () const noexcept override;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::sourceCode() */
			[[nodiscard]]
			std::string sourceCode () const noexcept override;

			/**
			 * @brief Adds a member to the block.
			 * @param type A C-string to set the type of the member. Use one of Keys::GLSL::* keyword.
			 * @param name A C-string to set the name of the member.
			 */
			virtual bool addMember (VariableType type, Key name) noexcept final;

			/**
			 * @brief Adds an array member to the block.
			 * @param type A C-string to set the type of the member. Use one of Keys::GLSL::* keyword.
			 * @param name A C-string to set the name of the member.
			 * @param arraySize The size of the array.
			 */
			virtual bool addArrayMember (VariableType type, Key name, size_t arraySize) noexcept final;

			/**
			 * @brief Returns the list of members.
			 * @return const std::vector< std::pair< Key, Member::PushConstant > > &
			 */
			[[nodiscard]]
			virtual const std::vector< std::pair< Key, Member::PushConstant > > & members () const noexcept final;

		private:

			std::vector< std::pair< Key, Member::PushConstant > > m_members{};
	};
}
