/*
 * Emeraude/Graphics/Renderable/MeshLayer.hpp
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
#include <string>
#include <memory>

/* Local inclusions for inheritances. */
#include "NamedItem.hpp"

/* Local inclusions for usages. */
#include "Graphics/Material/Interface.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief The MeshLayer class
	 */
	class MeshLayer final : public Libraries::NamedItem
	{
		public:

			/**
			 * @brief Constructs a mesh layer.
			 * @param name The name of the layer.
			 * @param material A reference to a material for this layer.
			 * @param flags The renderable level flags. Default 0.
			 */
			MeshLayer (const std::string & name, const std::shared_ptr< Material::Interface > & material, int flags = 0) noexcept;

			/**
			 * @brief Returns the material resource of the layer.
			 * @return shared_ptr< Material::Interface >
			 */
			[[nodiscard]]
			std::shared_ptr< Material::Interface > material () const noexcept;

			/**
			 * @brief Returns renderable level flags.
			 * @return int
			 */
			[[nodiscard]]
			int flags () const noexcept;

		private:

			std::shared_ptr< Material::Interface > m_material{};
			int m_renderableFlags = 0;
	};
}
