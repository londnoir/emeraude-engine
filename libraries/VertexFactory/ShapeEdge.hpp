/*
 * Libraries/VertexFactory/ShapeEdge.hpp
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
#include <cstddef>
#include <limits>

namespace Libraries::VertexFactory
{
	/**
	 * @brief The shape edge class.
	 */
	class ShapeEdge final
	{
		public:

			/**
			 * @brief Constructs a default edge.
			 */
			ShapeEdge () noexcept = default;

			/**
			 * @brief Constructs an edge from vertex indices.
			 * @param vertexIndexA The index of the first point for the edge.
			 * @param vertexIndexB The index of the last point for the edge.
			 */
			ShapeEdge (size_t vertexIndexA, size_t vertexIndexB) noexcept;

			/**
			 * @brief Equality operator.
			 * @param operand A reference to a ShapeEdge.
			 * @return bool
			 */
			bool operator== (const ShapeEdge & operand) const noexcept;

			/**
			 * @brief Inequality operator.
			 * @param operand A reference to a ShapeEdge.
			 * @return bool
			 */
			bool operator!= (const ShapeEdge & operand) const noexcept;

			/**
			 * @brief Sets the edge index shared with this one.
			 * @param value The index of the shared edge.
			 */
			void setSharedIndex (size_t index) noexcept;

			/**
			 * @brief Returns whether the edge is valid.
			 * @return bool
			 */
			[[nodiscard]]
			bool isValid () const noexcept;

			/**
			 * @brief Returns the index of the first point for the edge.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t vertexIndexA () const noexcept;

			/**
			 * @brief Returns the index of the last point for the edge.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t vertexIndexB () const noexcept;

			/**
			 * @brief Returns the shared index.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t sharedIndex () const noexcept;

			/**
			 * @brief Checks if the point is equals to this edge.
			 * @param vertexIndexA The index of the first point for the edge.
			 * @param vertexIndexB The index of the last point for the edge.
			 * @return bool
			 */
			[[nodiscard]]
			bool same (size_t vertexIndexA, size_t vertexIndexB) const noexcept;

			/**
			 * @brief Returns whether this edge is shared.
			 * @return bool
			 */
			[[nodiscard]]
			inline
			bool
			isShared () const noexcept
			{
				return m_sharedEdgeIndex < std::numeric_limits< size_t >::max();
			}

		private:

			size_t m_vertexIndexA{0};
			size_t m_vertexIndexB{0};
			size_t m_sharedEdgeIndex{std::numeric_limits< size_t >::max()};
	};
}
