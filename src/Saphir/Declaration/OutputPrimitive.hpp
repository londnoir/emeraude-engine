/*
 * Emeraude/Saphir/Declaration/OutputPrimitive.hpp
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
	 * @brief The OutputPrimitive class
	 * @extends Emeraude::Saphir::DeclarationInterface This is a shader code declaration.
	 */
	class OutputPrimitive : public Interface
	{
		public:

			/**
			 * @brief Constructs an output primitive.
			 * @param primitiveType A C-string to set the GLSL type of the primitive. Use one of Keys::GLSL::Geometry::Out::Primitive::* keyword.
			 * @param maxVertices The max vertices input.
			 */
			OutputPrimitive (Key primitiveType, uint32_t maxVertices) noexcept;

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
			 * @brief Returns the max vertices.
			 * @return unsigned int
			 */
			[[nodiscard]]
			uint32_t maxVertices () const noexcept;

		private:

			Key m_name; /* Primitive type */
			uint32_t m_maxVertices;
	};
}
