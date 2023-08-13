/*
 * Emeraude/Graphics/Material/Component/Roughness.hpp
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
	 * @brief The roughness component.
	 * @tparam component_t The type of component. This should be value or texture.
	 * @extends Emeraude::Graphics::Material::Component::ComponentInterface This is a material component.
	 */
	template<
		typename component_t,
		std::enable_if_t< std::is_base_of_v< TypeInterface, component_t >, bool > = false
	>
	class Roughness final : public Interface
	{
		public:

			/**
			 * @brief Constructs the component.
			 * @param component A reference to a type component.
			 */
			explicit Roughness (const component_t & component) noexcept
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
				switch ( generator.shaderType() )
				{
					case Emeraude::Saphir::ShaderType::VertexShader :

						break;

					case Emeraude::Saphir::ShaderType::FragmentShader :

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
