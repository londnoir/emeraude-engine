/*
 * Emeraude/Saphir/ShaderGenerationInterface.hpp
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

/* Forward declarations */
namespace Emeraude
{
	namespace Graphics::Geometry
	{
		class Interface;
	}

	namespace Saphir
	{
		class ShaderGenerator;
	}
}

namespace Emeraude::Saphir
{
	/**
	 * @brief The shader generation interface class.
	 */
	class ShaderGenerationInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ShaderGenerationInterface (const ShaderGenerationInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ShaderGenerationInterface (ShaderGenerationInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return ShaderGenerationInterface &
			 */
			ShaderGenerationInterface & operator= (const ShaderGenerationInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return ShaderGenerationInterface &
			 */
			ShaderGenerationInterface & operator= (ShaderGenerationInterface && copy) noexcept = default;

			/**
			 * @brief Destructs the shader generation interface.
			 */
			virtual ~ShaderGenerationInterface () = default;

			/**
			 * @brief Writes the shader code chunk.
			 * @param generator A reference to the generator responsible for the current shader.
			 * @param geometry A reference to a geometry interface to check available vertex attributes.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool generateShaderCode (Saphir::ShaderGenerator & generator, const Graphics::Geometry::Interface & geometry) const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a shader generation interface.
			 */
			ShaderGenerationInterface () noexcept = default;
	};
}
