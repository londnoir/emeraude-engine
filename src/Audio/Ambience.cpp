/*
 * Emeraude/Audio/Ambience.cpp
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

#include "Ambience.hpp"

/* C/C++ standard libraries. */
#include <cmath>

/* Local inclusions */
#include "Tracer.hpp"
#include "Audio/Manager.hpp"
#include "Resources/Manager.hpp"
#include "Utility.hpp"
#include "Constants.hpp"
#include "FastJSON.hpp"

namespace Emeraude::Audio
{
	using namespace Libraries;
	using namespace Libraries::Math;

	Ambience::~Ambience ()
	{
		this->releaseSources();
	}

	bool
	Ambience::isPlaying () const noexcept
	{
		return m_active;
	}

	bool
	Ambience::allocateSources () noexcept
	{
		if ( !m_sounds.empty() )
		{
			if ( m_channelCount == 0 )
			{
				Tracer::warning(ClassId, "Channel count parameter must a least be 1 !");

				return false;
			}

			if ( m_channelCount != m_channels.size() )
			{
				m_channels.clear();

				auto * audioManager = Manager::instance();

				for ( size_t channelIndex = 0; channelIndex < m_channelCount; channelIndex++ )
				{
					auto source = audioManager->requestSource();

					if ( source == nullptr )
						return !m_channels.empty();

					source->setRelativeState(false);
					source->setGain(1.0F);
					source->setReferenceDistance(m_radius * 0.5F);
					source->setMaxDistance(m_radius * 2.0F);

					if ( m_directFilter != nullptr )
						source->enableDirectFilter(m_directFilter);

					m_channels.emplace_back(source);
				}
			}
		}

		if ( m_loopedSoundResource != nullptr )
		{
			m_loopedSource = Manager::instance()->requestSource();

			if ( m_loopedSource == nullptr )
			{
				return false;
			}

			m_loopedSource->setRelativeState(true);
			m_loopedSource->setGain(m_loopedChannelGain);

			if ( m_directFilter != nullptr )
				m_loopedSource->enableDirectFilter(m_directFilter);
		}

		return true;
	}

	void
	Ambience::releaseSources () noexcept
	{
		if ( m_loopedSource != nullptr )
		{
			m_loopedSource->stop();
			m_loopedSource.reset();
		}

		for ( const auto & channel : m_channels )
			channel.getSource()->stop();

		m_channels.clear();
	}

	void
	Ambience::setChannelCount (size_t count) noexcept
	{
		m_channelCount = std::max(1UL, count);
	}

	size_t
	Ambience::channelCount () const noexcept
	{
		return m_channelCount;
	}

	void
	Ambience::setRadius (float radius) noexcept
	{
		m_radius = std::max(1.0F, std::abs(radius));

		for ( const auto & channel : m_channels )
		{
			auto source = channel.getSource();

			source->setReferenceDistance(m_radius * 0.5F);
			source->setMaxDistance(m_radius * 2.0F);
		}
	}

	float
	Ambience::radius () const noexcept
	{
		return m_radius;
	}

	void
	Ambience::setRandomDelayRange (unsigned int delayA, unsigned int delayB) noexcept
	{
		m_minDelay = std::min(delayA, delayB);
		m_maxDelay = std::max(delayA, delayB);
	}

	unsigned int
	Ambience::getRandomDelay () const noexcept
	{
		return Utility::random(m_minDelay, m_maxDelay);
	}

	bool
	Ambience::setLoopSound (const std::shared_ptr< SoundResource > & soundResource, float gain) noexcept
	{
		if ( soundResource == nullptr )
		{
			Tracer::error(ClassId, "The sound resource is null !");

			return false;
		}

		m_loopedSoundResource = soundResource;
		m_loopedChannelGain = gain;

		return true;
	}

	bool
	Ambience::addSound (const AmbienceSound & sound) noexcept
	{
		if ( sound.soundResource() == nullptr )
		{
			Tracer::error(ClassId, "The sound resource is null !");

			return false;
		}

		m_sounds.emplace_back(sound);

		return true;
	}

	bool
	Ambience::addSound (const std::shared_ptr< SoundResource > & sound, float channelGain, bool relative, float minPitch, float maxPitch, float velocity) noexcept
	{
		if ( sound == nullptr )
		{
			Tracer::error(ClassId, "The sound resource is null !");

			return false;
		}

		auto & soundEffect = m_sounds.emplace_back(sound);
		soundEffect.setChannelGain(channelGain);
		soundEffect.setRelativeState(relative);
		soundEffect.setRandomPitchRange(minPitch, maxPitch);
		soundEffect.setRadialVelocity(velocity);

		return true;
	}

	bool
	Ambience::enableDirectFilter (const std::shared_ptr< Filters::Abstract > & filter) noexcept
	{
		m_directFilter = filter;

		if ( m_loopedSource != nullptr )
			if ( !m_loopedSource->enableDirectFilter(filter) )
				return false;

		return !std::any_of(m_channels.cbegin(), m_channels.cend(), [filter] (auto & channel) {
			if ( !channel.getSource()->enableDirectFilter(filter) )
				return true;

			return false;
		});
	}

	void
	Ambience::disableDirectFilter () noexcept
	{
		if ( m_loopedSource != nullptr )
			m_loopedSource->disableDirectFilter();

		for ( const auto & channel : m_channels )
			channel.getSource()->disableDirectFilter();

		m_directFilter.reset();
	}

	void
	Ambience::start () noexcept
	{
		if ( m_active )
			return;

		if ( m_loopedSoundResource == nullptr && m_sounds.empty() )
		{
			Tracer::warning(ClassId, "No sound effect in Ambience ! Cancelling ...");

			return;
		}

		if ( this->allocateSources() )
		{
			if ( m_loopedSource != nullptr && m_loopedSoundResource != nullptr )
				m_loopedSource->play(m_loopedSoundResource.get(), Source::PlayMode::Loop);

			for ( auto & channel : m_channels )
				channel.setTimeBeforeNextPlay(this->getRandomDelay());

			m_active = true;
		}
	}

	void
	Ambience::stop () noexcept
	{
		if ( !m_active )
			return;

		m_active = false;

		this->releaseSources();
	}

	void
	Ambience::update () noexcept
	{
		if ( !m_active )
			return;

		for ( auto & channel : m_channels )
		{
			/* NOTE : Update the time. */
			if ( !channel.isTimeToPlay() )
			{
				channel.update(static_cast< unsigned int >(EngineUpdateCycleDuration< double > * 1000.0));

				continue;
			}

			/* Time elapsed, we play the sound. */
			const auto soundDuration = channel.play(this->getRandomSound(), m_radius);

			/* Preparing the next new time when the channel will play a sound. */
			channel.setTimeBeforeNextPlay(this->getRandomDelay() + soundDuration);
		}
	}

	bool
	Ambience::loadSoundSet (const Path::File & filepath) noexcept
	{
		const auto root = FastJSON::getRootFromFile(filepath);

		if ( root.isNull() )
		{
			TraceError{ClassId} << "Unable to read file " << filepath << " !";

			return false;
		}

		auto & soundManager = Resources::Manager::instance()->sounds();

		/* 1. Read base sound set information. */
		this->setChannelCount(FastJSON::getUnsignedInteger(root, JKChannelCount, 4UL));
		this->setRadius(FastJSON::getFloat(root, JKRadius, 1024.0F));

		/* 2. Read the loop sound effect. */
		if ( root.isMember(JKLoopSoundEffect) )
		{
			const auto & loopSFX = root[JKLoopSoundEffect];

			if ( loopSFX.isObject() )
			{
				const auto resourceName = FastJSON::getString(loopSFX, JKResourceName);

				if ( !resourceName.empty() )
					this->setLoopSound(soundManager.getResource(resourceName, true), FastJSON::getFloat(loopSFX, JKGain, 0.75F));
				else
					Tracer::error(ClassId, "The loop sound effect resource name is empty or unspecified !");
			}
			else
			{
				TraceError{ClassId} << "The '" << JKLoopSoundEffect << "' section in JSON file is ill-formed !";
			}
		}

		/* 3. Read the sound effect collection. */
		if ( root.isMember(JKSoundEffectCollection) )
		{
			const auto & SFXCollection = root[JKSoundEffectCollection];

			if ( SFXCollection.isArray() )
			{
				for ( const auto & SFX : SFXCollection )
				{
					if ( !SFX.isObject() )
					{
						Tracer::error(ClassId, "A sound effect section in JSON file is ill-formed !");

						continue;
					}

					const auto resourceName = FastJSON::getString(SFX, JKResourceName);

					if ( resourceName.empty() )
					{
						Tracer::error(ClassId, "A sound effect resource name is empty or unspecified !");

						continue;
					}

					const auto gain = FastJSON::getFloat(SFX, JKGain, 0.75F);
					const auto relative = FastJSON::getBoolean(SFX, JKRelative, true);
					const auto minPitch = FastJSON::getFloat(SFX, JKMinimumPitch, 1.0F);
					const auto maxPitch = FastJSON::getFloat(SFX, JKMaximumPitch, 1.0F);
					const auto velocity = FastJSON::getFloat(SFX, JKRadialVelocity, 0.0F);

					if ( !this->addSound(soundManager.getResource(resourceName, true), gain, relative, minPitch, maxPitch, velocity) )
						break;
				}
			}
			else
			{
				TraceError{ClassId} << "The '" << JKSoundEffectCollection << "' section in JSON file is ill-formed !";
			}
		}

		return true;
	}

	void
	Ambience::reset () noexcept
	{
		/* NOTE: Avoid to clear channels to reduce allocation/op cost. */
		//m_channels.clear();
		m_sounds.clear();
		std::shared_ptr< Source > m_loopedSource{};
		m_loopedSoundResource.reset();
		m_directFilter.reset();

		m_loopedChannelGain = 0.75F;
		m_channelCount = 4UL;
		m_radius = 1024.0F;
		m_minDelay = 500;
		m_maxDelay = 3000;
		m_active = false;
	}

	AmbienceSound &
	Ambience::getRandomSound () noexcept
	{
		return m_sounds[Utility::random(0UL, m_sounds.size() - 1)];
	}
}
