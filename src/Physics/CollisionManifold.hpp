/*
 * Emeraude/Physics/CollisionManifold.hpp
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
#include <vector>

/* Local inclusions for usages. */
#include "Math/Vector.hpp"
#include "Collision.hpp"

namespace Emeraude::Physics
{
	static constexpr auto CollisionCorrectionDistance = 0.0001F;

	/**
	 * @brief This class stacks a collection of collisions for simulation.
	 */
	class CollisionManifold final
	{
		public:

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PhysicsCollisionManifold"};

			/**
			 * @brief Constructs a default collision manifold.
			 */
			CollisionManifold () noexcept = default;

			/**
			 * @brief Adds a collision to the collection.
			 * @param type The type of collision.
			 * @param target The raw pointer to hit object.
			 * @param direction The direction vector of the hit.
			 * @param otherSpeed The speed of the other object.
			 */
			void addCollision (Collision::Type type, const void * target, const Libraries::Math::Vector< 3, float > & direction, float otherSpeed = 0.0F) noexcept;

			/**
			 * @brief hitSomething
			 * @return bool
			 */
			[[nodiscard]]
			bool hitSomething () const noexcept;

			/**
			 * @brief Returns the list of collisions.
			 * @return const std::vector< Collision > &
			 */
			[[nodiscard]]
			const std::vector< Collision > & collisions () const noexcept;

			/**
			 * @brief Removes all collision registered.
			 */
			void reset () noexcept;

		private:

			std::vector< Collision > m_collisions{};
	};
}
