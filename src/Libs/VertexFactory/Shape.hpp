/*
 * src/Libs/VertexFactory/Shape.hpp
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

/* Emeraude-Engine configuration. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>
#include <functional>
#include <set>

/* Local inclusions for usages. */
#include "Libs/Math/Cuboid.hpp"
#include "Libs/Math/Matrix.hpp"
#include "Libs/Math/Sphere.hpp"
#include "Libs/Math/Vector.hpp"
#include "Libs/PixelFactory/Color.hpp"
#include "ShapeEdge.hpp"
#include "ShapeTriangle.hpp"
#include "ShapeVertex.hpp"
#include "TextureCoordinates.hpp"
#include "Types.hpp"

namespace EmEn::Libs::VertexFactory
{
	/**
	 * @brief The shape class for defining a complete geometry.
	 * @tparam data_t The precision type of vertex data. Default float.
	 */
	template< typename data_t = float >
	requires (std::is_floating_point_v< data_t >)
	class Shape final
	{
		public:

			/**
			 * @brief Constructs a default shape.
			 */
			Shape () noexcept = default;

			/**
			 * @brief Constructs a shape and reserve space from triangle count.
			 * @param triangleCount The possible number of triangles to reserve.
			 */
			explicit
			Shape (size_t triangleCount) noexcept
			{
				this->reserveData(triangleCount);
			}

			/**
			 * @brief Constructs a shape and reserve space from vertex attributes count.
			 * @param positionsCount The possible number of position to reserve.
			 * @param vertexColorsCount The possible number of color vertex to reserve.
			 * @param facesCount The possible number of face to reserve.
			 * @param edgesCount The possible number of edge to reserve. Default 0.
			 */
			Shape (size_t positionsCount, size_t vertexColorsCount, size_t facesCount, size_t edgesCount = 0) noexcept
			{
				this->resizeData(positionsCount, vertexColorsCount, facesCount, edgesCount);
			}

			/**
			 * @brief Reserves data for geometry construction to avoid multiple re-allocations.
			 * @param triangleCount The possible number of triangle to reserve.
			 * @return void
			 */
			void
			reserveData (size_t triangleCount) noexcept
			{
				if ( triangleCount == 0 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", reserving data with triangle count equals to zero !" "\n";

					return;
				}

				m_vertices.reserve(triangleCount * 3);
				m_vertexColors.reserve(triangleCount * 3);
				m_triangles.reserve(triangleCount);
				m_edges.reserve(triangleCount * 3);
			}

			/**
			 * @brief Reserves data vectors for geometry construction to avoid multiple re-allocations. Finer version.
			 * @param positionsCount The possible number of position to reserve.
			 * @param vertexColorsCount The possible number of color vertex to reserve.
			 * @param facesCount The possible number of face to reserve.
			 * @param edgesCount The possible number of edge to reserve. Default 0.
			 * @return void
			 */
			void
			reserveData (size_t positionsCount, size_t vertexColorsCount, size_t facesCount, size_t edgesCount = 0) noexcept
			{
				auto somethingReserved = false;

				if ( positionsCount > 0 )
				{
					m_vertices.reserve(positionsCount);

					somethingReserved = true;
				}

				if ( vertexColorsCount > 0 )
				{
					m_vertexColors.reserve(vertexColorsCount);

					somethingReserved = true;
				}

				if ( facesCount > 0 )
				{
					m_triangles.reserve(facesCount);

					somethingReserved = true;
				}

				if ( edgesCount > 0 )
				{
					m_edges.reserve(edgesCount);

					somethingReserved = true;
				}

				if ( !somethingReserved )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", trying to reserve data with all parameters set to zero !" "\n";
				}
			}

			/**
			 * @brief Resizes data vectors for geometry construction to avoid multiple re-allocations. Finer version.
			 * @param positionsCount The possible number of position to reserve.
			 * @param vertexColorsCount The possible number of color vertex to reserve.
			 * @param facesCount The possible number of face to reserve.
			 * @param edgesCount The possible number of edge to reserve. Default 0.
			 * @return void
			 */
			void
			resizeData (size_t positionsCount, size_t vertexColorsCount, size_t facesCount, size_t edgesCount = 0) noexcept
			{
				m_vertices.resize(positionsCount);
				m_vertexColors.resize(vertexColorsCount);
				m_triangles.resize(facesCount);
				m_edges.resize(edgesCount);
			}

			/**
			 * @brief Clears geometry data.
			 * @return void
			 */
			void
			clear () noexcept
			{
				m_vertices.clear();
				m_vertexColors.clear();
				m_triangles.clear();
				m_edges.clear();
				m_groups.clear();
				m_groups.resize(1);
				m_boundingBox.reset();
				m_boundingSphere.reset();
				m_farthestDistance = 0;
				m_flags[TextureCoordinatesDeclared] = false;
			}

			/**
			 * @brief Returns the number of vertex.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			vertexCount () const noexcept
			{
				return m_vertices.size();
			}

			/**
			 * @brief Gives access to the vertices list.
			 * @return const std::vector< ShapeVertex< data_t > > &
			 */
			[[nodiscard]]
			const std::vector< ShapeVertex< data_t > > &
			vertices () const noexcept
			{
				return m_vertices;
			}

			/**
			 * @brief Gives access to the vertex colors list.
			 * @return const std::vector< Math::Vector< 4, data_t > > &
			 */
			[[nodiscard]]
			const std::vector< Math::Vector< 4, data_t > > &
			vertexColors () const noexcept
			{
				return m_vertexColors;
			}

			/**
			 * @brief Gives access to the triangles list.
			 * @return const std::vector< ShapeTriangle< data_t > > &
			 */
			[[nodiscard]]
			const std::vector< ShapeTriangle< data_t > > &
			triangles () const noexcept
			{
				return m_triangles;
			}

			/**
			 * @brief Returns a vertex from the list.
			 * @param index The index of the vertex in the list. You should get it from a ShapeTriangle.
			 * @return const ShapeVertex< data_t > &
			 */
			[[nodiscard]]
			const ShapeVertex< data_t > &
			vertex (size_t index) const noexcept
			{
				return m_vertices[index];
			}

			/**
			 * @brief Returns a vertex color from the list.
			 * @param index The index of the vertex color in the list. You should get it from a ShapeTriangle.
			 * @return const Math::Vector< 4, data_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 4, data_t > &
			vertexColor (size_t index) const noexcept
			{
				return m_vertexColors[index];
			}

			/**
			 * @brief Gives access to the edges list.
			 * @return const std::vector< ShapeEdge > &
			 */
			[[nodiscard]]
			const std::vector< ShapeEdge > &
			edges () const noexcept
			{
				return m_edges;
			}

			/**
			 * @brief Gives access to the bounding box.
			 * @return const Math::Cuboid< data_t > &
			 */
			[[nodiscard]]
			const Math::Cuboid< data_t > &
			boundingBox () const noexcept
			{
				return m_boundingBox;
			}

			/**
			 * @brief Gives access to the bounding sphere.
			 * @return const Math::Sphere< data_t > &
			 */
			[[nodiscard]]
			const Math::Sphere< data_t > &
			boundingSphere () const noexcept
			{
				return m_boundingSphere;
			}

			/**
			 * @brief Returns whether the geometry is composed of group.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			hasGroups () const noexcept
			{
				return m_groups.size() > 1;
			}

			/**
			 * @brief Returns the number of group the geometry is composed of.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			groupCount () const noexcept
			{
				return m_groups.size();
			}

			/**
			 * @brief Returns the group list the geometry is composed of.
			 * @return std::vector< std::pair< size_t, size_t > > &
			 */
			[[nodiscard]]
			const std::vector< std::pair< size_t, size_t > > &
			groups () const noexcept
			{
				return m_groups;
			}

			/**
			 * @brief Returns the average center of the geometry.
			 * @return const Math::Vector< 3, data_t > &
			 */
			[[nodiscard]]
			const Math::Vector< 3, data_t > &
			centroid () const noexcept
			{
				return m_boundingSphere.position();
			}

			/**
			 * @brief Returns the distance of the farthest vertex from the origin (0, 0, 0).
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			farthestDistance () const noexcept
			{
				return m_farthestDistance;
			}

			/**
			 * @brief Checks if the geometry is valid.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isValid () const noexcept
			{
				return !m_triangles.empty();
			}

			/**
			 * @brief Checks if the geometry is empty.
			 * @note Inverse of Shape::isValid(). Provided to satisfy C++ conventions.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			empty () const noexcept
			{
				return m_triangles.empty();
			}

			/**
			 * @brief Returns whether the geometry is an open shape or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isOpen () const noexcept
			{
				/* NOTE : if only one edge is not shared, then the geometry is open. */
				return std::ranges::any_of(m_edges, [] (const auto & edge) {
					return !edge.isShared();
				});
			}

			/**
			 * @brief Returns whether texture coordinates is available.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isTextureCoordinatesAvailable () const noexcept
			{
				return m_flags[TextureCoordinatesDeclared];
			}

			/**
			 * @brief Returns whether vertex color is available.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isVertexColorAvailable () const noexcept
			{
				return !m_vertexColors.empty();
			}

			/**
			 * @brief Generates automatically texture coordinates for the geometry.
			 * @param uScale U component scaling value. Default 1.
			 * @param vScale V component scaling value. Default 1.
			 * @param wScale W component scaling value. Default 1.
			 * @return bool
			 */
			bool
			generateTextureCoordinates (data_t uScale = 1, data_t vScale = 1, data_t wScale = 1) noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry data is empty !" "\n";

					return false;
				}

				#pragma omp parallel for default(none) shared(uScale, vScale, wScale)
				for ( const auto & triangle : m_triangles )
				{
					for ( size_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex )
					{
						auto & currentVertex = m_vertices[triangle.vertexIndex(vertexIndex)];

						auto textureCoordinates = TextureCoordinates::generateCubicCoordinates(currentVertex.position(), currentVertex.normal());
						textureCoordinates[Math::U] *= uScale;
						textureCoordinates[Math::V] *= vScale;
						textureCoordinates[Math::W] *= wScale;

						currentVertex.setTextureCoordinates(textureCoordinates);
					}
				}

				m_flags[TextureCoordinatesDeclared] = true;

				return true;
			}

			/**
			 * @brief Computes normal vector for every triangle.
			 * @return bool
			 */
			bool
			computeTriangleNormal () noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry data is empty !" "\n";

					return false;
				}

				#pragma omp parallel for default(none)
				for ( auto & triangle : m_triangles )
				{
					const auto & vertexA = m_vertices[triangle.vertexIndex(0)];
					const auto & vertexB = m_vertices[triangle.vertexIndex(1)];
					const auto & vertexC = m_vertices[triangle.vertexIndex(2)];

					/* Compute the surface normal. */
					const auto normal = Math::Vector< 3, data_t >::normal(
						vertexA.position(),
						vertexB.position(),
						vertexC.position()
					);

					triangle.setSurfaceNormal(normal);
				}

				return true;
			}

			/**
			 * @brief Computes tangent vector for every triangle.
			 * @warning The texture coordinates attributes are requested.
			 * @return bool
			 */
			bool
			computeTriangleTangent () noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry data is empty !" "\n";

					return false;
				}

				if ( !this->isTextureCoordinatesAvailable() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", there is no texture coordinates !" "\n";

					return false;
				}

				#pragma omp parallel for default(none)
				for ( auto & triangle : m_triangles )
				{
					const auto & vertexA = m_vertices[triangle.vertexIndex(0)];
					const auto & vertexB = m_vertices[triangle.vertexIndex(1)];
					const auto & vertexC = m_vertices[triangle.vertexIndex(2)];

					/* Compute the surface tangent. */
					const auto tangent = Math::Vector< 3, data_t >::tangent(
						vertexA.position(),
						vertexA.textureCoordinates(),
						vertexB.position(),
						vertexB.textureCoordinates(),
						vertexC.position(),
						vertexC.textureCoordinates()
					);

					triangle.setSurfaceTangent(tangent);
				}

				return true;
			}

			/**
			 * @brief Computes normal and tangent vectors for every triangle.
			 * @note If normals are present, use Shape::computeTriangleTangent() instead.
			 * @warning The texture coordinates attributes are requested.
			 * @return bool
			 */
			bool
			computeTriangleTBNSpace () noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry data is empty !" "\n";

					return false;
				}

				if ( !this->isTextureCoordinatesAvailable() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", there is no texture coordinates !" "\n";

					return false;
				}

				#pragma omp parallel for default(none)
				for ( auto & triangle : m_triangles )
				{
					const auto & vertexA = m_vertices[triangle.vertexIndex(0)];
					const auto & vertexB = m_vertices[triangle.vertexIndex(1)];
					const auto & vertexC = m_vertices[triangle.vertexIndex(2)];

					/* Compute the surface tangent. */
					const auto tangent = Math::Vector< 3, data_t >::tangent(
						vertexA.position(),
						vertexA.textureCoordinates(),
						vertexB.position(),
						vertexB.textureCoordinates(),
						vertexC.position(),
						vertexC.textureCoordinates()
					);

					triangle.setSurfaceTangent(tangent);

					/* Compute the surface normal. */
					const auto normal = Math::Vector< 3, data_t >::normal(
						vertexA.position(),
						vertexB.position(),
						vertexC.position()
					);

					triangle.setSurfaceNormal(normal);
				}

				return true;
			}

			/**
			 * @brief Computes normal vector for every vertex.
			 * @warning Geometry must have normal vectors computed for every triangle.
			 * @return bool
			 */
			bool
			computeVertexNormal () noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry is empty !" "\n";

					return false;
				}

				const auto verticesCount = m_vertices.size();

				#pragma omp parallel for default(none) shared(verticesCount)
				for ( size_t globalVertexIndex = 0; globalVertexIndex < verticesCount; globalVertexIndex++ )
				{
					Math::Vector< 3, data_t > normal;

					/* We look for every triangle sharing this vertex, add every vector then normalize. */
					for ( const auto & triangle : m_triangles )
					{
						for ( size_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex )
						{
							if ( triangle.vertexIndex(vertexIndex) != globalVertexIndex )
							{
								continue;
							}

							const auto & surfaceNormal = triangle.surfaceNormal();

							normal += surfaceNormal;
						}
					}

					m_vertices[globalVertexIndex].setNormal(normal.normalize());
				}

				return true;
			}

			/**
			 * @brief Computes tangent vector for every vertex.
			 * @warning Geometry must have tangent vectors computed for every triangle.
			 * @return bool
			 */
			bool
			computeVertexTangent () noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry is empty !" "\n";

					return false;
				}

				const auto verticesCount = m_vertices.size();

				#pragma omp parallel for default(none) shared(verticesCount)
				for ( size_t globalVertexIndex = 0; globalVertexIndex < verticesCount; globalVertexIndex++ )
				{
					Math::Vector< 3, data_t > tangent;

					/* We look for every triangle sharing this vertex, add every vector then normalize. */
					for ( const auto & triangle : m_triangles )
					{
						for ( size_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex )
						{
							if ( triangle.vertexIndex(vertexIndex) != globalVertexIndex )
							{
								continue;
							}

							const auto & surfaceTangent = triangle.surfaceTangent();

							tangent += surfaceTangent;
						}
					}

					m_vertices[globalVertexIndex].setTangent(tangent.normalize());
				}

				return true;
			}

			/**
			 * @brief Computes normal and tangent vectors for every vertex.
			 * @note If normals are present, use Shape::computeVertexTangent() instead.
			 * @warning Geometry must have normal and tangent vectors computed for every triangle.
			 * @return bool
			 */
			bool
			computeVertexTBNSpace () noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry is empty !" "\n";

					return false;
				}

				const auto verticesCount = m_vertices.size();

				#pragma omp parallel for default(none) shared(verticesCount)
				for ( size_t globalVertexIndex = 0; globalVertexIndex < verticesCount; globalVertexIndex++ )
				{
					Math::Vector< 3, data_t > tangent{};
					Math::Vector< 3, data_t > normal{};

					/* We look for every triangle sharing this vertex, add every vector then normalize. */
					for ( const auto & triangle : m_triangles )
					{
						for ( size_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex )
						{
							if ( triangle.vertexIndex(vertexIndex) != globalVertexIndex )
							{
								continue;
							}

							tangent += triangle.surfaceTangent();
							normal += triangle.surfaceNormal();
						}
					}

					m_vertices[globalVertexIndex].setTangent(tangent.normalize());
					m_vertices[globalVertexIndex].setNormal(normal.normalize());
				}

				return true;
			}

			/**
			 * @brief Moves axis origin the bottom of the geometry.
			 * @param updateProperties Enable the shape properties update. Default true.
			 * @return void
			 */
			void
			setCenterAtBottom (bool updateProperties = true)
			{
				/* Find the lowest position. */
				auto bottom = std::numeric_limits< data_t >::max();

				for ( const auto & vertexRef : m_vertices )
				{
					if ( vertexRef.position()[Math::Y] < bottom )
					{
						bottom = vertexRef.position()[Math::Y];
					}
				}

				this->transform(Math::Matrix< 4, data_t >::translation(0, bottom, 0), updateProperties);
			}

			/**
			 * @brief Performs a geometry transformation with a Matrix 4x4.
			 * @param transform A reference to a matrix.
			 * @param updateProperties Enable the shape properties to update. Default true.
			 * @return void
			 */
			void
			transform (const Math::Matrix< 4, data_t > & transform, bool updateProperties = true) noexcept
			{
				/* NOTE : For tangents and normals transformation,
				 * we don't want to translate the vector. */
				auto noTranslate(transform);
				noTranslate.clearTranslation();

				for ( auto & vertexRef : m_vertices )
				{
					vertexRef.setPosition(transform * Math::Vector< 4, data_t >(vertexRef.position(), 1));
					vertexRef.setTangent((noTranslate * Math::Vector< 4, data_t >(vertexRef.tangent(), 0)).normalize());
					vertexRef.setNormal((noTranslate * Math::Vector< 4, data_t >(vertexRef.normal(), 0)).normalize());
				}

				/* Updates the invalided bounding box. */
				if ( updateProperties )
				{
					this->updateProperties();
				}
			}

			/**
			 * @brief Removes vertices too close to each other under a tolerance value.
			 * @param vertexDistanceTolerance The distance below which two vertices will be welded.
			 * @return void
			 */
			[[deprecated("Not working correctly")]]
			void
			removeDoubleVertices (data_t vertexDistanceTolerance) noexcept
			{
				/* Gets a copy of the vertices position and clean the vector for replacement. */
				const std::vector< ShapeVertex< data_t > > baseVertices(m_vertices);

				m_vertices.clear();

				/* For every old vertex ... */
				for ( size_t baseIndex = 0; baseIndex < baseVertices.size(); baseIndex++ )
				{
					const auto & baseVertex = baseVertices[baseIndex];

					/* ... We check if we don't found a close position in the new list. */
					auto found = false;
					size_t newIndex = 0;

					for ( const auto & vertexRef : m_vertices )
					{
						if ( Math::Vector< 3, data_t >::distance(baseVertex.position(), vertexRef.position()) < vertexDistanceTolerance )
						{
							found = true;

							break;
						}

						newIndex++;
					}

					/* If not found, we put the new vertex position. */
					if ( !found )
					{
						m_vertices.emplace_back(baseVertex);

						newIndex = m_vertices.size() - 1;
					}

					/* Ne replacement requested. */
					if ( baseIndex == newIndex )
					{
						continue;
					}

					/* We processLogics every face index for vertices position. */
					for ( auto & triangle : m_triangles )
					{
						for ( size_t vertexIndex = 0; vertexIndex < 3; vertexIndex++ )
						{
							if ( triangle.vertexIndex(vertexIndex) == baseIndex )
							{
								triangle.setVertexIndex(vertexIndex, newIndex);
							}
						}
					}
				}

				/* Removes invalid triangles. */
				auto triangleIt = m_triangles.begin();

				while ( triangleIt != m_triangles.end() )
				{
					if ( (*triangleIt).vertexIndex(0) == (*triangleIt).vertexIndex(1) || (*triangleIt).vertexIndex(0) == (*triangleIt).vertexIndex(2) || (*triangleIt).vertexIndex(1) == (*triangleIt).vertexIndex(2) )
					{
						triangleIt = m_triangles.erase(triangleIt);
					}
					else
					{
						++triangleIt;
					}
				}
			}

			/**
			 * @brief Removes all vertex color information and replace by a new one.
			 * @param color The new color.
			 * @return void
			 */
			void
			setGlobalVertexColor (const Math::Vector< 4, data_t > & color) noexcept
			{
				m_vertexColors.clear();
				m_vertexColors.emplace_back(color);

				/* Sets color pointer to index 0, the unique color. */
				for ( auto & triangle : m_triangles )
				{
					for ( size_t vertexIndex = 0; vertexIndex < 3; vertexIndex++ )
					{
						triangle.setVertexColorIndex(vertexIndex, 0);
					}
				}
			}

			/**
			 * @brief Removes all vertex color information and replace by a new one.
			 * @param color The new color.
			 * @return void
			 */
			void
			setGlobalVertexColor (const PixelFactory::Color< float > & color) noexcept
			{
				this->setGlobalVertexColor(color.toVector4< float >());
			}

			/**
			 * @brief Flips the surface of the shape. This will reverse the order of vertices and the normal and tangent vectors of every triangle.
			 * @return void
			 */
			void
			flipSurface () noexcept
			{
				for ( auto & vertex : m_vertices )
				{
					vertex.flip();
				}

				for ( auto & triangle : m_triangles )
				{
					triangle.flip();
				}
			}

			/**
			 * @brief Flip the Y-Axis of every vertex attributes.
			 * @return void
			 */
			void
			flipYAxis () noexcept
			{
				for ( auto & vertex : m_vertices )
				{
					vertex.flipYAxis();
				}

				for ( auto & triangle : m_triangles )
				{
					triangle.flipYAxis();
				}
			}

			/**
			 * @brief Builds a shape using a function giving access to shape data.
			 * @param buildFunction A reference to a function.
			 * @param textureCoordinatesDeclared Set if texture coordinates will be set during the build.
			 * @param computeEdges Declares if edges must be calculated. Default false.
			 * @return bool
			 */
			bool
			build (const std::function< bool (std::vector< std::pair< size_t, size_t > > &, std::vector< ShapeVertex< data_t > > &, std::vector< ShapeTriangle< data_t > > &) > & buildFunction, bool textureCoordinatesDeclared, bool computeEdges = false) noexcept
			{
				this->clear();

				m_flags[TextureCoordinatesDeclared] = textureCoordinatesDeclared;
				m_flags[ComputeEdges] = computeEdges;

				if ( !buildFunction(m_groups, m_vertices, m_triangles) )
				{
					return false;
				}

				this->updateProperties();

				return true;
			}

			/**
			 * @brief Creates an indexed vertex buffer.
			 * @note Returns the element count in one vertex.
			 * @tparam buffer_t The precision of vertex attribute data.
			 * @param vertexBuffer A reference to the vertex buffer.
			 * @param normalType Set the normal format. Default none.
			 * @param textureCoordinatesType Set the texture coordinates format. Default none.
			 * @param vertexColorType Set the vertex color format. Default none.
			 * @param skeletalAnimationType Set vertex attributes for skeletal animation. Default none.
			 * @return size_t
			 */
			template< typename buffer_t = float >
			size_t
			createVertexBuffer (std::vector< buffer_t > & vertexBuffer, NormalType normalType = NormalType::None, TextureCoordinatesType textureCoordinatesType = TextureCoordinatesType::None, VertexColorType vertexColorType = VertexColorType::None, SkeletalAnimationType skeletalAnimationType = SkeletalAnimationType::None) const requires (std::is_floating_point_v< buffer_t >)
			{
				const auto vertexElementCount = getVertexElementCount(normalType, textureCoordinatesType, vertexColorType, skeletalAnimationType);

				/* NOTE: Resize destination buffers. */
				vertexBuffer.resize(m_triangles.size() * 3 * vertexElementCount);

				size_t indexBufferOffset = 0;

				for ( const auto & triangle : m_triangles )
				{
					for ( size_t triangleVertexIndex = 0; triangleVertexIndex < 3; ++triangleVertexIndex)
					{
						const auto shapeVertexIndex = triangle.vertexIndex(triangleVertexIndex);
						const auto & vertex = m_vertices[shapeVertexIndex];

						size_t vertexBufferOffset = vertexElementCount * indexBufferOffset;

						indexBufferOffset++;

						/* Positions */
						Shape::writeVector3ToBuffer(vertex.position(), vertexBuffer, vertexBufferOffset);

						/* Normals */
						switch ( normalType )
						{
							case NormalType::Normal :
								Shape::writeVector3ToBuffer(vertex.normal(), vertexBuffer, vertexBufferOffset);
								break;

							case NormalType::TangentNormal :
								Shape::writeVector3ToBuffer(vertex.tangent(), vertexBuffer, vertexBufferOffset);
								Shape::writeVector3ToBuffer(vertex.normal(), vertexBuffer, vertexBufferOffset);
								break;

							case NormalType::TBNSpace :
								Shape::writeVector3ToBuffer(vertex.tangent(), vertexBuffer, vertexBufferOffset);
								Shape::writeVector3ToBuffer(vertex.biNormal(), vertexBuffer, vertexBufferOffset);
								Shape::writeVector3ToBuffer(vertex.normal(), vertexBuffer, vertexBufferOffset);
								break;

							default:
								break;
						}

						/* Texture Coordinates */
						switch ( textureCoordinatesType )
						{
							case TextureCoordinatesType::UV :
								Shape::writeVector2ToBuffer(vertex.textureCoordinates(), vertexBuffer, vertexBufferOffset);
								break;

							case TextureCoordinatesType::UVW :
								Shape::writeVector3ToBuffer(vertex.textureCoordinates(), vertexBuffer, vertexBufferOffset);
								break;

							default:
								break;
						}

						/* Vertex Colors */
						if ( vertexColorType != VertexColorType::None )
						{
							const auto & vertexColor = m_vertexColors[triangle.vertexColorIndex(triangleVertexIndex)];

							switch ( vertexColorType )
							{
								case VertexColorType::Gray :
									Shape::writeVector1ToBuffer(vertexColor, vertexBuffer, vertexBufferOffset);
									break;

								case VertexColorType::RGB :
									Shape::writeVector3ToBuffer(vertexColor, vertexBuffer, vertexBufferOffset);
									break;

								case VertexColorType::RGBA :
									Shape::writeVector4ToBuffer(vertexColor, vertexBuffer, vertexBufferOffset);
									break;

								default:
									break;
							}
						}

						switch ( skeletalAnimationType )
						{
							case SkeletalAnimationType::Average3:
								Shape::writeVector3ToBuffer(vertex.influences(), vertexBuffer, vertexBufferOffset);
								break;

							case SkeletalAnimationType::Average4:
								Shape::writeVector4ToBuffer(vertex.influences(), vertexBuffer, vertexBufferOffset);
								break;

							case SkeletalAnimationType::Weighted3:
								Shape::writeVector3ToBuffer(vertex.influences(), vertexBuffer, vertexBufferOffset);
								Shape::writeVector3ToBuffer(vertex.weights(), vertexBuffer, vertexBufferOffset);
								break;

							case SkeletalAnimationType::Weighted4:
								Shape::writeVector4ToBuffer(vertex.influences(), vertexBuffer, vertexBufferOffset);
								Shape::writeVector4ToBuffer(vertex.weights(), vertexBuffer, vertexBufferOffset);
								break;

							default:
								break;
						}
					}
				}

				return vertexElementCount;
			}

			/**
			 * @brief Creates an indexed vertex buffer.
			 * @note Returns the element count in one vertex.
			 * @tparam buffer_t The precision of vertex attribute data.
			 * @tparam indexType_t The precision of index data.
			 * @param vertexBuffer A reference to the vertex buffer.
			 * @param indexBuffer A reference to the index buffer.
			 * @param normalType Set the normal format. Default none.
			 * @param textureCoordinatesType Set the texture coordinates format. Default none.
			 * @param vertexColorType Set the vertex color format. Default none.
			 * @param skeletalAnimationType Set vertex attributes for skeletal animation. Default none.
			 * @return size_t
			 */
			template< typename buffer_t = float, typename indexType_t = uint32_t >
			size_t
			createIndexedVertexBuffer (std::vector< buffer_t > & vertexBuffer, std::vector< indexType_t > & indexBuffer, NormalType normalType = NormalType::None, TextureCoordinatesType textureCoordinatesType = TextureCoordinatesType::None, VertexColorType vertexColorType = VertexColorType::None, SkeletalAnimationType skeletalAnimationType = SkeletalAnimationType::None) const noexcept requires (std::is_floating_point_v< buffer_t >, std::is_integral_v< indexType_t >)
			{
				/* NOTE: Keep track of vertex already used. */
				std::set< size_t > shapeVertexIndicesDone{};

				const auto vertexElementCount = getVertexElementCount(normalType, textureCoordinatesType, vertexColorType, skeletalAnimationType);

				/* NOTE: Resize destination buffers. */
				vertexBuffer.resize(m_vertices.size() * vertexElementCount);
				indexBuffer.resize(m_triangles.size() * 3);

				size_t indexBufferOffset = 0;

				for ( const auto & triangle : m_triangles )
				{
					for ( size_t triangleVertexIndex = 0; triangleVertexIndex < 3; ++triangleVertexIndex )
					{
						const auto shapeVertexIndex = triangle.vertexIndex(triangleVertexIndex);

						indexBuffer[indexBufferOffset++] = static_cast< indexType_t >(shapeVertexIndex);

						/* NOTE: Skip the vertex index already done. */
						if ( shapeVertexIndicesDone.contains(shapeVertexIndex) )
						{
							continue;
						}

						const auto & vertex = m_vertices.at(shapeVertexIndex);

						size_t vertexBufferOffset = vertexElementCount * shapeVertexIndex;

						/* Positions */
						Shape::writeVector3ToBuffer(vertex.position(), vertexBuffer, vertexBufferOffset);

						/* Normals */
						switch ( normalType )
						{
							case NormalType::Normal :
								Shape::writeVector3ToBuffer(vertex.normal(), vertexBuffer, vertexBufferOffset);
								break;

							case NormalType::TangentNormal :
								Shape::writeVector3ToBuffer(vertex.tangent(), vertexBuffer, vertexBufferOffset);
								Shape::writeVector3ToBuffer(vertex.normal(), vertexBuffer, vertexBufferOffset);
								break;

							case NormalType::TBNSpace :
								Shape::writeVector3ToBuffer(vertex.tangent(), vertexBuffer, vertexBufferOffset);
								Shape::writeVector3ToBuffer(vertex.biNormal(), vertexBuffer, vertexBufferOffset);
								Shape::writeVector3ToBuffer(vertex.normal(), vertexBuffer, vertexBufferOffset);
								break;

							default:
								break;
						}

						/* Texture Coordinates */
						switch ( textureCoordinatesType )
						{
							case TextureCoordinatesType::UV :
								Shape::writeVector2ToBuffer(vertex.textureCoordinates(), vertexBuffer, vertexBufferOffset);
								break;

							case TextureCoordinatesType::UVW :
								Shape::writeVector3ToBuffer(vertex.textureCoordinates(), vertexBuffer, vertexBufferOffset);
								break;

							default:
								break;
						}

						/* Vertex Colors */
						if ( vertexColorType != VertexColorType::None )
						{
							const auto & vertexColor = m_vertexColors[triangle.vertexColorIndex(triangleVertexIndex)];

							switch ( vertexColorType )
							{
								case VertexColorType::Gray :
									Shape::writeVector1ToBuffer(vertexColor, vertexBuffer, vertexBufferOffset);
									break;

								case VertexColorType::RGB :
									Shape::writeVector3ToBuffer(vertexColor, vertexBuffer, vertexBufferOffset);
									break;

								case VertexColorType::RGBA :
									Shape::writeVector4ToBuffer(vertexColor, vertexBuffer, vertexBufferOffset);
									break;

								default:
									break;
							}
						}

						switch ( skeletalAnimationType )
						{
							case SkeletalAnimationType::Average3:
								Shape::writeVector3ToBuffer< 4, int32_t >(vertex.influences(), vertexBuffer, vertexBufferOffset);
								break;

							case SkeletalAnimationType::Average4:
								Shape::writeVector4ToBuffer< int32_t >(vertex.influences(), vertexBuffer, vertexBufferOffset);
								break;

							case SkeletalAnimationType::Weighted3:
								Shape::writeVector3ToBuffer< 4, int32_t >(vertex.influences(), vertexBuffer, vertexBufferOffset);
								Shape::writeVector3ToBuffer(vertex.weights(), vertexBuffer, vertexBufferOffset);
								break;

							case SkeletalAnimationType::Weighted4:
								Shape::writeVector4ToBuffer< int32_t >(vertex.influences(), vertexBuffer, vertexBufferOffset);
								Shape::writeVector4ToBuffer(vertex.weights(), vertexBuffer, vertexBufferOffset);
								break;

							default:
								break;
						}

						shapeVertexIndicesDone.emplace(shapeVertexIndex);
					}
				}

				return vertexElementCount;
			}

			/**
			 * @brief Declares a new group.
			 * @note This function is for building the shape manually.
			 * @return void
			 */
			void
			newGroup () noexcept
			{
				if ( m_triangles.empty() )
				{
					return;
				}

				/* Creates a new group with the offset
				 * according to triangles execute offset. */
				m_groups.emplace_back(m_triangles.size(), 0);
			}

			/**
			 * @brief Declares a new vertex and returns the index of the new vertex.
			 * @note This function is for building the shape manually.
			 * @param position A reference to a vector.
			 * @return size_t
			 */
			size_t
			addVertex (const Math::Vector< 3, data_t > & position) noexcept
			{
				size_t offset = 0;

				for ( const auto & vertexRef : m_vertices )
				{
					if ( vertexRef.position() == position )
					{
						return offset;
					}

					offset++;
				}

				return this->saveVertex(position, {}, {});
			}

			/**
			 * @brief Declares a new vertex.
			 * @note This function is for building the shape manually.
			 * @param position The position of the vertex.
			 * @param normal The normal of the vertex.
			 * @return size_t The index of the new vertex.
			 */
			size_t
			addVertex (const Math::Vector< 3, data_t > & position, const Math::Vector< 3, data_t > & normal) noexcept
			{
				size_t offset = 0;

				for ( const auto & vertexRef : m_vertices )
				{
					if ( vertexRef.position() == position && vertexRef.normal() == normal )
					{
						return offset;
					}

					offset++;
				}

				return this->saveVertex(position, normal, {});
			}

			/**
			 * @brief Declares a new vertex.
			 * @note This function is for building the shape manually.
			 * @param position The position of the vertex.
			 * @param normal The normal of the vertex.
			 * @param textureCoordinates The texture coordinates to that vertex.
			 * @return size_t The index of the new vertex.
			 */
			size_t
			addVertex (const Math::Vector< 3, data_t > & position, const Math::Vector< 3, data_t > & normal, const Math::Vector< 3, data_t > & textureCoordinates) noexcept
			{
				size_t offset = 0;

				for ( const auto & vertexRef : m_vertices )
				{
					if ( vertexRef.position() == position && vertexRef.normal() == normal && vertexRef.textureCoordinates() == textureCoordinates )
					{
						return offset;
					}

					offset++;
				}

				return this->saveVertex(position, normal, textureCoordinates);
			}

			/**
			 * @brief Declares a new vertex color.
			 * @note This function is for building the shape manually.
			 * @param color The color.
			 * @return size_t The index of the new vertex color.
			 */
			size_t
			addVertexColor (const Math::Vector< 4, data_t > & color) noexcept
			{
				size_t offset = 0;

				for ( const auto & existingColor : m_vertexColors )
				{
					if ( existingColor == color )
					{
						return offset;
					}

					offset++;
				}

				return this->saveVertexColor(color);
			}

			/**
			 * @brief Saves a new vertex.
			 * @note This function is for building the shape manually.
			 * @param position The position of the vertex.
			 * @param normal The normal of the vertex.
			 * @param textureCoordinates The texture coordinates to that vertex.
			 * @return size_t The index of the new vertex.
			 */
			size_t
			saveVertex (const Math::Vector< 3, data_t > & position, const Math::Vector< 3, data_t > & normal = {}, const Math::Vector< 3, data_t > & textureCoordinates = {}) noexcept
			{
				m_vertices.emplace_back(position, normal, textureCoordinates);

				m_flags[TextureCoordinatesDeclared] = true;

				return m_vertices.size() - 1;
			}

			/**
			 * @brief Saves a new vertex color.
			 * @note This function is for building the shape manually.
			 * @param color The color.
			 * @return size_t The index of the new vertex color.
			 */
			size_t
			saveVertexColor (const Math::Vector< 4, data_t > & color) noexcept
			{
				m_vertexColors.emplace_back(color);

				return m_vertexColors.size() - 1;
			}

			/**
			 * @brief Declares a new triangle.
			 * @param triangle The triangle object.
			 * @return void
			 */
			void
			addTriangle (ShapeTriangle< data_t > & triangle) noexcept
			{
				/* Creates edges */
				triangle.setEdgeIndex(0, this->addEdge(triangle.vertexIndex(0), triangle.vertexIndex(1)));
				triangle.setEdgeIndex(1, this->addEdge(triangle.vertexIndex(1), triangle.vertexIndex(2)));
				triangle.setEdgeIndex(2, this->addEdge(triangle.vertexIndex(2), triangle.vertexIndex(0)));

				m_triangles.emplace_back(triangle);

				/* Updates group system. */
				if ( m_groups.empty() )
				{
					this->newGroup();
				}
				else
				{
					m_groups.back().second++;
				}
			}

			/**
			 * @brief Recomputes the centroid and the bounding box.
			 * @return void
			 */
			void
			updateProperties () noexcept
			{
				/* Reset properties. */
				m_boundingBox.reset();
				m_boundingSphere.reset();
				m_farthestDistance = 0;

				/* NOTE: This will hold up the center of every vertex. */
				Math::Vector< 3, data_t > centroid;

				for ( const auto & vertexRef : m_vertices )
				{
					/* Update the bounding box. */
					m_boundingBox.merge(vertexRef.position());

					centroid += vertexRef.position();

					/* Update the farthest point from the origin. */
					const auto distance = vertexRef.position().length();

					if ( distance > m_farthestDistance )
					{
						m_farthestDistance = distance;
					}
				}

				centroid /= m_vertices.size();

				data_t centroidDistance = 0;

				for ( const auto & vertexRef : m_vertices )
				{
					/* Update the farthest point from the origin. */
					const auto distance = (vertexRef.position() - centroid).length();

					if ( distance > centroidDistance )
					{
						centroidDistance = distance;
					}
				}

				m_boundingSphere.setRadius(centroidDistance);
				m_boundingSphere.setPosition(centroid);

#ifdef EMERAUDE_DEBUG_VERTEX_FACTORY
				std::cout <<
					"[DEBUG:VERTEX_FACTORY] Updating shape infos" "\n" <<
					m_boundingBox <<
					m_boundingSphere <<
					"Farthest distance : " << m_farthestDistance << "\n"
					"Centroid : " << centroid << "\n"
					"Centroid distance : " << centroid.length() << "\n";
#endif
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Shape & obj)
			{
				out <<
					"Shape triangle count: " << obj.m_triangles.size() << ", "
					"vertex count: " << obj.m_vertices.size() << ", "
					"vertex color count: " << obj.m_vertexColors.size() << "\n";

				size_t triangleIndex = 0;

				for ( const auto & triangle : obj.m_triangles )
				{
					out << "Triangle #" << triangleIndex << ", ";

					for ( size_t triangleVertexIndex = 0; triangleVertexIndex < 3; ++triangleVertexIndex )
					{
						const auto shapeVertexIndex = triangle.vertexIndex(triangleVertexIndex);
						const auto & vertex = obj.m_vertices.at(shapeVertexIndex);

						out <<
							"Triangle vertex index #" << triangleVertexIndex << " (Shape vertex index : #" << shapeVertexIndex << "). " "\n"
							"Position:" << vertex.position() << ", "
							"Tangent:" << vertex.tangent() << ", "
							"Normal:" << vertex.normal() << ", "
							"Texture Coordinates:" << vertex.textureCoordinates();

						if ( !obj.m_vertexColors.empty() )
						{
							const auto shapeColorIndex = triangle.vertexColorIndex(triangleVertexIndex);

							out << ", Vertex Color:" << obj.m_vertexColors.at(shapeColorIndex);
						}

						out << "\n";
					}

					triangleIndex++;
				}

				return out;
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const Shape & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			/**
			 * @brief Declares a new edge.
			 * @param vertexIndexA The index in the vertices list of the first vertex.
			 * @param vertexIndexB The index in the vertices list of the second vertex.
			 * @return size_t
			 */
			size_t
			addEdge (size_t vertexIndexA, size_t vertexIndexB) noexcept
			{
				/* Checks for shared edge. */
				auto sharedIndex = std::numeric_limits< size_t >::max();

				size_t offset = 0;

				for ( const auto & edge : m_edges )
				{
					if ( edge.same(vertexIndexA, vertexIndexB) )
					{
						sharedIndex = offset;

						/* Checks if the edge is alone, otherwise it's an error. */
						if ( edge.isShared() )
						{
							return std::numeric_limits< size_t >::max();
						}

						break;
					}

					offset++;
				}

				/* Insert the new edge. */
				m_edges.emplace_back(vertexIndexA, vertexIndexB);

				const auto newEdgeIndex = m_edges.size();

				/* Link with the shared edge if it found. */
				if ( sharedIndex < std::numeric_limits< size_t >::max() )
				{
					/* Sets to new inserted edge the index of the shared edge found. */
					m_edges.back().setSharedIndex(sharedIndex);

					/* Save the index of the new edge to the shared edge found. */
					m_edges[sharedIndex].setSharedIndex(newEdgeIndex);
				}

				return newEdgeIndex;
			}

			/**
			 * @briefs Checks and computes the vertex element count and returns the size.
			 * @param normalType Set the normal format. Default none.
			 * @param textureCoordinatesType Set the texture coordinates format. Default none.
			 * @param vertexColorType Set the vertex color format. Default none.
			 * @param skeletalAnimationType Set vertex attributes for skeletal animation. Default none.
			 * @return size_t
			 */
			[[nodiscard]]
			static
			size_t
			getVertexElementCount (NormalType normalType, TextureCoordinatesType textureCoordinatesType, VertexColorType vertexColorType, SkeletalAnimationType skeletalAnimationType)
			{
				auto vertexElementCount = 3UL;

				switch ( normalType )
				{
					case NormalType::Normal :
						vertexElementCount += 3UL;
						break;

					case NormalType::TangentNormal :
						vertexElementCount += 6UL;
						break;

					case NormalType::TBNSpace :
						vertexElementCount += 9UL;
						break;

					default:
						break;
				}

				switch ( textureCoordinatesType )
				{
					case TextureCoordinatesType::UV :
						vertexElementCount += 2UL;
						break;

					case TextureCoordinatesType::UVW :
						vertexElementCount += 3UL;
						break;

					default:
						break;
				}

				switch ( vertexColorType )
				{
					case VertexColorType::Gray :
						vertexElementCount += 1UL;
						break;

					case VertexColorType::RGB :
						vertexElementCount += 3UL;
						break;

					case VertexColorType::RGBA :
						vertexElementCount += 4UL;
						break;

					default:
						break;
				}

				switch ( skeletalAnimationType )
				{
					case SkeletalAnimationType::Average3 :
						vertexElementCount += 3UL;
						break;

					case SkeletalAnimationType::Average4 :
						vertexElementCount += 4UL;
						break;

					case SkeletalAnimationType::Weighted3 :
						vertexElementCount += 6UL;
						break;

					case SkeletalAnimationType::Weighted4 :
						vertexElementCount += 8UL;
						break;

					case SkeletalAnimationType::None :
					default:
						break;
				}

				return vertexElementCount;
			}

			/**
			 * @brief Writes the first value from a vector to a vertex buffer at a specific offset.
			 * @tparam vec_dim_t The dimension of the vector.
			 * @tparam vec_data_t The precision of vertex attribute data.
			 * @param vector A reference to a vector.
			 * @param vertexBuffer A reference to the vertex buffer.
			 * @param offset A reference to an offset.
			 * @return void
			 */
			template< size_t vec_dim_t, typename vec_data_t >
			static
			void
			writeVector1ToBuffer (const Math::Vector< vec_dim_t, vec_data_t > & vector, std::vector< data_t > & vertexBuffer, size_t & offset) noexcept
			{
				vertexBuffer[offset++] = static_cast< data_t >(vector[Math::X]);
			}

			/**
			 * @brief Writes the 2 first values from a vector to a vertex buffer at a specific offset.
			 * @tparam vec_dim_t The dimension of the vector.
			 * @tparam vec_data_t The precision of vertex attribute data.
			 * @param vector A reference to a vector.
			 * @param vertexBuffer A reference to the vertex buffer.
			 * @param offset A reference to an offset.
			 * @return void
			 */
			template< size_t vec_dim_t, typename vec_data_t >
			static
			void
			writeVector2ToBuffer (const Math::Vector< vec_dim_t, vec_data_t > & vector, std::vector< data_t > & vertexBuffer, size_t & offset) noexcept requires ( vec_dim_t == 2UL || vec_dim_t == 3UL || vec_dim_t == 4UL )
			{
				vertexBuffer[offset++] = static_cast< data_t >(vector[Math::X]);
				vertexBuffer[offset++] = static_cast< data_t >(vector[Math::Y]);
			}

			/**
			 * @brief Writes the 3 first values from a vector to a vertex buffer at a specific offset.
			 * @tparam vec_dim_t The dimension of the vector.
			 * @tparam vec_data_t The precision of vertex attribute data.
			 * @param vector A reference to a vector.
			 * @param vertexBuffer A reference to the vertex buffer.
			 * @param offset A reference to an offset.
			 * @return void
			 */
			template< size_t vec_dim_t, typename vec_data_t >
			static
			void
			writeVector3ToBuffer (const Math::Vector< vec_dim_t, vec_data_t > & vector, std::vector< data_t > & vertexBuffer, size_t & offset) noexcept requires ( vec_dim_t == 3UL || vec_dim_t == 4UL )
			{
				vertexBuffer[offset++] = static_cast< data_t >(vector[Math::X]);
				vertexBuffer[offset++] = static_cast< data_t >(vector[Math::Y]);
				vertexBuffer[offset++] = static_cast< data_t >(vector[Math::Z]);
			}

			/**
			 * @brief Writes a vector 4 to a vertex buffer at a specific offset.
			 * @tparam vec_data_t The precision of vertex attribute data.
			 * @param vector A reference to a vector.
			 * @param vertexBuffer A reference to the vertex buffer.
			 * @param offset A reference to an offset.
			 * @return void
			 */
			template< typename vec_data_t >
			static
			void
			writeVector4ToBuffer (const Math::Vector< 4, vec_data_t > & vector, std::vector< data_t > & vertexBuffer, size_t & offset) noexcept
			{
				vertexBuffer[offset++] = static_cast< data_t >(vector[Math::X]);
				vertexBuffer[offset++] = static_cast< data_t >(vector[Math::Y]);
				vertexBuffer[offset++] = static_cast< data_t >(vector[Math::Z]);
				vertexBuffer[offset++] = static_cast< data_t >(vector[Math::W]);
			}

			/**
			 * @brief Writes the texture coordinates vertex attributes to a vertex buffer at a specific offset.
			 * @tparam buffer_t The precision of vertex attribute data.
			 * @param textureCoordinates A reference to a vector.
			 * @param size The element count wanted.
			 * @param vertexBuffer A reference to the vertex buffer.
			 * @param offset A reference to an offset.
			 * @return void
			 */
			template< typename buffer_t >
			static
			void
			writeTextureCoordinatesToVertexBuffer (const Math::Vector< 3, buffer_t > & textureCoordinates, size_t size, std::vector< buffer_t > & vertexBuffer, size_t & offset)
			{
				switch ( size )
				{
					case 2 :
						vertexBuffer[offset++] = static_cast< buffer_t >(textureCoordinates[Math::X]);
						vertexBuffer[offset++] = static_cast< buffer_t >(textureCoordinates[Math::Y]);
						break;

					case 3 :
						vertexBuffer[offset++] = static_cast< buffer_t >(textureCoordinates[Math::X]);
						vertexBuffer[offset++] = static_cast< buffer_t >(textureCoordinates[Math::Y]);
						vertexBuffer[offset++] = static_cast< buffer_t >(textureCoordinates[Math::Z]);
						break;

					case 4 :
						vertexBuffer[offset++] = static_cast< buffer_t >(textureCoordinates[Math::X]);
						vertexBuffer[offset++] = static_cast< buffer_t >(textureCoordinates[Math::Y]);
						vertexBuffer[offset++] = static_cast< buffer_t >(textureCoordinates[Math::Z]);
						vertexBuffer[offset++] = static_cast< buffer_t >(0);
						break;

					default:
						break;
				}
			}

			/**
			 * @brief Writes the color vertex attributes to a vertex buffer at a specific offset.
			 * @tparam buffer_t The precision of vertex attribute data.
			 * @param vertexColor A reference to a vector.
			 * @param size The element count wanted.
			 * @param vertexBuffer A reference to the vertex buffer.
			 * @param offset A reference to an offset.
			 * @return void
			 */
			template< typename buffer_t >
			static
			void
			writeColorToVertexBuffer (const Math::Vector< 4, buffer_t > & vertexColor, size_t size, std::vector< buffer_t > & vertexBuffer, size_t & offset)
			{
				switch ( size )
				{
					case 1 :
						vertexBuffer[offset++] = static_cast< buffer_t >(vertexColor[Math::R]);
						break;

					case 2 :
						vertexBuffer[offset++] = static_cast< buffer_t >(vertexColor[Math::R]);
						vertexBuffer[offset++] = static_cast< buffer_t >(vertexColor[Math::G]);
						break;

					case 3 :
						vertexBuffer[offset++] = static_cast< buffer_t >(vertexColor[Math::R]);
						vertexBuffer[offset++] = static_cast< buffer_t >(vertexColor[Math::G]);
						vertexBuffer[offset++] = static_cast< buffer_t >(vertexColor[Math::B]);
						break;

					case 4 :
						vertexBuffer[offset++] = static_cast< buffer_t >(vertexColor[Math::R]);
						vertexBuffer[offset++] = static_cast< buffer_t >(vertexColor[Math::G]);
						vertexBuffer[offset++] = static_cast< buffer_t >(vertexColor[Math::B]);
						vertexBuffer[offset++] = static_cast< buffer_t >(vertexColor[Math::A]);
						break;

					default:
						break;
				}
			}

			/* Flag names. */
			static constexpr auto TextureCoordinatesDeclared{0UL};
			static constexpr auto ComputeEdges{1UL};

			/* NOTE: first = offset, second = the number of vertices for this group. */
			std::vector< std::pair< size_t, size_t > > m_groups{1};
			std::vector< ShapeVertex< data_t > > m_vertices{};
			std::vector< Math::Vector< 4, data_t > > m_vertexColors{};
			std::vector< ShapeTriangle< data_t > > m_triangles{};
			std::vector< ShapeEdge > m_edges{};
			Math::Cuboid< data_t > m_boundingBox{};
			Math::Sphere< data_t > m_boundingSphere{};
			/* NOTE: This is the max distance between [0,0,0] and the farthest vertex.
			 * This is different from the fourth component of the centroid (m_boundingSphere). */
			data_t m_farthestDistance{0};
			std::array< bool, 8 > m_flags{
				false/*TextureCoordinatesDeclared*/,
				false/*ComputeEdges*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
