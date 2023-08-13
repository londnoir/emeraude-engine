/*
 * Emeraude/Audio/MusicResource.cpp
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

#include "MusicResource.hpp"

/* Local inclusions */
#include "Manager.hpp"
#include "Resources/Manager.hpp"
#include "Tracer.hpp"
#include "WaveFactory/Processor.hpp"

/* Third-party libraries */
#include "Third-Party-Inclusion/taglib.hpp"

/* Defining the resource manager class id. */
template<>
const char * const Emeraude::Resources::Container< Emeraude::Audio::MusicResource >::ClassId{"MusicContainer"};

/* Defining the resource manager ClassUID. */
template<>
const size_t Emeraude::Resources::Container< Emeraude::Audio::MusicResource >::ClassUID{Observable::getClassUID()};

namespace Emeraude::Audio
{
	using namespace Libraries;

	const size_t MusicResource::ClassUID{Observable::getClassUID()};

	MusicResource::MusicResource (const std::string & name, uint32_t resourceFlagBits) noexcept
		: ResourceTrait(name, resourceFlagBits), m_title("Unknown"), m_artist("Unknown")
	{

	}

	bool
	MusicResource::is (size_t classUID) const noexcept
	{
		if ( ClassUID == 0UL )
		{
			Tracer::error(ClassId, "The unique class identifier has not been set !");

			return false;
		}

		return classUID == ClassUID;
	}

	bool
	MusicResource::onDependenciesLoaded () noexcept
	{
		const auto chunkSize = Manager::instance()->musicChunkSize();

		const auto chunkCount = m_localData.chunkCount(chunkSize);

		m_buffers.resize(chunkCount);

		for ( size_t chunkIndex = 0; chunkIndex < chunkCount; chunkIndex++ )
		{
			m_buffers[chunkIndex] = std::make_shared< Buffer >();

			if ( !m_buffers[chunkIndex]->isCreated() || !m_buffers[chunkIndex]->feedData(m_localData, chunkIndex, chunkSize) )
			{
				Tracer::error(ClassId, "Unable to load buffer in audio memory !");

				return false;
			}
		}

		return true;
	}

	size_t
	MusicResource::streamable () const noexcept
	{
		return m_buffers.size();
	}

	std::shared_ptr< const Buffer >
	MusicResource::buffer (size_t bufferIndex) const noexcept
	{
		return m_buffers.at(bufferIndex);
	}

#if defined(TAGLIB_ENABLED) && !defined(__clang__)
	void
	MusicResource::readMetaData (const std::string & filepath) noexcept
	{
		TagLib::FileRef file(filepath.c_str());

		if ( !file.isNull() )
		{
			auto tag = file.tag();

			if ( tag != nullptr )
			{
				m_title = tag->title().to8Bit(true);
				m_artist = tag->artist().to8Bit(true);
			}
			else
			{
				Tracer::warning(ClassId, "Unable to get audio tag !");
			}
		}
		else
		{
			Tracer::error(ClassId, Blob() << "Unable to read file '" << filepath << "' for audio tag extraction.");
		}
	}
#else
	void
	MusicResource::readMetaData (const std::string & /*filepath*/) noexcept
	{
		m_title = "UnknownTitle";
		m_artist = "UnknownArtist";
	}
#endif

	const char *
	MusicResource::classLabel () const noexcept
	{
		return ClassId;
	}

	bool
	MusicResource::load () noexcept
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
		const auto tenSeconds = 10 * static_cast< size_t >(frequencyPlayback);

		if ( !m_localData.initialize(tenSeconds, WaveFactory::Channels::Stereo, frequencyPlayback) )
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
	MusicResource::load (const Path::File & filepath) noexcept
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
			TraceError{ClassId} << "Unable to load the music file '" << filepath << "' !";

			return this->setLoadSuccess(false);
		}

		const auto frequencyPlayback = Manager::instance()->frequencyPlayback();

		/* Checks frequency for playback within audio engine. */
		if ( m_localData.frequency() != frequencyPlayback )
		{
			TraceWarning{ClassId} <<
				"Music '" << this->name() << "' frequency mismatch the system ! "
				"Resampling the wave from " << static_cast< int >(m_localData.frequency()) << "Hz to " << static_cast< int >(frequencyPlayback) << "Hz ...";

			/* Copy the buffer in float (single precision) format. */
			WaveFactory::Processor processor(m_localData);

			/* Launch a mix down process ... */
			/* FIXME: If music is not stereo, so mono or 5.1 for instance set it to a stereo wave format. */
			/*if ( m_localData.channels() != WaveFactory::Channels::Stereo )
			{
				Tracer::info(ClassId, Blob() << "The sound '" << this->name() << "' is multichannel ! Performing a mix down ...");

				if ( !processor.mixDown() )
				{
					Tracer::error(ClassId, "Mix down failed !");

					return this->setLoadSuccess(false);
				}
			}*/

			/* Launch a resampling process ... */
			if ( !processor.resample(frequencyPlayback) )
			{
				TraceError{ClassId} << "Unable to resample the wave to " << static_cast< int >(frequencyPlayback) << "Hz !";

				return this->setLoadSuccess(false);
			}

			/* Gets back the buffer in 16bits integer format. */
			if ( !processor.toWave(m_localData) )
			{
				Tracer::error(ClassId, "Unable to copy the fixed wave format !");

				return this->setLoadSuccess(false);
			}
		}

		/* Read optional metadata from soundtrack if available. */
		this->readMetaData(to_string(filepath));

		return this->setLoadSuccess(true);
	}

	bool
	MusicResource::load (const Json::Value & /*data*/) noexcept
	{
		if ( !Manager::isAudioAvailable() )
		{
			return true;
		}

		if ( !this->beginLoading() )
		{
			return false;
		}

		Tracer::warning(ClassId, "FIXME: This function is not available yet !");

		return this->setLoadSuccess(false);
	}

	const WaveFactory::Wave< short int > &
	MusicResource::localData () const noexcept
	{
		return m_localData;
	}

	WaveFactory::Wave< short int > &
	MusicResource::localData () noexcept
	{
		return m_localData;
	}

	const std::string &
	MusicResource::title () const noexcept
	{
		return m_title;
	}

	const std::string &
	MusicResource::artist () const noexcept
	{
		return m_artist;
	}

	std::shared_ptr< MusicResource >
	MusicResource::get (const std::string & resourceName, bool directLoad) noexcept
	{
		return Resources::Manager::instance()->musics().getResource(resourceName, directLoad);
	}

	std::shared_ptr< MusicResource >
	MusicResource::getDefault () noexcept
	{
		return Resources::Manager::instance()->musics().getDefaultResource();
	}
}
