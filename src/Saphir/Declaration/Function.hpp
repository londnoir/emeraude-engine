/*
 * Emeraude/Saphir/Declaration/Function.hpp
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
#include "../CodeGeneratorInterface.hpp"

/* Local inclusions for usage. */
#include "Blob.hpp"

namespace Emeraude::Saphir::Declaration
{
	/**
	 * @brief The Function class.
	 * @extends Emeraude::Saphir::DeclarationInterface This is a shader code declaration.
	 */
	class Function final : public Interface, public CodeGeneratorInterface
	{
		public:

			/**
			 * @brief Construct a GLSL function.
			 * @param name A C-string to set the name of the function.
			 * @param returnType A C-string to set the type of the uniform. Use one of Keys::GLSL::* keyword.
			 */
			explicit Function (Key name, Key returnType = Keys::GLSL::Void) noexcept;

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
			 * @brief returnType
			 * @return Key
			 */
			[[nodiscard]]
			Key returnType () const noexcept;

			/**
			 * @brief parameters
			 * @return const std::vector< std::string > &
			 */
			[[nodiscard]]
			const std::vector< std::string > & parameters () const noexcept;

			/**
			 * @brief Adds an input parameter to the function signature.
			 * @param type The type of the parameter.
			 * @param name The name of the parameter.
			 * @param isConstant Adds "const" before "in" qualifier. Default false.
			 */
			void addInParameter (Key type, Key name, bool isConstant = false) noexcept;

			/**
			 * @brief Adds an output parameter to the function signature.
			 * @param type The type of the parameter.
			 * @param name The name of the parameter.
			 */
			void addOutParameter (Key type, Key name) noexcept;

			/**
			 * @brief Adds an reference parameter to the function signature.
			 * @param type The type of the parameter.
			 * @param name The name of the parameter.
			 */
			void addInOutParameter (Key type, Key name) noexcept;

			/**
			 * @brief Generates the call code.
			 * @param parameters
			 * @return std::string
			 */
			[[nodiscard]]
			std::string callCode (const std::string & parameters) const noexcept;

			/**
			 * @brief Generates the call code.
			 * @param parameters
			 * @return std::string
			 */
			[[nodiscard]]
			std::string callCode (const std::vector< std::string > & parameters) const noexcept;

			/**
			 * @brief Generates the call code.
			 * @param parameters
			 * @return std::string
			 */
			[[nodiscard]]
			std::string callCode (const Libraries::Blob & parameters) const noexcept;

		private:

			Key m_name;
			Key m_returnType;
			std::vector< std::string > m_parameters{};
	};
}
