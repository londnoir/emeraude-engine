/*
 * src/Scenes/Component/Visual.hpp
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

/* Local inclusions for inheritances. */
#include "Abstract.hpp"
#include "Libraries/ObserverTrait.hpp"

/* Local inclusions for usages. */
#include "Animations/Types.hpp"
#include "Graphics/RenderableInstance/Unique.hpp"
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Cuboid.hpp"
#include "Libraries/Math/Sphere.hpp"
#include "Libraries/Variant.hpp"

namespace Emeraude::Scenes::Component
{
	/**
	 * @brief Defines a component for the visual part of an entity.
	 * @extends Emeraude::Scenes::Component::Abstract The base class for each entity component.
	 * @extends Libraries::ObserverTrait This class must dispatch modifications from renderable instance to the entity.
	 */
	class Visual final : public Abstract, public Libraries::ObserverTrait
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"Visual"};

			/**
			 * @brief Constructs a visual component.
			 * @param name The name of the renderable instance.
			 * @param parentEntity A reference to the parent entity.
			 * @param renderable A reference to a renderable smart pointer.
			 */
			Visual (const std::string & name, const AbstractEntity & parentEntity, const std::shared_ptr< Graphics::Renderable::Interface > & renderable) noexcept;

			/** @copydoc Emeraude::Scenes::Component::Abstract::getRenderableInstance() const */
			[[nodiscard]]
			std::shared_ptr< Graphics::RenderableInstance::Abstract > getRenderableInstance () const noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::getComponentType() */
			[[nodiscard]]
			const char * getComponentType () const noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::boundingBox() const */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > & boundingBox () const noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::boundingSphere() const */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > & boundingSphere () const noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::move() */
			void move (const Libraries::Math::CartesianFrame< float > & worldCoordinates) noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::processLogics() */
			void processLogics (const Scene & scene) noexcept override;

			/** @copydoc Emeraude::Scenes::Component::Abstract::shouldRemove() */
			bool shouldRemove () const noexcept override;

		private:

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t identifier, const Libraries::Variant & value) noexcept override;

			/** @copydoc Libraries::ObserverTrait::onNotification() */
			[[nodiscard]]
			bool onNotification (const ObservableTrait * observable, int notificationCode, const std::any & data) noexcept override;

			std::shared_ptr< Graphics::RenderableInstance::Unique > m_renderableInstance;
	};
}
