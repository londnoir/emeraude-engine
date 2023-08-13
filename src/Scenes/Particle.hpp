/*
 * Emeraude/Scenes/Particle.hpp
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
#include <array>

/* Local inclusions for inheritances. */
#include "Physics/MovableTrait.hpp"

namespace Emeraude::Scenes
{
	class ParticlesEmitter;

	class Particle final : public Physics::MovableTrait
	{
		public:

			/**
			 * @brief Constructs a particle.
			 * @param emitter A reference to the responsible particle emitter.
			 * @param initialLife The initial life of the particle. Default 1.
			 * @param initialSize The initial size of the particle. Default 1.0.
			 * @param spreading The spreading parameters. Default 0.0.
			 */
			explicit Particle (ParticlesEmitter & emitter, size_t initialLife = 1, float initialSize = 1.0F, float spreading = 0.0F) noexcept;

			/** @copydoc Emeraude::Physics::PhysicalInterface::enableSphereCollision() */
			void enableSphereCollision (bool state) noexcept override;

			/** @copydoc Emeraude::Physics::PhysicalInterface::sphereCollisionIsEnabled() */
			[[nodiscard]]
			bool sphereCollisionIsEnabled () const noexcept override;

			/** @copydoc Emeraude::Physics::PhysicalInterface::physicalObjectProperties() const */
			[[nodiscard]]
			const Physics::PhysicalObjectProperties & physicalObjectProperties () const noexcept override;

			/** @copydoc Emeraude::Physics::PhysicalInterface::physicalObjectProperties() */
			[[nodiscard]]
			Physics::PhysicalObjectProperties & physicalObjectProperties () noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setLocalCoordinates() */
			void setLocalCoordinates (const Libraries::Math::Coordinates< float > & coordinates) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::localCoordinates() const */
			[[nodiscard]]
			const Libraries::Math::Coordinates< float > & localCoordinates () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::localBoundingBox() const */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > & localBoundingBox () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::localBoundingSphere() const */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > & localBoundingSphere () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldCoordinates() const */
			[[nodiscard]]
			Libraries::Math::Coordinates< float > getWorldCoordinates () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldBoundingBox() const */
			[[nodiscard]]
			Libraries::Math::Cuboid< float > getWorldBoundingBox () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldBoundingSphere() const */
			[[nodiscard]]
			Libraries::Math::Sphere< float > getWorldBoundingSphere () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::setMovingAbility() */
			void setMovingAbility (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::isMovable() */
			[[nodiscard]]
			bool isMovable () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::pauseSimulation() */
			void pauseSimulation (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::isSimulationPaused() */
			[[nodiscard]]
			bool isSimulationPaused () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::enableFreeFlyMode() */
			void enableFreeFlyMode (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::isFreeFlyModeEnabled() */
			[[nodiscard]]
			bool isFreeFlyModeEnabled () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::enableNoClippingMode() */
			void enableNoClippingMode (bool state) noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::isNoClippingModeEnabled() */
			[[nodiscard]]
			bool isNoClippingModeEnabled () const noexcept override;

			/** @copydoc Emeraude::Scenes::MovableTrait::getWorldVelocity() */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getWorldVelocity () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldAcceleration() */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getWorldAcceleration () const noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldCenterOfMass() */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > getWorldCenterOfMass () const noexcept override;

			/**
			 * @brief Sets the life of the particle.
			 * @note If you set zero, the particle will be considered as dead.
			 * @param life The new life of the particle.
			 * @return void
			 */
			void setLife (size_t life) noexcept;

			/**
			 * @brief Returns the current life of the particle.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t life () const noexcept;

			/**
			 * @brief Sets the size of the particle.
			 * @note If you set zero, the particle will be considered as dead.
			 * @param size The new size of the particle.
			 * @return void
			 */
			void setSize (float size) noexcept;

			/**
			 * @brief Returns the current size of the particle.
			 * @return size_t
			 */
			[[nodiscard]]
			float size () const noexcept;

			/**
			 * @brief Returns whether the particle is dead or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool isDead () const noexcept;

			/**
			 * @brief Updates the particles position and properties.
			 * @param velocity A reference to a velocity vector.
			 * @param updateSize
			 * @param chaos
			 * @return void
			 */
			void update (const Libraries::Math::Vector< 3, float > & velocity, float updateSize, float chaos) noexcept;

		private:

			/* Flag names. */
			static constexpr auto SphereCollisionEnabled = 0UL;
			static constexpr auto IsMovable = 1UL;
			static constexpr auto SimulationPaused = 2UL;
			static constexpr auto FreeFlyModeEnabled = 3UL;
			static constexpr auto NoClippingModeEnabled = 4UL;

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWritableLocalCoordinates() */
			[[nodiscard]]
			Libraries::Math::Coordinates< float > & getWritableLocalCoordinates () noexcept override;

			/**
			 * @brief Applies chaos on the final update.
			 * @param magnitude The magnitude value.
			 */
			void applyChaos (float magnitude) noexcept;

			ParticlesEmitter * m_emitter = nullptr;
			Libraries::Math::Coordinates< float > m_coordinates{};
			size_t m_life;
			float m_size;
			std::array< bool, 8 > m_flags{
				true/*SphereCollisionEnabled*/,
				true/*IsMovable*/,
				false/*SimulationPaused*/,
				false/*FreeFlyModeEnabled*/,
				false/*NoClippingModeEnabled*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
