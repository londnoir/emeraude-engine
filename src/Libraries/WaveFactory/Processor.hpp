/*
 * src/Libraries/WaveFactory/Processor.hpp
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

/* Local inclusions for usages. */
#include "Libraries/Math/Base.hpp"
#include "Types.hpp"
#include "Wave.hpp"
#include <cstdint>
#include <iostream>

namespace Libraries::WaveFactory
{
	/**
	 * @brief The wave processor class. Used to perform some modification on wave to meet the engine needs.
	 * @note The internal wave format will use floating point number (float).
	 * @TODO This class should be a template to use an arbitrary internal precision type.
	 */
	class Processor final
	{
		public:

			/**
			 * @brief Constructs a default wave processor.
			 */
			Processor () noexcept = default;

			/**
			 * @brief Constructs a wave processor.
			 * @tparam precision_t The precision of the wave. Default int16_t.
			 * @param wave A reference to the wave.
			 */
			template< typename precision_t = int16_t >
			explicit
			Processor (const Wave< precision_t > & wave) noexcept requires (std::is_arithmetic_v< precision_t >)
			{
				if ( convertWaveFormat(wave, m_wave) == 0 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", wave structure was empty !" "\n";
				}
			}

			/**
			 * @brief Destructs the wave processor.
			 */
			~Processor () noexcept = default;

			/**
			 * @brief Deleted copy constructor.
			 */
			Processor (const Processor & copy) = delete;

			/**
			 * @brief Deleted move constructor.
			 */
			Processor (Processor && copy) = delete;

			/**
			 * @brief Deleted assignment operator.
			 */
			Processor & operator= (const Processor & other) = delete;

			/**
			 * @brief Deleted assignment operator.
			 */
			Processor & operator= (Processor && other) = delete;

			/**
			 * @brief Brings a wave object and convert it to float format for processing.
			 * @tparam precision_t The precision of the wave. Default int16_t.
			 * @param wave A reference to a wave.
			 * @return bool
			 */
			template< typename precision_t = int16_t >
			bool
			fromWave (const Wave< precision_t > & wave) noexcept requires (std::is_arithmetic_v< precision_t >)
			{
				return convertWaveFormat(wave, m_wave) > 0;
			}

			/**
			 * @brief Returns a processed wave object to the desired format.
			 * @tparam precision_t The precision of the wave. Default int16_t.
			 * @param wave A reference to a wave.
			 * @return bool
			 */
			template< typename precision_t = int16_t >
			bool
			toWave (Wave< precision_t > & wave) noexcept requires (std::is_arithmetic_v< precision_t >)
			{
				/* Float sample to request type. */
				return convertWaveFormat(m_wave, wave) > 0;
			}

			/**
			 * @brief Converts the wave from multi-channel to mono channel.
			 * @return bool
			 */
			bool mixDown () noexcept;

			/**
			 * @brief Resamples a wave to a new frequency.
			 * @param frequency The new frequency of the wave.
			 * @return bool
			 */
			bool resample (Frequency frequency) noexcept;

			/**
			 * @brief Generates sinusoidal wave sample.
			 * @tparam number_t The type of number. Default float.
			 * @param dTime The duration time.
			 * @param frequency The frequency of the sinusoidal wave. Default 440.
			 * @param amplitude The amplitude of the sinusoidal wave. Default 0.5.
			 * @return precision_t
			 */
			template< typename number_t = float >
			number_t
			sineWave (number_t dTime, number_t frequency = 440, number_t amplitude = 0.5) noexcept requires (std::is_arithmetic_v< number_t >)
			{
				return amplitude * std::sin(frequency * static_cast< number_t >(2) * Math::Pi< number_t > * dTime);
			}

			/**
			 * @brief Generates square wave sample.
			 * @tparam number_t The type of number. Default float.
			 * @param dTime The duration time.
			 * @param frequency The frequency of the square wave. Default 440.
			 * @param limit The square limite. Default 0.2.
			 * @return precision_t
			 */
			template< typename number_t = float >
			number_t
			squareWave (number_t dTime, number_t frequency = 440, number_t limit = 0.2) requires (std::is_arithmetic_v< number_t >)
			{
				const auto sample = Processor::sineWave(dTime, frequency, 1);

				if ( sample > 0 )
				{
					return limit;
				}

				return -limit;
			}

		private:

			Wave< float > m_wave{};
	};
}
