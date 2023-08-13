/*
 * Emeraude/Scenes/InfluenceAreaInterface.hpp
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
#include "Physics/MovableTrait.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief The influence area interface.
	 * It defines en influence area around a scene entity.
	 */
	class InfluenceAreaInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			InfluenceAreaInterface (const InfluenceAreaInterface & copy) noexcept = delete;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			InfluenceAreaInterface (InfluenceAreaInterface && copy) noexcept = delete;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return InfluenceAreaInterface &
			 */
			InfluenceAreaInterface & operator= (const InfluenceAreaInterface & copy) noexcept = delete;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return InfluenceAreaInterface &
			 */
			InfluenceAreaInterface & operator= (InfluenceAreaInterface && copy) noexcept = delete;

			/**
			 * @brief Destructs the influence area.
			 */
			virtual ~InfluenceAreaInterface () = default;

			/**
			 * @brief Returns whether a scene entity is under the influence of this area.
			 * @param entity A reference to a scene movable.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool isUnderInfluence (const Physics::MovableTrait & movable) const noexcept = 0;

			/**
			 * @brief Returns the strength of influence to a scene entity from this area.
			 * @param entity A reference to a scene movable.
			 * @return float
			 */
			[[nodiscard]]
			virtual float influenceStrength (const Physics::MovableTrait & movable) const noexcept = 0;

		protected:

			/**
			 * @brief Constructs an influence area.
			 */
			InfluenceAreaInterface () noexcept = default;

	};
}
