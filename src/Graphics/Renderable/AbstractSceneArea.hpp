/*
 * Emeraude/Graphics/Renderable/AbstractSceneArea.hpp
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
#include <cstddef>
#include <string>

/* Local inclusions for inheritances. */
#include "Interface.hpp"

/* Local inclusions for usages. */
#include "Graphics/Geometry/VertexGridResource.hpp"

/* Forward declarations */
namespace Emeraude::Scenes
{
	class Node;
}

namespace Emeraude::Graphics::Renderable
{
	/**
	 * @brief Abstract class to define a ground or floor for the scene. This is a special case to delimit a finite world.
	 * @extends Emeraude::Graphics::Renderable::Interface This class is a renderable object in the 3D world.
	 */
	class AbstractSceneArea : public Interface
	{
		public:

			/** @copydoc Emeraude::Graphics::Renderable::Interface::isReadyForInstantiation() */
			[[nodiscard]]
			bool isReadyForInstantiation () const noexcept final;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::flags() */
			[[nodiscard]]
			int flags (size_t layerIndex) const noexcept final;

			/**
			 * @brief Sets the scene area boundary.
			 */
			void setBoundary (float boundary) noexcept;

			/**
			 * @brief Returns the boundary in one direction.
			 * @note To get the total size of an axis, you need to multiply it by two or use AbstractSceneArea::size().
			 * @return float
			 */
			[[nodiscard]]
			float boundary () const noexcept;

			/**
			 * @brief Returns the ground level under the given position.
			 * @param worldPosition An absolute position.
			 * @return float
			 */
			[[nodiscard]]
			virtual float getLevelAt (const Libraries::Math::Vector< 3, float > & worldPosition) const noexcept;

			/**
			 * @brief Returns a position where Y is completed by the level at X,Z position.
			 * @param x The X coordinates.
			 * @param z The Z coordinates.
			 * @param delta A difference value to add to the height. Default 0.0F.
			 * @return Vector< 3, float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Vector< 3, float > getLevelAt (float x, float z, float delta = 0.0F) const noexcept;

			/**
			 * @brief Returns the normal vector under the given position.
			 * @param worldPosition An absolute position.
			 * @return Vector< 3, float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Vector< 3, float > getNormalAt (const Libraries::Math::Vector< 3, float > & worldPosition) const noexcept;

			/**
			 * @brief Checks a scene node is on the ground.
			 * @param node A reference to a smart pointer to a node.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isOnGround (Scenes::Node & node) const noexcept;

		protected:

			/**
			 * @brief Constructs a renderable scene area.
			 * @param name A reference to a string for the resource name.
			 * @param resourceFlagBits The resource flag bits.
			 */
			explicit AbstractSceneArea (const std::string & name, uint32_t resourceFlagBits) noexcept;

			/**
			 * @brief Destructs the renderable scene area.
			 */
			~AbstractSceneArea () override = default;

			/** @copydoc Emeraude::Graphics::Renderable::Interface::setReadyForInstanciation() */
			void setReadyForInstanciation (bool state) noexcept final;

		private:

			float m_boundary = 0.0F;
			int m_renderableFlags = 0;
	};
}
