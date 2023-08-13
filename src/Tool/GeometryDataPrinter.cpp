/*
 * Emeraude/Tool/GeometryDataPrinter.cpp
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

#include "GeometryDataPrinter.hpp"

/* C/C++ standard libraries. */
#include <iostream>
#include <fstream>

/* Local inclusions. */
#include "Tracer.hpp"
#include "Arguments.hpp"
#include "String.hpp"
#include "VertexFactory/ShapeGenerator.hpp"

namespace Emeraude::Tool
{
	using namespace Libraries;
	using namespace Graphics;

	GeometryDataPrinter::GeometryDataPrinter (const Arguments & arguments) noexcept
		: m_arguments(arguments)
	{
		{
			const auto arg = arguments.get("--output-file", "-o");

			if ( arg.isPresent() )
			{
				m_outputFile = arg.value();
			}
		}

		{
			const auto arg = arguments.get("--shape");

			if ( arg.isPresent() )
			{
				m_shapeType = to_ShapeType(String::ucfirst(arg.value()));
			}
		}

		{
			const auto arg = arguments.get("--size");

			if ( arg.isPresent() )
			{
				m_baseSize = String::toNumber< float >(arg.value());
			}
		}

		{
			const auto arg = arguments.get("--length");

			if ( arg.isPresent() )
			{
				m_baseLength = String::toNumber< float >(arg.value());
			}
		}

		{
			const auto arg = arguments.get("--quality");

			if ( arg.isPresent() )
			{
				m_quality = String::toNumber< uint64_t >(arg.value());
			}
		}

		m_flags[EnableNormals] = arguments.get("--enable-normals").isPresent();
		m_flags[EnableTangentSpace] = arguments.get("--enable-tangent-space").isPresent();
		m_flags[EnableTexCoords] = arguments.get("--enable-tex-coords").isPresent();
		m_flags[Enable3DTexCoords] = arguments.get("--enable-3d-tex-coords").isPresent();
	}

	bool
	GeometryDataPrinter::execute () noexcept
	{
		Tracer::info(ClassId, "Execution shape generation ...");

		switch ( m_shapeType )
		{
			case ShapeType::Triangle :
				m_shape = VertexFactory::ShapeGenerator::generateTriangle(m_baseSize);
				break;

			case ShapeType::Quad :
				m_shape = VertexFactory::ShapeGenerator::generateQuad(m_baseSize);
				break;

			case ShapeType::Cube :
				m_shape = VertexFactory::ShapeGenerator::generateCuboid(m_baseSize);
				break;

			case ShapeType::Sphere :
				m_shape = VertexFactory::ShapeGenerator::generateSphere(m_baseSize, m_quality, m_quality);
				break;

			case ShapeType::GeodesicSphere :
				m_shape = VertexFactory::ShapeGenerator::generateGeodesicSphere(m_baseSize, m_quality);
				break;

			case ShapeType::Cylinder :
				m_shape = VertexFactory::ShapeGenerator::generateCylinder(m_baseSize, m_baseSize, m_baseLength, m_quality);
				break;

			case ShapeType::Cone :
				m_shape = VertexFactory::ShapeGenerator::generateCone(m_baseSize, m_baseLength, m_quality);
				break;

			case ShapeType::Disk :
				m_shape = VertexFactory::ShapeGenerator::generateDisk(m_baseSize, m_baseSize * 0.5F, m_quality);
				break;

			case ShapeType::Torus :
				m_shape = VertexFactory::ShapeGenerator::generateTorus(m_baseSize, m_baseSize * 0.5F, m_quality, m_quality);
				break;

			case ShapeType::Tetrahedron :
				m_shape = VertexFactory::ShapeGenerator::generateTetrahedron(m_baseSize);
				break;

			case ShapeType::Hexahedron :
				m_shape = VertexFactory::ShapeGenerator::generateHexahedron(m_baseSize);
				break;

			case ShapeType::Octahedron :
				m_shape = VertexFactory::ShapeGenerator::generateOctahedron(m_baseSize);
				break;

			case ShapeType::Dodecahedron :
				m_shape = VertexFactory::ShapeGenerator::generateDodecahedron(m_baseSize);
				break;

			case ShapeType::Icosahedron :
				m_shape = VertexFactory::ShapeGenerator::generateIcosahedron(m_baseSize);
				break;

			case ShapeType::Custom :
			case ShapeType::Arrow :
			case ShapeType::Axis :
				TraceWarning{ClassId} << "The shape '" << to_cstring(m_shapeType) << "' is not handled !";
				return false;
		}

		if ( !m_shape.isValid() )
		{
			Tracer::error(ClassId, "Invalid shape produced !");

			return false;
		}

		if ( m_outputFile.empty() )
		{
			std::cout <<
				"\n\n" <<
				this->printVertices() <<
				this->printIndices() <<
				"\n\n";
		}
		else
		{
			std::ofstream out{m_outputFile};

			if ( !out.is_open() )
			{
				TraceError{ClassId} << "Unable to open file '" << m_outputFile << "' !";

				return false;
			}

			out <<
				"#pragma once" "\n\n"

				"#include <cstddef>" "\n"
				"#include <array>" "\n\n";

			out << this->printVertices() << this->printIndices();

			out.close();
		}

		Tracer::instance()->enableTracing(false);

		return true;
	}

	std::string
	GeometryDataPrinter::printVertices () const noexcept
	{
		std::vector< float > vertices{};

		const auto vertexElementCount = m_shape.createVerticesBuffer(
			vertices,
			3,
			m_flags[EnableNormals] ? 3 : 0,
			m_flags[EnableTangentSpace],
			m_flags[EnableTexCoords] ? (m_flags[Enable3DTexCoords] ? 3 : 2) : 0,
			0
		);

		std::stringstream out{};

		out <<
			"const size_t vertexElementCount = " << vertexElementCount << ";" "\n"
			"const size_t vertexCount = " << m_shape.vertexCount() << ";" "\n\n"

			"const std::array< float, " << vertexElementCount * m_shape.vertexCount() << " > vertices{" "\n";

		for ( size_t index = 0; index < vertices.size(); index += vertexElementCount )
		{
			out << '\t';

			for ( size_t elementIndex = 0; elementIndex < vertexElementCount; elementIndex++ )
			{
				out << vertices[index + elementIndex] << ", ";
			}

			out << '\n';
		}

		out << "};\n\n";

		return out.str();
	}

	std::string
	GeometryDataPrinter::printIndices () const noexcept
	{
		std::vector< size_t > indices{};

		m_shape.createIndicesBuffer(indices);

		std::stringstream out{};

		out << "const std::array< size_t, " << indices.size() << " > indices{" "\n";

		for ( size_t index = 0; index < indices.size(); index += 3 )
		{
			out << '\t';

			for ( size_t elementIndex = 0; elementIndex < 3; elementIndex++ )
			{
				out << indices[index + elementIndex] << ", ";
			}

			out << '\n';
		}

		out << "};\n\n";

		return out.str();
	}
}
