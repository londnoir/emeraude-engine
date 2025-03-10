/*
 * src/Libraries/VertexFactory/ShapeTriangle.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <array>
#include <limits>
#include <type_traits>

namespace Libraries::VertexFactory
{
	/**
	 * @brief The shape triangle class.
	 * @tparam data_t The precision type of vertex data. Default float.
	 */
	template< typename data_t = float >
	requires (std::is_floating_point_v< data_t >)
	class ShapeTriangle final
	{
		public:

			/**
			 * @brief Constructs a default triangle.
			 */
			ShapeTriangle () noexcept = default;

			/**
			 * @brief Constructs a triangle with position indexes.
			 * @param geometryVertexIndexA The first position index.
			 * @param geometryVertexIndexB The second position index.
			 * @param geometryVertexIndexC The third position index.
			 */
			ShapeTriangle (size_t geometryVertexIndexA, size_t geometryVertexIndexB, size_t geometryVertexIndexC) noexcept
				: m_vertexIndexes({geometryVertexIndexA, geometryVertexIndexB, geometryVertexIndexC})
			{

			}

			/**
			 * @brief Sets the surface tangent.
			 * @param tangent A reference to a vector.
			 * @return void
			 */
			void
			setSurfaceTangent (const Math::Vector< 3, data_t > & tangent) noexcept
			{
				m_surfaceTangent = tangent;
			}

			/**
			 * @brief Sets the surface normal.
			 * @param normal A reference to a vector.
			 * @return void
			 */
			void
			setSurfaceNormal (const Math::Vector< 3, data_t > & normal) noexcept
			{
				m_surfaceNormal = normal;
			}

			/**
			 * @brief Sets vertex index to one vertex of the triangle..
			 * @param triangleVertexIndex The vertex index of the triangle. Must be 0, 1 or 2 !
			 * @param geometryVertexIndex The vertex index from the geometry data.
			 * @return void
			 */
			void
			setVertexIndex (size_t triangleVertexIndex, size_t geometryVertexIndex) noexcept
			{
				m_vertexIndexes[triangleVertexIndex] = geometryVertexIndex;
			}

			/**
			 * @brief Sets vertex index to one vertex of the triangle..
			 * @param triangleVertexIndex The vertex index of the triangle. Must be 0, 1 or 2 !
			 * @param colorListIndex The color index from the geometry data.
			 * @return void
			 */
			void
			setVertexColorIndex (size_t triangleVertexIndex, size_t colorListIndex) noexcept
			{
				m_vertexColorIndexes[triangleVertexIndex] = colorListIndex;
			}

			/**
			 * @brief Sets edge index to one vertex of the triangle..
			 * @param triangleVertexIndex The vertex index of the triangle. Must be 0, 1 or 2 !
			 * @param edgeListIndex The edge index from the geometry data.
			 * @return void
			 */
			void
			setEdgeIndex (size_t triangleVertexIndex, size_t edgeListIndex) noexcept
			{
				m_edgeIndexes[triangleVertexIndex] = edgeListIndex;
			}

			/**
			 * @brief Returns the surface tangent vector.
			 * @return const Math::Vector< 3, data_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 3, data_t > &
			surfaceTangent () const noexcept
			{
				return m_surfaceTangent;
			}

			/**
			 * @brief Returns the surface normal vector.
			 * @return const Math::Vector< 3, data_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 3, data_t > &
			surfaceNormal () const noexcept
			{
				return m_surfaceNormal;
			}

			/**
			 * @brief Returns the surface bi-normal vector.
			 * @return const Math::Vector< 3, data_t > &
			 */
			[[nodiscard]]
			Math::Vector< 3, data_t >
			surfaceBinormal () const noexcept
			{
				return Math::Vector< 3, data_t >::crossProduct(m_surfaceNormal, m_surfaceTangent);
			}

			/**
			 * @brief Returns the vertex index in the geometry data from one vertex of the triangle.
			 * @param triangleVertexIndex The vertex index of the triangle. Must be 0, 1 or 2 !
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			vertexIndex (size_t triangleVertexIndex) const noexcept
			{
				return m_vertexIndexes[triangleVertexIndex];
			}

			/**
			 * @brief Returns the color index in the geometry data from one vertex of the triangle.
			 * @param triangleVertexIndex The vertex index of the triangle. Must be 0, 1 or 2 !
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			vertexColorIndex (size_t triangleVertexIndex) const noexcept
			{
				return m_vertexColorIndexes[triangleVertexIndex];
			}

			/**
			 * @brief Returns the edge index in the geometry data from one vertex of the triangle.
			 * @param triangleVertexIndex The vertex index of the triangle. Must be 0, 1 or 2 !
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			edgeIndex (size_t triangleVertexIndex) const noexcept
			{
				return m_edgeIndexes[triangleVertexIndex];
			}

			/**
			 * @brief Flips the triangle front-facing.
			 * @return void
			 */
			void
			flip () noexcept
			{
				/* First, we reverse the triangle normal and tangent vectors. */
				m_surfaceNormal.inverse();
				m_surfaceTangent.inverse();

				/* We swap indexes for building the triangle. */
				std::swap(m_vertexIndexes[0], m_vertexIndexes[1]);
				std::swap(m_vertexColorIndexes[0], m_vertexColorIndexes[1]);
			}

			/**
			 * @brief Flips the Y-Axis of tangent, normal and binormal vectors.
			 * @return void
			 */
			void
			flipYAxis () noexcept
			{
				m_surfaceTangent[Math::Y] = -m_surfaceTangent[Math::Y];
				m_surfaceNormal[Math::Y] = -m_surfaceNormal[Math::Y];
			}

		private:

			Math::Vector< 3, data_t > m_surfaceTangent{};
			Math::Vector< 3, data_t > m_surfaceNormal{};
			std::array< size_t, 3 > m_vertexIndexes{0, 0, 0}; /* Position, tangent, normal and texture coordinates indices. */
			std::array< size_t, 3 > m_vertexColorIndexes{0, 0, 0};
			std::array< size_t, 3 > m_edgeIndexes{
				std::numeric_limits< size_t >::max(),
				std::numeric_limits< size_t >::max(),
				std::numeric_limits< size_t >::max()
			};
	};
}
