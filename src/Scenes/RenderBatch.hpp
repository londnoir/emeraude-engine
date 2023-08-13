/*
 * Emeraude/Scenes/RenderBatch.hpp
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
#include <memory>
#include <map>

/* Local inclusions for usages. */
#include "Graphics/RenderableInstance/Abstract.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief The RenderBatch class
	 */
	class RenderBatch final
	{
		public :

			using List = std::multimap< uint64_t, RenderBatch >;

			/**
			 * @brief Constructs a render batch.
			 * @param renderableInstance A pointer to the renderable instance.
			 * @param subGeometryIndex The layer index of the renderable.
			 */
			explicit RenderBatch (const Graphics::RenderableInstance::Abstract * renderableInstance, size_t subGeometryIndex = 0UL) noexcept;

			/**
			 * @brief Returns the renderable instance pointer.
			 * @return const Graphics::RenderableInstance::Abstract *
			 */
			[[nodiscard]]
			const Graphics::RenderableInstance::Abstract * renderableInstance () const noexcept;

			/**
			 * @brief Returns the batch index of the renderable.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t subGeometryIndex () const noexcept;

			/**
			 * @brief Static method to instantiate a render batch and register it to a render list.
			 * @param renderList A referencer to a render list.
			 * @param distance The distance of the renderable from the camera.
			 * @param renderableInstance A pointer to the renderable instance.
			 * @param subGeometryIndex The layer index of the renderable.
			 * @return bool
			 */
			[[nodiscard]]
			static bool create (List & renderList, float distance, const Graphics::RenderableInstance::Abstract * renderableInstance, size_t subGeometryIndex = 0UL) noexcept;

		private :

			static constexpr auto DistanceMultiplier = 1000UL;

			const Graphics::RenderableInstance::Abstract * m_renderableInstance;
			size_t m_subGeometryIndex;
	};
}
