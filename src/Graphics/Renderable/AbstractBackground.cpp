/*
 * src/Graphics/Renderable/AbstractBackground.cpp
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

#include "AbstractBackground.hpp"

/* Local inclusions. */
#include "Libraries/VertexFactory/ShapeGenerator.hpp"
#include "Resources/Manager.hpp"

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::PixelFactory;
	using namespace Libraries::VertexFactory;

	AbstractBackground::AbstractBackground (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	const Cuboid< float > &
	AbstractBackground::boundingBox () const noexcept
	{
		return NullBoundingBox;
	}

	const Sphere< float > &
	AbstractBackground::boundingSphere () const noexcept
	{
		return NullBoundingSphere;
	}

	void
	AbstractBackground::setAverageColor (const Color< float > & color) noexcept
	{
		m_averageColor = color;
	}

	void
	AbstractBackground::setLightPosition (const Vector< 3, float > & position) noexcept
	{
		m_lightPosition = position;
	}

	void
	AbstractBackground::setLightAmbientColor (const Color< float > & color) noexcept
	{
		m_lightAmbientColor = color;
	}

	void
	AbstractBackground::setLightDiffuseColor (const Color< float > & color) noexcept
	{
		m_lightDiffuseColor = color;
	}

	void
	AbstractBackground::setLightSpecularColor (const Color< float > & color) noexcept
	{
		m_lightSpecularColor = color;
	}

	const Color< float > &
	AbstractBackground::averageColor () const noexcept
	{
		return m_averageColor;
	}

	const Vector< 3, float > &
	AbstractBackground::lightPosition () const noexcept
	{
		return m_lightPosition;
	}

	const Color< float > &
	AbstractBackground::lightAmbientColor () const noexcept
	{
		return m_lightAmbientColor;
	}

	const Color< float > &
	AbstractBackground::lightDiffuseColor () const noexcept
	{
		return m_lightDiffuseColor;
	}

	const Color< float > &
	AbstractBackground::lightSpecularColor () const noexcept
	{
		return m_lightSpecularColor;
	}

	std::shared_ptr< Geometry::IndexedVertexResource >
	AbstractBackground::getSkyBoxGeometry () noexcept
	{
		auto & geometries = Resources::Manager::instance()->indexedVertexGeometries();

		if ( geometries.isResourceLoaded(SkyBoxGeometryName) )
		{
			return geometries.getResource(SkyBoxGeometryName);
		}

		ShapeBuilderOptions< float > options{};
		options.enableGeometryFlipping(true);

		const auto shape = ShapeGenerator::generateCuboid(SkySize, SkySize, SkySize, options);

		auto geometry = std::make_shared< Geometry::IndexedVertexResource >(SkyBoxGeometryName);

		if ( !geometry->load(shape) )
		{
			return nullptr;
		}

		geometries.addResource(geometry);

		return geometry;
	}

	std::shared_ptr< Geometry::IndexedVertexResource >
	AbstractBackground::getSkyDomeGeometry () noexcept
	{
		auto & geometries = Resources::Manager::instance()->indexedVertexGeometries();

		if ( geometries.isResourceLoaded(SkyDomeGeometryName) )
		{
			return geometries.getResource(SkyDomeGeometryName);
		}

		ShapeBuilderOptions< float > options{};
		options.enableGeometryFlipping(true);

		const auto shape = ShapeGenerator::generateSphere(SkySize, 16, 16, options);

		auto geometry = std::make_shared< Geometry::IndexedVertexResource >(SkyBoxGeometryName);

		if ( !geometry->load(shape) )
		{
			return nullptr;
		}

		geometries.addResource(geometry);

		return geometry;
	}
}
