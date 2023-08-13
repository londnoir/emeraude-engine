/*
 * Libraries/Math/Coordinates.hpp
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

/* C/C++ standard libraries */
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>

/* Local inclusions for usages. */
#include "Base.hpp"
#include "Matrix.hpp"

/* OpenGL adopts the Right-Hand Coordinate System (RHS).
 * In the RHS, the x-axis is pointing right, y-axis is pointing up,
 * and z-axis is pointing out of the screen.
 * With your right-hand fingers curving from the x-axis
 * towards the y-axis, the thumb is pointing at the z-axis.
 * RHS is counter-clockwise (CCW).
 * The 3D Cartesian Coordinates is an RHS.
 *
 * Some graphics software (such as Microsoft Direct3D) use
 * Left-hand System (LHS), where the z-axis is inverted.
 * LHS is clockwise (CW). In this article,
 * we shall adopt the RHS and CCW used in OpenGL.
*/

namespace Libraries::Math
{
	// NOLINTBEGIN(*-magic-numbers)

	/**
	 * @brief The transform space enumeration.
	 */
	enum class TransformSpace
	{
		Local,
		Parent,
		World
	};

	/**
	 * @brief Defines a 3D coordinates system.
	 * @tparam data_t
	 */
	template< typename data_t = float, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
	class Coordinates final
	{
		public:

			/** @brief Default constructor. */
			constexpr
			Coordinates () noexcept = default;

			/**
			 * @brief Constructs coordinates from a position vector.
			 * @param position A reference to a vector for position.
			 */
			explicit
			constexpr
			Coordinates (const Vector< 3, data_t > & position) noexcept
				: m_position(position)
			{

			}

			/**
			 * @brief Constructs coordinates from a model matrix.
			 * @param matrix A reference to a matrix.
			 */
			explicit
			constexpr
			Coordinates (const Matrix< 4, data_t > & matrix) noexcept
				: m_position(matrix[M4x4Col3Row0], matrix[M4x4Col3Row1], matrix[M4x4Col3Row2]),
				  m_upward(matrix[M4x4Col1Row0], matrix[M4x4Col1Row1], matrix[M4x4Col1Row2]),
				  m_forward(matrix[M4x4Col2Row0], matrix[M4x4Col2Row1], matrix[M4x4Col2Row2])
			{

			}

			/**
			 * @brief Construct from a position vector and forward vector.
			 * @note This version will compute upward vector from position and forward vector.
			 * @param position A vector the position.
			 * @param forward A vector to point forward.
			 */
			Coordinates (const Vector< 3, data_t > & position, const Vector< 3, data_t > & forward) noexcept
				: m_position(position)
			{
				this->setForwardVector(forward);
			}

			/**
			 * @brief Construct from raw vectors.
			 * @param position A vector the position.
			 * @param upward A vector to point upward.
			 * @param forward A vector to point forward.
			 * @param scale A scaling vector. By default [1, 1, 1].
			 */
			constexpr
			Coordinates (const Vector< 3, data_t > & position, const Vector< 3, data_t > & upward, const Vector< 3, data_t > & forward, const Vector< 3, data_t > & scale = {1, 1, 1}) noexcept
				: m_position(position), m_upward(upward), m_forward(forward), m_scaleVector(scale)
			{

			}

			Coordinates
			operator+ (const Coordinates & operand) const noexcept
			{
				auto newCoordinates = *this;

				newCoordinates.m_position += operand.m_position;

				/* FIXME: Check this */
				newCoordinates.m_upward += operand.m_upward;
				newCoordinates.m_upward.normalize();

				/* FIXME: Check this */
				newCoordinates.m_forward += operand.m_forward;
				newCoordinates.m_forward.normalize();

				newCoordinates.m_scaleVector *= operand.m_scaleVector;

				return newCoordinates;
			}

			static
			Coordinates
			linearInterpolation (const Coordinates & operandA, const Coordinates & operandB, data_t factor) noexcept
			{
				Coordinates result;
				result.m_position = Math::linearInterpolation(operandA.m_position, operandB.m_position, factor);
				result.m_forward = Math::linearInterpolation(operandA.m_forward, operandB.m_forward, factor);
				result.m_upward = Math::linearInterpolation(operandA.m_upward, operandB.m_upward, factor);
				result.m_scaleVector = Math::linearInterpolation(operandA.m_scaleVector, operandB.m_scaleVector, factor);

				return result;
			}

			static
			Coordinates
			cosineInterpolation (const Coordinates & operandA, const Coordinates & operandB, data_t factor) noexcept
			{
				Coordinates result;
				result.m_position = Math::cosineInterpolation(operandA.m_position, operandB.m_position, factor);
				result.m_forward = Math::cosineInterpolation(operandA.m_forward, operandB.m_forward, factor);
				result.m_upward = Math::cosineInterpolation(operandA.m_upward, operandB.m_upward, factor);
				result.m_scaleVector = Math::cosineInterpolation(operandA.m_scaleVector, operandB.m_scaleVector, factor);

				return result;
			}

			[[nodiscard]]
			const Vector< 3, data_t > &
			position () const noexcept
			{
				return m_position;
			}

			void
			setPosition (const Vector< 3, data_t > & vector) noexcept
			{
				m_position = vector;
			}

			void
			setPosition (const Coordinates< data_t > & coords) noexcept
			{
				m_position = coords.m_position;
			}

			void
			setPosition (data_t xValue, data_t yValue, data_t zValue) noexcept
			{
				m_position[X] = xValue;
				m_position[Y] = yValue;
				m_position[Z] = zValue;
			}

			void
			setXPosition (data_t position) noexcept
			{
				m_position[X] = position;
			}

			void
			setYPosition (data_t position) noexcept
			{
				m_position[Y] = position;
			}

			void
			setZPosition (data_t position) noexcept
			{
				m_position[Z] = position;
			}

			/**
			 * Sets the forward vector (Z+) of the coordinates system.
			 *
			 * @note This will re-orient automatically the upward vector (Y+).
			 * @param forward The vector that hold the desired direction for the coordinates.
			 */
			void
			setForwardVector (const Vector< 3, data_t > & forward) noexcept
			{
				m_forward = forward.normalized();

				/* Special case when forward is +Y (0, 1, 0). */
				if ( m_forward == Vector< 3, data_t >::positiveY() )
				{
					m_upward = Vector< 3, data_t >::positiveZ();

					return;
				}

				/* Special case when forward is -Y (0, -1, 0). */
				if ( m_forward == Vector< 3, data_t >::negativeY() )
				{
					m_upward = Vector< 3, data_t >::negativeZ();

					return;
				}

				/* Compute temporal up vector based on the forward vector
				 * watch out when look up/down at 90 degree
				 * for example, forward vector is on the Y axis. */
				if ( std::fabs(m_forward[X]) < 0.0F && std::fabs(m_forward[Z]) < 0.0F )
				{
					/* If forward vector is pointing on +Y axis. */
					m_upward = m_forward[Y] > 0.0F ? Vector<3, data_t>::negativeZ() : Vector<3, data_t>::positiveZ();
				}
				/* In general, up vector is straight up. */
				else
				{
					m_upward = Vector<3, data_t>::positiveY();
				}

				/* Compute the right vector. */
				const auto right = Vector< 3, data_t >::crossProduct(m_upward, m_forward).normalize();

				/* Re-calculate the orthonormal up vector. */
				m_upward = Vector< 3, data_t >::crossProduct(m_forward, right).normalize();
			}

			void
			setForwardVector (data_t xValue, data_t yValue, data_t zValue) noexcept
			{
				this->setForwardVector(xValue, yValue, zValue);
			}

			/** Sets the forward vector (Z+) and the upward vector (Y+) of the coordinates system.
			 * @warning  You must pass correct vectors. */
			void
			setVectors (const Vector< 3, data_t > & forward, const Vector< 3, data_t > & upward) noexcept
			{
				m_forward = forward.normalized();
				m_upward = upward.normalized();
			}

			/**
			 * Point the backward (Z- axis) of the coordinates system toward the target.
			 *
			 * @note Use this for pointing a camera.
			 * @param target A position to look at.
			 */
			void
			lookAt (const Vector< 3, data_t > & target) noexcept
			{
				this->setForwardVector(m_position - target);
			}

			/**
			 * Point the backward (Z- axis) of the coordinates system toward the target.
			 *
			 * @note Same as Coordinates::lookAt() but using a matrix.
			 * @param target A position to look at.
			 */
			void
			lookAtUsingMatrix (const Vector< 3, data_t > & target) noexcept
			{
				auto matrix = Matrix< 4, data_t >::lookAt(m_position, target, m_upward);

				m_forward = (matrix * Vector< 4, data_t >(m_forward, 0)).toVector3();
				m_upward = (matrix * Vector< 4, data_t >(m_upward, 0)).toVector3();
			}

			/**
			 * Point the forward (Z+ axis) of the coordinates system toward the target.
			 *
			 * @note Use this for pointing an object toward an other.
			 * @param target A position to look off.
			 */
			void
			reverseLookAt (const Vector< 3, data_t > & target) noexcept
			{
				this->setForwardVector(target - m_position);
			}

			void
			reverseZ () noexcept
			{
				m_forward.inverse();
			}

			/**
			 * Point the forward (Z+ axis) of the coordinates system toward the target.
			 *
			 * @note Use this for pointing an object toward an other. Alias of reverseLookAt().
			 * @param target A position to look at.
			 */
			void
			pointTo (const Vector< 3, data_t > & target) noexcept
			{
				this->reverseLookAt(target);
			}

			/** Returns the vector pointing to X+ axis. */
			[[nodiscard]]
			Vector< 3, data_t >
			XVector () const noexcept
			{
				return Vector< 3, data_t >::crossProduct(m_upward, m_forward).normalize();
			}

			/** Returns the vector pointing to Y+ axis. */
			[[nodiscard]]
			const Vector< 3, data_t > &
			upwardVector () const noexcept
			{
				return m_upward;
			}

			/** Returns the vector pointing to Z+ axis. */
			[[nodiscard]]
			const Vector< 3, data_t > &
			forwardVector () const noexcept
			{
				return m_forward;
			}

			[[nodiscard]]
			data_t
			pitch () const noexcept
			{
				return Vector< 3, data_t >::angle(m_forward, Vector< 3, data_t >::negativeZ);
			}

			[[nodiscard]]
			data_t
			yaw () const noexcept
			{
				return Vector< 3, data_t >::angle(m_forward, Vector< 3, data_t >::positiveX);
			}

			[[nodiscard]]
			data_t
			roll () const noexcept
			{
				return Vector< 3, data_t >::angle(m_forward, Vector< 3, data_t >::positiveY);
			}

			void
			normalize () noexcept
			{
				m_forward.normalize();
				m_upward.normalize();
			}

			/**
			 * Sets the scale vector.
			 *
			 * @param factor A reference to a scale vector.
			 */
			void
			setScaleVector (const Vector< 3, data_t > & factor) noexcept
			{
				m_scaleVector = factor;
			}

			/**
			 * Sets the scale vector.
			 *
			 * @param xFactor The X axis factor value.
			 * @param yFactor The Y axis factor value.
			 * @param zFactor The Z axis factor value.
			 */
			void
			setScaleVector (data_t xFactor, data_t yFactor, data_t zFactor) noexcept
			{
				m_scaleVector[X] = xFactor;
				m_scaleVector[Y] = yFactor;
				m_scaleVector[Z] = zFactor;
			}

			/**
			 * Sets the scale vector.
			 *
			 * @param factor an unidirectional factor value.
			 */
			void
			setScaleVector (data_t factor) noexcept
			{
				m_scaleVector[X] = factor;
				m_scaleVector[Y] = factor;
				m_scaleVector[Z] = factor;
			}

			[[nodiscard]]
			const Vector< 3, data_t > &
			scaleVector () const noexcept
			{
				return m_scaleVector;
			}

			/** Use the local axis (following his own orientations) to move to the position. */
			void
			translateAlongLocalAxis (data_t xDistance, data_t yDistance, data_t zDistance) noexcept
			{
				if ( !Utility::isZero(xDistance) )
				{
					this->translateAlongLocalXAxis(xDistance);
				}

				if ( !Utility::isZero(yDistance) )
				{
					this->translateAlongLocalYAxis(yDistance);
				}

				if ( !Utility::isZero(zDistance) )
				{
					this->translateAlongLocalZAxis(zDistance);
				}
			}

			void
			translateAlongLocalAxis (const Vector< 3, data_t > & distance) noexcept
			{
				this->translateAlongLocalAxis(distance[X], distance[Y], distance[Z]);
			}

			void
			translateAlongLocalXAxis (data_t distance) noexcept
			{
				m_position += this->XVector() * distance;
			}

			void
			translateAlongLocalYAxis (data_t distance) noexcept
			{
				m_position += m_upward * distance;
			}

			void
			translateAlongLocalZAxis (data_t distance) noexcept
			{
				m_position += m_forward * distance;
			}

			/** Use the world axis to move to the position. */
			void
			translateAlongWorldAxis (const Vector< 3, data_t > & distance) noexcept
			{
				m_position += distance;
			}

			void
			translateAlongWorldAxis (data_t xDistance, data_t yDistance, data_t zDistance) noexcept
			{
				m_position[X] += xDistance;
				m_position[Y] += yDistance;
				m_position[Z] += zDistance;
			}

			void
			translateAlongWorldXAxis (data_t distance) noexcept
			{
				m_position[X] += distance;
			}

			void
			translateAlongWorldYAxis (data_t distance) noexcept
			{
				m_position[Y] += distance;
			}

			void
			translateAlongWorldZAxis (data_t distance) noexcept
			{
				m_position[Z] += distance;
			}

			/** Use a custom axis to move to the position. */
			void
			translateAlongCustomAxis (const Vector< 3, data_t > & distance, const Coordinates & axis) noexcept
			{
				if ( !Utility::isZero(distance[X]) )
				{
					this->translateAlongCustomXAxis(distance[X], axis);
				}

				if ( !Utility::isZero(distance[Y]) )
				{
					this->translateAlongCustomYAxis(distance[Y], axis);
				}

				if ( !Utility::isZero(distance[Z]) )
				{
					this->translateAlongCustomZAxis(distance[Z], axis);
				}
			}

			void
			translateAlongCustomAxis (data_t xDistance, data_t yDistance, data_t zDistance, const Coordinates & axis) noexcept
			{
				if ( !Utility::isZero(xDistance) )
				{
					this->translateAlongCustomXAxis(xDistance, axis);
				}

				if ( !Utility::isZero(yDistance) )
				{
					this->translateAlongCustomYAxis(yDistance, axis);
				}

				if ( !Utility::isZero(zDistance) )
				{
					this->translateAlongCustomZAxis(zDistance, axis);
				}
			}

			void
			translateAlongCustomXAxis (data_t distance, const Coordinates & axis) noexcept
			{
				m_position += axis.XVector() * distance;
			}

			void
			translateAlongCustomYAxis (data_t distance, const Coordinates & axis) noexcept
			{
				m_position += axis.m_upward * distance;
			}

			void
			translateAlongCustomZAxis (data_t distance, const Coordinates & axis) noexcept
			{
				m_position += axis.m_forward * distance;
			}

			/** Rotate the coordinates around an arbitrary axis.
			 * @param radian The angle expressed in radian. You can use the utility function Math::radians(degree).
			 * @param axis A Vector3 to defines the axis. */
			void
			rotate (data_t radian, const Vector< 3, data_t > & axis) noexcept
			{
				/* Make a Rotation Matrix. */
				auto matrix = Matrix< 3, data_t >::rotation(radian, axis);

				/* Rotate Y, and Z. */
				m_upward = (matrix * m_upward).normalize();
				m_forward = (matrix * m_forward).normalize();
			}

			/**
			 * Rotate on local X axis.
			 *
			 * @note You can use the Math::Radian(degree).
			 * @param radian The angle expressed in radian.
			 */
			void
			pitch (data_t radian) noexcept
			{
				this->rotate(radian, this->XVector());
			}

			/**
			 * Rotate on local Y axis.
			 *
			 * @note You can use the Math::Radian(degree).
			 * @param radian The angle expressed in radian.
			 */
			void
			yaw (data_t radian) noexcept
			{
				this->rotate(radian, m_upward);
			}

			/**
			 * @brief Rotates on local Z axis.
			 * @note You can use the Math::Radian(degree).
			 * @param radian The angle expressed in radian.
			 */
			void
			roll (data_t radian) noexcept
			{
				this->rotate(radian, m_forward);
			}

			/**
			 * @brief Gets the 4x4 model matrix.
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, data_t >
			modelMatrix () const noexcept
			{
				/* Sets rotations and position then multiply by scale vector :
				 * [Xx][Ux][Fx][Px]
				 * [Xy][Uy][Fy][Py]
				 * [Xz][Uz][Fz][Pz]
				 * [ 0][ 0][ 0][ 1]
				 */

				Matrix< 4, data_t > matrix;

				const auto xVector = this->XVector();

				#pragma omp simd
				for ( size_t index = 0; index < 3UL; index++ )
				{
					/* Rotation per row */
					matrix[0+index] = xVector[index];
					matrix[4+index] = m_upward[index];
					matrix[8+index] = m_forward[index];

					/* Position per column */
					matrix[12+index] = m_position[index];
				}

				if ( !m_scaleVector.isOne() )
				{
					matrix *= Matrix<4, data_t>::scaling(m_scaleVector);
				}

				return matrix;
			}

			/**
			 * @brief Gets the inverse 4x4 model matrix.
			 * @note This method don't use the generic inverse() method.
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, data_t >
			invertedModelMatrix () const noexcept
			{
				/* Rotations (transposed, row instead column) and negated position :
				 * [Xx][Xy][Xz][Px]
				 * [Ux][Uy][Uz][Py]
				 * [Fx][Fy][Fz][Pz]
				 * [ 0][ 0][ 0][ 1]
				 */

				Matrix< 4, data_t > matrix;

				const auto xVector = this->XVector();

				const Vector< 3, data_t > positionVector{
					-Vector< 3, data_t >::dotProduct(xVector, m_position) / m_scaleVector[X],
					-Vector< 3, data_t >::dotProduct(m_upward, m_position) / m_scaleVector[Y],
					-Vector< 3, data_t >::dotProduct(m_forward, m_position) / m_scaleVector[Z]
				};

				#pragma omp simd
				for ( size_t index = 0; index < 3UL; index++ )
				{
					const auto shift = index * 4;

					/* Rotation per row */
					matrix[shift] = xVector[index] / m_scaleVector[X];
					matrix[shift+1] = m_upward[index] / m_scaleVector[Y];
					matrix[shift+2] = m_forward[index] / m_scaleVector[Z];

					/* Position per column */
					matrix[12+index] = positionVector[index];
				}

				return matrix;
			}

			/**
			 * Gets an initial camera 4x4 matrix.
			 *
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, data_t >
			viewMatrix (bool rotationOnly = false) const noexcept
			{
				/* Rotations (transposed, row instead column) and negated position :
				 * [Xx][Xy][Xz][Px]
				 * [Ux][Uy][Uz][Py]
				 * [Fx][Fy][Fz][Pz]
				 * [ 0][ 0][ 0][ 1]
				 */

				Matrix< 4, data_t > matrix;

				const auto xVector = this->XVector();

				const Vector< 3, data_t > positionVector{
					rotationOnly ? 0 : -Vector< 3, data_t >::dotProduct(xVector, m_position),
					rotationOnly ? 0 : -Vector< 3, data_t >::dotProduct(m_upward, m_position),
					rotationOnly ? 0 : -Vector< 3, data_t >::dotProduct(m_forward, m_position)
				};

				#pragma omp simd
				for ( size_t index = 0; index < 3UL; index++ )
				{
					const auto shift = index * 4;

					/* Rotation per row */
					matrix[shift] = xVector[index];
					matrix[shift+1] = m_upward[index];
					matrix[shift+2] = m_forward[index];

					/* Position per column */
					matrix[12+index] = positionVector[index];
				}

				return matrix;
			}

			void
			clear () noexcept
			{
				m_position = {0, 0, 0};
				m_upward = Vector< 3, data_t >::positiveY(); /* Y direction */
				m_forward = Vector< 3, data_t >::positiveZ(); /* Z direction */
				m_scaleVector = {1, 1, 1};
			}

			void
			clearRotation () noexcept
			{
				m_upward = Vector< 3, data_t >::positiveY();
				m_forward = Vector< 3, data_t >::positiveZ();
			}

			/**
			 * STL streams printable object.
			 *
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Coordinates & obj) noexcept
			{
				return out << "Coordinates data :\n"
					"Position : " << obj.m_position << "\n"
					"Side vector (X+) : " << obj.XVector() << "\n"
					"Upward vector (Y+) : " << obj.m_upward << "\n"
					"Forward vector (Z+) : " << obj.m_forward << '\n';
			}

			/**
			 * Stringify the object.
			 *
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend
			std::string
			to_string (const Coordinates & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			/* NOTE: X vector is not here because it's extracted by
			 * a cross product from upward and forward vectors. */
			Vector< 3, data_t > m_position{};
			Vector< 3, data_t > m_upward = Vector< 3, data_t >::positiveY(); /* Y direction */
			Vector< 3, data_t > m_forward = Vector< 3, data_t >::positiveZ(); /* Z direction */
			Vector< 3, data_t > m_scaleVector{1, 1, 1};
	};
	// NOLINTEND(*-magic-numbers)
}
