/*
 * Libraries/VertexFactory/TriangleGenerator.hpp
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
#include <set>
#include <type_traits>
#include <vector>

/* Local inclusions */
#include "Math/Vector.hpp"
#include "ShapeBuilder.hpp"

namespace Libraries::VertexFactory
{
	/**
	 * @brief The triangle generator class.
	 * @tparam type_t The precision of data.
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	class TriangleGenerator final
	{
		public:

			/**
			 * @brief Constructs a triangle generator.
			 * @param verticesCount Reserve data for adding vertex. Optional.
			 */
			explicit TriangleGenerator (size_t verticesCount = 0) noexcept
			{
				if ( verticesCount > 0 )
				{
					m_vertices.reserve(verticesCount);
				}
			}

			/**
			 * @brief Adds a vertex.
			 * @param vertex A reference to Vector< 3, type_t >.
			 * @return void
			 */
			void
			addVertex (const Libraries::Math::Vector< 3, type_t > & vertex) noexcept
			{
				m_vertices.emplace_back(vertex);
			}

			/**
			 * @brief Adds a list of vertex.
			 * @param vertex A reference to vector< Vector< 3, type_t > >.
			 * @return void
			 */
			void
			addVertices (const std::vector< Libraries::Math::Vector< 3, type_t > > & vertices) noexcept
			{
				m_vertices.insert(m_vertices.end(), vertices.cbegin(), vertices.cend());
			}

			/**
			 * @brief Adds a list of vertex.
			 * @todo FIXME: Remove internal triangles.
			 * @warning  Bad algorithm.
			 * @param enableReduction Removes central vertices, before creating the envelope.
			 * @return Shape< type_t >
			 */
			Shape< type_t >
			generateEnvelope (bool enableReduction = true) noexcept
			{
				if ( m_vertices.empty() )
				{
					return {};
				}

				/* Vertices reduction. */
				if ( enableReduction && m_vertices.size() > 8 )
				{
					this->verticesReduction();
				}

				/* Generate every triangle possibilities. */
				std::set< std::array< size_t, 3 >, decltype([] (const std::array< size_t, 3 > & lhs, const std::array< size_t, 3 > & rhs) {
					if ( lhs[0] != rhs[0] && lhs[0] != rhs[1] && lhs[0] != rhs[2])
					{
						return true;
					}

					if ( lhs[1] != rhs[0] && lhs[1] != rhs[1] && lhs[1] != rhs[2])
					{
						return true;
					}

					if ( lhs[2] != rhs[0] && lhs[2] != rhs[1] && lhs[2] != rhs[2])
					{
						return true;
					}

					return false;
				}) > triangles;

				const auto verticesCount = m_vertices.size();

				for ( size_t indexA = 0; indexA < verticesCount; indexA++ )
				{
					for ( size_t indexB = 0; indexB < verticesCount; indexB++ )
					{
						if ( indexA == indexB )
						{
							continue;
						}

						for ( size_t indexC = 0; indexC < verticesCount; indexC++ )
						{
							if ( indexB == indexC || indexA == indexC )
							{
								continue;
							}

							triangles.emplace(std::array< size_t, 3 >{indexA, indexB, indexC});
						}
					}
				}

				/* Generate triangles. */
				Shape< type_t > shape{triangles.size() * 3, 1, triangles.size()};

				ShapeBuilder< type_t > builder{shape};

				builder.beginConstruction(ConstructionMode::Triangles);

				for ( const auto & triangle : triangles )
				{
					builder.newVertex(m_vertices[triangle[0]]);
					builder.newVertex(m_vertices[triangle[1]]);
					builder.newVertex(m_vertices[triangle[2]]);
				}

				builder.endConstruction();

				return shape;
			}

			/**
			 * @brief Generates the geometry.
			 * @return Shape< type_t >
			 */
			Shape< type_t >
			generate () noexcept
			{
				if ( m_vertices.empty() )
				{
					return {};
				}

				const auto aggregate = this->getDistancesAggregate();

				/* Generate every triangle possibilities. */
#ifdef __clang__
				auto compare = [] (const std::array< size_t, 3 > & lhs, const std::array< size_t, 3 > & rhs)
				{
					if ( lhs[0] != rhs[0] && lhs[0] != rhs[1] && lhs[0] != rhs[2])
						return true;

					if ( lhs[1] != rhs[0] && lhs[1] != rhs[1] && lhs[1] != rhs[2])
						return true;

					if ( lhs[2] != rhs[0] && lhs[2] != rhs[1] && lhs[2] != rhs[2])
						return true;

					return false;
				};

				std::set< std::array< size_t, 3 >, decltype(compare)> triangles{compare};
#else
				std::set< std::array< size_t, 3 >, decltype([] (const std::array< size_t, 3 > & lhs, const std::array< size_t, 3 > & rhs) {
					if ( lhs[0] != rhs[0] && lhs[0] != rhs[1] && lhs[0] != rhs[2])
					{
						return true;
					}

					if ( lhs[1] != rhs[0] && lhs[1] != rhs[1] && lhs[1] != rhs[2])
					{
						return true;
					}

					if ( lhs[2] != rhs[0] && lhs[2] != rhs[1] && lhs[2] != rhs[2])
					{
						return true;
					}

					return false;
				}) > triangles;
#endif

				const auto verticesCount = m_vertices.size();

				for ( size_t index = 0; index < verticesCount; index++ )
				{
					std::vector< size_t > indexes{};
					indexes.resize(verticesCount);

					for ( size_t subIndex = 0; subIndex < verticesCount; subIndex++ )
					{
						if ( index == subIndex )
						{
							continue;
						}

						const auto distance = Math::Vector< 3, type_t >::distance(m_vertices[index], m_vertices[subIndex]);

						if ( distance <= aggregate[Avg] )
						{
							indexes.emplace_back(subIndex);
						}

						if ( indexes.size() >= 2 )
						{
							triangles.emplace(std::array< size_t, 3 >{index, indexes[0], indexes[1]});
							indexes.clear();
						}
					}
				}

				/* Generate triangles. */
				Shape< type_t > shape{triangles.size() * 3, 1, triangles.size()};

				ShapeBuilder< type_t > builder{shape};

				builder.beginConstruction(ConstructionMode::Triangles);

				for ( const auto & triangle : triangles )
				{
					builder.newVertex(m_vertices[triangle[0]]);
					builder.newVertex(m_vertices[triangle[1]]);
					builder.newVertex(m_vertices[triangle[2]]);
				}

				builder.endConstruction();

				return shape;
			}

			/**
			 * @brief Returns the centroid of the vertices.
			 * @return Math::Vector< 3, type_t >
			 */
			Math::Vector< 3, type_t >
			getCentroid () const noexcept
			{
				if ( m_vertices.empty() )
				{
					return {};
				}

				Math::Vector< 3, type_t > centroid{};

				std::accumulate(m_vertices.cbegin(), m_vertices.cend(), [] (const auto & vertex) {
					return vertex;
				});

				centroid /= m_vertices.size();

				return centroid;
			}

			/**
			 * @brief Returns a list of distances between vertices.
			 * @return std::vector< type_t >
			 */
			[[nodiscard]]
			std::vector< type_t >
			getDistances () const noexcept
			{
				if ( m_vertices.empty() )
				{
					return {};
				}

				const auto verticesCount = m_vertices.size();

				/* Compute vector space. */
				size_t space = 0;
				auto count = verticesCount - 1;

				for ( size_t index = 0; index < verticesCount; index++ )
				{
					space += count--;
				}

				/* Find every distance between every vertex. */
				std::vector< type_t > distances{};
				distances.reserve(space);

				for ( size_t index = 0; index < verticesCount - 1; index++ )
				{
					for ( size_t subIndex = index + 1; subIndex < verticesCount; subIndex++ )
					{
						distances.emplace_back(Math::Vector<3, type_t>::distance(m_vertices[index], m_vertices[subIndex]));
					}
				}

				return distances;
			}

			/**
			 * @brief Returns minimum, maximum and the average distances between vertices.
			 * @return std::array< type_t, 3 >
			 */
			[[nodiscard]]
			std::array< type_t, 3 >
			getDistancesAggregate () const noexcept
			{
				const auto distances = TriangleGenerator::getDistances();

				return {
					*std::min_element(distances.cbegin(), distances.cend()),
					*std::max_element(distances.cbegin(), distances.cend()),
					std::accumulate(distances.cbegin(), distances.cend(), 0.0F) / distances.size()
				};
			}

			/**
			 * @brief Returns a list of distances between vertices and one point.
			 * @param point The reference point.
			 * @return std::vector< type_t >
			 */
			[[nodiscard]]
			std::vector< type_t >
			getDistances (const Math::Vector< 3, type_t > & point) const noexcept
			{
				if ( m_vertices.empty() )
				{
					return {};
				}

				const auto verticesCount = m_vertices.size();

				std::vector< type_t > distances(verticesCount, 0);

				for ( size_t index = 0; index < verticesCount; index++ )
				{
					distances[index] = Math::Vector<3, type_t>::distance(m_vertices[index], point);
				}

				return distances;
			}

			/**
			 * @brief Returns minimum, maximum and the average distances between vertices and one point.
			 * @param point The reference point.
			 * @return std::array< type_t, 3 >
			 */
			[[nodiscard]]
			std::array< type_t, 3 >
			getDistancesAggregate (const Math::Vector< 3, type_t > & point) const noexcept
			{
				const auto distances = TriangleGenerator::getDistances(point);

				return {
					*std::min_element(distances.cbegin(), distances.cend()),
					*std::max_element(distances.cbegin(), distances.cend()),
					std::accumulate(distances.cbegin(), distances.cend(), 0.0F) / distances.size()
				};
			}

		private:

			static constexpr auto Min = 0UL;
			static constexpr auto Max = 1UL;
			static constexpr auto Avg = 2UL;

			/**
			 * @brief Tries to reduce vertex number.
			 * @return void
			 */
			void
			verticesReduction () noexcept
			{
				const auto centroidPosition = this->getCentroid();

				const auto aggregate = this->getDistancesAggregate(centroidPosition);

				auto vertexIt = m_vertices.begin();

				while ( vertexIt != m_vertices.end() )
				{
					const auto distance = Math::Vector< 3, type_t >::distance(centroidPosition, *vertexIt);

					if ( distance < aggregate[Avg] )
					{
						vertexIt = m_vertices.erase(vertexIt);
					}
					else
					{
						++vertexIt;
					}
				}
			}

			std::vector< Libraries::Math::Vector< 3, type_t > > m_vertices{};
	};
}
