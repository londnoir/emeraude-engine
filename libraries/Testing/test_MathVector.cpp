/*
 * Libraries/Testing/test_MathVector.cpp
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
#include "Math/Vector.hpp"

using namespace Libraries::Math;

using MathTypeList = testing::Types< int, float, double, long double >;

template< typename >
struct Math
	: testing::Test
{

};
TYPED_TEST_SUITE(Math, MathTypeList);

TYPED_TEST(Math, Vector2Default)
{
	const std::array< TypeParam, 2 > dst{0, 0};

	auto test = Vector< 2, TypeParam >{};

	for ( size_t i = 0; i < dst.size(); ++i )
		EXPECT_EQ(test[i], dst[i]);

	test.reset();

	for ( size_t i = 0; i < dst.size(); ++i )
		EXPECT_EQ(test[i], dst[i]);
}

TYPED_TEST(Math, Vector3Default)
{
	const std::array< TypeParam, 3 > dst{0, 0, 0};

	auto test = Vector< 3, TypeParam >{};

	for ( size_t i = 0; i < dst.size(); ++i )
		EXPECT_EQ(test[i], dst[i]);

	test.reset();

	for ( size_t i = 0; i < dst.size(); ++i )
		EXPECT_EQ(test[i], dst[i]);
}

TYPED_TEST(Math, Vector4Default)
{
	const std::array< TypeParam, 4 > dst{0, 0, 0, 0};

	auto test = Vector< 4, TypeParam >{};

	for ( size_t i = 0; i < dst.size(); ++i )
		EXPECT_EQ(test[i], dst[i]);

	test.reset();

	for ( size_t i = 0; i < dst.size(); ++i )
		EXPECT_EQ(test[i], dst[i]);
}
