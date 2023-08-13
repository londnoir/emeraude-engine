/*
 * Libraries/WaveFactory/Wave.cpp
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

#include "Wave.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/sndfile.hpp"

namespace Libraries::WaveFactory
{
	// NOLINTBEGIN(cppcoreguidelines-pro-bounds-array-to-pointer-decay, *-magic-numbers)
#ifdef SNDFILE_ENABLED

	template<>
	bool
	Wave< short int >::readFile (const Path::File & filepath) noexcept
	{
		if ( !filepath.exists() )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", file '" << filepath << "' doesn't exist !" "\n";

			return false;
		}

		SF_INFO soundFileInfos;
		soundFileInfos.frames = 0;
		soundFileInfos.samplerate = 0;
		soundFileInfos.channels = 0;
		soundFileInfos.format = 0;
		soundFileInfos.sections = 0;
		soundFileInfos.seekable = 0;

		/* 1. Check file. */
		auto * file = sf_open(to_string(filepath).c_str(), SFM_READ, &soundFileInfos);

		if ( file == nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to open sound file '" << filepath << "' !" "\n";

			return false;
		}

		auto isDataValid = true;

		/* 2. Read information. */
		auto samples = static_cast< size_t >(soundFileInfos.frames);
		auto channels = toChannels(soundFileInfos.channels);
		auto frequency = toFrequency(soundFileInfos.samplerate);

		if ( channels == Channels::Invalid )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", invalid channels !" "\n";

			isDataValid = false;
		}

		if ( frequency == Frequency::Invalid )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", invalid frequency !" "\n";

			isDataValid = false;
		}

#ifdef DEBUG_WAVEFACTORY
		std::cout <<
			"[libsndfile_DEBUG] File loaded.\n" <<
			"\tFrames (Samples) : " << soundFileInfos.frames << '\n' <<
			"\tSample rates (Frequency) : " << soundFileInfos.samplerate << " Hz" << '\n' <<
			"\tDuration : " << ( static_cast< float >(soundFileInfos.frames) / static_cast< float >(soundFileInfos.samplerate) ) << " seconds" << '\n' <<
			"\tChannels : " << soundFileInfos.channels << '\n' <<
			"\tFormat (Bits) : " << soundFileInfos.format << '\n' <<
			"\tSections : " << soundFileInfos.sections << '\n' <<
			"\tSeekable : " << soundFileInfos.seekable << '\n' <<
		std::endl;
#endif

		/* 3. Read data */
		if ( isDataValid )
		{
			if ( this->initialize(samples, channels, frequency) )
			{
				/* NOTE: We use per-frame reading because we expect multichannel sound file. */
				if ( sf_readf_short(file, m_data.data(), soundFileInfos.frames) == soundFileInfos.frames )
				{
					isDataValid = true;
				}
			}
			else
			{
				std::cerr << __PRETTY_FUNCTION__ << ", unable to allocate memory for " << filepath << "\n";

				isDataValid = false;
			}
		}

		sf_close(file);

		return isDataValid;
	}

	template<>
	bool
	Wave< short int >::writeFile (const Path::File & filepath) noexcept
	{
		SF_INFO infos;
		infos.channels = static_cast< int >(m_channels);
		infos.samplerate = static_cast< int >(m_frequency);
		infos.format = SF_FORMAT_PCM_16 | SF_FORMAT_WAV;

		auto * file = sf_open(to_string(filepath).c_str(), SFM_WRITE, &infos);

		if ( file == nullptr )
		{
			std::cerr << __PRETTY_FUNCTION__ << ", unable to open file " << filepath << " for writing !" "\n";

			return false;
		}

		sf_writef_short(file, m_data.data(), static_cast< sf_count_t >(m_data.size()));

		sf_close(file);

		return true;
	}
#endif
	// NOLINTEND(cppcoreguidelines-pro-bounds-array-to-pointer-decay, *-magic-numbers)
}
