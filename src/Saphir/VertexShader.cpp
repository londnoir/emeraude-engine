/*
 * Emeraude/Saphir/VertexShader.cpp
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

#include "VertexShader.hpp"

namespace Emeraude::Saphir
{
	VertexShader::VertexShader (const std::string & name) noexcept
		: AbstractShader(name)
	{

	}

	ShaderType
	VertexShader::type () const noexcept
	{
		return ShaderType::VertexShader;
	}

	const std::set< Graphics::VertexAttributeType > &
	VertexShader::vertexAttributes () const noexcept
	{
		return m_vertexAttributes;
	}

	bool
	VertexShader::declareAttribute (const Graphics::VertexAttributeType & vertexAttribute) noexcept
	{
		return m_vertexAttributes.emplace(vertexAttribute).second;
	}

	void
	VertexShader::enableInstancing () noexcept
	{
		m_instancingEnabled = true;
	}

	bool
	VertexShader::instancingEnabled () const noexcept
	{
		return m_instancingEnabled;
	}
}
