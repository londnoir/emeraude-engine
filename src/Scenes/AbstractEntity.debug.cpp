/*
 * src/Scenes/AbstractEntity.debug.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "AbstractEntity.hpp"

/* Local inclusions. */
#include "Graphics/Geometry/ResourceGenerator.hpp"
#include "Graphics/Renderable/MeshResource.hpp"
#include "Graphics/Material/BasicResource.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"

namespace EmEn::Scenes
{
	using namespace EmEn::Libs;
	using namespace EmEn::Libs::Math;
	using namespace Graphics;

	constexpr auto TracerTag{"AbstractEntity.debug"};

	constexpr auto AxisDebugName{"+EntityAxis"};
	constexpr auto VelocityDebugName{"+EntityVelocity"};
	constexpr auto BoundingBoxDebugName{"+EntityBoundingBox"};
	constexpr auto BoundingSphereDebugName{"+EntityBoundingSphere"};
	constexpr auto CameraDebugName{"+EntityCamera"};

	void
	AbstractEntity::enableVisualDebug (VisualDebugType type) noexcept
	{
		if ( this->isVisualDebugEnabled(type) )
		{
			return;
		}

		auto * resources = Resources::Manager::instance();

		const char * label = nullptr;
		std::shared_ptr< Renderable::MeshResource > meshResource;

		switch ( type )
		{
			case VisualDebugType::Axis :
				label = AxisDebugName;
				meshResource = AbstractEntity::getAxisVisualDebug(*resources);
				break;

			case VisualDebugType::Velocity :
				label = VelocityDebugName;
				meshResource = AbstractEntity::getVelocityVisualDebug(*resources);
				break;

			case VisualDebugType::BoundingBox :
				label = BoundingBoxDebugName;
				meshResource = AbstractEntity::getBoundingBoxVisualDebug(*resources);
				break;

			case VisualDebugType::BoundingSphere :
				label = BoundingSphereDebugName;
				meshResource = AbstractEntity::getBoundingSphereVisualDebug(*resources);
				break;

			case VisualDebugType::Camera :
				label = CameraDebugName;
				meshResource = AbstractEntity::getCameraVisualDebug(*resources);
				break;
		}

		if ( meshResource == nullptr )
		{
			TraceError{TracerTag} << "Unable to get the visual debug mesh !";

			return;
		}

		/* NOTE: Create an instance of this visual debug mesh. */
		const auto meshInstance = this->newVisual(meshResource, false, false, label);

		if ( meshInstance == nullptr )
		{
			TraceError{TracerTag} << "Unable to instantiate a visual debug mesh instance !";

			return;
		}

		/* NOTE : Configure the renderable instance advanced options. */
		const auto renderableInstance = meshInstance->getRenderableInstance();

		switch ( type )
		{
			case VisualDebugType::Axis :
				renderableInstance->setTransformationMatrix(Matrix< 4, float >::scaling(m_boundingSphere.radius()));
				break;

			case VisualDebugType::Velocity :
				break;

			case VisualDebugType::BoundingBox :
				renderableInstance->setTransformationMatrix(
					Matrix< 4, float >::translation(m_boundingBox.centroid()) *
					Matrix< 4, float >::scaling(m_boundingBox.width(), m_boundingBox.height(), m_boundingBox.depth())
				);
				break;

			case VisualDebugType::BoundingSphere :
				renderableInstance->setTransformationMatrix(
					Matrix< 4, float >::translation(m_boundingSphere.position()) *
					Matrix< 4, float >::scaling(m_boundingSphere.radius())
				);
				break;

			case VisualDebugType::Camera :
				break;
		}

		renderableInstance->disableDepthTest(false);
	}

	void
	AbstractEntity::disableVisualDebug (VisualDebugType type) noexcept
	{
		switch ( type )
		{
			case VisualDebugType::Axis :
				this->removeComponent(AxisDebugName);
				break;

			case VisualDebugType::Velocity :
				this->removeComponent(VelocityDebugName);
				break;

			case VisualDebugType::BoundingBox :
				this->removeComponent(BoundingBoxDebugName);
				break;

			case VisualDebugType::BoundingSphere :
				this->removeComponent(BoundingSphereDebugName);
				break;

			case VisualDebugType::Camera :
				this->removeComponent(CameraDebugName);
				break;
		}
	}

	bool
	AbstractEntity::toggleVisualDebug (VisualDebugType type) noexcept
	{
		if ( this->isVisualDebugEnabled(type) )
		{
			this->disableVisualDebug(type);

			return false;
		}

		this->enableVisualDebug(type);

		return true;
	}

	bool
	AbstractEntity::isVisualDebugEnabled (VisualDebugType type) const noexcept
	{
		switch ( type )
		{
			case VisualDebugType::Axis :
				return m_components.contains(AxisDebugName);

			case VisualDebugType::Velocity :
				return m_components.contains(VelocityDebugName);

			case VisualDebugType::BoundingBox :
				return m_components.contains(BoundingBoxDebugName);

			case VisualDebugType::BoundingSphere :
				return m_components.contains(BoundingSphereDebugName);

			case VisualDebugType::Camera :
				return m_components.contains(CameraDebugName);
		}

		return false;
	}

	void
	AbstractEntity::updateVisualDebug () noexcept
	{
		/* Update axis. */
		{
			const auto visualDebugIt = m_components.find(AxisDebugName);

			if ( visualDebugIt != m_components.cend() )
			{
				const auto renderableInstance = visualDebugIt->second->getRenderableInstance();

				if ( m_boundingSphere.isValid() )
				{
					renderableInstance->setTransformationMatrix(Matrix< 4, float >::scaling(m_boundingSphere.radius()));
				}
				else
				{
					renderableInstance->setTransformationMatrix(Matrix< 4, float >::scaling(1.0F));
				}
			}
		}

		/* Update bounding box. */
		{
			const auto visualDebugIt = m_components.find(BoundingBoxDebugName);

			if ( visualDebugIt != m_components.cend() )
			{
				const auto renderableInstance = visualDebugIt->second->getRenderableInstance();

				renderableInstance->setTransformationMatrix(
					Matrix< 4, float >::translation(m_boundingBox.centroid()) *
					Matrix< 4, float >::scaling(m_boundingBox.width(), m_boundingBox.height(), m_boundingBox.depth())
				);
			}
		}

		/* Update bounding sphere. */
		{
			const auto visualDebugIt = m_components.find(BoundingSphereDebugName);

			if ( visualDebugIt != m_components.cend() )
			{
				const auto renderableInstance = visualDebugIt->second->getRenderableInstance();

				renderableInstance->setTransformationMatrix(
					Matrix< 4, float >::translation(m_boundingSphere.position()) *
					Matrix< 4, float >::scaling(m_boundingSphere.radius())
				);
			}
		}
	}

	std::shared_ptr< Material::BasicResource >
	AbstractEntity::getPlainVisualDebugMaterial (Resources::Manager & resources) noexcept
	{
		return resources.basicMaterials().getOrCreateResource("+PlainVisualDebug", [] (Material::BasicResource & newMaterial) {
			newMaterial.enableVertexColor();

			return newMaterial.setManualLoadSuccess(true);
		});
	}

	std::shared_ptr< Material::BasicResource >
	AbstractEntity::getTranslucentVisualDebugMaterial (Resources::Manager & resources) noexcept
	{
		return resources.basicMaterials().getOrCreateResource("+TranslucentVisualDebug", [] (Material::BasicResource & newMaterial) {
			newMaterial.enableVertexColor();
			newMaterial.setOpacity(0.333F);

			return newMaterial.setManualLoadSuccess(true);
		});
	}

	std::shared_ptr< Renderable::MeshResource >
	AbstractEntity::getAxisVisualDebug (Resources::Manager & resources) noexcept
	{
		return resources.meshes().getOrCreateResourceAsync(AxisDebugName, [&resources] (Renderable::MeshResource & newMesh) {
			/* NOTE: Get the geometry. */
			const Geometry::ResourceGenerator generator{resources, Geometry::EnableNormal | Geometry::EnableVertexColor};

			const auto geometryResource = generator.axis(1.0F);

			if ( geometryResource == nullptr )
			{
				return false;
			}

			/* NOTE: Get a plain material. */
			const auto materialResource = AbstractEntity::getPlainVisualDebugMaterial(resources);

			/* NOTE: Assemble the mesh. */
			return newMesh.load(geometryResource, materialResource);
		});
	}

	std::shared_ptr< Renderable::MeshResource >
	AbstractEntity::getVelocityVisualDebug (Resources::Manager & resources) noexcept
	{
		return resources.meshes().getOrCreateResourceAsync(AxisDebugName, [&resources] (Renderable::MeshResource & newMesh) {
			/* NOTE: Get the geometry. */
			const Geometry::ResourceGenerator generator{resources, Geometry::EnableNormal | Geometry::EnableVertexColor};

			const auto geometryResource = generator.arrow(1.0F, PointTo::PositiveZ);

			if ( geometryResource == nullptr )
			{
				return false;
			}

			/* NOTE: Get a basic material. */
			const auto materialResource = AbstractEntity::getPlainVisualDebugMaterial(resources);

			/* NOTE: Assemble the mesh. */
			return newMesh.load(geometryResource, materialResource);
		});
	}

	std::shared_ptr< Renderable::MeshResource >
	AbstractEntity::getBoundingBoxVisualDebug (Resources::Manager & resources) noexcept
	{
		return resources.meshes().getOrCreateResourceAsync(BoundingBoxDebugName, [&resources] (Renderable::MeshResource & newMesh) {
			/* NOTE: Get the geometry. */
			const Geometry::ResourceGenerator generator{resources, Geometry::EnableNormal | Geometry::EnableVertexColor};

			const auto geometryResource = generator.cube(1.0F);

			if ( geometryResource == nullptr )
			{
				return false;
			}

			/* NOTE: Get a translucent material. */
			const auto materialResource = AbstractEntity::getTranslucentVisualDebugMaterial(resources);

			/* NOTE: Assemble the mesh. */
			// TODO: Remove hard-coded wireframe !
			return newMesh.load(geometryResource, materialResource, {PolygonMode::Line, CullingMode::None});
		});
	}

	std::shared_ptr< Renderable::MeshResource >
	AbstractEntity::getBoundingSphereVisualDebug (Resources::Manager & resources) noexcept
	{
		return resources.meshes().getOrCreateResourceAsync(BoundingSphereDebugName, [&resources] (Renderable::MeshResource & newMesh) {
			/* NOTE: Get the geometry. */
			const Geometry::ResourceGenerator generator{resources, Geometry::EnableNormal | Geometry::EnableVertexColor};

			const auto geometryResource = generator.geodesicSphere(1.0F);

			if ( geometryResource == nullptr )
			{
				return false;
			}

			/* NOTE: Get a basic material. */
			const auto materialResource = AbstractEntity::getTranslucentVisualDebugMaterial(resources);

			/* NOTE: Assemble the mesh. */
			// TODO: Remove hard-coded wireframe !
			return newMesh.load(geometryResource, materialResource, {PolygonMode::Line, CullingMode::None});
		});
	}

	std::shared_ptr< Renderable::MeshResource >
	AbstractEntity::getCameraVisualDebug (Resources::Manager & resources) noexcept
	{
		return resources.meshes().getOrCreateResourceAsync(CameraDebugName, [&resources] (Renderable::MeshResource & newMesh) {
			/* NOTE: Get the geometry. */
			const auto geometryResource = resources.indexedVertexGeometries().getResource("Camera", false);

			/* NOTE: Get a basic material. */
			const auto materialResource = resources.basicMaterials().getDefaultResource();

			/* NOTE: Assemble the mesh. */
			return newMesh.load(geometryResource, materialResource);
		});
	}
}
