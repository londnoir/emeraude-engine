/*
 * Emeraude/Graphics/Renderable/AbstractBackground.cpp
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

#include "AbstractBackground.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "Graphics/RenderTarget/View/Texture2D.hpp"
#include "VertexFactory/ShapeGenerator.hpp"

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

	void
	AbstractBackground::setReadyForInstanciation (bool state) noexcept
	{
		if ( state )
			this->enableFlag(IsReadyForInstanciation);
		else
			this->disableFlag(IsReadyForInstanciation);
	}

	bool
	AbstractBackground::isReadyForInstantiation () const noexcept
	{
		return this->isFlagEnabled(IsReadyForInstanciation);
	}

	const Libraries::Math::Cuboid< float > &
	AbstractBackground::boundingBox () const noexcept
	{
		return Interface::NullBoundingBox;
	}

	const Libraries::Math::Sphere< float > &
	AbstractBackground::boundingSphere () const noexcept
	{
		return Interface::NullBoundingSphere;
	}

	int
	AbstractBackground::flags (size_t) const noexcept
	{
		return m_renderableFlags;
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
	AbstractBackground::getSkyboxGeometry () noexcept
	{
		auto & geometries = Resources::Manager::instance()->indexedVertexGeometries();

		if ( geometries.isResourceAvailable(SkyBoxGeometryName) )
			return geometries.getResource(SkyBoxGeometryName);

		ShapeBuilderOptions< float > options{};
		options.enableGeometryFlipping(true);

		const auto shape = ShapeGenerator::generateCuboid(SkySize, SkySize, SkySize, options);

		auto geometry = std::make_shared< Geometry::IndexedVertexResource >(SkyBoxGeometryName);

		if ( !geometry->load(shape) )
			return nullptr;

		geometries.addResource(geometry);

		return geometry;
	}

	std::shared_ptr< Geometry::IndexedVertexResource >
	AbstractBackground::getSkydomeGeometry () noexcept
	{
		auto & geometries = Resources::Manager::instance()->indexedVertexGeometries();

		if ( geometries.isResourceAvailable(DomeGeometryName) )
			return geometries.getResource(DomeGeometryName);

		ShapeBuilderOptions< float > options{};
		options.enableGeometryFlipping(true);

		const auto shape = ShapeGenerator::generateSphere(SkySize, 16, 16, options);

		auto geometry = std::make_shared< Geometry::IndexedVertexResource >(SkyBoxGeometryName);

		if ( !geometry->load(shape) )
			return nullptr;

		geometries.addResource(geometry);

		return geometry;
	}
}
