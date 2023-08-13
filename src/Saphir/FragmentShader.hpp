/*
 * Emeraude/Saphir/FragmentShader.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractShader.hpp"

namespace Emeraude::Saphir
{
	/**
	 * @brief The FragmentShader class.
	 * @extends Emeraude::Saphir::AbstractShader The base class of every shader type.
	 */
	class FragmentShader final : public AbstractShader
	{
		public:

			/**
			 * @brief Constructs a fragment shader.
			 * @param name The name of the shader for identification.
			 */
			explicit FragmentShader (const std::string & name) noexcept;

			/** @copydoc Emeraude::Saphir::AbstractShader::type() */
			[[nodiscard]]
			ShaderType type () const noexcept override;

			/**
			 * @brief Returns names of program outputs (fragments).
			 * @return const set< string >
			 */
			[[nodiscard]]
			const std::set< std::string > & outputs () const noexcept;

			/**
			 * @brief Declares a fragment output.
			 * @param name The identifier in GLSL code of the fragment output.
			 * @return bool
			 */
			bool declareOutput (const std::string & name) noexcept;

		private:

			std::set< std::string > m_outputs;
	};
}
