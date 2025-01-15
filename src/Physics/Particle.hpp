/*
 * src/Physics/Particle.hpp
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

/* STL inclusions */
#include <cstdint>
#include <set>
#include <memory>

/* Local inclusions for inheritances. */
#include "Scenes/LocatableInterface.hpp"

/* Local inclusions. */
#include "Scenes/Component/Abstract.hpp"
#include "Scenes/Component/AbstractModifier.hpp"
#include "PhysicalEnvironmentProperties.hpp"

namespace Emeraude::Physics
{
	/**
	 * @brief The particle class.
	 * @extends Emeraude::Scenes::LocatableInterface A particle is locatable in the scene.
	 */
	class Particle final : public Scenes::LocatableInterface
	{
		public:

			/**
			 * @brief Constructs a particle.
			 * @note Particle is dead by default.
			 */
			Particle () = default;

			/**
			 * @brief Initializes the particle.
			 * @param initialLife The initial life of the particle.
			 * @param initialSize The initial size of the particle.
			 * @param spreadingRadius The spreading parameters. Default 0.0.
			 * @param initialLocation A reference to a cartesian frame. Default origin.
			 * return void
			 */
			void initialize (uint32_t initialLife, float initialSize, float spreadingRadius = 0.0F, const Libraries::Math::CartesianFrame< float > & initialLocation = {}) noexcept;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setPosition(const Libraries::Math::Vector< 3, float > &, Libraries::Math::TransformSpace) */
			void setPosition (const Libraries::Math::Vector< 3, float > & position, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setXPosition(float, Libraries::Math::TransformSpace) */
			void setXPosition (float position, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setYPosition(float, Libraries::Math::TransformSpace) */
			void setYPosition (float position, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::setZPosition(float, Libraries::Math::TransformSpace) */
			void setZPosition (float position, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::move(const Libraries::Math::Vector< 3, float > &, Libraries::Math::TransformSpace) */
			void move (const Libraries::Math::Vector< 3, float > & distance, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveX(float, Libraries::Math::TransformSpace) */
			void moveX (float distance, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveY(float, Libraries::Math::TransformSpace) */
			void moveY (float distance, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::moveZ(float, Libraries::Math::TransformSpace) */
			void moveZ (float distance, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::rotate(float, const Libraries::Math::Vector< 3, float > &, Libraries::Math::TransformSpace) */
			void rotate (float radian, const Libraries::Math::Vector< 3, float > & axis, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::pitch(float, Libraries::Math::TransformSpace) */
			void pitch (float radian, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::yaw(float, Libraries::Math::TransformSpace) */
			void yaw (float radian, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::roll(float, Libraries::Math::TransformSpace) */
			void roll (float radian, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::scale(const Libraries::Math::Vector< 3, float > &, Libraries::Math::TransformSpace) */
			void scale (const Libraries::Math::Vector< 3, float > & factor, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::scale(float, Libraries::Math::TransformSpace) */
			void scale (float factor, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::scaleX(float, Libraries::Math::TransformSpace) */
			void scaleX (float factor, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::scaleY(float, Libraries::Math::TransformSpace) */
			void scaleY (float factor, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::scaleZ(float, Libraries::Math::TransformSpace) */
			void scaleZ (float factor, Libraries::Math::TransformSpace transformSpace) noexcept override;

			/** @copydoc Emeraude::Scenes::LocatableInterface::lookAt(const Libraries::Math::Vector< 3, float > &, bool) */
			void
			lookAt (const Libraries::Math::Vector< 3, float > & target, bool flipZAxis) noexcept override
			{
				m_cartesianFrame.lookAt(target, flipZAxis);
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::setLocalCoordinates(const Libraries::Math::CartesianFrame< float > &) */
			void
			setLocalCoordinates (const Libraries::Math::CartesianFrame< float > & coordinates) noexcept override
			{
				m_cartesianFrame = coordinates;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::localCoordinates() const */
			[[nodiscard]]
			const Libraries::Math::CartesianFrame< float > &
			localCoordinates () const noexcept override
			{
				return m_cartesianFrame;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::localCoordinates() */
			[[nodiscard]]
			Libraries::Math::CartesianFrame< float > &
			localCoordinates () noexcept override
			{
				return m_cartesianFrame;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldCoordinates() const */
			[[nodiscard]]
			Libraries::Math::CartesianFrame< float >
			getWorldCoordinates () const noexcept override
			{
				return m_cartesianFrame;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::localBoundingBox() const */
			[[nodiscard]]
			const Libraries::Math::Cuboid< float > &
			localBoundingBox () const noexcept override
			{
				return Scenes::Component::Abstract::NullBoundingBox;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldBoundingBox() const */
			[[nodiscard]]
			Libraries::Math::Cuboid< float >
			getWorldBoundingBox () const noexcept override
			{
				return Scenes::Component::Abstract::NullBoundingBox;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::localBoundingSphere() const */
			[[nodiscard]]
			const Libraries::Math::Sphere< float > &
			localBoundingSphere () const noexcept override
			{
				return Scenes::Component::Abstract::NullBoundingSphere;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::getWorldBoundingSphere() const */
			[[nodiscard]]
			Libraries::Math::Sphere< float >
			getWorldBoundingSphere () const noexcept override
			{
				return Scenes::Component::Abstract::NullBoundingSphere;
			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::enableSphereCollision(bool) */
			void
			enableSphereCollision (bool /*state*/) noexcept override
			{

			}

			/** @copydoc Emeraude::Scenes::LocatableInterface::sphereCollisionIsEnabled() const */
			[[nodiscard]]
			bool
			sphereCollisionIsEnabled () const noexcept override
			{
				return true;
			}

			/**
			 * @brief Returns the current particle velocity.
			 * @return const Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			const Libraries::Math::Vector< 3, float > &
			linearVelocity () const noexcept
			{
				return m_linearVelocity;
			}

			/**
			 * @brief Gives access to the velocity vector.
			 * @return Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			Libraries::Math::Vector< 3, float > &
			linearVelocity () noexcept
			{
				return m_linearVelocity;
			}

			/**
			 * @brief Returns the linear speed in meters per second.
			 * @note Computed on the fly.
			 * @return float
			 */
			[[nodiscard]]
			float
			linearSpeed () const noexcept
			{
				return m_linearVelocity.length();
			}

			/**
			 * @brief Sets the lifetime of the particle in milliseconds.
			 * @note If you set zero, the particle will be considered as dead.
			 * @param life The new life of the particle.
			 * @return void
			 */
			void
			setLifetime (uint32_t life) noexcept
			{
				m_lifetime = life;
			}

			/**
			 * @brief Returns the remaining lifetime of the particle in milliseconds.
			 * @return uint32_t
			 */
			[[nodiscard]]
			uint32_t
			remainingLifetime () const noexcept
			{
				return m_lifetime;
			}

			/**
			 * @brief Sets the size of the particle.
			 * @param size The new size of the particle.
			 * @return void
			 */
			void
			setSize (float size) noexcept
			{
				m_size = std::abs(size);
			}

			/**
			 * @brief Returns the current size of the particle.
			 * @return size_t
			 */
			[[nodiscard]]
			float
			size () const noexcept
			{
				return m_size;
			}

			/**
			 * @brief Returns whether the particle is dead or not.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isDead () const noexcept
			{
				return m_lifetime == 0;
			}

			/**
			 * @brief Updates the particle physics simulation.
			 * @note This is the default engine behavior.
			 * @param envProperties A reference to the physical environment properties coming from the scene.
			 * @param particleProperties A reference to the physical object properties coming from the particle emitter.
			 * @param worldCoordinates A reference to a cartesian frame according to the particle emitter location.
			 * @param modifiers A reference to a vector of scene modifiers.
			 * @return bool
			 */
			bool updateSimulation (const PhysicalEnvironmentProperties & envProperties, const PhysicalObjectProperties & particleProperties, const Libraries::Math::CartesianFrame< float > & worldCoordinates, const std::set< std::shared_ptr< Scenes::Component::AbstractModifier > > & modifiers) noexcept;

			/**
			 * @brief Updates the particles position and properties.
			 * @param velocity A reference to a velocity vector.
			 * @param sizeDelta A value to add to the current size of the particle.
			 * @param chaos A chaos value to apply.
			 * @return void
			 */
			void update (const Libraries::Math::Vector< 3, float > & velocity, float sizeDelta, float chaos) noexcept;

		private:

			/**
			 * @brief Shifts the particle location randomly according to a magnitude.
			 * @param magnitude The magnitude value.
			 */
			void shiftLocation (float magnitude) noexcept;

			Libraries::Math::CartesianFrame< float > m_cartesianFrame;
			Libraries::Math::Vector< 3, float > m_linearVelocity;
			uint32_t m_lifetime{0};
			float m_size{1.0F};
	};
}
