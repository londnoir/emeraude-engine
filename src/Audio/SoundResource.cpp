/*
 * Emeraude/Audio/SoundResource.cpp
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

#include "SoundResource.hpp"

/* Local inclusions */
#include "Manager.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"
#include "WaveFactory/Processor.hpp"

/* Defining the resource manager ClassId. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Audio::SoundResource >::ClassId{"SoundContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Audio::SoundResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Audio
{
	using namespace Libraries;

	const size_t SoundResource::ClassUID{Observable::getClassUID()};

	SoundResource::SoundResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits)
	{

	}

	bool
	SoundResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	size_t
	SoundResource::streamable () const noexcept
	{
		return 0;
	}

	std::shared_ptr< const Buffer >
	SoundResource::buffer (size_t /*bufferIndex*/) const noexcept
	{
		return m_buffer;
	}

	const char *
	SoundResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	SoundResource::load () noexcept
	{
		if ( !Manager::isAudioAvailable() )
		{
			return true;
		}

		if ( !this->beginLoading() )
		{
			return false;
		}

		const auto frequencyPlayback = Manager::instance()->frequencyPlayback();

		auto oneSecond = 1 * static_cast< size_t >(frequencyPlayback);

		if ( !m_localData.initialize(oneSecond, WaveFactory::Channels::Mono, frequencyPlayback) )
		{
			return this->setLoadSuccess(false);
		}

		if ( !m_localData.generateNoise() )
		{
			return this->setLoadSuccess(false);
		}

		return this->setLoadSuccess(true);
	}

	bool
	SoundResource::load (const Path::File & filepath) noexcept
	{
		if ( !Manager::isAudioAvailable() )
		{
			return true;
		}

		if ( !this->beginLoading() )
		{
			return false;
		}

		if ( !m_localData.readFile(filepath) )
		{
			TraceError{ClassId} << "Unable to load the sound file '" << filepath << "' !";

			return this->setLoadSuccess(false);
		}

		const auto frequencyPlayback = Manager::instance()->frequencyPlayback();

		/* Checks if the sound is valid for the engine.
		 * It must be mono and meet the audio engine frequency. */
		if ( m_localData.channels() != WaveFactory::Channels::Mono || m_localData.frequency() != frequencyPlayback )
		{
			/* Copy the buffer in float (single precision) format. */
			WaveFactory::Processor processor{m_localData};

			/* Launch a mix down process... */
			if ( m_localData.channels() != WaveFactory::Channels::Mono )
			{
				TraceInfo{ClassId} << "The sound '" << this->name() << "' is multichannel ! Performing a mix down ...";

				if ( !processor.mixDown() )
				{
					Tracer::error(ClassId, "Mix down failed !");

					return this->setLoadSuccess(false);
				}
			}

			/* Launch a resampling process ... */
			if ( m_localData.frequency() != frequencyPlayback )
			{
				TraceWarning{ClassId} <<
					"Sound '" << this->name() << "' frequency mismatch the system ! "
					"Resampling the wave from " << static_cast< int >(m_localData.frequency()) << "Hz to " << static_cast< int >(frequencyPlayback) << "Hz ...";

				if ( !processor.resample(frequencyPlayback) )
				{
					TraceError{ClassId} << "Unable to resample the wave to " << static_cast< int >(frequencyPlayback) << "Hz !";

					return this->setLoadSuccess(false);
				}
			}

			/* Gets back the buffer in 16bits integer format. */
			if ( !processor.toWave(m_localData) )
			{
				Tracer::error(ClassId, "Unable to copy the fixed wave format !");

				return this->setLoadSuccess(false);
			}
		}

		return this->setLoadSuccess(true);
	}

	bool
	SoundResource::load (const Json::Value & /*data*/) noexcept
	{
		if ( !Manager::isAudioAvailable() )
		{
			return true;
		}

		if ( !this->beginLoading() )
		{
			return false;
		}

		/* TODO: Empty function. */

		return this->setLoadSuccess(false);
	}

	const WaveFactory::Wave< short int > &
	SoundResource::localData () const noexcept
	{
		return m_localData;
	}

	WaveFactory::Wave< short int > &
	SoundResource::localData () noexcept
	{
		return m_localData;
	}

	bool
	SoundResource::onDependenciesLoaded () noexcept
	{
		m_buffer = std::make_shared< Buffer >();

		if ( !m_buffer->isCreated() || !m_buffer->feedData(m_localData, 0, 0) )
		{
			Tracer::error(ClassId, "Unable to load Buffer in audio memory !");

			return false;
		}

		return true;
	}

	std::shared_ptr< SoundResource >
	SoundResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->sounds().getResource(resourceName, directLoad);
	}

	std::shared_ptr< SoundResource >
	SoundResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->sounds().getDefaultResource();
	}
}
