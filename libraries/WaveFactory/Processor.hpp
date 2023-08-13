/*
 * Libraries/WaveFactory/Processor.hpp
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

/* Local inclusions for usages. */
#include "Math/Base.hpp"
#include "Wave.hpp"

namespace Libraries::WaveFactory
{
	// NOLINTBEGIN(*-magic-numbers)

	/**
	 * @brief The wave processor class. Used to perform some modification on wave to meet the engine needs.
	 * @note The internal wave format will use floating point number (float).
	 * @todo This class should be a template to use an arbitrary internal precision type.
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
			 * @tparam type_t The precision of the wave.
			 * @param wave A reference to the wave.
			 */
			template< typename type_t >
			explicit
			Processor (const Wave< type_t > & wave) noexcept
			{
				if ( convertWaveFormat(wave, m_wave) == 0 )
				{
					std::cerr << __PRETTY_FUNCTION__ << ", wave structure was empty !" << std::endl;
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
			 * @tparam type_t The precision of the wave.
			 * @param wave A reference to a wave.
			 * @return bool
			 */
			template< typename type_t >
			bool
			fromWave (const Wave< type_t > & wave) noexcept
			{
				return convertWaveFormat(wave, m_wave) > 0;
			}

			/**
			 * @brief Returns a processed wave object to the desired format.
			 * @tparam type_t The precision of the wave.
			 * @param wave A reference to a wave.
			 * @return bool
			 */
			template< typename type_t >
			bool
			toWave (Wave< type_t > & wave) noexcept
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
			 * @tparam type_t The precision of the wave.
			 * @param dTime The duration time.
			 * @param frequency The frequency of the sinusoidal wave. Default 440.
			 * @param amplitude The amplitude of the sinusoidal wave. Default 0.5.
			 * @return type_t
			 */
			template< typename type_t >
			type_t
			sineWave (type_t dTime, type_t frequency = 440, type_t amplitude = 0.5) noexcept
			{
				return amplitude * std::sin(frequency * static_cast< type_t >(2) * Math::Pi< type_t > * dTime);
			}

			/**
			 * @brief Generates square wave sample.
			 * @tparam type_t The precision of the wave.
			 * @param dTime The duration time.
			 * @param frequency The frequency of the square wave. Default 440.
			 * @param limit The square limite. Default 0.2.
			 * @return type_t
			 */
			template< typename type_t >
			type_t
			squareWave (type_t dTime, type_t frequency = 440, type_t limit = 0.2)
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
	// NOLINTEND(*-magic-numbers)
}
