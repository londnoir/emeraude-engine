/*
 * src/Libraries/Algorithms/PerlinNoise.hpp
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

/* STL inclusions. */
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <numeric>
#include <random>
#include <type_traits>
#include <vector>

namespace Libraries::Algorithms
{
	/**
	 * @brief Class performing the perlin noise algorithm for a set of points.
	 * @tparam number_t The type of number. Default float.
	 */
	template< typename number_t = float >
	requires (std::is_arithmetic_v< number_t >)
	class PerlinNoise final
	{
		public:

			/**
			 * @brief Constructs a perlin noise processor.
			 * @note Initialize with the reference values for the permutation vector.
			 */
			PerlinNoise () noexcept
				: m_permutations{
					151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
					8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
					35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168,68,175,74,165,71,
					134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
					55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
					18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186,3,64,52,217,226,
					250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
					189,28,42,223,183,170,213,119,248,152,2,44,154,163, 70,221,153,101,155,167,
					43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185,112,104,218,246,
					97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
					107,49,192,214, 31,181,199,106,157,184,84,204,176,115,121,50,45,127,4,150,254,
					138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
				}
			{
				/* Duplicate the permutation vector. */
				m_permutations.insert(m_permutations.end(), m_permutations.begin(), m_permutations.end());
			}

			/**
			 * @brief Constructs a perlin noise processor.
			 * @note Generate a new permutation vector based on the value of seed.
			 * @param seed The seed number.
			 */
			explicit
			PerlinNoise (unsigned int seed) noexcept
			{
				m_permutations.resize(256);

				/* Fill p with values from 0 to 255. */
				std::iota(m_permutations.begin(), m_permutations.end(), 0);

				/* Initialize a random engine with seed. */
				std::default_random_engine engine(seed);

				/* Shuffle  using the above random engine. */
				std::ranges::shuffle(m_permutations, engine);

				/* Duplicate the permutation vector. */
				m_permutations.insert(m_permutations.end(), m_permutations.begin(), m_permutations.end());
			}

			/**
			 * @brief Generates a noise value.
			 * @param x A value for X axis.
			 * @param y A value for Y axis.
			 * @param z A value for Z axis. Optional for 2D.
			 * @return type_t
			 */
			[[nodiscard]]
			number_t
			generate (number_t x, number_t y, number_t z) noexcept
			{
				/* Find the unit cube that contains the point. */
				auto X = static_cast< unsigned int >(std::floor(x)) & 255;
				auto Y = static_cast< unsigned int >(std::floor(y)) & 255;
				auto Z = static_cast< unsigned int >(std::floor(z)) & 255;

				/* Find relative x, y,z of point in cube. */
				x -= std::floor(x);
				y -= std::floor(y);
				z -= std::floor(z);

				/* Compute fade curves for each of x, y, z. */
				auto u = PerlinNoise::fade(x);
				auto v = PerlinNoise::fade(y);
				auto w = PerlinNoise::fade(z);

				/* Hash coordinates of the 8 cube corners. */
				const auto A = m_permutations[X] + Y;
				const auto AA = m_permutations[A] + Z;
				const auto AB = m_permutations[A + 1] + Z;
				const auto B = m_permutations[X + 1] + Y;
				const auto BA = m_permutations[B] + Z;
				const auto BB = m_permutations[B + 1] + Z;

				/* Adds blended results from 8 corners of cube. */
				auto res = PerlinNoise::linearInterpolation(
					w,
					PerlinNoise::linearInterpolation(
						v,
						PerlinNoise::linearInterpolation(
							u,
							this->grad(m_permutations[AA], x, y, z),
							this->grad(m_permutations[BA], x - 1, y, z)
						),
						PerlinNoise::linearInterpolation(
							u,
							this->grad(m_permutations[AB], x, y - 1, z),
							this->grad(m_permutations[BB], x - 1, y - 1, z)
						)
					),
					PerlinNoise::linearInterpolation(
						v,
						PerlinNoise::linearInterpolation(
							u,
							this->grad(m_permutations[AA + 1], x, y, z - 1),
							this->grad(m_permutations[BA + 1], x - 1, y, z - 1)
						),
						PerlinNoise::linearInterpolation(
							u,
							this->grad(m_permutations[AB + 1], x, y - 1, z - 1),
							this->grad(m_permutations[BB + 1], x - 1, y - 1, z - 1)
						)
					)
				);

				return (res + static_cast< number_t >(1.0)) * static_cast< number_t >(0.5);
			}

			/**
			 * @brief Generates a noise value for 8-bit integer.
			 * @param x A value for X axis.
			 * @param y A value for Y axis.
			 * @return uint8_t
			 */
			[[nodiscard]]
			uint8_t
			generate8bits (number_t x, number_t y) noexcept
			{
				return static_cast< uint8_t >(static_cast< number_t >(256.0) * this->generate(x, y, 0));
			}

		private:

			/**
			 * @brief Performs a fade.
			 * @param t
			 * @return type_t
			 */
			static
			number_t
			fade (number_t t) noexcept
			{
				return t * t * t * (t * (t * 6 - 15) + 10);
			}

			/**
			 * @brief Performs a linear interpolation.
			 * @param t
			 * @param a
			 * @param b
			 * @return type_t
			 */
			static
			number_t
			linearInterpolation (number_t t, number_t a, number_t b) noexcept
			{
				return a + t * (b - a);
			}

			/**
			 * @brief Performs a grad.
			 * @param hash
			 * @param x
			 * @param y
			 * @param z
			 * @return type_t
			 */
			number_t
			grad (unsigned int hash, number_t x, number_t y, number_t z) noexcept
			{
				const auto h = hash & 15;

				/* Convert lower 4 bits of hash into 12 gradient directions. */
				auto u = h < 8 ? x : y;
				auto v = h < 4 ? y : h == 12 || h == 14 ? x : z;

				return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
			}

			std::vector< unsigned int > m_permutations{};
	};
}
