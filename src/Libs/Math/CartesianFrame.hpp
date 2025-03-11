/*
 * src/Libs/Math/CartesianFrame.hpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#pragma once

/* STL inclusions. */
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>
#include <type_traits>

/* Local inclusions for usages. */
#include "Base.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"

namespace EmEn::Libs::Math
{
	/**
	 * @brief The transform space enumeration.
	 */
	enum class TransformSpace : uint8_t
	{
		Local,
		Parent,
		World
	};

	/**
	 * @brief Defines a frame in Euclidean space to easily manipulate the position and rotation of an object in a 3D scene.
	 * @note This class defines methods to build model and view matrices. The convention (Vulkan friendly at best) is :
	 *  - X axis : positive right, negative left
	 *  - Y axis : positive down, negative up
	 *  - Z axis : positive back, negative front
	 * @tparam precision_t The data precision, should be a floating point number. Default float.
	 */
	template< typename precision_t = float > requires (std::is_arithmetic_v< precision_t >)
	class CartesianFrame final
	{
		public:

			/**
			 * @brief Constructs a default cartesian frame.
			 */
			constexpr
			CartesianFrame () noexcept = default;

			/**
			 * @brief Constructs a cartesian frame from a position.
			 * @param position A reference to a vector for position.
			 */
			explicit
			constexpr
			CartesianFrame (const Vector< 3, precision_t > & position) noexcept
				: m_position(position)
			{

			}

			/**
			 * @brief Constructs a cartesian frame from a position and a uniform scaling factor.
			 * @param position A reference to a vector for position.
			 * @param scalingFactor A uniform scaling factor.
			 */
			constexpr
			CartesianFrame (const Vector< 3, precision_t > & position, precision_t scalingFactor) noexcept
				: m_position(position),
				  m_scaling(scalingFactor, scalingFactor, scalingFactor)
			{

			}

			/**
			 * @brief Constructs a cartesian frame from a position.
			 * @param xValue The X value.
			 * @param yValue The Y value.
			 * @param zValue The Z value.
			 */
			constexpr
			CartesianFrame (float xValue, float yValue, float zValue) noexcept
				: m_position(xValue, yValue, zValue)
			{

			}

			/**
			 * @brief Constructs a cartesian frame from a model matrix.
			 * @param matrix A reference to a matrix.
			 * @param scale A reference to a vector. Default, no scale.
			 */
			explicit
			constexpr
			CartesianFrame (const Matrix< 4, precision_t > & matrix, const Vector< 3, precision_t > & scale = {1, 1, 1}) noexcept
				: m_position(matrix[M4x4Col3Row0], matrix[M4x4Col3Row1], matrix[M4x4Col3Row2]),
				  m_downward(matrix[M4x4Col1Row0], matrix[M4x4Col1Row1], matrix[M4x4Col1Row2]),
				  m_backward(matrix[M4x4Col2Row0], matrix[M4x4Col2Row1], matrix[M4x4Col2Row2]),
				  m_scaling(scale)
			{
				m_downward.normalize();
				m_backward.normalize();
			}

			/**
			 * @brief Construct a cartesian frame from a position and a backward vector.
			 * @note This version will compute downward vector from position and backward vector.
			 * @param position A reference to a vector.
			 * @param backward A reference to a vector.
			 */
			CartesianFrame (const Vector< 3, precision_t > & position, const Vector< 3, precision_t > & backward) noexcept
				: m_position(position)
			{
				this->setBackwardVector(backward);
			}

			/**
			 * @brief Construct a cartesian frame from raw vectors.
			 * @param position A vector the position.
			 * @param downward A reference to a vector.
			 * @param backward A reference to a vector.
			 * @param scale A reference to a vector. Default, no scale.
			 */
			constexpr
			CartesianFrame (const Vector< 3, precision_t > & position, const Vector< 3, precision_t > & downward, const Vector< 3, precision_t > & backward, const Vector< 3, precision_t > & scale = {1, 1, 1}) noexcept
				: m_position(position),
				  m_downward(downward),
				  m_backward(backward),
				  m_scaling(scale)
			{

			}

			/*[[nodiscard]]
			CartesianFrame
			operator+ (const CartesianFrame & operand) const noexcept
			{
				CartesianFrame frame;

				return frame;
			}*/

			/*CartesianFrame &
			operator+= (const CartesianFrame & operand) noexcept
			{
				if ( this != &operand )
				{

				}

				return *this;
			}*/

			/**
			 * @brief Sets the world position.
			 * @param position A reference to a vector.
			 * @return void
			 */
			void
			setPosition (const Vector< 3, precision_t > & position) noexcept
			{
				m_position = position;
			}

			/**
			 * @brief Sets the world position.
			 * @param xValue The X position.
			 * @param yValue The Y position.
			 * @param zValue The Z position
			 * @return void
			 */
			void
			setPosition (precision_t xValue, precision_t yValue, precision_t zValue) noexcept
			{
				m_position[X] = xValue;
				m_position[Y] = yValue;
				m_position[Z] = zValue;
			}

			/**
			 * @brief Set the world X position.
			 * @param position The value on X Axis.
			 * @return void
			 */
			void
			setXPosition (precision_t position) noexcept
			{
				m_position[X] = position;
			}

			/**
			 * @brief Set the world Y position.
			 * @param position The value on Y Axis.
			 * @return void
			 */
			void
			setYPosition (precision_t position) noexcept
			{
				m_position[Y] = position;
			}

			/**
			 * @brief Set the world Z position.
			 * @param position The value on Z Axis.
			 * @return void
			 */
			void
			setZPosition (precision_t position) noexcept
			{
				m_position[Z] = position;
			}

			/**
			 * @brief Sets the backward vector (Z+).
			 * @note This will re-orient automatically the frame.
			 * @param forward The vector that hold the desired direction of the frame.
			 * @return void
			 */
			void
			setBackwardVector (const Vector< 3, precision_t > & forward) noexcept
			{
				m_backward = forward.normalized();

				/* NOTE: Recompute the downward vector from the new backward axis. */
				m_downward = CartesianFrame::computeYAxis(m_backward);
			}

			/**
			 * @brief Sets the backward vector (Z+).
			 * @param xValue The X value.
			 * @param yValue The Y value.
			 * @param zValue The Z value.
			 * @return void
			 */
			void
			setBackwardVector (precision_t xValue, precision_t yValue, precision_t zValue) noexcept
			{
				this->setBackwardVector(xValue, yValue, zValue);
			}

			/**
			 * @brief Sets the downward vector (Y+) and the backward vector (Z+).
			 * @warning You must pass coherent vectors.
			 * @param backward A reference to vector.
			 * @param downward A reference to vector.
			 * @return void
			 */
			void
			setOrientationVectors (const Vector< 3, precision_t > & backward, const Vector< 3, precision_t > & downward) noexcept
			{
				m_downward = downward.normalized();
				m_backward = backward.normalized();
			}

			/**
			 * @brief Sets the downward vector (Y+) and the backward vector (Z+) using another cartesian frame.
			 * @param frame A reference to a cartesian frame.
			 * @return void
			 */
			void
			setOrientationVectors (const CartesianFrame< precision_t > & frame) noexcept
			{
				m_downward = frame.m_downward;
				m_backward = frame.m_backward;
			}

			/**
			 * @brief Sets the scaling factor from a vector.
			 * @tparam vec_dim_t The vector dimension.
			 * @param factor A reference to a vector.
			 * @return void
			 */
			template< size_t vec_dim_t >
			void
			setScalingFactor (const Vector< vec_dim_t, precision_t > & factor) noexcept requires (vec_dim_t == 3 || vec_dim_t == 4)
			{
				m_scaling = factor;
			}

			/**
			 * @brief Sets the scaling factor from values.
			 * @param xFactor The X axis factor value.
			 * @param yFactor The Y axis factor value.
			 * @param zFactor The Z axis factor value.
			 * @return void
			 */
			void
			setScalingFactor (precision_t xFactor, precision_t yFactor, precision_t zFactor) noexcept
			{
				m_scaling[X] = xFactor;
				m_scaling[Y] = yFactor;
				m_scaling[Z] = zFactor;
			}

			/**
			 * @brief Sets a uniform scaling factor.
			 * @param factor The uniform factor value.
			 * @return void
			 */
			void
			setScalingFactor (precision_t factor) noexcept
			{
				m_scaling[X] = factor;
				m_scaling[Y] = factor;
				m_scaling[Z] = factor;
			}

			/**
			 * @brief Sets an X axis scaling factor.
			 * @param factor The factor value.
			 * @return void
			 */
			void
			setScalingXFactor (precision_t factor) noexcept
			{
				m_scaling[X] = factor;
			}

			/**
			 * @brief Sets an Y axis scaling factor.
			 * @param factor The factor value.
			 * @return void
			 */
			void
			setScalingYFactor (precision_t factor) noexcept
			{
				m_scaling[Y] = factor;
			}

			/**
			 * @brief Sets an Z axis scaling factor.
			 * @param factor The factor value.
			 * @return void
			 */
			void
			setScalingZFactor (precision_t factor) noexcept
			{
				m_scaling[Z] = factor;
			}

			/**
			 * @brief Returns the frame position in world/parent coordinates.
			 * @return const Vector< 3, precision_t > &
			 */
			[[nodiscard]]
			const Vector< 3, precision_t > &
			position () const noexcept
			{
				return m_position;
			}

			/**
			 * @brief Gives access to the position vector.
			 * @return Vector< 3, precision_t > &
			 */
			[[nodiscard]]
			Vector< 3, precision_t > &
			position () noexcept
			{
				return m_position;
			}

			/**
			 * @brief Returns the frame right (X+) direction vector.
			 * @note The return is a value. An initial frame should give [1, 0, 0] vector.
			 * @warning the return is a value.
			 * @return Vector< 3, precision_t >
			 */
			[[nodiscard]]
			Vector< 3, precision_t >
			rightVector () const noexcept
			{
				return Vector< 3, precision_t >::crossProduct(m_downward, m_backward).normalize();
			}

			/**
			 * @brief Returns the frame left (X-) direction vector.
			 * @note An initial frame should give [-1, 0, 0] vector.
			 * @warning the return is a value.
			 * @return Vector< 3, precision_t >
			 */
			[[nodiscard]]
			Vector< 3, precision_t >
			leftVector () const noexcept
			{
				return Vector< 3, precision_t >::crossProduct(m_backward.inversed(), m_downward.inversed()).normalize();
			}

			/**
			 * @brief Returns the frame downward vector (Y+).
			 * @note An initial frame should give [0, 1, 0] vector.
			 * @return const Vector< 3, precision_t > &
			 */
			[[nodiscard]]
			const Vector< 3, precision_t > &
			downwardVector () const noexcept
			{
				return m_downward;
			}

			/**
			 * @brief Returns the frame upward vector (Y-).
			 * @note An initial frame should give [0, -1, 0] vector.
			 * @warning the return is a value.
			 * @return Vector< 3, precision_t >
			 */
			[[nodiscard]]
			Vector< 3, precision_t >
			upwardVector () const noexcept
			{
				return m_downward.inversed();
			}

			/**
			 * @brief Returns the frame backward vector (Z+).
			 * @note An initial frame should give [0, 0, 1] vector.
			 * @return const Vector< 3, precision_t > &
			 */
			[[nodiscard]]
			const Vector< 3, precision_t > &
			backwardVector () const noexcept
			{
				return m_backward;
			}

			/**
			 * @brief Returns the frame forward vector (Z-).
			 * @note An initial frame should give [0, 0, -1] vector.
			 * @warning the return is a value.
			 * @return Vector< 3, precision_t >
			 */
			[[nodiscard]]
			Vector< 3, precision_t >
			forwardVector () const noexcept
			{
				return m_backward.inversed();
			}

			/**
			 * @brief Returns the frame X axis vector.
			 * @note This is the same as CartesianFrame::rightVector().
			 * @warning the return is a value.
			 * @return Vector< 3, precision_t >
			 */
			[[nodiscard]]
			Vector< 3, precision_t >
			XAxis () const noexcept
			{
				return this->rightVector();
			}

			/**
			 * @brief Returns the frame Y axis vector.
			 * @note This is the same as CartesianFrame::downwardVector().
			 * @return const Vector< 3, precision_t > &
			 */
			[[nodiscard]]
			const Vector< 3, precision_t > &
			YAxis () const noexcept
			{
				return m_downward;
			}

			/**
			 * @brief Returns the frame Z axis vector.
			 * @note This is the same as CartesianFrame::backwardVector().
			 * @return const Vector< 3, precision_t > &
			 */
			[[nodiscard]]
			const Vector< 3, precision_t > &
			ZAxis () const noexcept
			{
				return m_backward;
			}

			/**
			 * @brief Returns the frame scaling vector.
			 * @return const Vector< 3, precision_t > &
			 */
			[[nodiscard]]
			const Vector< 3, precision_t > &
			scalingFactor () const noexcept
			{
				return m_scaling;
			}

			/**
			 * @brief Returns the pitch (X) angle of the frame in radian.
			 * @note Floating point number version.
			 * @return precision_t
			 */
			[[nodiscard]]
			precision_t
			getPitchAngle () const noexcept requires (std::is_floating_point_v< precision_t >)
			{
				return Vector< 3, precision_t >::angle(m_backward, Vector< 3, precision_t >::negativeZ());
			}

			/**
			 * @brief Returns the pitch (X) angle of the frame in radian.
			 * @note Integer number version.
			 * @return float
			 */
			[[nodiscard]]
			float
			getPitchAngle () const noexcept requires (std::is_integral_v< precision_t >)
			{
				return 0;
			}

			/**
			 * @brief Returns the yaw (Y) angle of the frame in radian.
			 * @note Floating point number version.
			 * @return precision_t
			 */
			[[nodiscard]]
			precision_t
			getYawAngle () const noexcept requires (std::is_floating_point_v< precision_t >)
			{
				return Vector< 3, precision_t >::angle(m_backward, Vector< 3, precision_t >::positiveX());
			}

			/**
			 * @brief Returns the yaw (Y) angle of the frame in radian.
			 * @note Integer number version.
			 * @return float
			 */
			[[nodiscard]]
			float
			getYawAngle () const noexcept requires (std::is_integral_v< precision_t >)
			{
				return 0;
			}

			/**
			 * @brief Returns the roll (Z) angle of the frame in radian.
			 * @note Floating point number version.
			 * @return precision_t
			 */
			[[nodiscard]]
			precision_t
			getRollAngle () const noexcept requires (std::is_floating_point_v< precision_t >)
			{
				return Vector< 3, precision_t >::angle(m_backward, Vector< 3, precision_t >::positiveY());
			}

			/**
			 * @brief Returns the roll (Z) angle of the frame in radian.
			 * @note Integer number version.
			 * @return float
			 */
			[[nodiscard]]
			float
			getRollAngle () const noexcept requires (std::is_integral_v< precision_t >)
			{
				return 0;
			}

			/**
			 * @brief Normalizes the frame axes.
			 * @return void
			 */
			void
			normalize () noexcept
			{
				m_downward.normalize();
				m_backward.normalize();
			}

			/**
			 * @brief Points the backward (Z- axis) toward the target.
			 * @note Use this for pointing a camera.
			 * @param target A position to look at.
			 * @param flipAxis Flip the Z axis to point forward instead.
			 * @return void
			 */
			void
			lookAt (const Vector< 3, precision_t > & target, bool flipAxis) noexcept
			{
				if ( flipAxis )
				{
					/* Z+ will point toward the target. */
					this->setBackwardVector(target - m_position);
				}
				else
				{
					/* Z- will point toward the target. */
					this->setBackwardVector(m_position - target);
				}
			}

			/**
			 * @brief Points the backward (Z- axis) toward the target.
			 * @note Same as CartesianFrame::lookAt() but using a matrix.
			 * @param target A position to look at.
			 * @return void
			 */
			void
			lookAtUsingMatrix (const Vector< 3, precision_t > & target) noexcept
			{
				const auto matrix = Matrix< 4, precision_t >::lookAt(m_position, target, m_downward);

				m_backward = (matrix * Vector< 4, precision_t >(m_backward, 0)).toVector3();
				m_downward = (matrix * Vector< 4, precision_t >(m_downward, 0)).toVector3();
			}

			/**
			 * @brief Translates the frame into a new position.
			 * @param distance A reference to a vector.
			 * @param local Using local axis.
			 * @return void
			 */
			void
			translate (const Vector< 3, precision_t > & distance, bool local) noexcept
			{
				if ( local )
				{
					m_position += this->getRotationMatrix3() * distance;
				}
				else
				{
					m_position += distance;
				}
			}

			/**
			 * @brief Translates the frame into a new position.
			 * @param xDistance The X value.
			 * @param yDistance The Y value.
			 * @param zDistance The Z value.
			 * @param local Using local axis.
			 * @return void
			 */
			void
			translate (precision_t xDistance, precision_t yDistance, precision_t zDistance, bool local) noexcept
			{
				if ( local )
				{
					m_position += this->getRotationMatrix3() * Vector < 3, precision_t > {xDistance, yDistance, zDistance};
				}
				else
				{
					m_position[X] += xDistance;
					m_position[Y] += yDistance;
					m_position[Z] += zDistance;
				}
			}

			/**
			 * @brief Translates the frame into a new X position.
			 * @param distance The X value.
			 * @param local Using local axis.
			 * @return void
			 */
			void
			translateX (precision_t distance, bool local) noexcept
			{
				if ( local )
				{
					m_position += this->rightVector() * distance;
				}
				else
				{
					m_position[X] += distance;
				}
			}

			/**
			 * @brief Translates the frame into a new Y position.
			 * @param distance The Y value.
			 * @param local Using local axis.
			 * @return void
			 */
			void
			translateY (precision_t distance, bool local) noexcept
			{
				if ( local )
				{
					m_position += m_downward * distance;
				}
				else
				{
					m_position[Y] += distance;
				}
			}

			/**
			 * @brief Translates the frame into a new Z position.
			 * @param distance The Z value.
			 * @param local Using local axis.
			 * @return void
			 */
			void
			translateZ (precision_t distance, bool local) noexcept
			{
				if ( local )
				{
					m_position += m_backward * distance;
				}
				else
				{
					m_position[Z] += distance;
				}
			}

			/**
			 * @brief Translates the frame into a new position using axis from another frame.
			 * @param distance A reference to a vector.
			 * @param frame A reference to a cartesian frame.
			 * @return void
			 */
			void
			translate (const Vector< 3, precision_t > & distance, const CartesianFrame & frame) noexcept
			{
				m_position += frame.getRotationMatrix3() * distance;
			}

			/**
			 * @brief Translates the frame into a new position using axis from another frame.
			 * @param xDistance The X value.
			 * @param yDistance The Y value.
			 * @param zDistance The Z value.
			 * @param frame A reference to a cartesian frame.
			 * @return void
			 */
			void
			translate (precision_t xDistance, precision_t yDistance, precision_t zDistance, const CartesianFrame & frame) noexcept
			{
				this->translate({xDistance, yDistance, zDistance}, frame);
			}

			/**
			 * @brief Translates the frame into a new X position using axis from another frame.
			 * @param distance The X value.
			 * @param frame A reference to a cartesian frame.
			 * @return void
			 */
			void
			translateX (precision_t distance, const CartesianFrame & frame) noexcept
			{
				m_position += frame.rightVector() * distance;
			}

			/**
			 * @brief Translates the frame into a new Y position using axis from another frame.
			 * @param distance The Y value.
			 * @param frame A reference to a cartesian frame.
			 * @return void
			 */
			void
			translateY (precision_t distance, const CartesianFrame & frame) noexcept
			{
				m_position += frame.downwardVector() * distance;
			}

			/**
			 * @brief Translates the frame into a new Z position using axis from another frame.
			 * @param distance The Z value.
			 * @param frame A reference to a cartesian frame.
			 * @return void
			 */
			void
			translateZ (precision_t distance, const CartesianFrame & frame) noexcept
			{
				m_position += frame.backwardVector() * distance;
			}

			/**
			 * @brief Rotates the frame around an arbitrary axis.
			 * @param radian The angle expressed in radian. You can use the utility function Math::radians(degree).
			 * @param axis A Vector3 to defines the axis.
			 * @param local Using local axis.
			 * @return void
			 */
			void
			rotate (precision_t radian, const Vector< 3, precision_t > & axis, bool local) noexcept requires (std::floating_point < precision_t>)
			{
				const auto matrix = Matrix< 3, precision_t >::rotation(radian, axis);

				m_downward = (matrix * m_downward).normalize();
				m_backward = (matrix * m_backward).normalize();

				if ( !local )
				{
					m_position = matrix * m_position;
				}
			}

			/**
			 * @brief Rotates on X axis.
			 * @note You can use the Math::Radian(degree).
			 * @param radian The angle expressed in radian.
			 * @param local Using local axis.
			 * @return void
			 */
			void
			pitch (precision_t radian, bool local) noexcept requires (std::floating_point < precision_t>)
			{
				this->rotate(radian, this->rightVector(), local);
			}

			/**
			 * @brief Rotate on Y axis (downward).
			 * @note You can use the Math::Radian(degree).
			 * @param radian The angle expressed in radian.
			 * @param local Using local axis.
			 * @return void
			 */
			void
			yaw (precision_t radian, bool local) noexcept requires (std::floating_point < precision_t>)
			{
				this->rotate(radian, m_downward, local);
			}

			/**
			 * @brief Rotates on Z axis.
			 * @note You can use the Math::Radian(degree).
			 * @param radian The angle expressed in radian.
			 * @param local Using local axis.
			 * @return void
			 */
			void
			roll (precision_t radian, bool local) noexcept requires (std::floating_point < precision_t>)
			{
				this->rotate(radian, m_backward, local);
			}

			/**
			 * @brief Rotates the frame around an arbitrary axis.
			 * @FIXME Incorrect !
			 * @param radian The angle expressed in radian. You can use the utility function Math::radians(degree).
			 * @param axis A Vector3 to defines the axis.
			 * @param frame A reference to a cartesian frame.
			 * @return void
			 */
			void
			rotate (precision_t radian, const Vector< 3, precision_t > & axis, const CartesianFrame & /*frame*/) noexcept requires (std::floating_point < precision_t>)
			{
				const auto matrix = Matrix< 3, precision_t >::rotation(radian, axis);

				m_downward = (matrix * m_downward).normalize();
				m_backward = (matrix * m_backward).normalize();
			}

			/**
			 * @brief Rotates on X axis using another frame.
			 * @note You can use the Math::Radian(degree).
			 * @param radian The angle expressed in radian.
			 * @param frame A reference to a cartesian frame.
			 * @return void
			 */
			void
			pitch (precision_t radian, const CartesianFrame & frame) noexcept requires (std::floating_point < precision_t>)
			{
				this->rotate(radian, this->rightVector(), frame);
			}

			/**
			 * @brief Rotates on Y axis using another frame.
			 * @note You can use the Math::Radian(degree).
			 * @param radian The angle expressed in radian.
			 * @param frame A reference to a cartesian frame.
			 * @return void
			 */
			void
			yaw (precision_t radian, const CartesianFrame & frame) noexcept requires (std::floating_point < precision_t>)
			{
				this->rotate(radian, m_downward, frame);
			}

			/**
			 * @brief Rotates on Z axis using another frame.
			 * @note You can use the Math::Radian(degree).
			 * @param radian The angle expressed in radian.
			 * @param frame A reference to a cartesian frame.
			 * @return void
			 */
			void
			roll (precision_t radian, const CartesianFrame & frame) noexcept requires (std::floating_point < precision_t>)
			{
				this->rotate(radian, m_backward, frame);
			}

			/**
			 * @brief Returns the translation 4x4 matrix.
			 * @note Matrix layout :
			 *   [ 1][ 0][ 0][Px]
			 *   [ 0][ 1][ 0][Py]
			 *   [ 0][ 0][ 1][Pz]
			 *   [ 0][ 0][ 0][ 1]
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, precision_t >
			getTranslationMatrix4 () const noexcept
			{
				return Matrix< 4, precision_t >::translation(m_position);
			}

			/**
			 * @brief Returns the rotation 3x3 matrix.
			 * @note Matrix layout :
			 *   [Xx][Ux][Fx]
			 *   [Xy][Uy][Fy]
			 *   [Xz][Uz][Fz]
			 * @return Matrix< 3, type_t >
			 */
			[[nodiscard]]
			Matrix< 3, precision_t >
			getRotationMatrix3 () const noexcept
			{
				return {this->rightVector(), m_downward, m_backward};
			}

			/**
			 * @brief Returns the rotation 4x4 matrix.
			 * @note Matrix layout :
			 *   [Xx][Ux][Fx][ 0]
			 *   [Xy][Uy][Fy][ 0]
			 *   [Xz][Uz][Fz][ 0]
			 *   [ 0][ 0][ 0][ 1]
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, precision_t >
			getRotationMatrix4 () const noexcept
			{
				return {this->rightVector(), m_downward, m_backward};
			}

			/**
			 * @brief Returns the scaling 3x3 matrix.
			 * @note Matrix layout :
			 *   [Sx][ 0][ 0]
			 *   [ 0][Sy][ 0]
			 *   [ 0][ 0][Sz]
			 * @return Matrix< 3, type_t >
			 */
			[[nodiscard]]
			Matrix< 3, precision_t >
			getScalingMatrix3 () const noexcept
			{
				return Matrix< 3, precision_t >::scaling(m_scaling);
			}

			/**
			 * @brief Returns the scaling 4x4 matrix.
			 * @note Matrix layout :
			 *   [Sx][ 0][ 0][ 0]
			 *   [ 0][Sy][ 0][ 0]
			 *   [ 0][ 0][Sz][ 0]
			 *   [ 0][ 0][ 0][ 1]
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, precision_t >
			getScalingMatrix4 () const noexcept
			{
				return Matrix< 4, precision_t >::scaling(m_scaling);
			}

			/**
			 * @brief Returns the model matrix to place an object in a 3D scene.
			 * @note This the combination of rotation, translation and scaling matrices.
			 * Matrix layout :
			 *   [Xx][Ux][Fx][Px] Xx with scalingX
			 *   [Xy][Uy][Fy][Py] Uy with scalingY
			 *   [Xz][Uz][Fz][Pz] Fz with scalingZ
			 *   [ 0][ 0][ 0][ 1]
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, precision_t >
			getModelMatrix () const noexcept
			{
				/* NOTE: This is the full mathematical way. */
				/*return
					Matrix< 4, precision_t >::translation(m_position) *
					Matrix< 4, precision_t >::rotation(this->rightVector(), m_downward, m_backward) *
					Matrix< 4, precision_t >::scaling(m_scaling);*/

				/* NOTE: Init directly the model matrix with translation and rotation vectors and check if scaling is requested. */
				Matrix< 4, precision_t > modelMatrix{this->rightVector(), m_downward, m_backward, m_position};

				if ( !m_scaling.isAllComponentOne() )
				{
					modelMatrix *= Matrix< 4, precision_t >::scaling(m_scaling);
				}

				return modelMatrix;
			}

			/**
			 * @brief Returns the model matrix to place a billboard in a 3D scene.
			 * @note This is a variant of Cartesian::getModelMatrix() for sprite facing camera.
			 * Matrix layout :
			 *   [Xx][Ux][Fx][Px] Xx with scalingX
			 *   [Xy][Uy][Fy][Py] Uy with scalingY
			 *   [Xz][Uz][Fz][Pz] Fz with scalingZ
			 *   [ 0][ 0][ 0][ 1]
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, precision_t >
			getSpriteModelMatrix (const Vector< 3, float > & cameraPosition) const noexcept
			{
				/* Prepare re-oriented vectors toward the camera. */
				const auto backward = (cameraPosition - m_position).normalize();
				const auto downward = CartesianFrame::computeYAxis(backward);
				const auto right = Vector< 3, precision_t >::crossProduct(downward, backward);

				Matrix< 4, precision_t > modelMatrix{right, downward, backward, m_position};

				/* Scale if needed. */
				if ( !m_scaling.isAllComponentOne() )
				{
					modelMatrix *= Matrix< 4, precision_t >::scaling(m_scaling);
				}

				return modelMatrix;
			}

			/**
			 * @brief Returns the inverted model matrix to place an object in a 3D scene.
			 * @todo Check this method !
			 * @note This method don't use the generic inverse() method.
			 * Matrix Layout :
			 *   [Xx][Xy][Xz][Px]
			 *   [Ux][Uy][Uz][Py]
			 *   [Fx][Fy][Fz][Pz]
			 *   [ 0][ 0][ 0][ 1]
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, precision_t >
			getInvertedModelMatrix () const noexcept
			{
				/*Matrix< 4, precision_t > modelMatrix;

				const auto right = this->rightVector();

				const Vector< 3, precision_t > position{
					-Vector< 3, precision_t >::dotProduct(right, m_position) / m_scaling[X],
					-Vector< 3, precision_t >::dotProduct(m_downward, m_position) / m_scaling[Y],
					-Vector< 3, precision_t >::dotProduct(m_backward, m_position) / m_scaling[Z]
				};

				#pragma omp simd
				for ( size_t index = 0; index < 3UL; index++ )
				{
					const auto shift = index * 4;

					modelMatrix[shift] = right[index] / m_scaling[X];
					modelMatrix[shift + 1] = m_downward[index] / m_scaling[Y];
					modelMatrix[shift + 2] = m_backward[index] / m_scaling[Z];

					modelMatrix[12 + index] = position[index];
				}

				return modelMatrix;*/

				if ( !m_scaling.isAllComponentOne() )
				{
					const auto right = this->rightVector();

					const auto positionX = -Vector< 3, precision_t >::dotProduct(right, m_position) / m_scaling[X];
					const auto positionY = -Vector< 3, precision_t >::dotProduct(m_downward, m_position) / m_scaling[X];
					const auto positionZ = -Vector< 3, precision_t >::dotProduct(m_backward, m_position) / m_scaling[X];

					std::array< precision_t, 16 > rawData{
						right[X] / m_scaling[X], m_downward[X] / m_scaling[Y], m_backward[X] / m_scaling[Z], 0,
						right[Y] / m_scaling[X], m_downward[Y] / m_scaling[Y], m_backward[Y] / m_scaling[Z], 0,
						right[Z] / m_scaling[X], m_downward[Z] / m_scaling[Y], m_backward[Z] / m_scaling[Z], 0,
						positionX, positionY, positionZ, 1
					};

					return Matrix< 4, precision_t >{rawData};
				}

				return this->getViewMatrix();
			}

			/**
			 * @brief Returns a view matrix to use as a camera point of view.
			 * @note This the combination of rotation (transposed, row instead column) and negated translation matrices.
			 * Matrix layout :
			 *   [Xx][Xy][Xz][Px]
			 *   [Ux][Uy][Uz][Py]
			 *   [Fx][Fy][Fz][Pz]
			 *   [ 0][ 0][ 0][ 1]
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, precision_t >
			getViewMatrix () const noexcept
			{
				const auto right = this->rightVector();

				// TODO: Do benchmark to see the fastest approach.
				/*Matrix< 4, precision_t > matrix;
				matrix[0] = right[X];
				matrix[1] = m_downward[X];
				matrix[2] = m_backward[X];

				matrix[4] = right[Y];
				matrix[5] = m_downward[Y];
				matrix[6] = m_backward[Y];

				matrix[8] = right[Z];
				matrix[9] = m_downward[Z];
				matrix[10] = m_backward[Z];

				matrix[12] = -Vector< 3, precision_t >::dotProduct(right, m_position);
				matrix[13] = -Vector< 3, precision_t >::dotProduct(m_downward, m_position);
				matrix[14] = -Vector< 3, precision_t >::dotProduct(m_backward, m_position);

				return matrix;*/

				const auto positionX = -Vector< 3, precision_t >::dotProduct(right, m_position);
				const auto positionY = -Vector< 3, precision_t >::dotProduct(m_downward, m_position);
				const auto positionZ = -Vector< 3, precision_t >::dotProduct(m_backward, m_position);

				std::array< precision_t, 16 > rawData{
					right[X], m_downward[X], m_backward[X], 0,
					right[Y], m_downward[Y], m_backward[Y], 0,
					right[Z], m_downward[Z], m_backward[Z], 0,
					positionX, positionY, positionZ, 1
				};

				return Matrix< 4, precision_t >{rawData};
			}

			/**
			 * @brief Returns an infinity view matrix to use as a camera point of view.
			 * @note Same as CartesianFrame::getViewMatrix() without the translation.
			 * Matrix layout :
			 *   [Xx][Xy][Xz][ 0]
			 *   [Ux][Uy][Uz][ 0]
			 *   [Fx][Fy][Fz][ 0]
			 *   [ 0][ 0][ 0][ 1]
			 * @return Matrix< 4, type_t >
			 */
			[[nodiscard]]
			Matrix< 4, precision_t >
			getInfinityViewMatrix () const noexcept
			{
				const auto right = this->rightVector();

				// TODO: Do benchmark to see the fastest approach.
				/*Matrix< 4, precision_t > matrix;

				matrix[0] = right[X];
				matrix[1] = m_downward[X];
				matrix[2] = m_backward[X];

				matrix[4] = right[Y];
				matrix[5] = m_downward[Y];
				matrix[6] = m_backward[Y];

				matrix[8] = right[Z];
				matrix[9] = m_downward[Z];
				matrix[10] = m_backward[Z];

				return matrix;*/

				std::array< precision_t, 16 > rawData{
					right[X], m_downward[X], m_backward[X], 0,
					right[Y], m_downward[Y], m_backward[Y], 0,
					right[Z], m_downward[Z], m_backward[Z], 0,
					0, 0, 0, 1
				};

				return Matrix< 4, precision_t >{rawData};
			}

			/**
			 * @brief Resets all vectors.
			 * @return void
			 */
			void
			reset () noexcept
			{
				m_position = {0, 0, 0};
				this->resetRotation();
				m_scaling = {1, 1, 1};
			}

			/**
			 * @brief Resets the direction vectors.
			 * @return void
			 */
			void
			resetRotation () noexcept
			{
				m_downward = Vector< 3, precision_t >::positiveY();
				m_backward = Vector< 3, precision_t >::positiveZ();
			}

			/**
			 * @brief Performs a linear interpolation between two cartesian frames.
			 * @param operandA A reference to a cartesian frame.
			 * @param operandB A reference to a cartesian frame.
			 * @param factor The interpolation factor from 0.0 to 1.0.
			 * @return CartesianFrame
			 */
			static
			CartesianFrame
			linearInterpolation (const CartesianFrame & operandA, const CartesianFrame & operandB, precision_t factor) noexcept
			{
				return {
					Math::linearInterpolation(operandA.m_position, operandB.m_position, factor),
					Math::linearInterpolation(operandA.m_downward, operandB.m_downward, factor),
					Math::linearInterpolation(operandA.m_backward, operandB.m_backward, factor),
					Math::linearInterpolation(operandA.m_scaling, operandB.m_scaling, factor)
				};
			}

			/**
			 * @brief Performs a cosine interpolation between two cartesian frames.
			 * @param operandA A reference to a cartesian frame.
			 * @param operandB A reference to a cartesian frame.
			 * @param factor The interpolation factor from 0.0 to 1.0.
			 * @return CartesianFrame
			 */
			static
			CartesianFrame
			cosineInterpolation (const CartesianFrame & operandA, const CartesianFrame & operandB, precision_t factor) noexcept
			{
				return {
					Math::cosineInterpolation(operandA.m_position, operandB.m_position, factor),
					Math::cosineInterpolation(operandA.m_downward, operandB.m_downward, factor),
					Math::cosineInterpolation(operandA.m_backward, operandB.m_backward, factor),
					Math::cosineInterpolation(operandA.m_scaling, operandB.m_scaling, factor)
				};
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return std::ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const CartesianFrame & obj) noexcept
			{
				return out << "Cartesian frame data :\n"
					"Position : " << obj.m_position << "\n"
					"Right (X+) : " << obj.rightVector() << "\n"
					"Left (X-) : " << obj.leftVector() << "\n"
					"Downward (Y+) : " << obj.downwardVector() << "\n"
					"Upward (Y-) : " << obj.upwardVector() << "\n"
					"Backward (Z+) : " << obj.backwardVector() << "\n"
					"Forward (Z-) : " << obj.forwardVector() << '\n';
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return std::string
			 */
			friend
			std::string
			to_string (const CartesianFrame & obj) noexcept
			{
				std::stringstream output;

				output << obj;

				return output.str();
			}

		private:

			/**
			 * @brief Computes the downward (Y-Axis) vector from backward vector (Z-Axis).
			 * @param backward A reference to a vector.
			 * @return Vector< 3, precision_t >
			 */
			static
			Vector< 3, precision_t >
			computeYAxis (const Vector< 3, precision_t > & backward) noexcept
			{
				/* Special case when backward is equal to downward (0, 1, 0). */
				if ( backward == Vector< 3, precision_t >::positiveY() )
				{
					return Vector< 3, precision_t >::positiveZ();
				}

				/* Special case when backward is equal to upward (0, -1, 0). */
				if ( backward == Vector< 3, precision_t >::negativeY() )
				{
					return Vector< 3, precision_t >::negativeZ();
				}

				Vector< 3, precision_t > downward;

				/* Compute temporal downward vector based on the backward
				 * vector watch out when look up/down at 90 degree for
				 * example, backward vector is on the Y axis. */
				if ( std::abs(backward[X]) < 0.0F && std::abs(backward[Z]) < 0.0F )
				{
					/* If backward vector is pointing on +Y axis. */
					downward = backward[Y] > 0.0F ? Vector< 3, precision_t >::negativeZ() : Vector< 3, precision_t >::positiveZ();
				}
				else
				{
					/* In general, downward vector is straight down. */
					downward = Vector< 3, precision_t >::positiveY();
				}

				/* Re-calculate the orthonormal downward vector with right vector. */
				const auto right = Vector< 3, precision_t >::crossProduct(downward, backward).normalize();

				return Vector< 3, precision_t >::crossProduct(backward, right); // NOTE: normalize() here seems useless.
			}

			/* NOTE:
			 * The position and directions are expressed in parent axis (or world axis).
			 * X axe vector is not here because it's extracted by a cross product from downward and backward vectors.
			 * The scale vector is expressed in local axis.
			 */
			Vector< 3, precision_t > m_position;
			Vector< 3, precision_t > m_downward{Vector< 3, precision_t >::positiveY()};
			Vector< 3, precision_t > m_backward{Vector< 3, precision_t >::positiveZ()};
			Vector< 3, precision_t > m_scaling{1, 1, 1};
	};

	using CartesianFrameF = CartesianFrame< float >;
	using CartesianFrameD = CartesianFrame< double >;
	using CartesianFrameLD = CartesianFrame< long double >;
}
