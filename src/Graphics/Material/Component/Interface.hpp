/*
 * Emeraude/Graphics/Material/Component/Interface.hpp
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
#include <type_traits>

/* Local inclusions for inheritances. */
#include "Saphir/ShaderGenerationInterface.hpp"

/* Local inclusions for usages. */
#include "Graphics/Geometry/Interface.hpp"
#include "TypeInterface.hpp"

namespace Emeraude::Graphics::Material::Component
{
	/**
	 * @brief The component interface.
	 * @extends Emeraude::Saphir::ShaderGenerationInterface Needs to interact with shader generations.
	 */
	class Interface : public Saphir::ShaderGenerationInterface
	{
		public:

			/**
			 * @brief Returns the component type structre.
			 * @return TypeInterface
			 */
			[[nodiscard]]
			virtual TypeInterface & component () noexcept = 0;

			/**
			 * @brief Returns the component type structre.
			 * @return TypeInterface
			 */
			[[nodiscard]]
			virtual const TypeInterface & component () const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a component interface.
			 */
			Interface () noexcept = default;
	};
}
