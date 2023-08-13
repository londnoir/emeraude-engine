/*
 * Emeraude/Saphir/Declaration/Structure.hpp
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
#include <vector>

/* Local inclusions for inheritances. */
#include "Interface.hpp"
#include "Member/Structure.hpp"

namespace Emeraude::Saphir::Declaration
{
	/**
	 * @brief The Structure class
	 * @extends Emeraude::Saphir::DeclarationInterface This is a shader code declaration.
	 */
	class Structure final : public Interface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Structure"};

			/**
			 * @brief Constructs a GLSL struct.
			 * @param name A C-string to set the name of the structure.
			 * @param instanceName A C-string to set the instance name of the structure to call it into the code. Default nullptr.
			 */
			explicit Structure (Key name, Key instanceName = nullptr) noexcept;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::isValid() */
			[[nodiscard]]
			bool isValid () const noexcept override;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::name() */
			[[nodiscard]]
			Key name () const noexcept override;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::bytes() */
			[[nodiscard]]
			size_t bytes () const noexcept override;

			/** @copydoc Emeraude::Saphir::DeclarationInterface::sourceCode() */
			[[nodiscard]]
			std::string sourceCode () const noexcept override;

			/**
			 * @brief Returns the instance name of the struct in GLSL code.
			 * @return string.
			 */
			[[nodiscard]]
			const std::string & instanceName () const noexcept;

			/**
			 * @brief Adds a member to the structure.
			 * @param type A C-string to set the GLSL type of the member. Use one of Keys::GLSL::* keyword.
			 * @param name A C-string to set the name of the member.
			 * @return bool.
			 */
			bool addMember (VariableType type, Key name) noexcept;

			/**
			 * @brief Returns the list of members.
			 * @return const std::vector< std::pair< Key, Member::Structure > > &
			 */
			[[nodiscard]]
			const std::vector< std::pair< Key, Member::Structure > > & members () const noexcept;

		private:

			Key m_name;
			std::string m_instanceName{};
			std::vector< std::pair< Key, Member::Structure > > m_members{};
	};
}
