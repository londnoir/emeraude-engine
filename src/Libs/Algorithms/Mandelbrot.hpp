/*
 * src/Libs/Algorithms/Mandelbrot.hpp
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
#include <functional>
#include <type_traits>

/* Local inclusions. */
#include "../PixelFactory/Pixmap.hpp"

namespace EmEn::Libs::Algorithms
{
	/**
	 * @brief The Mandelbrot algorithm class.
	 * @tparam number_t The type of number. Default float.
	 */
	template< typename number_t = float >
	requires (std::is_arithmetic_v< number_t >)
	class Mandelbrot final
	{
		public:

			using colorize = std::function< void (PixelFactory::Pixmap< number_t > &, unsigned int, unsigned int, int, int) >;

			/**
			 * @brief Constructs the mandelbrot algorithm.
			 * @param width The width of the pixmap.
			 * @param height The height of the pixma.
			 * @param channels The number of color. Default RBG.
			 */
			Mandelbrot (size_t width, size_t height, PixelFactory::ChannelMode channels = PixelFactory::ChannelMode::RGB) noexcept
				: m_pixmap(width, height, channels)
			{

			}

			/**
			 * @brief
			 * @param function
			 * @return void
			 */
			void
			setColorizationMethod (const colorize & function)
			{
				m_colorizationFunction = function;
			}

			/**
			 * @brief Executes the generation.
			 * @param minReal
			 * @param maxReal
			 * @param minImaginary
			 * @param maxImaginary
			 * @param maxIterations
			 * @return void
			 */
			void
			execute (float minReal = -1.5F, float maxReal = 0.7F, float minImaginary = -1.0F, float maxImaginary = 1.0F, unsigned int maxIterations = 1000) noexcept
			{
				for ( size_t y = 0; y < m_pixmap.height(); y++ )
				{
					const auto ci = Mandelbrot::map(y, m_pixmap.height(), minImaginary, maxImaginary);

					for ( size_t x = 0; x < m_pixmap.width(); x++ )
					{
						const auto cr = Mandelbrot::map(x, m_pixmap.width(), minReal, maxReal);

						m_colorizationFunction(m_pixmap, x, y, Mandelbrot::findMandelbrot(cr, ci, maxIterations), maxIterations);
					}
				}
			}

			/**
			 * @brief Returns the generated pixmap.
			 * @return const PixelFactory::Pixmap< type_t > &
			 */
			[[nodiscard]]
			const PixelFactory::Pixmap< number_t > &
			get () noexcept
			{
				return m_pixmap;
			}

		private:

			/**
			 * @brief
			 * @param cr
			 * @param ci
			 * @param maxIterations
			 * @return int
			 */
			static
			int
			findMandelbrot (float cr, float ci, int maxIterations) noexcept
			{
				auto i = 0;

				auto zr = 0.0F;
				auto zi = 0.0F;

				while ( i < maxIterations && zr * zr + zi * zi < 4.0F )
				{
					const auto tmp = zr * zr - zi * zi + cr;

					zi = 2.0F * zr * zi + ci;

					zr = tmp;

					i++;
				}

				return i;
			}

			/**
			 * @brief
			 * @param offset
			 * @param dimension
			 * @param min
			 * @param max
			 * @return float
			 */
			static
			float
			map (unsigned int offset, unsigned int dimension, float min, float max) noexcept
			{
				const auto range = max - min;

				return static_cast< float >(offset) * (range / static_cast< float >(dimension)) + min;
			}

			PixelFactory::Pixmap< number_t > m_pixmap;
			colorize m_colorizationFunction{[] (PixelFactory::Pixmap< number_t > & pixmap, unsigned int x, unsigned int y, int n, int) {
				auto cmp = static_cast< uint8_t>(n % 256);
				pixmap.setPixel(x, y, {cmp, cmp, cmp});
			}};
	};
}
