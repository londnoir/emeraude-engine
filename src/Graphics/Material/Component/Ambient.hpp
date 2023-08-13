/*
 * Emeraude/Graphics/Material/Component/Ambient.hpp
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
#include "Interface.hpp"

namespace Emeraude::Graphics::Material::Component
{
	/**
	 * @brief The ambient component.
	 * @tparam component_t The type of component. This should be color or texture.
	 * @extends Emeraude::Graphics::Material::Component::ComponentInterface This is a material component.
	 */
	template<
		typename component_t,
		std::enable_if_t< std::is_base_of_v< TypeInterface, component_t >, bool > = false
	>
	class Ambient final : public Interface
	{
		public:

			/**
			 * @brief Constructs the component.
			 * @param component A reference to a type component.
			 */
			explicit Ambient (const component_t & component) noexcept
				: m_component(component)
			{

			}

			/** @copydoc Emeraude::Graphics::Material::Component::ComponentInterface::component() */
			[[nodiscard]]
			TypeInterface &
			component () noexcept override
			{
				return m_component;
			}

			/** @copydoc Emeraude::Graphics::Material::Component::ComponentInterface::component() */
			[[nodiscard]]
			const TypeInterface &
			component () const noexcept override
			{
				return m_component;
			}

			/** @copydoc Emeraude::Graphics::Material::Component::ComponentInterface::generateShaderCode() */
			[[nodiscard]]
			bool
			generateShaderCode (Saphir::ShaderGenerator & generator, const Geometry::Interface & geometry) const noexcept override
			{
				using namespace Libraries;
				using namespace Saphir;
				using namespace Saphir::Keys;

				switch ( generator.shaderType() )
				{
					case ShaderType::VertexShader :
						/*if constexpr ( std::is_same_v< TypeTexture, component_t > )
						{

						}*/
						break;

					case ShaderType::FragmentShader :
						/*generator.declare(Uniform{GLSL::FloatVector4, Uniforms::AmbientLight, "vec4(1.0, 1.0, 1.0, 1.0)"});

						if constexpr ( std::is_same_v< TypeColor, component_t > )
						{
							generator.declare(Uniform{GLSL::FloatVector4, Uniforms::Ambient});

							generator.addInstruction(Blob() << GLSL::FloatVector4 << ' ' << Materials::Ambient << " = " << Uniforms::AmbientLight << " * " << Uniforms::Ambient << ';');
						}

						if constexpr ( std::is_same_v< TypeTexture, component_t > )
						{
							generator.declare(Uniform{m_component->textureType(), Uniforms::Ambient});

							generator.addInstruction(Blob() << GLSL::FloatVector4 << ' ' << Materials::Ambient << " = " << Uniforms::AmbientLight << " * texture(" << Uniforms::Ambient << ", " << this->getTextureCoordinatesVariableName(ComponentType::Ambient) << ");");
						}*/
						break;

					default:
						break;
				}

				return true;
			}

		private:

			component_t m_component;
	};
}
