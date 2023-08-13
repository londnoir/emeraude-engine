/*
 * Libraries/Math/Vector.hpp
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
#include <algorithm>
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

/* Local inclusions for usages. */
#include "Utility.hpp"
#include "String.hpp" // FIXME : Should not be here !

namespace Libraries::Math
{
	// NOLINTBEGIN(readability-identifier-length, *-magic-numbers)

	constexpr auto X = 0UL;
	constexpr auto Y = 1UL;
	constexpr auto Z = 2UL;
	constexpr auto W = 3UL;

	constexpr auto U = 0UL;
	constexpr auto V = 1UL;

	constexpr auto R = 0UL;
	constexpr auto G = 1UL;
	constexpr auto B = 2UL;
	constexpr auto A = 3UL;

	/**
	 * @brief Defines a vector from two to four values suitable for 3D graphics.
	 * @tparam dim_t The dimension of the vector. This can be 2, 3 or 4.
	 * @tparam data_t The type for the vector data. Default float.
	 * @note For position the fourth component should be 1 and for direction, it should be 0.
	 * In that way, translation with matrices won't affect direction vectors.
	 */
	template<
		std::size_t dim_t,
		typename data_t = float,
		std::enable_if_t< dim_t == 2 || dim_t == 3 || dim_t == 4, bool > = false,
		std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false
	>
	class Vector final
	{
		public:

			/**
			 * @brief Constructs a default vector.
			 */
			constexpr
			Vector () noexcept = default;

			/**
			 * @brief Swizzle constructor for Vector< 2, data_t >.
			 * @param vector A reference to a Vector< 3, data_t >.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			constexpr
			explicit
			Vector (const Vector< 3, data_t > & vector) noexcept
				: m_data({vector[X], vector[Y]})
			{

			}

			/**
			 * @brief Swizzle constructor for Vector< 2, data_t >.
			 * @param vector A reference to a Vector< 4, data_t >.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			constexpr
			explicit
			Vector (const Vector< 4, data_t > & vector) noexcept
				: m_data({vector[X], vector[Y]})
			{

			}

			/**
			 * @brief Swizzle constructor for Vector< 3, data_t >.
			 * @param vector A reference to a Vector< 2, data_t >.
			 * @param z Z component value. Default 0.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3, bool > = false >
			constexpr
			explicit
			Vector (const Vector< 2, data_t > & vector, data_t z = 0) noexcept
				: m_data({vector[X], vector[Y], z})
			{

			}

			/**
			 * @brief Swizzle constructor for Vector< 3, data_t >.
			 * @param vector A reference to a Vector< 4, data_t >.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3, bool > = false >
			constexpr
			explicit
			Vector (const Vector< 4, data_t > & vector) noexcept
				: m_data({vector[X], vector[Y], vector[Z]})
			{

			}

			/**
			 * @brief Swizzle constructor for Vector< 4, data_t >.
			 * @param vector A reference to a Vector< 2, data_t >.
			 * @param z Z component value. Default 0.
			 * @param w W component value. Default 0.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			constexpr
			explicit
			Vector (const Vector< 2, data_t > & vector, data_t z = 0, data_t w = 0) noexcept
				: m_data({vector[X], vector[Y], z, w})
			{

			}

			/**
			 * @brief Swizzle constructor for Vector< 4, data_t >.
			 * @param vector A reference to a Vector< 3, data_t >.
			 * @param w W component value. Default 0.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			constexpr
			explicit
			Vector (const Vector< 3, data_t > & vector, data_t w = 0) noexcept
				: m_data({vector[X], vector[Y], vector[Z], w})
			{

			}

			/**
			 * @brief Simple parametric constructor for Vector< 2, data_t >.
			 * @param x Value of the vector first component.
			 * @param y Value of the vector second component.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			constexpr
			Vector (data_t x, data_t y) noexcept
				: m_data({x, y})
			{

			}

			/**
			 * @brief Simple parametric constructor for Vector< 3, data_t >.
			 * @param x Value of the vector first component.
			 * @param y Value of the vector second component.
			 * @param z Value of the vector third component.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3, bool > = false >
			constexpr
			Vector (data_t x, data_t y, data_t z) noexcept
				: m_data({x, y, z})
			{

			}

			/**
			 * @brief Simple parametric constructor for Vector< 4, data_t >.
			 * @param x Value of the vector first component.
			 * @param y Value of the vector second component.
			 * @param z Value of the vector third component.
			 * @param w Value of the vector fourth component. Default is 0.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			constexpr
			Vector (data_t x, data_t y, data_t z, data_t w = 0) noexcept
				: m_data({x, y, z, w})
			{

			}

			/**
			 * @brief Constructs a vector from STL array.
			 * @param data A std::array of N value.
			 */
			explicit
			constexpr
			Vector (const std::array< data_t, dim_t > & data) noexcept
				: m_data(data)
			{

			}

			/**
			 * @brief Constructs a vector from C-Style array.
			 * @warning Unsafe !
			 * @param data A pointer to a C-Style containing at least the dimension of the vector.
			 */
			explicit
			Vector (const data_t * data) noexcept
			{
				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					m_data[index] = data[index]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
				}
			}

			/**
			 * @brief Builds a Vector< dim_t, data_t > using a raw definition from a std::string.
			 * @param str The string containing the vector definition.
			 * @param separator A char to specify the values separator. Default is ' '.
			 * @param offset An index where to execute copying values. Default is 0.
			 */
			explicit
			Vector (const std::string & str, char separator = ' ', size_t offset = 0) noexcept
			{
				const auto chunks = String::explode(str, separator, false);

				if ( chunks.size() < (offset + dim_t) )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", invalid parameter !" "\n";

					return;
				}

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					m_data[index] = static_cast< data_t >(String::toNumber< double >(chunks[offset + index]));
				}
			}

			/**
			 * @brief Copy assignment operator specialization from Vector< 2, data_t >.
			 * @param copy The copied vector.
			 * @return Vector
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N != 2, bool > = false >
			Vector &
			operator= (const Vector< 2, data_t > & copy) noexcept
			{
				m_data[X] = copy[X];
				m_data[Y] = copy[Y];

				if constexpr ( dim_t == 3 || dim_t == 4 )
				{
					m_data[Z] = 0;
				}

				if constexpr ( dim_t == 4 )
				{
					m_data[W] = 0;
				}

				return *this;
			}

			/**
			 * @brief Copy assignment operator specialization from Vector< 3, data_t >.
			 * @param copy The copied vector.
			 * @return Vector &
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N != 3, bool > = false >
			Vector &
			operator= (const Vector< 3, data_t > & copy) noexcept
			{
				m_data[X] = copy[X];
				m_data[Y] = copy[Y];

				if constexpr ( dim_t == 3 || dim_t == 4 )
				{
					m_data[Z] = copy[Z];
				}

				return *this;
			}

			/**
			 * @brief Copy assignment operator specialization from Vector< 4, data_t >.
			 * @param copy The copied vector.
			 * @return Vector &
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N != 4, bool > = false >
			Vector &
			operator= (const Vector< 4, data_t > & copy) noexcept
			{
				m_data[X] = copy[X];
				m_data[Y] = copy[Y];

				if constexpr ( dim_t == 3 || dim_t == 4 )
				{
					m_data[Z] = copy[Z];
				}

				if constexpr ( dim_t == 4 )
				{
					m_data[W] = copy[W];
				}

				return *this;
			}

			/**
			 * @brief Returns a copy of the Vector< dim_t, data_t >.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			operator+ () const noexcept
			{
				return *this;
			}

			/**
			 * @brief Returns the reverse copy of the Vector< dim_t, data_t >.
			 * @note Same as operation as method inverse().
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			operator- () const noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = -m_data[index];
				}

				return vector;
			}

			/**
			 * @brief Data accessor.
			 * @param index The index of vector element.
			 * @return data_t &
			 */
			data_t &
			operator[] (size_t index) noexcept
			{
				return m_data[index];
			}

			/**
			 * @brief Data accessor (const version).
			 * @param index The index of vector element.
			 * @return const data_t &
			 */
			[[nodiscard]]
			const data_t &
			operator[] (size_t index) const noexcept
			{
				return m_data[index];
			}

			/**
			 * @brief Performs an equality comparison between vectors.
			 * @param operand A reference to an other vector.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator== (const Vector & operand) const noexcept
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

					if constexpr ( dim_t == 3 || dim_t == 4 )
					{
						if ( !Utility::equal(m_data[Z], operand.m_data[Z]) )
						{
							return false;
						}
					}

					if constexpr ( dim_t == 4 )
					{
						if ( !Utility::equal(m_data[W], operand.m_data[W]) )
						{
							return false;
						}
					}
				}

				return true;
			}

			/**
			 * @brief Performs an inequality comparison between vectors.
			 * @param operand A reference to an other vector.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator!= (const Vector & operand) const noexcept
			{
				return !this->operator==(operand);
			}

			/**
			 * @brief Returns the addition between two vectors.
			 * @param operand A reference to an other vector.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			operator+ (const Vector & operand) const noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = m_data[index] + operand.m_data[index];
				}

				return vector;
			}

			/**
			 * @brief Returns the addition between a vector and a scalar.
			 * @param operand A scalar.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			operator+ (const data_t & operand) const noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = m_data[index] + operand;
				}

				return vector;
			}

			/**
			 * @brief Returns the addition with an other vector.
			 * @param operand A reference to an other vector.
			 * @return Vector &
			 */
			Vector &
			operator+= (const Vector & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					#pragma omp simd
					for ( size_t index = 0; index < dim_t; index++ )
					{
						m_data[index] += operand.m_data[index];
					}
				}

				return *this;
			}

			/**
			 * @brief Returns the addition with a scalar.
			 * @param operand A scalar.
			 * @return Vector &
			 */
			Vector &
			operator+= (const data_t & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					#pragma omp simd
					for ( size_t index = 0; index < dim_t; index++ )
					{
						m_data[index] += operand;
					}
				}

				return *this;
			}

			/**
			 * @brief Returns the subtraction between two vectors.
			 * @param operand A reference to an other vector.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			operator- (const Vector & operand) const noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = m_data[index] - operand.m_data[index];
				}

				return vector;
			}

			/**
			 * @brief Returns the subtraction between a vector and a scalar.
			 * @param operand A scalar.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			operator- (const data_t & operand) const noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = m_data[index] - operand;
				}

				return vector;
			}

			/**
			 * @brief Returns the subtraction with an other vector.
			 * @param operand A reference to an other vector.
			 * @return Vector &
			 */
			Vector &
			operator-= (const Vector & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					#pragma omp simd
					for ( size_t index = 0; index < dim_t; index++ )
					{
						m_data[index] -= operand.m_data[index];
					}
				}

				return *this;
			}

			/**
			 * @brief Returns the subtraction with a scalar.
			 * @param operand A scalar.
			 * @return Vector &
			 */
			Vector &
			operator-= (const data_t & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					#pragma omp simd
					for ( size_t index = 0; index < dim_t; index++ )
					{
						m_data[index] -= operand;
					}
				}

				return *this;
			}

			/**
			 * @brief Returns the multiplication between two vectors.
			 * @param operand A reference to an other vector.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			operator* (const Vector & operand) const noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = m_data[index] * operand.m_data[index];
				}

				return vector;
			}

			/**
			 * @brief Returns the multiplication between a vector and a scalar.
			 * @param operand A scalar.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			operator* (const data_t & operand) const noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = m_data[index] * operand;
				}

				return vector;
			}

			/**
			 * @brief Returns the multiplication with an other vector.
			 * @param operand A reference to an other vector.
			 * @return Vector &
			 */
			Vector &
			operator*= (const Vector & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					#pragma omp simd
					for ( size_t index = 0; index < dim_t; index++ )
					{
						m_data[index] *= operand.m_data[index];
					}
				}

				return *this;
			}

			/**
			 * @brief Returns the multiplication with a scalar.
			 * @param operand A scalar.
			 * @return Vector &
			 */
			Vector &
			operator*= (const data_t & operand) noexcept
			{
				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					m_data[index] *= operand;
				}

				return *this;
			}

			/**
			 * @brief Returns the division between two vectors.
			 * @param operand A reference to an other vector.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			operator/ (const Vector & operand) const noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = m_data[index] / operand.m_data[index];
				}

				return vector;
			}

			/**
			 * @brief Returns the division between a vector and a scalar.
			 * @param operand A scalar.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			operator/ (const data_t & operand) const noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = m_data[index] / operand;
				}

				return vector;
			}

			/**
			 * @brief Returns the division between two vectors.
			 * @param operand A reference to an other vector.
			 * @return Vector &
			 */
			Vector &
			operator/= (const Vector & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					#pragma omp simd
					for ( size_t index = 0; index < dim_t; index++ )
					{
						m_data[index] /= operand.m_data[index];
					}
				}

				return *this;
			}

			/**
			 * @brief Returns the division with a scalar.
			 * @param operand A scalar.
			 * @return Vector &
			 */
			Vector &
			operator/= (const data_t & operand) noexcept
			{
				if ( !Utility::isZero(operand) )
				{
					#pragma omp simd
					for ( size_t index = 0; index < dim_t; index++ )
					{
						m_data[index] /= operand;
					}
				}
				else
				{
					std::cerr << __PRETTY_FUNCTION__ << ", division by zero !" "\n";
				}

				return *this;
			}

			/**
			 * @brief Returns the X component.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			x () const noexcept
			{
				return m_data[X];
			}

			/**
			 * @brief Returns the Y component.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			y () const noexcept
			{
				return m_data[Y];
			}

			/**
			 * @brief Returns the Z component.
			 * @return data_t
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4 , bool > = false >
			[[nodiscard]]
			data_t
			z () const noexcept
			{
				return m_data[Z];
			}

			/**
			 * @brief Returns the W component.
			 * @return data_t
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4 , bool > = false >
			[[nodiscard]]
			data_t
			w () const noexcept
			{
				return m_data[W];
			}

			/**
			 * @brief Performs a equality comparison between vectors.
			 * @param operand A reference to an other vector.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			equal (const Vector & operand, data_t epsilon = std::numeric_limits< data_t >::epsilon()) const noexcept
			{
				for ( size_t index = 0; index < dim_t * dim_t; index++ )
				{
					if ( Utility::different(m_data[index], operand.m_data[index], epsilon) )
					{
						return false;
					}
				}

				return true;
			}

			/**
			 * @brief Performs a inequality comparison between vectors.
			 * @param operand A reference to an other vector.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			different (const Vector & operand, data_t epsilon = std::numeric_limits< data_t >::epsilon()) const noexcept
			{
				return !this->equal(operand, epsilon);
			}

			/** @brief Resets vector to 0. */
			void
			reset () noexcept
			{
				m_data.fill(0);
			}

			/**
			 * @brief Returns the vector data as a C array.
			 * @return data_t *
			 */
			[[nodiscard]]
			data_t *
			data () noexcept
			{
				return m_data.data();
			}

			/**
			 * @brief Returns the vector data as a C array.
			 * @return const data_t *
			 */
			[[nodiscard]]
			const data_t *
			data () const noexcept
			{
				return m_data.data();
			}

			/**
			 * @brief Swaps two vectors data.
			 * @param target A reference to an other Vector.
			 */
			void
			swap (Vector & target) noexcept
			{
				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					std::swap(m_data[index], target.m_data[index]);
				}
			}

			/**
			 * @brief Reverses the vector direction.
			 * @return Vector &
			 */
			Vector &
			inverse () noexcept
			{
				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					m_data[index] = -m_data[index];
				}

				return *this;
			}

			/**
			 * @brief Returns the inversed vector.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			inversed () const noexcept
			{
				return Vector::operator-();
			}

			/**
			 * @brief Scales the vector length by a scalar value.
			 * @param scalar Value to multiply with.
			 * @return Vector &
			 */
			Vector &
			scale (data_t scalar) noexcept
			{
				return *this *= scalar;
			}

			/**
			 * @brief Returns a scaled copy of this vector.
			 * @param scalar Value to multiply with.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			scaled (data_t scalar) const noexcept
			{
				return *this * scalar;
			}

			/**
			 * @brief Scales the normalized vector length by a scalar value.
			 * @param scalar Value to multiply with.
			 * @return Vector &
			 */
			[[nodiscard]]
			Vector &
			rescale (data_t scalar) noexcept
			{
				return this->normalize().scale(scalar);
			}

			/**
			 * @brief Returns a rescaled copy of this vector.
			 * @param scalar Value to multiply with.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			rescaled (data_t scalar) const noexcept
			{
				return this->normalized().scale(scalar);
			}

			/**
			 * @brief Returns the squared length of the vector.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			lengthSquared () const noexcept
			{
				data_t value = 0;

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					value += m_data[index] * m_data[index];
				}

				return value;
			}

			/**
			 * @brief Returns the norm (length) of the vector.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			length () const noexcept
			{
				return std::sqrt(this->lengthSquared());
			}

			/**
			 * @brief Rescales the vector length to unit.
			 * @return Vector &
			 */
			Vector &
			normalize () noexcept
			{
				const auto L = this->lengthSquared();

				if ( !Utility::isZero(L) )
				{
					this->scale(static_cast< data_t >(1) / std::sqrt(L));
				}

				return *this;
			}

			/**
			 * @brief Rescales the vector length to unit.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			normalized () const noexcept
			{
				const auto L = this->lengthSquared();

				if ( !Utility::isZero(L) )
				{
					return this->scaled(static_cast< data_t >(1) / std::sqrt(L));
				}

				return {};
			}

			/**
			 * @brief Performs a dot-product between two vectors.
			 * @param lhs A Vector as first operand.
			 * @param rhs A Vector as second operand.
			 * @return data_t
			 */
			[[nodiscard]]
			static
			data_t
			dotProduct (const Vector & lhs, const Vector & rhs) noexcept
			{
				data_t value = 0;

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					value += lhs.m_data[index] * rhs.m_data[index];
				}

				return value;
			}

			/**
			 * @brief Performs a cross-product between two vectors.
			 * @note Specialization for vector 2.
			 * @param lhs A Vector as first operand.
			 * @param rhs A Vector as second operand.
			 * @return data_t
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			[[nodiscard]]
			static
			data_t
			crossProduct (const Vector & lhs, const Vector & rhs) noexcept
			{
				return lhs[X] * rhs[Y] - lhs[Y] * lhs[X];
			}

			/**
			 * @brief Performs a cross-product between two vectors.
			 * @note Specialization for vector 3.
			 * @param lhs A Vector as first operand.
			 * @param rhs A Vector as second operand.
			 * @return Vector
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			static
			Vector
			crossProduct (const Vector & lhs, const Vector & rhs) noexcept
			{
				if constexpr ( dim_t == 3 )
				{
					return {
						lhs.m_data[Y] * rhs.m_data[Z] - lhs.m_data[Z] * rhs.m_data[Y],
						lhs.m_data[Z] * rhs.m_data[X] - lhs.m_data[X] * rhs.m_data[Z],
						lhs.m_data[X] * rhs.m_data[Y] - lhs.m_data[Y] * rhs.m_data[X]
					};
				}

				if constexpr ( dim_t == 4 )
				{
					return {
						lhs.m_data[Y] * rhs.m_data[Z] - lhs.m_data[Z] * rhs.m_data[Y],
						lhs.m_data[Z] * rhs.m_data[X] - lhs.m_data[X] * rhs.m_data[Z],
						lhs.m_data[X] * rhs.m_data[Y] - lhs.m_data[Y] * rhs.m_data[X],
						0.0F
					};
				}
			}

			/**
			 * @brief Returns distance between two points.
			 * @param lhs A Vector representing the first point.
			 * @param rhs A Vector representing the second point.
			 * @return data_t
			 */
			[[nodiscard]]
			static
			data_t
			distance (const Vector & lhs, const Vector & rhs) noexcept
			{
				/* Formula : sqrt( (x2-x1)² + (y2-y1)² + (z2-z1) ) */
				return (rhs - lhs).length();
			}

			/**
			 * @brief Returns squared distance between two points.
			 * @note Faster than distance() to compare two distances.
			 * @param lhs A Vector representing the first point.
			 * @param rhs A Vector representing the second point.
			 * @return data_t
			 */
			[[nodiscard]]
			static
			data_t
			distanceSquared (const Vector & lhs, const Vector & rhs) noexcept
			{
				return (rhs - lhs).lengthSquared();
			}

			/**
			 * @brief Returns distance between this vector and a point.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			distanceToPoint (const Vector & point) const noexcept
			{
				return (*this - point).length();
			}

			/**
			 * @brief Returns squared distance between this vector and a point.
			 * @note Faster than distanceToPoint() to compare two distances.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			distanceSquaredToPoint (const Vector & point) const noexcept
			{
				return (*this - point).lengthSquared();
			}

			/**
			 * @brief Returns distance between this vector and a line.
			 * @param point A point where the line is passing.
			 * @param direction The direction vector of the line.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			distanceToLine (const Vector & point, const Vector & direction) const noexcept
			{
				if ( direction.isNull() )
				{
					return (*this - point).length();
				}

				auto p = point + Vector::dotProduct(*this - point, direction) * direction;

				return (*this - p).length();
			}

			/**
			 * @brief Returns distance between this vector and a line.
			 * @note Faster than distanceToLine() to compare two distances.
			 * @param point A point where the line is passing.
			 * @param direction The direction vector of the line.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			distanceSquaredToLine (const Vector & point, const Vector & direction) const noexcept
			{
				if ( direction.isNull() )
				{
					return (*this - point).lengthSquared();
				}

				auto p = point + Vector::dotProduct(*this - point, direction) * direction;

				return (*this - p).lengthSquared();
			}

			/**
			 * @brief Returns distance between this vector and a plane.
			 * @param plane A vector that defines the plane.
			 * @param normal A vector perpendicular to the plane.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			distanceToPlane (const Vector & plane, const Vector & normal) const noexcept
			{
				return Vector::dotProduct(*this - plane, normal);
			}

			/**
			 * @brief Returns distance between this vector and a plane.
			 * @param pointA A point lying in the plane.
			 * @param pointB A point lying in the plane.
			 * @param pointC A point lying in the plane.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			distanceToPlane (const Vector & pointA, const Vector & pointB, const Vector & pointC) const noexcept
			{
				return Vector::dotProduct(*this - pointA, this->normal(pointB - pointA, pointC - pointA));
			}

			/**
			 * @brief Returns the angle between two vectors in radian.
			 * @note You can use Math::Degree() to convert the result.
			 * @param vectorA A Vector as first operand.
			 * @param vectorB A Vector as second operand.
			 * @return data_t
			 */
			[[nodiscard]]
			static
			data_t
			angle (const Vector & vectorA, const Vector & vectorB) noexcept
			{
				const auto factor = vectorA.length() * vectorB.length();

				if ( factor < 1e-6F )
				{
					factor = 1e-6F;
				}

				return std::acos(clamp(Vector::dotProduct(vectorA, vectorB) / factor, -1.0, 1.0));
			}

			/**
			 * @brief Returns the reflected vector on a surface.
			 * @param incident The Vector to reflect.
			 * @param normal The Vector representing the surface normal where the reflection occurs.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector
			reflect (const Vector & incident, const Vector & normal) noexcept
			{
				/* I' = I - 2 * dot(N, I) * N; */
				//return incident - 2.0F * Vector3::dot(normal, incident) * normal;
				return incident - (normal * (Vector::dotProduct(normal, incident) * 2.0F));
			}

			/**
			 * @brief Returns the refracted vector in a surface.
			 * @param incident The Vector to refract.
			 * @param normal A reference to a Vector representing the surface normal where the refraction occurs.
			 * @param eta Specifies the ratio of indices of refraction.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector
			refract (const Vector & incident, const Vector & normal, float eta) noexcept
			{
				const auto d = Vector::dotProduct(normal, incident);

				const auto k = 1.0 - eta * eta * (1.0 - d * d);

				if ( k < 0.0 )
				{
					return {};
				}

				return eta * incident - (eta * d + std::sqrt(k)) * normal;
			}

			/**
			 * @brief Returns the normal vector of a plane defined by two vectors.
			 * @param lhs A reference to a Vector.
			 * @param rhs A reference to a Vector.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector
			normal (const Vector & lhs, const Vector & rhs) noexcept
			{
				return Vector::crossProduct(lhs, rhs).normalize();
			}

			/**
			 * @brief Gets the normal vector from a triangle defined by three points.
			 * @note Gives points in counter clock wise order !
			 * @param pointA Vertex A position of the triangle.
			 * @param pointB Vertex B position of the triangle.
			 * @param pointC Vertex C position of the triangle.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector
			normal (const Vector & pointA, const Vector & pointB, const Vector & pointC) noexcept
			{
				return Vector::crossProduct(pointA - pointB, pointB - pointC).normalize();
			}

			/**
			 * @brief Gets the tangent vector from a triangle defined by three points and three texture coordinates.
			 * @note Gives points in counter clock wise order !
			 * @param pointA Vertex A position of the triangle.
			 * @param uvA Vertex A texture coordinates of the triangle.
			 * @param pointB Vertex B position of the triangle.
			 * @param uvB Vertex B texture coordinates of the triangle.
			 * @param pointC Vertex C position of the triangle.
			 * @param uvC Vertex C texture coordinates of the triangle.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector
			tangent (const Vector & pointA, const Vector< 2, data_t > & uvA, const Vector & pointB, const Vector< 2, data_t > & uvB, const Vector & pointC, const Vector< 2, data_t > & uvC) noexcept
			{
				const auto tmpA = (pointA - pointB) * (uvC - uvB)[Y];
				const auto tmpB = (pointB - pointC) * (uvB - uvA)[Y];

				return (tmpA - tmpB).normalize();
			}

			/**
			 * @brief Gets the perpendicular vector.
			 * @return Vector
			 */
			[[nodiscard]]
			Vector
			perpendicular () const noexcept
			{
				if ( std::abs(m_data[X]) > std::abs(m_data[Z]) )
				{
					return Vector{-m_data[Y], m_data[X], 0}.normalize();
				}

				return Vector{0, -m_data[Z], m_data[Y]}.normalize();
			}

			/**
			 * @brief Gets the mid point.
			 * @param lhs Left-handed side vector.
			 * @param rhs Right-handed side vector.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector
			midPoint (const Vector & lhs, const Vector & rhs) noexcept
			{
				return {
					(lhs.m_data[X] + rhs.m_data[X]) * 0.5F,
					(lhs.m_data[Y] + rhs.m_data[Y]) * 0.5F,
					(lhs.m_data[Z] + rhs.m_data[Z]) * 0.5F
				};
			}

			/**
			 * @brief Checks if vector is null.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isNull () const noexcept
			{
				return std::all_of(m_data.cbegin(), m_data.cend(), [] (const auto & value) {
					return Utility::isZero(value);
				});
			}

			/**
			 * @brief Checks if vector is 1 for every comp.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isOne () const noexcept
			{
				return std::all_of(m_data.cbegin(), m_data.cend(), [] (const auto & value) {
					return value == 1.0F;
				});
			}

			/**
			 * @brief Returns a vector that is made from the largest components of two vectors.
			 * @param a first vector.
			 * @param b second vector.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector
			min (const Vector & a, const Vector & b) noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = std::min(a[index], b[index]);
				}

				return vector;
			}

			/**
			 * @brief Returns a vector that is made from the smallest components of two vectors.
			 * @param a first vector.
			 * @param b second vector.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector
			max (const Vector & a, const Vector & b) noexcept
			{
				Vector vector{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector.m_data[index] = std::max(a[index], b[index]);
				}

				return vector;
			}

			/**
			 * @brief Swaps axis.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			void
			swapAxis () noexcept
			{
				std::swap(m_data[X], m_data[Y]);
			}

			/**
			 * @brief Converts a vector to a vector of 2 values.
			 * @return Vector
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			Vector< 2, data_t >
			toVector2 () const noexcept
			{
				return {m_data[X], m_data[Y]};
			}

			/**
			 * @brief Converts a vector to a vector of 3 values.
			 * @return Vector
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2 || N == 4, bool > = false >
			[[nodiscard]]
			Vector< 3, data_t >
			toVector3 () const noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {m_data[X], m_data[Y], 0};
				}

				if constexpr ( dim_t == 4 )
				{
					return {m_data[X], m_data[Y], m_data[Z]};
				}
			}

			/**
			 * @brief Converts a vector to a vector of 4 values.
			 * @return Vector
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2 || N == 3, bool > = false >
			[[nodiscard]]
			Vector< 4, data_t >
			toVector4 () const noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {m_data[X], m_data[Y], 0, 0};
				}

				if constexpr ( dim_t == 3 )
				{
					return {m_data[X], m_data[Y], m_data[Z], 0};
				}
			}

			/**
			 * @brief Copies the vector data inside a C-Array of data_t.
			 * @warning  The target must provide enough space.
			 * @param target Where to copy vector data.
			 */
			void
			copy (data_t * target) const noexcept
			{
				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					target[index] = m_data[index]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
				}
			}

			/**
			 * @brief Vector constant at origin.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			constexpr
			Vector
			origin () noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {0, 0};
				}

				if constexpr ( dim_t == 3 )
				{
					return {0, 0, 0};
				}

				if constexpr ( dim_t == 4 )
				{
					return {0, 0, 0, 1};
				}
			}

			/**
			 * @brief Vector constant pointing toward positive X axis.
			 * @note In world space, this point to the right.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			constexpr
			Vector
			positiveX () noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {1, 0};
				}

				if constexpr ( dim_t == 3 )
				{
					return {1, 0, 0};
				}

				if constexpr ( dim_t == 4 )
				{
					return {1, 0, 0, 0};
				}
			}

			/**
			 * @brief Vector constant pointing toward negative X axis.
			 * @note In world space, this point to the left.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			constexpr
			Vector
			negativeX () noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {-1, 0};
				}

				if constexpr ( dim_t == 3 )
				{
					return {-1, 0, 0};
				}

				if constexpr ( dim_t == 4 )
				{
					return {-1, 0, 0, 0};
				}
			}

			/**
			 * @brief Vector constant pointing toward positive Y axis.
			 * @note In world space, this point to bottom.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			constexpr
			Vector
			positiveY () noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {0, 1};
				}

				if constexpr ( dim_t == 3 )
				{
					return {0, 1, 0};
				}

				if constexpr ( dim_t == 4 )
				{
					return {0, 1, 0, 0};
				}
			}

			/**
			 * @brief Vector constant pointing toward negative Y axis.
			 * @note In world space, this point to top.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			constexpr
			Vector
			negativeY () noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {0, -1};
				}

				if constexpr ( dim_t == 3 )
				{
					return {0, -1, 0};
				}

				if constexpr ( dim_t == 4 )
				{
					return {0, -1, 0, 0};
				}
			}

			/**
			 * @brief Vector constant pointing toward positive Z axis.
			 * @note In world space, this point to the user which looks the screen.
			 * @return Vector
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			static
			constexpr
			Vector
			positiveZ () noexcept
			{
				if constexpr ( dim_t == 3 )
				{
					return {0, 0, 1};
				}

				if constexpr ( dim_t == 4 )
				{
					return {0, 0, 1, 0};
				}
			}

			/**
			 * @brief Vector constant pointing toward negative Z axis.
			 * @note In world space, this point into the screen.
			 * @return Vector
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			static
			constexpr
			Vector
			negativeZ () noexcept
			{
				if constexpr ( dim_t == 3 )
				{
					return {0, 0, -1};
				}

				if constexpr ( dim_t == 4 )
				{
					return {0, 0, -1, 0};
				}
			}

			/**
			 * @brief Returns a random vector.
			 * @param min The minimum value.
			 * @param max The maximum value.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector
			random (data_t min, data_t max) noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {Utility::random(min, max), Utility::random(min, max)};
				}

				if constexpr ( dim_t == 3 )
				{
					return {Utility::random(min, max), Utility::random(min, max), Utility::random(min, max)};
				}

				if constexpr ( dim_t == 4 )
				{
					return {Utility::random(min, max), Utility::random(min, max), Utility::random(min, max), 0};
				}
			}

			/**
			 * @brief Returns a random vector.
			 * @param min The minimum value.
			 * @param max The maximum value.
			 * @return Vector
			 */
			[[nodiscard]]
			static
			Vector
			trueRandom (data_t min, data_t max) noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {Utility::trueRandom(min, max), Utility::trueRandom(min, max)};
				}

				if constexpr ( dim_t == 3 )
				{
					return {Utility::trueRandom(min, max), Utility::trueRandom(min, max), Utility::trueRandom(min, max)};
				}

				if constexpr ( dim_t == 4 )
				{
					return {Utility::trueRandom(min, max), Utility::trueRandom(min, max), Utility::trueRandom(min, max), 0};
				}
			}

			/**
			 * @brief Performs a quadratic Bezier interpolation between 3 points.
			 * @param a The first point.
			 * @param b The second point.
			 * @param c The third point.
			 * @param mu The factor between 0 and 1.
			 * @return Vector
			 */
			static
			Vector
			quadraticBezierInterpolation (const Vector & a, const Vector & b, const Vector & c, data_t mu) noexcept
			{
				return linearInterpolation(
					linearInterpolation(a, b, mu),
					linearInterpolation(b, c, mu),
					mu
				);
			}

			/**
			 * @brief Performs a cubic Bezier interpolation between 4 points.
			 * @param a The first point.
			 * @param b The second point.
			 * @param c The third point.
			 * @param d The fourth point.
			 * @param mu The factor between 0 and 1.
			 * @return data_t
			 */
			static
			Vector
			cubicBezierInterpolation (const Vector & a, const Vector & b, const Vector & c, const Vector & d, data_t mu) noexcept
			{
				return linearInterpolation(
					quadraticBezierInterpolation(a, b, d, mu),
					quadraticBezierInterpolation(a, c, d, mu),
					mu
				);
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Vector & obj)
			{
				using namespace std;

				if constexpr ( dim_t == 2 )
				{
					return out << "Vector2(" << fixed << setprecision(8) << '[' << setw(16) << obj.m_data[X] << ", " << setw(16) << obj.m_data[Y] << ')';
				}

				if constexpr ( dim_t == 3 )
				{
					return out << "Vector3(" << fixed << setprecision(8) << '[' << setw(16) << obj.m_data[X] << ", " << setw(16) << obj.m_data[Y] << ", " << setw(16) << obj.m_data[Z] << ')';
				}

				if constexpr ( dim_t == 4 )
				{
					return out << "Vector4(" << fixed << setprecision(8) << '[' << setw(16) << obj.m_data[X] << ", " << setw(16) << obj.m_data[Y] << ", " << setw(16) << obj.m_data[Z] << ", " << setw(16) << obj.m_data[W] << ')';
				}
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend
			std::string
			to_string (const Vector & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			std::array< data_t, dim_t > m_data{};
	};

	using Vector2f = Vector< 2UL, float >;
	using Vector3f = Vector< 3UL, float >;
	using Vector4f = Vector< 4UL, float >;

	using Vector2d = Vector< 2UL, double >;
	using Vector3d = Vector< 3UL, double >;
	using Vector4d = Vector< 4UL, double >;

	// NOLINTEND(readability-identifier-length, *-magic-numbers)
}
