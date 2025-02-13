/*
 * src/Scenes/Component/MultipleVisuals.hpp
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

#pragma once

/* STL inclusions. */
#include <any>
#include <memory>
#include <string>
#include <vector>

/* Local inclusions for inheritances. */
#include "Abstract.hpp"
#include "Libraries/ObserverTrait.hpp"

/* Local inclusions for usages. */
#include "Graphics/RenderableInstance/Multiple.hpp"

namespace Emeraude::Scenes::Component
{
	/**
	 * @brief Defines a renderable instance suitable for the scene node tree.
	 * @extends Emeraude::Scenes::Component::Abstract The base class for each entity component.
	 * @extends Libraries::ObserverTrait This class must dispatch modifications from renderable instance to the entity.
	 */
	class MultipleVisuals final : public Abstract, public Libraries::ObserverTrait
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"MultipleVisuals"};

			/**
			 * @brief Constructs a multiple visuals component.
			 * @param name The name of the renderable instance.
			 * @param parentEntity A reference to the parent entity.
			 * @param renderable A reference to a renderable smart pointer.
			 * @param coordinates A list of sub-coordinates.
			 */
			MultipleVisuals (const std::string & name, const AbstractEntity & parentEntity, const std::shared_ptr< Graphics::Renderable::Interface > & renderable, const std::vector< Libraries::Math::CartesianFrame< float > > & coordinates) noexcept;

			/** @copydoc Emeraude::Scenes::Component::Abstract::getRenderableInstance() const */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderableInstance::Abstract >
			getRenderableInstance () const noexcept override
			{
				return m_renderableInstance;
			}

			/** @copydoc Emeraude::Scenes::Component::Abstract::getComponentType() */
			[[nodiscard]]
			const char *
			getComponentType () const noexcept override
			{
				return ClassId;
			}

			/** @copydoc Emeraude::Scenes::Component::Abstract::boundingBox() const */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > &
			boundingBox () const noexcept override
			{
				return NullBoundingBox;
			}

			/** @copydoc Emeraude::Scenes::Component::Abstract::boundingSphere() const */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > &
			boundingSphere () const noexcept override
			{
				return NullBoundingSphere;
			}

			/** @copydoc Emeraude::Scenes::Component::Abstract::move() */
			void move (const Libraries::Math::CartesianFrame< float > & worldCoordinates) noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::processLogics() */
			void processLogics (const Scene & scene) noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::shouldRemove() */
			bool shouldRemove () const noexcept override;

		private:

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (uint8_t animationID, const Libraries::Variant & value, size_t cycle) noexcept override;

			/** @copydoc Libraries::ObserverTrait::onNotification() */
			[[nodiscard]]
			bool onNotification (const ObservableTrait * observable, int notificationCode, const std::any & data) noexcept override;

			std::shared_ptr< Graphics::RenderableInstance::Multiple > m_renderableInstance;
			std::vector< Libraries::Math::CartesianFrame< float > > m_coordinates;
	};
}
