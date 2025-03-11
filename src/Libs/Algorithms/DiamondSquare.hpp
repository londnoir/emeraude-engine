/*
 * src/Libs/Algorithms/DiamondSquare.hpp
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
#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <vector>

/* Local inclusions for usages. */
#include "../Utility.hpp"

namespace EmEn::Libs::Algorithms
{
	/**
	 * @brief Class performing the diamond square algorithm for terrain generation.
	 * @tparam number_t The type of number. Default float.
	 */
	template< typename number_t = float > requires (std::is_arithmetic_v< number_t >)
	class DiamondSquare final
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
			const std::vector< number_t > &
			data () const noexcept
			{
				return m_data;
			}

			/**
			 * @brief Returns a specific point from the generated data.
			 * @param coordX The coordinate in X.
			 * @param coordY The coordinate in Y.
			 * @return type_t
			 */
			number_t
			value (size_t coordX, size_t coordY) noexcept
			{
				return m_data[this->index(coordX, coordY)];
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
					std::cerr << __PRETTY_FUNCTION__ << ", invalid size !" "\n";

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
			 * @brief The index of a point from coordinates.
			 * @param coordX The coordinate in X.
			 * @param coordY The coordinate in Y.
			 * @return size_t
			 */
			[[nodiscard]]
			size_t
			index (size_t coordX, size_t coordY) const noexcept
			{
				return (coordY * m_size) + coordX;
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
				const auto size = static_cast< number_t >(m_size);

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
				for ( size_t coordX = halfSize; coordX < m_size; coordX += size )
				{
					for ( size_t coordY = halfSize; coordY < m_size; coordY += size )
					{
						const auto posX = coordX - halfSize;
						const auto negX = coordX + halfSize;
						const auto negY = coordY - halfSize;
						const auto posY = coordY + halfSize;

						auto average = m_data[this->index(negX, negY)];
						average += m_data[this->index(negX, posY)];
						average += m_data[this->index(posX, posY)];
						average += m_data[this->index(posX, negY)];
						average *= 0.25;

						m_data[this->index(coordX, coordY)] = average + Utility::random(-static_cast< number_t >(halfSize), static_cast< number_t >(halfSize));
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

				for ( size_t coordX = 0; coordX < m_size; coordX += halfSize )
				{
					if ( offset == 0 )
					{
						offset = halfSize;
					}
					else
					{
						offset = 0;
					}

					for ( size_t coordY = offset; coordY < m_size; coordY += size )
					{
						number_t sum = 0;
						size_t count = 0;

						if ( coordX >= halfSize )
						{
							sum += m_data[index(coordX - halfSize, coordY)];
							count++;
						}

						if ( coordX + halfSize < m_size )
						{
							sum += m_data[index(coordX + halfSize, coordY)];
							count++;
						}

						if ( coordY >= halfSize )
						{
							sum += m_data[index(coordX, coordY - halfSize)];
							count++;
						}

						if ( coordY + halfSize < m_size )
						{
							sum += m_data[index(coordX, coordY + halfSize)];
							count++;
						}

						m_data[this->index(coordX, coordY)] = (sum / count) + Utility::random< number_t >(-static_cast< number_t >(halfSize), static_cast< number_t >(halfSize));
					}
				}
			}

			static constexpr auto UseSameValueForCorner = 0;

			size_t m_size{0};
			std::vector< number_t > m_data{};
			std::array< bool, 4 > m_flags{
				false/*UseSameValueForCorner*/,
				false/*UNUSED*/,
				false/*UNUSED*/,
				false/*UNUSED*/
			};
	};
}
