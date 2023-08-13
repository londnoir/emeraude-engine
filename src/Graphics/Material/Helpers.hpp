/*
 * Emeraude/Graphics/Material/Helpers.hpp
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

/* Forward declarations. */
namespace Emeraude
{
	namespace Saphir
	{
		class ShaderGenerator;
	}

	namespace Graphics
	{
		namespace Material
		{
			class Interface;
		}

		namespace Geometry
		{
			class Interface;
		}
	}
}

namespace Emeraude::Graphics::Material
{
	/**
	 * @brief Checks primary texture coordinates linkage between the material and the geometry.
	 * @param gen A reference to the shader gen.
	 * @param material A reference to the material.
	 * @param geometry A reference to the geometry.
	 * @return bool
	 */
	bool checkPrimaryTextureCoordinates (Saphir::ShaderGenerator & gen, const Interface & material, const Geometry::Interface & geometry) noexcept;

	/**
	 * @brief Checks secondary texture coordinates linkage between the material and the geometry.
	 * @param gen A reference to the shader gen.
	 * @param material A reference to the material.
	 * @param geometry A reference to the geometry.
	 * @return bool
	 */
	bool checkSecondaryTextureCoordinates (Saphir::ShaderGenerator & gen, const Interface & material, const Geometry::Interface & geometry) noexcept;
}
