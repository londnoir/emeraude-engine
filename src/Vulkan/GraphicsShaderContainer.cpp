/*
 * Emeraude/Vulkan/GraphicsShaderContainer.cpp
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

#include "GraphicsShaderContainer.hpp"

/* Local inclusions. */
#include "Tracer.hpp"

namespace Emeraude::Vulkan
{
	using namespace Saphir;

	std::shared_ptr< VertexShader >
	GraphicsShaderContainer::initVertexShader (const std::string & name) noexcept
	{
		if ( m_vertexShader != nullptr )
		{
			Tracer::error(ClassId, "The vertex shader is already initialized !");

			return nullptr;
		}

		m_vertexShader = std::make_shared< VertexShader >(name);

		return m_vertexShader;
	}

	std::shared_ptr< TesselationControlShader >
	GraphicsShaderContainer::initTesselationControlShader (const std::string & name) noexcept
	{
		if ( m_tesselationControlShader != nullptr )
		{
			Tracer::error(ClassId, "The tesselation control shader is already initialized !");

			return nullptr;
		}

		m_tesselationControlShader = std::make_shared< TesselationControlShader >(name);

		return m_tesselationControlShader;
	}

	std::shared_ptr< TesselationEvaluationShader >
	GraphicsShaderContainer::initTesselationEvaluationShader (const std::string & name) noexcept
	{
		if ( m_tesselationEvaluationShader != nullptr )
		{
			Tracer::error(ClassId, "The tesselation evaluation shader is already initialized !");

			return nullptr;
		}

		m_tesselationEvaluationShader = std::make_shared< TesselationEvaluationShader >(name);

		return m_tesselationEvaluationShader;
	}

	std::shared_ptr< GeometryShader >
	GraphicsShaderContainer::initGeometryShader (const std::string & name) noexcept
	{
		if ( m_geometryShader != nullptr )
		{
			Tracer::error(ClassId, "The geometry shader is already initialized !");

			return nullptr;
		}

		m_geometryShader = std::make_shared< GeometryShader >(name);

		return m_geometryShader;
	}

	std::shared_ptr< FragmentShader >
	GraphicsShaderContainer::initFragmentShader (const std::string & name) noexcept
	{
		if ( m_fragmentShader != nullptr )
		{
			Tracer::error(ClassId, "The fragment shader is already initialized !");

			return nullptr;
		}

		m_fragmentShader = std::make_shared< FragmentShader >(name);

		return m_fragmentShader;
	}

	std::shared_ptr< Saphir::VertexShader >
	GraphicsShaderContainer::vertexShader () const noexcept
	{
		return m_vertexShader;
	}

	std::shared_ptr< Saphir::TesselationControlShader >
	GraphicsShaderContainer::tesselationControlShader () const noexcept
	{
		return m_tesselationControlShader;
	}

	std::shared_ptr< Saphir::TesselationEvaluationShader >
	GraphicsShaderContainer::tesselationEvaluationShader () const noexcept
	{
		return m_tesselationEvaluationShader;
	}

	std::shared_ptr< Saphir::GeometryShader >
	GraphicsShaderContainer::geometryShader () const noexcept
	{
		return m_geometryShader;
	}

	std::shared_ptr< Saphir::FragmentShader >
	GraphicsShaderContainer::fragmentShader () const noexcept
	{
		return m_fragmentShader;
	}

	std::vector< std::shared_ptr< Saphir::AbstractShader > >
	GraphicsShaderContainer::getShaderList () const noexcept
	{
		std::vector< std::shared_ptr< Saphir::AbstractShader > > list{};

		if ( m_vertexShader != nullptr )
		{
			list.emplace_back(m_vertexShader);
		}

		if ( m_tesselationControlShader != nullptr )
		{
			list.emplace_back(m_tesselationControlShader);
		}

		if ( m_tesselationEvaluationShader != nullptr )
		{
			list.emplace_back(m_tesselationEvaluationShader);
		}

		if ( m_geometryShader != nullptr )
		{
			list.emplace_back(m_geometryShader);
		}

		if ( m_fragmentShader != nullptr )
		{
			list.emplace_back(m_fragmentShader);
		}

		return list;
	}
}
