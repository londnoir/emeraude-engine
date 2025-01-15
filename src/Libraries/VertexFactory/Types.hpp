/*
 * src/Libraries/VertexFactory/Types.hpp
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
#include <cstdint>

namespace Libraries::VertexFactory
{
	/** @brief The normal format. */
	enum class NormalType : uint8_t
	{
		None,
		Normal,
		TangentNormal,
		TBNSpace
	};

	/** @brief The texture coordinates format. */
	enum class TextureCoordinatesType : uint8_t
	{
		None,
		UV,
		UVW
	};

	/** @brief The vertex color format. */
	enum class VertexColorType : uint8_t
	{
		None,
		Gray,
		RGB,
		RGBA
	};

	/** @brief The skeletal animation format. */
	enum class SkeletalAnimationType : uint8_t
	{
		None,
		Average3,
		Average4,
		Weighted3,
		Weighted4
	};
}
