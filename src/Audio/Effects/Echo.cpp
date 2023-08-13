/*
 * Emeraude/Audio/Effects/Echo.cpp
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

#include "Echo.hpp"

/* Local inclusions */
#include "Tracer.hpp"
#include <Audio/OpenAL.EFX.hpp>
#include "Audio/Utility.hpp"

namespace Emeraude::Audio::Effects
{
	using namespace Libraries;

	Echo::Echo () noexcept
		: Abstract()
	{
		if ( this->identifier() == 0 )
			return;

		EFX::alEffecti(this->identifier(), AL_EFFECT_TYPE, AL_EFFECT_ECHO);

		if ( alGetErrors("alEffecti()", __FILE__, __LINE__) )
			Tracer::error(ClassId, "Unable to generate OpenAL Echo effect !");
	}

	void
	Echo::resetProperties () noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		EFX::alEffectf(this->identifier(), AL_ECHO_DELAY, AL_ECHO_DEFAULT_DELAY);
		EFX::alEffectf(this->identifier(), AL_ECHO_LRDELAY, AL_ECHO_DEFAULT_LRDELAY);
		EFX::alEffectf(this->identifier(), AL_ECHO_DAMPING, AL_ECHO_DEFAULT_DAMPING);
		EFX::alEffectf(this->identifier(), AL_ECHO_SPREAD, AL_ECHO_DEFAULT_SPREAD);
	}

	void
	Echo::setDelay (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_ECHO_MIN_DELAY || value > AL_ECHO_MAX_DELAY )
		{
			Tracer::warning(ClassId, Blob() << "Delay must be between " << AL_ECHO_MIN_DELAY << " and " << AL_ECHO_MAX_DELAY << ".");

			return;
		}

		EFX::alEffectf(this->identifier(), AL_ECHO_DELAY, value);
	}

	void
	Echo::setLRDelay (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_ECHO_MIN_LRDELAY || value > AL_ECHO_MAX_LRDELAY )
		{
			Tracer::warning(ClassId, Blob() << "LR Delay must be between " << AL_ECHO_MIN_LRDELAY << " and " << AL_ECHO_MAX_LRDELAY << ".");

			return;
		}

		EFX::alEffectf(this->identifier(), AL_ECHO_LRDELAY, value);
	}

	void
	Echo::setDamping (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_ECHO_MIN_DAMPING || value > AL_ECHO_MAX_DAMPING )
		{
			Tracer::warning(ClassId, Blob() << "Damping must be between " << AL_ECHO_MIN_DAMPING << " and " << AL_ECHO_MAX_DAMPING << ".");

			return;
		}

		EFX::alEffectf(this->identifier(), AL_ECHO_DAMPING, value);
	}

	void
	Echo::setFeedBack (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_ECHO_MIN_FEEDBACK || value > AL_ECHO_MAX_FEEDBACK )
		{
			Tracer::warning(ClassId, Blob() << "Feedback must be between " << AL_ECHO_MIN_FEEDBACK << " and " << AL_ECHO_MAX_FEEDBACK << ".");

			return;
		}

		EFX::alEffectf(this->identifier(), AL_ECHO_FEEDBACK, value);
	}

	void
	Echo::setSpread (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_ECHO_MIN_SPREAD || value > AL_ECHO_MAX_SPREAD )
		{
			Tracer::warning(ClassId, Blob() << "Spread must be between " << AL_ECHO_MIN_SPREAD << " and " << AL_ECHO_MAX_SPREAD << ".");

			return;
		}

		EFX::alEffectf(this->identifier(), AL_ECHO_SPREAD, value);
	}

	float
	Echo::delay () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetEffectf(this->identifier(), AL_ECHO_DELAY, &value);

		return value;
	}

	float
	Echo::LRDelay () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetEffectf(this->identifier(), AL_ECHO_LRDELAY, &value);

		return value;
	}

	float
	Echo::damping () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetEffectf(this->identifier(), AL_ECHO_DAMPING, &value);

		return value;
	}

	float
	Echo::feedBack () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetEffectf(this->identifier(), AL_ECHO_FEEDBACK, &value);

		return value;
	}

	float
	Echo::spread () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetEffectf(this->identifier(), AL_ECHO_SPREAD, &value);

		return value;
	}
}
