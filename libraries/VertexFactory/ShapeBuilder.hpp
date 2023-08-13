/*
 * Libraries/VertexFactory/ShapeBuilder.hpp
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
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <vector>

/* Local inclusions */
#include "Shape.hpp"
#include "ShapeBuilderOptions.hpp"

namespace Libraries::VertexFactory
{
	/**
	 * @brief The triangle construction mode enumeration.
	 */
	enum class ConstructionMode
	{
		None,
		Triangles,
		TriangleStrip,
		TriangleFan
	};

	/**
	 * @brief The vertex attributes feeding mode enumeration.
	 */
	enum class FeedingMode
	{
		None,
		Position,
		PositionTextureCoordinate,
		PositionNormal,
		PositionVertexColor,
		PositionTextureCoordinateNormal,
		PositionTextureCoordinateVertexColor,
		PositionNormalVertexColor,
		All
	};

	/**
	 * @brief The shape builder can build geometry
	 * by providing vertex in an OpenGL direct mode
	 * way or build predefined parametric geometries.
	 * @tparam type_t The type of data. Default float.
	 */
	template< typename type_t = float, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	class ShapeBuilder final
	{
		public:

			/**
			 * @brief Construct the shape builder.
			 * @param options A reference to initial builder options. Default none.
			 */
			explicit
			ShapeBuilder (const ShapeBuilderOptions< type_t > & options = {}) noexcept
				: m_options(options)
			{

			}

			/**
			 * @brief Constructs the shape builder with a targeted destination.
			 * @param destinationShape A reference to a shape to build.
			 * @param options A reference to initial builder options. Default none.
			 */
			explicit
			ShapeBuilder (Shape< type_t > & destinationShape, const ShapeBuilderOptions< type_t > & options = {}) noexcept
				: m_destinationShape(&destinationShape), m_options(options)
			{

			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ShapeBuilder (const ShapeBuilder & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ShapeBuilder (ShapeBuilder && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			ShapeBuilder & operator= (const ShapeBuilder & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			ShapeBuilder & operator= (ShapeBuilder && copy) noexcept = delete;

			/**
			 * @brief Destructs the shape assembler.
			 */
			~ShapeBuilder () = default;

			/**
			 * @brief Changes the destination shape.
			 * @param destinationShape A reference to a shape to build.
			 * @return void
			 */
			void
			setDestinationShape (Shape< type_t > & destinationShape) noexcept
			{
				if ( m_constructionMode != ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] You can't set an other Geometry while constructing !" "\n";

					return;
				}

				this->reset();

				m_destinationShape = &destinationShape;
			}

			/**
			 * @brief Returns a reference to options to parametrize the build.
			 * @return ShapeBuilderOptions< type_t > &
			 */
			[[nodiscard]]
			ShapeBuilderOptions< type_t > &
			options () noexcept
			{
				return m_options;
			}

			/**
			 * @brief Begins the shape construction.
			 * @param constructionMode The primitive type for construction. Default Triangles.
			 * @return void
			 */
			void
			beginConstruction (ConstructionMode constructionMode = ConstructionMode::Triangles) noexcept
			{
				if ( m_constructionMode != ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] A construction is already begun !" "\n";

					return;
				}

				if ( m_destinationShape == nullptr )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] Unable to begin a construction on a null Geometry !" "\n";

					return;
				}

				/* Reset the current triangle building from the builder. */
				{
					this->resetCurrentTriangle();

					m_constructionMode = constructionMode;
					m_feedingMode = FeedingMode::None;
				}

#ifdef VERTEXFACTORY_DEBUG
				std::cout << __PRETTY_FUNCTION__ << ", ready for construction ... " "\n";
#endif
			}

			/**
			 * @brief Declares a new group in the geometry.
			 * @return void
			 */
			void
			newGroup () noexcept
			{
				if ( m_constructionMode == ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] Builder is not in construction mode !" "\n";

					return;
				}

				this->resetCurrentTriangle();

				m_destinationShape->newGroup();
			}

			/**
			 * @brief Declares a new vertex in the current group of the geometry.
			 * @param position A reference to a vector 3.
			 * @return void
			 */
			void
			newVertex (const Math::Vector< 3, type_t > & position) noexcept
			{
				m_feedingMode = FeedingMode::Position;

				m_triangleVertices[m_triangleVertexIndex] = position;

				if ( m_options.isGlobalVertexColorEnabled() )
				{
					m_triangleVertexColors[m_triangleVertexIndex] = m_options.globalVertexColor();
				}

				if ( m_options.isVertexColorGenerationEnabled() )
				{
					m_triangleVertexColors[m_triangleVertexIndex] = Math::Vector< 4, type_t >{position.normalized(), 1};
				}
				else
				{
					m_triangleVertexColors[m_triangleVertexIndex] = Math::Vector< 4, type_t >{1, 1, 1, 1}; // White
				}

				if ( m_options.isGlobalNormalEnabled() )
				{
					m_triangleTextureCoordinates[m_triangleVertexIndex] = TextureCoordinates::generateCubicCoordinates(position, m_options.globalNormal());
					m_triangleNormals[m_triangleVertexIndex] = m_options.globalNormal();
				}
				else
				{
					m_triangleTextureCoordinates[m_triangleVertexIndex] = TextureCoordinates::generateCubicCoordinates(position, Math::Vector< 3, type_t >::positiveZ());
				}

				this->newVertexAdded();
			}

			/**
			 * @brief Declares a new vertex in the current group of the geometry.
			 * @param position A reference to a vector 3.
			 * @param textureCoordinate A reference to a vector 2.
			 * @return void
			 */
			void
			newVertex (const Math::Vector< 3, type_t > & position, const Math::Vector< 2, type_t > & textureCoordinate) noexcept
			{
				if ( m_constructionMode == ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] There is no construction !" "\n";

					return;
				}

				m_feedingMode = FeedingMode::PositionTextureCoordinate;

				m_triangleVertices[m_triangleVertexIndex] = position;
				m_triangleTextureCoordinates[m_triangleVertexIndex] = textureCoordinate;

				if ( m_options.isGlobalVertexColorEnabled() )
				{
					m_triangleVertexColors[m_triangleVertexIndex] = m_options.globalVertexColor();
				}

				if ( m_options.isVertexColorGenerationEnabled() )
				{
					m_triangleVertexColors[m_triangleVertexIndex] = Math::Vector< 4, type_t >{position.normalized(), 1};
				}
				else
				{
					m_triangleVertexColors[m_triangleVertexIndex] = Math::Vector< 4, type_t >{1, 1, 1, 1}; // White
				}

				if ( m_options.isGlobalNormalEnabled() )
				{
					m_triangleNormals[m_triangleVertexIndex] = m_options.globalNormal();
				}

				this->newVertexAdded();
			}

			/**
			 * @brief Declares a new vertex in the current group of the geometry.
			 * @param position A reference to a vector 3.
			 * @param normal A reference to a vector 3.
			 * @return void
			 */
			void
			newVertex (const Math::Vector< 3, type_t > & position, const Math::Vector< 3, type_t > & normal) noexcept
			{
				if ( m_constructionMode == ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] There is no construction !" "\n";

					return;
				}

				m_feedingMode = FeedingMode::PositionNormal;

				m_triangleVertices[m_triangleVertexIndex] = position;
				m_triangleTextureCoordinates[m_triangleVertexIndex] = TextureCoordinates::generateCubicCoordinates(position, normal);

				if ( m_options.isGlobalVertexColorEnabled() )
				{
					m_triangleVertexColors[m_triangleVertexIndex] = m_options.globalVertexColor();
				}

				if ( m_options.isVertexColorGenerationEnabled() )
				{
					m_triangleVertexColors[m_triangleVertexIndex] = Math::Vector< 4, type_t >{position.normalized(), 1};
				}
				else
				{
					m_triangleVertexColors[m_triangleVertexIndex] = Math::Vector< 4, type_t >{1, 1, 1, 1}; // White
				}

				m_triangleNormals[m_triangleVertexIndex] = normal;

				/* NOTE: We are providing normals. */
				m_options.enableNormalGeneration(false);

				this->newVertexAdded();
			}

			/**
			 * @brief Declares a new vertex in the current group of the geometry.
			 * @param position A reference to a vector 3.
			 * @param vertexColor A reference to a vector 4.
			 * @return void
			 */
			void
			newVertex (const Math::Vector< 3, type_t > & position, const Math::Vector< 4, type_t > & vertexColor) noexcept
			{
				if ( m_constructionMode == ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] There is no construction !" "\n";

					return;
				}

				m_feedingMode = FeedingMode::PositionVertexColor;

				m_triangleVertices[m_triangleVertexIndex] = position;
				m_triangleVertexColors[m_triangleVertexIndex] = vertexColor;

				if ( m_options.isGlobalNormalEnabled() )
				{
					m_triangleTextureCoordinates[m_triangleVertexIndex] = TextureCoordinates::generateCubicCoordinates(position, m_options.globalNormal());
					m_triangleNormals[m_triangleVertexIndex] = m_options.globalNormal();
				}
				else
				{
					m_triangleTextureCoordinates[m_triangleVertexIndex] = TextureCoordinates::generateCubicCoordinates(position, Math::Vector< 3, type_t >::positiveZ());
				}

				this->newVertexAdded();
			}

			/**
			 * @brief Declares a new vertex in the current group of the geometry.
			 * @param position A reference to a vector 3.
			 * @param textureCoordinate A reference to a vector 2.
			 * @param normal A reference to a vector 3.
			 * @return void
			 */
			void
			newVertex (const Math::Vector< 3, type_t > & position, const Math::Vector< 2, type_t > & textureCoordinate, const Math::Vector< 3, type_t > & normal) noexcept
			{
				if ( m_constructionMode == ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] There is no construction !" "\n";

					return;
				}

				m_feedingMode = FeedingMode::PositionTextureCoordinateNormal;

				m_triangleVertices[m_triangleVertexIndex] = position;
				m_triangleTextureCoordinates[m_triangleVertexIndex] = textureCoordinate;

				if ( m_options.isGlobalVertexColorEnabled() )
				{
					m_triangleVertexColors[m_triangleVertexIndex] = m_options.globalVertexColor();
				}

				if ( m_options.isVertexColorGenerationEnabled() )
				{
					m_triangleVertexColors[m_triangleVertexIndex] = Math::Vector< 4, type_t >{position.normalized(), 1};
				}
				else
				{
					m_triangleVertexColors[m_triangleVertexIndex] = Math::Vector< 4, type_t >{1, 1, 1, 1}; // White
				}

				m_triangleNormals[m_triangleVertexIndex] = normal;

				/* NOTE: We are providing normals. */
				m_options.enableNormalGeneration(false);

				this->newVertexAdded();
			}

			/**
			 * @brief Declares a new vertex in the current group of the geometry.
			 * @param position A reference to a vector 3.
			 * @param textureCoordinate A reference to a vector 2.
			 * @param vertexColor A reference to a vector 4.
			 * @return void
			 */
			void
			newVertex (const Math::Vector< 3, type_t > & position, const Math::Vector< 2, type_t > & textureCoordinate, const Math::Vector< 4, type_t > & vertexColor) noexcept
			{
				if ( m_constructionMode == ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] There is no construction !" "\n";

					return;
				}

				m_feedingMode = FeedingMode::PositionTextureCoordinateVertexColor;

				m_triangleVertices[m_triangleVertexIndex] = position;
				m_triangleTextureCoordinates[m_triangleVertexIndex] = textureCoordinate;
				m_triangleVertexColors[m_triangleVertexIndex] = vertexColor;

				if ( m_options.isGlobalNormalEnabled() )
				{
					m_triangleNormals[m_triangleVertexIndex] = m_options.globalNormal();
				}

				this->newVertexAdded();
			}

			/**
			 * @brief Declares a new vertex in the current group of the geometry.
			 * @param position A reference to a vector 3.
			 * @param normal A reference to a vector 3.
			 * @param vertexColor A reference to a vector 4.
			 * @return void
			 */
			void
			newVertex (const Math::Vector< 3, type_t > & position, const Math::Vector< 3, type_t > & normal, const Math::Vector< 4, type_t > & vertexColor) noexcept
			{
				if ( m_constructionMode == ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] There is no construction !" "\n";

					return;
				}

				m_feedingMode = FeedingMode::PositionNormalVertexColor;

				m_triangleVertices[m_triangleVertexIndex] = position;
				m_triangleTextureCoordinates[m_triangleVertexIndex] = TextureCoordinates::generateCubicCoordinates(position, normal);
				m_triangleVertexColors[m_triangleVertexIndex] = vertexColor;
				m_triangleNormals[m_triangleVertexIndex] = normal;

				/* NOTE: We are providing normals. */
				m_options.enableNormalGeneration(false);

				this->newVertexAdded();
			}

			/**
			 * @brief Declares a new vertex in the current group of the geometry.
			 * @param position A reference to a vector 3.
			 * @param textureCoordinate A reference to a vector 2.
			 * @param normal A reference to a vector 3.
			 * @param vertexColor A reference to a vector 4.
			 * @return void
			 */
			void
			newVertex (const Math::Vector< 3, type_t > & position, const Math::Vector< 2, type_t > & textureCoordinate, const Math::Vector< 3, type_t > & normal, const Math::Vector< 4, type_t > & vertexColor) noexcept
			{
				if ( m_constructionMode == ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] There is no construction !" "\n";

					return;
				}

				m_feedingMode = FeedingMode::All;

				m_triangleVertices[m_triangleVertexIndex] = position;
				m_triangleTextureCoordinates[m_triangleVertexIndex] = textureCoordinate;
				m_triangleVertexColors[m_triangleVertexIndex] = vertexColor;
				m_triangleNormals[m_triangleVertexIndex] = normal;

				/* NOTE: We are providing normals. */
				m_options.enableNormalGeneration(false);

				this->newVertexAdded();
			}

			/**
			 * @brief Ends the construction of the shape.
			 * @return void
			 */
			void
			endConstruction () noexcept
			{
				if ( m_constructionMode == ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] There was no construction to end !" "\n";

					return;
				}

				/* Move the whole geometry above Y- axis, if requested. */
				if ( m_options.isCenteredAtBottom()  )
				{
					m_destinationShape->setCenterAtBottom(false);
				}

				/* Flip the whole geometry. */
				if ( m_options.isGeometryFlippingEnabled() )
				{
					m_destinationShape->flipSurface();
				}

				/* Should never happen, but we absolutely
				 * need valid texture coordinates. */
				if ( m_triangleTextureCoordinates.empty() )
				{
#ifdef DEBUG_VERTEX_FACTORY
					std::cout << "[" << __PRETTY_FUNCTION__ << "] Generating texture coordinates !" "\n";
#endif
					const auto & textureCoordinatesMultiplier = m_options.textureCoordinatesMultiplier();

					m_destinationShape->generateTextureCoordinates(textureCoordinatesMultiplier[Math::X], textureCoordinatesMultiplier[Math::Y]);
				}

				/* Compute normal and tangent of every triangle. */
				m_destinationShape->computeTrianglesSpace();

				/* If no normal provided by vertex,
				 * we compute it from triangle normal with tangent.
				 * Otherwise, we compute only the tangent vector for every vertex. */
				if ( m_options.isNormalGenerationEnabled() )
				{
					m_destinationShape->computeVerticesSpace();
				}
				else
				{
					m_destinationShape->computeVerticesTangent();
				}

				/* This will update the bounding box, sphere and centroid. */
				m_destinationShape->updateProperties();

				/* We reset construction variable. */
				{
					this->resetCurrentTriangle();

					m_constructionMode = ConstructionMode::None;
					m_feedingMode = FeedingMode::None;
				}

#ifdef VERTEXFACTORY_DEBUG
				std::cout << "[DEBUG] " << __PRETTY_FUNCTION__ << ", construction finished !" "\n";
#endif
			}

			/**
			 * @brief Returns a list of distances between vertices.
			 * @param vertices A list of vertex.
			 * @return std::vector< type_t >
			 */
			[[nodiscard]]
			static
			std::vector< type_t >
			getDistances (const std::vector< std::vector< ShapeVertex< type_t > > > & vertices) noexcept
			{
				if ( vertices.empty() )
				{
					return {};
				}

				const auto verticesCount = vertices.size();

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
						distances.emplace_back(Math::Vector<3, type_t>::distance(vertices[index].position(), vertices[subIndex].position()));
					}
				}

				return distances;
			}

			/**
			 * @brief Returns minimum, maximum and the average distances between vertices.
			 * @param vertices A list of vertex.
			 * @return std::array< type_t, 3 >
			 */
			[[nodiscard]]
			static
			std::array< type_t, 3 >
			getDistancesAggregate (const std::vector< std::vector< ShapeVertex< type_t > > > & vertices) noexcept
			{
				const auto distances = ShapeBuilder::getDistances(vertices);

				return {
					*std::min_element(distances.cbegin(), distances.cend()),
					*std::max_element(distances.cbegin(), distances.cend()),
					std::accumulate(distances.cbegin(), distances.cend(), 0.0F) / distances.size()
				};
			}

			/**
			 * @brief Resets the current triangle.
			 * @return void
			 */
			void
			resetCurrentTriangle () noexcept
			{
				m_triangleVertexIndex = 0;
				m_triangleCount = 0;
			}

			/**
			 * @brief Resets the construction.
			 * @return void
			 */
			void
			reset () noexcept
			{
				if ( m_constructionMode != ConstructionMode::None )
				{
					this->endConstruction();

					return;
				}

				/* Reset building data. */
				m_destinationShape = nullptr;

				this->resetCurrentTriangle();

				/* Reset building parameters. */
				m_constructionMode = ConstructionMode::None;
				m_feedingMode = FeedingMode::None;
				m_options.reset();
			}

		private:

			/**
			 * @brief Event when a new vertex is added.
			 * @return void
			 */
			void
			newVertexAdded () noexcept
			{
				m_triangleVertexIndex++;

				/* NOTE: If we got 3 vertices, we can create a triangle. */
				if ( m_triangleVertexIndex >= 3 )
				{
					/* Creates the triangle in the shape. */
					this->createTriangle();

					/* Prepare the next triangle following the mode of construction. */
					switch ( m_constructionMode )
					{
						case ConstructionMode::Triangles :
							m_triangleVertexIndex = 0;
							break;

						case ConstructionMode::TriangleStrip :
							m_triangleVertexIndex = 2;

							if ( (m_triangleCount % 2) > 0 )
							{
								m_triangleVertices[0] = m_triangleVertices[2];
								m_triangleTextureCoordinates[0] = m_triangleTextureCoordinates[2];
								m_triangleVertexColors[0] = m_triangleVertexColors[2];
								m_triangleNormals[0] = m_triangleNormals[2];
							}
							else
							{
								m_triangleVertices[1] = m_triangleVertices[2];
								m_triangleTextureCoordinates[1] = m_triangleTextureCoordinates[2];
								m_triangleVertexColors[1] = m_triangleVertexColors[2];
								m_triangleNormals[1] = m_triangleNormals[2];
							}
							break;

						case ConstructionMode::TriangleFan :
							m_triangleVertexIndex = 2;

							/* FIXME: Check this. */
							m_triangleVertices[1] = m_triangleVertices[2];
							m_triangleTextureCoordinates[1] = m_triangleTextureCoordinates[2];
							m_triangleVertexColors[1] = m_triangleVertexColors[2];
							m_triangleNormals[1] = m_triangleNormals[2];
							break;

						default:
							std::cerr << __PRETTY_FUNCTION__ << ", invalid usage !" "\n";
							break;
					}
				}
			}

			/**
			 * @brief Creates a triangle when sufficient data are available to build one.
			 * @return void
			 */
			void
			createTriangle () noexcept
			{
				ShapeTriangle< type_t > triangle{};

				const auto & textureCoordinatesMultiplier = m_options.textureCoordinatesMultiplier();

				#pragma omp simd
				for ( size_t vertexIndex = 0; vertexIndex < 3; vertexIndex++ )
				{
					size_t attributeIndex = 0;

					/* Vertex position, normal and texCoords. */
					{
						const auto textureCoordinates = Math::Vector< 2, type_t >(
							m_triangleTextureCoordinates[vertexIndex][Math::X] * textureCoordinatesMultiplier[Math::X],
							m_triangleTextureCoordinates[vertexIndex][Math::Y] * textureCoordinatesMultiplier[Math::Y]
						);

						if (m_options.dataEconomyEnabled() )
						{
							attributeIndex = m_destinationShape->addVertex(m_triangleVertices[vertexIndex], m_triangleNormals[vertexIndex], textureCoordinates);
						}
						else
						{
							attributeIndex = m_destinationShape->saveVertex(m_triangleVertices[vertexIndex], m_triangleNormals[vertexIndex], textureCoordinates);
						}

						triangle.setVertexIndex(vertexIndex, attributeIndex);
					}

					/* Vertex color. */
					{
						if (m_options.dataEconomyEnabled() )
						{
							attributeIndex = m_destinationShape->addVertexColor(m_triangleVertexColors[vertexIndex]);
						}
						else
						{
							attributeIndex = m_destinationShape->saveVertexColor(m_triangleVertexColors[vertexIndex]);
						}

						triangle.setVertexColorIndex(vertexIndex, attributeIndex);
					}
				}

				m_destinationShape->addTriangle(triangle);

				m_triangleCount++;
			}

			Shape< type_t > * m_destinationShape{nullptr};
			std::array< Math::Vector< 3, type_t >, 3 > m_triangleVertices{};
			std::array< Math::Vector< 2, type_t >, 3 > m_triangleTextureCoordinates{};
			std::array< Math::Vector< 4, type_t >, 3 > m_triangleVertexColors{};
			std::array< Math::Vector< 3, type_t >, 3 > m_triangleNormals{};
			size_t m_triangleVertexIndex{0};
			size_t m_triangleCount{0};
			ConstructionMode m_constructionMode{ConstructionMode::None};
			FeedingMode m_feedingMode{FeedingMode::None};
			ShapeBuilderOptions< type_t > m_options{};
	};
}
