/*
 * Emeraude/Graphics/Geometry/SubGeometry.hpp
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

/* C/C++ standards libraries. */
#include <cstddef>
#include <array>

/* Local inclusions for inheritances */
#include "FlagTrait.hpp"

namespace Emeraude::Graphics::Geometry
{
	/** @brief SubGeometry flag bits. */
	enum SubGeometryFlagBits
	{
		EnableDoubleSidedFaces = 1
	};

	/**
	 * @brief Defines how to use an IBO or a VBO to draw a specific geometry or sub-geomtry.
	 * @extends Libraries::FlagTrait
	 */
	class SubGeometry final : public Libraries::FlagTrait< uint32_t >
	{
		public:

			/**
			 * @brief Constructs a sub geometry.
			 * @param offset Sets where to execute in the VBO or IBO.
			 * @param length Sets the length in VBO or IBO.
			 * @param enableDoubleSidedFaces Enable double sided faces. Default false.
			 */
			explicit SubGeometry (size_t offset, size_t length, bool enableDoubleSidedFaces = false) noexcept;

			/**
			 * @brief Returns where to execute in the VBO or IBO to draw the geometry.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t offset () const noexcept;

			/**
			 * @brief Returns where the length from offset in the VBO or IBO to draw the geometry.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t length () const noexcept;

		private:

			size_t m_offset;
			size_t m_length;
	};
}
