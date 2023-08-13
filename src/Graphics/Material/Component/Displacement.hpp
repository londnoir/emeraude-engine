/*
 * Emeraude/Graphics/Material/Component/Displacement.hpp
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
	 * @brief The displacement component.
	 * @tparam component_t The type of component. This can be all type.
	 * @extends Emeraude::Graphics::Material::Component::ComponentInterface This is a material component.
	 */
	template<
		typename component_t,
		std::enable_if_t< std::is_base_of_v< TypeInterface, component_t >, bool > = false
	>
	class Displacement final : public Interface
	{
		public:

			/**
			 * @brief Constructs the component.
			 * @param component A reference to a type component.
			 * @param scale A scale value. Default 1.0.
			 */
			explicit Displacement (const component_t & component, float scale = 1.0F) noexcept
				: m_component(component), m_scale(scale)
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
			TypeInterface &
			const component () const noexcept override
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

					case Emeraude::Saphir::ShaderType::GeometryShader :

						break;

					default:
						break;
				}

				return true;
			}

			/**
			 * @brief Sets the displacement scale.
			 * @param scale The scale value.
			 * @return void
			 */
			void
			setScale (float scale) noexcept
			{
				m_scale = scale;
			}

			/**
			 * @brief Returns the displacement scale.
			 * @return float
			 */
			[[nodiscard]]
			float
			scale () const noexcept
			{
				return m_scale;
			}

		private:

			component_t m_component;
			float m_scale;
	};
}
