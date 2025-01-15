/*
 * src/Saphir/Declaration/Sampler.hpp
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
#include <cstdint>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

namespace Emeraude::Saphir::Declaration
{
	/**
	 * @brief The Sampler class
	 * @extends Emeraude::Saphir::DeclarationInterface This is a shader code declaration.
	 */
	class Sampler final : public Interface
	{
		public:

			/**
			 * @brief Constructs a shader uniform variable.
			 * @param set An integer to define in which set the sampler is.
			 * @param binding An integer to define at which point the sampler is bound.
			 * @param type A C-string to set the GLSL type of the sampler. Use one of Keys::GLSL::Sampler* keyword.
			 * @param name A C-string to set the name of the sampler.
			 * @param arraySize Set the variable as an array. Default 0.
			 */
			Sampler (uint32_t set, uint32_t binding, Key type, Key name, size_t arraySize = 0) noexcept;

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
			 * @brief Gets the set index.
			 * @return uint32_t.
			 */
			[[nodiscard]]
			uint32_t set () const noexcept;

			/**
			 * @brief Gets the binding point.
			 * @return uint32_t.
			 */
			[[nodiscard]]
			uint32_t binding () const noexcept;

			/**
			 * @brief Returns the variable type.
			 * @param Key
			 */
			[[nodiscard]]
			Key type () const noexcept;

			/**
			 * @brief Returns the array size.
			 * @param size_t
			 */
			[[nodiscard]]
			size_t arraySize () const noexcept;

		private:

			uint32_t m_set;
			uint32_t m_binding;
			Key m_type;
			Key m_name;
			size_t m_arraySize;
	};
}
