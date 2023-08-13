/*
 * Emeraude/Physics/Collider.cpp
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

#include "Collider.hpp"

/* Local inclusions */
#include "Math/OrientedCuboid.hpp"

namespace Emeraude::Physics
{
	using namespace Libraries;
	using namespace Libraries::Math;
	using namespace Scenes;

	Collider::Collider (std::shared_ptr< Node > node) noexcept
		: m_node{std::move(node)}
	{

	}

	CollisionManifold &
	Collider::collisionManifold () noexcept
	{
		return m_collisionsManifold;
	}

	const CollisionManifold &
	Collider::collisionManifold () const noexcept
	{
		return m_collisionsManifold;
	}

	void
	Collider::checkCollision (Node * against) noexcept
	{
		Vector< 3, float > collisionDirection{};
		auto collisionOverflow = 0.0F;

		if ( m_node->sphereCollisionIsEnabled() && !Collider::isSphereCollision(m_node.get(), against, collisionOverflow, collisionDirection) )
		{
			return;
		}

		if ( !Collider::isBoxCollision(m_node.get(), against, collisionOverflow, collisionDirection) )
		{
			return;
		}

		/* NOTE: Add a small gape. */
		collisionOverflow += CollisionCorrectionDistance;

		/* If the other node is a deflector (Not movable), we just act over current node.
		 * Otherwise, we share the impact between both nodes. */
		if ( against->isMovable() )
		{
			const auto speedMassA = m_node->getSpeed() * m_node->physicalObjectProperties().mass();
			const auto totalMass = m_node->physicalObjectProperties().mass() + against->physicalObjectProperties().mass();

			/* Clip position at the intersection to prevent multiple collision. */
			{
				const auto influenceA = m_node->physicalObjectProperties().mass() / totalMass;
				const auto influenceB = against->physicalObjectProperties().mass() / totalMass;

				m_node->moveBy(collisionDirection.scaled(-(collisionOverflow * influenceB)), TransformSpace::World);
				against->moveBy(collisionDirection.scaled(collisionOverflow * influenceA), TransformSpace::World);
			}

			/* Force transfer. Momentum problem.
			 * NOTE : https://www.youtube.com/watch?v=VVC_9Qi6zvw */
			const auto speedMassB = against->getSpeed() * against->physicalObjectProperties().mass();
			const auto force = (speedMassA + speedMassB) / totalMass;

			m_node->addRawAcceleration(collisionDirection.scaled(-force));
			m_node->clearVelocity();

			against->addRawAcceleration(collisionDirection.scaled(force));
			against->clearVelocity();
		}
		else
		{
			/* Clip position against the other node. */
			m_node->moveBy(collisionDirection.scaled(-collisionOverflow), TransformSpace::World);

			/* Adds the collision vector. */
			m_collisionsManifold.addCollision(Collision::Type::Node, &against, -collisionDirection, 0.0F);
		}
	}

	void
	Collider::checkCollision (StaticEntity * against) noexcept
	{
		Vector< 3, float > collisionDirection{};
		auto collisionOverflow = 0.0F;

		if ( m_node->sphereCollisionIsEnabled() && !Collider::isSphereCollision(m_node.get(), against, collisionOverflow, collisionDirection) )
		{
			return;
		}

		if ( !Collider::isBoxCollision(m_node.get(), against, collisionOverflow, collisionDirection) )
		{
			return;
		}

		/* NOTE: Add a small gape. */
		collisionOverflow += CollisionCorrectionDistance;

		/* Clip position against the other node. */
		m_node->moveBy(collisionDirection.scaled(-collisionOverflow), TransformSpace::World);

		/* Adds the collision vector. */
		m_collisionsManifold.addCollision(Collision::Type::StaticEntity, &against, -collisionDirection, 0.0F);
	}

	void
	Collider::resolveCollisions () const noexcept
	{
		Vector< 3, float > globalCollision{};

		for ( const auto & collision : m_collisionsManifold.collisions() )
		{
			globalCollision += collision.direction();

			/* FIXME: Scene look to notify itself ... */
			//m_node->notify(Node::Hit, &node);

			switch ( collision.type() )
			{
				case Collision::Type::SceneAreaBoundaries :
					//m_node->notify(Node::HitSceneAreaBoundaries, &node);
					break;

				case Collision::Type::SceneAreaGround :
					//m_node->notify(Node::HitSceneAreaGround, &node);

					if ( m_node->getSpeed() <= InertiaThreshold< float > )
					{
						/* Completely stops the object. */
						/* FIXME: Incorrect way, should use mass and forces to stop the movement naturally. */
						m_node->stopMovement();

						/* Prevent the object to add gravity and drag force. */
						m_node->pauseSimulation(true);
					}
					break;

				case Collision::Type::StaticEntity :
					break;

				case Collision::Type::Node :
					//m_node->notify(Node::HitNode, &node);
					break;
			}
		}

		m_node->deflect(globalCollision.normalize());
	}

	bool
	Collider::isSphereCollision (const AbstractEntity * entityA, const AbstractEntity * entityB, float & overflow, Vector< 3, float > & direction) noexcept
	{
		overflow = Sphere< float >::getIntersectionOverlap(entityA->getWorldBoundingSphere(), entityB->getWorldBoundingSphere());

		if ( overflow <= 0.0F )
		{
			return false;
		}

		direction = (entityB->getWorldCoordinates().position() - entityA->getWorldCoordinates().position()).normalize();

		return true;
	}

	bool
	Collider::isBoxCollision (const AbstractEntity * entityA, const AbstractEntity * entityB, float & overflow, Vector< 3, float > & direction) noexcept
	{
		/* Axis aligned bounding box test first. */
		if ( !entityA->getWorldBoundingBox().isCollidingWith(entityB->getWorldBoundingBox()) )
		{
			return false;
		}

		/* Oriented bounding box then. */
		overflow = OrientedCuboid< float >::isIntersecting(
			{entityA->localBoundingBox(), entityA->getWorldCoordinates()},
			{entityB->localBoundingBox(), entityB->getWorldCoordinates()},
			direction
		);

		return overflow > 0.0F;
	}
}
