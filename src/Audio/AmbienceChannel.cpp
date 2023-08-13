/*
 * Emeraude/Audio/AmbienceChannel.cpp
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

#include "AmbienceChannel.hpp"

namespace Emeraude::Audio
{
	using namespace Libraries;
	using namespace Libraries::Math;

	AmbienceChannel::AmbienceChannel (const std::shared_ptr< Source > & source) noexcept
		: m_source(source)
	{

	}

	std::shared_ptr< Source >
	AmbienceChannel::getSource () const noexcept
	{
		return m_source;
	}

	void
	AmbienceChannel::setTimeBeforeNextPlay (unsigned int time) noexcept
	{
		m_timeBeforeNextPlay = time;
		m_time = 0;
	}

	[[nodiscard]]
	unsigned int
	AmbienceChannel::play (const AmbienceSound & sound, float radius) noexcept
	{
		/* Randomize the source parameters. */
		const auto pitch = sound.getRandomPitch();

		m_position = Vector< 3, float >::trueRandom(-radius, radius);
		m_velocity = sound.getRandomVelocity();

		if ( !sound.isRelative() )
		{
			Vector< 3, float > listenerPosition;

			alGetListenerfv(AL_POSITION, listenerPosition.data());

			m_position += listenerPosition;
		}

		/* Configure the ambience channel. */
		if ( sound.useVelocityRandomization() )
			this->setVelocity(sound.getRandomVelocity());

		/* Configure of the audio source. */
		m_source->setRelativeState(sound.isRelative());
		m_source->setPosition(m_position);
		m_source->setVelocity(m_velocity);
		m_source->setDirection(Vector< 3, float >::trueRandom(-1.0F, 1.0F).normalize());
		m_source->setGain(sound.channelGain());
		m_source->setPitch(pitch);

		m_source->play(sound.soundResource().get(), Source::PlayMode::Once);

		return static_cast< unsigned int >(sound.soundResource()->localData().milliseconds() / pitch);
	}

	void
	AmbienceChannel::update (unsigned int time) noexcept
	{
		m_time += time;

		/* Update the position if there is a fake velocity enabled. */
		if ( !m_velocity.isNull() )
		{
			m_position += m_velocity;
			m_source->setPosition(m_position);
		}
	}

	bool
	AmbienceChannel::isTimeToPlay () const noexcept
	{
		return m_time > m_timeBeforeNextPlay;
	}

	void
	AmbienceChannel::setPosition (const Vector< 3, float > & position) noexcept
	{
		m_velocity = position;
	}

	void
	AmbienceChannel::setVelocity (const Vector< 3, float > & velocity) noexcept
	{
		m_velocity = velocity;
	}

	void
	AmbienceChannel::disableVelocity () noexcept
	{
		m_velocity.reset();
	}
}
