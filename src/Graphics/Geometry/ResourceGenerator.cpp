/*
 * Emeraude/Graphics/Geometry/ResourceGenerator.cpp
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

#include "ResourceGenerator.hpp"

/* C/C++ standard libraries. */
#include <thread>

/* Local inclusions. */
#include "Hash/Hash.hpp"
#include "Resources/Manager.hpp"
#include "VertexFactory/ShapeAssembler.hpp"
#include "VertexFactory/ShapeGenerator.hpp"

namespace Emeraude::Graphics::Geometry
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Libraries::VertexFactory;

	ResourceGenerator::ResourceGenerator (uint32_t geometryFlags) noexcept
		: m_vertexGeometries(Resources::Manager::instance()->vertexGeometries()),
		m_indexedVertexGeometries(Resources::Manager::instance()->indexedVertexGeometries()),
		m_vertexGridGeometries(Resources::Manager::instance()->vertexGridGeometries()),
		m_generationParameters(geometryFlags)
	{

	}

	const GenerationParameters &
	ResourceGenerator::parameters () const noexcept
	{
		return m_generationParameters;
	}

	GenerationParameters &
	ResourceGenerator::parameters () noexcept
	{
		return m_generationParameters;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::shape (const Shape< float > & shape, const std::string & resourceName) noexcept
	{
		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Loading '" << resourceName << "' custom geometry resource ...";

			/* FIXME: Check for the reference to the shape. */
			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters /*parameters*/, const Shape< float > & shape) {
				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Custom geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a custom geometry resource !"); 
				}
			}, geometry, m_generationParameters, shape};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< VertexResource >
	ResourceGenerator::triangle (float size, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("ShapeTriangle", (std::stringstream{} << size).str()); 
		}

		auto geometry = m_vertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' triangle geometry resource ...";

			std::thread generation{[] (std::shared_ptr< VertexResource > geometry, GenerationParameters parameters, float size) {
				auto shape = ShapeGenerator::generateTriangle(size, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] ShapeTriangle geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a triangle geometry resource !"); 
				}
			}, geometry, m_generationParameters, size};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::quad (float width, float height, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Quad", (std::stringstream{} << width << ',' << height).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' quad geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float width, float height) {
				auto shape = ShapeGenerator::generateQuad(width, height, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Quad geometry resource generated successfully !"); 
				}
				else
				{
					Tracer::error(ClassId, "[Background] Unable to generate a quad geometry resource !"); 
				}
			}, geometry, m_generationParameters, width, height};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::cuboid (float width, float height, float depth, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{
			resourceName = this->generateResourceName("Cuboid", (std::stringstream{} << width << ',' << height << ',' << depth).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' cuboid geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float width, float height, float depth) {
				auto shape = ShapeGenerator::generateCuboid(width, height, depth, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Cuboid geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a cuboid geometry resource !"); 
				}
			}, geometry, m_generationParameters, width, height, depth};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::cuboid (const Vector< 3, float > & max, const Vector< 3, float > & min, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Cuboid", (std::stringstream{} << max << ',' << min).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' cuboid geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, const Vector< 3, float > & max, const Vector< 3, float > & min) {
				auto shape = ShapeGenerator::generateCuboid(max, min, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Cuboid geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a cuboid geometry resource !"); 
				}
			}, geometry, m_generationParameters, max, min};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::sphere (float radius, size_t slices, size_t stacks, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Sphere", (std::stringstream{} << radius << ',' << slices << ',' << stacks).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' sphere geometry resource ... ";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float radius, size_t slices, size_t stacks) {
				auto shape = ShapeGenerator::generateSphere(radius, slices, stacks, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Sphere geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a sphere geometry resource !"); 
				}
			}, geometry, m_generationParameters, radius, slices, stacks};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::geodesicSphere (float radius, size_t depth, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("GeodesicSphere", (std::stringstream{} << radius << ',' << depth).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' geodesic sphere geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float radius, size_t depth) {
				auto shape = ShapeGenerator::generateGeodesicSphere(radius, depth, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Geodesic sphere geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a geodesic sphere geometry resource !"); 
				}
			}, geometry, m_generationParameters, radius, depth};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::cylinder (float baseRadius, float topRadius, float length, size_t slices, size_t stacks, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Cylinder", (std::stringstream{} << baseRadius << ',' << topRadius << ',' << length << ',' << slices << ',' << stacks).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' cylinder geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float baseRadius, float topRadius, float length, size_t slices, size_t stacks) {
				auto shape = ShapeGenerator::generateCylinder(baseRadius, topRadius, length, slices, stacks, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Cylinder geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a cylinder geometry resource !"); 
				}
			}, geometry, m_generationParameters, baseRadius, topRadius, length, slices, stacks};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::disk (float outerRadius, float innerRadius, size_t slices, size_t stacks, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{
			resourceName = this->generateResourceName("Disk", (std::stringstream{} << outerRadius << ',' << innerRadius << ',' << slices << ',' << stacks).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' disk geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float outerRadius, float innerRadius, size_t slices, size_t stacks) {
				auto shape = ShapeGenerator::generateDisk(outerRadius, innerRadius, slices, stacks, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Disk geometry resource generated successfully !"); 
				}
				else
				{
					Tracer::error(ClassId, "[Background] Unable to generate a disk geometry resource !"); 
				}
			}, geometry, m_generationParameters, outerRadius, innerRadius, slices, stacks};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::torus (float majorRadius, float minorRadius, size_t slices, size_t stacks, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Torus", (std::stringstream{} << majorRadius << ',' << minorRadius << ',' << slices << ',' << stacks).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' torus geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float majorRadius, float minorRadius, size_t slices, size_t stacks) {
				auto shape = ShapeGenerator::generateTorus(majorRadius, minorRadius, slices, stacks, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Torus geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a torus geometry resource !"); 
				}
			}, geometry, m_generationParameters, majorRadius, minorRadius, slices, stacks};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::tetrahedron (float radius, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Tetrahedron", (std::stringstream{} << radius).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' tetrahedron geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float radius) {
				auto shape = ShapeGenerator::generateTetrahedron(radius, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{
					Tracer::success(ClassId, "[Background] Tetrahedron geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a tetrahedron geometry resource !"); 
				}
			}, geometry, m_generationParameters, radius};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::hexahedron (float radius, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Hexahedron", (std::stringstream{} << radius).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' hexahedron geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float radius) {
				auto shape = ShapeGenerator::generateHexahedron(radius, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Hexahedron geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a hexahedron geometry resource !"); 
				}
			}, geometry, m_generationParameters, radius};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::octahedron (float radius, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Octahedron", (std::stringstream{} << radius).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' octahedron geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float radius) {
				auto shape = ShapeGenerator::generateOctahedron(radius, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Octahedron geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a octahedron geometry resource !"); 
				}
			}, geometry, m_generationParameters, radius};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::dodecahedron (float radius, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{
			resourceName = this->generateResourceName("Dodecahedron", (std::stringstream{} << radius).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' dodecahedron geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float radius) {
				auto shape = ShapeGenerator::generateDodecahedron(radius, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Dodecahedron geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a dodecahedron geometry resource !"); 
				}
			}, geometry, m_generationParameters, radius};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::icosahedron (float radius, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Icosahedron", (std::stringstream{} << radius).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' icosahedron geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float radius) {
				auto shape = ShapeGenerator::generateIcosahedron(radius, parameters.getShapeBuilderOptions());

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Icosahedron geometry resource generated successfully !");
				}
				else
				{
					Tracer::error(ClassId, "[Background] Unable to generate a icosahedron geometry resource !"); 
				}
			}, geometry, m_generationParameters, radius};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::uniformArea (float size, float thickness, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("UniformArea", (std::stringstream{} << size << ',' << thickness).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' uniform area geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float size, float thickness) {
				Shape< float > shape{};

				{
					Shape< float > assembly{};
					Shape< float > part{};

					ShapeBuilderOptions< float > options{};
					options.enableGlobalVertexColor(parameters.globalVertexColor());
					options.enableGlobalNormal(Vector< 3, float >::positiveY());
					options.setTextureCoordinatesMultiplier(parameters.textureCoordinatesMultiplier());
					options.setCenterAtBottom(parameters.isCenteredAtBottom());

					ShapeBuilder builder{part, options};

					const auto Positive = size * 0.5F;
					const auto Negative = -Positive;

					builder.beginConstruction(ConstructionMode::TriangleStrip);

					{
						builder.newVertex(Vector< 3, float >(Negative, Negative, Negative));
						builder.newVertex(Vector< 3, float >(Positive, Negative, Negative));
						builder.newVertex(Vector< 3, float >(Negative+thickness, Negative, Negative+thickness));
						builder.newVertex(Vector< 3, float >(Positive-thickness, Negative, Negative+thickness));

						builder.resetCurrentTriangle();

						builder.newVertex(Vector< 3, float >(Negative+thickness, Negative, Positive-thickness));
						builder.newVertex(Vector< 3, float >(Positive-thickness, Negative, Positive-thickness));
						builder.newVertex(Vector< 3, float >(Negative, Negative, Positive));
						builder.newVertex(Vector< 3, float >(Positive, Negative, Positive));

						builder.resetCurrentTriangle();

						builder.newVertex(Vector< 3, float >(Positive-thickness, Negative, Negative+thickness));
						builder.newVertex(Vector< 3, float >(Positive, Negative, Negative));
						builder.newVertex(Vector< 3, float >(Positive-thickness, Negative, Positive-thickness));
						builder.newVertex(Vector< 3, float >(Positive, Negative, Positive));

						builder.resetCurrentTriangle();

						builder.newVertex(Vector< 3, float >(Negative+thickness, Negative, Positive-thickness));
						builder.newVertex(Vector< 3, float >(Negative, Negative, Positive));
						builder.newVertex(Vector< 3, float >(Negative+thickness, Negative, Negative+thickness));
						builder.newVertex(Vector< 3, float >(Negative, Negative, Negative));

						builder.resetCurrentTriangle();
					}

					{
						builder.newVertex(Vector< 3, float >(Negative+thickness, Positive-thickness, Negative));
						builder.newVertex(Vector< 3, float >(Positive-thickness, Positive-thickness, Negative));
						builder.newVertex(Vector< 3, float >(Negative+thickness, Positive-thickness, Negative+thickness));
						builder.newVertex(Vector< 3, float >(Positive-thickness, Positive-thickness, Negative+thickness));

						builder.resetCurrentTriangle();

						builder.newVertex(Vector< 3, float >(Negative+thickness, Positive-thickness, Positive-thickness));
						builder.newVertex(Vector< 3, float >(Positive-thickness, Positive-thickness, Positive-thickness));
						builder.newVertex(Vector< 3, float >(Negative+thickness, Positive-thickness, Positive));
						builder.newVertex(Vector< 3, float >(Positive-thickness, Positive-thickness, Positive));

						builder.resetCurrentTriangle();

						builder.newVertex(Vector< 3, float >(Positive-thickness, Positive-thickness, Negative+thickness));
						builder.newVertex(Vector< 3, float >(Positive, Positive-thickness, Negative+thickness));
						builder.newVertex(Vector< 3, float >(Positive-thickness, Positive-thickness, Positive-thickness));
						builder.newVertex(Vector< 3, float >(Positive, Positive-thickness, Positive-thickness));

						builder.resetCurrentTriangle();

						builder.newVertex(Vector< 3, float >(Negative+thickness, Positive-thickness, Positive-thickness));
						builder.newVertex(Vector< 3, float >(Negative, Positive-thickness, Positive-thickness));
						builder.newVertex(Vector< 3, float >(Negative+thickness, Positive-thickness, Negative+thickness));
						builder.newVertex(Vector< 3, float >(Negative, Positive-thickness, Negative+thickness));

						builder.resetCurrentTriangle();
					}

					builder.endConstruction();

					ShapeAssembler assembler{assembly};

					/* Assembly */
					assembler.merge(part);
					assembler.merge(part, Matrix< 4, float >::rotation(Radian(QuartRevolution< float >), 1.0F, 0.0F, 0.0F));

					/* Final construction */
					assembler.setDestinationShape(shape);
					assembler.merge(assembly);
					assembler.merge(assembly, Matrix< 4, float >::rotation(Radian(QuartRevolution< float >), 1.0F, 0.0F, 0.0F));
					assembler.merge(assembly, Matrix< 4, float >::rotation(Radian(QuartRevolution< float >), 0.0F, 0.0F, 1.0F));
				}

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Uniform area geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate an uniform area geometry resource !"); 
				}
			}, geometry, m_generationParameters, size, thickness};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::arrow (float size, PointTo pointTo, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Arrow", (std::stringstream{} << size << ',' << static_cast< int >(pointTo)).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' arrow geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float size, PointTo pointTo) {
				const auto arrowLength = 1.0F * size;
				const auto arrowThickness = 0.015F * size;
				const auto arrowCapLength = arrowLength * 0.2F;
				const auto arrowCapThickness = 0.06F * size;
				const auto quality = 8U;
				const auto gape = arrowCapThickness * 0.5F;

				Shape< float > shape{};

				ShapeAssembler assembler{shape};

				ShapeBuilderOptions< float > options{};
				options.enableGlobalVertexColor(parameters.globalVertexColor());
				options.setTextureCoordinatesMultiplier(parameters.textureCoordinatesMultiplier());
				options.setCenterAtBottom(parameters.isCenteredAtBottom());

				const auto translate = Matrix< 4, float >::translation(0.0F, -(gape + arrowLength), 0.0F);

				/* Base arrow. */
				{
					auto chunk = ShapeGenerator::generateCylinder(arrowThickness, arrowThickness, arrowLength, quality, 1, options);

					assembler.merge(chunk, Matrix< 4, float >::translation(0.0F, -gape, 0.0F));
				}

				/* Arrow cap. */
				{
					auto chunk = ShapeGenerator::generateCone(arrowCapThickness, arrowCapLength, quality, 1, options);

					assembler.merge(chunk, translate);
				}

				/* Arrow cap end. */
				{
					options.enableGeometryFlipping(true);

					auto chunk = ShapeGenerator::generateDisk(0.0F, arrowCapThickness, quality, 1, options);

					assembler.merge(chunk, translate);

					options.enableGeometryFlipping(false);
				}

				/* Arrow origin. */
				{
					options.enableGlobalVertexColor(White);

					auto chunk = ShapeGenerator::generateSphere(arrowCapThickness * 0.75F, quality, quality, options); // NOLINT(*-magic-numbers)

					assembler.merge(chunk);
				}

				switch ( pointTo )
				{
					case PointTo::PositiveX :
						shape.transform(Matrix< 4, float >::rotation(Radian(QuartRevolution< float >), 0.0F, 0.0, 1.0F));
						break;

					case PointTo::NegativeX :
						shape.transform(Matrix< 4, float >::rotation(Radian(-QuartRevolution< float >), 0.0F, 0.0, 1.0F));
						break;

					case PointTo::PositiveY :
						shape.transform(Matrix< 4, float >::rotation(Radian(HalfRevolution< float >), 1.0F, 0.0, 0.0F));
						break;

					case PointTo::NegativeY :
						/* Nothing to do, the arrow is built pointing to Y- by default. */
						break;

					case PointTo::PositiveZ :
						shape.transform(Matrix< 4, float >::rotation(Radian(-QuartRevolution< float >), 1.0F, 0.0, 0.0F));
						break;

					case PointTo::NegativeZ :
						shape.transform(Matrix< 4, float >::rotation(Radian(QuartRevolution< float >), 1.0F, 0.0, 0.0F));
						break;
				}

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Arrow geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate an arrow geometry resource !"); 
				}
			}, geometry, m_generationParameters, size, pointTo};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< IndexedVertexResource >
	ResourceGenerator::axis (float size, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Axis", (std::stringstream{} << size).str()); 
		}

		auto geometry = m_indexedVertexGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' axis geometry resource ...";

			std::thread generation{[] (std::shared_ptr< IndexedVertexResource > geometry, GenerationParameters parameters, float size) {
				const auto arrowLength = 1.0F * size;
				const auto arrowThickness = 0.015F * size;
				const auto arrowCapLength = arrowLength * 0.2F;
				const auto arrowCapThickness = 0.06F * size;
				const auto quality = 8U;
				const auto gape = arrowCapThickness * 0.5F;

				Shape< float > shape{};

				ShapeAssembler assembler{shape};

				ShapeBuilderOptions< float > options{};
				options.setTextureCoordinatesMultiplier(parameters.textureCoordinatesMultiplier());
				options.setCenterAtBottom(parameters.isCenteredAtBottom());

				{
					Shape< float > arrow{};

					{
						ShapeAssembler arrowAssembler{arrow};

						const auto translate = Matrix< 4, float >::translation(0.0F, -arrowLength, 0.0F);

						/* Base arrow. */
						{
							auto chunk = ShapeGenerator::generateCylinder(arrowThickness, arrowThickness, arrowLength, quality, 1, options);

							arrowAssembler.merge(chunk, Matrix< 4, float >::translation(0.0F, -gape, 0.0F));
						}

						/* Arrow cap. */
						{
							auto chunk = ShapeGenerator::generateCone(arrowCapThickness, arrowCapLength, quality, 1, options);

							arrowAssembler.merge(chunk, translate);
						}

						/* Arrow cap end. */
						{
							options.enableGeometryFlipping(true);

							auto chunk = ShapeGenerator::generateDisk(0.0F, arrowCapThickness, quality, 1, options);

							options.enableGeometryFlipping(false);

							arrowAssembler.merge(chunk, translate);
						}
					}

					/* Adds the Y+ arrow in green. This should point downward. */
					arrow.setGlobalVertexColor(Green);

					assembler.merge(arrow);

					/* Adds the X+ arrow in red. This should point toward the right. */
					arrow.setGlobalVertexColor(Red);

					assembler.merge(arrow, Matrix< 4, float >::rotation(Radian(QuartRevolution< float >), 0.0F, 0.0, 1.0F));

					/* Adds the Z+ arrow in blue. This should point to camera. */
					arrow.setGlobalVertexColor(Blue);

					assembler.merge(arrow, Matrix< 4, float >::rotation(Radian(-QuartRevolution< float >), 1.0F, 0.0, 0.0F));
				}

				/* Arrow origin. */
				{
					options.enableGlobalVertexColor(White);

					auto chunk = ShapeGenerator::generateSphere(arrowCapThickness * 0.75F, quality, quality, options); // NOLINT(*-magic-numbers)

					assembler.merge(chunk);
				}

				if ( !parameters.transformMatrix().isIdentity() )
				{ 
					shape.transform(parameters.transformMatrix()); 
				}

				if ( geometry->load(shape) )
				{ 
					Tracer::success(ClassId, "[Background] Axis geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate an axis geometry resource !"); 
				}
			}, geometry, m_generationParameters, size};

			generation.detach();
		}

		return geometry;
	}

	std::shared_ptr< VertexGridResource >
	ResourceGenerator::surface (float size, size_t division, std::string resourceName) noexcept
	{
		if ( resourceName.empty() )
		{ 
			resourceName = this->generateResourceName("Surface", (std::stringstream{} << size << ',' << division).str()); 
		}

		auto geometry = m_vertexGridGeometries.getOrCreateResource(resourceName, m_generationParameters.geometryFlags());

		if ( geometry->isUnloaded() )
		{
			TraceInfo{ClassId} << "Generating '" << resourceName << "' surface grid geometry resource ...";

			std::thread generation{[] (std::shared_ptr< VertexGridResource > geometry, GenerationParameters parameters, float size, size_t division) {
				if ( geometry->load(size, division, parameters.textureCoordinatesMultiplier()[X]) )
				{ 
					Tracer::success(ClassId, "[Background] Surface grid geometry resource generated successfully !"); 
				}
				else
				{ 
					Tracer::error(ClassId, "[Background] Unable to generate a surface grid geometry resource !"); 
				}
			}, geometry, m_generationParameters, size, division};

			generation.detach();
		}

		return geometry;
	}

	std::string
	ResourceGenerator::generateResourceName (const char * type, const std::string & values) const noexcept
	{
		return (std::stringstream{} << '+' << type << '(' << Hash::md5(m_generationParameters.uniqueIdentifier() + '-' + values) << ')').str();
	}
}
