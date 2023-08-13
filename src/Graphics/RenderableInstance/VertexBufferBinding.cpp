/*
 * Emeraude/Graphics/RenderableInstance/VertexBufferBinding.cpp
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

#include "VertexBufferBinding.hpp"

namespace Emeraude::Graphics
{
	VertexBufferBinding::VertexBufferBinding (uint32_t binding, size_t elementCount, Topology topology, uint32_t bufferFlags) noexcept
		: FlagTrait(bufferFlags), m_binding(binding), m_elementCount(elementCount), m_topology(topology)
	{

	}

	bool
	VertexBufferBinding::operator== (const VertexBufferBinding & operand) const noexcept
	{
		if ( this != &operand )
		{
			if ( m_binding != operand.m_binding )
				return false;

			if ( m_elementCount != operand.m_elementCount )
				return false;

			if ( m_topology != operand.m_topology )
				return false;

			if ( this->flagBits() != operand.flagBits() )
				return false;
		}

		return true;
	}

	bool
	VertexBufferBinding::operator!= (const VertexBufferBinding & operand) const noexcept
	{
		return !this->operator==(operand);
	}

	size_t
	VertexBufferBinding::elementCount () const noexcept
	{
		return m_elementCount;
	}

	size_t
	VertexBufferBinding::size () const noexcept
	{
		return m_elementCount * sizeof(float);
	}

	Topology
	VertexBufferBinding::topology () const noexcept
	{
		return m_topology;
	}

	std::ostream &
	operator<< (std::ostream & out, const VertexBufferBinding & obj)
	{
		return out << obj.ClassId << ". "
			"Binding: " << obj.m_binding << ", "
			"Element count: " << obj.m_elementCount << ", "
			"Topology: " << to_string(obj.m_topology) << ", "
			"Per instance: " << ( obj.perInstance() ? "yes" : "no" ) << ", "
			"Request primitive restart: " << ( obj.requestPrimitiveRestart() ? "yes" : "no" ) << ", "
			"Is position absolute: " << ( obj.isPositionAbsolute() ? "yes" : "no" ) << ", "
			"Is dynamic vertex buffer: " << ( obj.isDynamicVertexBuffer() ? "yes" : "no" );
	}

	std::string
	to_string (const VertexBufferBinding & obj) noexcept
	{
		return (std::stringstream{} << obj).str();
	}
}
