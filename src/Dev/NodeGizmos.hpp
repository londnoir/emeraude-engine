/*
 * Emeraude/Dev/NodeGizmos.hpp
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

#pragma once

/* C/C++ standard libraries. */
#include <map>
#include <memory>

/* Local inclusions for usages. */
#include "Graphics/Renderable/SimpleMeshResource.hpp"
#include "Graphics/Renderer.hpp"

/* Forward declarations. */
namespace Emeraude::Scenes
{
	class Node;
}

namespace Emeraude::Dev
{
	class NodeGizmos final
	{
		public:

			/** @brief Constructs a scene node gizmos container. */
			NodeGizmos () noexcept = default;

			/**
			 * @brief Returns whether the container is empty.
			 * @return bool
			 */
			[[nodiscard]]
			bool empty () const noexcept;

			/**
			 * @brief Returns whether a labeled gizmo is present in the container.
			 * @param label The label identifier for the gizmo.
			 * @return bool
			 */
			[[nodiscard]]
			bool isGizmoPresent (const char * label) const noexcept;

			/**
			 * @brief Adds a gizmo to the scene node gizmos.
			 * @param label The label identifier for the gizmo.
			 * @param gizmo A reference to a gizmo smart pointer.
			 * @return bool
			 */
			bool addGizmo (const char * label, const std::shared_ptr< Graphics::Renderable::SimpleMeshResource > & gizmo) noexcept;

			/**
			 * @brief Removes a gizmo from the scene node gizmos.
			 * @param label The label identifier for the gizmo to delete.
			 * @return bool
			 */
			bool removeGizmo (const char *) noexcept;

			/** @brief Deletes all gizmos from the scene node. */
			void clearGizmos () noexcept;

			/**
			 * @brief Draws gizmos.
			 * @param renderer A reference to the renderer.
			 * @param renderTarget A reference to the render target.
			 */
			void render (Graphics::Renderer & renderer, const Graphics::RenderTarget::Abstract & renderTarget) const noexcept;

			/**
			 * @brief Initializes or update the video memory concerning the model matrices UBO.
			 * @param modelMatrix A reference to a model matrix.
			 */
			bool initOrUpdateVideoMemory (const Libraries::Math::Matrix< 4, float > & modelMatrix = {}) noexcept;

		private:

			std::map< const char *, std::shared_ptr< Graphics::Renderable::SimpleMeshResource > > m_gizmos{};
	};
}
