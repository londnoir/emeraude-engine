/*
 * src/Scenes/LocatableInterface.hpp
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

/* Local inclusions for usages. */
#include "Libraries/Math/CartesianFrame.hpp"
#include "Libraries/Math/Cuboid.hpp"

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
			 * @brief Sets an absolute position in meters.
			 * @param position A reference to a vector.
			 * @param transformSpace The space where occurs the move.
			 * @return void
			 */
			virtual void setPosition (const Libraries::Math::Vector< 3, float > & position, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Sets an absolute X position in meters.
			 * @param position The position on X axis.
			 * @param transformSpace The space where occurs the move.
			 * @return void
			 */
			virtual void setXPosition (float position, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Sets an absolute Y position in meters.
			 * @param position The position on Y axis.
			 * @param transformSpace The space where occurs the move.
			 * @return void
			 */
			virtual void setYPosition (float position, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Sets an absolute Z position in meters.
			 * @param position The position on Z axis.
			 * @param transformSpace The space where occurs the move.
			 * @return void
			 */
			virtual void setZPosition (float position, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Shifts the position in meters.
			 * @param distance A reference to a vector.
			 * @param transformSpace The space where occurs the move.
			 * @return void
			 */
			virtual void move (const Libraries::Math::Vector< 3, float > & distance, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Shifts the X position in meters.
			 * @param distance The distance on X axis.
			 * @param transformSpace The space where occurs the move.
			 * @return void
			 */
			virtual void moveX (float distance, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Shifts the Y position in meters.
			 * @param distance The distance on Y axis.
			 * @param transformSpace The space where occurs the move.
			 * @return void
			 */
			virtual void moveY (float distance, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Shifts the Z position in meters.
			 * @param distance The distance on Z axis.
			 * @param transformSpace The space where occurs the move.
			 * @return void
			 */
			virtual void moveZ (float distance, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Performs a rotation around an arbitrary axis.
			 * @param radian The angle expressed in radians. You can use the function Math::Radians(degree).
			 * @param axis A vector to define the axis.
			 * @param transformSpace The space where occurs the rotation.
			 * @return void
			 */
			virtual void rotate (float radian, const Libraries::Math::Vector< 3, float > & axis, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Performs a rotation around the X axis.
			 * @param radian The angle expressed in radians. You can use the function Math::Radians(degree).
			 * @param transformSpace The space where occurs the rotation.
			 * @return void
			 */
			virtual void pitch (float radian, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Performs a rotation around the Y axis.
			 * @param radian The angle expressed in radians. You can use the function Math::Radians(degree).
			 * @param transformSpace The space where occurs the rotation.
			 * @return void
			 */
			virtual void yaw (float radian, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Performs a rotation around the Z axis.
			 * @param radian The angle expressed in radians. You can use the function Math::Radians(degree).
			 * @param transformSpace The space where occurs the rotation.
			 * @return void
			 */
			virtual void roll (float radian, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Applies a scale factor on the coordinates.
			 * @param factor A reference to a scale vector.
			 * @param transformSpace The space where occurs the scale.
			 * @return void
			 */
			virtual void scale (const Libraries::Math::Vector< 3, float > & factor, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Applies a scale factor on the coordinates.
			 * @param factor an unidirectional factor value.
			 * @param transformSpace The space where occurs the scale.
			 * @return void
			 */
			virtual void scale (float factor, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Applies a scale factor on the coordinates.
			 * @param factor an unidirectional factor value.
			 * @param transformSpace The space where occurs the scale.
			 * @return void
			 */
			virtual void scaleX (float factor, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Applies a scale factor on the coordinates.
			 * @param factor an unidirectional factor value.
			 * @param transformSpace The space where occurs the scale.
			 * @return void
			 */
			virtual void scaleY (float factor, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Applies a scale factor on the coordinates.
			 * @param factor an unidirectional factor value.
			 * @param transformSpace The space where occurs the scale.
			 * @return void
			 */
			virtual void scaleZ (float factor, Libraries::Math::TransformSpace transformSpace) noexcept = 0;

			/**
			 * @brief Points the backward (Z- axis) of the coordinates system toward the target.
			 * @note Use this for pointing a camera.
			 * @param target A position to look at.
			 * @param flipZAxis Flip the final Z axis.
			 * @return void
			 */
			virtual void lookAt (const Libraries::Math::Vector< 3, float > & target, bool flipZAxis) noexcept = 0;

			/**
			 * @brief Sets the local coordinates of this entity.
			 * @return Libraries::Math::Coordinates< float > &
			 */
			virtual void setLocalCoordinates (const Libraries::Math::CartesianFrame< float > & coordinates) noexcept = 0;

			/**
			 * @brief Returns the local coordinates of a 3D world entity.
			 * @return const Libraries::Math::Coordinates< float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::CartesianFrame< float > & localCoordinates () const noexcept = 0;

			/**
			 * @brief Returns the internal local coordinates of a 3D world entity.
			 * @return const Libraries::Math::Coordinates< float > &
			 */
			[[nodiscard]]
			virtual Libraries::Math::CartesianFrame< float > & localCoordinates () noexcept = 0;

			/**
			 * @brief Returns the world coordinates of a 3D world entity.
			 * @return Libraries::Math::Coordinates< float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::CartesianFrame< float > getWorldCoordinates () const noexcept = 0;

			/**
			 * @brief Returns the world bounding box of a 3D world entity.
			 * @return const Libraries::Math::Cuboid< float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Cuboid< float > & localBoundingBox () const noexcept = 0;

			/**
			 * @brief Returns the world bounding box of a 3D world entity.
			 * @return Libraries::Math::Cuboid< float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Cuboid< float > getWorldBoundingBox () const noexcept = 0;

			/**
			 * @brief Returns the world bounding sphere of a 3D world entity.
			 * @return const Libraries::Math::Sphere< float > &
			 */
			[[nodiscard]]
			virtual const Libraries::Math::Sphere< float > & localBoundingSphere () const noexcept = 0;

			/**
			 * @brief Returns the world bounding sphere of a 3D world entity.
			 * @return Libraries::Math::Sphere< float >
			 */
			[[nodiscard]]
			virtual Libraries::Math::Sphere< float > getWorldBoundingSphere () const noexcept = 0;

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

		protected:

			/**
			 * @brief Constructs a locatable interface.
			 */
			LocatableInterface () noexcept = default;
	};
}
