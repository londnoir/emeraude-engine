/*
 * Libraries/Math/Quaternion.hpp
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
#include <array>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

/* Local inclusions */
#include "Vector.hpp"
#include "Matrix.hpp"

namespace Libraries::Math
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-pointer-arithmetic, readability-identifier-length, *-magic-numbers)

	/** Class defining a Quaternion. */
	template< typename data_t = float, std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false >
	class Quaternion final
	{
		public:

			/* Imaginary part */
			static constexpr auto X = 0UL;
			static constexpr auto Y = 1UL;
			static constexpr auto Z = 2UL;
			/* Real part */
			static constexpr auto W = 3UL;

			/** Default constructor. */
			Quaternion () noexcept = default;

			/** Construct from STL array. */
			explicit Quaternion (const std::array< data_t, 4 > & data) noexcept
				: m_data(data)
			{

			}

			/** Construct from C array.
			 * @warning  Unsafe ! */
			explicit Quaternion (const data_t * data) noexcept
				: m_data(data[0], data[1], data[2], data[3])
			{

			}

			/** Construct from raw values. */
			Quaternion (data_t x, data_t y, data_t z, data_t w) noexcept
				: m_data{x, y, z, w}
			{

			}

			/** Construct from euclidian angles. */
			Quaternion (data_t x, data_t y, data_t z) noexcept
			{
				this->setEulerAngles(x, y, z);
			}

			/** Construct from euclidian angles. */
			explicit Quaternion (const Vector< 3, data_t > & euler) noexcept
			{
				this->setEulerAngles(euler);
			}

			/** Construct from a vector3. */
			explicit Quaternion (const Vector< 3, data_t > & vector, data_t real) noexcept
				: m_data{vector[X], vector[Y], vector[Z], real}
			{

			}

			/** Construct from a vector4. */
			explicit Quaternion (const Vector< 4, data_t > & vector) noexcept
				: m_data{vector[Vector< 4, data_t >::X], vector[Vector< 4, data_t >::Y], vector[Vector< 4, data_t >::Z], vector[Vector< 4, data_t >::W]}
			{

			}

			explicit Quaternion (const Matrix< 4, data_t > & matrix) noexcept
			{
				(*this) = matrix;
			}

			Quaternion &
			operator= (const Matrix< 4, data_t > & matrix) noexcept
			{
				const auto diag = matrix[0] + matrix[5] + matrix[10] + 1;

				if ( diag > 0.0 )
				{
					/* Det scale from diagonal. */
					const auto scale = std::sqrt(diag) * 2.0;

					/* FIXME: speed this up. */
					m_data = {
						(matrix[6] - matrix[9]) / scale,
						(matrix[8] - matrix[2]) / scale,
						(matrix[1] - matrix[4]) / scale,
						0.25F * scale
					};
				}
				else
				{
					if ( matrix[0] > matrix[5] && matrix[0] > matrix[10] )
					{
						/* 1st element of diag is the greatest value find scale according to 1st element, and data_t it. */
						const auto scale = std::sqrt(1.0 + matrix[0] - matrix[5] - matrix[10]) * 2.0;

						/* FIXME: speed this up. */
						m_data = {
							0.25F * scale,
							(matrix[4] + matrix[1]) / scale,
							(matrix[2] + matrix[8]) / scale,
							(matrix[6] - matrix[9]) / scale
						};
					}
					else if ( matrix[5] > matrix[10] )
					{
						/* 2nd element of diag is the greatest value find scale according to 2nd element, and data_t it. */
						const auto scale = std::sqrt(1.0 + matrix[5] - matrix[0] - matrix[10]) * 2.0;

						/* FIXME: speed this up. */
						m_data = {
							(matrix[4] + matrix[1]) / scale,
							0.25F * scale,
							(matrix[9] + matrix[6]) / scale,
							(matrix[8] - matrix[2]) / scale
						};
					}
					else
					{
						/* 3rd element of diag is the greatest value find scale according to 3rd element, and data_t it. */
						const auto scale = std::sqrt(1.0 + matrix[10] - matrix[0] - matrix[5]) * 2.0;

						/* FIXME: speed this up. */
						m_data = {
							(matrix[8] + matrix[2]) / scale,
							(matrix[9] + matrix[6]) / scale,
							0.25F * scale,
							(matrix[1] - matrix[4]) / scale
						};
					}
				}

				this->normalize();

				return *this;
			}

			/** Equality operator. */
			bool
			operator== (const Quaternion & operand) const noexcept
			{
				if ( this != &operand )
				{
					if ( !Utility::equal(m_data[X], operand.m_data[X]) )
					{
						return false;
					}

					if ( !Utility::equal(m_data[Y], operand.m_data[Y]) )
					{
						return false;
					}

					if ( !Utility::equal(m_data[Z], operand.m_data[Z]) )
					{
						return false;
					}

					if ( !Utility::equal(m_data[W], operand.m_data[W]) )
					{
						return false;
					}
				}

				return true;
			}

			/** Inequality operator. */
			bool
			operator!= (const Quaternion & operand) const noexcept
			{
				return !this->operator==(operand);
			}

			/** Unary negation. */
			Quaternion
			operator- () const noexcept
			{
				return {
					-m_data[X],
					-m_data[Y],
					-m_data[Z],
					-m_data[W]
				};
			}

			Quaternion
			operator+ (const Quaternion & operand) const noexcept
			{
				return {
					m_data[X] + operand.m_data[X],
					m_data[Y] + operand.m_data[Y],
					m_data[Z] + operand.m_data[Z],
					m_data[W] + operand.m_data[W]
				};
			}

			Quaternion
			operator+= (const Quaternion & operand) const noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					m_data[X] += operand.m_data[X];
					m_data[Y] += operand.m_data[Y];
					m_data[Z] += operand.m_data[Z];
					m_data[W] += operand.m_data[W];
				}

				return *this;
			}

			Quaternion
			operator- (const Quaternion & operand) const noexcept
			{
				return {
					m_data[X] - operand.m_data[X],
					m_data[Y] - operand.m_data[Y],
					m_data[Z] - operand.m_data[Z],
					m_data[W] - operand.m_data[W]
				};
			}

			Quaternion
			operator-= (const Quaternion & operand) const noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					m_data[X] -= operand.m_data[X];
					m_data[Y] -= operand.m_data[Y];
					m_data[Z] -= operand.m_data[Z];
					m_data[W] -= operand.m_data[W];
				}

				return *this;
			}

			Quaternion
			operator* (const Quaternion & operand) const noexcept
			{
				return Quaternion::product(*this, operand);
			}

			Quaternion
			operator*= (const Quaternion & operand) const noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					*this = Quaternion::product(*this, operand);
				}

				return *this;
			}

			Quaternion
			operator/ (const Quaternion & operand) const noexcept
			{
				return {
					m_data[X] / operand.m_data[X],
					m_data[Y] / operand.m_data[Y],
					m_data[Z] / operand.m_data[Z],
					m_data[W] / operand.m_data[W]
				};
			}

			Quaternion
			operator/= (const Quaternion & operand) const noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					m_data[X] /= operand.m_data[X];
					m_data[Y] /= operand.m_data[Y];
					m_data[Z] /= operand.m_data[Z];
					m_data[W] /= operand.m_data[W];
				}

				return *this;
			}

			Quaternion
			operator* (data_t operand) const noexcept
			{
				return {
					m_data[X] * operand,
					m_data[Y] * operand,
					m_data[Z] * operand,
					m_data[W] * operand
				};
			}

			Quaternion &
			operator*= (data_t operand) const noexcept
			{
				m_data[X] *= operand;
				m_data[Y] *= operand;
				m_data[Z] *= operand;
				m_data[W] *= operand;

				return *this;
			}

			/**
			 * Multiplication operator with a vector.
			 *
			 * @note nVidia SDK implementation.
			 */
			Vector< 3, data_t >
			operator* (const Vector< 3, data_t > & operand) const noexcept
			{
				Vector< 3, data_t > qvec(m_data[X], m_data[Y], m_data[Z]);

				auto uv = Vector< 3, data_t >::cross(qvec, operand);
				auto uuv = Vector< 3, data_t >::cross(qvec, uv);

				uv *= 2.0 * m_data[W];
				uuv *= 2.0;

				return operand + uv + uuv;
			}

			/**
			 * Multiplication operator with a vector.
			 *
			 * @note nVidia SDK implementation.
			 */
			Vector< 4, data_t >
			operator* (const Vector< 4, data_t > & operand) const noexcept
			{
				Vector< 4, data_t > qvec(m_data[X], m_data[Y], m_data[Z]);

				auto uv = Vector< 4, data_t >::cross(qvec, operand);
				auto uuv = Vector< 4, data_t >::cross(qvec, uv);

				uv *= 2.0 * m_data[W];
				uuv *= 2.0;

				return operand + uv + uuv;
			}

			/** Quaternion scalar division operator. */
			Quaternion
			operator/ (data_t operand) const noexcept
			{
				if ( Utility::isZero(operand) )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", division by zero !" << std::endl;

					return {};
				}

				return {
					this->complex() / operand,
					this->real() / operand
				};
			}

			/** Quaternion scalar division operator. */
			Quaternion &
			operator/= (data_t operand) const noexcept
			{
				if ( !Utility::isZero(operand) )
				{
					m_data[X] /= operand;
					m_data[Y] /= operand;
					m_data[Z] /= operand;
					m_data[W] /= operand;
				}
				else
				{
					std::cerr << __PRETTY_FUNCTION__ << ", division by zero !" << std::endl;
				}

				return *this;
			}

			Quaternion &
			set (data_t x, data_t y, data_t z, data_t w) noexcept
			{
				m_data[X] = x;
				m_data[Y] = y;
				m_data[Z] = z;
				m_data[W] = w;

				return *this;
			}

			Quaternion &
			setEulerAngles (data_t x, data_t y, data_t z) noexcept
			{
				auto angle = x * 0.5F;
				const auto sr = std::sin(angle);
				const auto cr = std::cos(angle);

				angle = y * 0.5F;
				const auto sp = std::sin(angle);
				const auto cp = std::cos(angle);

				angle = z * 0.5F;
				const auto sy = std::sin(angle);
				const auto cy = std::cos(angle);

				const auto cpcy = cp * cy;
				const auto spcy = sp * cy;
				const auto cpsy = cp * sy;
				const auto spsy = sp * sy;

				m_data[X] = sr * cpcy - cr * spsy;
				m_data[Y] = cr * spcy + sr * cpsy;
				m_data[Z] = cr * cpsy - sr * spcy;
				m_data[W] = cr * cpcy + sr * spsy;

				return this->normalize();
			}

			inline
			Quaternion &
			setEulerAngles (const Vector< 3, data_t > & euler) noexcept
			{
				return this->setEulerAngles(euler[X], euler[Y], euler[Z]);
			}

			void
			setComplex (const Vector< 3, data_t > & complex) noexcept
			{
				m_data[X] = complex[X];
				m_data[Y] = complex[Y];
				m_data[Z] = complex[Z];
			}

			Vector< 3, data_t >
			complex () const noexcept
			{
				return {m_data[X], m_data[Y], m_data[Z]};
			}

			void
			setReal (data_t real) noexcept
			{
				m_data[W] = real;
			}

			data_t
			real () const noexcept
			{
				return m_data[W];
			}

			Vector< 4, data_t >
			toVector4 () const noexcept
			{
				return {m_data[X], m_data[Y], m_data[Z], m_data[W]};
			}

			Quaternion &
			loadIdentity () noexcept
			{
				m_data = {0.0, 0.0, 0.0, 1.0};

				return *this;
			}

			Quaternion &
			conjugate () noexcept
			{
				m_data[X] = -m_data[X];
				m_data[Y] = -m_data[Y];
				m_data[Z] = -m_data[Z];

				return *this;
			}

			Quaternion
			conjugated () const noexcept
			{
				return {this->complex().inverse(), this->real()};
			}

			/** Computes the inverse of this quaternion.
			 * @note This is a general inverse. If you know a priori that you're using a unit quaternion (i.e., norm() == 1), it will be significantly faster to use conjugate() instead.
			 * @return The quaternion q such that q * (*this) == (*this) * q == [ 0 0 0 1 ]. */
			Quaternion
			inversed () const noexcept
			{
				return this->conjugate() / this->length();
			}

			/** Returns the inverse of this quaternion. */
			Quaternion &
			inverse () noexcept
			{
				*this = this->conjugate() / this->length();

				return *this;
			}

			Quaternion &
			normalize () noexcept
			{
				const auto normal = (m_data[X] * m_data[X]) + (m_data[Y] * m_data[Y]) + (m_data[Z] * m_data[Z]) + (m_data[W] * m_data[W]);

				if ( !Utility::equal(normal, 1.0) )
				{
					*this *= reciprocalSquareRoot(normal);
				}

				return *this;
			}

			/** Returns the length (norm or magnitude) of the quaternion. */
			data_t
			length () const noexcept
			{
				return std::sqrt((m_data[X] * m_data[X]) + (m_data[Y] * m_data[Y]) + (m_data[Z] * m_data[Z]) + (m_data[W] * m_data[W]));
			}

			static
			data_t
			dot (const Quaternion & qA, const Quaternion & qB) noexcept
			{
				return (qA.m_data[0] * qB.m_data[0]) + (qA.m_data[1] * qB.m_data[1]) + (qA.m_data[2] * qB.m_data[2]) + (qA.m_data[3] * qB.m_data[3]);
			}

			/** Computes the product of this quaternion with the quaternion 'rhs'. */
			static
			Quaternion
			product (const Quaternion & qA, const Quaternion & qB) noexcept
			{
				return {
					qA.m_data[Y] * qB.m_data[Z] - qA.m_data[Z] * qB.m_data[Y] + qA.m_data[X] * qB.m_data[W] + qA.m_data[W] * qB.m_data[X],
					qA.m_data[Z] * qB.m_data[X] - qA.m_data[X] * qB.m_data[Z] + qA.m_data[Y] * qB.m_data[W] + qA.m_data[W] * qB.m_data[Y],
					qA.m_data[X] * qB.m_data[Y] - qA.m_data[Y] * qB.m_data[X] + qA.m_data[Z] * qB.m_data[W] + qA.m_data[W] * qB.m_data[Z],
					qA.m_data[W] * qB.m_data[W] - qA.m_data[X] * qB.m_data[X] - qA.m_data[Y] * qB.m_data[Y] - qA.m_data[Z] * qB.m_data[Z]
				};
			}

			/** Sets this quaternion to the linear interpolation between two quaternions.
			 * @param qA First quaternion to be interpolated.
			 * @param qB Second quaternion to be interpolated.
			 * @param time Progress of interpolation. */
			static
			Quaternion
			lerp (const Quaternion & qA, const Quaternion & qB, data_t time) noexcept
			{
				return (qA * (1.0 - time)) + (qB * time);
			}

			/** Returns quaternion that is slerped by fraction 't' between two quaternions. */
			static
			Quaternion
			slerp (const Quaternion & qA, const Quaternion & qB, data_t time) noexcept
			{
				auto omega = std::acos(clamp(Quaternion::dot(qA, qB), -1.0, 1.0));

				if ( Utility::isZero(omega) )
				{
					omega = std::numeric_limits<data_t>::epsilon();
				}

				const auto som = std::sin(omega);
				const auto st0 = std::sin((1.0 - time) * omega) / som;
				const auto st1 = std::sin(time * omega) / som;

				return {
					qA.m_data[0] * st0 + qB.m_data[0] * st1,
					qA.m_data[1] * st0 + qB.m_data[1] * st1,
					qA.m_data[2] * st0 + qB.m_data[2] * st1,
					qA.m_data[3] * st0 + qB.m_data[3] * st1
				};
			}

			/** Sets this quaternion to the result of the spherical interpolation between two quaternions
			 * @param qA First quaternion to be interpolated.
			 * @param qB Second quaternion to be interpolated.
			 * @param time Progress of interpolation.
			 * @param threshold To avoid inaccuracies at the end (time=1) the interpolation switches to linear interpolation at some point. This value defines how much of the remaining interpolation will be calculated with linearInterpolation. Everything from 1-threshold up will be linear interpolation. */
			static
			Quaternion &
			slerp (const Quaternion & qA, const Quaternion & qB, data_t time, data_t threshold = 0.05) noexcept
			{
				auto angle = Quaternion::dot(qA, qB);

				/* Make sure we use the short rotation. */
				if ( angle < 0.0 )
				{
					qA *= -1.0;
					angle *= -1.0;
				}

				/* Spherical interpolation. */
				if ( angle <= (1.0 - threshold) )
				{
					const auto theta = std::acos(angle);
					const auto invsintheta = reciprocal(sinf(theta));
					const auto scale = std::sin(theta * (1.0 - time)) * invsintheta;
					const auto invscale = std::sin(theta * time) * invsintheta;

					return (qA * scale) + (qB * invscale);
				}

				/* linear interpolation. */
				return Quaternion::lerp(qA, qB, time);
			}

			/** Creates quaternion from rotation angle and rotation axis.
			 * @note Axis must be unit length. The quaternion representing the rotation is "q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)".
			 * @param angle Rotation Angle in radians.
			 * @param axis Rotation axis. */
			Quaternion &
			fromAngleAxis (data_t angle, const Vector< 3, data_t > & axis) noexcept
			{
				const auto halfAngle = 0.5 * angle;
				const auto sin = std::sin(halfAngle);

				m_data[W] = std::cos(halfAngle);
				m_data[X] = sin * axis[X];
				m_data[Y] = sin * axis[Y];
				m_data[Z] = sin * axis[Z];

				return *this;
			}

			/** Fills an angle (radians) around an axis (unit vector) */
			void
			toAngleAxis (data_t & angle, Vector< 3, data_t > & axis) const noexcept
			{
				const auto scale = std::sqrt(m_data[X] * m_data[X] + m_data[Y] * m_data[Y] + m_data[Z] * m_data[Z]);

				if ( Utility::isZero(scale) || m_data[W] > 1.0 || m_data[W] < -1.0 )
				{
					angle = 0.0;
					axis[X] = 0.0;
					axis[Y] = 1.0;
					axis[X] = 0.0;
				}
				else
				{
					const auto invscale = reciprocal(scale);

					angle = 2.0 * std::acos(m_data[W]);
					axis[X] = m_data[X] * invscale;
					axis[Y] = m_data[Y] * invscale;
					axis[Z] = m_data[Z] * invscale;
				}
			}

			/** Output this quaternion to an Euler angle (radians) */
			void
			toEuler (Vector< 3, data_t > & euler) const noexcept
			{
				const auto sqw = m_data[W] * m_data[W];
				const auto sqx = m_data[X] * m_data[X];
				const auto sqy = m_data[Y] * m_data[Y];
				const auto sqz = m_data[Z] * m_data[Z];

				const auto test = 2.0 * (m_data[Y] * m_data[W] - m_data[X] * m_data[Z]);

				if ( Utility::equal(test, 1.0) )
				{
					/* heading = rotation about z-axis. */
					euler[Z] = -2.0 * std::atan2(m_data[X], m_data[W]);
					/* bank = rotation about x-axis. */
					euler[X] = 0.0;
					/* attitude = rotation about y-axis. */
					euler[Y] = (Pi< data_t >) / 2.0;
				}
				else if ( Utility::equal(test, -1.0) )
				{
					/* heading = rotation about z-axis. */
					euler[Z] = 2.0 * std::atan2(m_data[X], m_data[W]);
					/* bank = rotation about x-axis. */
					euler[X] = 0.0;
					/* attitude = rotation about y-axis. */
					euler[Y] = (Pi< data_t >) / -2.0;
				}
				else
				{
					/* heading = rotation about z-axis. */
					euler[Z] = std::atan2(2.0 * (m_data[X] * m_data[Y] + m_data[Z] * m_data[W]), (sqx - sqy - sqz + sqw));
					/* bank = rotation about x-axis. */
					euler[X] = std::atan2(2.0 * (m_data[Y] * m_data[Z] + m_data[X] * m_data[W]),(-sqx - sqy + sqz + sqw));
					/* attitude = rotation about y-axis. */
					euler[Y] = std::asin(clamp(test, -1.0, 1.0));
				}
			}

			/** Sets quaternion to represent a rotation from one vector to another. */
			Quaternion &
			rotationFromTo (const Vector< 3, data_t > & from, const Vector< 3, data_t > & to) noexcept
			{
				auto v0 = from.normalized();
				auto v1 = to.normalized();

				const auto d = Vector< 3, data_t >::dot(v0, v1);

				/* If dot == 1, vectors are the same */
				if ( d >= 1.0 )
				{
					return this->loadIdentitm_data[Y];
				}

				/* exactly opposite */
				if ( d <= -1.0 )
				{
					auto axis = Vector< 3, data_t >::cross({1.0, 0.0, 0.0}, v0);

					if ( axis.length() == 0.0 )
					{
						axis = Vector<3, data_t>::cross({0.0, 1.0, 0.0}, v0);
					}

					/* same as fromAngleAxis(core::PI, axis).normalize(); */
					return this->set(axis[X], axis[Y], axis[Z], 0.0).normalize();
				}

				const auto s = std::sqrt((1.0 + d) * 2.0); // optimize inv_sqrt
				const auto invS = 1.0 / s;
				const auto c = Vector< 3, data_t >::cross(v0, v1) * invS;

				return this->set(c[X], c[Y], c[Z], s * 0.5F).normalize();
			}

			/**
			 * @brief Computes the rotation matrix represented by a unit quaternion.
			 * @note This does not check that this quaternion is normalized.
			 * It returns the matrix, which will not be a rotation if the quaternion is non-unit.
			 */
			Matrix< 3, data_t >
			rotationMatrix () const noexcept
			{
				std::array< data_t, 9 > m {
					1.0 - 2.0 * m_data[Y] * m_data[Y] - 2.0 * m_data[Z] * m_data[Z],
						  2.0 * m_data[X] * m_data[Y] - 2.0 * m_data[Z] * m_data[W],
						  2.0 * m_data[X] * m_data[Z] + 2.0 * m_data[Y] * m_data[W],

						  2.0 * m_data[X] * m_data[Y] + 2.0 * m_data[Z] * m_data[W],
					1.0 - 2.0 * m_data[X] * m_data[X] - 2.0 * m_data[Z] * m_data[Z],
						  2.0 * m_data[Y] * m_data[Z] - 2.0 * m_data[X] * m_data[W],

						  2.0 * m_data[X] * m_data[Z] - 2.0 * m_data[Y] * m_data[W],
						  2.0 * m_data[Y] * m_data[Z] + 2.0 * m_data[X] * m_data[W],
					1.0 - 2.0 * m_data[X] * m_data[X] - 2.0 * m_data[Y] * m_data[Y]
				};

				return Matrix< 3, data_t >{m};
			}

			/** Returns the scaled-axis representation of this quaternion rotation. */
			Vector< 3, data_t >
			scaledAxis () const noexcept
			{
				std::array< data_t, 3 > axis;

				/* FIXME: Find the black magic behind this ! */
				//HeliMath::scaled_axis_from_quaternion(axis.data(), m_data.data());

				return Vector< 3, data_t >{axis};
			}

			/** Sets quaternion to be same as rotation by scaled axis w. */
			void
			scaledAxis (const Vector< 3, data_t > & w) noexcept
			{
				auto theta = w.length();

				if ( theta > 0.0001 )
				{
					auto s = std::sin(theta / 2.0);

					Vector< 3, data_t > tmp(w / theta * s);

					m_data[0] = tmp[X];
					m_data[1] = tmp[Y];
					m_data[2] = tmp[Z];
					m_data[3] = std::cos(theta / 2.0);
				}
				else
				{
					m_data[0] = m_data[1] = m_data[2] = 0;
					m_data[3] = 1.0;
				}
			}

			/** Returns a vector rotated by this quaternion. Functionally equivalent to:  (rotationMatrim_data[X] * v) or (q * Quaternion(0, v) * q.inverse()).
			 * @warning  conjugate() is used instead of inverse() for better performance, when this quaternion must be normalized. */
			Vector< 3, data_t >
			rotatedVector (const Vector< 3, data_t > & v) const noexcept
			{
				return (((*this) * Quaternion(v, 0)) * this->conjugate()).complex();
			}

			/** Computes the quaternion that is equivalent to a given euler angle rotation.
			 * @param euler A 3-vector in order:  roll-pitch-yaw. */
			void
			euler (const Vector< 3, data_t > & euler) noexcept
			{
				auto c1 = std::cos(euler[Z] * 0.5);
				auto c2 = std::cos(euler[Y] * 0.5);
				auto c3 = std::cos(euler[X] * 0.5);
				auto s1 = std::sin(euler[Z] * 0.5);
				auto s2 = std::sin(euler[Y] * 0.5);
				auto s3 = std::sin(euler[X] * 0.5);

				m_data[0] = c1*c2*s3 - s1*s2*c3;
				m_data[1] = c1*s2*c3 + s1*c2*s3;
				m_data[2] = s1*c2*c3 - c1*s2*s3;
				m_data[3] = c1*c2*c3 + s1*s2*s3;
			}

			/** Returns an equivalent euler angle representation of this quaternion.
			 * @return Euler angles in roll-pitch-yaw order. */
			Vector< 3, data_t >
			euler () const noexcept
			{
				const static auto PiOver2 = Pi< data_t > * 0.5;

				Vector< 3, data_t > euler;

				/* Quick conversion to Euler angles to give tilt to user. */
				auto sqw = m_data[3] * m_data[3];
				auto sqx = m_data[0] * m_data[0];
				auto sqy = m_data[1] * m_data[1];
				auto sqz = m_data[2] * m_data[2];

				euler[Y] = std::asin(2.0 * (m_data[3] * m_data[1] - m_data[0] * m_data[2]));

				if ( PiOver2 - std::abs(euler[Y]) > std::numeric_limits< data_t >::epsilon() )
				{
					euler[Z] = std::atan2(2.0 * (m_data[0] * m_data[1] + m_data[3] * m_data[2]), sqx - sqy - sqz + sqw);
					euler[X] = std::atan2(2.0 * (m_data[3] * m_data[0] + m_data[1] * m_data[2]), sqw - sqx - sqy + sqz);
				}
				else
				{
					/* Compute heading from local 'down' vector. */
					euler[Z] = std::atan2(2 * m_data[1] * m_data[2] - 2 * m_data[0] * m_data[3], 2 * m_data[0] * m_data[2] + 2 * m_data[1] * m_data[3]);
					euler[X] = 0.0;

					/* If facing down, reverse yaw. */
					if ( euler[X] < 0 )
						euler[Z] = Pi< data_t > - euler[Z];
				}

				return euler;
			}

			/** Computes a special representation that decouples the Z rotation. The decoupled representation is two rotations, Qxy and Qz, so that Q = Qxy * Qz. */
			void
			decoupleZ (Quaternion * Qxy, Quaternion * Qz) const noexcept
			{
				Vector< 3, data_t > ztt(0.0, 0.0, 1.0);
				auto zbt = this->rotatedVector(ztt);
				auto axis_xy = Vector< 3, data_t >::cross(ztt, zbt);
				auto axis_norm = axis_xy.length();

				auto axis_theta = std::acos(clamp(zbt[Z], -1.0, 1.0));

				if ( axis_norm > 0.00001 )
				{
					axis_xy = axis_xy * (axis_theta / axis_norm); // limit is *1
				}

				Qxy->scaledAxis(axis_xy);
				*Qz = (Qxy->conjugate() * (*this));
			}


			/** Returns a matrix representation of this quaternion. Specifically this is the matrix such that:
			 * this->matrim_data[X] * q.vector() = (*this) * q for any quaternion q.
			 * Note that this is @e NOT the rotation matrix that may be represented by a unit quaternion. */
			Matrix< 4, data_t >
			matrix () const noexcept
			{
				std::array< data_t, 16 > m{
					 m_data[W], -m_data[Z],  m_data[Y],  m_data[X],
					 m_data[Z],  m_data[W], -m_data[X],  m_data[Y],
					-m_data[Y],  m_data[X],  m_data[W],  m_data[Z],
					-m_data[X], -m_data[Y], -m_data[Z],  m_data[W]
				};

				return Matrix< 4, data_t >{m};
			}

			/** Returns a matrix representation of this quaternion for right multiplication. Specifically this is the matrix such that:
			 * q.vector().transpose() * this->matrim_data[X] = (q * (*this)).vector().transpose() for any quaternion q.
			 * Note that this is @e NOT the rotation matrix that may be represented by a unit quaternion. */
			Matrix< 4, data_t >
			rightMatrix () const noexcept
			{
				std::array< data_t, 16 > m{
					+m_data[W], -m_data[Z],  m_data[Y], -m_data[X],
					+m_data[Z],  m_data[W], -m_data[X], -m_data[Y],
					-m_data[Y],  m_data[X],  m_data[W], -m_data[Z],
					+m_data[X],  m_data[Y],  m_data[Z],  m_data[W]
				};

				return Matrix< 4, data_t >{m};
			}

			/** Creates a matrix from this quaternion. */
			Matrix< 4, data_t >
			getMatrix () const noexcept
			{
				Matrix< 4, data_t > m;

				this->getMatrix(m);

				return m;
			}

			/** Creates a matrix from this quaternion. */
			void
			getMatrix (Matrix< 4, data_t > & dest, const Vector< 3, data_t > & center = {}) const noexcept
			{
				dest[0] = 1.0 - 2.0 * m_data[Y] * m_data[Y] - 2.0 * m_data[Z] * m_data[Z];
				dest[1] = 2.0 * m_data[X] * m_data[Y] + 2.0 * m_data[Z] * m_data[W];
				dest[2] = 2.0 * m_data[X] * m_data[Z] - 2.0 * m_data[Y] * m_data[W];
				dest[3] = 0.0;

				dest[4] = 2.0 * m_data[X] * m_data[Y] - 2.0 * m_data[Z] * m_data[W];
				dest[5] = 1.0 - 2.0 * m_data[X] * m_data[X] - 2.0 * m_data[Z] * m_data[Z];
				dest[6] = 2.0 * m_data[Z] * m_data[Y] + 2.0 * m_data[X] * m_data[W];
				dest[7] = 0.0;

				dest[8] = 2.0 * m_data[X] * m_data[Z] + 2.0 * m_data[Y] * m_data[W];
				dest[9] = 2.0 * m_data[Z] * m_data[Y] - 2.0 * m_data[X] * m_data[W];
				dest[10] = 1.0 - 2.0 * m_data[X] * m_data[X] - 2.0 * m_data[Y] * m_data[Y];
				dest[11] = 0.0;

				dest[12] = center[X];
				dest[13] = center[Y];
				dest[14] = center[Z];
				dest[15] = 1.0;

				/* FIXME: Find the black magic behind this ! */
				dest.setDefinitelyIdentityMatrix(false);
			}

			/*!
				Creates a matrix from this quaternion
				Rotate about a center point
				shortcut for
				core::quaternion q;
				q.rotationFromTo ( vin[i].Normal, forward );
				q.getMatrixCenter ( lookat, center, newPos );

				core::Matrix< 4, data_t > m2;
				m2.setInverseTranslation ( center );
				lookat *= m2;

				core::Matrix< 4, data_t > m3;
				m2.setTranslation ( newPos );
				lookat *= m3;

			*/
			void
			getMatrixCenter (Matrix< 4, data_t > & dest, const Vector< 3, data_t > & center, const Vector< 3, data_t > & translation) const noexcept
			{
				dest[0] = 1.0 - 2.0 * m_data[Y] * m_data[Y] - 2.0 * m_data[Z] * m_data[Z];
				dest[1] = 2.0 * m_data[X] * m_data[Y] + 2.0 * m_data[Z] * m_data[W];
				dest[2] = 2.0 * m_data[X] * m_data[Z] - 2.0 * m_data[Y] * m_data[W];
				dest[3] = 0.0;

				dest[4] = 2.0 * m_data[X] * m_data[Y] - 2.0 * m_data[Z] * m_data[W];
				dest[5] = 1.0 - 2.0 * m_data[X] * m_data[X] - 2.0 * m_data[Z] * m_data[Z];
				dest[6] = 2.0 * m_data[Z] * m_data[Y] + 2.0 * m_data[X] * m_data[W];
				dest[7] = 0.0;

				dest[8] = 2.0 * m_data[X] * m_data[Z] + 2.0 * m_data[Y] * m_data[W];
				dest[9] = 2.0 * m_data[Z] * m_data[Y] - 2.0 * m_data[X] * m_data[W];
				dest[10] = 1.0 - 2.0 * m_data[X] * m_data[X] - 2.0 * m_data[Y] * m_data[Y];
				dest[11] = 0.0;

				/* FIXME: Find the black magic behind this ! */
				dest.setRotationCenter(center, translation);
			}

			/** Creates a matrix from this quaternion. */
			inline
			void
			getMatrix_transposed (Matrix< 4, data_t > & dest) const noexcept
			{
				dest[0] = 1.0 - 2.0 * m_data[Y] * m_data[Y] - 2.0 * m_data[Z] * m_data[Z];
				dest[4] = 2.0 * m_data[X] * m_data[Y] + 2.0 * m_data[Z] * m_data[W];
				dest[8] = 2.0 * m_data[X] * m_data[Z] - 2.0 * m_data[Y] * m_data[W];
				dest[12] = 0.0;

				dest[1] = 2.0 * m_data[X] * m_data[Y] - 2.0 * m_data[Z] * m_data[W];
				dest[5] = 1.0 - 2.0 * m_data[X] * m_data[X] - 2.0 * m_data[Z] * m_data[Z];
				dest[9] = 2.0 * m_data[Z] * m_data[Y] + 2.0 * m_data[X] * m_data[W];
				dest[13] = 0.0;

				dest[2] = 2.0 * m_data[X] * m_data[Z] + 2.0 * m_data[Y] * m_data[W];
				dest[6] = 2.0 * m_data[Z] * m_data[Y] - 2.0 * m_data[X] * m_data[W];
				dest[10] = 1.0 - 2.0 * m_data[X] * m_data[X] - 2.0 * m_data[Y] * m_data[Y];
				dest[14] = 0.0;

				dest[3] = 0.0;
				dest[7] = 0.0;
				dest[11] = 0.0;
				dest[15] = 1.0;

				/* FIXME: Find the black magic behind this ! */
				dest.setDefinitelyIdentityMatrix(false);
			}

			/** Reset vector to 0.
			 * @return A reference to this vector. */
			Quaternion &
			reset () noexcept
			{
				m_data[X] = 0;
				m_data[Y] = 0;
				m_data[Z] = 0;
				m_data[W] = 0;

				return *this;
			}

			/** Copy the quaternion data insided a C-Array of data_t.
			 * @warning  The target must provide enough space. */
			void
			copy (data_t * target) const noexcept
			{
				target[0] = m_data[X];
				target[1] = m_data[Y];
				target[2] = m_data[Z];
				target[3] = m_data[W];
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
			operator<< (std::ostream & out, const Quaternion & obj)
			{
				using namespace std;

				return out << "Quaternion(" << fixed << setprecision(8) << '[' << setw(16) << obj.m_data[0] << ", " << setw(16) << obj.m_data[1] << ", " << setw(16) << obj.m_data[2] << ", " << setw(16) << obj.m_data[3] << ')';
			}

			/**
			 * Stringify the object.
			 *
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend
			std::string
			to_string (const Quaternion & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			std::array< data_t, 4 > m_data{0.0, 0.0, 0.0, 1.0};
	};

	// NOLINTEND(cppcoreguidelines-pro-bounds-pointer-arithmetic, readability-identifier-length, *-magic-numbers)
}
