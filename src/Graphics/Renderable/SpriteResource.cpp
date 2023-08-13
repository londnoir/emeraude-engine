/*
 * Emeraude/Graphics/Renderable/SpriteResource.cpp
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

#include "SpriteResource.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include "Resources/Manager.hpp"
#include "VertexFactory/ShapeGenerator.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Graphics::Renderable::SpriteResource >::ClassId{"SpriteContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Graphics::Renderable::SpriteResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Graphics::Renderable
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Libraries::VertexFactory;
	using namespace Saphir;
	using namespace Saphir::Keys;

	const size_t SpriteResource::ClassUID{Observable::getClassUID()};

	SpriteResource::SpriteResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: Interface(name, resourceFlagBits)
	{

	}

	bool
	SpriteResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	void
	SpriteResource::setReadyForInstanciation (bool state) noexcept
	{
		if ( state )
			this->enableFlag(IsReadyForInstanciation);
		else
			this->disableFlag(IsReadyForInstanciation);
	}

	bool
	SpriteResource::isReadyForInstantiation () const noexcept
	{
		return this->isFlagEnabled(IsReadyForInstanciation);
	}

	size_t
	SpriteResource::layerCount () const noexcept
	{
		return 1;
	}

	bool
	SpriteResource::isOpaque (size_t) const noexcept
	{
		if ( m_material != nullptr )
			return m_material->isOpaque();

		return true;
	}

	const Geometry::Interface *
	SpriteResource::geometry () const noexcept
	{
		return m_geometry.get();
	}

	const Material::Interface *
	SpriteResource::material (size_t) const noexcept
	{
		return m_material.get();
	}

	const Cuboid< float > &
	SpriteResource::boundingBox () const noexcept
	{
		if ( m_geometry == nullptr )
			return Interface::NullBoundingBox;

		return m_geometry->boundingBox();
	}

	const Sphere< float > &
	SpriteResource::boundingSphere () const noexcept
	{
		if ( m_geometry == nullptr )
			return Interface::NullBoundingSphere;

		return m_geometry->boundingSphere();
	}

	int
	SpriteResource::flags (size_t) const noexcept
	{
		return m_renderableFlags;
	}

	void
	SpriteResource::setSize (float value) noexcept
	{
		m_size = value;
	}

	float
	SpriteResource::size () const noexcept
	{
		return m_size;
	}

	float
	SpriteResource::duration () const noexcept
	{
		if ( m_material == nullptr )
		{
			Tracer::warning(ClassId, "Material is not yet loaded ! Unable to get the Sprite duration.");

			return 0.0F;
		}

		return m_material->duration();
	}

	size_t
	SpriteResource::frameCount () const noexcept
	{
		if ( m_material == nullptr )
		{
			Tracer::warning(ClassId, "Material is not yet loaded ! Unable to get the Sprite frame count.");

			return 1;
		}

		return m_material->frameCount();
	}

	const char *
	SpriteResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	SpriteResource::load () noexcept
	{
		if ( !this->beginLoading() )
			return false;

		this->setReadyForInstanciation(false);

		/* Checks the quad geometry. */
		if ( !this->loadGeometry(CenteredQuadGeometryName) )
		{
			Tracer::error(ClassId, "Unable to get default Geometry to generate the default Sprite !");

			return this->setLoadSuccess(false);
		}

		if ( !this->setMaterial(Material::BasicResource::getDefault()) )
			return this->setLoadSuccess(false);

		/* Checks if all is loaded */
		return this->setLoadSuccess(this->addDependency(m_material.get()));
	}

	bool
	SpriteResource::load (const Json::Value & data) noexcept
	{
		if ( !this->beginLoading() )
			return false;

		this->setReadyForInstanciation(false);

		auto centerAtBottom = false;

		/* Gets Sprite options. */
		if ( data.isMember(SizeKey) )
		{
			if ( data[SizeKey].isNumeric() )
				m_size = data[SizeKey].asFloat();
			else
				TraceError{ClassId} << "The '" << SizeKey << "' key in Sprite definition must be a float !";
		}

		if ( data.isMember(CenterAtBottomKey) )
		{
			if ( data[CenterAtBottomKey].isBool() )
				centerAtBottom = data[CenterAtBottomKey].asBool();
			else
				TraceError{ClassId} << "The '" << CenterAtBottomKey << "' key in Sprite definition must be a boolean !";
		}

		/* Checks the quad geometry. */
		if ( !this->loadGeometry(centerAtBottom ? BottomQuadGeometryName : CenteredQuadGeometryName) )
		{
			Tracer::error(ClassId, "Unable to get default Geometry to generate the default Sprite !");

			return this->setLoadSuccess(false);
		}

		/* Creates and load material. */
		auto materialName = this->name() + "Material";

		auto materialResource = Resources::Manager::instance()
			->basicMaterials()
			.createResource(materialName);

		if ( !this->setMaterial(materialResource) )
		{
			TraceError{ClassId} << "Unable to load SpriteMaterial '" << materialName << "' !";

			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	SpriteResource::loadGeometry (const char * const geometryName) noexcept
	{
		auto & geometries = Resources::Manager::instance()->indexedVertexGeometries();

		if ( geometries.isResourceAvailable(geometryName) )
			return this->setGeometry(geometries.getResource(geometryName));

		ShapeBuilderOptions< float > options{};
		options.setCenterAtBottom(geometryName == BottomQuadGeometryName);

		auto shape = ShapeGenerator::generateQuad(1.0F, 1.0F, options);

		auto geometryMateriel = std::make_shared< Geometry::IndexedVertexResource >(
			geometryName,
			Geometry::EnableTangentSpace | Geometry::EnablePrimaryTextureCoordinates
		);

		if ( !geometryMateriel->load(shape) )
		{
			Tracer::error(ClassId, "Unable to generate the Geometry for every Sprite !");

			return false;
		}

		geometries.addResource(geometryMateriel);

		return this->setGeometry(geometryMateriel);
	}

	bool
	SpriteResource::setGeometry (const std::shared_ptr< Geometry::Interface > & geometryResource) noexcept
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
	SpriteResource::setMaterial (const std::shared_ptr< Material::Interface > & materialResource) noexcept
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
	SpriteResource::prepareShaders (const Geometry::Interface & geometry, const Material::Interface & material, RenderPassType renderPassType, bool enableInstancing, Vulkan::GraphicsShaderContainer & shaders) const noexcept
	{
		TraceWarning{ClassId} << "Not done yet !";

		return false;
	}

	std::shared_ptr< SpriteResource >
	SpriteResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->sprites().getResource(resourceName, directLoad);
	}

	std::shared_ptr< SpriteResource >
	SpriteResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->sprites().getDefaultResource();
	}
}
