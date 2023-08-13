/*
 * Emeraude/Physics/Collision.hpp
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

/* Local inclusions for usages. */
#include "Math/Vector.hpp"

namespace Emeraude::Physics
{
	/**
	 * @brief This class defines a collision.
	 */
	class Collision final
	{
		public:

			/** @brief Collision type. */
			enum class Type
			{
				SceneAreaBoundaries,
				SceneAreaGround,
				StaticEntity,
				Node
			};

			/** @brief Class identifier. */
			static constexpr auto ClassId{"PhysicsCollision"};

			/**
			 * @brief Constructs a collision structure.
			 * @param type
			 * @param target
			 * @param direction
			 * @param speed
			 */
			Collision (Type type, const void * target, const Libraries::Math::Vector< 3, float > & direction, float speed) noexcept;

			/**
			 * @brief Returns the collision type.
			 * @return Type
			 */
			[[nodiscard]]
			Type type () const noexcept;

			/**
			 * @brief Returns a raw pointer to the object hit.
			 * @return const void *
			 */
			[[nodiscard]]
			const void * target () const noexcept;

			/**
			 * @brief Returns the direction vector of the collision.
			 * @return const Libraries::Math::Vector< 3, float > &
			 */
			[[nodiscard]]
			const Libraries::Math::Vector< 3, float > & direction () const noexcept;

			/**
			 * @brief Returns the speed at collision.
			 * @return float
			 */
			[[nodiscard]]
			float speed () const noexcept;

		private:

			Type m_type;
			const void * m_target;
			Libraries::Math::Vector< 3, float > m_direction;
			float m_speed;
	};
}
