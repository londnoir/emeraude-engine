/*
 * src/Graphics/Renderable/MeshLayer.cpp
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

#include "MeshLayer.hpp"

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;

	MeshLayer::MeshLayer (const std::string & name, const std::shared_ptr< Material::Interface > & material, const RasterizationOptions & options, int flags) noexcept
		: NameableTrait(name), m_material(material), m_rasterizationOptions(options), m_renderableFlags(flags)
	{

	}

	std::shared_ptr< Material::Interface >
	MeshLayer::material () const noexcept
	{
		return m_material;
	}

	const RasterizationOptions &
	MeshLayer::rasterizationOptions () const noexcept
	{
		return m_rasterizationOptions;
	}

	int
	MeshLayer::flags () const noexcept
	{
		return m_renderableFlags;
	}
}
