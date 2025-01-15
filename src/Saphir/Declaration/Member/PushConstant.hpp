/*
 * src/Saphir/Declaration/Member/PushConstant.hpp
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
#include <string>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

namespace Emeraude::Saphir::Declaration::Member
{
	/**
	 * @brief The push constant member structure.
	 * @extends Emeraude::Saphir::Declaration::Member::Interface This is a structure member.
	 */
	class PushConstant final : public Interface
	{
		public:

			/**
			 * @brief Constructs a push constant member.
			 * @param type A C-string to set the type of the member. Use one of Keys::GLSL::* keyword.
			 * @param name A C-string to set the name of the member.
			 * @param arraySize The size of the array. Default 0.
			 */
			PushConstant (VariableType type, Key name, size_t arraySize = 0) noexcept;

			/** @copydoc Emeraude::Saphir::Declaration::Member::Interface::type() */
			[[nodiscard]]
			VariableType type () const noexcept override;

			/** @copydoc Emeraude::Saphir::Declaration::Member::Interface::name() */
			[[nodiscard]]
			Key name () const noexcept override;

			/** @copydoc Emeraude::Saphir::Declaration::Member::Interface::bytes() */
			[[nodiscard]]
			size_t bytes () const noexcept override;

			/** @copydoc Emeraude::Saphir::Declaration::Member::Interface::sourceCode() */
			[[nodiscard]]
			std::string sourceCode () const noexcept override;

			/**
			 * @brief Returns the array size.
			 * @note 0 Means a single variable.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t arraySize () const noexcept;

		private:

			VariableType m_type;
			Key m_name;
			size_t m_arraySize;
	};
}
