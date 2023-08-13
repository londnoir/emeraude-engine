/*
 * Libraries/DiamondSquare.hpp
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
#include <iostream>
#include <vector>

/* Local inclusions */
#include "Utility.hpp"

namespace Libraries
{
	// NOLINTBEGIN(readability-identifier-length, *-magic-numbers)
	/**
	 * @brief Class performing the diamond square algorithm for terrain generation.
	 * @tparam type_t The type of data to randomize.
	 */
	template< typename type_t >
	class [[maybe_unused]] DiamondSquare final
	{
		public:

			/**
			 * @brief Constructs a diamond square processor.
			 * @param size The size of pattern.
			 * @param useSameValueForCorner Use the same value for corner. Default false.
			 */
			explicit DiamondSquare (size_t size, bool useSameValueForCorner = false) noexcept
				: m_size(size)
			{
				m_flags[UseSameValueForCorner] = useSameValueForCorner;
			}

			/**
			 * @brief Returns the size of the diamond square pattern.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			size () const noexcept
			{
				return m_size;
			}

			/**
			 * @brief Returns the generated data.
			 * @return const std::vector< type_t > &
			 */
			[[nodiscard]]
			const std::vector< type_t > &
			data () const noexcept
			{
				return m_data;
			}

			/**
			 * @brief Returns a specific point from the generated data.
			 * @param x The coordinate in X.
			 * @param y The coordinate in Y.
			 * @return type_t
			 */
			type_t
			value (size_t x, size_t y) noexcept
			{
				return m_data[this->index(x, y)];
			}

			/**
			 * @brief Generates the noise data.
			 * @param seed seed The seed number. Default 1.
			 * @return bool
			 */
			bool
			generate (unsigned int seed = 1) noexcept
			{
				if ( !this->initializeData() )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", invalid size !" << std::endl;

					return false;
				}

				std::srand(seed);

				this->cornerStep();

				auto currentSize = m_size - 1;

				while ( currentSize > 1 )
				{
					auto halfSize = currentSize / 2;

					/* Diamond step. The centers of each tile. */
					this->diamondStep(currentSize, halfSize);

					/* Square step. The midpoints of the sides. */
					this->squareStep(currentSize, halfSize);

					currentSize = halfSize;
				}

				return true;
			}

		private:

			/**
			 * @return The index of a point from coordinates.
			 * @param x The coordinate in X.
			 * @param y The coordinate in Y.
			 * @return size_t
			 */
			[[nodiscard]]
			inline
			size_t
			index (size_t x, size_t y) const noexcept
			{
				return (y * m_size) + x;
			}

			/**
			 * @brief Initializes the data before noise generation.
			 * @return bool
			 */
			bool
			initializeData () noexcept
			{
				if ( m_size < 3 )
				{
					return false;
				}

				if ( m_size % 2 == 0 )
				{
					m_size++;
				}

				m_data.resize(m_size * m_size);

				return true;
			}

			/**
			 * @brief Performs the corner step.
			 * @return void
			 */
			void
			cornerStep () noexcept
			{
				const auto size = static_cast< type_t >(m_size);

				if ( m_flags[UseSameValueForCorner] )
				{
					const auto randValue = Utility::random(-size, size);

					m_data[0] = randValue;
					m_data[m_size - 1] = randValue;
					m_data[m_size * (m_size - 1)] = randValue;
					m_data[(m_size * m_size) - 1] = randValue;
				}
				else
				{
					m_data[0] = Utility::random(-size, size);
					m_data[m_size - 1] = Utility::random(-size, size);
					m_data[m_size * (m_size - 1)] = Utility::random(-size, size);
					m_data[(m_size * m_size) - 1] = Utility::random(-size, size);
				}
			}

			/**
			 * @brief Performs the diamond step.
			 * @param size
			 * @param halfSize
			 * @return void
			 */
			void
			diamondStep (size_t size, size_t halfSize) noexcept
			{
				for ( auto x = halfSize; x < m_size; x += size )
				{
					for ( auto y = halfSize; y < m_size; y += size )
					{
						const auto posX = x - halfSize;
						const auto negX = x + halfSize;
						const auto negY = y - halfSize;
						const auto posY = y + halfSize;

						auto average = m_data[this->index(negX, negY)];
						average += m_data[this->index(negX, posY)];
						average += m_data[this->index(posX, posY)];
						average += m_data[this->index(posX, negY)];
						average *= 0.25;

						m_data[this->index(x, y)] = average + Utility::random(-static_cast< type_t >(halfSize), static_cast< type_t >(halfSize));
					}
				}
			}

			/**
			 * @brief Performs the square step.
			 * @param size
			 * @param halfSize
			 * @return void
			 */
			void
			squareStep (size_t size, size_t halfSize) noexcept
			{
				size_t offset = 0;

				for ( size_t x = 0; x < m_size; x += halfSize )
				{
					if ( offset == 0 )
					{
						offset = halfSize;
					}
					else
					{
						offset = 0;
					}

					for ( auto y = offset; y < m_size; y += size )
					{
						type_t sum = 0;

						size_t n = 0;

						if ( x >= halfSize )
						{
							sum += m_data[index(x - halfSize, y)];
							n++;
						}

						if ( x + halfSize < m_size )
						{
							sum += m_data[index(x + halfSize, y)];
							n++;
						}

						if ( y >= halfSize )
						{
							sum += m_data[index(x, y - halfSize)];
							n++;
						}

						if ( y + halfSize < m_size )
						{
							sum += m_data[index(x, y + halfSize)];
							n++;
						}

						m_data[this->index(x, y)] = (sum / n) + Utility::random< type_t >(-static_cast< type_t >(halfSize), static_cast< type_t >(halfSize));
					}
				}
			}

			static constexpr auto UseSameValueForCorner = 0;

			size_t m_size{0};
			std::vector< type_t > m_data{};
			std::array< bool, 4 > m_flags{
				false/*UseSameValueForCorner*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
	//NOLINTEND(readability-identifier-length, *-magic-numbers)
}
