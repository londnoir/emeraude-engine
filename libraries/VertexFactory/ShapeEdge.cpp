/*
 * Libraries/VertexFactory/ShapeEdge.cpp
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

#include "ShapeEdge.hpp"

namespace Libraries::VertexFactory
{
	ShapeEdge::ShapeEdge (size_t vertexIndexA, size_t vertexIndexB) noexcept
		: m_vertexIndexA(vertexIndexA), m_vertexIndexB(vertexIndexB)
	{

	}

	bool
	ShapeEdge::operator== (const ShapeEdge & operand) const noexcept
	{
		if ( this != &operand )
		{
			if ( m_vertexIndexA == operand.m_vertexIndexA && m_vertexIndexB == operand.m_vertexIndexB )
				return true;

			if ( m_vertexIndexA == operand.m_vertexIndexB && m_vertexIndexB == operand.m_vertexIndexA )
				return true;
		}

		return false;
	}

	bool
	ShapeEdge::operator!= (const ShapeEdge & operand) const noexcept
	{
		return !this->operator==(operand);
	}

	void
	ShapeEdge::setSharedIndex (size_t index) noexcept
	{
		m_sharedEdgeIndex = index;
	}

	bool
	ShapeEdge::isValid () const noexcept
	{
		return m_vertexIndexA != m_vertexIndexB;
	}

	size_t
	ShapeEdge::vertexIndexA () const noexcept
	{
		return m_vertexIndexA;
	}

	size_t
	ShapeEdge::vertexIndexB () const noexcept
	{
		return m_vertexIndexB;
	}

	size_t
	ShapeEdge::sharedIndex () const noexcept
	{
		return m_sharedEdgeIndex;
	}

	bool
	ShapeEdge::same (size_t a, size_t b) const noexcept
	{
		if ( a == m_vertexIndexA && b == m_vertexIndexB )
			return true;

		if ( a == m_vertexIndexB && b == m_vertexIndexA )
			return true;

		return false;
	}
}
