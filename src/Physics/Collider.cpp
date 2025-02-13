/*
 * src/Physics/Collider.cpp
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

#include "Collider.hpp"

/* Local inclusions. */
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/OrientedCuboid.hpp"
#include "Libraries/Math/Sphere.hpp"
#include "Scenes/AbstractEntity.hpp"
#include "Physics/MovableTrait.hpp"

namespace Emeraude::Physics
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Scenes;

	bool
	Collider::checkCollisionAgainstMovable (AbstractEntity & movableEntityA, AbstractEntity & movableEntityB) noexcept
	{
#ifdef DEBUG
		if ( &movableEntityA ==  &movableEntityB )
		{
			Tracer::error(ClassId, "Collision search on the same entity detected !");
			return false;
		}
#endif

		Vector< 3, float > collisionDirection;
		auto collisionOverflow = 0.0F;

		/* TODO: Add sphere against box collision. */
		if ( movableEntityA.sphereCollisionIsEnabled() && movableEntityB.sphereCollisionIsEnabled() )
		{
			if ( !isSphereCollisionWith(movableEntityB, movableEntityA, collisionOverflow, collisionDirection) )
			{
				return false;
			}
		}
		else
		{
			if ( !isBoxCollisionWith(movableEntityB, movableEntityA, collisionOverflow, collisionDirection) )
			{
				return false;
			}
		}

		/* NOTE: Location correction. */
		{
			/* TODO: Use a ratio between node speed to avoid moving back an inert entity with location correction. */
			const auto halfway = collisionDirection.scaled(collisionOverflow * 0.5F);

			/* NOTE: We move the two entities back halfway. */
			movableEntityA.move(halfway, TransformSpace::World);
			movableEntityB.move(-halfway, TransformSpace::World);
		}

		/* NOTE: Collision declaration. */
		const auto collisionPosition = Vector< 3, float >::midPoint(
			movableEntityA.getWorldCoordinates().position(),
			movableEntityB.getWorldCoordinates().position()
		);

		this->addCollision(CollisionType::MovableEntity, &movableEntityB, collisionPosition, collisionDirection);
		
		return true;
	}
	
	bool
	Collider::checkCollisionAgainstStatic (AbstractEntity & movableEntityA, AbstractEntity & staticEntityB) noexcept
	{
		Vector< 3, float > collisionDirection;
		auto collisionOverflow = 0.0F;

		/* TODO: Add sphere <> box collision. */
		if ( movableEntityA.sphereCollisionIsEnabled() && staticEntityB.sphereCollisionIsEnabled() )
		{
			if ( !isSphereCollisionWith(staticEntityB, movableEntityA, collisionOverflow, collisionDirection) )
			{
				return false;
			}
		}
		else
		{
			if ( !isBoxCollisionWith(staticEntityB, movableEntityA, collisionOverflow, collisionDirection) )
			{
				return false;
			}
		}

		/* NOTE: Location correction. */
		movableEntityA.move(collisionDirection.scaled(collisionOverflow), TransformSpace::World);

		/* NOTE: Collision declaration. */
		const auto collisionPosition = Vector< 3, float >::midPoint(
			movableEntityA.getWorldCoordinates().position(),
			staticEntityB.getWorldCoordinates().position()
		);

		this->addCollision(CollisionType::StaticEntity, &staticEntityB, collisionPosition, collisionDirection);

		return true;
	}

	void
	Collider::resolveCollisions (AbstractEntity & targetEntity) noexcept
	{
		for ( const auto & collision : m_collisions )
		{
			switch ( collision.type() )
			{
				/* TODO: Get physical properties from the scene. */
				case CollisionType::SceneBoundary :
				{
					auto * movableTrait = targetEntity.getMovableTrait();
					const auto speedAtHit = movableTrait->deflect(collision.direction(), 1.0F);

					movableTrait->onHit(speedAtHit * targetEntity.physicalObjectProperties().mass());
				}
					break;

				/* TODO: Get physical properties from the scene ground. */
				case CollisionType::SceneGround :
				{
					auto * movableTrait = targetEntity.getMovableTrait();
					const auto speedAtHit = movableTrait->deflect(collision.direction(), 0.5F);

					movableTrait->onHit(speedAtHit * targetEntity.physicalObjectProperties().mass());
				}
					break;

				/* NOTE: As the main entity is static, we only modify the collided movable trajectory. */
				case CollisionType::StaticEntity :
				{
					auto * movableTrait = targetEntity.getMovableTrait();
					const auto speedAtHit = movableTrait->deflect(collision.direction(), collision.entity()->physicalObjectProperties().bounciness());

					movableTrait->onHit(speedAtHit * targetEntity.physicalObjectProperties().mass());
				}
					break;

				/* NOTE: Both entities are movable, we modify both trajectories. */
				case CollisionType::MovableEntity :
				{
					const auto & objectAProperties = targetEntity.physicalObjectProperties();
					const auto & objectBProperties = collision.entity()->physicalObjectProperties();

					auto * movableTraitA = targetEntity.getMovableTrait();
					auto * movableTraitB = collision.entity()->getMovableTrait();

					/* Force transfer. Momentum problem.
					 * TODO: Incorrect impact forces distribution.
					 * NOTE : https://www.youtube.com/watch?v=VVC_9Qi6zvw */
					const auto totalMass = objectAProperties.mass() + objectBProperties.mass();
					const auto speedMassA = movableTraitA->linearSpeed() * targetEntity.physicalObjectProperties().mass();
					const auto speedMassB = movableTraitB->linearSpeed() * collision.entity()->physicalObjectProperties().mass();
					const auto force = (speedMassA - speedMassB) / totalMass;
					const auto totalSpeedMass = speedMassA + speedMassB;

					const auto transferredSpeedB = movableTraitB->linearSpeed() * objectBProperties.bounciness();
					movableTraitA->addAcceleration(collision.direction().scaled(force + transferredSpeedB));
					movableTraitA->stopMovement();
					movableTraitA->onHit(totalSpeedMass);

					const auto transferredSpeedA = movableTraitA->linearSpeed() * objectAProperties.bounciness();
					movableTraitB->addAcceleration(-collision.direction().scaled(force + transferredSpeedA));
					movableTraitB->stopMovement();
					movableTraitB->onHit(totalSpeedMass);
				}
					break;
			}
		}

		m_collisions.clear();
	}

	bool
	Collider::isSphereCollisionWith (const AbstractEntity & sphereEntityA, const AbstractEntity & sphereEntityB, float & overflow, Vector< 3, float > & direction) noexcept
	{
		const auto sphereA = sphereEntityA.getWorldBoundingSphere();
		const auto sphereB = sphereEntityB.getWorldBoundingSphere();

		overflow = Sphere< float >::getIntersectionOverlap(sphereA, sphereB);

		if ( overflow <= 0.0F )
		{
			return false;
		}

		direction = (sphereB.position() - sphereA.position()).normalize();

		return true;
	}

	bool
	Collider::isBoxCollisionWith (const AbstractEntity & boxEntityA, const AbstractEntity & boxEntityB, float & overflow, Vector< 3, float > & direction) noexcept
	{
		/* NOTE: We check first with axis-aligned bounding box ... */
		if ( !boxEntityA.getWorldBoundingBox().isCollidingWith(boxEntityB.getWorldBoundingBox()) )
		{
			return false;
		}

		/* NOTE: Then with oriented bounding box ... */
		overflow = OrientedCuboid< float >::isIntersecting(
			{boxEntityA.localBoundingBox(), boxEntityA.getWorldCoordinates()},
			{boxEntityB.localBoundingBox(), boxEntityB.getWorldCoordinates()},
			direction
		);

		return overflow > 0.0F;
	}

	bool
	Collider::isBoxSphereCollisionWith (const AbstractEntity & /*boxEntity*/, const AbstractEntity & /*sphereEntity*/, float & /*overflow*/, Vector< 3, float > & /*direction*/) noexcept
	{
		/*const auto box = boxEntity.getWorldBoundingBox();
		const auto sphere = sphereEntity.getWorldBoundingSphere();

		overflow = Cuboid< float >::getIntersectionOverlap(box, sphere);

		return overflow > 0.0F;*/

		return false;
	}
}
