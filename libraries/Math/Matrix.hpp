/*
 * Libraries/Math/Matrix.hpp
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
#include <array>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

/* Local inclusions for usages. */
#include "Base.hpp" // fastCotan()
#include "Vector.hpp"

namespace Libraries::Math
{
	// NOLINTBEGIN(readability-identifier-length, *-magic-numbers)

	/* Matrix 2x2 column major indexes */
	constexpr auto M2x2Col0Row0 = 0;
	constexpr auto M2x2Col0Row1 = 1;
	constexpr auto M2x2Col1Row0 = 2;
	constexpr auto M2x2Col1Row1 = 3;

	/* Matrix 3x3 column major indexes */
	constexpr auto M3x3Col0Row0 = 0;
	constexpr auto M3x3Col0Row1 = 1;
	constexpr auto M3x3Col0Row2 = 2;
	constexpr auto M3x3Col1Row0 = 3;
	constexpr auto M3x3Col1Row1 = 4;
	constexpr auto M3x3Col1Row2 = 5;
	constexpr auto M3x3Col2Row0 = 6;
	constexpr auto M3x3Col2Row1 = 7;
	constexpr auto M3x3Col2Row2 = 8;

	/* Matrix 4x4 column major indexes */
	constexpr auto M4x4Col0Row0 = 0;
	constexpr auto M4x4Col0Row1 = 1;
	constexpr auto M4x4Col0Row2 = 2;
	constexpr auto M4x4Col0Row3 = 3;
	constexpr auto M4x4Col1Row0 = 4;
	constexpr auto M4x4Col1Row1 = 5;
	constexpr auto M4x4Col1Row2 = 6;
	constexpr auto M4x4Col1Row3 = 7;
	constexpr auto M4x4Col2Row0 = 8;
	constexpr auto M4x4Col2Row1 = 9;
	constexpr auto M4x4Col2Row2 = 10;
	constexpr auto M4x4Col2Row3 = 11;
	constexpr auto M4x4Col3Row0 = 12;
	constexpr auto M4x4Col3Row1 = 13;
	constexpr auto M4x4Col3Row2 = 14;
	constexpr auto M4x4Col3Row3 = 15;

	/* Matrix 2x2 row major indexes */
	constexpr auto M2x2Row0Col0 = 0;
	constexpr auto M2x2Row0Col1 = 2;
	constexpr auto M2x2Row1Col0 = 1;
	constexpr auto M2x2Row1Col1 = 3;

	/* Matrix 3x3 row major indexes */
	constexpr auto M3x3Row0Col0 = 0;
	constexpr auto M3x3Row0Col1 = 3;
	constexpr auto M3x3Row0Col2 = 6;
	constexpr auto M3x3Row1Col0 = 1;
	constexpr auto M3x3Row1Col1 = 4;
	constexpr auto M3x3Row1Col2 = 7;
	constexpr auto M3x3Row2Col0 = 2;
	constexpr auto M3x3Row2Col1 = 5;
	constexpr auto M3x3Row2Col2 = 8;

	/* Matrix 4x4 row major indexes */
	constexpr auto M4x4Row0Col0 = 0;
	constexpr auto M4x4Row0Col1 = 4;
	constexpr auto M4x4Row0Col2 = 8;
	constexpr auto M4x4Row0Col3 = 12;
	constexpr auto M4x4Row1Col0 = 1;
	constexpr auto M4x4Row1Col1 = 5;
	constexpr auto M4x4Row1Col2 = 9;
	constexpr auto M4x4Row1Col3 = 13;
	constexpr auto M4x4Row2Col0 = 2;
	constexpr auto M4x4Row2Col1 = 6;
	constexpr auto M4x4Row2Col2 = 10;
	constexpr auto M4x4Row2Col3 = 14;
	constexpr auto M4x4Row3Col0 = 3;
	constexpr auto M4x4Row3Col1 = 7;
	constexpr auto M4x4Row3Col2 = 11;
	constexpr auto M4x4Row3Col3 = 15;

	/**
	 * @brief Column Major matrix.
	 * @tparam dim_t The dimension of the vector. This can be 2, 3 or 4.
	 * @tparam data_t The type for the vector data. Default float.
	 * @note
	 *	Matrix 2x2 memory layout (column major)
	 *		[0][2]
	 *		[1][3]
	 *
	 *	Matrix 3x3 memory layout (column major)
	 *		[0][3][6]
	 *		[1][4][7]
	 *		[2][5][8]
	 *
	 *	Matrix 4x4 memory layout (column major)
	 *		[ 0][ 4][ 8][12]
	 *		[ 1][ 5][ 9][13]
	 *		[ 2][ 6][10][14]
	 *		[ 3][ 7][11][15]
	 *
	 *		Column 0 is for X axis vector
	 *		Column 1 is for Y axis vector
	 *		Column 2 is for Z axis vector
	 *		Column 3 is for position point
	 *
	 *		Object Coordinates * Model Matrix -> World Coordinates
	 *		World Coordinates * View Matrix -> Eye Coordinates
	 *		Eye Coordinates * Projection Matrix -> Clip Coordinates
	 */
	template<
		std::size_t dim_t,
		typename data_t = float,
		std::enable_if_t< dim_t == 2 || dim_t == 3 || dim_t == 4, bool > = false,
		std::enable_if_t< std::is_arithmetic_v< data_t >, bool > = false
	>
	class Matrix final
	{
		public:

			/**
			 * @brief Constructs a default matrix to identity.
			 */
			constexpr
			Matrix () noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					m_data[0] = 1;
					m_data[3] = 1;
				}

				if constexpr ( dim_t == 3 )
				{
					m_data[0] = 1;
					m_data[4] = 1;
					m_data[8] = 1;
				}

				if constexpr ( dim_t == 4 )
				{
					m_data[0] = 1;
					m_data[5] = 1;
					m_data[10] = 1;
					m_data[15] = 1;
				}
			}

			/**
			 * @brief Constructs a matrix 2x2 from vectors as columns.
			 * @param column0 A reference to a vector< 2, data_t > for the first column.
			 * @param column1 A reference to a vector< 2, data_t > for the second column.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			constexpr
			Matrix (const Vector< dim_t, data_t > & column0, const Vector< dim_t, data_t > & column1) noexcept
				: m_data{
					column0[X], column0[Y],
					column1[X], column1[Y]}
			{

			}

			/**
			 * @brief Constructs a matrix 3x3 from vectors as columns.
			 * @param column0 A reference to a vector< 3, data_t > for the first column.
			 * @param column1 A reference to a vector< 3, data_t > for the second column.
			 * @param column2 A reference to a vector< 3, data_t > for the third column.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3, bool > = false >
			constexpr
			Matrix (const Vector< dim_t, data_t > & column0, const Vector< dim_t, data_t > & column1, const Vector< dim_t, data_t > & column2) noexcept
				: m_data{
					column0[X], column0[Y], column0[Z],
					column1[X], column1[Y], column1[Z],
					column2[X], column2[Y], column2[Z]}
			{

			}

			/**
			 * @brief Constructs a matrix 4x4 from vectors as columns.
			 * @param column0 A reference to a vector< 4, data_t > for the first column.
			 * @param column1 A reference to a vector< 4, data_t > for the second column.
			 * @param column2 A reference to a vector< 4, data_t > for the third column.
			 * @param column3 A reference to a vector< 4, data_t > for the fourth column.
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			constexpr
			Matrix (const Vector< dim_t, data_t > & column0, const Vector< dim_t, data_t > & column1, const Vector< dim_t, data_t > & column2, const Vector< dim_t, data_t > & column3) noexcept
				: m_data{
					column0[X], column0[Y], column0[Z], column0[W],
					column1[X], column1[Y], column1[Z], column1[W],
					column2[X], column2[Y], column2[Z], column2[W],
					column3[X], column3[Y], column3[Z], column3[W]}
			{

			}

			/**
			 * @brief Constructs a matrix from STL array.
			 * @param data A array of dim_t * dim_t value.
			 * @todo Adding explicit keyword makes Matrix::noTranslation() bug !
			 */
			constexpr
			Matrix (const std::array< data_t, dim_t * dim_t > & data) noexcept
				: m_data{data}
			{

			}

			/**
			 * @brief Constructs a matrix from C-Style array.
			 * @warning Unsafe !
			 * @param data A pointer to a C-Style array containing at least the dimension of the matrix.
			 */
			explicit
			Matrix (const data_t * data) noexcept
			{
				#pragma omp simd
				for ( size_t index = 0; index < dim_t * dim_t; index++ )
				{
					m_data[index] = data[index]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
				}
			}

			/**
			 * @brief Returns a copy of the matrix.
			 * @return Matrix
			 */
			[[nodiscard]]
			Matrix
			operator+ () const noexcept
			{
				return *this;
			}

			/**
			 * @brief Returns the inverse copy of the matrix.
			 * @return Matrix
			 */
			[[nodiscard]]
			Matrix
			operator- () const noexcept
			{
				Matrix matrix{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					matrix.m_data[index] = -m_data[index];
				}

				return matrix;
			}

			/**
			 * @brief Data accessor.
			 * @param index The index of matrix element.
			 * @return data_t &
			 */
			data_t &
			operator[] (size_t index) noexcept
			{
				return m_data[index];
			}

			/**
			 * @brief Data accessor (const version).
			 * @param index The index of matrix element.
			 * @return const data_t &
			 */
			[[nodiscard]]
			const data_t &
			operator[] (size_t index) const noexcept
			{
				return m_data[index];
			}

			/**
			 * @brief Overloads the equality operator.
			 * @param operand A reference to an other matrix.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator== (const Matrix & operand) const noexcept
			{
				if ( this != &operand )
				{
					for ( size_t index = 0; index < dim_t * dim_t; index++ )
					{
						if ( Utility::different(m_data[index], operand.m_data[index]) )
						{
							return false;
						}
					}
				}

				return true;
			}

			/**
			 * @brief Overloads the inequality operator.
			 * @param operand A reference to an other matrix.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			operator!= (const Matrix & operand) const noexcept
			{
				return !this->operator==(operand);
			}

			/**
			 * @brief Overloads the addition operator.
			 * @param operand A reference to an other matrix.
			 * @return Matrix
			 */
			[[nodiscard]]
			Matrix
			operator+ (const Matrix & operand) const noexcept
			{
				Matrix matrix{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t * dim_t; index++ )
				{
					matrix[index] = m_data[index] + operand.m_data[index];
				}

				return matrix;
			}

			/**
			 * @brief Overloads the addition and assign operator.
			 * @param operand A reference to an other matrix.
			 * @return Matrix
			 */
			Matrix &
			operator+= (const Matrix & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					#pragma omp simd
					for ( size_t index = 0; index < dim_t * dim_t; index++ )
					{
						m_data[index] += operand.m_data[index];
					}
				}

				return *this;
			}

			/**
			 * @brief Overloads the subtract operator.
			 * @param operand A reference to an other matrix.
			 * @return Matrix
			 */
			[[nodiscard]]
			Matrix
			operator- (const Matrix & operand) const noexcept
			{
				Matrix matrix{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t * dim_t; index++ )
				{
					matrix[index] = m_data[index] - operand.m_data[index];
				}

				return matrix;
			}

			/**
			 * @brief Overloads the subtract and assign operator.
			 * @param operand A reference to an other matrix.
			 * @return Matrix
			 */
			Matrix &
			operator-= (const Matrix & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					#pragma omp simd
					for ( size_t index = 0; index < dim_t * dim_t; index++ )
					{
						m_data[index] -= operand.m_data[index];
					}
				}

				return *this;
			}

			/**
			 * @brief Overloads the multiply operator.
			 * @param operand A reference to an other matrix.
			 * @return Matrix
			 */
			[[nodiscard]]
			Matrix
			operator* (const Matrix & operand) const noexcept
			{
				Matrix matrix{};

				#pragma omp simd
				for ( size_t columnIndex = 0; columnIndex < dim_t; columnIndex++ )
				{
					for ( size_t rowIndex = 0; rowIndex < dim_t; rowIndex++ )
					{
						const size_t index = (columnIndex * dim_t) + rowIndex;

						matrix[index] = 0;

						for ( size_t i = 0; i < dim_t; i++ )
						{
							matrix[index] += (m_data[(i * dim_t) + rowIndex] * operand.m_data[(columnIndex * dim_t) + i]);
						}
					}
				}

				return matrix;
			}

			/**
			 * @brief Overloads the multiply and assign operator.
			 * @param operand A reference to an other matrix.
			 * @return Matrix
			 */
			Matrix &
			operator*= (const Matrix & operand) noexcept
			{
				/* Guard self assignment */
				if ( this != &operand )
				{
					*this = *this * operand;
				}

				return *this;
			}

			/**
			 * @brief Overloads the multiply operator.
			 * @param operand A value.
			 * @return Matrix
			 */
			[[nodiscard]]
			Matrix
			operator* (data_t operand) const noexcept
			{
				Matrix matrix{};

				#pragma omp simd
				for ( size_t index = 0; index < dim_t * dim_t; index++ )
				{
					matrix.m_data[index] = m_data[index] * operand;
				}

				return matrix;
			}

			/**
			 * @brief Overloads the multiply and assign operator.
			 * @param operand A value.
			 * @return Matrix
			 */
			Matrix &
			operator*= (data_t operand) noexcept
			{
				#pragma omp simd
				for ( size_t index = 0; index < dim_t * dim_t; index++ )
				{
					m_data[index] *= operand;
				}

				return *this;
			}

			/**
			 * @brief Overloads the multiply operator.
			 * @param operand A reference to a vector.
			 * @return Vector< dim_t, data_t >
			 */
			[[nodiscard]]
			Vector< dim_t, data_t >
			operator* (const Vector< dim_t, data_t > & operand) const noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {
						(operand[X] * m_data[M2x2Col0Row0]) + (operand[Y] * m_data[M2x2Col1Row0]),
						(operand[X] * m_data[M2x2Col0Row1]) + (operand[Y] * m_data[M2x2Col1Row1])
					};
				}

				if constexpr ( dim_t == 3 )
				{
					return {
						(operand[X] * m_data[M3x3Col0Row0]) + (operand[Y] * m_data[M3x3Col1Row0]) + (operand[Z] * m_data[M3x3Col2Row0]),
						(operand[X] * m_data[M3x3Col0Row1]) + (operand[Y] * m_data[M3x3Col1Row1]) + (operand[Z] * m_data[M3x3Col2Row1]),
						(operand[X] * m_data[M3x3Col0Row2]) + (operand[Y] * m_data[M3x3Col1Row2]) + (operand[Z] * m_data[M3x3Col2Row2])
					};
				}

				if constexpr ( dim_t == 4 )
				{
					return {
						(operand[X] * m_data[M4x4Col0Row0]) + (operand[Y] * m_data[M4x4Col1Row0]) + (operand[Z] * m_data[M4x4Col2Row0]) + (operand[W] * m_data[M4x4Col3Row0]),
						(operand[X] * m_data[M4x4Col0Row1]) + (operand[Y] * m_data[M4x4Col1Row1]) + (operand[Z] * m_data[M4x4Col2Row1]) + (operand[W] * m_data[M4x4Col3Row1]),
						(operand[X] * m_data[M4x4Col0Row2]) + (operand[Y] * m_data[M4x4Col1Row2]) + (operand[Z] * m_data[M4x4Col2Row2]) + (operand[W] * m_data[M4x4Col3Row2]),
						(operand[X] * m_data[M4x4Col0Row3]) + (operand[Y] * m_data[M4x4Col1Row3]) + (operand[Z] * m_data[M4x4Col2Row3]) + (operand[W] * m_data[M4x4Col3Row3])
					};
				}

				return {};
			}

			/**
			 * @brief Returns whether a matrix is equal.
			 * @param operand A reference to an other matrix.
			 * @param epsilon The floating point tolerance value. Default C++ epsilon.
			 * @return equal
			 */
			[[nodiscard]]
			bool
			equal (const Matrix & operand, data_t epsilon = std::numeric_limits< data_t >::epsilon()) const noexcept
			{
				if ( this != &operand )
				{
					for ( size_t index = 0; index < dim_t * dim_t; index++ )
					{
						if ( Utility::different(m_data[index], operand.m_data[index], epsilon) )
						{
							return false;
						}
					}
				}

				return true;
			}

			/**
			 * @brief Returns whether a matrix is different.
			 * @param operand A reference to an other matrix.
			 * @param epsilon The floating point tolerance value. Default C++ epsilon.
			 * @return equal
			 */
			[[nodiscard]]
			bool
			different (const Matrix & operand, data_t epsilon = std::numeric_limits< data_t >::epsilon()) const noexcept
			{
				return !this->equal(operand, epsilon);
			}

			/**
			 * @brief Returns whether two matrices are equal.
			 * @param a A reference to a matrix.
			 * @param b A reference to a matrix.
			 * @param epsilon The floating point tolerance value. Default C++ epsilon.
			 * @return equal
			 */
			[[nodiscard]]
			static
			bool
			equal (const Matrix & a, const Matrix & b, data_t epsilon = std::numeric_limits< data_t >::epsilon()) noexcept
			{
				if ( &a != &b )
				{
					for ( size_t index = 0; index < dim_t * dim_t; index++ )
					{
						if ( Utility::different(a.m_data[index], b.m_data[index], epsilon) )
						{
							return false;
						}
					}
				}

				return true;
			}

			/**
			 * @brief Returns whether two matrices are different.
			 * @param a A reference to a matrix.
			 * @param b A reference to a matrix.
			 * @param epsilon The floating point tolerance value. Default C++ epsilon.
			 * @return equal
			 */
			[[nodiscard]]
			static
			bool
			different (const Matrix & a, const Matrix & b, data_t epsilon = std::numeric_limits< data_t >::epsilon()) noexcept
			{
				return !Matrix::equal(a, b, epsilon);
			}

			/**
			 * @brief Resets matrix to identity.
			 * @return void
			 */
			void
			reset () noexcept
			{
				#pragma omp simd
				for ( size_t columnIndex = 0; columnIndex < dim_t; columnIndex++ )
				{
					for ( size_t rowIndex = 0; rowIndex < dim_t; rowIndex++ )
					{
						m_data[(columnIndex * dim_t) + rowIndex] = columnIndex == rowIndex ? 1 : 0;
					}
				}
			}

			/**
			 * @brief Returns whether the matrix is identity.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isIdentity () const noexcept // NOLINT(readability-function-cognitive-complexity)
			{
				if constexpr ( dim_t == 2 )
				{
					if ( Utility::different(m_data[0], static_cast< data_t >(1)) )
					{
						return false;
					}

					if ( Utility::different(m_data[1], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[2], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[3], static_cast< data_t >(1)) )
					{
						return false;
					}
				}

				if constexpr ( dim_t == 3 )
				{
					if ( Utility::different(m_data[0], static_cast< data_t >(1)) )
					{
						return false;
					}

					if ( Utility::different(m_data[1], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[2], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[3], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[4], static_cast< data_t >(1)) )
					{
						return false;
					}

					if ( Utility::different(m_data[5], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[6], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[7], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[8], static_cast< data_t >(1)) )
					{
						return false;
					}
				}

				if constexpr ( dim_t == 4 )
				{
					if ( Utility::different(m_data[0], static_cast< data_t >(1)) )
					{
						return false;
					}

					if ( Utility::different(m_data[1], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[2], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[3], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[4], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[5], static_cast< data_t >(1)) )
					{
						return false;
					}

					if ( Utility::different(m_data[6], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[7], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[8], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[9], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[10], static_cast< data_t >(1)) )
					{
						return false;
					}

					if ( Utility::different(m_data[11], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[12], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[13], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[14], static_cast< data_t >(0)) )
					{
						return false;
					}

					if ( Utility::different(m_data[15], static_cast< data_t >(1)) )
					{
						return false;
					}
				}

				return true;
			}

			/**
			 * @brief Returns the matrix data as a C array.
			 * @return data_t *
			 */
			[[nodiscard]]
			data_t *
			data () noexcept
			{
				return m_data.data();
			}

			/**
			 * @brief Return the matrix data as a C array.
			 * @return const data_t *
			 */
			[[nodiscard]]
			const data_t *
			data () const noexcept
			{
				return m_data.data();
			}

			/**
			 * @brief Sets values to a matrix row.
			 * @tparam N The size must be 2.
			 * @param row The index of the row.
			 * @param x The first value.
			 * @param y The second value.
			 * @return void
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			void
			setRow (size_t row, data_t x, data_t y) noexcept
			{
				if ( row > dim_t )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", matrix row dimension overflow !" << std::endl;

					return;
				}

				m_data[row] = x;
				m_data[row + dim_t] = y;
			}

			/**
			 * @brief Sets values to a matrix row.
			 * @tparam N The size must be 3.
			 * @param row The index of the row.
			 * @param x The first value.
			 * @param y The second value.
			 * @param y The third value.
			 * @return void
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3, bool > = false >
			void
			setRow (size_t row, data_t x, data_t y, data_t z) noexcept
			{
				if ( row > dim_t )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", matrix row dimension overflow !" << std::endl;

					return;
				}

				m_data[row] = x;
				m_data[row + dim_t] = y;
				m_data[row + (2 * dim_t)] = z;
			}

			/**
			 * @brief Sets values to a matrix row.
			 * @tparam N The size must be 4.
			 * @param row The index of the row.
			 * @param x The first value.
			 * @param y The second value.
			 * @param y The third value.
			 * @param w The fourth value.
			 * @return void
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			void
			setRow (size_t row, data_t x, data_t y, data_t z, data_t w) noexcept
			{
				if ( row > dim_t )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", matrix row dimension overflow !" << std::endl;

					return;
				}

				m_data[row] = x;
				m_data[row + dim_t] = y;
				m_data[row + (2 * dim_t)] = z;
				m_data[row + (3 * dim_t)] = w;
			}

			/**
			 * @brief Sets values to a matrix row with a vector.
			 * @param row The index of the row.
			 * @param vector A reference to a vector.
			 * @return void
			 */
			void
			setRow (size_t row, const Vector< dim_t, data_t > & vector) noexcept
			{
				if ( row > dim_t )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", matrix row dimension overflow !" << std::endl;

					return;
				}

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					m_data[(index * dim_t) + row] = vector[index];
				}
			}

			/**
			 * @brief Returns a matrix row as a vector.
			 * @param row The index of the row.
			 * @return Vector< dim_t, data_t >
			 */
			[[nodiscard]]
			Vector< dim_t, data_t >
			row (size_t row) const noexcept
			{
				if ( row > dim_t )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", matrix row dimension overflow !" << std::endl;

					return {};
				}

				Vector< dim_t, data_t > vector;

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector[index] = m_data[(index * dim_t) + row];
				}

				return vector;
			}

			/**
			 * @brief Sets values to a matrix column.
			 * @tparam N The size must be 2.
			 * @param row The index of the row.
			 * @param x The first value.
			 * @param y The second value.
			 * @return void
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			void
			setColumn (size_t col, data_t x, data_t y) noexcept
			{
				if ( col > dim_t )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", matrix column dimension overflow !" << std::endl;

					return;
				}

				const auto shift = dim_t * col;

				m_data[shift] = x;
				m_data[shift + 1] = y;
			}

			/**
			 * @brief Sets values to a matrix column.
			 * @tparam N The size must be 3.
			 * @param row The index of the row.
			 * @param x The first value.
			 * @param y The second value.
			 * @param y The third value.
			 * @return void
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3, bool > = false >
			void
			setColumn (size_t col, data_t x, data_t y, data_t z) noexcept
			{
				if ( col > dim_t )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", matrix column dimension overflow !" << std::endl;

					return;
				}

				const auto shift = dim_t * col;

				m_data[shift] = x;
				m_data[shift + 1] = y;
				m_data[shift + 2] = z;
			}

			/**
			 * @brief Sets values to a matrix column.
			 * @tparam N The size must be 4.
			 * @param row The index of the row.
			 * @param x The first value.
			 * @param y The second value.
			 * @param y The third value.
			 * @param w The fourth value.
			 * @return void
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			void
			setColumn (size_t col, data_t x, data_t y, data_t z, data_t w) noexcept
			{
				if ( col > dim_t )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", matrix column dimension overflow !" << std::endl;

					return;
				}

				const auto shift = dim_t * col;

				m_data[shift] = x;
				m_data[shift + 1] = y;
				m_data[shift + 2] = z;
				m_data[shift + 3] = w;
			}

			/**
			 * @brief Sets a matrix column from a vector.
			 * @param columnIndex The index of the column.
			 * @param vector A reference to a vector.
			 * @return void
			 */
			void
			setColumn (size_t columnIndex, const Vector< dim_t, data_t > & vector) noexcept
			{
				if ( columnIndex > dim_t )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", matrix column dimension overflow !" << std::endl;

					return;
				}

				const auto shift = dim_t * columnIndex;

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					m_data[shift + index] = vector[index];
				}
			}

			/**
			 * @brief Returns a column as a vector.
			 * @param columnIndex The index of the column.
			 * @return Vector< dim_t, data_t >
			 */
			[[nodiscard]]
			Vector< dim_t, data_t >
			column (size_t columnIndex) const noexcept
			{
				if ( columnIndex > dim_t )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", matrix column dimension overflow !" << std::endl;

					return {};
				}

				Vector< dim_t, data_t > vector;

				auto shift = dim_t * columnIndex;

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector[index] = m_data[shift + index];
				}

				return vector;
			}

			/**
			 * @brief Returns the X vector (X+) from a matrix.
			 * @return Vector< dim_t, data_t >
			 */
			[[nodiscard]]
			Vector< dim_t, data_t >
			XVector () const noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {m_data[M2x2Col0Row0], m_data[M2x2Col0Row1]};
				}

				if constexpr ( dim_t == 3 )
				{
					return {m_data[M3x3Col0Row0], m_data[M3x3Col0Row1], m_data[M3x3Col0Row2]};
				}

				if constexpr ( dim_t == 4 )
				{
					return {m_data[M4x4Col0Row0], m_data[M4x4Col0Row1], m_data[M4x4Col0Row2]};
				}

				return {};
			}

			/**
			 * @brief Returns the upward vector (Y+) from a matrix.
			 * @return Vector< dim_t, data_t >
			 */
			[[nodiscard]]
			Vector< dim_t, data_t >
			upwardVector () const noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return {m_data[M2x2Col1Row0], m_data[M2x2Col1Row1]};
				}

				if constexpr ( dim_t == 3 )
				{
					return {m_data[M3x3Col1Row0], m_data[M3x3Col1Row1], m_data[M3x3Col1Row2]};
				}

				if constexpr ( dim_t == 4 )
				{
					return {m_data[M4x4Col1Row0], m_data[M4x4Col1Row1], m_data[M4x4Col1Row2]};
				}

				return {};
			}

			/**
			 * @brief Returns the forward vector (Z+) from a matrix.
			 * @return Vector< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			Vector< dim_t, data_t >
			forwardVector () const noexcept
			{
				if constexpr ( dim_t == 3 )
				{
					return {m_data[M3x3Col2Row0], m_data[M3x3Col2Row1], m_data[M3x3Col2Row2]};
				}

				if constexpr ( dim_t == 4 )
				{
					return {m_data[M4x4Col2Row0], m_data[M4x4Col2Row1], m_data[M4x4Col2Row2]};
				}

				return {};
			}

			/**
			 * @brief Returns the position vector.
			 * @tparam N The size must be 4.
			 * @return Vector< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			[[nodiscard]]
			Vector< dim_t, data_t >
			position () const noexcept
			{
				return {m_data[M4x4Col3Row0], m_data[M4x4Col3Row1], m_data[M4x4Col3Row2]};
			}

			/**
			 * @brief Returns the scale vector.
			 * @return Vector< dim_t, data_t >
			 */
			[[nodiscard]]
			Vector< dim_t, data_t >
			scaleVector () const noexcept
			{
				Vector< dim_t, data_t > vector;

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					vector[index] = m_data[index + (index * dim_t)];
				}

				return vector;
			}

			/**
			 * @brief Returns the determinant of the matrix.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			determinant () const noexcept // NOLINT(readability-function-cognitive-complexity)
			{
				if constexpr ( dim_t == 2 )
				{
					return (m_data[M2x2Col0Row0] * m_data[M2x2Col1Row1]) - (m_data[M2x2Col1Row0] * m_data[M2x2Col0Row1]);
				}

				if constexpr ( dim_t == 3 || dim_t == 4 )
				{
					data_t determinantValue = 0;

					/* FIXME: GCC crash 6-dec-2020 with "Matrix< data_t, dim_t - 1 > subMatrix;" */
					//#pragma omp simd
					for ( size_t index = 0; index < dim_t; index++ )
					{
						const auto value = m_data[index * dim_t];

						if ( Utility::isZero(value) )
						{
							continue;
						}

						/* Creates a sub matrix. */
						Matrix< dim_t - 1, data_t > subMatrix;

						for ( size_t dstCol = 0; dstCol < dim_t; dstCol++ )
						{
							/* Skip the current column.  */
							if ( index != dstCol )
							{
								const auto columnIndex = dstCol > index ? dstCol - 1 : dstCol;
								const auto columnVector = this->column(dstCol);

								if constexpr ( dim_t == 3 )
								{
									subMatrix.setColumn(columnIndex, {columnVector[Y], columnVector[Z]});
								}

								if constexpr ( dim_t == 4 )
								{
									subMatrix.setColumn(columnIndex, {columnVector[Y], columnVector[Z], columnVector[W]});
								}
							}
						}

						/* Gets determinant from sub matrix. */
						if ( index % 2 == 0 )
						{
							determinantValue += value * subMatrix.determinant();
						}
						else
						{
							determinantValue -= value * subMatrix.determinant();
						}
					}

					return determinantValue;
				}
			}

			/**
			 * @brief Returns the determinant of the matrix. Fast version.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			fastDeterminant () const noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return (m_data[M2x2Col0Row0] * m_data[M2x2Col1Row1]) - (m_data[M2x2Col1Row0] * m_data[M2x2Col0Row1]);
				}

				if constexpr ( dim_t == 3 )
				{
					return
						(m_data[M3x3Col0Row0] * m_data[M3x3Col1Row1] * m_data[M3x3Col2Row2]) +
						(m_data[M3x3Col1Row0] * m_data[M3x3Col2Row1] * m_data[M3x3Col0Row2]) +
						(m_data[M3x3Col2Row0] * m_data[M3x3Col0Row1] * m_data[M3x3Col1Row2]) -
						(m_data[M3x3Col0Row0] * m_data[M3x3Col2Row1] * m_data[M3x3Col1Row2]) -
						(m_data[M3x3Col1Row0] * m_data[M3x3Col0Row1] * m_data[M3x3Col2Row2]) -
						(m_data[M3x3Col2Row0] * m_data[M3x3Col1Row1] * m_data[M3x3Col0Row2]);
				}

				if constexpr ( dim_t == 4 )
				{
					return
						m_data[M4x4Col3Row0] * m_data[M4x4Col2Row1] * m_data[M4x4Col1Row2] * m_data[M4x4Col0Row3] - m_data[M4x4Col2Row0] * m_data[M4x4Col3Row1] * m_data[M4x4Col1Row2] * m_data[M4x4Col0Row3] -
						m_data[M4x4Col3Row0] * m_data[M4x4Col1Row1] * m_data[M4x4Col2Row2] * m_data[M4x4Col0Row3] + m_data[M4x4Col1Row0] * m_data[M4x4Col3Row1] * m_data[M4x4Col2Row2] * m_data[M4x4Col0Row3] +
						m_data[M4x4Col2Row0] * m_data[M4x4Col1Row1] * m_data[M4x4Col3Row2] * m_data[M4x4Col0Row3] - m_data[M4x4Col1Row0] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row2] * m_data[M4x4Col0Row3] -
						m_data[M4x4Col3Row0] * m_data[M4x4Col2Row1] * m_data[M4x4Col0Row2] * m_data[M4x4Col1Row3] + m_data[M4x4Col2Row0] * m_data[M4x4Col3Row1] * m_data[M4x4Col0Row2] * m_data[M4x4Col1Row3] +
						m_data[M4x4Col3Row0] * m_data[M4x4Col0Row1] * m_data[M4x4Col2Row2] * m_data[M4x4Col1Row3] - m_data[M4x4Col0Row0] * m_data[M4x4Col3Row1] * m_data[M4x4Col2Row2] * m_data[M4x4Col1Row3] -
						m_data[M4x4Col2Row0] * m_data[M4x4Col0Row1] * m_data[M4x4Col3Row2] * m_data[M4x4Col1Row3] + m_data[M4x4Col0Row0] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row2] * m_data[M4x4Col1Row3] +
						m_data[M4x4Col3Row0] * m_data[M4x4Col1Row1] * m_data[M4x4Col0Row2] * m_data[M4x4Col2Row3] - m_data[M4x4Col1Row0] * m_data[M4x4Col3Row1] * m_data[M4x4Col0Row2] * m_data[M4x4Col2Row3] -
						m_data[M4x4Col3Row0] * m_data[M4x4Col0Row1] * m_data[M4x4Col1Row2] * m_data[M4x4Col2Row3] + m_data[M4x4Col0Row0] * m_data[M4x4Col3Row1] * m_data[M4x4Col1Row2] * m_data[M4x4Col2Row3] +
						m_data[M4x4Col1Row0] * m_data[M4x4Col0Row1] * m_data[M4x4Col3Row2] * m_data[M4x4Col2Row3] - m_data[M4x4Col0Row0] * m_data[M4x4Col1Row1] * m_data[M4x4Col3Row2] * m_data[M4x4Col2Row3] -
						m_data[M4x4Col2Row0] * m_data[M4x4Col1Row1] * m_data[M4x4Col0Row2] * m_data[M4x4Col3Row3] + m_data[M4x4Col1Row0] * m_data[M4x4Col2Row1] * m_data[M4x4Col0Row2] * m_data[M4x4Col3Row3] +
						m_data[M4x4Col2Row0] * m_data[M4x4Col0Row1] * m_data[M4x4Col1Row2] * m_data[M4x4Col3Row3] - m_data[M4x4Col0Row0] * m_data[M4x4Col2Row1] * m_data[M4x4Col1Row2] * m_data[M4x4Col3Row3] -
						m_data[M4x4Col1Row0] * m_data[M4x4Col0Row1] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row3] + m_data[M4x4Col0Row0] * m_data[M4x4Col1Row1] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row3];
				}
			}

			/**
			 * @brief Returns the trace of the matrix.
			 * @return data_t
			 */
			[[nodiscard]]
			data_t
			trace () const noexcept
			{
				auto value = 0;

				#pragma omp simd
				for ( size_t index = 0; index < dim_t; index++ )
				{
					value += m_data[index + (index * dim_t)];
				}

				return value;
			}

			/**
			 * @brief Transposes the matrix.
			 * @return Matrix &
			 */
			Matrix &
			transpose () noexcept
			{
				if constexpr ( dim_t == 2  )
				{
					std::swap(m_data[M2x2Col0Row1], m_data[M2x2Col1Row0]);
				}

				if constexpr ( dim_t == 3  )
				{
					std::swap(m_data[M3x3Col0Row1], m_data[M3x3Col1Row0]);
					std::swap(m_data[M3x3Col0Row2], m_data[M3x3Col2Row0]);
					std::swap(m_data[M3x3Col1Row2], m_data[M3x3Col2Row1]);
				}

				if constexpr ( dim_t == 4  )
				{
					std::swap(m_data[M4x4Col0Row1], m_data[M4x4Col1Row0]);
					std::swap(m_data[M4x4Col0Row2], m_data[M4x4Col2Row0]);
					std::swap(m_data[M4x4Col1Row2], m_data[M4x4Col2Row1]);
					std::swap(m_data[M4x4Col0Row3], m_data[M4x4Col3Row0]);
					std::swap(m_data[M4x4Col1Row3], m_data[M4x4Col3Row1]);
					std::swap(m_data[M4x4Col2Row3], m_data[M4x4Col3Row2]);
				}

				return *this;
			}

			/**
			 * @brief Returns whether the matrix is reversible.
			 * @return bool
			 */
			[[nodiscard]]
			bool
			isInversible () const noexcept
			{
				return !Utility::isZero(this->determinant());
			}

			/**
			 * @brief Returns the inverse copy of the matrix.
			 * @return Matrix
			 */
			[[maybe_unused]]
			[[nodiscard]]
			Matrix
			inverseTEST () const noexcept
			{
				const auto D = this->determinant();

				if ( Utility::isZero(D) )
				{
					std::cerr << "Matrix:inverse() : this matrix (" << dim_t << ") is not inversible !" "\n";

					return *this;
				}

				//const auto invD = static_cast< data_t >(1) / D;

				Matrix inverseMatrix{};

				for ( size_t rowIndex = 0; rowIndex < dim_t; rowIndex++ )
				{
					for ( size_t columnIndex = 0; columnIndex < dim_t; columnIndex++ )
					{
						const auto index = (columnIndex * dim_t) + rowIndex;

						inverseMatrix[index] = index;

						//BUG
					}
				}

				return inverseMatrix;
			}

			/**
			 * @brief Returns the inverse copy of the matrix.
			 * @return Matrix
			 */
			[[nodiscard]]
			Matrix
			inverse () const noexcept
			{
				const auto D = this->determinant();

				if ( Utility::isZero(D) )
				{
					std::cerr << "Matrix:inverse() : this matrix (" << dim_t << ") is not inversible !" "<n";

					return *this;
				}

				const auto invD = static_cast< data_t >(1) / D;

				Matrix inverse;

				if constexpr ( dim_t == 2 )
				{
					inverse.m_data[M2x2Col0Row0] = m_data[M2x2Col1Row1] * invD;
					inverse.m_data[M2x2Col0Row1] = m_data[M2x2Col1Row0] * invD;

					inverse.m_data[M2x2Col1Row0] = m_data[M2x2Col0Row1] * invD;
					inverse.m_data[M2x2Col1Row1] = m_data[M2x2Col0Row0] * invD;
				}

				if constexpr ( dim_t == 3 )
				{
					inverse.m_data[M3x3Col0Row0] = (m_data[M3x3Col1Row1] * m_data[M3x3Col2Row2] - m_data[M3x3Col1Row2] * m_data[M3x3Col2Row1]) * invD;
					inverse.m_data[M3x3Col0Row1] = (m_data[M3x3Col0Row2] * m_data[M3x3Col2Row1] - m_data[M3x3Col0Row1] * m_data[M3x3Col2Row2]) * invD;
					inverse.m_data[M3x3Col0Row2] = (m_data[M3x3Col0Row1] * m_data[M3x3Col1Row2] - m_data[M3x3Col0Row2] * m_data[M3x3Col1Row1]) * invD;

					inverse.m_data[M3x3Col1Row0] = (m_data[M3x3Col1Row2] * m_data[M3x3Col2Row0] - m_data[M3x3Col1Row0] * m_data[M3x3Col2Row2]) * invD;
					inverse.m_data[M3x3Col1Row1] = (m_data[M3x3Col0Row0] * m_data[M3x3Col2Row2] - m_data[M3x3Col0Row2] * m_data[M3x3Col2Row0]) * invD;
					inverse.m_data[M3x3Col1Row2] = (m_data[M3x3Col0Row2] * m_data[M3x3Col1Row0] - m_data[M3x3Col0Row0] * m_data[M3x3Col1Row2]) * invD;

					inverse.m_data[M3x3Col2Row0] = (m_data[M3x3Col1Row0] * m_data[M3x3Col2Row1] - m_data[M3x3Col1Row1] * m_data[M3x3Col2Row0]) * invD;
					inverse.m_data[M3x3Col2Row1] = (m_data[M3x3Col0Row1] * m_data[M3x3Col2Row0] - m_data[M3x3Col0Row0] * m_data[M3x3Col2Row1]) * invD;
					inverse.m_data[M3x3Col2Row2] = (m_data[M3x3Col0Row0] * m_data[M3x3Col1Row1] - m_data[M3x3Col0Row1] * m_data[M3x3Col1Row0]) * invD;
				}

				if constexpr ( dim_t == 4 )
				{
					inverse.m_data[M4x4Col0Row0] = (m_data[M4x4Col1Row2] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row1] - m_data[M4x4Col1Row3] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row1] + m_data[M4x4Col1Row3] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row2] - m_data[M4x4Col1Row1] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row2] - m_data[M4x4Col1Row2] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row3] + m_data[M4x4Col1Row1] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row3]) * invD;
					inverse.m_data[M4x4Col0Row1] = (m_data[M4x4Col0Row3] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row1] - m_data[M4x4Col0Row2] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row1] - m_data[M4x4Col0Row3] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row2] + m_data[M4x4Col0Row1] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row2] + m_data[M4x4Col0Row2] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row3] - m_data[M4x4Col0Row1] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row3]) * invD;
					inverse.m_data[M4x4Col0Row2] = (m_data[M4x4Col0Row2] * m_data[M4x4Col1Row3] * m_data[M4x4Col3Row1] - m_data[M4x4Col0Row3] * m_data[M4x4Col1Row2] * m_data[M4x4Col3Row1] + m_data[M4x4Col0Row3] * m_data[M4x4Col1Row1] * m_data[M4x4Col3Row2] - m_data[M4x4Col0Row1] * m_data[M4x4Col1Row3] * m_data[M4x4Col3Row2] - m_data[M4x4Col0Row2] * m_data[M4x4Col1Row1] * m_data[M4x4Col3Row3] + m_data[M4x4Col0Row1] * m_data[M4x4Col1Row2] * m_data[M4x4Col3Row3]) * invD;
					inverse.m_data[M4x4Col0Row3] = (m_data[M4x4Col0Row3] * m_data[M4x4Col1Row2] * m_data[M4x4Col2Row1] - m_data[M4x4Col0Row2] * m_data[M4x4Col1Row3] * m_data[M4x4Col2Row1] - m_data[M4x4Col0Row3] * m_data[M4x4Col1Row1] * m_data[M4x4Col2Row2] + m_data[M4x4Col0Row1] * m_data[M4x4Col1Row3] * m_data[M4x4Col2Row2] + m_data[M4x4Col0Row2] * m_data[M4x4Col1Row1] * m_data[M4x4Col2Row3] - m_data[M4x4Col0Row1] * m_data[M4x4Col1Row2] * m_data[M4x4Col2Row3]) * invD;

					inverse.m_data[M4x4Col1Row0] = (m_data[M4x4Col1Row3] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row0] - m_data[M4x4Col1Row2] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row0] - m_data[M4x4Col1Row3] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row2] + m_data[M4x4Col1Row0] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row2] + m_data[M4x4Col1Row2] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row3] - m_data[M4x4Col1Row0] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row3]) * invD;
					inverse.m_data[M4x4Col1Row1] = (m_data[M4x4Col0Row2] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row0] - m_data[M4x4Col0Row3] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row0] + m_data[M4x4Col0Row3] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row2] - m_data[M4x4Col0Row0] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row2] - m_data[M4x4Col0Row2] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row3] + m_data[M4x4Col0Row0] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row3]) * invD;
					inverse.m_data[M4x4Col1Row2] = (m_data[M4x4Col0Row3] * m_data[M4x4Col1Row2] * m_data[M4x4Col3Row0] - m_data[M4x4Col0Row2] * m_data[M4x4Col1Row3] * m_data[M4x4Col3Row0] - m_data[M4x4Col0Row3] * m_data[M4x4Col1Row0] * m_data[M4x4Col3Row2] + m_data[M4x4Col0Row0] * m_data[M4x4Col1Row3] * m_data[M4x4Col3Row2] + m_data[M4x4Col0Row2] * m_data[M4x4Col1Row0] * m_data[M4x4Col3Row3] - m_data[M4x4Col0Row0] * m_data[M4x4Col1Row2] * m_data[M4x4Col3Row3]) * invD;
					inverse.m_data[M4x4Col1Row3] = (m_data[M4x4Col0Row2] * m_data[M4x4Col1Row3] * m_data[M4x4Col2Row0] - m_data[M4x4Col0Row3] * m_data[M4x4Col1Row2] * m_data[M4x4Col2Row0] + m_data[M4x4Col0Row3] * m_data[M4x4Col1Row0] * m_data[M4x4Col2Row2] - m_data[M4x4Col0Row0] * m_data[M4x4Col1Row3] * m_data[M4x4Col2Row2] - m_data[M4x4Col0Row2] * m_data[M4x4Col1Row0] * m_data[M4x4Col2Row3] + m_data[M4x4Col0Row0] * m_data[M4x4Col1Row2] * m_data[M4x4Col2Row3]) * invD;

					inverse.m_data[M4x4Col2Row0] = (m_data[M4x4Col1Row1] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row0] - m_data[M4x4Col1Row3] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row0] + m_data[M4x4Col1Row3] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row1] - m_data[M4x4Col1Row0] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row1] - m_data[M4x4Col1Row1] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row3] + m_data[M4x4Col1Row0] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row3]) * invD;
					inverse.m_data[M4x4Col2Row1] = (m_data[M4x4Col0Row3] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row0] - m_data[M4x4Col0Row1] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row0] - m_data[M4x4Col0Row3] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row1] + m_data[M4x4Col0Row0] * m_data[M4x4Col2Row3] * m_data[M4x4Col3Row1] + m_data[M4x4Col0Row1] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row3] - m_data[M4x4Col0Row0] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row3]) * invD;
					inverse.m_data[M4x4Col2Row2] = (m_data[M4x4Col0Row1] * m_data[M4x4Col1Row3] * m_data[M4x4Col3Row0] - m_data[M4x4Col0Row3] * m_data[M4x4Col1Row1] * m_data[M4x4Col3Row0] + m_data[M4x4Col0Row3] * m_data[M4x4Col1Row0] * m_data[M4x4Col3Row1] - m_data[M4x4Col0Row0] * m_data[M4x4Col1Row3] * m_data[M4x4Col3Row1] - m_data[M4x4Col0Row1] * m_data[M4x4Col1Row0] * m_data[M4x4Col3Row3] + m_data[M4x4Col0Row0] * m_data[M4x4Col1Row1] * m_data[M4x4Col3Row3]) * invD;
					inverse.m_data[M4x4Col2Row3] = (m_data[M4x4Col0Row3] * m_data[M4x4Col1Row1] * m_data[M4x4Col2Row0] - m_data[M4x4Col0Row1] * m_data[M4x4Col1Row3] * m_data[M4x4Col2Row0] - m_data[M4x4Col0Row3] * m_data[M4x4Col1Row0] * m_data[M4x4Col2Row1] + m_data[M4x4Col0Row0] * m_data[M4x4Col1Row3] * m_data[M4x4Col2Row1] + m_data[M4x4Col0Row1] * m_data[M4x4Col1Row0] * m_data[M4x4Col2Row3] - m_data[M4x4Col0Row0] * m_data[M4x4Col1Row1] * m_data[M4x4Col2Row3]) * invD;

					inverse.m_data[M4x4Col3Row0] = (m_data[M4x4Col1Row2] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row0] - m_data[M4x4Col1Row1] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row0] - m_data[M4x4Col1Row2] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row1] + m_data[M4x4Col1Row0] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row1] + m_data[M4x4Col1Row1] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row2] - m_data[M4x4Col1Row0] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row2]) * invD;
					inverse.m_data[M4x4Col3Row1] = (m_data[M4x4Col0Row1] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row0] - m_data[M4x4Col0Row2] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row0] + m_data[M4x4Col0Row2] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row1] - m_data[M4x4Col0Row0] * m_data[M4x4Col2Row2] * m_data[M4x4Col3Row1] - m_data[M4x4Col0Row1] * m_data[M4x4Col2Row0] * m_data[M4x4Col3Row2] + m_data[M4x4Col0Row0] * m_data[M4x4Col2Row1] * m_data[M4x4Col3Row2]) * invD;
					inverse.m_data[M4x4Col3Row2] = (m_data[M4x4Col0Row2] * m_data[M4x4Col1Row1] * m_data[M4x4Col3Row0] - m_data[M4x4Col0Row1] * m_data[M4x4Col1Row2] * m_data[M4x4Col3Row0] - m_data[M4x4Col0Row2] * m_data[M4x4Col1Row0] * m_data[M4x4Col3Row1] + m_data[M4x4Col0Row0] * m_data[M4x4Col1Row2] * m_data[M4x4Col3Row1] + m_data[M4x4Col0Row1] * m_data[M4x4Col1Row0] * m_data[M4x4Col3Row2] - m_data[M4x4Col0Row0] * m_data[M4x4Col1Row1] * m_data[M4x4Col3Row2]) * invD;
					inverse.m_data[M4x4Col3Row3] = (m_data[M4x4Col0Row1] * m_data[M4x4Col1Row2] * m_data[M4x4Col2Row0] - m_data[M4x4Col0Row2] * m_data[M4x4Col1Row1] * m_data[M4x4Col2Row0] + m_data[M4x4Col0Row2] * m_data[M4x4Col1Row0] * m_data[M4x4Col2Row1] - m_data[M4x4Col0Row0] * m_data[M4x4Col1Row2] * m_data[M4x4Col2Row1] - m_data[M4x4Col0Row1] * m_data[M4x4Col1Row0] * m_data[M4x4Col2Row2] + m_data[M4x4Col0Row0] * m_data[M4x4Col1Row1] * m_data[M4x4Col2Row2]) * invD;
				}

				return inverse;
			}

			/**
			 * @brief Clears the rotation component of the matrix.
			 * @return void
			 */
			void
			clearRotation () noexcept
			{
				if constexpr ( dim_t == 4 )
				{
					m_data[M4x4Col0Row0] = 1;
					m_data[M4x4Col1Row0] = 0;
					m_data[M4x4Col2Row0] = 0;

					m_data[M4x4Col0Row1] = 0;
					m_data[M4x4Col1Row1] = 1;
					m_data[M4x4Col2Row1] = 0;

					m_data[M4x4Col0Row2] = 0;
					m_data[M4x4Col1Row2] = 0;
					m_data[M4x4Col2Row2] = 1;
				}
				else
				{
					this->reset();
				}
			}

			/**
			 * @brief Convenient way to get a identity matrix.
			 * @note This is the same as calling the default constructor.
			 * @return Matrix
			 */
			[[nodiscard]]
			static
			constexpr
			Matrix
			identity () noexcept
			{
				return {};
			}

			/**
			 * @brief Clears the translation component of the matrix.
			 * @tparam N The size must be 4.
			 * @return void
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			void
			clearTranslation () noexcept
			{
				m_data[M4x4Col3Row0] = 0;
				m_data[M4x4Col3Row1] = 0;
				m_data[M4x4Col3Row2] = 0;
			}

			/**
			 * @brief Returns the matrix without the translation transformation.
			 * @tparam N The size must be 4.
			 * @return Matrix
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			Matrix
			noTranslation () const noexcept
			{
				/* FIXME: Check this ! */
				return {{{
					m_data[M4x4Col0Row0], m_data[M4x4Col1Row0], m_data[M4x4Col2Row0], 0,
					m_data[M4x4Col0Row1], m_data[M4x4Col1Row1], m_data[M4x4Col2Row1], 0,
					m_data[M4x4Col0Row2], m_data[M4x4Col1Row2], m_data[M4x4Col2Row2], 0,
					m_data[M4x4Col0Row3], m_data[M4x4Col1Row3], m_data[M4x4Col2Row3], m_data[M4x4Col3Row3]
				}}};
			}

			/*enum class Quadrant
			{
				TopLeft = 0,
				BottomLeft = 1,
				TopRight = 2,
				BottomRight = 3
			};

			template< std::size_t N = dim_t, std::enable_if_t< N == 3, bool > = false >
			Matrix< 2, data_t >
			reduceMatrix (Quadrant quadrant) const noexcept
			{
				Matrix< 2, data_t > matrix;

				switch ( quadrant )
				{
					case Quadrant::TopLeft :
						matrix[M2x2Col0Row0] = m_data[M3x3Col0Row0];
						matrix[M2x2Col0Row1] = m_data[M3x3Col0Row1];

						matrix[M2x2Col1Row0] = m_data[M3x3Col1Row0];
						matrix[M2x2Col1Row1] = m_data[M3x3Col1Row1];
						break;

					case Quadrant::BottomLeft :
						matrix[M2x2Col0Row0] = m_data[M3x3Col1Row0];
						matrix[M2x2Col0Row1] = m_data[M3x3Col1Row1];

						matrix[M2x2Col1Row0] = m_data[M3x3Col2Row0];
						matrix[M2x2Col1Row1] = m_data[M3x3Col2Row1];
						break;

					case Quadrant::TopRight :
						matrix[M2x2Col0Row0] = m_data[M3x3Col0Row1];
						matrix[M2x2Col0Row1] = m_data[M3x3Col0Row2];

						matrix[M2x2Col1Row0] = m_data[M3x3Col1Row1];
						matrix[M2x2Col1Row1] = m_data[M3x3Col1Row2];
						break;

					case Quadrant::BottomRight :
						matrix[M2x2Col0Row0] = m_data[M3x3Col1Row1];
						matrix[M2x2Col0Row1] = m_data[M3x3Col1Row2];

						matrix[M2x2Col1Row0] = m_data[M3x3Col2Row1];
						matrix[M2x2Col1Row1] = m_data[M3x3Col2Row2];
						break;
				}

				return matrix;
			}

			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			Matrix< 3, data_t >
			reduceMatrix (Quadrant quadrant) const noexcept
			{
				Matrix< 3, data_t > matrix;

				switch ( quadrant )
				{
					case Quadrant::TopLeft :
						matrix[M3x3Col0Row0] = m_data[M4x4Col0Row0];
						matrix[M3x3Col0Row1] = m_data[M4x4Col0Row1];
						matrix[M3x3Col0Row2] = m_data[M4x4Col0Row2];

						matrix[M3x3Col1Row0] = m_data[M4x4Col1Row0];
						matrix[M3x3Col1Row1] = m_data[M4x4Col1Row1];
						matrix[M3x3Col1Row2] = m_data[M4x4Col1Row2];

						matrix[M3x3Col2Row0] = m_data[M4x4Col2Row0];
						matrix[M3x3Col2Row1] = m_data[M4x4Col2Row1];
						matrix[M3x3Col2Row2] = m_data[M4x4Col2Row2];
						break;

					case Quadrant::BottomLeft :
						matrix[M3x3Col0Row0] = m_data[M4x4Col1Row0];
						matrix[M3x3Col0Row1] = m_data[M4x4Col1Row1];
						matrix[M3x3Col0Row2] = m_data[M4x4Col1Row2];

						matrix[M3x3Col1Row0] = m_data[M4x4Col2Row0];
						matrix[M3x3Col1Row1] = m_data[M4x4Col2Row1];
						matrix[M3x3Col1Row2] = m_data[M4x4Col2Row2];

						matrix[M3x3Col2Row0] = m_data[M4x4Col3Row0];
						matrix[M3x3Col2Row1] = m_data[M4x4Col3Row1];
						matrix[M3x3Col2Row2] = m_data[M4x4Col3Row2];
						break;

					case Quadrant::TopRight :
						matrix[M3x3Col0Row0] = m_data[M4x4Col0Row1];
						matrix[M3x3Col0Row1] = m_data[M4x4Col0Row2];
						matrix[M3x3Col0Row2] = m_data[M4x4Col0Row3];

						matrix[M3x3Col1Row0] = m_data[M4x4Col1Row1];
						matrix[M3x3Col1Row1] = m_data[M4x4Col1Row2];
						matrix[M3x3Col1Row2] = m_data[M4x4Col1Row3];

						matrix[M3x3Col2Row0] = m_data[M4x4Col2Row1];
						matrix[M3x3Col2Row1] = m_data[M4x4Col2Row2];
						matrix[M3x3Col2Row2] = m_data[M4x4Col2Row3];
						break;

					case Quadrant::BottomRight :
						matrix[M3x3Col0Row0] = m_data[M4x4Col1Row1];
						matrix[M3x3Col0Row1] = m_data[M4x4Col1Row2];
						matrix[M3x3Col0Row2] = m_data[M4x4Col1Row3];

						matrix[M3x3Col1Row0] = m_data[M4x4Col2Row1];
						matrix[M3x3Col1Row1] = m_data[M4x4Col2Row2];
						matrix[M3x3Col1Row2] = m_data[M4x4Col2Row3];

						matrix[M3x3Col2Row0] = m_data[M4x4Col3Row1];
						matrix[M3x3Col2Row1] = m_data[M4x4Col3Row2];
						matrix[M3x3Col2Row2] = m_data[M4x4Col3Row3];
						break;
				}

				return matrix;
			}*/

			/**
			 * @brief Converts a matrix to a matrix of 2x2 dimensions.
			 * @return Matrix< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			Matrix< 2, data_t >
			toMatrix2 () const noexcept
			{
				Matrix< 2, data_t > matrix;

				if constexpr ( dim_t == 3 )
				{
					matrix[M2x2Col0Row0] = m_data[M3x3Col0Row0];
					matrix[M2x2Col0Row1] = m_data[M3x3Col0Row1];

					matrix[M2x2Col1Row0] = m_data[M3x3Col1Row0];
					matrix[M2x2Col1Row1] = m_data[M3x3Col1Row1];
				}

				if constexpr ( dim_t == 4 )
				{
					matrix[M2x2Col0Row0] = m_data[M4x4Col0Row0];
					matrix[M2x2Col0Row1] = m_data[M4x4Col0Row1];

					matrix[M2x2Col1Row0] = m_data[M4x4Col1Row0];
					matrix[M2x2Col1Row1] = m_data[M4x4Col1Row1];
				}

				return matrix;
			}

			/**
			 * @brief Converts a matrix to a matrix of 3x3 dimensions.
			 * @return Matrix< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2 || N == 4, bool > = false >
			[[nodiscard]]
			Matrix< 3, data_t >
			toMatrix3 () const noexcept
			{
				Matrix< 3, data_t > matrix;

				if constexpr ( dim_t == 2 )
				{
					matrix[M3x3Col0Row0] = m_data[M2x2Col0Row0];
					matrix[M3x3Col0Row1] = m_data[M2x2Col0Row1];

					matrix[M3x3Col1Row0] = m_data[M2x2Col1Row0];
					matrix[M3x3Col1Row1] = m_data[M2x2Col1Row1];
				}

				if constexpr ( dim_t == 4 )
				{
					matrix[M3x3Col0Row0] = m_data[M4x4Col0Row0];
					matrix[M3x3Col0Row1] = m_data[M4x4Col0Row1];
					matrix[M3x3Col0Row2] = m_data[M4x4Col0Row2];

					matrix[M3x3Col1Row0] = m_data[M4x4Col1Row0];
					matrix[M3x3Col1Row1] = m_data[M4x4Col1Row1];
					matrix[M3x3Col1Row2] = m_data[M4x4Col1Row2];

					matrix[M3x3Col2Row0] = m_data[M4x4Col2Row0];
					matrix[M3x3Col2Row1] = m_data[M4x4Col2Row1];
					matrix[M3x3Col2Row2] = m_data[M4x4Col2Row2];
				}

				return matrix;
			}

			/**
			 * @brief Converts a matrix to a matrix of 4x4 dimensions.
			 * @return Matrix< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2 || N == 3, bool > = false >
			[[nodiscard]]
			Matrix< 4, data_t >
			toMatrix4 () const noexcept
			{
				Matrix< 4, data_t > matrix;

				if constexpr ( dim_t == 2 )
				{
					matrix[M4x4Col0Row0] = m_data[M2x2Col0Row0];
					matrix[M4x4Col0Row1] = m_data[M2x2Col0Row1];

					matrix[M4x4Col1Row0] = m_data[M2x2Col1Row0];
					matrix[M4x4Col1Row1] = m_data[M2x2Col1Row1];
				}

				if constexpr ( dim_t == 3 )
				{
					matrix[M4x4Col0Row0] = m_data[M3x3Col0Row0];
					matrix[M4x4Col0Row1] = m_data[M3x3Col0Row1];
					matrix[M4x4Col0Row2] = m_data[M3x3Col0Row2];

					matrix[M4x4Col1Row0] = m_data[M3x3Col1Row0];
					matrix[M4x4Col1Row1] = m_data[M3x3Col1Row1];
					matrix[M4x4Col1Row2] = m_data[M3x3Col1Row2];

					matrix[M4x4Col2Row0] = m_data[M3x3Col2Row0];
					matrix[M4x4Col2Row1] = m_data[M3x3Col2Row1];
					matrix[M4x4Col2Row2] = m_data[M3x3Col2Row2];
				}

				return matrix;
			}

			/**
			 * @brief Returns a rotation 2x2 matrix.
			 * @param radian Angle of rotation in radian.
			 * @param x Around X axis.
			 * @param y Around Y axis.
			 * @return Matrix< 2, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			[[nodiscard]]
			static
			Matrix
			rotation (data_t radian, data_t x, data_t y) noexcept
			{
				Matrix matrix{};

				auto sinus = std::sin(radian);
				auto cosin = std::cos(radian);

				matrix[M2x2Col0Row0] = x * cosin;
				matrix[M2x2Col0Row1] = x * sinus;

				matrix[M2x2Col1Row0] = y * -sinus;
				matrix[M2x2Col1Row1] = y * cosin;

				return matrix;
			}

			/**
			 * @brief Returns a rotation matrix.
			 * @param radian Angle of rotation in radian.
			 * @param x Around X axis.
			 * @param y Around Y axis.
			 * @return Matrix< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			rotation (data_t radian, data_t x, data_t y, data_t z) noexcept
			{
				Matrix matrix{};

				auto sinus = std::sin(radian);
				auto cosin = std::cos(radian);
				auto acosin = static_cast< data_t >(1.0) - cosin;

				if constexpr ( dim_t == 3 )
				{
					matrix[M3x3Col0Row0] = x * x * acosin + cosin;
					matrix[M3x3Col1Row0] = y * x * acosin - z * sinus;
					matrix[M3x3Col2Row0] = z * x * acosin + y * sinus;

					matrix[M3x3Col0Row1] = x * y * acosin + z * sinus;
					matrix[M3x3Col1Row1] = y * y * acosin + cosin;
					matrix[M3x3Col2Row1] = z * y * acosin - x * sinus;

					matrix[M3x3Col0Row2] = x * z * acosin - y * sinus;
					matrix[M3x3Col1Row2] = y * z * acosin + x * sinus;
					matrix[M3x3Col2Row2] = z * z * acosin + cosin;
				}

				if constexpr ( dim_t == 4 )
				{
					matrix[M4x4Col0Row0] = x * x * acosin + cosin;
					matrix[M4x4Col1Row0] = y * x * acosin - z * sinus;
					matrix[M4x4Col2Row0] = z * x * acosin + y * sinus;

					matrix[M4x4Col0Row1] = x * y * acosin + z * sinus;
					matrix[M4x4Col1Row1] = y * y * acosin + cosin;
					matrix[M4x4Col2Row1] = z * y * acosin - x * sinus;

					matrix[M4x4Col0Row2] = x * z * acosin - y * sinus;
					matrix[M4x4Col1Row2] = y * z * acosin + x * sinus;
					matrix[M4x4Col2Row2] = z * z * acosin + cosin;
				}

				return matrix;
			}

			/**
			 * @brief Returns a rotation 2x2 matrix.
			 * @param radian Angle of rotation in radian.
			 * @param rotationVector A reference to a Vector< 2, data_t > for the rotation axis.
			 * @return Matrix< 2, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			[[nodiscard]]
			static
			Matrix
			rotation (data_t radian, const Vector< 2, data_t > & rotationVector) noexcept
			{
				return Matrix::rotation(radian, rotationVector[X], rotationVector[Y]);
			}

			/**
			 * @brief Returns a rotation 2x2 matrix.
			 * @param radian Angle of rotation in radian.
			 * @param rotationVector A reference to a Vector< 3, data_t > for the rotation axis.
			 * @return Matrix< 2, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			[[nodiscard]]
			static
			Matrix
			rotation (data_t radian, const Vector< 3, data_t > & rotationVector) noexcept
			{
				return Matrix::rotation(radian, rotationVector[X], rotationVector[Y]);
			}

			/**
			 * @brief Returns a rotation 2x2 matrix.
			 * @param radian Angle of rotation in radian.
			 * @param rotationVector A reference to a Vector< 4, data_t > for the rotation axis.
			 * @return Matrix< 2, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			[[nodiscard]]
			static
			Matrix
			rotation (data_t radian, const Vector< 4, data_t > & rotationVector) noexcept
			{
				return Matrix::rotation(radian, rotationVector[X], rotationVector[Y]);
			}

			/**
			 * @brief Returns a rotation matrix.
			 * @param radian Angle of rotation in radian.
			 * @param rotationVector A reference to a Vector< 3, data_t > for the rotation axis.
			 * @return Matrix< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			rotation (data_t radian, const Vector< 3, data_t > & rotationVector) noexcept
			{
				return Matrix::rotation(radian, rotationVector[X], rotationVector[Y], rotationVector[Z]);
			}

			/**
			 * @brief Returns a rotation matrix.
			 * @param radian Angle of rotation in radian.
			 * @param rotationVector A reference to a Vector< 4, data_t > for the rotation axis.
			 * @return Matrix< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			rotation (data_t radian, const Vector< 4, data_t > & rotationVector) noexcept
			{
				return Matrix::rotation(radian, rotationVector[X], rotationVector[Y], rotationVector[Z]);
			}

			/**
			 * @brief Returns a scaling matrix.
			 * @param scale A scalar value.
			 * @return Matrix< dim_t, data_t >
			 */
			[[nodiscard]]
			static
			Matrix
			scaling (data_t scale) noexcept
			{
				if constexpr ( dim_t == 2 )
				{
					return Matrix::scaling(scale, scale);
				}
				else
				{
					return Matrix::scaling(scale, scale, scale);
				}
			}

			/**
			 * @brief Returns a scaling 2x2 matrix.
			 * @param xScale A scalar value for X axis.
			 * @param yScale A scalar value for Y axis.
			 * @return Matrix< 2, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			[[nodiscard]]
			static
			Matrix
			scaling (data_t xScale, data_t yScale) noexcept
			{
				Matrix matrix{};

				matrix[M2x2Col0Row0] = xScale;
				matrix[M2x2Col1Row1] = yScale;

				return matrix;
			}

			/**
			 * @brief Returns a scaling matrix.
			 * @param xScale A scalar value for X axis.
			 * @param yScale A scalar value for Y axis.
			 * @param zScale A scalar value for Z axis.
			 * @return Matrix< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			scaling (data_t xScale, data_t yScale, data_t zScale) noexcept
			{
				Matrix matrix{};

				if constexpr ( dim_t == 3 )
				{
					matrix[M3x3Col0Row0] = xScale;
					matrix[M3x3Col1Row1] = yScale;
					matrix[M3x3Col2Row2] = zScale;
				}

				if constexpr ( dim_t == 4 )
				{
					matrix[M4x4Col0Row0] = xScale;
					matrix[M4x4Col1Row1] = yScale;
					matrix[M4x4Col2Row2] = zScale;
				}

				return matrix;
			}

			/**
			 * @brief Returns a scaling 2x2 matrix.
			 * @param scaleVector A reference to a Vector< 2, data_t > for scaling factor.
			 * @return Matrix< 2, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			[[nodiscard]]
			static
			Matrix
			scaling (const Vector< 2, data_t > & scaleVector) noexcept
			{
				return Matrix::scaling(scaleVector[X], scaleVector[Y]);
			}

			/**
			 * @brief Returns a scaling 2x2 matrix.
			 * @param scaleVector A reference to a Vector< 3, data_t > for scaling factor.
			 * @return Matrix< 2, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			[[nodiscard]]
			static
			Matrix
			scaling (const Vector< 3, data_t > & scaleVector) noexcept
			{
				return Matrix::scaling(scaleVector[X], scaleVector[Y]);
			}

			/**
			 * @brief Returns a scaling 2x2 matrix.
			 * @param scaleVector A reference to a Vector< 4, data_t > for scaling factor.
			 * @return Matrix< 2, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 2, bool > = false >
			[[nodiscard]]
			static
			Matrix
			scaling (const Vector< 4, data_t > & scaleVector) noexcept
			{
				return Matrix::scaling(scaleVector[X], scaleVector[Y]);
			}

			/**
			 * @brief Returns a scaling matrix.
			 * @param scaleVector A reference to a Vector< 3, data_t > for scaling factor.
			 * @return Matrix< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			scaling (const Vector< 3, data_t > & scaleVector) noexcept
			{
				return Matrix::scaling(scaleVector[X], scaleVector[Y], scaleVector[Z]);
			}

			/**
			 * @brief Returns a scaling matrix.
			 * @param scaleVector A reference to a Vector< 4, data_t > for scaling factor.
			 * @return Matrix< dim_t, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 3 || N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			scaling (const Vector< 4, data_t > & scaleVector) noexcept
			{
				return Matrix::scaling(scaleVector[X], scaleVector[Y], scaleVector[Z]);
			}

			/**
			 * @brief Returns a translation 4x4 matrix.
			 * @param xShift Shift distance on X axis.
			 * @param yShift Shift distance on Y axis.
			 * @param zShift Shift distance on Z axis.
			 * @return Matrix< 4, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			translation (data_t xShift, data_t yShift, data_t zShift) noexcept
			{
				Matrix matrix{};

				matrix[M4x4Col3Row0] = xShift;
				matrix[M4x4Col3Row1] = yShift;
				matrix[M4x4Col3Row2] = zShift;

				return matrix;
			}

			/**
			 * @brief Returns a translation 4x4 matrix.
			 * @param shiftVector A reference to a Vector< 3, data_t > for the shift in XYZ axis.
			 * @return Matrix< 4, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			translation (const Vector< 3, data_t > & shiftVector) noexcept
			{
				return Matrix::translation(shiftVector[X], shiftVector[Y], shiftVector[Z]);
			}

			/**
			 * @brief Returns a translation 4x4 matrix.
			 * @param shiftVector A reference to a Vector< 4, data_t > for the shift in XYZ axis.
			 * @return Matrix< 4, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			translation (const Vector< 4, data_t > & shiftVector) noexcept
			{
				return Matrix::translation(shiftVector[X], shiftVector[Y], shiftVector[Z]);
			}

			/**
			 * @brief Returns a frustum 4x4 matrix.
			 * @param xLeft Negative X distance.
			 * @param xRight Positive X distance.
			 * @param yBottom Negative Y distance.
			 * @param yTop Positive Y distance.
			 * @param zNear Negative Z distance.
			 * @param zFar Positive Z distance.
			 * @return Matrix< 4, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			frustum (data_t xLeft, data_t xRight, data_t yBottom, data_t yTop, data_t zNear, data_t zFar) noexcept
			{
				Matrix matrix{};

				if ( Utility::different(xRight, xLeft) && Utility::different(yTop, yBottom) && Utility::different(zNear, zFar) && zNear >= 0.0 && zFar >= 0.0 )
				{
					matrix[M4x4Col0Row0] = (2.0 * zNear) / (xRight - xLeft);
					matrix[M4x4Col2Row0] = (xRight + xLeft) / (xRight - xLeft);

					matrix[M4x4Col1Row1] = (2.0 * zNear) / (yTop - yBottom);
					matrix[M4x4Col2Row1] = (yTop + yBottom) / (yTop - yBottom);

					matrix[M4x4Col2Row2] = -(zFar + zNear) / (zFar - zNear);
					matrix[M4x4Col3Row2] = -(2.0 * zFar * zNear) / (zFar - zNear);

					matrix[M4x4Col2Row3] = -1.0;
					matrix[M4x4Col3Row3] = 0.0;
				}

				return matrix;
			}

			/**
			 * @brief Returns a orthographic projection 4x4 matrix.
			 * @note OpenGL compliant (right handed). Tested against glm::orthoRH().
			 * @param xLeft Negative X distance.
			 * @param xRight Positive X distance.
			 * @param yBottom Negative Y distance.
			 * @param yTop Positive Y distance.
			 * @param zNear Negative Z distance. Default -1.
			 * @param zFar Positive Z distance. Default 1.
			 * @return Matrix< 4, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			orthographicProjection (data_t xLeft, data_t xRight, data_t yBottom, data_t yTop, data_t zNear = -1, data_t zFar = 1) noexcept
			{
				Matrix matrix{};

				if ( Utility::different(xRight, xLeft) && Utility::different(yTop, yBottom) && Utility::different(zFar, zNear) )
				{
					auto deltaValue = xRight - xLeft;

					matrix[M4x4Col0Row0] = 2 / deltaValue;
					matrix[M4x4Col3Row0] = -((xRight + xLeft) / deltaValue);

					deltaValue = yTop - yBottom;

					matrix[M4x4Col1Row1] = 2 / deltaValue;
					matrix[M4x4Col3Row1] = -((yTop + yBottom) / deltaValue);

					deltaValue = zFar - zNear;

					matrix[M4x4Col2Row2] = -2 / deltaValue;
					matrix[M4x4Col3Row2] = -((zFar + zNear) / deltaValue);
				}
				else
				{
					std::cerr << __PRETTY_FUNCTION__ << ", Orthographic projection : bad params !" << std::endl;
				}

				return matrix;
			}

			/**
			 * @brief Returns a orthographic projection 4x4 matrix.
			 * @note OpenGL compliant (right handed). Tested against glm::perspectiveRH().
			 * @param fov Field of view in degree.
			 * @param aspectRatio The aspect ratio of the viewport.
			 * @param zNear Limit for nearest vertices.
			 * @param zFar Limit for farthest vertices.
			 * @return Matrix< 4, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			perspectiveProjection (data_t fov, data_t aspectRatio, data_t zNear = 0, data_t zFar = 1) noexcept
			{
				Matrix matrix{};

				/* zNear, zFar must always be positive */
				if ( zNear >= 0 && zFar >= 0 )
				{
					const auto a = fastCotan(fov * static_cast< data_t >(0.5));

					matrix[M4x4Col0Row0] = a / aspectRatio;

					matrix[M4x4Col1Row1] = a;

					matrix[M4x4Col2Row2] = -((zFar + zNear) / (zFar - zNear));
					matrix[M4x4Col3Row2] = -((2 * zFar * zNear) / (zFar - zNear));

					matrix[M4x4Col2Row3] = -1;
					matrix[M4x4Col3Row3] = 0;
				}
				else
				{
					std::cerr << __PRETTY_FUNCTION__ << ", bad params ! (zNear: " << zNear << ", zFar: " << zFar << ")" << std::endl;
				}

				return matrix;
			}

			/**
			 * @brief Returns a lookAt view 4x4 matrix.
			 * @note OpenGL compliant (right handed). Tested against glm::lookAtRH().
			 * @param eye A reference to a Vector< 3, data_t > for the "eye" direction.
			 * @param center A reference to a Vector< 3, data_t > for the "eye" position.
			 * @param up A reference to a Vector< 3, data_t > for the upward direction from the "eye".
			 * @return Matrix< 4, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			lookAt (const Vector< 3, data_t > & eye, const Vector< 3, data_t > & center, const Vector< 3, data_t > & up) noexcept
			{
				auto forward = (center - eye).normalize();

				/* Left = forward x up */
				auto left = Vector< 3, data_t >::crossProduct(forward, up);
				left.normalize();

				/* Recompute up as: upward = side x forward */
				auto upward = Vector< 3, data_t >::crossProduct(left, forward);

				Matrix matrix{};
				matrix.setColumn(0, left[X], left[Y], left[Z], 0);
				matrix.setColumn(1, upward[X], upward[Y], upward[Z], 0);
				matrix.setColumn(2, -forward[X], -forward[Y], -forward[Z], -0);
				//matrix.setColumn(3, -eye[X], -eye[Y], -eye[Z], -1);
				matrix *= Matrix::translation(-eye[X], -eye[Y], -eye[Z]);

				return matrix;
			}

			/**
			 * @brief Returns a lookAt view 4x4 matrix.
			 * @note OpenGL compliant (right handed). Tested against glm::lookAtRH().
			 * @param eye A reference to a Vector< 4, data_t > for the "eye" direction.
			 * @param center A reference to a Vector< 4, data_t > for the "eye" position.
			 * @param up A reference to a Vector< 4, data_t > for the upward direction from the "eye".
			 * @return Matrix< 4, data_t >
			 */
			template< std::size_t N = dim_t, std::enable_if_t< N == 4, bool > = false >
			[[nodiscard]]
			static
			Matrix
			lookAt (const Vector< 4, data_t > & eye, const Vector< 4, data_t > & center, const Vector< 4, data_t > & up) noexcept
			{
				auto forward = (center - eye).normalize();

				/* Left = forward x up */
				auto left = Vector< 4, data_t >::crossProduct(forward, up);
				left.normalize();

				/* Recompute up as: upward = side x forward */
				auto upward = Vector< 4, data_t >::crossProduct(left, forward);

				Matrix matrix{};
				matrix.setColumn(0, left);
				matrix.setColumn(1, upward);
				matrix.setColumn(2, -forward);
				//matrix.setColumn(3, -eye);
				matrix *= Matrix::translation(-eye[X], -eye[Y], -eye[Z]);

				return matrix;
			}

			/**
			 * @brief Copies the matrix data inside a C-Array of data_t.
			 * @warning Unsafe !
			 * @param target A pointer to the data.
			 * @warning The target must provide enough space.
			 */
			void
			copy (data_t * target) const noexcept
			{
				#pragma omp simd
				for ( size_t index = 0; index < dim_t * dim_t; index++ )
				{
					target[index] = m_data[index]; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
				}
			}

			/**
			 * @brief STL streams printable object.
			 * @param out A reference to the stream output.
			 * @param obj A reference to the object to print.
			 * @return ostream &
			 */
			friend
			std::ostream &
			operator<< (std::ostream & out, const Matrix & obj) noexcept
			{
				using namespace std;

				out << "Matrix" << dim_t << 'X' << dim_t << '\n' << fixed << setprecision(8);

				for ( size_t rowIndex = 0; rowIndex < dim_t; rowIndex++ )
				{
					for ( size_t columnIndex = 0; columnIndex < dim_t; columnIndex++ )
					{
						out << '[' << setw(16) << obj.m_data[(columnIndex * dim_t) + rowIndex] << ']';
					}

					out << '\n';
				}

				return out;
			}

			/**
			 * @brief Stringifies the object.
			 * @param obj A reference to the object to print.
			 * @return string
			 */
			friend
			std::string
			to_string (const Matrix & obj) noexcept
			{
				return (std::stringstream{} << obj).str();
			}

		private:

			std::array< data_t, dim_t * dim_t > m_data{0};
	};

	using Matrix2f = Matrix< 2UL, float >;
	using Matrix3f = Matrix< 3UL, float >;
	using Matrix4f = Matrix< 4UL, float >;

	using Matrix2d = Matrix< 2UL, double >;
	using Matrix3d = Matrix< 3UL, double >;
	using Matrix4d = Matrix< 4UL, double >;

	// NOLINTEND(readability-identifier-length, *-magic-numbers)
}
