/*
 * Libraries/WaveFactory/Processor.cpp
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

#include "Processor.hpp"

/* C/C++ standard libraries. */
#include <vector>

/* Third-party libraries */
#include "Third-Party-Inclusion/samplerate.hpp"

namespace Libraries::WaveFactory
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

	bool
	Processor::mixDown () noexcept
	{
		if ( !m_wave.isValid() )
		{
			std::cerr << __PRETTY_FUNCTION__ << "No wave to process !" "\n";

			return false;
		}

		/* Checks channel and convert it to an integer. */
		if ( m_wave.channels() == Channels::Mono )
		{
			return true;
		}

		/* Gets the right channel count in a size_t. */
		auto channelsCount = static_cast< size_t >(m_wave.channels());

		/* Reserve a temporary buffer. */
		const auto size = m_wave.m_data.size();

		std::vector< float > temporaryBuffer(size / channelsCount);

		/* Stat the copy of the mix down of the wave. */
		size_t monoIndex = 0;

		for ( size_t index = 0; index < size; index += channelsCount )
		{
			auto value = 0.0F;

			for ( size_t channel = 0; channel < channelsCount; channel++ )
			{
				value += m_wave.m_data[index + channel];
			}

			temporaryBuffer[monoIndex] = value / static_cast< float >(channelsCount);

			monoIndex++;
		}

		/* Swap data. */
		m_wave.m_data.swap(temporaryBuffer);
		m_wave.m_channels = Channels::Mono;

		return true;
	}

	bool
	Processor::resample (Frequency frequency) noexcept
	{
#ifdef SAMPLERATE_ENABLED
		if ( !m_wave.isValid() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", no wave to resample !" "\n";

			return false;
		}

		if ( m_wave.frequency() == frequency )
		{
			std::cout << __PRETTY_FUNCTION__ << ", the frequency is already at " << static_cast< int >(frequency) << " Hz !" "\n";

			return true;
		}

		const auto ratio = static_cast< double >(frequency) / static_cast< double >(m_wave.frequency());

		/* Reserve a temporary buffer. */
		const auto newSampleCount = static_cast< size_t >(std::ceil(static_cast< double >(m_wave.samplesCount()) * ratio));

		std::vector< float > temporaryBuffer(newSampleCount * static_cast< size_t >(m_wave.channels()), 0.0F);

		SRC_DATA data;
		/* A pointer to the input data samples. */
		data.data_in = m_wave.data();
		/* The number of frames of data pointed to by data_in. */
		data.input_frames = static_cast< long >(m_wave.samplesCount());
		/* A pointer to the output data samples. */
		data.data_out = temporaryBuffer.data();
		/* Maximum number of frames pointer to "data_out". */
		data.output_frames = static_cast< long >(newSampleCount);
		/* Equal to output_sample_rate / input_sample_rate. */
		data.src_ratio = ratio;

		auto error = src_simple(&data, SRC_SINC_BEST_QUALITY, static_cast< int >(m_wave.channels()));

		if ( error > 0 )
		{
			std::cerr << src_strerror(error) << "\n";

			return false;
		}

		/* Swap data. */
		m_wave.m_data.swap(temporaryBuffer);
		m_wave.m_frequency = frequency;

		return true;
#else
		std::cerr << __PRETTY_FUNCTION__ << ", libsamplerate is not available !" "\n";

		return false;
#endif
	}

	// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay)
}
