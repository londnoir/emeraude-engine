/*
 * Emeraude/Scenes/LocatableInterface.hpp
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
#include "Math/Coordinates.hpp"
#include "Math/Cuboid.hpp"
#include "Math/Sphere.hpp"

namespace Emeraude::Scenes
{
	/**
	 * @brief The LocatableInterface class is used to locate something in the 3D world and set its coordinates.
	 */
	class LocatableInterface
	{
		public:

			/**
			 * @brief Copy constructor.
			 * @param copy A reference to the copied instance.
			 */
			LocatableInterface (const LocatableInterface & copy) noexcept = default;

			/**
			 * @brief Move constructor.
			 * @param copy A reference to the copied instance.
			 */
			LocatableInterface (LocatableInterface && copy) noexcept = default;

			/**
			 * @brief Copy assignment.
			 * @param copy A reference to the copied instance.
			 * @return LocatableInterface &
			 */
			LocatableInterface & operator= (const LocatableInterface & copy) noexcept = default;

			/**
			 * @brief Move assignment.
			 * @param copy A reference to the copied instance.
			 * @return LocatableInterface &
			 */
			LocatableInterface & operator= (LocatableInterface && copy) noexcept = default;

			/**
			 * @brief Destructs the locatable interface.
			 */
			virtual ~LocatableInterface () = default;

			/**
			 * @brief Moves the entity to a new position.
			 * @param position A reference to a vector.
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual void moveTo (const Libraries::Math::Vector< 3, float > & position, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept;

			/**
			 * @brief Moves the entity to a new X position.
			 * @param xPosition The new position on X axis.
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual void moveOnXAxisTo (float xPosition, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept;

			/**
			 * @brief Moves the entity to a new Y position.
			 * @param yPosition The new position on Y axis.
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual void moveOnYAxisTo (float yPosition, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept;

			/**
			 * @brief Moves the entity to a new Z position.
			 * @param zPosition The new position on Z axis.
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual void moveOnZAxisTo (float zPosition, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept;

			/**
			 * @brief Moves the entity toward a direction.
			 * @param distance A reference to a vector.
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual void moveBy (const Libraries::Math::Vector< 3, float > & distance, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept;

			/**
			 * @brief Moves the entity on the X axis.
			 * @param xDistance The distance on X axis.
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual void moveOnXAxisBy (float xDistance, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept;

			/**
			 * @brief Moves the entity on the Y axis.
			 * @param xDistance The distance on Y axis.
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual void moveOnYAxisBy (float yDistance, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept;

			/**
			 * @brief Moves the entity on the Z axis.
			 * @param xDistance The distance on Z axis.
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual void moveOnZAxisBy (float zDistance, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Parent) noexcept;

			/**
			 * @brief Performs a rotation around an arbitrary axis.
			 * @param radian The angle expressed in radians. You can use the function Math::Radians(degree).
			 * @param axis A vector to define the axis.
			 * @param transformSpace The space from where the X axis will be picked up to performs the rotation.
			 * 'Local' use the Node axis, 'Parent' use the parent node axis then 'World' the world origin axis.
			 * @return void
			 */
			virtual void rotate (float radian, const Libraries::Math::Vector< 3, float > & axis, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Local) noexcept;

			/**
			 * @brief Performs a rotation around the X axis.
			 * @param radian The angle expressed in radians. You can use the function Math::Radians(degree).
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual
			inline
			void
			pitch (float radian, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Local) noexcept final
			{
				this->rotate(radian, Libraries::Math::Vector< 3, float >::positiveX(), transformSpace);
			}

			/**
			 * @brief Performs a rotation around the Y axis.
			 * @param radian The angle expressed in radians. You can use the function Math::Radians(degree).
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual
			inline
			void
			yaw (float radian, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Local) noexcept final
			{
				this->rotate(radian, Libraries::Math::Vector< 3, float >::positiveY(), transformSpace);
			}

			/**
			 * @brief Performs a rotation around the Z axis.
			 * @param radian The angle expressed in radians. You can use the function Math::Radians(degree).
			 * @param transformSpace The transform space relative to.
			 * @return void
			 */
			virtual
			inline
			void
			roll (float radian, Libraries::Math::TransformSpace transformSpace = Libraries::Math::TransformSpace::Local) noexcept final
			{
				this->rotate(radian, Libraries::Math::Vector< 3, float >::positiveZ(), transformSpace);
			}

			/**
			 * @brief Applies a scale factor on the coordinates.
			 * @param factor A reference to a scale vector.
			 * @return void
			 */
			virtual void scale (const Libraries::Math::Vector< 3, float > & factor) noexcept;

			/**
			 * @brief Applies a scale factor on the coordinates.
			 * @param xFactor The X axis factor value.
			 * @param yFactor The Y axis factor value.
			 * @param zFactor The Z axis factor value.
			 * @return void
			 */
			virtual void scale (float xFactor, float yFactor, float zFactor) noexcept;

			/**
			 * @brief Applies a scale factor on the coordinates.
			 * @param factor an unidirectional factor value.
			 * @return void
			 */
			virtual void scale (float factor) noexcept;

			/**
			 * @brief Points the backward (Z- axis) of the coordinates system toward the target.
			 * @note Use this for pointing a camera.
			 * @param target A position to look at.
			 * @return void
			 */
			virtual void lookAt (const Libraries::Math::Vector< 3, float > & target) noexcept final;

			/**
			 * @brief Points the forward (Z+ axis) of the coordinates system toward the target.
			 * @note Use this for pointing an object toward an other.
			 * @param target A position to look at.
			 * @return void
			 */
			virtual void pointTo (const Libraries::Math::Vector< 3, float > & target) noexcept final;

			/**
			 * @brief Sets the local coordinates of this entity.
			 * @return Libraries::Math::Coordinates< float > &
			 */
			virtual void setLocalCoordinates (const Libraries::Math::Coordinates< float > & coordinates) noexcept = 0;

			/**
			 * @brief Returns the local coordinates of a 3D world entity.
			 * @return const Libraries::Math::Coordinates< float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Coordinates< float > & localCoordinates () const noexcept = 0;

			/**
			 * @brief Returns the world bounding box of a 3D world entity.
			 * @return const Libraries::Math::Cuboid< float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Cuboid< float > & localBoundingBox () const noexcept = 0;

			/**
			 * @brief Returns the world bounding sphere of a 3D world entity.
			 * @return const Libraries::Math::Sphere< float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Sphere< float > & localBoundingSphere () const noexcept = 0;

			/**
			 * @brief Returns the world coordinates of a 3D world entity.
			 * @return Libraries::Math::Coordinates< float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Coordinates< float > getWorldCoordinates () const noexcept = 0;

			/**
			 * @brief Returns the world bounding box of a 3D world entity.
			 * @return Libraries::Math::Cuboid< float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Cuboid< float > getWorldBoundingBox () const noexcept = 0;

			/**
			 * @brief Returns the world bounding sphere of a 3D world entity.
			 * @return Libraries::Math::Sphere< float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Sphere< float > getWorldBoundingSphere () const noexcept = 0;

		protected:

			/**
			 * @brief Constructs a locatable interface.
			 */
			LocatableInterface () noexcept = default;

			/**
			 * @brief Returns the internal local coordinates of a 3D world entity.
			 * @return const Libraries::Math::Coordinates< float > &
			 */
			[[nodiscard]]
			virtual Libraries::Math::Coordinates< float > & getWritableLocalCoordinates () noexcept = 0;
	};
}
