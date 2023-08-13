/*
 * Emeraude/Saphir/Declaration/Member/Interface.hpp
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
#include <string>

/* Local inclusions for usages. */
#include "Saphir/Keys.hpp"
#include "Saphir/Declaration/Types.hpp"

namespace Emeraude::Saphir::Declaration::Member
{
	/**
	 * @brief The structure member interface.
	 */
	class Interface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			Interface (const Interface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			Interface (Interface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return Interface &
			 */
			Interface & operator= (const Interface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return Interface &
			 */
			Interface & operator= (Interface && copy) noexcept = default;
			
			/**
			 * @brief Destructs the member interface.
			 */
			virtual ~Interface () = default;

			/**
			 * @brief Returns the member GLSL type.
			 * @return VariableType
			 */
			[[nodiscard]]
			virtual VariableType type () const noexcept = 0;

			/**
			 * @brief Returns the member name.
			 * @return Key
			 */
			[[nodiscard]]
			virtual Key name () const noexcept = 0;

			/**
			 * @brief Returns the size in bytes of the member taking in account the alignement.
			 * @return size_t
			 */
			[[nodiscard]]
			virtual size_t bytes () const noexcept = 0;

			/**
			 * @brief Returns the GLSL source code for the member.
			 * @return std::string
			 */
			[[nodiscard]]
			virtual std::string sourceCode () const noexcept = 0;
			
		protected:

			/**
			 * @brief Constructs a member interface.
			 */
			Interface () noexcept = default;
	};
}
