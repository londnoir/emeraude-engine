/*
 * Libraries/Testing/test_Hash.cpp
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

/* Local inclusions. */
#include "Hash/Hash.hpp"

using namespace Libraries;

TEST(Hash, md5)
{
	EXPECT_EQ(Hash::md5("TestString"), "5b56f40f8828701f97fa4511ddcd25fb");
}

TEST(Hash, sha256)
{
	EXPECT_EQ(Hash::sha256("TestString"), "6dd79f2770a0bb38073b814a5ff000647b37be5abbde71ec9176c6ce0cb32a27");
}

TEST(Hash, sha512)
{
	EXPECT_EQ(Hash::sha512("TestString"), "69dfd91314578f7f329939a7ea6be4497e6fe3909b9c8f308fe711d29d4340d90d77b7fdf359b7d0dbeed940665274f7ca514cd067895fdf59de0cf142b62336");
}
