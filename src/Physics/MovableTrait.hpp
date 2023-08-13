/*
 * Emeraude/Physics/MovableTrait.hpp
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

/* Local inclusions for inheritances. */
#include "Scenes/LocatableInterface.hpp"
#include "PhysicalInterface.hpp"

/* Local inclusions for usages. */
#include "Math/Vector.hpp"
#include "PhysicalEnvironmentProperties.hpp"

namespace Emeraude::Physics
{
	/**
	 * @brief Gives the ability to move something in the 3D world with physical properties.
	 * @extends Emeraude::Scenes::LocatableInterface Something movable has a position in the 3D world.
	 * @extends Emeraude::Physics::PhysicalInterface Something movable has physical properties to interact with other entities from the 3D world.
	 */
	class MovableTrait : virtual public Scenes::LocatableInterface, virtual public PhysicalInterface
	{
		public:

			/**
			 * @brief Destructs the movable trait.
			 */
			~MovableTrait () override = default;

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			MovableTrait (const MovableTrait & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			MovableTrait (MovableTrait && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 */
			MovableTrait & operator= (const MovableTrait & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 */
			MovableTrait & operator= (MovableTrait && copy) noexcept = default;

			/**
			 * @brief Sets an initial velocity.
			 * @param velocity A reference to a vector.
			 * @param resetAcceleration Reset the acceleration vector. Default: false.
			 * @return void
			 */
			virtual void setVelocity (const Libraries::Math::Vector< 3, float > & velocity, bool resetAcceleration = false) noexcept final;

			/**
			 * @brief Sets the acceleration.
			 * @param acceleration A reference to a vector.
			 * @return void
			 */
			virtual void setAcceleration (const Libraries::Math::Vector< 3, float > & acceleration) noexcept final;

			/**
			 * @brief This will add an arbitrary vector to the acceleration without any checking.
			 * @param acceleration A reference to an absolute acceleration vector.
			 * @return void
			 */
			virtual void addRawAcceleration (const Libraries::Math::Vector< 3, float > & acceleration) noexcept final;

			/**
			 * @brief Sets the center of mass.
			 * @param centerOfMass A reference to a vector.
			 * @return void
			 */
			virtual void setCenterOfMass (const Libraries::Math::Vector< 3, float > & centerOfMass) noexcept final;

			/**
			 * @brief Returns the velocity
			 * @return const Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Vector< 3, float > & velocity () const noexcept final;

			/**
			 * @brief Returns an acceleration vector relative to scene node.
			 * @return const Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Vector< 3, float > & acceleration () const noexcept final;

			/**
			 * @brief Returns the center of mass from the scene node position.
			 * @return const Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Vector< 3, float > & centerOfMass () const noexcept final;

			/**
			 * @brief Gives the speed in meters per second.
			 * @return float
			 */
			[[nodiscard]]
			virtual float getSpeed () const noexcept final;

			/**
			 * @brief Sets the object into inertia.
			 * @return void
			 */
			virtual void stopMovement () final;

			/**
			 * @brief Returns whether the object is moving.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isMoving () const final;

			/**
			 * @brief Reset the velocity vector.
			 * @note This method don't touch the acceleration vector. Use Node::stopMovement() instead.
			 * @return void
			 */
			virtual void clearVelocity () noexcept final;

			/**
			 * @brief Adds a physical force to the object acceleration.
			 * @param force A reference to a vector representing the force. The magnitude (length) will represent the acceleration in m/s².
			 */
			virtual void addForce (const Libraries::Math::Vector< 3, float > & force) noexcept final;

			/**
			 * @brief Adds an impulse to the node.
			 * @param direction A reference to a direction vector.
			 * @param power The strength of the impulse.
			 * @return void
			 */
			inline
			virtual
			void
			impulse (const Libraries::Math::Vector< 3, float > & direction, float power) noexcept final
			{
				this->addForce(direction.scaled(power));
			}

			/**
			 * @brief Deviate velocity direction from a normal vector when the object hit something.
			 * @param surfaceNormal A vector representing the hit surface normal.
			 * @param surfaceBounciness A scalar to reduce the velocity after deviating the movement. 1.0F = no velocity loss from the surface. Default 0.75.
			 * @return void
			 */
			virtual void deflect (const Libraries::Math::Vector< 3, float > & surfaceNormal, float surfaceBounciness = 0.75F) noexcept final;

			/**
			 * @brief Updates the velocity vector from the acceleration vector and return a reference to the new velocity.
			 * This will in order :
			 *  - Apply gravity force to acceleration vector.
			 *  - Apply drag force to acceleration vector.
			 *  - Add acceleration vector to velocity vector. (then reset acceleration)
			 * @param properties A reference to physical environment properties.
			 * @return const Vector< 3, float > &
			 */
			virtual const Libraries::Math::Vector< 3, float > & updateVelocity (const PhysicalEnvironmentProperties & properties) noexcept final;

			/**
			 * @brief Enables or not the moving ability.
			 * @param state The state.
			 * @return void
			 */
			virtual void setMovingAbility (bool state) noexcept = 0;

			/**
			 * @brief Returns whether the entity is movable by physical interactions.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isMovable () const noexcept = 0;

			/**
			 * @brief Pauses the simulation on this object.
			 * The object is stopped from receiving gravity and drag force.
			 * @note The simulation will restart automatically after adding a custom force.
			 * @param state The state.
			 */
			virtual void pauseSimulation (bool state) noexcept = 0;

			/**
			 * @brief Returns the simulation execution state.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isSimulationPaused () const noexcept = 0;

			/**
			 * @brief Enables the free fly mode. In other terms , the gravity will be ignored.
			 * @param state The state.
			 */
			virtual void enableFreeFlyMode (bool state) noexcept = 0;

			/**
			 * @brief Returns whether the free fly mode is enabled or not.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isFreeFlyModeEnabled () const noexcept = 0;

			/**
			 * @brief Enables the collision test.
			 * @param state The state of the effect.
			 */
			virtual void enableNoClippingMode (bool state) noexcept = 0;

			/**
			 * @brief Returns the ability of node to interact with others physical objects.
			 * For this, this node must have a physical component, be able to move (Node::isMovable())
			 * and shouldn't have the special no clip mode enabled.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isNoClippingModeEnabled () const noexcept = 0;

			/**
			 * @brief Returns the world velocity of the entity.
			 * @note If not override, velocity is null.
			 * @return Libraries::Math::Vector< float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Vector< 3, float > getWorldVelocity () const noexcept = 0;

			/**
			 * @brief Returns the world acceleration of the entity.
			 * @note If not override, velocity is null.
			 * @return Libraries::Math::Vector< float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Vector< 3, float > getWorldAcceleration () const noexcept = 0;

			/**
			 * @brief Returns the world center of mass of the entity.
			 * @note If not override, velocity is null.
			 * @return Libraries::Math::Vector< float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Vector< 3, float > getWorldCenterOfMass () const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a movable trait.
			 */
			MovableTrait () noexcept = default;

		private:

			/**
			 * @brief Adds a gravity force to the object acceleration.
			 * @note This acts like addForce() method, but in an easier way.
			 * @param gravity The gravity value.
			 */
			virtual void applyGravityForce (float gravity) noexcept final;

			/**
			 * @brief Applies a drag force to object acceleration according to his current velocity.
			 * @note If the velocity is null, there will be no drag force computed or added.
			 * @param density Fluid or Air density expressed in kg/m³.
			 */
			virtual void applyDragForce (float density) noexcept final;

			Libraries::Math::Vector< 3, float > m_velocity{};
			Libraries::Math::Vector< 3, float > m_acceleration{};
			Libraries::Math::Vector< 3, float > m_centerOfMass{};
	};
}
