/*
 * src/Libraries/VertexFactory/ShapeBuilder.hpp
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

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <array>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <vector>

/* Local inclusions. */
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
	 * @brief The shape builder construct a geometry shape by providing the structure by triangles.
	 * @tparam float_t The type of data. Default float.
	 */
	template< typename float_t = float >
	requires (std::is_floating_point_v< float_t >)
	class ShapeBuilder final
	{
		public:

			/**
			 * @brief Constructs a default shape builder.
			 * @param options A reference to initial builder options. Default none.
			 */
			explicit
			ShapeBuilder (const ShapeBuilderOptions< float_t > & options = {}) noexcept
				: m_options(options)
			{

			}

			/**
			 * @brief Constructs the shape builder with a targeted destination.
			 * @param destinationShape A reference to a shape to build.
			 * @param options A reference to initial builder options. Default none.
			 */
			explicit
			ShapeBuilder (Shape< float_t > & destinationShape, const ShapeBuilderOptions< float_t > & options = {}) noexcept
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
			setDestinationShape (Shape< float_t > & destinationShape) noexcept
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
			ShapeBuilderOptions< float_t > &
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
				}

#ifdef EMERAUDE_DEBUG_VERTEX_FACTORY
				std::cout << "[DEBUG:VERTEX_FACTORY] Ready for construction ... " "\n";
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
			 * @brief Creates a new vertex.
			 * @param position A reference to vector.
			 * @return void
			 */
			void
			setPosition (const Math::Vector< 3, float_t > & position) noexcept
			{
				m_triangleVertices[m_triangleVertexIndex] = position;
				m_declaredAttributes[PositionDeclared] = true;
			}

			void
			setPosition (float_t x, float_t y, float_t z) noexcept
			{
				m_triangleVertices[m_triangleVertexIndex][Math::X] = x;
				m_triangleVertices[m_triangleVertexIndex][Math::Y] = y;
				m_triangleVertices[m_triangleVertexIndex][Math::Z] = z;
				m_declaredAttributes[PositionDeclared] = true;
			}

			void
			setNormal (const Math::Vector< 3, float_t > & normal) noexcept
			{
				m_triangleNormals[m_triangleVertexIndex] = normal;
				m_declaredAttributes[NormalDeclared] = true;
			}

			void
			setNormal (float_t x, float_t y, float_t z) noexcept
			{
				m_triangleNormals[m_triangleVertexIndex][Math::X] = x;
				m_triangleNormals[m_triangleVertexIndex][Math::Y] = y;
				m_triangleNormals[m_triangleVertexIndex][Math::Z] = z;
				m_declaredAttributes[NormalDeclared] = true;
			}

			void
			setTextureCoordinates (const Math::Vector< 3, float_t > & textureCoordinates) noexcept
			{
				m_triangleTextureCoordinates[m_triangleVertexIndex] = textureCoordinates;
				m_declaredAttributes[TextureCoordinatesDeclared] = true;
			}

			void
			setTextureCoordinates (float_t u, float_t v, float_t w = 0) noexcept
			{
				m_triangleTextureCoordinates[m_triangleVertexIndex][Math::X] = u;
				m_triangleTextureCoordinates[m_triangleVertexIndex][Math::Y] = v;
				m_triangleTextureCoordinates[m_triangleVertexIndex][Math::Z] = w;
				m_declaredAttributes[TextureCoordinatesDeclared] = true;
			}

			void
			setVertexColor (const Math::Vector< 4, float_t > & vertexColor) noexcept
			{
				m_triangleVertexColors[m_triangleVertexIndex] = vertexColor;
				m_declaredAttributes[VertexColorDeclared] = true;
			}

			void
			setVertexColor (const PixelFactory::Color< float_t > & vertexColor) noexcept
			{
				m_triangleVertexColors[m_triangleVertexIndex][Math::X] = vertexColor.red();
				m_triangleVertexColors[m_triangleVertexIndex][Math::Y] = vertexColor.green();
				m_triangleVertexColors[m_triangleVertexIndex][Math::Z] = vertexColor.blue();
				m_triangleVertexColors[m_triangleVertexIndex][Math::W] = vertexColor.alpha();
				m_declaredAttributes[VertexColorDeclared] = true;
			}

			void
			setVertexColor (float_t red, float_t green, float_t blue, float_t alpha = 1) noexcept
			{
				m_triangleVertexColors[m_triangleVertexIndex][Math::X] = red;
				m_triangleVertexColors[m_triangleVertexIndex][Math::Y] = green;
				m_triangleVertexColors[m_triangleVertexIndex][Math::Z] = blue;
				m_triangleVertexColors[m_triangleVertexIndex][Math::W] = alpha;
				m_declaredAttributes[VertexColorDeclared] = true;
			}

			void
			setInfluences (const Math::Vector< 4, int32_t > & influences) noexcept
			{
				//m_triangleVertexColors[m_triangleVertexIndex] = influences;
				m_declaredAttributes[InfluencesDeclared] = true;
			}

			void
			setWeights (const Math::Vector< 4, float_t > & weights) noexcept
			{
				//m_triangleVertexColors[m_triangleVertexIndex] = weights;
				m_declaredAttributes[WeightsDeclared] = true;
			}

			bool
			newVertex () noexcept
			{
				if ( m_constructionMode == ConstructionMode::None )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] There is no construction !" "\n";

					return false;
				}

				if ( !m_declaredAttributes[PositionDeclared] )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] The position attribute is not declared for this vertex !" "\n";

					return false;
				}

				if ( m_options.isNormalsEnabled() && !this->checkNormal() )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] The normal attribute is not declared for this vertex !" "\n";

					return false;
				}

				if ( m_options.isTextureCoordinatesEnabled() && !this->checkTextureCoordinates() )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] The texture coordinates attribute is not declared for this vertex !" "\n";

					return false;
				}

				if ( m_options.isVertexColorsEnabled() && !this->checkVertexColor() )
				{
					std::cerr << "[" << __PRETTY_FUNCTION__ << "] The vertex color attribute is not declared for this vertex !" "\n";

					return false;
				}

				this->newVertexAdded();

				return true;
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

				/* NOTE: Should never happen, but we absolutely
				 * need valid texture coordinates. */
				if ( m_triangleTextureCoordinates.empty() )
				{
					const auto & textureCoordinatesMultiplier = m_options.textureCoordinatesMultiplier();

#ifdef EMERAUDE_DEBUG_VERTEX_FACTORY
					std::cout << "[DEBUG:VERTEX_FACTORY] Generating texture coordinates !" "\n";
#endif

					m_destinationShape->generateTextureCoordinates(textureCoordinatesMultiplier[Math::X], textureCoordinatesMultiplier[Math::Y]);
				}

				/* Compute normal and tangent of every triangle.
				 * NOTE: If no normals were provided by vertex, we will compute it from triangle.
				 * Otherwise, we compute only the tangent vector for every vertex. */
				if ( m_options.isNormalsGenerationEnabled() )
				{
					/* NOTE: To work properly, the shape should have texture coordinates. */
					m_destinationShape->computeTriangleTBNSpace();

					m_destinationShape->computeVertexTBNSpace();
				}
				else
				{
					/* NOTE: To work properly, the shape should have texture coordinates. */
					m_destinationShape->computeTriangleTangent();

					m_destinationShape->computeVertexTangent();
				}

				/* NOTE: If asked with generation parameters, we flip the whole geometry. */
				if ( m_options.isGeometryFlippingEnabled() )
				{
#ifdef EMERAUDE_DEBUG_VERTEX_FACTORY
					std::cout << "[DEBUG:VERTEX_FACTORY] Flipping the shape !" "\n";
#endif
					m_destinationShape->flipSurface();
				}

				/* This will processLogics the bounding box, sphere and centroid. */
				m_destinationShape->updateProperties();

				/* We reset construction variable. */
				{
					this->resetCurrentTriangle();

					m_constructionMode = ConstructionMode::None;
				}

#ifdef EMERAUDE_DEBUG_VERTEX_FACTORY
				std::cout << "[DEBUG:VERTEX_FACTORY] Construction finished !" "\n";
#endif
			}

			/**
			 * @brief Returns a list of distances between vertices.
			 * @param vertices A list of vertex.
			 * @return std::vector< type_t >
			 */
			[[nodiscard]]
			static
			std::vector< float_t >
			getDistances (const std::vector< std::vector< ShapeVertex< float_t > > > & vertices) noexcept
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
				std::vector< float_t > distances{};
				distances.reserve(space);

				for ( size_t index = 0; index < verticesCount - 1; index++ )
				{
					for ( size_t subIndex = index + 1; subIndex < verticesCount; subIndex++ )
					{
						distances.emplace_back(Math::Vector<3, float_t>::distance(vertices[index].position(), vertices[subIndex].position()));
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
			std::array< float_t, 3 >
			getDistancesAggregate (const std::vector< std::vector< ShapeVertex< float_t > > > & vertices) noexcept
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
				m_declaredAttributes.fill(false);
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
				m_options.reset();
			}

		private:

			/**
			 * @brief Check the normal attribute for one vertex.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			checkNormal () noexcept
			{
				if ( m_options.isGlobalNormalEnabled() )
				{
					m_triangleNormals[m_triangleVertexIndex] = m_options.globalNormal();

					return true;
				}

				if ( m_options.isNormalsGenerationEnabled() )
				{
					return false;
				}

				return m_declaredAttributes[NormalDeclared];
			}

			/**
			 * @brief Check the texture coordinates attribute for one vertex.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			checkTextureCoordinates () noexcept
			{
				if ( m_options.isTextureCoordinatesGenerationEnabled() )
				{
					m_triangleTextureCoordinates[m_triangleVertexIndex] = TextureCoordinates::generateCubicCoordinates(
						m_triangleVertices[m_triangleVertexIndex],
						m_options.isNormalsEnabled() ? m_triangleNormals[m_triangleVertexIndex] : Math::Vector< 3, float_t >::positiveZ()
					);

					return true;
				}

				return m_declaredAttributes[TextureCoordinatesDeclared];
			}

			/**
			 * @brief Check the vertex color attribute for one vertex.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			checkVertexColor () noexcept
			{
				if ( m_options.isGlobalVertexColorEnabled() )
				{
					m_triangleVertexColors[m_triangleVertexIndex] = m_options.globalVertexColor();

					return true;
				}

				if ( m_options.isVertexColorsGenerationEnabled() )
				{
					m_triangleVertexColors[m_triangleVertexIndex] = Math::Vector< 4, float_t >{m_triangleVertices[m_triangleVertexIndex].normalized(), 1};

					return true;
				}

				return m_declaredAttributes[VertexColorDeclared];
			}

			/**
			 * @brief Adds a new vertex into the incoming triangle.
			 * @return void
			 */
			void
			newVertexAdded () noexcept
			{
				m_triangleVertexIndex++;
				m_declaredAttributes.fill(false);

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

							if ( m_triangleCount % 2 > 0 )
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
				ShapeTriangle< float_t > triangle{};

				const auto & textureCoordinatesMultiplier = m_options.textureCoordinatesMultiplier();

				for ( size_t vertexIndex = 0; vertexIndex < 3; vertexIndex++ )
				{
					size_t attributeIndex = 0;

					/* Vertex position, normal and texCoords. */
					{
						const auto textureCoordinates = Math::Vector< 3, float_t >(
							m_triangleTextureCoordinates[vertexIndex][Math::X] * textureCoordinatesMultiplier[Math::X],
							m_triangleTextureCoordinates[vertexIndex][Math::Y] * textureCoordinatesMultiplier[Math::Y],
							m_triangleTextureCoordinates[vertexIndex][Math::Z] * textureCoordinatesMultiplier[Math::Z]
						);

						if ( m_options.dataEconomyEnabled() )
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
						if ( m_options.dataEconomyEnabled() )
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

			static constexpr auto PositionDeclared{0UL};
			static constexpr auto NormalDeclared{1UL};
			static constexpr auto TextureCoordinatesDeclared{2UL};
			static constexpr auto VertexColorDeclared{3UL};
			static constexpr auto InfluencesDeclared{4UL};
			static constexpr auto WeightsDeclared{5UL};

			Shape< float_t > * m_destinationShape{nullptr};
			std::array< Math::Vector< 3, float_t >, 3 > m_triangleVertices{};
			std::array< Math::Vector< 3, float_t >, 3 > m_triangleNormals{};
			std::array< Math::Vector< 3, float_t >, 3 > m_triangleTextureCoordinates{};
			std::array< Math::Vector< 4, float_t >, 3 > m_triangleVertexColors{};
			size_t m_triangleVertexIndex{0};
			size_t m_triangleCount{0};
			ShapeBuilderOptions< float_t > m_options;
			ConstructionMode m_constructionMode{ConstructionMode::None};
			std::array< bool, 8 > m_declaredAttributes{
				false/*PositionDeclared*/,
				false/*NormalDeclared*/,
				false/*TextureCoordinatesDeclared*/,
				false/*VertexColorDeclared*/,
				false/*InfluencesDeclared*/,
				false/*WeightsDeclared*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
