/*
 * Emeraude/Graphics/Renderable/SimpleMeshResource.cpp
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

#include "SimpleMeshResource.hpp"

/* Local inclusion */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Renderable::SimpleMeshResource >::ClassId{"SimpleMeshContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Renderable::SimpleMeshResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;

	const size_t SimpleMeshResource::ClassUID{Observable::getClassUID()};

	SimpleMeshResource::SimpleMeshResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	bool
	SimpleMeshResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	void
	SimpleMeshResource::setReadyForInstanciation (bool state) noexcept
	{
		if ( state )
			this->enableFlag(IsReadyForInstanciation);
		else
			this->disableFlag(IsReadyForInstanciation);
	}

	bool
	SimpleMeshResource::isReadyForInstantiation () const noexcept
	{
		return this->isFlagEnabled(IsReadyForInstanciation);
	}

	size_t
	SimpleMeshResource::layerCount () const noexcept
	{
		return 1;
	}

	bool
	SimpleMeshResource::isOpaque (size_t) const noexcept
	{
		return true;
	}

	const Geometry::Interface *
	SimpleMeshResource::geometry () const noexcept
	{
		return m_geometry.get();
	}

	const Material::Interface *
	SimpleMeshResource::material (size_t) const noexcept
	{
		return m_material.get();
	}

	const Cuboid< float > &
	SimpleMeshResource::boundingBox () const noexcept
	{
		if ( m_geometry == nullptr )
			return Interface::NullBoundingBox;

		return m_geometry->boundingBox();
	}

	const Sphere< float > &
	SimpleMeshResource::boundingSphere () const noexcept
	{
		if ( m_geometry == nullptr )
			return Interface::NullBoundingSphere;

		return m_geometry->boundingSphere();
	}

	int
	SimpleMeshResource::flags (size_t) const noexcept
	{
		return m_renderableFlags;
	}

	const char *
	SimpleMeshResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	SimpleMeshResource::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !this->setGeometry(Geometry::VertexResource::getDefault()) )
			return this->setLoadSuccess(false);

		if ( !this->setMaterial(Material::BasicResource::getDefault()) )
			return this->setLoadSuccess(false);

		return this->setLoadSuccess(true);
	}

	bool
	SimpleMeshResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		Tracer::warning(ClassId, "FIXME: This function is not available yet !");

		return this->setLoadSuccess(false);
	}

	bool
	SimpleMeshResource::load (const std::shared_ptr< Geometry::Interface > & geometry, const std::shared_ptr< Material::Interface > & material) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		if ( !this->setGeometry(geometry) )
			return this->setLoadSuccess(false);

		if ( material != nullptr )
		{
			if ( !this->setMaterial(material) )
				return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	SimpleMeshResource::setGeometry (const std::shared_ptr< Geometry::Interface > & geometryResource) noexcept
	{
		if ( geometryResource == nullptr )
		{
			TraceError{ClassId} <<
				"The geometry resource is null ! "
				"Unable to attach it to the renderable object '" << this->name() << "' " << this << ".";

			return false;
		}

		this->setReadyForInstanciation(false);

		m_geometry = geometryResource;

		return this->addDependency(m_geometry.get());
	}

	bool
	SimpleMeshResource::setMaterial (const std::shared_ptr< Material::Interface > & materialResource) noexcept
	{
		if ( materialResource == nullptr )
		{
			TraceError{ClassId} <<
				"The material resource is null ! "
				"Unable to attach it to the renderable object '" << this->name() << "' " << this << ".";

			return false;
		}

		this->setReadyForInstanciation(false);

		m_material = materialResource;

		return this->addDependency(m_material.get());
	}

	bool
	SimpleMeshResource::prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept
	{
		TraceWarning{ClassId} << "Not done yet !";

		return false;
	}

	std::shared_ptr< SimpleMeshResource >
	SimpleMeshResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->simpleMeshes().getResource(resourceName, directLoad);
	}

	std::shared_ptr< SimpleMeshResource >
	SimpleMeshResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->simpleMeshes().getDefaultResource();
	}
}
