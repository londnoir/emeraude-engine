/*
 * src/Libs/VertexFactory/ShapeAssembler.hpp
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

/* Engine configuration file. */
#include "emeraude_config.hpp"

/* STL inclusions. */
#include <type_traits>

/* Local inclusions. */
#include "Libs/Math/CartesianFrame.hpp"
#include "ShapeBuilder.hpp"

namespace EmEn::Libs::VertexFactory
{
	/**
	 * @brief The shape assembler class provide an easy way to group shapes.
	 * @tparam float_t The type of floating point number. Default float.
	 */
	template< typename float_t = float >
	requires (std::is_floating_point_v< float_t >)
	class ShapeAssembler final
	{
		public:

			/**
			 * @brief Constructs the shape assembler.
			 */
			ShapeAssembler () noexcept = default;

			/**
			 * @brief Constructs the shape assembler with a targeted destination.
			 * @param destinationShape A reference to the shape.
			 */
			explicit ShapeAssembler (Shape< float_t > & destinationShape) noexcept
				: m_destinationShape(&destinationShape)
			{

			}

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			ShapeAssembler (const ShapeAssembler & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			ShapeAssembler (ShapeAssembler && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			ShapeAssembler & operator= (const ShapeAssembler & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			ShapeAssembler & operator= (ShapeAssembler && copy) noexcept = delete;

			/**
			 * @brief Destructs the shape assembler.
			 */
			~ShapeAssembler () = default;

			/**
			 * @brief Sets the target geometry where shape will be merged.
			 * @param destinationShape A reference to a shape.
			 * @return void
			 */
			void
			setDestinationShape (Shape< float_t > & destinationShape) noexcept
			{
				m_destinationShape = &destinationShape;
			}

			/**
			 * @brief Merges a new shape.
			 * @param sourceShape A reference to the shape.
			 * @param useNewGroup Define the new shape as a new group. Default false.
			 * @return bool
			 */
			bool
			merge (const Shape< float_t > & sourceShape, bool useNewGroup = false) noexcept
			{
				if ( m_destinationShape == nullptr || sourceShape.empty() )
				{
					return false;
				}

				ShapeBuilder builder{*m_destinationShape};
				builder.beginConstruction(ConstructionMode::Triangles);

				if ( useNewGroup )
				{
					builder.newGroup();
				}

				for ( const auto & triangle : sourceShape.triangles() )
				{
					for ( size_t vertexIndex = 0; vertexIndex < 3; vertexIndex++ )
					{
						const auto & vertex = sourceShape.vertex(triangle.vertexIndex(vertexIndex));

						builder.setPosition(vertex.position());
						builder.setNormal(vertex.normal());
						builder.setTextureCoordinates(vertex.textureCoordinates());
						builder.setVertexColor(sourceShape.vertexColor(triangle.vertexColorIndex(vertexIndex)));
						builder.newVertex();
					}
				}

				builder.endConstruction();

				return true;
			}

			/**
			 * @brief Merges a new shape with transformations.
			 * @param sourceShape A reference to the shape.
			 * @param transform A reference to a transform matrix.
			 * @param useNewGroup Define the new shape as a new group. Default false.
			 * @return bool
			 */
			bool
			merge (const Shape< float_t > & sourceShape, const Math::Matrix< 4, float_t > & transform, bool useNewGroup = false) noexcept
			{
				if ( m_destinationShape == nullptr || sourceShape.empty() )
				{
					return false;
				}

				ShapeBuilder builder{*m_destinationShape};
				builder.beginConstruction(ConstructionMode::Triangles);

				if ( useNewGroup )
				{
					builder.newGroup();
				}

				/* Remove translation from the incoming matrix. */
				const auto noTranslate = transform.noTranslation();

				for ( const auto & triangle : sourceShape.triangles() )
				{
					for ( size_t vertexIndex = 0; vertexIndex < 3; vertexIndex++ )
					{
						const auto & vertex = sourceShape.vertex(triangle.vertexIndex(vertexIndex));

						builder.setPosition((transform * Math::Vector< 4, float_t >(vertex.position(), 1)).toVector3());
						builder.setNormal((noTranslate * Math::Vector< 4, float_t >(vertex.normal(), 0)).toVector3().normalize());
						builder.setTextureCoordinates(vertex.textureCoordinates());
						builder.setVertexColor(sourceShape.vertexColor(triangle.vertexColorIndex(vertexIndex)));
						builder.newVertex();
					}
				}

				builder.endConstruction();

				return true;
			}

			/**
			 * @brief Merges a new shape.
			 * @param sourceShape A reference to the shape.
			 * @param atLocation A reference to a coordinates.
			 * @param useNewGroup Define the new shape as a new group. Default false.
			 * @return bool
			 */
			bool
			merge (const Shape< float_t > & sourceShape, const Math::CartesianFrame< float_t > & atLocation, bool useNewGroup = false) noexcept
			{
				return this->merge(sourceShape, atLocation.modelMatrix(), useNewGroup);
			}

			/**
			 * @brief Merges two shapes. Quick version.
			 * @param destinationShape A reference to a destination shape.
			 * @param sourceShape A reference to a source shape.
			 * @param useNewGroup Define the new shape as a new group. Default false.
			 * @return bool
			 */
			static
			bool
			merge (Shape< float_t > & destinationShape, const Shape< float_t > & sourceShape, bool useNewGroup = false) noexcept
			{
				return ShapeAssembler{destinationShape}.merge(sourceShape, useNewGroup);
			}

			/**
			 * @brief Merges two shapes and returns a new one.
			 * @param shapeA A reference to a shape.
			 * @param shapeB A reference to a shape.
			 * @param useGroup Define the shapes as group. Default false.
			 * @return Shape< type_t >
			 */
			static
			Shape< float_t >
			merge (const Shape< float_t > & shapeA, const Shape< float_t > & shapeB, bool useGroup = false) noexcept
			{
				Shape< float_t > output{};

				ShapeAssembler assembler{output};
				assembler.merge(shapeA, useGroup);
				assembler.merge(shapeB, useGroup);

				return output;
			}

			/**
			 * @brief Merges a list of shapes and returns a new one.
			 * @param shapes A reference to vector of shapes.
			 * @param useGroup Define every shape as a group. Default false.
			 * @return Shape< type_t >
			 */
			static
			Shape< float_t >
			mergeList (const std::vector< Shape< float_t > > & shapes, bool useGroup = false) noexcept
			{
				Shape< float_t > output{};

				ShapeAssembler assembler{output};

				for ( const auto & shape : shapes )
				{
					assembler.merge(shapes, useGroup);
				}

				return output;
			}

		private:

			Shape< float_t > * m_destinationShape{nullptr};
	};
}
