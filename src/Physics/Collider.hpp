/*
 * Emeraude/Physics/Collider.hpp
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

/* Local inclusions for usages. */
#include "Scenes/Node.hpp"
#include "CollisionManifold.hpp"
#include "Scenes/StaticEntity.hpp"

namespace Emeraude::Physics
{
	/**
	 * @brief The Collider class
	 */
	class Collider final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PhysicsCollider"};

			/**
			 * @brief Constructs a collider.
			 * @param node A node smart pointer.
			 */
			explicit Collider (std::shared_ptr< Scenes::Node > node) noexcept;

			/**
			 * @brief Returns the collision manifold.
			 * @return CollisionManifold &
			 */
			[[nodiscard]]
			CollisionManifold & collisionManifold () noexcept;

			/**
			 * @brief Returns the collision manifold.
			 * @return const CollisionManifold &
			 */
			[[nodiscard]]
			const CollisionManifold & collisionManifold () const noexcept;

			/**
			 * @brief Checks if a collision occurs with an other scene node.
			 * @param against A pointer to an other scene node.
			 * @return void
			 */
			void checkCollision (Scenes::Node * against) noexcept;

			/**
			 * @brief Checks if a collision occurs with a static entity.
			 * @param against A pointer to a static entity.
			 * @return void
			 */
			void checkCollision (Scenes::StaticEntity * against) noexcept;

			/**
			 * @brief Prepares the scene subdivision to speed up collision tests and other things.
			 * @param hits The node hit list.
			 * @return void
			 */
			void resolveCollisions () const noexcept;

		private:

			/**
			 * @brief Returns the possible overflow between two entities using the sphere collision model.
			 * @param entityA A pointer to the first entity.
			 * @param entityB A pointer to the second entity.
			 * @param overflow A reference to put the distance of collision overflow.
			 * @param direction A reference to put the direction of collision if exists.
			 * @return bool
			 */
			[[nodiscard]]
			static bool isSphereCollision (const Scenes::AbstractEntity * entityA, const Scenes::AbstractEntity * entityB, float & overflow, Libraries::Math::Vector< 3, float > & direction) noexcept;

			/**
			 * @brief Returns the possible overflow between two entities using the box collision model.
			 * @param entityA A pointer to the first entity.
			 * @param entityB A pointer to the second entity.
			 * @param overflow A reference to put the distance of collision overflow.
			 * @param direction A reference to put the direction of collision if exists.
			 * @return bool
			 */
			[[nodiscard]]
			static bool isBoxCollision (const Scenes::AbstractEntity * entityA, const Scenes::AbstractEntity * entityB, float & overflow, Libraries::Math::Vector< 3, float > & direction) noexcept;

			std::shared_ptr< Scenes::Node > m_node;
			CollisionManifold m_collisionsManifold{};
	};
}
