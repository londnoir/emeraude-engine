/*
 * Emeraude/Audio/AmbienceSound.cpp
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

#include "AmbienceSound.hpp"

/* Local inclusions */
#include "Utility.hpp"

namespace Emeraude::Audio
{
	using namespace Libraries;
	using namespace Libraries::Math;

	AmbienceSound::AmbienceSound (const std::shared_ptr< SoundResource > & soundEffect) noexcept
		: m_soundEffect(soundEffect)
	{

	}

	std::shared_ptr< SoundResource >
	AmbienceSound::soundResource () const noexcept
	{
		return m_soundEffect;
	}

	void
	AmbienceSound::setChannelGain (float gain) noexcept
	{
		if ( gain >= 0.0F )
			m_channelGain = gain;
	}

	float
	AmbienceSound::channelGain () const noexcept
	{
		return m_channelGain;
	}

	void
	AmbienceSound::setRandomPitchRange (float pitchA, float pitchB) noexcept
	{
		m_minimumPitch = Utility::ifZero(std::min(pitchA, pitchB), 1.0F);
		m_maximumPitch = Utility::ifZero(std::max(pitchA, pitchB), 1.0F);
	}

	float
	AmbienceSound::minimumPitch () const noexcept
	{
		return m_minimumPitch;
	}

	float
	AmbienceSound::maximumPitch () const noexcept
	{
		return m_maximumPitch;
	}

	float
	AmbienceSound::getRandomPitch () const noexcept
	{
		if ( m_minimumPitch == m_maximumPitch )
			return m_minimumPitch;

		return Utility::trueRandom(m_minimumPitch, m_maximumPitch);
	}

	void
	AmbienceSound::setRadialVelocity (float velocity) noexcept
	{
		m_radialVelocity = std::abs(velocity);
	}

	float
	AmbienceSound::radialVelocity () const noexcept
	{
		return m_radialVelocity;
	}

	Vector< 3, float >
	AmbienceSound::getRandomVelocity () const noexcept
	{
		if ( !this->useVelocityRandomization() )
			return {};

		return Vector< 3, float >::trueRandom(-m_radialVelocity, -m_radialVelocity);
	}

	void
	AmbienceSound::setRelativeState (bool state) noexcept
	{
		m_relative = state;
	}

	bool
	AmbienceSound::isRelative () const noexcept
	{
		return m_relative;
	}

	bool
	AmbienceSound::usePitchRandomization () const noexcept
	{
		return m_minimumPitch != 1.0F && m_maximumPitch != 1.0F;
	}

	bool
	AmbienceSound::useVelocityRandomization () const noexcept
	{
		return m_radialVelocity > 0.0F;
	}
}
