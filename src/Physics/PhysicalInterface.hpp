/*
 * Emeraude/Physics/PhysicalInterface.hpp
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
#include "PhysicalObjectProperties.hpp"

namespace Emeraude::Physics
{
	/**
	 * @brief Defines physical properties to an object in the 3D world.
	 */
	class PhysicalInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			PhysicalInterface (const PhysicalInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			PhysicalInterface (PhysicalInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return PhysicalInterface &
			 */
			PhysicalInterface & operator= (const PhysicalInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return PhysicalInterface &
			 */
			PhysicalInterface & operator= (PhysicalInterface && copy) noexcept = default;

			/**
			 * @brief Destructs the physical interface.
			 */
			virtual ~PhysicalInterface () = default;

			/**
			 * @brief Enables the sphere collision simplification.
			 * @return state The state.
			 */
			virtual void enableSphereCollision (bool state) noexcept = 0;

			/**
			 * @brief Returns whether the sphere collision is enabled or not.
			 * @return bool
			 */
			[[nodiscard]]
			virtual bool sphereCollisionIsEnabled () const noexcept = 0;

			/**
			 * @brief Returns the physical properties.
			 * @return const PhysicalObjectProperties &
			 */
			[[nodiscard]]
			virtual const PhysicalObjectProperties & physicalObjectProperties () const noexcept = 0;

			/**
			 * @brief Returns the physical properties.
			 * @return PhysicalObjectProperties &
			 */
			[[nodiscard]]
			virtual PhysicalObjectProperties & physicalObjectProperties () noexcept = 0;

		protected:

			/**
			 * @brief Constructs a physical interface.
			 */
			PhysicalInterface () noexcept = default;
	};
}
