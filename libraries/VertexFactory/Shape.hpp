/*
 * Libraries/VertexFactory/Shape.hpp
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

/* C/C++ standard libraries */
#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>

/* Local inclusions for usages. */
#include "Path/File.hpp"
#include "Math/Cuboid.hpp"
#include "Math/Matrix.hpp"
#include "Math/Sphere.hpp"
#include "PixelFactory/Color.hpp"
#include "ShapeEdge.hpp"
#include "ShapeTriangle.hpp"
#include "ShapeVertex.hpp"
#include "TextureCoordinates.hpp"

namespace Libraries::VertexFactory
{
	// NOLINTBEGIN(readability-identifier-length, *-magic-numbers)
	/**
	 * @brief The shape class for defining a complete geometry.
	 * @tparam data_t The precision type of vertex data. Default float.
	 */
	template< typename data_t = float, std::enable_if_t< std::is_floating_point_v< data_t >, bool > = false >
	class Shape final
	{
		template< typename T, std::enable_if_t< std::is_floating_point_v< T >, bool > >
		friend class ShapeBuilder;

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
				m_radiusFromOrigin = 0;
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
			radiusFromOrigin () const noexcept
			{
				return m_radiusFromOrigin;
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
				return std::any_of(m_edges.cbegin(), m_edges.cend(), [] (const auto & edge) {
					return !edge.isShared();
				});
			}

			/**
			 * @brief Returns whether texture coordinates is available.
			 * @return bool
			 */
			[[nodiscard]]
			inline
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
			 * @return bool
			 */
			bool
			generateTextureCoordinates (data_t uScale = 1, data_t vScale = 1) noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry data is empty !" "\n";

					return false;
				}

				for ( const auto & triangle : m_triangles )
				{
					for ( size_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex )
					{
						auto & currentVertex = m_vertices[triangle.vertexIndex(vertexIndex)];

						auto textureCoordinates = TextureCoordinates::generateCubicCoordinates(currentVertex.position(), currentVertex.normal());
						textureCoordinates[Math::U] *= uScale;
						textureCoordinates[Math::V] *= vScale;

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
			computeTrianglesNormal () noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry data is empty !" "\n";

					return false;
				}

				for ( auto & triangle : m_triangles )
				{
					const auto & vertexA = m_vertices[triangle.vertexIndex(0)];
					const auto & vertexB = m_vertices[triangle.vertexIndex(1)];
					const auto & vertexC = m_vertices[triangle.vertexIndex(2)];

					/* Compute the surface normal. */
					const auto normal = Math::Vector< 3, data_t >::normal(
						vertexA.position(),
						vertexC.position(),
						vertexB.position()
					);

					triangle.setSurfaceNormal(normal);
				}

				return true;
			}

			/**
			 * @brief Computes tangent vector for every triangle.
			 * @note Requests valid texture coordinates.
			 * @return bool
			 */
			bool
			computeTrianglesTangent () noexcept
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

				for ( auto & triangle : m_triangles )
				{
					const auto & vertexA = m_vertices[triangle.vertexIndex(0)];
					const auto & vertexB = m_vertices[triangle.vertexIndex(1)];
					const auto & vertexC = m_vertices[triangle.vertexIndex(2)];

					/* Compute the surface tangent.
					 * NOTE: Points parameter are inverted from normal computation to follow OpenGL requirement. */
					const auto tangent = Math::Vector< 3, data_t >::tangent(
						vertexA.position(),
						vertexA.textureCoordinates(),
						vertexC.position(),
						vertexC.textureCoordinates(),
						vertexB.position(),
						vertexB.textureCoordinates()
					);

					triangle.setSurfaceTangent(tangent);
				}

				return true;
			}

			/**
			 * @brief Computes normal and tangent vectors for every triangle.
			 * @note Requests valid texture coordinates.
			 * @return bool
			 */
			bool
			computeTrianglesSpace () noexcept
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

				for ( auto & triangle : m_triangles )
				{
					const auto & vertexA = m_vertices[triangle.vertexIndex(0)];
					const auto & vertexB = m_vertices[triangle.vertexIndex(1)];
					const auto & vertexC = m_vertices[triangle.vertexIndex(2)];

					/* Compute the surface tangent.
					 * NOTE: Points parameter are inverted from normal computation to follow OpenGL requirement. */
					const auto tangent = Math::Vector< 3, data_t >::tangent(
						vertexA.position(),
						vertexA.textureCoordinates(),
						vertexC.position(),
						vertexC.textureCoordinates(),
						vertexB.position(),
						vertexB.textureCoordinates()
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
			 * @warning Geometry must have normal vectors computed for every triangles.
			 * @return bool
			 */
			bool
			computeVerticesNormal () noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry is empty !" "\n";

					return false;
				}

				const auto verticesCount = m_vertices.size();

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

#ifdef VERTEXFACTORY_DEBUG
					std::cout << "[DEBUG] Vertex space #" << ( currentVertexIndex + 1 ) << "/" << verticesCount << " computed !" "\n";
#endif
				}

				return true;
			}

			/**
			 * @brief Computes tangent vector for every vertex.
			 * @warning Geometry must have tangent vectors computed for every triangles.
			 * @return bool
			 */
			bool
			computeVerticesTangent () noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry is empty !" "\n";

					return false;
				}

				const auto verticesCount = m_vertices.size();

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

#ifdef VERTEXFACTORY_DEBUG
					std::cout << "[DEBUG] Vertex space #" << ( currentVertexIndex + 1 ) << "/" << verticesCount << " computed !" "\n";
#endif
				}

				return true;
			}

			/**
			 * @brief Computes normal and tangent vectors for every vertex.
			 * @warning Geometry must have normal and tangent vectors computed for every triangles.
			 * @return bool
			 */
			bool
			computeVerticesSpace () noexcept
			{
				if ( m_triangles.empty() || m_vertices.empty() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", geometry is empty !" "\n";

					return false;
				}

				const auto verticesCount = m_vertices.size();

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

#ifdef VERTEXFACTORY_DEBUG
					std::cout << "[DEBUG] Vertex space #" << ( currentVertexIndex + 1 ) << "/" << verticesCount << " computed !" "\n";
#endif
				}

				return true;
			}

			/**
			 * @brief Computes normal and tangent vectors for the whole surface.
			 * This is a main function that call triangles computation then vertices computation.
			 * @return bool
			 */
			bool
			computeSurfaceSpace () noexcept
			{
				if ( !this->computeTrianglesSpace() )
				{
					return false;
				}

				if ( !this->computeVerticesSpace() )
				{
					return false;
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
					if (vertexRef.position()[Math::Y] < bottom)
					{
						bottom = vertexRef.position()[Math::Y];
					}
				}

				this->transform(Math::Matrix< 4, data_t >::translation(0, -bottom, 0), updateProperties);
			}

			/**
			 * @brief Performs a geometry transformation with a Matrix 4x4.
			 * @param transform The transformation matrix.
			 * @param updateProperties Enable the shape properties update. Default true.
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

					/* We update every face index for vertices position. */
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
			 * @brief Flip the front-facing of every triangles.
			 * @return void
			 */
			void
			flipSurface () noexcept
			{
				for ( auto & triangle : m_triangles )
				{
					triangle.flip();
				}

				m_flags[ReverseTriangleWinding] = !m_flags[ReverseTriangleWinding];
			}

			/**
			 * @brief Flip the Y-Axis of every vertex attributes.
			 * @return void
			 */
			void
			flipYAxis () noexcept
			{
				for ( auto & vertexRef : m_vertices )
				{
					vertexRef.flipYAxis();
				}

				for ( auto & triangle : m_triangles )
				{
					triangle.flipYAxis();
				}
			}

			/**
			 * @brief Writes vertices data to a STL vector and returns vertex element count. Each vertex will be written uniquely
			 * with all vertex attributes to be used with an index buffer. Disabled attributes will
			 * removed from the vertex form, the attributes order will never change.
			 * @param destinationBuffer A reference to a floating point number vector.
			 * @param positionSize The position attribute size. This can be 2, 3 or 4.
			 * @param normalSize The TBN attribute size. This can be 0(disabled), 3 or 4.
			 * @param enableTangentSpace This will enable the full tangent space (TBN) instead of only the normal.
			 * @param textureCoordinatesSize The texture coordinates attribute size. This can be 0(disabled), 2 (2D), 3(3D) or 4(2x2D).
			 * @param vertexColorSize The vertex color attribute size. This can be 0(disabled), 1, 2, 3 or 4.
			 * @return size_t
			 */
			template< typename vertexType_t, std::enable_if_t< std::is_floating_point_v< vertexType_t >, bool > = false >
			size_t
			createVerticesBuffer (std::vector< vertexType_t > & destinationBuffer, size_t positionSize, size_t normalSize, bool enableTangentSpace, size_t textureCoordinatesSize, size_t vertexColorSize) const noexcept
			{
				/* NOTE: Keep track of vertex already used. */
				std::vector< size_t > indexDone{};
				indexDone.reserve(this->vertexCount());

				positionSize = std::clamp(positionSize, 2UL, 4UL);

				auto vertexElementCount = positionSize;

				if ( normalSize )
				{
					normalSize = std::clamp(normalSize, 3UL, 4UL);

					vertexElementCount += enableTangentSpace ? normalSize * 3 : normalSize;
				}

				if ( textureCoordinatesSize )
				{
					textureCoordinatesSize = std::clamp(textureCoordinatesSize, 2UL, 4UL);

					vertexElementCount += textureCoordinatesSize;
				}

				if ( vertexColorSize )
				{
					vertexColorSize = std::clamp(vertexColorSize, 1UL, 4UL);

					vertexElementCount += vertexColorSize;
				}

				/* NOTE: Resize the targeted buffer. */
				destinationBuffer.resize(m_vertices.size() * vertexElementCount);

				size_t offset = 0;

				for ( const auto & triangle : m_triangles )
				{
					for ( size_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex )
					{
						const auto positionIndex = triangle.vertexIndex(vertexIndex);

						if ( std::find(indexDone.cbegin(), indexDone.cend(), positionIndex) != indexDone.cend() )
						{
							continue;
						}

						const auto & vertexRef = m_vertices[positionIndex];

						/* Position */
						const auto & position = vertexRef.position();

						switch ( positionSize )
						{
							case 2 :
								destinationBuffer[offset++] = static_cast< vertexType_t >(position[Math::X]);
								destinationBuffer[offset++] = static_cast< vertexType_t >(position[Math::Y]);
								break;

							case 3 :
								destinationBuffer[offset++] = static_cast< vertexType_t >(position[Math::X]);
								destinationBuffer[offset++] = static_cast< vertexType_t >(position[Math::Y]);
								destinationBuffer[offset++] = static_cast< vertexType_t >(position[Math::Z]);
								break;

							case 4 :
								destinationBuffer[offset++] = static_cast< vertexType_t >(position[Math::X]);
								destinationBuffer[offset++] = static_cast< vertexType_t >(position[Math::Y]);
								destinationBuffer[offset++] = static_cast< vertexType_t >(position[Math::Z]);
								destinationBuffer[offset++] = static_cast< vertexType_t >(1);
								break;

							default:
								return 0;
						}

						/* Normal */
						if ( normalSize )
						{
							/* Tangent + Binormal. */
							if ( enableTangentSpace )
							{
								const auto & tangent = vertexRef.tangent();

								destinationBuffer[offset++] = static_cast< vertexType_t >(tangent[Math::X]);
								destinationBuffer[offset++] = static_cast< vertexType_t >(tangent[Math::Y]);
								destinationBuffer[offset++] = static_cast< vertexType_t >(tangent[Math::Z]);
								if ( normalSize > 3 )
								{
									destinationBuffer[offset++] = static_cast< vertexType_t >(0);
								}

								const auto binormal = vertexRef.binormal();

								destinationBuffer[offset++] = static_cast< vertexType_t >(binormal[Math::X]);
								destinationBuffer[offset++] = static_cast< vertexType_t >(binormal[Math::Y]);
								destinationBuffer[offset++] = static_cast< vertexType_t >(binormal[Math::Z]);
								if ( normalSize > 3 )
								{
									destinationBuffer[offset++] = static_cast< vertexType_t >(0);
								}
							}

							const auto & normal = vertexRef.normal();

							destinationBuffer[offset++] = static_cast< vertexType_t >(normal[Math::X]);
							destinationBuffer[offset++] = static_cast< vertexType_t >(normal[Math::Y]);
							destinationBuffer[offset++] = static_cast< vertexType_t >(normal[Math::Z]);
							if ( normalSize > 3 )
							{
								destinationBuffer[offset++] = static_cast< vertexType_t >(0);
							}
						}

						/* Texture Coordinates */
						if ( textureCoordinatesSize )
						{
							const auto & textureCoordinates = vertexRef.textureCoordinates();

							switch ( textureCoordinatesSize )
							{
								case 2 :
									destinationBuffer[offset++] = static_cast< vertexType_t >(textureCoordinates[Math::X]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(textureCoordinates[Math::Y]);
									break;

								case 3 :
									destinationBuffer[offset++] = static_cast< vertexType_t >(textureCoordinates[Math::X]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(textureCoordinates[Math::Y]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(0);
									break;

								case 4 :
									destinationBuffer[offset++] = static_cast< vertexType_t >(textureCoordinates[Math::X]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(textureCoordinates[Math::Y]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(0);
									destinationBuffer[offset++] = static_cast< vertexType_t >(0);
									break;

								default:
									break;
							}
						}

						/* Vertex Color */
						if ( vertexColorSize )
						{
							const auto & vertexColorRef = m_vertexColors[triangle.vertexColorIndex(vertexIndex)];

							switch ( vertexColorSize )
							{
								case 1 :
									destinationBuffer[offset++] = static_cast< vertexType_t >(vertexColorRef[Math::R]);
									break;

								case 2 :
									destinationBuffer[offset++] = static_cast< vertexType_t >(vertexColorRef[Math::R]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(vertexColorRef[Math::G]);
									break;

								case 3 :
									destinationBuffer[offset++] = static_cast< vertexType_t >(vertexColorRef[Math::R]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(vertexColorRef[Math::G]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(vertexColorRef[Math::B]);
									break;

								case 4 :
									destinationBuffer[offset++] = static_cast< vertexType_t >(vertexColorRef[Math::R]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(vertexColorRef[Math::G]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(vertexColorRef[Math::B]);
									destinationBuffer[offset++] = static_cast< vertexType_t >(vertexColorRef[Math::A]);
									break;

								default:
									break;
							}
						}

						indexDone.emplace_back(positionIndex);
					}
				}

				return vertexElementCount;
			}

			/**
			 * @brief Writes the order of rendering vertices to a vector.
			 * @param destinationBuffer A reference to a floating point number vector.
			 * @return size_t
			 */
			template< typename indexType_t, std::enable_if_t< std::is_integral_v< indexType_t >, bool > = false >
			size_t
			createIndicesBuffer (std::vector< indexType_t > & destinationBuffer) const noexcept
			{
				/* NOTE: Resize the targeted buffer. */
				destinationBuffer.resize(m_triangles.size() * 3);

				size_t offset = 0;

				/* NOTE: We use only the position indexes over the other attributes. */
				if ( m_flags[ReverseTriangleWinding] )
				{
					for ( const auto & triangle : m_triangles )
					{
						destinationBuffer[offset++] = static_cast< indexType_t >(triangle.vertexIndex(2));
						destinationBuffer[offset++] = static_cast< indexType_t >(triangle.vertexIndex(1));
						destinationBuffer[offset++] = static_cast< indexType_t >(triangle.vertexIndex(0));
					}
				}
				else
				{
					for ( const auto & triangle : m_triangles )
					{
						destinationBuffer[offset++] = static_cast< indexType_t >(triangle.vertexIndex(0));
						destinationBuffer[offset++] = static_cast< indexType_t >(triangle.vertexIndex(1));
						destinationBuffer[offset++] = static_cast< indexType_t >(triangle.vertexIndex(2));
					}
				}

				return destinationBuffer.size();
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
				for ( const auto & triangle : obj.m_triangles )
				{
					for ( size_t vertexIndex = 0; vertexIndex < 3; ++vertexIndex )
					{
						const auto & vertexRef = obj.m_vertices[triangle.vertexIndex(vertexIndex)];

						out <<
							"Vertex. "
							"Position:" << vertexRef.position() << ", "
							"Tangent:" << vertexRef.tangent() << ", "
							"Normal:" << vertexRef.normal() << ", "
							"Texture Coordinates:" << vertexRef.textureCoordinates() << ", "
							"Vertex Color:" << vertexRef.position() << ", "
							"Position:" << obj.m_vertexColors[triangle.vertexColorIndex(vertexIndex)] <<
							std::endl;
					}
				}

				return out;
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend
			std::string
			to_string (const Shape & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			/**
			 * @brief Declares a new group.
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
			 * @brief Declares a new vertex.
			 * @param position The position of the vertex.
			 * @return size_t The index of the new vertex.
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
			 * @param position The position of the vertex.
			 * @param normal The normal of the vertex.
			 * @param textureCoordinates The texture coordinates to that vertex.
			 * @return size_t The index of the new vertex.
			 */
			size_t
			addVertex (const Math::Vector< 3, data_t > & position, const Math::Vector< 3, data_t > & normal, const Math::Vector< 2, data_t > & textureCoordinates) noexcept
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
			 * @warning Should never be called outside the Geometry class.
			 * @param position The position of the vertex.
			 * @param normal The normal of the vertex.
			 * @param textureCoordinates The texture coordinates to that vertex.
			 * @return size_t The index of the new vertex.
			 */
			size_t
			saveVertex (const Math::Vector< 3, data_t > & position, const Math::Vector< 3, data_t > & normal = {}, const Math::Vector< 2, data_t > & textureCoordinates = {}) noexcept
			{
				m_vertices.emplace_back(position, normal, textureCoordinates);

				m_flags[TextureCoordinatesDeclared] = true;

				return m_vertices.size() - 1;
			}

			/**
			 * @brief Saves a new vertex color.
			 * @warning  Should never be called outside the Geometry class.
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

				auto newEdgeIndex = m_edges.size();

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
			 * @brief Recomputes the centroid and the bounding box.
			 * @return void
			 */
			void
			updateProperties () noexcept
			{
				/* Reset properties. */
				m_boundingBox.reset();
				m_radiusFromOrigin = 0;

				Math::Vector< 3, data_t > center{};

				for ( const auto & vertexRef : m_vertices )
				{
					center += vertexRef.position();

					const auto length = vertexRef.position().length();

					if ( length > m_radiusFromOrigin )
					{
						m_radiusFromOrigin = length;
					}
				}

				center /= m_vertices.size();

				data_t maxDistance = 0;

				for ( const auto & vertexRef : m_vertices )
				{
					const auto distance = Math::Vector< 3, data_t >::distance(center, vertexRef.position());

					if ( distance > maxDistance )
					{
						maxDistance = distance;
					}

					m_boundingBox.merge(vertexRef.position());
				}

				m_boundingSphere.setRadius(m_boundingBox.highestLength() * 0.5F);
				m_boundingSphere.setPosition(center);
			}

			/* Flag names. */
			static constexpr auto TextureCoordinatesDeclared = 0UL;
			static constexpr auto ReverseTriangleWinding = 1UL;

			std::vector< ShapeTriangle< data_t > > m_triangles{};
			std::vector< ShapeEdge > m_edges{};
			std::vector< ShapeVertex< data_t > > m_vertices{};
			std::vector< Math::Vector< 4, data_t > > m_vertexColors{};
			/* NOTE: first = offset, second = the number of vertices for this group. */
			std::vector< std::pair< size_t, size_t > > m_groups{1};
			Math::Cuboid< data_t > m_boundingBox{};
			Math::Sphere< data_t > m_boundingSphere{};
			/* NOTE: This is the max distance between [0,0,0] and the farthest vertex.
			 * This is different from the fourth component of the centroid (m_boundingSphere). */
			data_t m_radiusFromOrigin{0};
			std::array< bool, 8 > m_flags{
				false/*TextureCoordinatesDeclared*/,
				false/*ReverseTriangleWinding*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
	// NOLINTEND(readability-identifier-length, *-magic-numbers)
}
