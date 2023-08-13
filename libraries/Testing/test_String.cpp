/*
 * Libraries/Testing/test_String.cpp
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
#include "String.hpp"

using namespace Libraries;

TEST(String, concat)
{
	EXPECT_EQ(String::concat("Year ", 2023), "Year 2023");

	EXPECT_EQ(String::concat("Result : ", 93.5F), "Result : 93.500000");

	EXPECT_EQ(String::concat("Hello", " world !"), "Hello world !");
}

TEST(String, contains)
{
	const std::string test{"Is the a number 365 in this sentence ?"};

	EXPECT_EQ(String::contains(test, "365"), true);

	EXPECT_EQ(String::contains(test, "arzepuhf"), false);
}

TEST(String, explode)
{
	EXPECT_EQ(String::explode("aaaa---bb--cccc----ffffrrrr------", "--").size(), 7);

	EXPECT_EQ(String::explode("Hello stupid world !", ' ').size(), 4);
}

TEST(String, ExplodeImplode)
{
	const std::vector< std::string > words{
		"Hello", "stupid", "world", "!"
	};

	EXPECT_EQ(String::implode(words), "Hellostupidworld!");

	EXPECT_EQ(String::implode(words, ' '), "Hello stupid world !");

	EXPECT_EQ(String::implode(words, 99.3F), "Hello99.3stupid99.3world99.3!");

	EXPECT_EQ(String::implode(words, "---"), "Hello---stupid---world---!");
}

TEST(String, trim)
{
	const std::string test{"\t\nDummySTR \t   "};

	EXPECT_EQ(String::trim(test, String::WhiteCharsList, String::Side::Right), "\t\nDummySTR");

	EXPECT_EQ(String::trim(test, String::WhiteCharsList, String::Side::Left), "DummySTR \t   ");

	EXPECT_EQ(String::trim(test, String::WhiteCharsList, String::Side::Both), "DummySTR");
}

TEST(String, pad)
{
	const std::string test{"DummySTR!"};

	EXPECT_EQ(String::pad(test, 16, '-', String::Side::Right), "DummySTR!-------");

	EXPECT_EQ(String::pad(test, 16, '-', String::Side::Left), "-------DummySTR!");

	EXPECT_EQ(String::pad(test, 16, '-', String::Side::Both), "---DummySTR!----");
}

TEST(String, toLower)
{
	EXPECT_EQ(String::toLower("DummySTR!"), "dummystr!");
}

TEST(String, toUpper)
{
	EXPECT_EQ(String::toUpper("DummySTR!"), "DUMMYSTR!");
}

TEST(String, ucfirst)
{
	EXPECT_EQ(String::ucfirst("magnus"), "Magnus");

	EXPECT_EQ(String::ucfirst(" wilson"), " wilson");
}

TEST(String, numericLabel)
{
	EXPECT_EQ(String::numericLabel(std::string("toto"), 3), "toto3");
}

TEST(String, incrementalLabel)
{
	int identifier = 4;

	EXPECT_EQ(String::incrementalLabel(std::string("toto"), identifier), "toto4");

	EXPECT_EQ(identifier, 5);
}

TEST(String, toNumber)
{
	/*std::cout <<
		"sizeof(char) : " << sizeof(char) << "\n"
		"sizeof(unsigned char) : " << sizeof(unsigned char) << "\n"
		"sizeof(short int) : " << sizeof(short int) << "\n"
		"sizeof(unsigned short int) : " << sizeof(unsigned short int) << "\n"
		"sizeof(int) : " << sizeof(int) << "\n"
		"sizeof(unsigned int) : " << sizeof(unsigned int) << "\n"
		"sizeof(long int) : " << sizeof(long int) << "\n"
		"sizeof(unsigned long int) : " << sizeof(unsigned long int) << "\n"
		"sizeof(long long int) : " << sizeof(long long int) << "\n"
		"sizeof(unsigned long int) : " << sizeof(unsigned long long int) << "\n";

	std::cout <<
		"sizeof(int8_t) : " << sizeof(int8_t) << "\n"
		"sizeof(uint8_t) : " << sizeof(uint8_t) << "\n"
		"sizeof(int16_t) : " << sizeof(int16_t) << "\n"
		"sizeof(uint16_t) : " << sizeof(uint16_t) << "\n"
		"sizeof(int32_t) : " << sizeof(int32_t) << "\n"
		"sizeof(uint32_t) : " << sizeof(uint32_t) << "\n"
		"sizeof(int64_t) : " << sizeof(int64_t) << "\n"
		"sizeof(uint64_t) : " << sizeof(uint64_t) << "\n";*/

	/* Check 8-bit integers. */
	EXPECT_EQ(String::toNumber< char >("-128"), (char)-128);
	EXPECT_EQ(String::toNumber< char >("127"), (char)127);
	EXPECT_EQ(String::toNumber< unsigned char >("255"), (unsigned char)255);
	EXPECT_EQ(String::toNumber< int8_t >("-128"), (int8_t)-128);
	EXPECT_EQ(String::toNumber< int8_t >("127"), (int8_t)127);
	EXPECT_EQ(String::toNumber< uint8_t >("255"), (uint8_t)255);

	/* Check 16-bit integers. */
	EXPECT_EQ(String::toNumber< short int >("-32768"), (short int)-32768);
	EXPECT_EQ(String::toNumber< short int >("32767"), (short int)32767);
	EXPECT_EQ(String::toNumber< unsigned short int >("65535"), (unsigned short int)65535);
	EXPECT_EQ(String::toNumber< int16_t >("-32768"), (int16_t)-32768);
	EXPECT_EQ(String::toNumber< int16_t >("32767"), (int16_t)32767);
	EXPECT_EQ(String::toNumber< uint16_t >("65535"), (uint16_t)65535);

	/* Check 32-bit integers. */
	EXPECT_EQ(String::toNumber< int >("-2147483648"), -2147483648);
	EXPECT_EQ(String::toNumber< int >("2147483647"), 2147483647);
	EXPECT_EQ(String::toNumber< unsigned int >("4294967295"), 4294967295U);
	EXPECT_EQ(String::toNumber< int32_t >("-2147483648"), (int32_t)-2147483648);
	EXPECT_EQ(String::toNumber< int32_t >("2147483647"), (int32_t)2147483647);
	EXPECT_EQ(String::toNumber< uint32_t >("4294967295"), (uint32_t)4294967295);

	/* Check 64-bit integers. */
	EXPECT_EQ(String::toNumber< long int >("-9223372036854775808"), -9223372036854775808L);
	EXPECT_EQ(String::toNumber< long int >("9223372036854775807"), 9223372036854775807L);
	EXPECT_EQ(String::toNumber< unsigned long int >("18446744073709551615"), 18446744073709551615UL);
	EXPECT_EQ(String::toNumber< int64_t >("-9223372036854775808"), (int64_t)-9223372036854775808);
	EXPECT_EQ(String::toNumber< int64_t >("9223372036854775807"), (int64_t)9223372036854775807);
	EXPECT_EQ(String::toNumber< uint64_t >("18446744073709551615"), (uint64_t)18446744073709551615);

	/* Check floating point numbers. */
	EXPECT_EQ(String::toNumber< float >("754.125"), 754.125F);
	EXPECT_EQ(String::toNumber< float >("-1847.057"), -1847.057F);
	EXPECT_EQ(String::toNumber< double >("755465465844.1564674968725"), 755465465844.1564674968725);
	EXPECT_EQ(String::toNumber< double >("-6546478.564185678746"), -6546478.564185678746);
	EXPECT_EQ(String::toNumber< long double >("7554654696849861895844.156467498916987678968725"), 7554654696849861895844.156467498916987678968725L);
	EXPECT_EQ(String::toNumber< long double >("-42.56418561798676658688764578127878746"), -42.56418561798676658688764578127878746L);
}
