/*
 * src/Audio/Effects/Distortion.cpp
 * This file is part of Emeraude-Engine
 *
 * Copyright (C) 2010-2025 - Sébastien Léon Claude Christian Bémelmans "LondNoir" <londnoir@gmail.com>
 *
 * Emeraude-Engine is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * Emeraude-Engine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Emeraude-Engine; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 * Complete project and additional information can be found at :
 * https://github.com/londnoir/emeraude-engine
 *
 * --- THIS IS AUTOMATICALLY GENERATED, DO NOT CHANGE ---
 */

#include "Distortion.hpp"

/* Local inclusions. */
#include "Tracer.hpp"
#include <Audio/OpenAL.EFX.hpp>
#include "Audio/Utility.hpp"

namespace EmEn::Audio::Effects
{
	using namespace EmEn::Libs;

	Distortion::Distortion () noexcept
		: Abstract()
	{
		if ( this->identifier() == 0 )
			return;

		EFX::alEffecti(this->identifier(), AL_EFFECT_TYPE, AL_EFFECT_DISTORTION);

		if ( alGetErrors("alEffecti()", __FILE__, __LINE__) )
			Tracer::error(ClassId, "Unable to generate OpenAL Distortion effect !");
	}

	void
	Distortion::resetProperties () noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		EFX::alEffectf(this->identifier(), AL_DISTORTION_EDGE, AL_DISTORTION_DEFAULT_EDGE);
		EFX::alEffectf(this->identifier(), AL_DISTORTION_GAIN, AL_DISTORTION_DEFAULT_GAIN);
		EFX::alEffectf(this->identifier(), AL_DISTORTION_LOWPASS_CUTOFF, AL_DISTORTION_DEFAULT_LOWPASS_CUTOFF);
		EFX::alEffectf(this->identifier(), AL_DISTORTION_EQCENTER, AL_DISTORTION_DEFAULT_EQCENTER);
		EFX::alEffectf(this->identifier(), AL_DISTORTION_EQBANDWIDTH, AL_DISTORTION_DEFAULT_EQBANDWIDTH);
	}

	void
	Distortion::setEdge (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_DISTORTION_MIN_EDGE || value > AL_DISTORTION_MAX_EDGE )
		{
			Tracer::warning(ClassId, BlobTrait() << "ShapeEdge must be between " << AL_DISTORTION_MIN_EDGE << " and " << AL_DISTORTION_MAX_EDGE << ".");

			return;
		}

		EFX::alEffectf(this->identifier(), AL_DISTORTION_EDGE, value);
	}

	void
	Distortion::setGain (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_DISTORTION_MIN_GAIN || value > AL_DISTORTION_MAX_GAIN )
		{
			Tracer::warning(ClassId, BlobTrait() << "Gain must be between " << AL_DISTORTION_MIN_GAIN << " and " << AL_DISTORTION_MAX_GAIN << ".");

			return;
		}

		EFX::alEffectf(this->identifier(), AL_DISTORTION_GAIN, value);
	}

	void
	Distortion::setLowPassCutOff (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_DISTORTION_MIN_LOWPASS_CUTOFF || value > AL_DISTORTION_MAX_LOWPASS_CUTOFF )
		{
			Tracer::warning(ClassId, BlobTrait() << "Low-pass cut-off must be between " << AL_DISTORTION_MIN_LOWPASS_CUTOFF << " and " << AL_DISTORTION_MAX_LOWPASS_CUTOFF << ".");

			return;
		}

		EFX::alEffectf(this->identifier(), AL_DISTORTION_LOWPASS_CUTOFF, value);
	}

	void
	Distortion::setEQCenter (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_DISTORTION_MIN_EQCENTER || value > AL_DISTORTION_MAX_EQCENTER )
		{
			Tracer::warning(ClassId, BlobTrait() << "EQ center must be between " << AL_DISTORTION_MIN_EQCENTER << " and " << AL_DISTORTION_MAX_EQCENTER << ".");

			return;
		}

		EFX::alEffectf(this->identifier(), AL_DISTORTION_EQCENTER, value);
	}

	void
	Distortion::setEQBandWidth (float value) noexcept
	{
		if ( !EFX::isAvailable() )
			return;

		if ( value < AL_DISTORTION_MIN_EQBANDWIDTH || value > AL_DISTORTION_MAX_EQBANDWIDTH )
		{
			Tracer::warning(ClassId, BlobTrait() << "EQ bandwidth must be between " << AL_DISTORTION_MIN_EQBANDWIDTH << " and " << AL_DISTORTION_MAX_EQBANDWIDTH << ".");

			return;
		}

		EFX::alEffectf(this->identifier(), AL_DISTORTION_EQBANDWIDTH, value);
	}

	float
	Distortion::edge () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetEffectf(this->identifier(), AL_DISTORTION_EDGE, &value);

		return value;
	}

	float
	Distortion::gain () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetEffectf(this->identifier(), AL_DISTORTION_GAIN, &value);

		return value;
	}

	float
	Distortion::lowPassCutOff () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetEffectf(this->identifier(), AL_DISTORTION_LOWPASS_CUTOFF, &value);

		return value;
	}

	float
	Distortion::EQCenter () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetEffectf(this->identifier(), AL_DISTORTION_EQCENTER, &value);

		return value;
	}

	float
	Distortion::EQBandWidth () const noexcept
	{
		if ( !EFX::isAvailable() )
			return 0.0F;

		ALfloat value;

		EFX::alGetEffectf(this->identifier(), AL_DISTORTION_EQBANDWIDTH, &value);

		return value;
	}
}
