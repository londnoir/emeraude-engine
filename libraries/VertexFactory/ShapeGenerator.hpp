/*
 * Libraries/VertexFactory/ShapeGenerator.hpp
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
#include <type_traits>
#include <functional>
#include <vector>
#include <array>
#include <cmath>

/* Local inclusions for usages. */
#include "TextureCoordinates.hpp"
#include "ShapeBuilder.hpp"

namespace Libraries::VertexFactory::ShapeGenerator
{
	/**
	 * @brief Generates a triangle front-facing the camera (Z+).
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param size The size of the triangle. Default 1.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateTriangle (type_t size = 1, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{1};

		ShapeBuilder< type_t > builder{shape, options};

		const auto height = size * (std::sqrt(static_cast< type_t >(3)) * static_cast< type_t >(0.5));
		const auto halfSize = size * static_cast< type_t >(0.5);

		builder.beginConstruction(ConstructionMode::Triangles);

		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::positiveZ());

		/* The top of the triangle (Negative Y). */
		builder.newVertex(
			Math::Vector< 3, type_t >{0, -(height * static_cast< type_t >(0.5)), 0},
			Math::Vector< 2, type_t >{0.5, 0},
			Math::Vector< 4, type_t >{1, 0, 0, 1}
		);

		/* The left of the triangle (Negative X). */
		builder.newVertex(
			Math::Vector< 3, type_t >{-halfSize, halfSize, 0},
			Math::Vector< 2, type_t >{0, 1},
			Math::Vector< 4, type_t >{0, 1, 0, 1}
		);

		/* The right of the triangle (Positive X). */
		builder.newVertex(
			Math::Vector< 3, type_t >{halfSize, halfSize, 0},
			Math::Vector< 2, type_t >{1, 1},
			Math::Vector< 4, type_t >{0, 0, 1, 1}
		);

		builder.endConstruction();

		return shape;
	}

	/**
	 * @brief Generates a quad front-facing the camera (Z+).
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape
	 * @param xScale The size in X-axis.
	 * @param yScale The size in Y-axis. Default same as X-axis.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateQuad (type_t xScale, type_t yScale = 0, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{2};

		ShapeBuilder< type_t > builder{shape, options};

		xScale *= 0.5;

		if ( Utility::isZero(yScale) )
			yScale = xScale;
		else
			yScale *= 0.5;

		builder.beginConstruction(ConstructionMode::TriangleStrip);

		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::positiveZ());

		/* Top-left */
		builder.newVertex(Math::Vector< 3, type_t >{-xScale, -yScale, 0});
		/* Bottom-left */
		builder.newVertex(Math::Vector< 3, type_t >{-xScale,  yScale, 0});
		/* Top-right */
		builder.newVertex(Math::Vector< 3, type_t >{ xScale, -yScale, 0});
		/* Bottom-right */
		builder.newVertex(Math::Vector< 3, type_t >{ xScale,  yScale, 0});

		builder.endConstruction();

		return shape;
	}

	/**
	 * @brief Generates a cuboid shape.
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param width The width of the cuboid shape. Default 1.
	 * @param height The height of the cuboid shape. Default same as width.
	 * @param depth The depth of the cuboid shape. Default same as width.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateCuboid (type_t width = 1, type_t height = 0, type_t depth = 0, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{12};

		ShapeBuilder< type_t > builder{shape, options};

		/* Centering value on axis */
		{
			/* X-axis */
			width *= static_cast< type_t >(0.5);

			/* Y-axis */
			if ( height > 0 )
				height *= static_cast< type_t >(0.5);
			else
				height = width;

			/* Z-axis */
			if ( depth > 0 )
				depth *= static_cast< type_t >(0.5);
			else
				depth = width;
		}

		builder.beginConstruction(ConstructionMode::TriangleStrip);

		/* Right face (X+) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::positiveX());
		builder.newVertex(Math::Vector< 3, type_t >{ width, -height, -depth});
		builder.newVertex(Math::Vector< 3, type_t >{ width, -height,  depth});
		builder.newVertex(Math::Vector< 3, type_t >{ width,  height, -depth});
		builder.newVertex(Math::Vector< 3, type_t >{ width,  height,  depth});
		builder.resetCurrentTriangle();

		/* Left face (X-) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::negativeX());
		builder.newVertex(Math::Vector< 3, type_t >{-width,  height, -depth});
		builder.newVertex(Math::Vector< 3, type_t >{-width,  height,  depth});
		builder.newVertex(Math::Vector< 3, type_t >{-width, -height, -depth});
		builder.newVertex(Math::Vector< 3, type_t >{-width, -height,  depth});
		builder.resetCurrentTriangle();

		/* Top face (Y+) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::positiveY());
		builder.newVertex(Math::Vector< 3, type_t >{-width,  height, -depth});
		builder.newVertex(Math::Vector< 3, type_t >{ width,  height, -depth});
		builder.newVertex(Math::Vector< 3, type_t >{-width,  height,  depth});
		builder.newVertex(Math::Vector< 3, type_t >{ width,  height,  depth});
		builder.resetCurrentTriangle();

		/* Bottom face (Y-) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::negativeY());
		builder.newVertex(Math::Vector< 3, type_t >{-width, -height,  depth});
		builder.newVertex(Math::Vector< 3, type_t >{ width, -height,  depth});
		builder.newVertex(Math::Vector< 3, type_t >{-width, -height, -depth});
		builder.newVertex(Math::Vector< 3, type_t >{ width, -height, -depth});
		builder.resetCurrentTriangle();

		/* Front face (Z+) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::positiveZ());
		builder.newVertex(Math::Vector< 3, type_t >{-width, -height,  depth}); // Top-left
		builder.newVertex(Math::Vector< 3, type_t >{-width,  height,  depth}); // Bottom-left
		builder.newVertex(Math::Vector< 3, type_t >{ width, -height,  depth}); // Top-right
		builder.newVertex(Math::Vector< 3, type_t >{ width,  height,  depth}); // Bottom-right
		builder.resetCurrentTriangle();

		/* Back face (Z-) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::negativeZ());
		builder.newVertex(Math::Vector< 3, type_t >{ width, -height, -depth}); // Top-right
		builder.newVertex(Math::Vector< 3, type_t >{ width,  height, -depth}); // Bottom-right
		builder.newVertex(Math::Vector< 3, type_t >{-width, -height, -depth}); // Top-left
		builder.newVertex(Math::Vector< 3, type_t >{-width,  height, -depth}); // Bottom-left
		builder.resetCurrentTriangle();

		builder.endConstruction();

		return shape;
	}

	/**
	 * @brief Generates a cuboid shape from a vector 3.
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param size The dimension of the cuboid. X for width, Y for height and Z for depth.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	inline
	Shape< type_t >
	generateCuboid (const Math::Vector< 3, type_t > & size, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		return generateCuboid(size[Math::X], size[Math::Y], size[Math::Z], options);
	}

	/**
	 * @brief Generates a cuboid shape from a vector 4.
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param size The dimension of the cuboid. X for width, Y for height and Z for depth.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	inline
	Shape< type_t >
	generateCuboid (const Math::Vector< 4, type_t > & size, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		return generateCuboid(size[Math::X], size[Math::Y], size[Math::Z], options);
	}

	/**
	 * @brief Generates a cuboid shape by using a minimum and a maximum vector.
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param max Positive point of the cuboid.
	 * @param min Negative point of the cuboid.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateCuboid (const Math::Vector< 3, type_t > & max, const Math::Vector< 3, type_t > & min, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{12};

		ShapeBuilder< type_t > builder{shape, options};

		builder.beginConstruction(ConstructionMode::TriangleStrip);

		/* Right face (X+) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::positiveX());
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], min[Math::Y], min[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], min[Math::Y], max[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], max[Math::Y], min[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], max[Math::Y], max[Math::Z]});
		builder.resetCurrentTriangle();

		/* Left face (X-) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::negativeX());
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], max[Math::Y], min[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], max[Math::Y], max[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], min[Math::Y], min[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], min[Math::Y], max[Math::Z]});
		builder.resetCurrentTriangle();

		/* Top face (Y+) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::positiveY());
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], max[Math::Y], min[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], max[Math::Y], min[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], max[Math::Y], max[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], max[Math::Y], max[Math::Z]});
		builder.resetCurrentTriangle();

		/* Bottom face (Y-) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::negativeY());
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], min[Math::Y], max[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], min[Math::Y], max[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], min[Math::Y], min[Math::Z]});
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], min[Math::Y], min[Math::Z]});
		builder.resetCurrentTriangle();

		/* Front face (Z+) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::positiveZ());
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], min[Math::Y], max[Math::Z]}); // Top-left
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], max[Math::Y], max[Math::Z]}); // Bottom-left
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], min[Math::Y], max[Math::Z]}); // Top-right
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], max[Math::Y], max[Math::Z]}); // Bottom-right
		builder.resetCurrentTriangle();

		/* Back face (Z-) */
		builder.options().enableGlobalNormal(Math::Vector< 3, type_t >::negativeZ());
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], min[Math::Y], min[Math::Z]}); // Top-right
		builder.newVertex(Math::Vector< 3, type_t >{max[Math::X], max[Math::Y], min[Math::Z]}); // Bottom-right
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], min[Math::Y], min[Math::Z]}); // Top-left
		builder.newVertex(Math::Vector< 3, type_t >{min[Math::X], max[Math::Y], min[Math::Z]}); // Bottom-left
		builder.resetCurrentTriangle();

		builder.endConstruction();

		return shape;
	}

	/**
	 * @brief Generates a cuboid shape.
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param box A reference to a cuboid definition.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateCuboid (const Math::Cuboid< type_t > & box, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		return generateCuboid(box.maximum(), box.minimum(), options);
	}

	/**
	 * @brief Generates a sphere shape.
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param radius The radius of the sphere shape. Default 1.
	 * @param slices Slices precision of the sphere shape. Default 8.
	 * @param stacks Stack precision of the sphere shape. Default 8.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateSphere (type_t radius = 1, size_t slices = 8, size_t stacks = 8, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{slices * stacks * 6};

		ShapeBuilder< type_t > builder{shape, options};

		if ( radius < 0 )
			radius *= -1;
		else if ( Utility::isZero(radius) )
			radius = 1;

		const auto drho = Math::Pi< type_t > / static_cast< type_t >(stacks);
		const auto dtheta = (2 * Math::Pi< type_t >) / static_cast< type_t >(slices);

		const auto deltaU = static_cast< type_t >(1) / static_cast< type_t >(slices);
		const auto deltaV = static_cast< type_t >(1) / static_cast< type_t >(stacks);

		std::array< Math::Vector< 3, type_t >, 4 > positions{};
		std::array< Math::Vector< 3, type_t >, 4 > normals{};
		std::array< Math::Vector< 2, type_t >, 4 > texCoords{};

		auto U = static_cast< type_t >(1);

		builder.beginConstruction(ConstructionMode::TriangleStrip);

		for ( size_t stackIndex = 0; stackIndex < stacks; stackIndex++ )
		{
			const auto rho = drho * static_cast< type_t >(stackIndex);

			const auto srho = std::sin(rho);
			const auto crho = std::cos(rho);

			const auto srhodrho = std::sin(rho + drho);
			const auto crhodrho = std::cos(rho + drho);

			/* Many sources of OpenGL sphere drawing code uses a triangle fan
			 * for the caps of the sphere. This however introduces texturing
			 * artifacts at the poles on some OpenGL implementations. */
			auto V = static_cast< type_t >(0);

			for ( size_t sliceIndex = 0; sliceIndex < slices; sliceIndex++)
			{
				auto theta = sliceIndex == slices ? 0 : static_cast< type_t >(sliceIndex) * dtheta;
				auto stheta = -std::sin(theta);
				auto ctheta = std::cos(theta);

				auto x = stheta * srho;
				auto y = crho;
				auto z = ctheta * srho;

				positions[0] = {x * radius, y * radius, z * radius};
				texCoords[0] = {U, V};
				normals[0] = {x, y, z};

				x = stheta * srhodrho;
				y = crhodrho;
				z = ctheta * srhodrho;

				positions[1] = {x * radius, y * radius, z * radius};
				texCoords[1] = {U - deltaV, V};
				normals[1] = {x, y, z};

				theta = ( sliceIndex + 1 == slices ) ? 0 : static_cast< type_t >(sliceIndex + 1) * dtheta;
				stheta = -std::sin(theta);
				ctheta = std::cos(theta);

				x = stheta * srho;
				y = crho;
				z = ctheta * srho;

				V += deltaU;

				positions[2] = {x * radius, y * radius, z * radius};
				texCoords[2] = {U, V};
				normals[2] = {x, y, z};

				x = stheta * srhodrho;
				y = crhodrho;
				z = ctheta * srhodrho;

				positions[3] = {x * radius, y * radius, z * radius};
				texCoords[3] = {U - deltaV, V};
				normals[3] = {x, y, z};

				/* Draw quad */
				builder.newVertex(positions[0], texCoords[0], normals[0]);
				builder.newVertex(positions[1], texCoords[1], normals[1]);
				builder.newVertex(positions[2], texCoords[2], normals[2]);
				builder.newVertex(positions[3], texCoords[3], normals[3]);

				builder.resetCurrentTriangle();
			}

			U -= deltaV;
		}

		builder.endConstruction();

		return shape;
	}

	/**
	 * @brief Subdivision method for geodesic sphere generation.
	 * @param builder A reference to the builder.
	 * @param v1
	 * @param v2
	 * @param v3
	 * @param points
	 * @param depth
	 * @return void
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	void
	subdivide (ShapeBuilder< type_t > & builder, const Math::Vector< 3, type_t > & v1, const Math::Vector< 3, type_t > & v2, const Math::Vector< 3, type_t > & v3, std::vector< Math::Vector< 3, type_t > > & points, size_t depth) noexcept
	{
		if ( depth == 0 )
		{
			builder.newVertex(v1, TextureCoordinates::generateSphericalCoordinates(v1));
			builder.newVertex(v2, TextureCoordinates::generateSphericalCoordinates(v2));
			builder.newVertex(v3, TextureCoordinates::generateSphericalCoordinates(v3));

			return;
		}

		const auto v12 = (v1 + v2).normalize();
		const auto v23 = (v2 + v3).normalize();
		const auto v31 = (v3 + v1).normalize();
		const auto newDepth = depth - 1;

		subdivide(builder, v1, v12, v31, points, newDepth);
		subdivide(builder, v2, v23, v12, points, newDepth);
		subdivide(builder, v3, v31, v23, points, newDepth);
		subdivide(builder, v12, v23, v31, points, newDepth);
	}
	/**
	 * @brief Generates a geodesic sphere shape.
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param radius The radius of the sphere shape. Default 1.
	 * @param depth Depth precision of the sphere shape. Default 2.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateGeodesicSphere (type_t radius = 1, size_t depth = 2, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{depth * 20};

		ShapeBuilder< type_t > builder{shape, options};

		const auto X = static_cast< type_t >(0.525731112119133606);
		const auto Y = static_cast< type_t >(0.0);
		const auto Z = static_cast< type_t >(0.850650808352039932);

		const std::array< Math::Vector< 3, type_t >, 12 > vertices{{
			{-X,  Y,  Z},
			{ X,  Y,  Z},
			{-X,  Y, -Z},
			{ X,  Y, -Z},
			{ Y,  Z,  X},
			{ Y,  Z, -X},
			{ Y, -Z,  X},
			{ Y, -Z, -X},
			{ Z,  X,  Y},
			{-Z,  X,  Y},
			{ Z, -X,  Y},
			{-Z, -X,  Y}
		}};

		const std::array< std::array< size_t , 3 >, 20 > indices{{
			{{0, 4, 1}},
			{{0, 9, 4}},
			{{9, 5, 4}},
			{{4, 5, 8}},
			{{4, 8, 1}},
			{{8, 10, 1}},
			{{8, 3, 10}},
			{{5, 3, 8}},
			{{5, 2, 3}},
			{{2, 7, 3}},
			{{7, 10, 3}},
			{{7, 6, 10}},
			{{7, 11, 6}},
			{{11, 0, 6}},
			{{0, 1, 6}},
			{{6, 1, 10}},
			{{9, 0, 11}},
			{{9, 11, 2}},
			{{9, 2, 5}},
			{{7, 2, 11}}
		}};

		std::vector< Math::Vector< 3, type_t > > points{};

		builder.beginConstruction(ConstructionMode::Triangles);

		for ( const auto & index : indices )
			subdivide(builder, vertices[index[0]], vertices[index[1]], vertices[index[2]], points, depth);

		builder.endConstruction();

		shape.transform(Math::Matrix< 4, type_t >::scaling(radius));

		return shape;
	}

	/**
	 * @brief Generates a cylinder shape.
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param baseRadius The bottom radius of the cylinder shape. Default 1.
	 * @param topRadius The top radius of the cylinder shape. Default 1.
	 * @param length The lenght of the cylinder shape. Default 1.
	 * @param slices Slices precision of the cylinder shape. Default 8.
	 * @param stacks Stack precision of the cylinder shape. Default 1.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateCylinder (type_t baseRadius = 1, type_t topRadius = 1, type_t length = 1, size_t slices = 8, size_t stacks = 1, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{slices * stacks * 6};

		ShapeBuilder< type_t > builder{shape, options};

		const auto radiusStep = (topRadius - baseRadius) / static_cast< type_t >(stacks);
		const auto stepSizeSlice = (2 * Math::Pi< type_t >) / static_cast< type_t >(slices);

		/* Texture coordinates */
		const auto deltaU = static_cast< type_t >(1) / static_cast< type_t >(slices);
		const auto deltaV = static_cast< type_t >(1) / static_cast< type_t >(stacks);

		std::array< Math::Vector< 3, type_t >, 4 > positions{};
		std::array< Math::Vector< 3, type_t >, 4 > normals{};
		std::array< Math::Vector< 2, type_t >, 4 > texCoords{};

		builder.beginConstruction(ConstructionMode::TriangleStrip);

		for ( size_t stackIndex = 0; stackIndex < stacks; stackIndex++ )
		{
			const auto stackIndexF = static_cast< type_t >(stackIndex);
			const auto stackIndexPlusOneF = static_cast< type_t >(stackIndex + 1);

			/* Texture coordinates.
			 * NOTE: Inverted for Vulkan. */
			const auto V = 1.0F - (( stackIndex == 0 ) ? 0 : deltaV * stackIndexF);
			const auto nextV = 1.0F - (( stackIndex == stacks - 1 ) ? 1 : deltaV * stackIndexPlusOneF);

			const auto currentRadius = baseRadius + (radiusStep * stackIndexF);
			const auto nextRadius = baseRadius + (radiusStep * stackIndexPlusOneF);

			const auto currentY = -(length / stacks) * stackIndexF;
			const auto nextY = -(length / stacks) * stackIndexPlusOneF;

			/* Rise over run... */
			const auto yNormal = Utility::isZero(baseRadius - topRadius) ? 0 : baseRadius - topRadius;

			for ( size_t sliceIndex = 0; sliceIndex < slices; sliceIndex++ )
			{
				const auto sliceIndexF = static_cast< type_t >(sliceIndex);
				const auto sliceIndexPlusOneF = static_cast< type_t >(sliceIndex + 1);

				/* Texture coordinates.
				 * NOTE : Surface Normal, same for everybody
				 * NOTE² : Inverted for Vulkan. */
				const auto U = 1.0F - (( sliceIndex == 0 ) ? 0 : deltaU * sliceIndexF);
				const auto nextU = 1.0F - (( sliceIndex == slices - 1 ) ? 1 : deltaU * sliceIndexPlusOneF);

				const auto theyta = stepSizeSlice * sliceIndexF;
				const auto theytaNext = ( sliceIndex == slices - 1 ) ? 0 : stepSizeSlice * sliceIndexPlusOneF;

				/* Inner First */
				positions[0] = {std::cos(theyta) * currentRadius, currentY, std::sin(theyta) * currentRadius};
				texCoords[0] = {U, V};
				normals[0] = {positions[0][Math::X], yNormal, positions[0][Math::Z]};
				normals[0].normalize();

				/* Outer First */
				positions[1] = {std::cos(theyta) * nextRadius, nextY, std::sin(theyta) * nextRadius};
				texCoords[1] = {U, nextV};

				if ( Utility::isZero(nextRadius) )
				{
					normals[1] = normals[0];
				}
				else
				{
					normals[1] = {positions[1][Math::X], yNormal, positions[1][Math::Z]};
					normals[1].normalize();
				}

				/* Inner second */
				positions[2] = {std::cos(theytaNext) * currentRadius, currentY, std::sin(theytaNext) * currentRadius};
				texCoords[2] = {nextU, V};
				normals[2] = {positions[2][Math::X], yNormal, positions[2][Math::Z]};
				normals[2].normalize();

				/* Outer second */
				positions[3] = {std::cos(theytaNext) * nextRadius, nextY, std::sin(theytaNext) * nextRadius};
				texCoords[3] = {nextU, nextV};

				if ( Utility::isZero(nextRadius) )
				{
					normals[3] = normals[2];
				}
				else
				{
					normals[3] = {positions[3][Math::X], yNormal, positions[3][Math::Z]};
					normals[3].normalize();
				}

				/* Draw quad */
				builder.newVertex(positions[0], texCoords[0], normals[0]);
				builder.newVertex(positions[1], texCoords[1], normals[1]);
				builder.newVertex(positions[2], texCoords[2], normals[2]);
				builder.newVertex(positions[3], texCoords[3], normals[3]);
				builder.resetCurrentTriangle();
			}
		}

		builder.endConstruction();

		return shape;
	}

	/**
	 * @brief Generates a cone shape.
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param radius The radius of the base cylinder. Default 1.
	 * @param length The lenght of the cone shape. Default 1.
	 * @param slices Slices precision of the cone shape. Default 8.
	 * @param stacks Stack precision of the cone shape. Default 1.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateCone (type_t radius = 1, type_t length = 1, size_t slices = 8, size_t stacks = 1, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		return generateCylinder(radius, static_cast< type_t >(0), length, slices, stacks, options);
	}

	/**
	 * @brief Generates a disk shape facing the sky (Y-).
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param outerRadius The radius of the outer part of the disl. Default 1.
	 * @param innerRadius The radius of the inner part of the disk. Default 0.5.
	 * @param slices Slices precision of the disk shape. Default 8.
	 * @param stacks Stack precision of the disk shape. Default 1.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateDisk (type_t outerRadius = 1, type_t innerRadius = 0.5, size_t slices = 8, size_t stacks = 1, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{slices * stacks * 6};

		ShapeBuilder< type_t > builder{shape, options};

		if ( innerRadius > outerRadius )
		{
			auto tmp = innerRadius;

			innerRadius = outerRadius;
			outerRadius = tmp;
		}

		const auto stepSizeRadial = std::abs(outerRadius - innerRadius) / stacks;
		const auto stepSizeSlice = (2 * Math::Pi< type_t >) / slices;
		const auto radialScale = static_cast< type_t >(1) / outerRadius;

		std::array< Math::Vector< 3, type_t >, 4 > positions{};
		std::array< Math::Vector< 2, type_t >, 4 > texCoords{};

		builder.beginConstruction(ConstructionMode::TriangleStrip);

		for ( size_t stackIndex = 0; stackIndex < stacks; stackIndex++ )
		{
			for ( size_t sliceIndex = 0; sliceIndex < slices; sliceIndex++ )
			{
				const auto inner = innerRadius + stackIndex * stepSizeRadial;
				const auto outer = innerRadius + ( stackIndex + 1 ) * stepSizeRadial;

				const auto theyta = stepSizeSlice * sliceIndex;
				const auto theytaNext = ( sliceIndex == (slices - 1) ) ? 0 : stepSizeSlice * (sliceIndex + 1);

				/* Inner First */
				positions[0] = {std::cos(theyta) * inner, 0, std::sin(theyta) * inner};
				texCoords[0] = {
					((positions[0][Math::X] * radialScale) + 1) * static_cast< type_t >(0.5),
					((positions[0][Math::Z] * radialScale) + 1) * static_cast< type_t >(0.5)
				};

				/* Inner Second */
				positions[1] = {std::cos(theytaNext) * inner, 0, std::sin(theytaNext) * inner};
				texCoords[1] = {
					((positions[1][Math::X] * radialScale) + 1) * static_cast< type_t >(0.5),
					((positions[1][Math::Z] * radialScale) + 1) * static_cast< type_t >(0.5)
				};

				/* Outer First */
				positions[2] = {std::cos(theyta) * outer, 0, std::sin(theyta) * outer};
				texCoords[2] = {
					((positions[2][Math::X] * radialScale) + 1) * static_cast< type_t >(0.5),
					((positions[2][Math::Z] * radialScale) + 1) * static_cast< type_t >(0.5)
				};

				/* Outer Second */
				positions[3] = {std::cos(theytaNext) * outer, 0, std::sin(theytaNext) * outer};
				texCoords[3] = {
					((positions[3][Math::X] * radialScale) + 1) * static_cast< type_t >(0.5),
					((positions[3][Math::Z] * radialScale) + 1) * static_cast< type_t >(0.5)
				};

				/* Draw quad */
				builder.newVertex(positions[0], texCoords[0], Math::Vector< 3, type_t >::positiveY());
				builder.newVertex(positions[1], texCoords[1], Math::Vector< 3, type_t >::positiveY());
				builder.newVertex(positions[2], texCoords[2], Math::Vector< 3, type_t >::positiveY());
				builder.newVertex(positions[3], texCoords[3], Math::Vector< 3, type_t >::positiveY());
				builder.resetCurrentTriangle();
			}
		}

		builder.endConstruction();

		return shape;
	}

	/**
	 * @brief Generates a torus shape.
	 * @note Ready for vulkan default world axis.
	 * @tparam type_t The data type of the shape.
	 * @param majorRadius The major radius of the torus shape. Default 1.
	 * @param minorRadius The minor radius of the torus shape. Default 0.5.
	 * @param slices Slices precision of the torus shape. Default 8.
	 * @param stacks Stack precision of the torus shape. Default 8.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateTorus (type_t majorRadius = 1, type_t minorRadius = 0.5, size_t slices = 8, size_t stacks = 8, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{stacks * (slices + 1) * 6};

		ShapeBuilder< type_t > builder{shape, options};

		const auto stacksF = static_cast< type_t >(stacks);
		const auto slicesF = static_cast< type_t >(slices);

		const auto majorStep = (2 * Math::Pi< type_t >) / stacksF;
		const auto minorStep = (2 * Math::Pi< type_t >) / slicesF;

		std::array< Math::Vector< 3, type_t >, 4 > positions{};
		std::array< Math::Vector< 3, type_t >, 4 > normals{};
		std::array< Math::Vector< 2, type_t >, 4 > texCoords{};

		builder.beginConstruction(ConstructionMode::TriangleStrip);

		for ( size_t stackIndex = 0; stackIndex < stacks; ++stackIndex )
		{
			const auto stackIndexF = static_cast< type_t >(stackIndex);

			const auto a0 = stackIndexF * majorStep;
			const auto a1 = a0 + majorStep;

			const auto x0 = std::cos(a0);
			const auto z0 = std::sin(a0);

			const auto x1 = std::cos(a1);
			const auto z1 = std::sin(a1);

			for ( size_t sliceIndex = 0; sliceIndex <= slices; ++sliceIndex )
			{
				const auto sliceIndexF = static_cast< type_t >(sliceIndex);

				auto b = sliceIndexF * minorStep;
				auto c = std::cos(b);
				auto r = minorRadius * c + majorRadius;
				auto y = minorRadius * std::sin(b);

				/* Texture coordinates.
				 * NOTE: V is inverted for Vulkan. */
				const auto uA = stackIndexF / stacksF;
				const auto vA = 1.0F - (sliceIndexF / slicesF);
				const auto uB = (stackIndexF + 1) / stacksF;
				const auto vB = 1.0F - ((sliceIndexF + 1) / slicesF);

				/* First point */
				positions[0] = {x0 * r, y, z0 * r};
				texCoords[0] = {uA, vA};
				normals[0] = {x0 * c, y / minorRadius, z0 * c};
				normals[0].normalize();

				/* Second point */
				positions[1] = {x1 * r, y, z1 * r};
				texCoords[1] = {uB, vA};
				normals[1] = {x1 * c, y / minorRadius, z1 * c};
				normals[1].normalize();

				/* Next one over */
				b = (sliceIndexF + 1) * minorStep;
				c = std::cos(b);
				r = minorRadius * c + majorRadius;
				y = minorRadius * std::sin(b);

				/* Third (based on first) */
				positions[2] = {x0 * r, y, z0 * r};
				texCoords[2] = {uA, vB};
				normals[2] = {x0 * c, y / minorRadius, z0 * c};
				normals[2].normalize();

				/* Fourth (based on second) */
				positions[3] = {x1 * r, y, z1 * r};
				texCoords[3] = {uB, vB};
				normals[3] = {x1 * c, y / minorRadius, z1 * c};
				normals[3].normalize();

				/* Draw quad */
				builder.newVertex(positions[0], texCoords[0], normals[0]);
				builder.newVertex(positions[1], texCoords[1], normals[1]);
				builder.newVertex(positions[2], texCoords[2], normals[2]);
				builder.newVertex(positions[3], texCoords[3], normals[3]);
				builder.resetCurrentTriangle();
			}
		}

		builder.endConstruction();

		return shape;
	}

	/**
	 * @brief Generates a tetrahedron shape (Fire symbol).
	 * @note Ready for vulkan default world axis.
	 * @fixme Mathematically incorrect geometry.
	 * @tparam type_t The data type of the shape.
	 * @param radius The radius of the shape. Default 1.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateTetrahedron (type_t radius = 1, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{4};

		ShapeBuilder< type_t > builder{shape, options};

		/* NOTE : a = (2 * √6) / 3 * r */
		const type_t edgeSize = (static_cast< type_t >(2) * std::sqrt(static_cast< type_t >(6))) / static_cast< type_t >(3) * radius;

		const Math::Vector< 3, type_t > frontLeft{ edgeSize, edgeSize, -edgeSize};
		const Math::Vector< 3, type_t > frontRight{-edgeSize, edgeSize, -edgeSize};
		const Math::Vector< 3, type_t > back{0, edgeSize, edgeSize};
		const Math::Vector< 3, type_t > top{0, -edgeSize, 0};

		const Math::Vector< 2, type_t > UVBottomLeft{0, 1};
		const Math::Vector< 2, type_t > UVBottomRight{1, 1};
		const Math::Vector< 2, type_t > UVTopMiddle{0.5, 0};

		builder.beginConstruction(ConstructionMode::Triangles);

		builder.newVertex(frontLeft, UVBottomLeft);
		builder.newVertex(frontRight, UVBottomRight);
		builder.newVertex(top, UVTopMiddle);

		builder.newVertex(frontRight, UVBottomLeft);
		builder.newVertex(back, UVBottomRight);
		builder.newVertex(top, UVTopMiddle);

		builder.newVertex(back, UVBottomLeft);
		builder.newVertex(frontLeft, UVBottomRight);
		builder.newVertex(top, UVTopMiddle);

		builder.newVertex(frontRight, Math::Vector< 2, type_t >{1, 0});
		builder.newVertex(frontLeft, Math::Vector< 2, type_t >{0, 0});
		builder.newVertex(back, Math::Vector< 2, type_t >{0.5, 1});

		builder.endConstruction();

		return shape;
	}

	/**
	 * @brief Generates an hexahedron shape (Earth symbol).
	 * @note Ready for vulkan default world axis.
	 * @fixme Mathematically incorrect geometry.
	 * @tparam type_t The data type of the shape.
	 * @param radius The radius of the shape. Default 1.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateHexahedron (type_t radius = 1, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		/* NOTE: c = √(2) * r */
		const type_t edgeSize = std::sqrt(static_cast< type_t >(2)) * radius;
		const type_t D = (std::sqrt(static_cast< type_t >(3)) * edgeSize) * 0.5;

		return generateCuboid(D, D, D, options);
	}

	/**
	 * @brief Generates an octahedron shape (Air symbol).
	 * @note Ready for vulkan default world axis.
	 * @fixme Mathematically incorrect geometry.
	 * @tparam type_t The data type of the shape.
	 * @param size The radius of the shape. Default 1.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateOctahedron (type_t radius = 1, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{8};

		ShapeBuilder< type_t > builder{shape, options};

		/* NOTE: a = √2 / 2 * r */
		const type_t edgeSize = std::sqrt(static_cast< type_t >(2)) / static_cast< type_t >(2) * radius;

		builder.beginConstruction(ConstructionMode::Triangles);

		/* Top pyramid */
		/* Front */
		builder.newVertex(Math::Vector< 3, type_t >{-edgeSize, 0, edgeSize}, Math::Vector< 2, type_t >{0, 0});
		builder.newVertex(Math::Vector< 3, type_t >{ edgeSize, 0, edgeSize}, Math::Vector< 2, type_t >{1, 0});
		builder.newVertex(Math::Vector< 3, type_t >{0, -edgeSize, 0}, Math::Vector< 2, type_t >{0.5, -1});

		/* Back */
		builder.newVertex(Math::Vector< 3, type_t >{ edgeSize, 0, -edgeSize}, Math::Vector< 2, type_t >{0, 0});
		builder.newVertex(Math::Vector< 3, type_t >{-edgeSize, 0, -edgeSize}, Math::Vector< 2, type_t >{1, 0});
		builder.newVertex(Math::Vector< 3, type_t >{0, -edgeSize, 0}, Math::Vector< 2, type_t >{0.5, -1});

		/* Left */
		builder.newVertex(Math::Vector< 3, type_t >{-edgeSize, 0, -edgeSize}, Math::Vector< 2, type_t >{0, 0});
		builder.newVertex(Math::Vector< 3, type_t >{-edgeSize, 0,  edgeSize}, Math::Vector< 2, type_t >{1, 0});
		builder.newVertex(Math::Vector< 3, type_t >{0, -edgeSize, 0}, Math::Vector< 2, type_t >{0.5, -1});

		/* Right */
		builder.newVertex(Math::Vector< 3, type_t >{edgeSize, 0,  edgeSize}, Math::Vector< 2, type_t >{0, 0});
		builder.newVertex(Math::Vector< 3, type_t >{edgeSize, 0, -edgeSize}, Math::Vector< 2, type_t >{1, 0});
		builder.newVertex(Math::Vector< 3, type_t >{0, -edgeSize, 0}, Math::Vector< 2, type_t >{0.5, -1});

		/* Bottom pyramid */
		/* Front */
		builder.newVertex(Math::Vector< 3, type_t >{edgeSize, 0, edgeSize}, Math::Vector< 2, type_t >{1, -1});
		builder.newVertex(Math::Vector< 3, type_t >{-edgeSize, 0, edgeSize}, Math::Vector< 2, type_t >{0, -1});
		builder.newVertex(Math::Vector< 3, type_t >{0, edgeSize, 0}, Math::Vector< 2, type_t >{0.5, 0});

		/* Back */
		builder.newVertex(Math::Vector< 3, type_t >{-edgeSize, 0, -edgeSize}, Math::Vector< 2, type_t >{1, -1});
		builder.newVertex(Math::Vector< 3, type_t >{edgeSize, 0, -edgeSize}, Math::Vector< 2, type_t >{0, -1});
		builder.newVertex(Math::Vector< 3, type_t >{0, edgeSize, 0}, Math::Vector< 2, type_t >{0.5, 0});

		/* Left */
		builder.newVertex(Math::Vector< 3, type_t >{-edgeSize, 0,  edgeSize}, Math::Vector< 2, type_t >{1, -1});
		builder.newVertex(Math::Vector< 3, type_t >{-edgeSize, 0, -edgeSize}, Math::Vector< 2, type_t >{0, -1});
		builder.newVertex(Math::Vector< 3, type_t >{0,  edgeSize, 0}, Math::Vector< 2, type_t >{0.5, 0});

		/* Right */
		builder.newVertex(Math::Vector< 3, type_t >{edgeSize, 0, -edgeSize}, Math::Vector< 2, type_t >{1, -1});
		builder.newVertex(Math::Vector< 3, type_t >{edgeSize, 0,  edgeSize}, Math::Vector< 2, type_t >{0, -1});
		builder.newVertex(Math::Vector< 3, type_t >{0,  edgeSize, 0}, Math::Vector< 2, type_t >{0.5, 0});

		builder.endConstruction();

		return shape;
	}

	/**
	 * @brief Generates a dodecahedron shape (Ether, Universe symbol).
	 * @todo Write the algorithm.
	 * @tparam type_t The data type of the shape.
	 * @param radius The radius of the shape. Default 1.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateDodecahedron (type_t radius = 1, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{36};

		ShapeBuilder< type_t > builder{shape, options};

		std::cerr << __PRETTY_FUNCTION__ << ", not handle yet ! (Radius: " << radius << ")" "\n";

		return shape;
	}

	/**
	 * @brief Generates an icosahedron shape (Water symbol).
	 * @todo Write the algorithm.
	 * @tparam type_t The data type of the shape.
	 * @param radius The radius of the shape. Default 1.
	 * @param options A reference to initial builder options. Default none.
	 * @return Shape< type_t >
	 */
	template< typename type_t, std::enable_if_t< std::is_floating_point_v< type_t >, bool > = false >
	Shape< type_t >
	generateIcosahedron (type_t radius = 1, const ShapeBuilderOptions< type_t > & options = {}) noexcept
	{
		Shape< type_t > shape{20};

		ShapeBuilder< type_t > builder{shape, options};

		std::cerr << __PRETTY_FUNCTION__ << ", not handle yet ! (Radius: " << radius << ")" "\n";

		return shape;
	}
}
