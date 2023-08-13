/*
 * Emeraude/Scenes/StaticEntity.hpp
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

/* Local C/C++ standard libraries */
#include <string>
#include <array>

/* Local inclusions for inheritances. */
#include "AbstractEntity.hpp"
#include "Physics/PhysicalInterface.hpp"
#include "Animations/AnimatableInterface.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief Defines a static entity, which means that it does not physically act on its own.
	 * @extends Emeraude::Scenes::AbstractEntity A static entity is obviously an entity of the 3D world.
	 * @extends Emeraude::Animations::AnimatableInterface This class can be animated by the engine logics.
	 */
	class StaticEntity final : public AbstractEntity, public Animations::AnimatableInterface
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"StaticEntity"};

			/** @brief Observable class unique identifier. */
			static const size_t ClassUID;

			/**
			 * @brief Constructs a static entity.
			 * @param name A reference to a string to name the entity in the scene.
			 * @param parentScene A pointer to the scene holding this static entity.
			 * @param coordinates The location of the static entity. Default origin.
			 */
			explicit StaticEntity (const std::string & name, Scene * parentScene, const Libraries::Math::Coordinates< float > & coordinates = {}) noexcept;

			/**
			 * @brief Destructs a static entity.
			 */
			~StaticEntity () override;

			/** @copydoc Libraries::Observable::is() */
			[[nodiscard]]
			bool is (size_t classUID) const noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::isRenderable() */
			[[nodiscard]]
			bool isRenderable () const noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::hasPhysicalObjectProperties() */
			[[nodiscard]]
			bool hasPhysicalObjectProperties () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setLocalCoordinates() */
			void setLocalCoordinates (const Libraries::Math::Coordinates< float > & coordinates) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::localCoordinates() const */
			[[nodiscard]]
			const Libraries::Math::Coordinates< float > & localCoordinates () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldCoordinates() const */
			[[nodiscard]]
			Libraries::Math::Coordinates< float > getWorldCoordinates () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldBoundingBox() const */
			[[nodiscard]]
			Libraries::Math::Cuboid< float > getWorldBoundingBox () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldBoundingSphere() const */
			[[nodiscard]]
			Libraries::Math::Sphere< float > getWorldBoundingSphere () const noexcept override;

			/** @copydoc Emeraude::Physics::PhysicalInterface::enableSphereCollision() const */
			void enableSphereCollision (bool state) noexcept override;

			/** @copydoc Emeraude::Physics::PhysicalInterface::sphereCollisionIsEnabled() */
			[[nodiscard]]
			bool sphereCollisionIsEnabled () const noexcept override;

			/**
			 * @brief This function is called from Core::processLogics() to update the logic of the node and return if it has been moved.
			 * @param scene The scene where the node is present.
			 * @param cycle The engine cycle number to use with time dependent effects.
			 * @return bool
			 */
			bool processLogics (const Scene & scene, size_t cycle) noexcept override;

			/**
			 * @brief Returns the coordinates of the static renderable.
			 * @return Libraries::Math::Matrix< 4, float >
			 */
			[[nodiscard]]
			Libraries::Math::Matrix< 4, float > getModelMatrix () const noexcept;

			/**
			 * @brief Short-hand for Coordinates class, but use the tree to get the right view matrix.
			 * @param rotateOnly Don't set translation in final matrices.
			 * @return Matrix< 4, float >
			 */
			[[nodiscard]]
			Libraries::Math::Matrix< 4, float > getViewMatrix (bool rotateOnly = false) const noexcept;

		private:

			/* Flag names. */
			static constexpr auto IsRenderable = 0UL;
			static constexpr auto HasPhysicalObjectProperties = 1UL;
			static constexpr auto SphereCollisionEnabled = 2UL;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWritableLocalCoordinates() */
			[[nodiscard]]
			Libraries::Math::Coordinates< float > & getWritableLocalCoordinates () noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::setRenderingAbilityState() */
			void setRenderingAbilityState (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::setPhysicalObjectPropertiesState() */
			void setPhysicalObjectPropertiesState (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::AbstractEntity::onAppNotification() */
			bool onUnhandledNotification (const Observable * observable, int notificationCode, const std::any & data) noexcept override;

			/** @copydoc Emeraude::Animations::AnimatableInterface::playAnimation() */
			bool playAnimation (Animations::id_t id, const Libraries::Variant & value) noexcept override;

			Libraries::Math::Coordinates< float > m_coordinates{};
			std::array< bool, 8 > m_flags{
				false/*IsRenderable*/,
				false/*HasPhysicalObjectProperties*/,
				false/*SphereCollisionEnabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
