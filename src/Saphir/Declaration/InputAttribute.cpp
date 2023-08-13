/*
 * Emeraude/Saphir/Declaration/InputAttribute.cpp
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

#include "InputAttribute.hpp"

/* C/C++ standard libraries. */
#include <sstream>

namespace Emeraude::Saphir::Declaration
{
	using namespace Keys;
	using namespace Graphics;

	Key
	getVertexAttributeVariableType (VertexAttributeType vertexAttribute) noexcept
	{
		switch ( vertexAttribute )
		{
			case VertexAttributeType::VertexColor :
				return GLSL::FloatVector4;

			case VertexAttributeType::Position :
			case VertexAttributeType::Binormal :
			case VertexAttributeType::Tangent :
			case VertexAttributeType::Normal :
			case VertexAttributeType::Primary3DTextureCoordinates :
			case VertexAttributeType::Secondary3DTextureCoordinates :
				return GLSL::FloatVector3;

			case VertexAttributeType::Primary2DTextureCoordinates :
			case VertexAttributeType::Secondary2DTextureCoordinates :
				return GLSL::FloatVector2;

			case VertexAttributeType::ModelMatrixR0 :
			case VertexAttributeType::ModelMatrixR1 :
			case VertexAttributeType::ModelMatrixR2 :
			case VertexAttributeType::ModelMatrixR3 :
				return GLSL::Matrix4;

			case VertexAttributeType::NormalModelMatrixR0 :
			case VertexAttributeType::NormalModelMatrixR1 :
			case VertexAttributeType::NormalModelMatrixR2 :
				return GLSL::Matrix3;

			default:
				return nullptr;
		}
	}

	Key
	getVertexAttributeVariableName (VertexAttributeType vertexAttribute) noexcept
	{
		switch ( vertexAttribute )
		{
			case VertexAttributeType::Position :
				return Attributes::Position;

			case VertexAttributeType::Binormal :
				return Attributes::Binormal;

			case VertexAttributeType::Tangent :
				return Attributes::Tangent;

			case VertexAttributeType::Normal :
				return Attributes::Normal;

			case VertexAttributeType::VertexColor :
				return Attributes::Color;

			case VertexAttributeType::Primary2DTextureCoordinates :
				return Attributes::Primary2DTextureCoordinates;

			case VertexAttributeType::Primary3DTextureCoordinates :
				return Attributes::Primary3DTextureCoordinates;

			case VertexAttributeType::Secondary2DTextureCoordinates :
				return Attributes::Secondary2DTextureCoordinates;

			case VertexAttributeType::Secondary3DTextureCoordinates :
				return Attributes::Secondary3DTextureCoordinates;

			case VertexAttributeType::ModelMatrixR0 :
			case VertexAttributeType::ModelMatrixR1 :
			case VertexAttributeType::ModelMatrixR2 :
			case VertexAttributeType::ModelMatrixR3 :
				return Attributes::ModelMatrix;

			case VertexAttributeType::NormalModelMatrixR0 :
			case VertexAttributeType::NormalModelMatrixR1 :
			case VertexAttributeType::NormalModelMatrixR2 :
				return Attributes::NormalModelMatrix;

			default:
				return nullptr;
		}
	}

	InputAttribute::InputAttribute (VertexAttributeType vertexAttribute) noexcept
		: m_location(static_cast< uint32_t >(vertexAttribute)),
		  m_type(getVertexAttributeVariableType(vertexAttribute)),
		  m_name(getVertexAttributeVariableName(vertexAttribute))
	{

	}

	InputAttribute::InputAttribute (VertexAttributeType vertexAttribute, Key type) noexcept
		: m_location(static_cast< uint32_t >(vertexAttribute)),
		  m_type(type),
		  m_name(getVertexAttributeVariableName(vertexAttribute))
	{

	}

	InputAttribute::InputAttribute (uint32_t location, Key type, Key name, size_t arraySize) noexcept
		: m_location(location),
		m_type(type),
		m_name(name),
		m_arraySize(arraySize)
	{

	}

	bool
	InputAttribute::isValid () const noexcept
	{
		if ( m_type == nullptr || m_name == nullptr )
			return false;

		return true;
	}

	std::string
	InputAttribute::sourceCode () const noexcept
	{
		std::stringstream code{};

		code <<
			GLSL::Layout << " (" << GLSL::Location << " = " << std::to_string(m_location) << ") " <<
			GLSL::In << ' ' << m_type << ' ' << m_name;

		if ( m_arraySize > 0 )
		{
			code << '[' << m_arraySize << ']';
		}

		code << ";" "\n";

		return code.str();
	}

	Key
	InputAttribute::name () const noexcept
	{
		return m_name;
	}

	size_t
	InputAttribute::bytes () const noexcept
	{
		return 0;
	}

	uint32_t
	InputAttribute::location () const noexcept
	{
		return m_location;
	}

	Key
	InputAttribute::type () const noexcept
	{
		return m_type;
	}

	size_t
	InputAttribute::arraySize () const noexcept
	{
		return m_arraySize;
	}

	bool
	InputAttribute::isModelMatricesVBOAttribute () const noexcept
	{
		if ( to_string(VertexAttributeType::ModelMatrixR0) == m_name )
			return true;

		if ( to_string(VertexAttributeType::NormalModelMatrixR0) == m_name )
			return true;

		return false;
	}
}
