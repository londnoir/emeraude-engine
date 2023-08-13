/*
 * Emeraude/Saphir/Declaration/StageInput.hpp
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
#include <cstdint>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

namespace Emeraude::Saphir::Declaration
{
	/**
	 * @brief The StageInput class
	 * @extends Emeraude::Saphir::DeclarationInterface This is a shader code declaration.
	 */
	class StageInput final : public Interface
	{
		public:

			/**
			 * @brief Constructs a stage input variable.
			 * @param name A C-string to set the name of the sampler.
			 * @param interpolation The interpolation type between stages. Default nullptr. Use one of Keys::GLSL::* keyword.
			 * @param arraySize Set the variable as an array. If size is set to -1, the array will be defined as "[]" in the code.  Default 0.
			 */
			explicit StageInput (Key name, Key interpolation = nullptr, int32_t arraySize = 0) noexcept;

			/**
			 * @brief Constructs a stage input variable.
			 * @param location An integer to specify the location to use in the shader.
			 * @param type A C-string to set the GLSL type of the sampler. Use one of Keys::GLSL::Sampler* keyword.
			 * @param name A C-string to set the name of the sampler.
			 * @param interpolation The interpolation type between stages. Default nullptr. Use one of Keys::GLSL::* keyword.
			 * @param arraySize Set the variable as an array. If size is set to -1, the array will be defined as "[]" in the code.  Default 0.
			 */
			StageInput (uint32_t location, Key type, Key name, Key interpolation = nullptr, int32_t arraySize = 0) noexcept;

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
			 * @brief Returns the variable location in the shader.
			 * @param uint32_t
			 */
			[[nodiscard]]
			uint32_t location () const noexcept;

			/**
			 * @brief Returns the variable type.
			 * @param Key
			 */
			[[nodiscard]]
			Key type () const noexcept;

			/**
			 * @brief Returns the variable interpolation.
			 * @param Key
			 */
			[[nodiscard]]
			Key interpolation () const noexcept;

			/**
			 * @brief Returns the array size.
			 * @param size_t
			 */
			[[nodiscard]]
			int32_t arraySize () const noexcept;

			/**
			 * @brief Returns whether the expression is an array.
			 * @param bool
			 */
			[[nodiscard]]
			bool isArray () const noexcept;

			/**
			 * @brief Returns whether the expression is an array non size fixed.
			 * @param bool
			 */
			[[nodiscard]]
			bool isNonFixedArraySize () const noexcept;

		private:

			uint32_t m_location;
			Key m_type;
			Key m_name;
			Key m_interpolation;
			int32_t m_arraySize;
	};
}
