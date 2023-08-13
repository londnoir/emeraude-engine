/*
 * Emeraude/Scenes/VisualComponent.hpp
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

/* Local inclusions for inheritances. */
#include "AbstractComponent.hpp"

/* Local inclusions for usages. */
#include "Graphics/RenderableInstance/Unique.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief Defines a component for the visual part of an entity.
	 * @extends Emeraude::Scenes::AbstractComponent The base class for each entity component.
	 */
	class VisualComponent final : public AbstractComponent
	{
		public:

			/**
			 * @brief Constructs a renderable instance from a raw renderable.
			 * @param name The name of the renderable instance.
			 * @param parentEntity A reference to the parent entity.
			 * @param mesh A reference to a renderable smart pointer.
			 */
			VisualComponent (const std::string & name, const AbstractEntity & parentEntity, const std::shared_ptr< Graphics::Renderable::Interface > & renderable) noexcept;

			/** @copydoc Emeraude::Scenes::AbstractComponent::getRenderableInstance() const */
			[[nodiscard]]
			const Graphics::RenderableInstance::Abstract * getRenderableInstance () const noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractComponent::getRenderableInstance() */
			[[nodiscard]]
			Graphics::RenderableInstance::Abstract * getRenderableInstance () noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractComponent::getComponentType() */
			[[nodiscard]]
			const char * getComponentType () const noexcept override;

		private:

			/** @copydoc Emeraude::Scenes::AbstractComponent::move() */
			void move () noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractComponent::processLogics() */
			void processLogics (const Scene & scene, size_t cycle) noexcept override;

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept override;

			std::shared_ptr< Graphics::RenderableInstance::Unique > m_renderableInstance;
	};
}
