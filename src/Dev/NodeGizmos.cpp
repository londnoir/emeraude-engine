/*
 * Emeraude/Dev/NodeGizmos.cpp
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

#include "NodeGizmos.hpp"

/* Local inclusions */
#include "Scenes/Node.hpp"
#include "Tracer.hpp"

namespace Emeraude::Dev
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Graphics;
	using namespace Saphir;
	using namespace Saphir::Keys;
	using namespace Scenes;

	bool
	NodeGizmos::empty () const noexcept
	{
		return m_gizmos.empty();
	}

	bool
	NodeGizmos::isGizmoPresent (const char * label) const noexcept
	{
		return m_gizmos.find(label) != m_gizmos.cend();
	}

	bool
	NodeGizmos::addGizmo (const char * label, const std::shared_ptr< Renderable::SimpleMeshResource > & gizmo) noexcept
	{
		auto gizmoIt = m_gizmos.find(label);

		if ( gizmoIt != m_gizmos.cend() )
		{
			return false;
		}

		return m_gizmos.emplace(label, gizmo).second;
	}

	bool
	NodeGizmos::removeGizmo (const char * label) noexcept
	{
		auto gizmoIt = m_gizmos.find(label);

		if ( gizmoIt == m_gizmos.cend() )
		{
			return false;
		}

		m_gizmos.erase(gizmoIt);

		/* FIXME: BAD IDEA FOR VIDEO MEMORY THREAD. */
		//if ( m_gizmos.empty() )
		//	m_modelMatricesUBO.destroyFromHardware();

		return true;
	}

	void
	NodeGizmos::clearGizmos () noexcept
	{
		m_gizmos.clear();

		/* FIXME: BAD IDEA FOR VIDEO MEMORY THREAD. */
		//m_modelMatricesUBO.destroyFromHardware();
	}

	void
	NodeGizmos::render (Renderer & renderer, const RenderTarget::Abstract & renderTarget) const noexcept
	{
		/* VULKAN_DEV */
		/*m_modelMatricesUBO.updateVideoMemoryWithView(output);

		for ( auto & pair : m_gizmos )
		{
			auto & renderable = pair.second;

			/ * Gets the underlying renderable object. * /
			if ( !renderable->isReadyToDraw() )
				continue;

			/ * Gets the geometry from the renderable object and bind the VAO and configure the triangle rasterization. * /
			const auto geometryPtr = renderable->geometry();

			if ( geometryPtr == nullptr )
				return;

			geometryPtr->bind();
			renderer.setRasterizationMode(geometryPtr->rasterizationMode());

			/ * Gets the material from the renderable object. * /
			const auto materialPtr = renderable->material();

			if ( materialPtr == nullptr )
				return;

			auto textureUnit = 0U;

			/ * Gets the right rendering program from the renderable object. * /
			const auto programPtr = renderable->programs().variation(ModelMatricesType::UniformBufferObject);

			if ( programPtr == nullptr )
				return;

			programPtr->use();

			/ * Configure the model matrices. UBO:1 * /
			m_modelMatricesUBO.bindToProgram(*programPtr);

			/ * Configure material, effects, lights and shadows. * /
			materialPtr->activate(renderer, *programPtr, textureUnit, RenderPassType::AmbientPass);

			/ * Draw the object. * /
			geometryPtr->draw();
		}*/
	}

	bool
	NodeGizmos::initOrUpdateVideoMemory (const Matrix< 4, float > & modelMatrix) noexcept
	{
		if ( m_gizmos.empty() )
		{
			return true;
		}

		/*if ( !m_modelMatricesUBO.isCreated() )
		{
			Tracer::info(ClassId, "Allocating a ModelMatricesUBO !");

			if ( !m_modelMatricesUBO.create() )
			{
				Tracer::error(ClassId, "Unable to allocate a ModelMatricesUBO !");

				return false;
			}
		}

		if ( !m_modelMatricesUBO.updateWithModel(modelMatrix) )
		{
			Tracer::error(ClassId, "Unable to update the ModelMatricesUBO !");

			return false;
		}*/

		return true;
	}
}
