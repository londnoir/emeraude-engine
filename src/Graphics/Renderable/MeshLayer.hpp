/*
 * src/Graphics/Renderable/MeshLayer.hpp
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
#include <string>
#include <memory>

/* Local inclusions for inheritances. */
#include "Libraries/NameableTrait.hpp"

/* Local inclusions for usages. */
#include "Graphics/Material/Interface.hpp"
#include "Graphics/RasterizationOptions.hpp"

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief The MeshLayer class
	 */
	class MeshLayer final : public Libraries::NameableTrait
	{
		public:

			/**
			 * @brief Constructs a mesh layer.
			 * @param name The name of the layer.
			 * @param material A reference to a material for this layer.
			 * @param options A reference to a rasterization options.
			 * @param flags The renderable level flags.
			 */
			MeshLayer (const std::string & name, const std::shared_ptr< Material::Interface > & material, const RasterizationOptions & options, int flags) noexcept;

			/**
			 * @brief Returns the material resource of the layer.
			 * @return shared_ptr< Material::Interface >
			 */
			[[nodiscard]]
			std::shared_ptr< Material::Interface > material () const noexcept;

			/**
			 * @brief Returns the rasterization options for this layer.
			 * @return const RasterizationOptions &
			 */
			[[nodiscard]]
			const RasterizationOptions & rasterizationOptions () const noexcept;

			/**
			 * @brief Returns renderable level flags.
			 * @return int
			 */
			[[nodiscard]]
			int flags () const noexcept;

		private:

			std::shared_ptr< Material::Interface > m_material;
			RasterizationOptions m_rasterizationOptions;
			int m_renderableFlags;
	};
}
