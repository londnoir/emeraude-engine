/*
 * Emeraude/Saphir/VertexShader.hpp
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
#include <set>

/* Local inclusions for inheritances. */
#include "AbstractShader.hpp"

/* Local inclusions for usages. */
#include "Graphics/Types.hpp"

namespace Emeraude::Saphir
{
	/**
	 * @brief The VertexShader class.
	 * @extends Emeraude::Saphir::AbstractShader The base class of every shader type.
	 */
	class VertexShader final : public AbstractShader
	{
		public:

			/**
			 * @brief Constructs a vertex shader.
			 * @param name The name of the shader for identification.
			 */
			explicit VertexShader (const std::string & name) noexcept;

			/** @copydoc Emeraude::Saphir::AbstractShader::type() */
			[[nodiscard]]
			ShaderType type () const noexcept override;

			/**
			 * @brief Returns a list of requested vertex attributes in the shader.
			 * @return const std::set< Graphics::VertexAttributeType > &
			 */
			[[nodiscard]]
			const std::set< Graphics::VertexAttributeType > & vertexAttributes () const noexcept;

			/**
			 * @brief Declares a vertex attribute as a program input.
			 * @param vertexAttribute The vertex attribute type.
			 * @return bool
			 */
			bool declareAttribute (const Graphics::VertexAttributeType & vertexAttribute) noexcept;

			/**
			 * @brief Sets the vertex shader uses instancing.
			 * @return void
			 */
			void enableInstancing () noexcept;

			/**
			 * @brief Returns whether the vertex shader is using instancing.
			 * @return bool
			 */
			[[nodiscard]]
			bool instancingEnabled () const noexcept;

		private:

			std::set< Graphics::VertexAttributeType > m_vertexAttributes{};
			bool m_instancingEnabled{false};
	};
}
