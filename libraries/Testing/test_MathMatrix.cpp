/*
 * Libraries/Testing/test_MathMatrix.cpp
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

#include <gtest/gtest.h>

/* C/C++ standard libraries. */
#include <array>

/* Local inclusions. */
#include "Math/Matrix.hpp"

using namespace Libraries::Math;

using MathTypeList = testing::Types< int, float, double, long double >;

template< typename >
struct Math
	: testing::Test
{

};
TYPED_TEST_SUITE(Math, MathTypeList);

TYPED_TEST(Math, Matrix2Default)
{
	const std::array< TypeParam, 4 > identity{
		1, 0,
		0, 1
	};

	auto test = Matrix< 2, TypeParam >{};

	for ( size_t i = 0; i < identity.size(); ++i )
		EXPECT_EQ(test[i], identity[i]);

	test = Matrix< 2, TypeParam >::identity();

	for ( size_t i = 0; i < identity.size(); ++i )
		EXPECT_EQ(test[i], identity[i]);

	test.reset();

	for ( size_t i = 0; i < identity.size(); ++i )
		EXPECT_EQ(test[i], identity[i]);
}

TYPED_TEST(Math, Matrix3Default)
{
	const std::array< TypeParam, 9 > identity{
		1, 0, 0,
		0, 1, 0,
		0, 0, 1
	};

	auto test = Matrix< 3, TypeParam >{};

	for ( size_t i = 0; i < identity.size(); ++i )
		EXPECT_EQ(test[i], identity[i]);

	test = Matrix< 3, TypeParam >::identity();

	for ( size_t i = 0; i < identity.size(); ++i )
		EXPECT_EQ(test[i], identity[i]);

	test.reset();

	for ( size_t i = 0; i < identity.size(); ++i )
		EXPECT_EQ(test[i], identity[i]);
}

TYPED_TEST(Math, Matrix4Default)
{
	const std::array< TypeParam, 16 > identity{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	auto test = Matrix< 4, TypeParam >{};

	for ( size_t i = 0; i < identity.size(); ++i )
		EXPECT_EQ(test[i], identity[i]);

	test = Matrix< 4, TypeParam >::identity();

	for ( size_t i = 0; i < identity.size(); ++i )
		EXPECT_EQ(test[i], identity[i]);

	test.reset();

	for ( size_t i = 0; i < identity.size(); ++i )
		EXPECT_EQ(test[i], identity[i]);
}

TYPED_TEST(Math, DeterminantInverse2)
{
	if constexpr ( !std::is_integral_v< TypeParam > )
	{
		const Matrix< 2, TypeParam > matrix{std::array< TypeParam, 4 >{
			15.2, 65.0,
			-3.8, -9.0
		}};

		EXPECT_NEAR(matrix.determinant(), 110.2, 0.001);

		const auto inversedMatrix = matrix.inverse();
		const auto originalMatrix = inversedMatrix.inverse();

		for ( size_t i = 0; i < 4; ++i )
			EXPECT_EQ(inversedMatrix[i], inversedMatrix[i]);
	}
}

TYPED_TEST(Math, DeterminantInverse3)
{
	if constexpr ( !std::is_integral_v< TypeParam > )
	{
		const Matrix< 3, TypeParam > matrix{std::array< TypeParam, 9 >{
			-2.0, 4.1, 8.9,
			7.3, -1.0, 3.2,
			9.6, 0.2, 22.0
		}};

		EXPECT_NEAR(matrix.determinant(), -388.794, 0.001);

		const auto inversedMatrix = matrix.inverse();
		const auto originalMatrix = inversedMatrix.inverse();

		for ( size_t i = 0; i < 9; ++i )
			EXPECT_EQ(inversedMatrix[i], inversedMatrix[i]);
	}
}

TYPED_TEST(Math, DeterminantInverse4)
{
	if constexpr ( !std::is_integral_v< TypeParam > )
	{
		const Matrix< 4, TypeParam > matrix{std::array< TypeParam, 16 >{
			-56.0, 4.1, 13.5, 1.645,
			7.0, 1.2, 3.1, -6.54,
			9.1, 0.0, -2.5, 0.0,
			-4.0, 7.58, -52.2, 3.54
		}};

		EXPECT_NEAR(matrix.determinant(), -12946.25, 0.001);

		const auto inversedMatrix = matrix.inverse();
		const auto originalMatrix = inversedMatrix.inverse();

		for ( size_t i = 0; i < 16; ++i )
			EXPECT_EQ(inversedMatrix[i], inversedMatrix[i]);
	}
}
